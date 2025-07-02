#include "LPC55S16.h"
#include "stdio.h"
#include "fsl_clock.h"
#include "Driver_I2C.h"
#include "Driver_Timer.h"


#define	FLEXCOMM_INDEX	    1
#define I2C_SLAVE_ADD		0xD0      //0xA8
#define WRITE_BIT			0x00
#define READ_BIT			0x01



uint8_t Error_flag;
extern uint8_t G_Battery_full;

//void i2c_Init(uint16_t mode);
//void i2c_start(uint8_t rw_bit);
//void i2c_Stop(void);

void i2c_Init(uint16_t mode)
	{
	CLOCK_AttachClk(kFRO12M_to_FLEXCOMM4);													//Muxing the clock pulse for flexcomm 4
	SYSCON->PRESETCTRLSET[FLEXCOMM_INDEX] |= 1<<15U;									//Flexcomm - 4 peripheral init
	while (0U == (SYSCON->PRESETCTRLX[FLEXCOMM_INDEX] & (1<<15U)))	//Verifying initialization
	{
	}
		SYSCON->PRESETCTRLCLR[FLEXCOMM_INDEX] |= 1<<15U;									//Flexcomm - 4 peripheral clear
		while ((1<<15U) == (SYSCON->PRESETCTRLX[FLEXCOMM_INDEX] & (1<<15U)))	//Verifying peripheral clearance
		{
		}

		IOCON->PIO[1][21] = (5 << 0U) | (1 << 8U);	// 5 - I2C data(pin mux with SPI also), 1 - digimode enable
		IOCON->PIO[1][20] = (5 << 0U) | (1 << 8U);	// 5 - I2C clock(pin mux with SPI also), 1 - digimode enable

		SYSCON->AHBCLKCTRLSET[FLEXCOMM_INDEX] |= 1<<15U;									//Flexcomm - 4 AHB clock initialized
		SYSCON->PRESETCTRLSET[FLEXCOMM_INDEX] |= 1<<15U;									//Flexcomm - 4 peripheral init

		while (0u == (SYSCON->PRESETCTRLX[FLEXCOMM_INDEX] & (1<<15U)))	//Verifying initialization
		{
		}
		SYSCON->PRESETCTRLCLR[FLEXCOMM_INDEX] |= 1<<15U;									//Flexcomm - 4 peripheral clear

		while ((1<<15U) == (SYSCON->PRESETCTRLX[FLEXCOMM_INDEX] & (1<<15U)))	//Verifying peripheral clearance
		{
		}

		//3 - I2C function selected, F - USART(4th),SPI(5th),I2C(6th),I2S(7th) present, 11-8 reserved, ID - 102(reset value)
		//			FLEXCOMM4->PSELID = 0x102043U;	//If I2C only is presented means enable pselid like this
		FLEXCOMM4->PSELID = 0x1020F3U;					//I2C only present
		I2C4->CFG = 0x01U;
		if(mode == I2C_SPEED_400)
		{
			I2C4->CLKDIV = 0x05U;								//100 - standard mode, for fast mode means CLKDIV = 0x05U;
			I2C4->MSTTIME = 0x01U;							//100 - standard mode, for fast mode means MSTTIME = 0x01U;
		}
		else
		{
			I2C4->CLKDIV = 0x07U;								//100 - standard mode, for fast mode means CLKDIV = 0x05U;
			I2C4->MSTTIME = 0x86U;							//100 - standard mode, for fast mode means MSTTIME = 0x01U;
		}
		I2C4->TIMEOUT = 0xFFFFU;
	}


void i2c_start(int rw_bit)
{
	uint16_t hold_time = 0;
	//Waiting to enable the MSTPENDING bit to be set internally in status register then only write possible in MSTCTL register
	while((I2C4->STAT & 0x01U) == 0)
	{
		hold_time++;
		if(hold_time > 1000)
		{
			hold_time = 0;
			I2C4->MSTCTL = 0x04U;//Passing stop command before sending the start if MSTPENDING bit is not send even after waiting upto 1000 counts
			break;
		}
	}
	I2C4->MSTDAT = I2C_SLAVE_ADD | rw_bit;
	I2C4->MSTCTL = 0x02U;
	}


void i2c_Stop(void)
{
	uint16_t hold_time = 0;
	//Waiting to enable the MSTPENDING bit to be set internally in status register then only write possible in MSTCTL register
	while((I2C4->STAT & 0x01U) == 0)
	{
		hold_time++;
		if(hold_time > 1000)
		{
		  hold_time = 0;
		  break;
		}
	}
	I2C4->MSTCTL = 0x04U;


}

uint32_t EEPROM_datawrite(uint16_t addrs1, uint32_t data, uint16_t bytes_val)
{

	uint32_t device_addr1 = addrs1;
	uint16_t no_of_write_byte = 4;		//+2 count is for address bytes(msb and lsb)
	uint8_t re_write_count = 0;
	uint8_t byte_count = 0, total_bytes = 0;
	uint8_t data_byte[6] = {0, 0, 0, 0, 0, 0};
	uint8_t data_write_byte[3] = {0, 0, 0};
	uint8_t Read_Write_Error = 0;
	uint32_t hold_time = 0;

//	GPIO->CLR[1]|=1<<15;


	delay_100us(10);

	//(((bytes_val-1)-(byte_count-2))*8) - logic is for shifting operation
	//				here (bytes_val - 1) - is for 0 to 3(if 4 bytes) - no. of bytes - 1
	//				(byte_count - 2) - is for getting 0 when writing msb as first byte
	//				* 8 means right shifting 8 bytes from actual byte value
	for(byte_count = 0; byte_count < bytes_val; byte_count++)
			{
			if(bytes_val >= 1)
					{
					data_byte[byte_count] = (data >> (((bytes_val-1)-byte_count)*8)) & 0x000000FF;
					}
			}

	if((device_addr1 >= 65535) && (bytes_val > 1))
			{
			Read_Write_Error = 1;
			Error_flag=1;
			}
		//    Error_flag=0;
	for(total_bytes = 0; ((total_bytes < bytes_val) && !Read_Write_Error); total_bytes++)
			{
			//For consecutive write operation device address msb and lsb also send in data_byte buffer
			data_write_byte[0] = (device_addr1 >> 8) & 0xFF;
			data_write_byte[1] = (device_addr1>> 0) & 0xFF;
			data_write_byte[2] = data_byte[total_bytes];

			i2c_start(WRITE_BIT);

			for(byte_count = 1; ((byte_count < no_of_write_byte) && !Read_Write_Error); byte_count++)
					{
					hold_time = 0;
					//Waiting to enable the MSTPENDING bit to be set internally in status register
					//				then only write possible in MSTCTL register
					while((I2C4->STAT & 0x01U) == 0)
							{
							hold_time++;
							if(hold_time > 1000)
									{
									hold_time = 0;
									break;
									}
							}
					//			PRINTF("write hold_time %d\n", hold_time);
							if(I2C4->STAT == 0x805U)	//Checks MASTER ready to transmitt or not
							{
								I2C4->MSTDAT = data_write_byte[byte_count-1];
								I2C4->MSTCTL = 0x01U;
							}
							else
							{
								i2c_Stop();
								delay_100us(50);
								byte_count = 0;
								re_write_count++;				//For re-starting and writing the data_bytes from the start byte
								if(re_write_count > 4)
								{
									Read_Write_Error = 1;	//After attempting 5 re-writes return no_of_write_byte as 0
							//	Error_flag=1;
								}
								Error_flag=0;
								i2c_start(WRITE_BIT);
							}

					//This 25micro seconds delay is needed for writing sequential 4 byte data without skipping the data bytes
					//			in case 24LC516 IC has no pull up resisitor in it
					//					delay25us()
					}
			i2c_Stop();
			delay_100us(100);
			if(device_addr1 < 65535)
			//	if(device_addr1 < 4294967296)

					{
				device_addr1++;
					}
			else
					{
					Read_Write_Error = 1;
					Error_flag=1;
					}
		//	Error_flag=0;
			//This 3 milli seconds delay is needed for writing continuous i2c_datawrite (data with diff eeprom address)
			//			without skipping the next i2c_datawrite becaz of MSTPENDING bit in I2C->STAT register is disabled
			//			have to be enable then only I2C->MSTCTL send start makes an effect if not it return error
	//		delay3ms();
			}
	no_of_write_byte = byte_count;//no of bytes successfully written

//	GPIO->SET[1]|=1<<15;   		//Always set the CE pin for Charging otherwise it affect the EEPROM while Self Test

	GPIO->SET[1]|=1<<22;


	//	GPIO->CLR[1]|=1<<22;
	return no_of_write_byte;
}



uint32_t EEPROM_dataread(uint16_t addrs, uint16_t byte_val)
{
	uint8_t addrs_count = 3, re_read_limit = 0;
	uint8_t Read_Write_Error = 0;
	uint8_t byte_count = 0;
	uint8_t re_write_limit = 0;	//For re-writing address byte
	uint32_t read_value = 0, hold_time = 0;
	uint8_t data_byte[4] = {0, 0, 0, 0}, addr_byte[2] = {0, 0};

//	GPIO->CLR[1]|=1<<15;

	addr_byte[0] = (addrs >> 8) & 0xFF;
	addr_byte[1] = (addrs >> 0) & 0xFF;

	if((addrs >= 65535) && (byte_val > 1))
			{
			Read_Write_Error = 1;
			//Error_flag=1;
			}
	//	Error_flag=0;
	i2c_start(WRITE_BIT);

	for(byte_count = 1; ((byte_count < addrs_count) && !Read_Write_Error); byte_count++)
			{
			//Waiting to enable the MSTPENDING bit to be set internally in status register
			//				then only write possible in MSTCTL register
			while((I2C4->STAT & 0x01U) == 0)
					{
					hold_time++;
					if(hold_time > 50000)
							{
							hold_time = 0;
							break;
							}
					}
			//		PRINTF("write hold_time %d\n", hold_time);
			if(I2C4->STAT == 0x805U)	//Checks MASTER ready to transmitt or not
					{
					I2C4->MSTDAT = addr_byte[byte_count-1];		//Writing address bytes as msb and lsb
					I2C4->MSTCTL = 0x01U;
					}
			else
					{
					i2c_Stop();
					delay_100us(10);
					re_write_limit++;
					byte_count = 0;
					if(re_write_limit > 4)
							{
							Read_Write_Error = 1;
						//	Error_flag=1;
							}
				//	Error_flag=0;
					i2c_start(WRITE_BIT);
					}
			}

	i2c_start(READ_BIT);
	hold_time = 0;
	for(byte_count = 1; ((byte_count < (byte_val+1)) && !Read_Write_Error); byte_count++)
			{
			//Waiting to enable the MSTPENDING bit to be set internally in status register
			//then only write possible in MSTCTL register
			while((I2C4->STAT & 0x01U) == 0)
					{
					hold_time++;
					if(hold_time > 50000)
							{
							hold_time = 0;
							break;
							}
					}
			//		PRINTF("write hold_time %d\n", hold_time);
			if(I2C4->STAT == 0x803U)	//Checks MASTER ready to receive or not
					{
					data_byte[byte_count-1] = I2C4->MSTDAT;
					I2C4->MSTCTL = 0x01U;
					}
			else
					{
					i2c_Stop();
					delay_100us(10);
					if(re_read_limit > 4)
							{
							Read_Write_Error = 1;
							Error_flag=1;
							}
				//	Error_flag=0;
					re_read_limit++;
					byte_count = 0;
					//Re-send start condition with read bit if master is other than pending and receive status
					i2c_start(READ_BIT);
					}
			}
	i2c_Stop();
	read_value = 0;

	//(((byte_val-1)-byte_count)*8) - logic is for shifting data_byte values and retun as a complete no of  bytes readed
	//				here (bytes_val - 1) - is for 0 to 3(if 4 bytes) - no. of bytes - 1
	//				(- byte_count) - is for getting 0 when writing msb as first byte
	//				* 8 means left shifting 8 bytes from actual byte value
	for(byte_count = 0; byte_count < byte_val; byte_count++)
			{
			read_value = read_value + ((uint32_t)data_byte[byte_count]<<(((byte_val-1)-byte_count)*8));
			//		PRINTF("0x%2x\t", data_byte[byte_count]);
			}
	//	PRINTF("\r\n\r\n");

//	if(!G_Battery_full)
//	{
//		GPIO->SET[1]|=1<<15;	//Always set the CE pin for Charging otherwise it affect the EEPROM while Self Test
//	}

	return read_value;
	}

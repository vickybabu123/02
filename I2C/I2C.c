///***************************************************************
//				        						Include files
//****************************************************************/
//#include "LPC55S16.h"
//#include "stdio.h"
//#include "fsl_clock.h"
//#include "Driver_I2C.h"
//#include "Driver_Timer.h"
//#include "TFT_String.h"
//#include "TFT_Commands.h"
//#include "Color.h"
///***************************************************************
//				        							Macro definition
//****************************************************************/
//
///*******************************Global variable********************************/
//
//#define	FLEXCOMM_INDEX	    1
//#define I2C_SLAVE_ADD		0xA8
//#define WRITE_BIT			0x00
//#define READ_BIT			0x01
//
//uint16_t i2c_time_F8,i2c_time_recheck;
//extern uint8_t i2c_time_;
//uint8_t slave_address;
//volatile uint8_t buf_length;
//uint8_t buf_rec_length;
//volatile uint8_t i2c0_busy;
//
//
//volatile uint8_t write_flag;
//volatile uint8_t read_flag;
//volatile uint8_t buf_rec_count;
//volatile uint8_t addr_hi;
//volatile uint8_t addr_lo;
//volatile uint8_t data_hi;
//volatile uint8_t data_hi1;
//volatile uint8_t data_hi2;
//volatile uint8_t data_lo;
//volatile uint8_t buf[3];
//volatile uint8_t buf_rec[1];
//
////extern unsigned long int keyvalue;
//
//volatile uint8_t buf_count;
//uint8_t condition_block;
//uint8_t Error_flag;
//
//uint16_t sd,we;
//uint8_t Read_Write_Error;
//extern uint16_t delay_ms;
//#define	FLEXCOMM_INDEX	    1
//
///****************************************************************/
//
///*
//*********************************************
//  Function Name : i2c_Init(uint16_t mode)
//  Description   :	I2C Initialisation
//  Input         : I2C mode
//  Output        : Void
//  Note          :
//*********************************************
//*/
//
//void i2c_Init(uint16_t mode)
//{
//	CLOCK_AttachClk(kFRO12M_to_FLEXCOMM4);													//Muxing the clock pulse for flexcomm 4
//	SYSCON->PRESETCTRLSET[FLEXCOMM_INDEX] |= 1<<15U;									//Flexcomm - 4 peripheral init
//	while (0U == (SYSCON->PRESETCTRLX[FLEXCOMM_INDEX] & (1<<15U)))	//Verifying initialization
//	{
//	}
//		SYSCON->PRESETCTRLCLR[FLEXCOMM_INDEX] |= 1<<15U;									//Flexcomm - 4 peripheral clear
//		while ((1<<15U) == (SYSCON->PRESETCTRLX[FLEXCOMM_INDEX] & (1<<15U)))	//Verifying peripheral clearance
//		{
//		}
//
//		IOCON->PIO[1][21] = (5 << 0U) | (1 << 8U);	// 5 - I2C data(pin mux with SPI also), 1 - digimode enable
//		IOCON->PIO[1][20] = (5 << 0U) | (1 << 8U);	// 5 - I2C clock(pin mux with SPI also), 1 - digimode enable
//
//		SYSCON->AHBCLKCTRLSET[FLEXCOMM_INDEX] |= 1<<15U;									//Flexcomm - 4 AHB clock initialized
//		SYSCON->PRESETCTRLSET[FLEXCOMM_INDEX] |= 1<<15U;									//Flexcomm - 4 peripheral init
//
//		while (0u == (SYSCON->PRESETCTRLX[FLEXCOMM_INDEX] & (1<<15U)))	//Verifying initialization
//		{
//		}
//		SYSCON->PRESETCTRLCLR[FLEXCOMM_INDEX] |= 1<<15U;									//Flexcomm - 4 peripheral clear
//
//		while ((1<<15U) == (SYSCON->PRESETCTRLX[FLEXCOMM_INDEX] & (1<<15U)))	//Verifying peripheral clearance
//		{
//		}
//
//		//3 - I2C function selected, F - USART(4th),SPI(5th),I2C(6th),I2S(7th) present, 11-8 reserved, ID - 102(reset value)
//		//			FLEXCOMM4->PSELID = 0x102043U;	//If I2C only is presented means enable pselid like this
//		FLEXCOMM4->PSELID = 0x1020F3U;					//I2C only present
//		I2C4->CFG = 0x01U;
//		if(mode == I2C_SPEED_400)
//		{
//			I2C4->CLKDIV = 0x05U;								//100 - standard mode, for fast mode means CLKDIV = 0x05U;
//			I2C4->MSTTIME = 0x01U;							//100 - standard mode, for fast mode means MSTTIME = 0x01U;
//		}
//		else
//		{
//			I2C4->CLKDIV = 0x7U;								//100 - standard mode, for fast mode means CLKDIV = 0x05U;
//			I2C4->MSTTIME = 0x86U;							//100 - standard mode, for fast mode means MSTTIME = 0x01U;
//		}
//		NVIC_SetPriority(FLEXCOMM4_IRQn,3);
//		I2C4->TIMEOUT = 0xFFFFU;
//}
//
///****************************************************************************
//* Function Name :
//* Arguments     :
//* Return type   :
//* Description   :
//
//*****************************************************************************/
////void FLEXCOMM4_IRQHandler(void)
////{
////	volatile uint16_t status=0;
////
////	status = I2C4->STAT;
//////	PID=(FLEXCOMM4->PID >> 16) & 0xFFF0;
//////PRINTF("%d\n",status);
////switch(status)
////   {
////
////			case 0x801:                                         // START CONDITION has been sent
////				if(i2c0_busy)
////				{
////					if((buf_count==0)&&(condition_block==0))
////						I2C4->MSTDAT = SLAVE_ADDRESS_EEPROM;
////					if(condition_block==1) //
////					{
////						condition_block =0;
////						I2C4->MSTDAT = SLAVE_ADDRESS_EEPROM | 1;
////					}
////					I2C4->MSTCTL = 0x02U;
////				}
////			break;
////
////			case 0x807:
////
////					I2C4->MSTCTL = 0x00U;
////					I2C4->INTENSET=0X00;
////					I2C4->INTENCLR=0X01;
////					i2c0_busy = 0;
////			break;
////
////			break;
////			case 0x805:	                                       //Data in I2DAT has been transmitted - Byte Address LSB , MSB and Data byte values
////
////				if(buf_count < buf_length)
////				{
////					I2C4->MSTDAT = buf[buf_count];
////					buf_count++;
////					I2C4->MSTCTL = 0x01U;
////
////				}
////				else if(write_flag==1)
////				{
////					I2C4->MSTCTL = 0x04U;
////					write_flag=0;
////					i2c0_busy = 0;
//////					I2C4->INTENCLR=0X01;
////				}
////				else if(read_flag==1)
////				{
////					read_flag=0;
////					condition_block=1;
////					I2C4->MSTCTL = 0x04U;
////				}
////			break;
////			case 0x803:                                          // Data byte value has been received
////					buf_rec[buf_rec_count] = I2C4->MSTDAT ;
////					buf_rec_count++;
////				  if(buf_rec_count < buf_rec_length)
////				  {
////					  I2C4->MSTCTL = 0x01U;
////				}
////				else
////				{
////					I2C4->MSTCTL = 0x04U;
//// 					i2c0_busy = 0;
////					buf_rec_count=0;
//////					I2C4->INTENCLR=0X01;
////				}
//////				i2c0_busy = 0;
////			   break;
////
////   }
////
////}
//
///****************************************************************************
//* Function Name :
//* Arguments     :
//* Return type   :
//* Description   :
//
//*****************************************************************************/
//
////uint32_t EEPROM_datawrite(uint16_t addrs, uint32_t data, uint16_t bytes_val)  //REW_UP
////{
////		uint8_t byte_wcount=0;//,safety_rewrie=0,rewrite_limit=0;
////		uint32_t i=0;
////		uint16_t temp_addrs=addrs;
////	//	uint16_t hold_time=0;
////
////		GPIO->CLR[1]|=1<<22;
////		for(byte_wcount=0;byte_wcount<bytes_val;byte_wcount++)
////		{
////
////// 			if(safety_rewrie==1)
////// 				byte_wcount=0;
////
////			write_flag=1;
////			read_flag=0;
////
////			i2c0_busy = 1;  // set to status to 'busy'
////
////			//slave_address = 0xA0; change to macro
////
////			temp_addrs=addrs+byte_wcount;       //Register address
////
////			addr_hi = (temp_addrs>>8) & 0xFF;
////			addr_lo = temp_addrs & 0xFF;
////			buf[0] = addr_hi;
////			buf[1] = addr_lo;
////
////			if(bytes_val==4) // WHILE WRITTING MORE THAN 1 BYTES VALUE , FALSE VALUE IS RETURNING
////			{
////				data_hi2 = (data>>24) & 0xFF;
////				data_hi1 = (data>>16) & 0xFF;
////				data_hi  = (data>>8)  & 0xFF;
////				data_lo  = (data)     & 0xFF;
////
////				if(byte_wcount==0)
////					buf[2] = data_hi2;
////				else if(byte_wcount==1)
////					buf[2] = data_hi1;
////				else if(byte_wcount==2)
////					buf[2] = data_hi;
////				else if(byte_wcount==3)
////					buf[2] = data_lo;
////			}
////			else if(bytes_val==3)
////			{
////				data_hi1 = (data>>16) & 0xFF;
////				data_hi = (data>>8) & 0xFF;
////				data_lo = data & 0xFF;
////
////				if(byte_wcount==0)
////					buf[2] = data_hi1;
////				else if(byte_wcount==1)
////					buf[2] = data_hi;
////				else if(byte_wcount==2)
////					buf[2] = data_lo;
////
////			}
////			else if(bytes_val==2)
////			{
////				data_hi = (data>>8) & 0xFF;
////				data_lo = data & 0xFF;
////
////				if(byte_wcount==0)
////					buf[2] = data_hi;
////				else if(byte_wcount==1)
////					buf[2] = data_lo;
////
////			}
////			else if(bytes_val==1)
////			{
////				data_lo = data & 0xFF;
////				buf[2] = data_lo;
////			}
////
////			buf_length=3;
////			buf_count = 0;
////			NVIC_EnableIRQ(FLEXCOMM4_IRQn);
////			I2C4->INTENSET=0X01;
////			for(i=0;i<=10000;i++)
////			{
////
////			}
////			I2C4->MSTCTL = 0x02U;
////			i2c_time_F8=1;
////
////			while(i2c0_busy) // wait for completion
////			{
////				if(i2c_time_F8==0) // for 6006 hang
////				{
//////					i2c_Init(I2C_SPEED_100);
////					i2c0_busy=0;
////					break;
////				}
////			}
////
////			i2c_time_F8=0;
////			i2c_time_=0;
////
////			NVIC_DisableIRQ(FLEXCOMM4_IRQn);
////			while(I2C4->INTSTAT & 0X01);
////			I2C4->INTENCLR=0X01;
//////			for(i=0;i<=100000;i++)
//////			{
//////
//////			}
////			delay_ms(5);
////		}
////		GPIO->SET[1]|=1<<22;
////	 return byte_wcount;
////}
//
///****************************************************************************
//* Function Name :
//* Arguments     :
//* Return type   :
//* Description   :
//
//*****************************************************************************/
//
////uint32_t EEPROM_dataread(uint16_t addrs, uint16_t byte_val)//REW_UP
////{
////		uint8_t byte_rcount=0,re_read_limit=0,safety_reread=0;
////		volatile uint16_t temp_addrs=0;
////		uint32_t value=0,i=0;
//////		uint16_t hold_time=0;
////
////
////		for(byte_rcount=0;byte_rcount<byte_val;byte_rcount++)
////		{
////// 			if (i2c0_busy == 1)
////// 					return 0;
////
//////			if(safety_reread==1)
//////				byte_rcount=0;
////
////			i2c0_busy = 1;
////			buf_count = 0;
////			buf_length = 2;
////			buf_rec_count=0;
////
////			read_flag=1;
////			write_flag=0;
////
////			temp_addrs=addrs+byte_rcount;       //Register address
////			addr_hi = (temp_addrs>>8) & 0xFF;
////			addr_lo =  temp_addrs & 0xFF;
////			buf[0]  = addr_hi;
////			buf[1]  = addr_lo;
////			condition_block = 0;
////			buf_rec_length =1;
////			buf_rec[0]=0;
////			buf_rec_count=0;
////
////			I2C4->INTENSET=0X01;
//////			Font_Select(ARIAL_14);
//////			TFT_Number(30,70,8,YELLOW,RED);
////
////			NVIC_EnableIRQ(FLEXCOMM4_IRQn);
////
//////			Font_Select(ARIAL_14);
//////			TFT_Number(60,70,9,YELLOW,RED);
////			for(i=0;i<=10000;i++)
////			{
////
////			}
////			I2C4->MSTCTL = 0x02U;
////
//////			i2c_time_recheck=0;
////			i2c_time_F8=1;
////			while (i2c0_busy)   // wait for completion
////			{
////				if(i2c_time_F8==0) // for 6006 hang
////				{
////					i2c0_busy=0;
////					break;
////				}
//////				if(++i2c_time_recheck > 40000)
//////				{ 																					//again Read the same byte,i2c0_busy flag not clear
//////					re_read_limit++;
//////					if(byte_rcount==0)
//////						safety_reread=1;
//////					else
//////						byte_rcount=byte_rcount-1;
//////					i2c0_busy=0;
//////					break;
//////				}
////			}
////
////			i2c_time_F8=0;
////		    i2c_time_=0;
////			I2C4->INTENCLR=0X01;
////			NVIC_DisableIRQ(FLEXCOMM4_IRQn);
////			while(I2C4->INTSTAT & 0X01);
////
////			if(re_read_limit>=3)
////			{                        // read operation fail more than 3 times,Read_Write_Error flag =1
////				Read_Write_Error=1;
////				return 0;
////			}
////
////			if(byte_rcount==0)
////				value=buf_rec[0];
////			if(byte_rcount==1)
////				value=(value<<8) | buf_rec[0];
////			if(byte_rcount==2)
////				value=(value<<8) | buf_rec[0];
////			if(byte_rcount==3)
////				value=(value<<8) | buf_rec[0];
////		   if(byte_rcount>3) break;
////			for(i=0;i<=1000;i++)
////			{
////
////			}
////		}
////
//////		for(i=0;i<=1000;i++)
//////		{
//////
//////		}
////		delay_ms(5);
////		read_flag=0;
////
////		return value;
////
////}
///*****************************************************************
//					        									End of file
//******************************************************************/
//uint32_t EEPROM_datawrite(uint16_t addrs1, uint32_t data, uint16_t bytes_val)
//{
//	uint32_t device_addr1 = addrs1;
//	uint16_t no_of_write_byte = 4;		//+2 count is for address bytes(msb and lsb)
//	uint8_t re_write_count = 0;
//	uint8_t data_byte[6] = {0, 0, 0, 0, 0, 0};
//	uint8_t data_write_byte[3] = {0, 0, 0};
//	uint8_t Read_Write_Error = 0;
//
//	volatile uint32_t hold_time = 0;
//	volatile uint8_t byte_count = 0;
//	volatile uint8_t  total_bytes = 0;
//
//	GPIO->CLR[1]|=1<<22;      //write production
//	delay_100us(10);
//
//	//(((bytes_val-1)-(byte_count-2))*8) - logic is for shifting operation
//	//				here (bytes_val - 1) - is for 0 to 3(if 4 bytes) - no. of bytes - 1
//	//				(byte_count - 2) - is for getting 0 when writing msb as first byte
//	//				* 8 means right shifting 8 bytes from actual byte value
//
//	for(byte_count = 0; byte_count < bytes_val; byte_count++)
//	{
//		if(bytes_val >= 1)
//		{
//			data_byte[byte_count] = (data >> (((bytes_val-1)-byte_count)*8)) & 0x000000FF;
//		}
//	}
//
//	if((device_addr1 >= 65535) && (bytes_val > 1))
//	{
//		Read_Write_Error = 1;
//		Error_flag=1;
//	}
//			for(total_bytes = 0; ((total_bytes < bytes_val) && !Read_Write_Error); total_bytes++)
//			{
//			//For consecutive write operation device address msb and lsb also send in data_byte buffer
//				data_write_byte[0] = (device_addr1 >> 8) & 0xFF;
//				data_write_byte[1] = (device_addr1>> 0) & 0xFF;
//				data_write_byte[2] = data_byte[total_bytes];
//
//				i2c_start(WRITE_BIT);
//
//			for(byte_count = 1; ((byte_count < no_of_write_byte) && !Read_Write_Error); byte_count++)
//			{
//					hold_time = 0;
//					//Waiting to enable the MSTPENDING bit to be set internally in status register
//					//				then only write possible in MSTCTL register
//					while((I2C4->STAT & 0x01U) == 0)
//						{
//							hold_time++;
//							if(hold_time > 1000)
//							{
//								hold_time = 0;
//								break;
//							}
//						}
//					//			PRINTF("write hold_time %d\n", hold_time);
//							if(I2C4->STAT == 0x805U)	//Checks MASTER ready to transmitt or not
//							{
//								I2C4->MSTDAT = data_write_byte[byte_count-1];
//								I2C4->MSTCTL = 0x01U;
//							}
//							else
//							{
//								i2c_Stop();
//								delay_100us(50);
//								byte_count = 0;
//								re_write_count++;				//For re-starting and writing the data_bytes from the start byte
//								if(re_write_count > 4)
//								{
//									Read_Write_Error = 1;	//After attempting 5 re-writes return no_of_write_byte as 0
//							//	Error_flag=1;
//								}
//								Error_flag=0;
//								i2c_start(WRITE_BIT);
//							}
//
//					//This 25micro seconds delay is needed for writing sequential 4 byte data without skipping the data bytes
//					//			in case 24LC516 IC has no pull up resisitor in it
//					//					delay25us()
//					}
//			i2c_Stop();
//			delay_100us(100);
//			if(device_addr1 < 65535)
//			{
//				device_addr1++;
//			}
//			else
//			{
//				Read_Write_Error = 1;
//				Error_flag=1;
//			}
//			//	Error_flag=0;
//			//This 3 milli seconds delay is needed for writing continuous i2c_datawrite (data with diff eeprom address)
//			//			without skipping the next i2c_datawrite becaz of MSTPENDING bit in I2C->STAT register is disabled
//			//			have to be enable then only I2C->MSTCTL send start makes an effect if not it return error
//			//		delay3ms();
//			}
//	no_of_write_byte = byte_count;//no of bytes successfully written
//	GPIO->SET[1]|=1<<22;
//
//	return no_of_write_byte;
//}
//
//uint32_t EEPROM_dataread(uint16_t addrs, uint16_t byte_val)
//{
//	 uint8_t addrs_count = 3, re_read_limit = 0;
//	 uint8_t Read_Write_Error = 0;
//	uint8_t byte_count = 0;
//	uint8_t re_write_limit = 0;	//For re-writing address byte
//	 uint32_t read_value = 0, hold_time = 0;
//	 volatile uint8_t data_byte[4] = {0, 0, 0, 0}, addr_byte[2] = {0, 0};
//
//	addr_byte[0] = (addrs >> 8) & 0xFF;
//	addr_byte[1] = (addrs >> 0) & 0xFF;
//
//	if((addrs >= 65535) && (byte_val > 1))
//	{
//		Read_Write_Error = 1;
//		//Error_flag=1;
//	}
//	//	Error_flag=0;
//	i2c_start(WRITE_BIT);
//
//	for(byte_count = 1; ((byte_count < addrs_count) && !Read_Write_Error); byte_count++)
//			{
//			//Waiting to enable the MSTPENDING bit to be set internally in status register
//			//				then only write possible in MSTCTL register
//			while((I2C4->STAT & 0x01U) == 0)
//			{
//				hold_time++;
//				if(hold_time > 10000)
//				{
//					hold_time = 0;
//					break;
//				}
//			}
//			//		PRINTF("write hold_time %d\n", hold_time);
//			if(I2C4->STAT == 0x805U)	//Checks MASTER ready to transmitt or not
//			{
//				I2C4->MSTDAT = addr_byte[byte_count-1];		//Writing address bytes as msb and lsb
//				I2C4->MSTCTL = 0x01U;
//			}
//			else
//			{
//				i2c_Stop();
//				delay_100us(10);
//				re_write_limit++;
//				byte_count = 0;
//				if(re_write_limit > 4)
//				{
//					Read_Write_Error = 1;
//					//	Error_flag=1;
//				}
//					//	Error_flag=0;
//				i2c_start(WRITE_BIT);
//			}
//			}
//
//	i2c_start(READ_BIT);
//	hold_time = 0;
//	for(byte_count = 1; ((byte_count < (byte_val+1)) && !Read_Write_Error); byte_count++)
//			{
//			//Waiting to enable the MSTPENDING bit to be set internally in status register
//			//then only write possible in MSTCTL register
//			while((I2C4->STAT & 0x01U) == 0)
//			{
//				hold_time++;
//			if(hold_time > 10000)
//			{
//				hold_time = 0;
//				break;
//			}
//					}
//			//		PRINTF("write hold_time %d\n", hold_time);
//			if(I2C4->STAT == 0x803U)	//Checks MASTER ready to receive or not
//					{
//					data_byte[byte_count-1] = I2C4->MSTDAT;
//					I2C4->MSTCTL = 0x01U;
//					}
//			else
//					{
//					i2c_Stop();
//					delay_100us(10);
//					if(re_read_limit > 4)
//							{
//							Read_Write_Error = 1;
//							Error_flag=1;
//							}
//				//	Error_flag=0;
//					re_read_limit++;
//					byte_count = 0;
//					//Re-send start condition with read bit if master is other than pending and receive status
//					i2c_start(READ_BIT);
//					}
//			}
//	i2c_Stop();
//	read_value = 0;
//
//	//(((byte_val-1)-byte_count)*8) - logic is for shifting data_byte values and retun as a complete no of  bytes readed
//	//				here (bytes_val - 1) - is for 0 to 3(if 4 bytes) - no. of bytes - 1
//	//				(- byte_count) - is for getting 0 when writing msb as first byte
//	//				* 8 means left shifting 8 bytes from actual byte value
//	for(byte_count = 0; byte_count < byte_val; byte_count++)
//			{
//			read_value = read_value + ((uint32_t)data_byte[byte_count]<<(((byte_val-1)-byte_count)*8));
//			//		PRINTF("0x%2x\t", data_byte[byte_count]);
//			}
//	//	PRINTF("\r\n\r\n");
//	return read_value;
//	}
//
//
//
//void i2c_start(int rw_bit)
//{
//	uint16_t hold_time = 0;
//	//Waiting to enable the MSTPENDING bit to be set internally in status register then only write possible in MSTCTL register
//	while((I2C4->STAT & 0x01U) == 0)
//	{
//		hold_time++;
//		if(hold_time > 1000)
//		{
//			hold_time = 0;
//			I2C4->MSTCTL = 0x04U;//Passing stop command before sending the start if MSTPENDING bit is not send even after waiting upto 1000 counts
//			break;
//		}
//	}
//	I2C4->MSTDAT = I2C_SLAVE_ADD | rw_bit;
//	I2C4->MSTCTL = 0x02U;
//	}
//
//
//void i2c_Stop(void)
//{
//	uint16_t hold_time = 0;
//	//Waiting to enable the MSTPENDING bit to be set internally in status register then only write possible in MSTCTL register
//	while((I2C4->STAT & 0x01U) == 0)
//	{
//		hold_time++;
//		if(hold_time > 1000)
//		{
//		  hold_time = 0;
//		  break;
//		}
//	}
//	I2C4->MSTCTL = 0x04U;
//
//
//}
//#include "LPC55S16.h"
//#include "stdio.h"
//#include "fsl_clock.h"
//#include "Driver_I2C.h"
//#include "Driver_Timer.h"
//
//
//#define	FLEXCOMM_INDEX	    1
//#define I2C_SLAVE_ADD		0xA8
//#define WRITE_BIT			0x00
//#define READ_BIT			0x01
//
//
//
//uint8_t Error_flag;
//
//
//
////void i2c_Init(uint16_t mode);
////void i2c_start(uint8_t rw_bit);
////void i2c_Stop(void);
//
//void i2c_Init(uint16_t mode)
//	{
//	CLOCK_AttachClk(kFRO12M_to_FLEXCOMM4);													//Muxing the clock pulse for flexcomm 4
//	SYSCON->PRESETCTRLSET[FLEXCOMM_INDEX] |= 1<<15U;									//Flexcomm - 4 peripheral init
//	while (0U == (SYSCON->PRESETCTRLX[FLEXCOMM_INDEX] & (1<<15U)))	//Verifying initialization
//	{
//	}
//		SYSCON->PRESETCTRLCLR[FLEXCOMM_INDEX] |= 1<<15U;									//Flexcomm - 4 peripheral clear
//		while ((1<<15U) == (SYSCON->PRESETCTRLX[FLEXCOMM_INDEX] & (1<<15U)))	//Verifying peripheral clearance
//		{
//		}
//
//		IOCON->PIO[1][21] = (5 << 0U) | (1 << 8U);	// 5 - I2C data(pin mux with SPI also), 1 - digimode enable
//		IOCON->PIO[1][20] = (5 << 0U) | (1 << 8U);	// 5 - I2C clock(pin mux with SPI also), 1 - digimode enable
//
//		SYSCON->AHBCLKCTRLSET[FLEXCOMM_INDEX] |= 1<<15U;									//Flexcomm - 4 AHB clock initialized
//		SYSCON->PRESETCTRLSET[FLEXCOMM_INDEX] |= 1<<15U;									//Flexcomm - 4 peripheral init
//
//		while (0u == (SYSCON->PRESETCTRLX[FLEXCOMM_INDEX] & (1<<15U)))	//Verifying initialization
//		{
//		}
//		SYSCON->PRESETCTRLCLR[FLEXCOMM_INDEX] |= 1<<15U;									//Flexcomm - 4 peripheral clear
//
//		while ((1<<15U) == (SYSCON->PRESETCTRLX[FLEXCOMM_INDEX] & (1<<15U)))	//Verifying peripheral clearance
//		{
//		}
//
//		//3 - I2C function selected, F - USART(4th),SPI(5th),I2C(6th),I2S(7th) present, 11-8 reserved, ID - 102(reset value)
//		//			FLEXCOMM4->PSELID = 0x102043U;	//If I2C only is presented means enable pselid like this
//		FLEXCOMM4->PSELID = 0x1020F3U;					//I2C only present
//		I2C4->CFG = 0x01U;
//		if(mode == I2C_SPEED_400)
//		{
//			I2C4->CLKDIV = 0x05U;								//100 - standard mode, for fast mode means CLKDIV = 0x05U;
//			I2C4->MSTTIME = 0x01U;							//100 - standard mode, for fast mode means MSTTIME = 0x01U;
//		}
//		else
//		{
//			I2C4->CLKDIV = 0x07U;								//100 - standard mode, for fast mode means CLKDIV = 0x05U;
//			I2C4->MSTTIME = 0x86U;							//100 - standard mode, for fast mode means MSTTIME = 0x01U;
//		}
//		I2C4->TIMEOUT = 0xFFFFU;
//	}
//
//
//void i2c_start(int rw_bit)
//{
//	uint16_t hold_time = 0;
//	//Waiting to enable the MSTPENDING bit to be set internally in status register then only write possible in MSTCTL register
//	while((I2C4->STAT & 0x01U) == 0)
//	{
//		hold_time++;
//		if(hold_time > 5000)
//		{
//			hold_time = 0;
//			I2C4->MSTCTL = 0x04U;//Passing stop command before sending the start if MSTPENDING bit is not send even after waiting upto 1000 counts
//			break;
//		}
//	}
//	I2C4->MSTDAT = I2C_SLAVE_ADD | rw_bit;
//	I2C4->MSTCTL = 0x02U;
//	}
//
//
//void i2c_Stop(void)
//{
//	uint16_t hold_time = 0;
//	//Waiting to enable the MSTPENDING bit to be set internally in status register then only write possible in MSTCTL register
//	while((I2C4->STAT & 0x01U) == 0)
//	{
//		hold_time++;
//		if(hold_time > 5000)
//		{
//		  hold_time = 0;
//		  break;
//		}
//	}
//	I2C4->MSTCTL = 0x04U;
//
//
//}
//
//uint32_t EEPROM_datawrite(uint16_t addrs1, uint32_t data, uint16_t bytes_val)
//{
//	uint32_t device_addr1 = addrs1;
//
//	uint16_t no_of_write_byte = 4;		//+2 count is for address bytes(msb and lsb)
//	uint8_t re_write_count = 0;
//	uint8_t byte_count = 0, total_bytes = 0;
//	uint8_t data_byte[6] = {0, 0, 0, 0, 0, 0};
//	uint8_t data_write_byte[3] = {0, 0, 0};
//	uint8_t Read_Write_Error = 0;
//	uint32_t hold_time = 0;
//	//	GPIO->SET[1]|=1<<22;
//
//	GPIO->CLR[1]|=1<<22;      //write production
//	//	GPIO->SET[1]|=1<<22;
//	delay_100us(10);
//
//	//(((bytes_val-1)-(byte_count-2))*8) - logic is for shifting operation
//	//				here (bytes_val - 1) - is for 0 to 3(if 4 bytes) - no. of bytes - 1
//	//				(byte_count - 2) - is for getting 0 when writing msb as first byte
//	//				* 8 means right shifting 8 bytes from actual byte value
//	for(byte_count = 0; byte_count < bytes_val; byte_count++)
//			{
//			if(bytes_val >= 1)
//					{
//					data_byte[byte_count] = (data >> (((bytes_val-1)-byte_count)*8)) & 0x000000FF;
//					}
//			}
//
//	if((device_addr1 >= 65535) && (bytes_val > 1))
//			{
//			Read_Write_Error = 1;
//			Error_flag=1;
//			}
//		//    Error_flag=0;
//	for(total_bytes = 0; ((total_bytes < bytes_val) && !Read_Write_Error); total_bytes++)
//			{
//			//For consecutive write operation device address msb and lsb also send in data_byte buffer
//			data_write_byte[0] = (device_addr1 >> 8) & 0xFF;
//			data_write_byte[1] = (device_addr1>> 0) & 0xFF;
//			data_write_byte[2] = data_byte[total_bytes];
//
//			i2c_start(WRITE_BIT);
//
//			for(byte_count = 1; ((byte_count < no_of_write_byte) && !Read_Write_Error); byte_count++)
//					{
//					hold_time = 0;
//					//Waiting to enable the MSTPENDING bit to be set internally in status register
//					//				then only write possible in MSTCTL register
//					while((I2C4->STAT & 0x01U) == 0)
//							{
//							hold_time++;
//							if(hold_time > 5000)
//									{
//									hold_time = 0;
//									break;
//									}
//							}
//					//			PRINTF("write hold_time %d\n", hold_time);
//							if(I2C4->STAT == 0x805U)	//Checks MASTER ready to transmitt or not
//							{
//								I2C4->MSTDAT = data_write_byte[byte_count-1];
//								I2C4->MSTCTL = 0x01U;
//							}
//							else
//							{
//								i2c_Stop();
//								delay_100us(50);
//								byte_count = 0;
//								re_write_count++;				//For re-starting and writing the data_bytes from the start byte
//								if(re_write_count > 4)
//								{
//									Read_Write_Error = 1;	//After attempting 5 re-writes return no_of_write_byte as 0
//							//	Error_flag=1;
//								}
//								Error_flag=0;
//								i2c_start(WRITE_BIT);
//							}
//
//					//This 25micro seconds delay is needed for writing sequential 4 byte data without skipping the data bytes
//					//			in case 24LC516 IC has no pull up resisitor in it
//					//					delay25us()
//					}
//			i2c_Stop();
//			delay_100us(100);
//			if(device_addr1 < 65535)
//			//	if(device_addr1 < 4294967296)
//
//					{
//				device_addr1++;
//					}
//			else
//					{
//					Read_Write_Error = 1;
//					Error_flag=1;
//					}
//		//	Error_flag=0;
//			//This 3 milli seconds delay is needed for writing continuous i2c_datawrite (data with diff eeprom address)
//			//			without skipping the next i2c_datawrite becaz of MSTPENDING bit in I2C->STAT register is disabled
//			//			have to be enable then only I2C->MSTCTL send start makes an effect if not it return error
//	//		delay3ms();
//			}
//	no_of_write_byte = byte_count;//no of bytes successfully written
//	GPIO->SET[1]|=1<<22;
//	//	GPIO->CLR[1]|=1<<22;
//	return no_of_write_byte;
//}
//
//
//
//uint32_t EEPROM_dataread(uint16_t addrs, uint16_t byte_val)
//{
//	uint8_t addrs_count = 3, re_read_limit = 0;
//	uint8_t Read_Write_Error = 0;
//	uint8_t byte_count = 0;
//	uint8_t re_write_limit = 0;	//For re-writing address byte
//	uint32_t read_value = 0, hold_time = 0;
//	uint8_t data_byte[4] = {0, 0, 0, 0}, addr_byte[2] = {0, 0};
//
//	addr_byte[0] = (addrs >> 8) & 0xFF;
//	addr_byte[1] = (addrs >> 0) & 0xFF;
//
//	if((addrs >= 65535) && (byte_val > 1))
//			{
//			Read_Write_Error = 1;
//			//Error_flag=1;
//			}
//	//	Error_flag=0;
//	i2c_start(WRITE_BIT);
//
//	for(byte_count = 1; ((byte_count < addrs_count) && !Read_Write_Error); byte_count++)
//			{
//			//Waiting to enable the MSTPENDING bit to be set internally in status register
//			//				then only write possible in MSTCTL register
//			while((I2C4->STAT & 0x01U) == 0)
//					{
//					hold_time++;
//					if(hold_time > 10000)
//							{
//							hold_time = 0;
//							break;
//							}
//					}
//			//		PRINTF("write hold_time %d\n", hold_time);
//			if(I2C4->STAT == 0x805U)	//Checks MASTER ready to transmitt or not
//					{
//					I2C4->MSTDAT = addr_byte[byte_count-1];		//Writing address bytes as msb and lsb
//					I2C4->MSTCTL = 0x01U;
//					}
//			else
//					{
//					i2c_Stop();
//					delay_100us(10);
//					re_write_limit++;
//					byte_count = 0;
//					if(re_write_limit > 4)
//							{
//							Read_Write_Error = 1;
//						//	Error_flag=1;
//							}
//				//	Error_flag=0;
//					i2c_start(WRITE_BIT);
//					}
//			}
//
//	i2c_start(READ_BIT);
//	hold_time = 0;
//	for(byte_count = 1; ((byte_count < (byte_val+1)) && !Read_Write_Error); byte_count++)
//			{
//			//Waiting to enable the MSTPENDING bit to be set internally in status register
//			//then only write possible in MSTCTL register
//			while((I2C4->STAT & 0x01U) == 0)
//					{
//					hold_time++;
//					if(hold_time > 10000)
//							{
//							hold_time = 0;
//							break;
//							}
//					}
//			//		PRINTF("write hold_time %d\n", hold_time);
//			if(I2C4->STAT == 0x803U)	//Checks MASTER ready to receive or not
//					{
//					data_byte[byte_count-1] = I2C4->MSTDAT;
//					I2C4->MSTCTL = 0x01U;
//					}
//			else
//					{
//					i2c_Stop();
//					delay_100us(10);
//					if(re_read_limit > 4)
//							{
//							Read_Write_Error = 1;
//							Error_flag=1;
//							}
//				//	Error_flag=0;
//					re_read_limit++;
//					byte_count = 0;
//					//Re-send start condition with read bit if master is other than pending and receive status
//					i2c_start(READ_BIT);
//					}
//			}
//	i2c_Stop();
//	read_value = 0;
//
//	//(((byte_val-1)-byte_count)*8) - logic is for shifting data_byte values and retun as a complete no of  bytes readed
//	//				here (bytes_val - 1) - is for 0 to 3(if 4 bytes) - no. of bytes - 1
//	//				(- byte_count) - is for getting 0 when writing msb as first byte
//	//				* 8 means left shifting 8 bytes from actual byte value
//	for(byte_count = 0; byte_count < byte_val; byte_count++)
//			{
//			read_value = read_value + ((uint32_t)data_byte[byte_count]<<(((byte_val-1)-byte_count)*8));
//			//		PRINTF("0x%2x\t", data_byte[byte_count]);
//			}
//	//	PRINTF("\r\n\r\n");
//	return read_value;
//	}

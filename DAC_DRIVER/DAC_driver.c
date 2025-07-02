///*
// * DAC_DRIVER.c
// *
// *  Created on: 12-Apr-2024
// *      Author: Software4
// */
//
//#include <stdint.h>
//#include "DAC_driver.h"
//#include "LPC55S16.h"
///**********************************************************
//  Function Name	 		:	uint16_t calculateADCResult(float voltage, unsigned int resolution)
//  Description   		: 	VOLTAGE TO ADC VALUE CONVERSION
//  Argument      		: 	voltage,resolution
//  Return Type   		: 	uint16_t
//  Date		         	: 	12/04/2024
//  Version		    	:
//**********************************************************/
//uint16_t calculateADCResult(float voltage, unsigned int resolution)
//{
//    return (uint16_t)(((float)resolution * voltage) / 3.3);
//}
//
///**********************************************************
//  Function Name	 		:	uint32_t DAC__datawrite(uint16_t addrs1,float voltage, uint16_t bytes_val)
//  Description   		: 	This function used to pass the voltage to the registered address and the total number of bytes of data.
//  Argument      		: 	addrs1,voltage,bytes_val
//  Return Type   		: 	uint32_t
//  Date		         	: 	12/04/2024
//  Version		    	:
//**********************************************************/
//
//uint32_t DAC__datawrite(uint16_t addrs1,float voltage, uint16_t bytes_val)
//{
//
//	uint32_t device_addr1 = addrs1;
//	uint16_t no_of_write_byte = 4;		//+2 count is for address bytes(msb and lsb)
//	uint8_t re_write_count = 0;
//	uint8_t byte_count = 0;
//	//uint8_t data_byte[6] = {0, 0, 0, 0, 0, 0};
//	uint8_t data_write_byte[3] = {0, 0, 0};
//	uint8_t Read_Write_Error = 0;
//	uint32_t hold_time = 0;
//	//uint8_t Error_flag=0;
//
//	uint16_t data=calculateADCResult(voltage,RESOLUTION);
//
//
//	IOCON->PIO[LATCH_PIN_PORT][LATCH_PIN]|=0X100;
//	GPIO->DIR[LATCH_PIN_PORT]|=1<<LATCH_PIN;
//
//	GPIO->SET[LATCH_PIN_PORT]|=1<<LATCH_PIN;
//
//	//	GPIO->SET[1]|=1<<22;
//	delay_us(100);
//
//
//	if((device_addr1 >= 65535) && (bytes_val > 1))
//	{
//		Read_Write_Error = 1;
//				//Error_flag=1;
//	}
//
//
//		data_write_byte[0] = (device_addr1>> 0) & 0xFF;
//
//		data_write_byte[1] = (data >> 8) & 0xFF;
//
//		data_write_byte[2] = (data >> 0) & 0xFF;
//
//		DAC_i2c_start(WRITE_BIT);
//
//		for(byte_count = 0; ((byte_count < 3) && !Read_Write_Error); byte_count++)
//				{
//					hold_time = 0;
//					//Waiting to enable the MSTPENDING bit to be set internally in status register
//					//				then only write possible in MSTCTL register
//					while((I2C4->STAT & 0x01U) == 0)
//							{
//							hold_time++;
//							if(hold_time > 1000)
//									{
//									hold_time = 0;
//									break;
//									}
//							}
//					//			PRINTF("write hold_time %d\n", hold_time);
//						if(I2C4->STAT == 0x805U)	//Checks MASTER ready to transmitt or not
//							{
//							I2C4->MSTDAT = data_write_byte[byte_count];
//							//printf("\nI2C4->MSTDAT = %d",I2C4->MSTDAT);
//							I2C4->MSTCTL = 0x01U;
//							}
//					else
//							{
//							DAC_i2c_Stop();
//							delay_us(1);
//							byte_count = 0;
//							re_write_count++;				//For re-starting and writing the data_bytes from the start byte
//							if(re_write_count > 4)
//							{
//								Read_Write_Error = 1;	//After attempting 5 re-writes return no_of_write_byte as 0
//						//		Error_flag=1;
//							}
//							//Error_flag=0;
//							DAC_i2c_start(WRITE_BIT);
//							}
//
//					//This 25micro seconds delay is needed for writing sequential 4 byte data without skipping the data bytes
//					//			in case 24LC516 IC has no pull up resisitor in it
//					//					delay25us()
//				}
//					DAC_i2c_Stop();
//					delay_us(10);
//					if(device_addr1 < 65535)
//					//	if(device_addr1 < 4294967296)
//
//							{
//								device_addr1++;
//							}
//					else
//							{
//							Read_Write_Error = 1;
//							//Error_flag=1;
//							}
//
//
//		no_of_write_byte = byte_count;//no of bytes successfully written
//		GPIO->CLR[LATCH_PIN_PORT]|=1<<LATCH_PIN;
//		//	GPIO->CLR[1]|=1<<22;
//	return no_of_write_byte;
//}
//
///**********************************************************
//  Function Name	 		:	void DAC_i2c_start(int rw_bit)
//  Description   		: 	This function used to START THE I2C WITH SLAVE READ/ WRITE BIT
//  Argument      		: 	rw_bit
//  Return Type   		: 	VOID
//  Date		         	: 	12/04/2024
//  Version		    	:
//**********************************************************/
//
//void DAC_i2c_start(int rw_bit)
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
//	I2C4->MSTDAT = DAC_SLAVE_ADD | rw_bit;
//	I2C4->MSTCTL = 0x02U;
//}
//
///**********************************************************
//  Function Name	 		:	void DAC_i2c_Stop(void)
//  Description   		: 	This function used to STOP THE I2C communication
//  Argument      		: 	rw_bit
//  Return Type   		: 	VOID
//  Date		         	: 	12/04/2024
//  Version		    	:
//**********************************************************/
//
//void DAC_i2c_Stop(void)
//{
//	uint16_t hold_time = 0;
//	//Waiting to enable the MSTPENDING bit to be set internally in status register then only write possible in MSTCTL register
//	while((I2C4->STAT & 0x01U) == 0)
//	{
//		hold_time++;
//		if(hold_time > 1000)
//		{
//			hold_time = 0;
//			break;
//		}
//	}
//	I2C4->MSTCTL = 0x04U;
//}


/*
 * DAC_DRIVER.c
 *
 *  Created on: 12-Apr-2024
 *      Author: Software4
 */

#include <stdint.h>
#include "DAC_driver.h"
#include "LPC55S16.h"
/**********************************************************
  Function Name	 		:	uint16_t calculateADCResult(float voltage, unsigned int resolution)
  Description   		: 	VOLTAGE TO ADC VALUE CONVERSION
  Argument      		: 	voltage,resolution
  Return Type   		: 	uint16_t
  Date		         	: 	12/04/2024
  Version		    	:
**********************************************************/
uint16_t calculateADCResult(float voltage, unsigned int resolution)
{
    return (uint16_t)(((float)resolution * voltage) / 3.3);
}
/**********************************************************
  Function Name	 		:	uint32_t DAC__datawrite(uint16_t addrs1,float voltage, uint16_t bytes_val)
  Description   		: 	This function used to pass the voltage to the registered address and the total number of bytes of data.
  Argument      		: 	addrs1,voltage,bytes_val
  Return Type   		: 	uint32_t
  Date		         	: 	12/04/2024
  Version		    	:
**********************************************************/
uint32_t DAC__datawrite(uint16_t addrs1,float voltage, uint16_t bytes_val)
{

	uint32_t device_addr1 = addrs1;
	uint16_t no_of_write_byte = 4;		//+2 count is for address bytes(msb and lsb)
	uint8_t re_write_count = 0;
	uint8_t byte_count = 0; //total_bytes = 0;
	//uint8_t data_byte[6] = {0, 0, 0, 0, 0, 0};
	uint8_t data_write_byte[3] = {0, 0, 0};
	uint8_t Read_Write_Error = 0;
	uint32_t hold_time = 0;
	//uint8_t Error_flag=0;

	uint16_t data=calculateADCResult(voltage,RESOLUTION);
//	data=100;

	IOCON->PIO[LATCH_PIN_PORT][LATCH_PIN]|=0X100;
	GPIO->DIR[LATCH_PIN_PORT]|=1<<LATCH_PIN;

	GPIO->SET[LATCH_PIN_PORT]|=1<<LATCH_PIN;

	//	GPIO->SET[1]|=1<<22;
	delay_us(100);


	if((device_addr1 >= 65535) && (bytes_val > 1))
	{
		Read_Write_Error = 1;
		//Error_flag=1;
	}


		data_write_byte[0] = (device_addr1>> 0) & 0xFF;

		data_write_byte[1] = (data >> 8) & 0xFF;

		data_write_byte[2] = (data >> 0) & 0xFF;

			DAC_i2c_start(WRITE_BIT);

		for(byte_count = 0; ((byte_count < 3) && !Read_Write_Error); byte_count++)
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
							I2C4->MSTDAT = data_write_byte[byte_count];
							//printf("\nI2C4->MSTDAT = %d",I2C4->MSTDAT);
							I2C4->MSTCTL = 0x01U;
							}
					else
							{
							DAC_i2c_Stop();
							delay_us(1);
							byte_count = 0;
							re_write_count++;				//For re-starting and writing the data_bytes from the start byte
							if(re_write_count > 4)
									{
									Read_Write_Error = 1;	//After attempting 5 re-writes return no_of_write_byte as 0
								//	Error_flag=1;
									}
							//Error_flag=0;
							DAC_i2c_start(WRITE_BIT);
							}

					//This 25micro seconds delay is needed for writing sequential 4 byte data without skipping the data bytes
					//			in case 24LC516 IC has no pull up resisitor in it
					//					delay25us()
				}
					DAC_i2c_Stop();
					delay_us(10);
					if(device_addr1 < 65535)
					//	if(device_addr1 < 4294967296)

							{
						device_addr1++;
							}
					else
							{
							Read_Write_Error = 1;
							//Error_flag=1;
							}


		no_of_write_byte = byte_count;//no of bytes successfully written
		GPIO->CLR[LATCH_PIN_PORT]|=1<<LATCH_PIN;
		//	GPIO->CLR[1]|=1<<22;
	return no_of_write_byte;
}
/**********************************************************
  Function Name	 		:	void DAC_i2c_start(int rw_bit)
  Description   		: 	This function used to START THE I2C WITH SLAVE READ/ WRITE BIT
  Argument      		: 	rw_bit
  Return Type   		: 	VOID
  Date		         	: 	12/04/2024
  Version		    	:
**********************************************************/
void DAC_i2c_start(int rw_bit)
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
	I2C4->MSTDAT = DAC_SLAVE_ADD | rw_bit;
	I2C4->MSTCTL = 0x02U;
}
/**********************************************************
  Function Name	 		:	void DAC_i2c_Stop(void)
  Description   		: 	This function used to STOP THE I2C communication
  Argument      		: 	rw_bit
  Return Type   		: 	VOID
  Date		         	: 	12/04/2024
  Version		    	:
**********************************************************/
void DAC_i2c_Stop(void)
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

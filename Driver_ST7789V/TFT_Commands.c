#include <TFT_Commands.h>
#include <stdio.h>
#include "stdint.h"
#include "LPC55S16.h"
#include "Driver_SPI.h"

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void ST7789V_PIN_conf(void)
{
	IOCON->PIO[0][9]|=0X100;        	//VDD






	IOCON->PIO[1][1]|=0X100;        	//Reset the TFT
	IOCON->PIO[1][3]|=0X100;        	//Enable the AO_Command

	GPIO->DIR[0]|=1<<9;
	GPIO->DIR[1]|=1<<4;
	GPIO->CLR[1]|=1<<4;

	GPIO->DIR[1]|=1<<1;
	GPIO->DIR[1]|=1<<3;

	GPIO->SET[0]|=1<<9;
//  GPIO->SET[1]|=1<<4;
	GPIO->SET[1]|=1<<1;
	GPIO->SET[1]|=1<<3;
}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void SPI_cmd(uint8_t value,uint8_t length)
{
	A0_COMMAND;           //Pin Low for sending command
	SPI_transfer(value,length);
}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void SPI_data(uint8_t value,uint8_t length)
{
	A0_DATA;					 //Pin high for sending data
	SPI_transfer(value,length);
}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void TFT_ST7789V_init(void)
{
	uint8_t gamma_data[14]={0xF0,0x00,0x0A,0x10,0x12,0x1B,0x39,0x44,0x47,0x28,0x12,0x10,0x16,0x1B};
	uint8_t nv_data[14]={0xF0,0x00,0x0A,0x10,0x11,0x1A,0x3B,0x34,0x4E,0x3A,0x17,0x16,0x21,0x22};

	uint8_t ps_cmd[9]={0xBB,0xC3,0xC4,0xC5,0xC6,0x3A,0x36,0xD0,0xCC};
	uint8_t ps_data[9]={0x2B,0x17,0x20,0x23,0x01,0x05,0x40,0xA4,0x20};


	//ST7789V_PIN_conf();

	RES_ENABLE;
	delay_us(10);

	RES_DISABLE;
	delay_us(10);
	RES_ENABLE;
	delay_us(10);
	SPI_cmd(0x11,_8_BIT);        // Sleep Out = 0x11, sleep in = 0x10
	delay_us(10);
	//**********************ST7789V Frame rate setting*********************//

	SPI_cmd(0xb2,_8_BIT); 	// porch control
	SPI_data(0x0c,_8_BIT);		// porch control in normal mode
	delay_us(5);
	SPI_data(0x0c,_8_BIT);		//Read Display Pixel Format
	delay_us(5);
	SPI_data(0x00,_8_BIT);		//NOP
	delay_us(5);
	SPI_data(0x33,_8_BIT);		//Vertical scrolling Definitioin
	delay_us(5);
	SPI_cmd(0xb7,_8_BIT);		// Gate control
	SPI_data(0x35,_8_BIT);		//Default value
	delay_us(5);
	//*******************ST7789V Power setting***********************//

	for(uint8_t loop=0;loop<9;loop++)
	{
		SPI_cmd(ps_cmd[loop],_8_BIT);		//VCOMS,  VCOMS is used for feed through voltage compensation
		SPI_data(ps_data[loop],_8_BIT);
		delay_us(5);
	}
//	SPI_cmd(0xbb,_8_BIT);		//VCOMS,  VCOMS is used for feed through voltage compensation
//	SPI_data(0x2b,_8_BIT);
//	delay_us(5);
//	SPI_cmd(0xc3,_8_BIT);		//VRH Set
//	SPI_data(0x17,_8_BIT);
//	delay_us(5);
//	SPI_cmd(0xc4,_8_BIT);
//	SPI_data(0x20,_8_BIT);		//VDV Set
//	delay_us(5);
//	SPI_cmd(0xc5,_8_BIT);		//VCOMS Offset Set
//	SPI_data(0x23,_8_BIT);
//	delay_us(5);
//	SPI_cmd(0xc6,_8_BIT);		//Frame Rate Control in Normal Mode
//	SPI_data(0x01,_8_BIT);
//	delay_us(5);
//	//SPI_cmd(0x38,_8_BIT);
//
//
//	SPI_cmd(0x3A,_8_BIT);		//Interface Pixel Format
//	//   SPI_data(0x56);		// 0‘101’ = 65K of RGB interface, 0‘101’ = 16bit/pixel
//	SPI_data(0x55,_8_BIT);		// 0‘101’ = 65K of RGB interface, 0‘101’ = 16bit/pixel
//
//
//	delay_us(5);
//	SPI_cmd(0x36,_8_BIT);		//Memory Data Access Control
//	SPI_data(0x40,_8_BIT);		//Column Address Order Control
//	delay_us(5);
//
//
//	SPI_cmd(0xd0,_8_BIT);		// Power Control 1
//	SPI_data(0xa4,_8_BIT);		//AVDD
//	delay_us(5);
//	SPI_data(0xa2,_8_BIT);     //A2 NOT ADDED
//	delay_us(5);
//	SPI_cmd(0xcc,_8_BIT);		// pwm frequency
//	SPI_data(0x20,_8_BIT);		//(0xFF); //(0X28)
//	delay_us(5);

	//*********************ST7789V gamma setting****************//



	SPI_cmd(0xe0,_8_BIT);		//Positive Voltage Gamma Control

	for(uint8_t loop=0;loop<14;loop++)
	{
		SPI_data(gamma_data[loop],_8_BIT);
		delay_us(5);
	}
//	SPI_data(0xf0,_8_BIT);
//	delay_us(5);
//	SPI_data(0x00,_8_BIT);
//	delay_us(5);
//	SPI_data(0x0a,_8_BIT);
//	delay_us(5);
//	SPI_data(0x10,_8_BIT);
//	delay_us(5);
//	SPI_data(0x12,_8_BIT);
//	delay_us(5);
//	SPI_data(0x1b,_8_BIT);
//	delay_us(5);
//	SPI_data(0x39,_8_BIT);
//	delay_us(5);
//	SPI_data(0x44,_8_BIT);
//	delay_us(5);
//	SPI_data(0x47,_8_BIT);
//	delay_us(5);
//	SPI_data(0x28,_8_BIT);
//	delay_us(5);
//	SPI_data(0x12,_8_BIT);
//	delay_us(5);
//	SPI_data(0x10,_8_BIT);
//	delay_us(5);
//	SPI_data(0x16,_8_BIT);
//	delay_us(5);
//	SPI_data(0x1b,_8_BIT);
//	delay_us(5);
	/******************************************************************/
	SPI_cmd(0xe1,_8_BIT);      //Negative Voltage Gamma Control
	for(uint8_t loop=0;loop<14;loop++)
	{
		SPI_data(nv_data[loop],_8_BIT);
		delay_us(5);
	}

//	SPI_data(0xf0,_8_BIT);
//	delay_us(5);
//	SPI_data(0x00,_8_BIT);
//	delay_us(5);
//	SPI_data(0x0a,_8_BIT);
//	delay_us(5);
//	SPI_data(0x10,_8_BIT);
//	delay_us(5);
//	SPI_data(0x11,_8_BIT);
//	delay_us(5);
//	SPI_data(0x1a,_8_BIT);
//	delay_us(5);
//	SPI_data(0x3b,_8_BIT);
//	delay_us(5);
//	SPI_data(0x34,_8_BIT);
//	delay_us(5);
//	SPI_data(0x4e,_8_BIT);
//	delay_us(5);
//	SPI_data(0x3a,_8_BIT);
//	delay_us(5);
//	SPI_data(0x17,_8_BIT);
//	delay_us(5);
//	SPI_data(0x16,_8_BIT);
//	delay_us(5);
//	SPI_data(0x21,_8_BIT);
//	delay_us(5);
//	SPI_data(0x22,_8_BIT);
//	delay_us(5);

	/******************************************************************/

	SPI_cmd(0x20,_8_BIT); //Invert mode display     // Memory Data Access Control - Defines direction of pixel Read/write operation
	delay_us(5);

	/****************************************************************************/
	SPI_cmd(0x36,_8_BIT);      // Memory Data Access Control - Defines direction of pixel Read/write operation
	SPI_data(0x84,_8_BIT);     //Row Address Order					//Invert mode display
//  SPI_data(0x40);            //Column Address Order			//Normal display
	delay_us(5);

//    SPI_cmd(0x21,_8_BIT);             // RGB interface
//    delay_us(5);

//	delay_us(5);

	SPI_cmd(0x51,_8_BIT);      //Negative Voltage Gamma Control
	SPI_data(0x05,_8_BIT);
	delay_us(5);

	// SPI_cmd(0x20,_8_BIT);      //
	// SPI_data(0x05);
	// delay_us(5);


	SPI_cmd(0x29,_8_BIT);     //  display on = 0x29, display off = 0x28
	delay_us(2);
}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void TFT_ST7789V_BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend)   //reentrant
{

	uint8_t Block_write_cmd[2]={0x2A,0x2B};
	uint8_t Block_write_data[8]={Xstart>>8,Xstart,Xend>>8,Xend,Ystart>>8,Ystart,Yend>>8,Yend};
	uint8_t loop=0;
	uint8_t loop_1=0;
//	for(uint8_t loop_1=0;loop_1<=1;loop_1++)
//	{
//		for(uint8_t loop=start_loop;loop<end_loop;loop++)
//		{
//			if((loop%start_loop)<1)
//			{
//			 SPI_cmd( Block_write_cmd[loop_1],_8_BIT);
//			 SPI_data(Block_write_data[loop],_8_BIT);
//			}
//
//			else
//			{
//			 SPI_data(Block_write_data[loop],_8_BIT);
//			}
//		}
//
//		 start_loop=4;
//		 end_loop=8;
//
//	}
//
//
	for(loop_1=0;loop_1<2;loop_1++)
	{
		SPI_cmd( Block_write_cmd[loop_1],_8_BIT);
		for(loop=0;loop<4;loop++)
		{
			SPI_data(Block_write_data[(loop_1*4)+loop],_8_BIT);
		}

	}





//  SPI_cmd(0x2A,_8_BIT);		//Column Address Set
//	SPI_data(Xstart>>8,_8_BIT);
//	SPI_data(Xstart,_8_BIT);
//	SPI_data(Xend>>8,_8_BIT);
//	SPI_data(Xend,_8_BIT);
//
//	SPI_cmd(0x2B,_8_BIT);		//Row Address Set
//	SPI_data(Ystart>>8,_8_BIT);
//	SPI_data(Ystart,_8_BIT);
//	SPI_data(Yend>>8,_8_BIT);
//	SPI_data(Yend,_8_BIT);

    SPI_cmd(0x2c,_8_BIT);		//Memory_write
}


/**********************************************************
  Function Name	 :	SPI_transfer(argument)
  Description   		: 	write data through SPI
  Argument      		: 	data
  Return Type   	: 	void
  Date		         	: 	8/4/2022
  Version		    	:	V0.03

**********************************************************/

void delay_us(unsigned int data)
{
	uint16_t delay = 0,delay3 = 0;
	for(delay = 0; delay < data; delay++)
	{
	//	for(delay1 = 0; delay1 < 125; delay1++);
	//	for(delay2 = 0; delay2 < 100; delay2++);
		for(delay3 = 0; delay3 < 10000; delay3++);
	}
}


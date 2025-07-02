#include <stdio.h>
#include "LPC55S16.h"
#include "Keypad.h"


Keys KEY;
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Keypad_Init()
{
	/******************************ENABLE_CLOCK_FOR_GPIO_AND_IOCON***************/

	/*********************************************************************************/


	/******************************COLUMN*******************************************/
	     SYSCON->AHBCLKCTRL.AHBCLKCTRL0|=1u<<13;
	     SYSCON->AHBCLKCTRL.AHBCLKCTRL0|=1u<<14;
	     IOCON->PIO[0][24]|=0X100;                            //[DIGITMODE=1]
	     IOCON->PIO[0][25]|=0X100;                            //[DIGITMODE=1]
	     IOCON->PIO[0][26]|=0X100;                            //[DIGITMODE=1]
	     IOCON->PIO[0][27]|=0X100;                            //[DIGITMODE=1]

	     GPIO->DIR[0]|=1<<24;                                  //Set as Output of Column 1
	     GPIO->DIR[0]|=1<<25;                                  //Set as Output of Column 2
	     GPIO->DIR[0]|=1<<26;                                  //Set as Output of Column  3
	     GPIO->DIR[0]|=1<<27;                                  //Set as Output of Column  4

//	   	 GPIO->SET[0]|=1<<24;                                  //High the p[0][1]
//	   	 GPIO->SET[0]|=1<<25;                                  //High the p[0][2]
//	   	 GPIO->SET[0]|=1<<26;                                  //High the p[0][5]
//	     GPIO->SET[0]|=1<<27;                                  //High the p[0][10]

   /*********************************************************************************/

	/********************************ROW*******************************************/

	     IOCON->PIO[0][20]|=0X120;                            //[DIGITMODE=1]
		 IOCON->PIO[0][21]|=0X120;                            //[DIGITMODE=1]
		 IOCON->PIO[0][22]|=0X120;                            //[DIGITMODE=1]

		 GPIO->DIR[0]&=~(1<<20);                                //Set as Input  of Row 3
	     GPIO->DIR[0]&=~(1<<21);                                //Set as Input of Row  4
	     GPIO->DIR[0]&=~(1<<22);                                //Set as Input of Row  4

	/********************************************************************************/
	     IOCON->PIO[0][13]|=0x100;       // PIN SELECTION for load cell
	     IOCON->PIO[0][14]|=0x100;
	     GPIO->DIR[0]&=~(1<<14);     	 // data input pin
	     GPIO->DIR[0]|=1u<<13;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :
*****************************************************************************/

void keypad_function()
{

	if(KEY.counter)
	   KEY.counter--;

	GPIO->SET[0]|=(Column1|Column2|Column3|Column4);
	if(!KEY.on_flag)
	{
		GPIO->CLR[0]|=Column1;
		GPIO->SET[0]|=Column2|Column3|Column4;
	}

	if(!(KEY_SC_PIN & (Row1)))
	{
		KEY.on_flag=1;
		KEY.scan=(KEY_PORT_SCAN);
	}

	if(!(KEY_SC_PIN & (Row2)))
	{
		KEY.on_flag=1;
		KEY.scan=(KEY_PORT_SCAN);
	}

	if(!(KEY_SC_PIN & (Row3)))
	{
		KEY.on_flag=1;
		KEY.scan=(KEY_PORT_SCAN);
	}

//	if(!(KEY_SC_PIN & (Row4)))
//	{
//	keyon=1;
//	key_scan_1=(KEY_PORT_SCAN);
//	}


	if(!KEY.on_flag)
	GPIO->SET[0]|=(Column1|Column2|Column3|Column4);
	if(!KEY.on_flag)
	{
	// PRINTF("COLUMN 2. \r\n");
		GPIO->CLR[0]|=Column2;
		GPIO->SET[0]|=Column1|Column3|Column4;
	}

	if(!(KEY_SC_PIN & (Row1)))
	{
		KEY.on_flag=1;
		KEY.scan=(KEY_PORT_SCAN);
	}

	if(!(KEY_SC_PIN & (Row2)))
	{
		KEY.on_flag=1;
		KEY.scan=(KEY_PORT_SCAN);
	}

	if(!(KEY_SC_PIN & (Row3)))
	{
		KEY.on_flag=1;
		KEY.scan=(KEY_PORT_SCAN);
	}

//	if(!(KEY_SC_PIN & (Row4)))
//	{
//	keyon=1;
//	key_scan_1=(KEY_PORT_SCAN);
//	}


	if(!KEY.on_flag)
	GPIO->SET[0]|=(Column1|Column2|Column3|Column4);
	if(!KEY.on_flag)
	{
	// PRINTF("COLUMN 2. \r\n");
		GPIO->CLR[0]|=Column3;
		GPIO->SET[0]|=Column1|Column2|Column4;
	}

	if(!(KEY_SC_PIN & (Row1)))
	{
		KEY.on_flag=1;
		KEY.scan=(KEY_PORT_SCAN);
	}

	if(!(KEY_SC_PIN & (Row2)))
	{
		KEY.on_flag=1;
		KEY.scan=(KEY_PORT_SCAN);
	}

	if(!(KEY_SC_PIN & (Row3)))
	{
		KEY.on_flag=1;
		KEY.scan=(KEY_PORT_SCAN);
	}

//	if(!(KEY_SC_PIN & (Row4)))
//	{
//	keyon=1;
//	key_scan_1=(KEY_PORT_SCAN);
//	}


	if(!KEY.on_flag)
	GPIO->SET[0]|=(Column1|Column2|Column3|Column4);
	if(!KEY.on_flag)
	{
	// PRINTF("COLUMN 2. \r\n");
		GPIO->CLR[0]|=Column4;
		GPIO->SET[0]|=Column1|Column2|Column3;
	}

	if(!(KEY_SC_PIN & (Row1)))
	{
		KEY.on_flag=1;
		KEY.scan=(KEY_PORT_SCAN);
	}

	if(!(KEY_SC_PIN & (Row2)))
	{
		KEY.on_flag=1;
		KEY.scan=(KEY_PORT_SCAN);
	}

	if(!(KEY_SC_PIN & (Row3)))
	{
		KEY.on_flag=1;
		KEY.scan=(KEY_PORT_SCAN);
	}

//	if(!(KEY_SC_PIN & (Row4)))
//	{
//	keyon=1;
//	key_scan_1=(KEY_PORT_SCAN);
//	}


	if(KEY.on_flag  &&  !KEY.counter)
	{
	//PRINTF("Before pressing. \r\n");
		KEY.count1++;
		KEY.counter=5;                               //It allows 5 miliseond ones to load the value

	if(KEY.count1>3)                               // 20 milisecond status checking allowed the button to do an operation
	{
	//PRINTF("After  pressing. \r\n");
		KEY.count1=0;
		KEY.value=KEY.scan;
	}
	}

	else if(!KEY.on_flag && !KEY.counter)
	{
	//PRINTF("KEY VALUE. \r\n");
		KEY.count2++;
		KEY.counter=10;
		KEY.count1=0;
	if(KEY.count2>5)              		 //  60 miliseconds to wait for execution of an function.
	{
	//PRINTF("KEY VALUE. \r\n");
		KEY.count2=0;
		KEY.value=0;
	}
	}
	KEY.on_flag=0;
}

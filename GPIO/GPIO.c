 #include "LPC55S16.h"
#include "Color.h"
#include "Driver_SPI.h"
#include "TFT_Commands.h"
#include "Shapes.h"
#include "TFT_String.h"
#include "clock_config.h"

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/


void GPIO_Init()
{
	SYSCON->AHBCLKCTRLSET[0]|= (1 << 0);       //Enable clock CLOCK_EnableClock(kCLOCK_Iocon)
	SYSCON->AHBCLKCTRLSET[0]|= (1<<13);
	SYSCON->AHBCLKCTRLSET[0]|= (1<<14);        //Enable the Clock for GPIO0
	SYSCON->AHBCLKCTRLSET[0]|= (1<<15);        //Enable the Clock for GPIO1

	IOCON->PIO[1][4]|=0X100;       		//LED Back Light
	GPIO->DIR[1]|=1<<4;
	GPIO->SET[1]|=1<<4;

	IOCON->PIO[1][5]|=0X100;
	GPIO->DIR[1]|=1<<5;
	GPIO->CLR[1]|=1<<5;

	IOCON->PIO[0][18]|=0X100;       //Disc switch
	GPIO->DIR[0]&=~(1<<18);

	IOCON->PIO[0][19]|=0X100;       //Release switch
	GPIO->DIR[0]&=~(1<<19);

//	IOCON->PIO[1][15]|=0X100;
//	GPIO->DIR[1]|=1<<15;
//	GPIO->SET[1]|=1<<15;

//	IOCON->PIO[1][4]|=0X100;
//	GPIO->DIR[1]|=1<<4;

	IOCON->PIO[0][13]|=0X100;
	GPIO->DIR[0]|=1<<13;
	GPIO->SET[0]|=1<<13;

	IOCON->PIO[0][14]|=0X100;       //Release switch
	GPIO->DIR[0]&=~(1<<14);

	IOCON->PIO[0][17]|=0X100;       //External Interrupt
	GPIO->DIR[0]&=~(1<<17);

	IOCON->PIO[1][8]|=0X100;       //Mains switch
	GPIO->DIR[1]&=~(1<<8);

	IOCON->PIO[1][22]|=0X100;       //Mains switch
	GPIO->DIR[1]|=(1<<22);

	IOCON->PIO[1][12]|=0X100;
	GPIO->DIR[1]|=1<<12;
	GPIO->CLR[1]|=1<<12;
}



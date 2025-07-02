 #include <stdio.h>
#include "stdint.h"
#include "LPC55S16.h"
#include <string.h>
#include <STEPPER.h>
#include "Motor.h"

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void DRV8428_Init(void)
{

	IOCON->PIO[1][23]|=0X100;                          //[DIGITMODE=1]
	IOCON->PIO[1][25]|=0X100;                          //[DIGITMODE=1]
	IOCON->PIO[1][24]|=0X100;                          //[DIGITMODE=1]
	IOCON->PIO[1][26]|=0X100;                          //[DIGITMODE=1]

	GPIO->DIR[1]|=1<<23;                                 //Set as output as NSLEEP.                        //Set as Output for NSLEEP and NFAULT
	GPIO->DIR[1]|=1<<24;                                 //Set as Output for ENABLE.
	GPIO->DIR[1]|=1<<25;                                 //Set as Output of DIRECTION.
	GPIO->DIR[1]|=1<<26;                                 //Set as Output of STEP.

	GPIO->SET[1]|=1<<24;                                 //High the p[0][24]
	GPIO->SET[1]|=1<<25;                                 //High the p[0][25]
	GPIO->SET[1]|=1<<23;                                 //High the p[1][23]
//  GPIO->SET[1]|=1<<26;                                 //High the p[1][26]

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void DRV8428_ENABLE(void)
{
  GPIO->SET[1]|=1<<24;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void DRV8428_DISABLE(void)
{

   GPIO->CLR[1]|=1<<24;

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void stepper_Forward(void)
{
	GPIO->CLR[1]|=1<<25;
  //DRV8428_ENABLE();
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void stepper_Reverse(void)
{
	GPIO->SET[1]|=1<<25;
}

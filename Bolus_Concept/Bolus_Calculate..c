/*
 * BOLUS_CALCULATE..c
 *
 *  Created on: 21-Sep-2023
 *      Author: Software4
 */


#include <infused_calculate.h>
#include "LPC55S16.h"
#include "Bolus_Header.h"
#include "FR_CALC.h"
#include "Driver_Timer.h"
#include <stdio.h>
#include "Color.h"
#include "stdint.h"
#include "TFT_Commands.h"
#include "TFT_String.h"
//#include "Keypad.h"
#include "Motor.h"


extern volatile uint8_t normal_run;
extern uint8_t Bolus_status_flag;
BOLUS BOL;

/*  bolus varibles and its usage
 1.   BOL.run_mode

    these flag used to check the whether the device in bolus mode or not
     -> if BOL.run_mode = 1: It is in bolus mode
     -> if BOL.run_mode = 0: It is not in bolus mode


2.   BOL.auto_purg_flag

     these flag used to identify the device run in AUTO/PURGE bolus mode or not
     -> if BOL.auto_purg_flag = 1: It is in AUTO bolus mode
     -> if BOL.auto_purg_flag = 0: It is in PURG bolus mode

3.   normal_run

     these flag used to identify the device run in normal run flowrate or not
     -> if normal_run = 1: device run in normal run flowrate
     -> if normal_run = 0: device not run in normal run flowrate


4.    bolus_mode

      these flag determine the device is going to run in AUTO bolus mode/ PURGE bolus mode
      ->bolus_mode = 0: device is going to run in PURGE bolus mode
      ->bolus_mode = 1: device is going to run in AUTO bolus mode
 */

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void auto_bolus_stop()
 {

	BOL.run_mode=0;
	Timer_disable();   //
	BOL.run_mode=0;

 }

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void bolus(uint8_t bolus_mode) /*** BOLUS START ***/
{
	BOL.run_mode=1; //
	BOL.temp_flowrate=MOT.flowrate;
	if(!Bolus_status_flag)
	{
		BOL.infused_ml=0;
	}
	//TFT_Number(10,90,99,YELLOW,WHITE);
	MR_Value_calculate(BOL.flowrate);
}

/*** BOLUS END ***/
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void bolus_mode_stop(void)
{
     if( (BOL.mode==1) )//&& (KEY.value != PURGE_KEY) ) // purge bolus stop
	 {
		BOL.run_mode=0;
		MOT.flowrate=BOL.temp_flowrate;
		Timer_disable();

		//printf("\n puge mode stopped");

		if(normal_run==1)
		{
			 bolus_to_normal_run();
		}

	 }
	 else if(BOL.mode==0)/*BOL.auto_purg_flag==1 new cond */      // auto bolus stop
		{
			 auto_bolus_stop();
		}
}


/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void bolus_to_normal_run(void)
{

	MOT.flowrate=BOL.temp_flowrate;
	MR_Value_calculate(MOT.flowrate);

}

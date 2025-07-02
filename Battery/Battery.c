
#include <FR_CALC.h>
#include <Boot_up.h>
#include <STEPPER.h>
#include "LPC55S16.h"
#include "Color.h"
#include "Driver_SPI.h"
#include "TFT_Commands.h"
#include "Shapes.h"
#include "TFT_String.h"
#include "clock_config.h"
#include "Keypad.h"
#include "GPIO.h"
#include "Flowrate_Screen.h"
#include "Driver_Timer.h"
#include "fsl_clock.h"
#include "PWM.h"
#include "Main_screen.h"
#include "Occlusion.h"
#include "Main_menu.h"
#include "Driver_ADC.h"
#include "Bolus_Header.h"
#include "Power_off.h"
#include "Driver_PINT.h"
#include "Driver_I2C.h"
#include "Dosage_mode.h"
#include "Alarm.h"
#include "battery.h"
#include "math.h"

bat_status  BAT_CHECK;
uint8_t G_Battery_full_flag=0;
uint8_t prev_main_flag;
uint8_t G_Bt_Low_timer=0;
uint8_t G_Battery_full=0;
uint8_t G_add=0;
uint8_t Current_value=0;
uint8_t Prev_value=0;
uint16_t G_Battery_err_ver=0;
uint16_t Batt_ADC;

extern uint8_t home_flag;
extern uint8_t batt_high_flag;
extern uint8_t home_return_flag;
extern uint8_t G_main_screen_flag;
extern uint8_t Battery_stat_delay;
extern uint8_t G_Bt_Low_Flag;
extern uint8_t G_Fr_sound_flag;

struct ADC_sampling{
	 uint16_t Raw_data[20];
	 uint8_t  current_pos;
	 uint16_t Sample_data;
	 uint8_t  Err_flag;
	 uint8_t  Err_count;
	 uint8_t  Fail_count;
	 uint32_t cumm_data;
	 uint8_t  count;
	}bat_sample;

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint16_t ADC_bat_status(uint16_t Raw_val, uint16_t Data_diff,uint8_t samples)
{
	bat_sample.cumm_data=0;

			if(!bat_sample.current_pos)
			{
				for(bat_sample.count=0;bat_sample.count<samples;bat_sample.count++)
				{
					bat_sample.Raw_data[bat_sample.count]=Raw_val;
				}
				bat_sample.current_pos=samples-1;
				bat_sample.Err_flag=0;
				bat_sample.Fail_count=0;
				bat_sample.Sample_data=Raw_val;
			}

			else if((Raw_val>=Data_diff && Raw_val>(bat_sample.Raw_data[bat_sample.current_pos]-Data_diff) &&

			Raw_val<(bat_sample.Raw_data[bat_sample.current_pos]+Data_diff) )
						||	( Raw_val<=Data_diff && Raw_val>0 && Raw_val<(bat_sample.Raw_data[bat_sample.current_pos]+Data_diff) ))//Linerity checking with differences 100

			{

			for(bat_sample.count=0;bat_sample.count<samples-1;bat_sample.count++)
			{
				bat_sample.Raw_data[bat_sample.count]=bat_sample.Raw_data[bat_sample.count+1];//FIFO METHOD TO LOAD THE VALUES IN THE SAMPLING
			}

			bat_sample.Raw_data[bat_sample.current_pos]=Raw_val;     //ZEROTH POSITION TO LOAD THE SAMPLING VALUES


			for(bat_sample.count=0;bat_sample.count<samples;bat_sample.count++)
			{
				bat_sample.cumm_data+=bat_sample.Raw_data[bat_sample.count];  //AVERAGING THE 10 SAMPLE DATA
			}

			bat_sample.Sample_data=bat_sample.cumm_data/samples;    //DIVIDED BY 10 TO GET THE AVERAGE

				//bat_sample.Sample_data=(bat_sample.Sample_data/10)*10;
				bat_sample.Sample_data=bat_sample.Sample_data;
			}
			else
			{
				bat_sample.current_pos	=	0;
			}
			return bat_sample.Sample_data;



	}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :
*****************************************************************************/

void batt_pin_init(void)
{

//	SYSCON->AHBCLKCTRLSET[0]|= (1<<14);        //Enable the Clock for GPIO0
//	SYSCON->AHBCLKCTRLSET[0]|= (1<<15);        //Enable the Clock for GPIO1

	IOCON->PIO[1][15]|=0X100;
    GPIO->DIR[1]|=1<<15;     		    	   //BATT_CE
	GPIO->SET[1]|=1<<15;

	IOCON->PIO[1][27]|=0X100;				   //(1<<4)|(1<<8);  					//4,8 func,digimode
	GPIO->DIR[1]&=~(1<<27);    				   //BAT_STAT   IP

	IOCON->PIO[1][28]|=0X100;				   //(1<<4)|(1<<8);
	GPIO->DIR[1]&=~(1<<28);    				   //BAT_PG   IP

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void batt_stat(void)
{
	uint8_t STAT_pin=0;


	if(!G_Battery_err_ver)
	{
		if(BATT_STAT)
		{
			STAT_pin=1;
		}
		else
		{
			STAT_pin=0;
		}
//		Font_Select(ARIAL_14);
//		TFT_Number(0,70,100,YELLOW,RED);
		//Current_value=STAT_pin;

		if(STAT_pin!=Prev_value)
		{
			G_add++;
			Prev_value=STAT_pin;
		}
		else
		{
			G_add=0;
		//	Prev_value=STAT_pin;

		}
		G_Battery_err_ver=9;
	}

     if(G_add >= 5)
     {
    	 G_add=0;
  //   	 Alarm(BATTERY_ERR);
     }



//	 Alarm(BATTERY_ERR);

//	switch(STAT_pin)    //0   1
//				{
//					case 0:
//
//					if(batt_high_flag==1)
//					{
//						BAT_CHECK.error_code=27;
//					//	Alarm(BATTERY_ERR);
//					}
////					else if(batt_high_flag==0)
////						{
////							BAT_CHECK.error_code=28;   //charge inprogress  T
////						}
////					else if(batt_high_flag==2)
////						{
////						BAT_CHECK.error_code=29;
////						}
//					break;
//
//
////					case 1:
////						if(batt_high_flag==1)
////						{
////							BAT_CHECK.error_code=30;        //IC sleep
////						}
//////						else if(batt_high_flag==0)
//////						{
//////							BAT_CHECK.error_code=31;   //charge complte
//////						}
//////						else if(batt_high_flag==2)
//////						{
//////							BAT_CHECK.error_code=32;
//////						}
////					break;
//				}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void power_status(void)
{
	static uint8_t pow_switch_cnt=0;

	if((GPIO->PIN[1] & 1<<8))  //(MAINS_PIN)
		{
			pow_switch_cnt++;
			if(pow_switch_cnt>5)
			{
				BATT.mode=0;
				pow_switch_cnt=5;
			}
		}

		else
		{
			BATT.mode=1;
			BATT.full=0;
			pow_switch_cnt=0;
		}


			if(prev_main_flag!=BATT.mode)
			{
				POW.mains_bat_swt_flag=1;
				prev_main_flag=BATT.mode;

				if(!home_flag)
				{

					if(!BATT.mode)
					{
						WARN_SOUND(2,1,2);
					//	delay_secs(1);
					}
					else
					{
						WARN_SOUND(2,1,2);
					//	delay_secs(1);
					}

				}
			}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void battery_status(void)
{
	uint16_t temp_bat_ADC=0;
	uint16_t battery_avg=0;
	float perc_val=0.0;

//    if(!Battery_stat_delay)
//    {
//    	Battery_stat_delay=1;
    	temp_bat_ADC=ADC_read(ADC_CH_BATTERY);
   // }

	temp_bat_ADC=(temp_bat_ADC/10)*10;//20-07-2024
	battery_avg=ADC_bat_status(temp_bat_ADC,150,5);//20-07-2024

//	if(temp_bat_ADC<899)
//	{
//		GPIO->SET[1]|=1<<15;
//	}
//
//	else
//	{
//		GPIO->CLR[1]|=1<<15;
//	}



	if(temp_bat_ADC < 890)
	{
		G_Battery_full=0;
	}
	else if((temp_bat_ADC>930))
	{
		if(home_flag)
			{
				if( (!G_Battery_full)  )
				{

					 //Notification(BATTERY_FULL_1);
					 //GPIO->CLR[1]|=1<<15;
					   G_Battery_full=1;
				}
			}
	}


	if(BATTERY_CRITICAL<=battery_avg)//20-07-2024
	{
		perc_val=(float)((float)(battery_avg-BATTERY_CRITICAL)/(float)(BATTERY_FULL-BATTERY_CRITICAL));
	}
	else
	{
		perc_val=0;
	}

	perc_val=perc_val*100.0;
	perc_val=ceil(perc_val);//20-07-2024
	BATT.percent=(uint8_t)perc_val;
	BATT.percent=(BATT.percent/2)*2;

//	if(BAT_CHECK.STAT_high)
//  {
//	    Alarm(BATTERY_ERR);
//      BAT_CHECK.error_code=0;
//  }


if(BATT.mode)
{
	if((!home_flag) && (!G_Fr_sound_flag))
	{
		if( ((BATT.percent>=15) && (BATT.percent<25)) && (!G_Bt_Low_timer) )
		{
			WARN_SOUND(3,1,3);
			G_Bt_Low_timer=5;
		//	G_Bt_Low_Flag=1;
		}
	}
}

	if(BATT.percent>99)
	{
		if(!BATT.mode)
		{
			if((!BATT.full) && (home_flag)) 					//&& (!G_Battery_full_flag))
			{
				BATT.full=1;

//				if(BATT.mode)
//				{
				//}
			}
		}
		BATT.percent=99;
	}

	if(BATT.percent<90)
	{
		BATT.full=0;
	}
//	  Font_Select(ARIAL_14);
//    TFT_Number(110,70,home_flag,NAVY,WHITE);
//    TFT_Number(110,90,G_Bt_Low_Flag,NAVY,WHITE);

	if((home_flag) || (home_return_flag)) //|| (BATT.mode)))
	{
		Battery_symbol();
	}

}

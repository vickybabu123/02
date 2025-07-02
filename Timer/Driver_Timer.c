//#include <FR_CALC.h>
#include <infused_calculate.h>
#include "LPC55S16.h"
#include "Driver_Timer.h"
#include "Driver_HX711.h"
#include "Bolus_Header.h"
#include "Keypad.h"
#include "FR_CALC.h"
#include "TFT_String.h"
#include "Color.h"
#include "TFT_Commands.h"
#include "../Menu_Setting/Main_Menu.h"
#include "Motor.h"
#include <Consumed_hrs.h>
#include "sound.h"
#include "Battery.h"

#define MR0_VALUE 	       96000       // 1500000    /* 1 milli Sec */
#define MR1_VALUE 	       96000       // 150000     /* 1 milli Sec */
#define MR2_VALUE 		   2880        // 4500       //30micro second timer
#define MR3_VALUE 		   9600        // 15000	     //100micro second timer

uint8_t buzzercount=0;
uint8_t soundontime=0;
uint8_t soundofftime=0;
uint8_t soundflag=0;
uint8_t soundduration=0;
uint8_t soundcount=0;
uint8_t bright_count=0;
uint8_t _1sec_delay=0;
uint8_t batt_high_flag=0;
uint8_t Battery_run=0;
uint8_t power_key_delay=0;
uint8_t rtc_power_read=0;
uint8_t Switch_power_read=0;
uint8_t Press_Back_Read=0;
uint8_t Bar_power_Read=0;
uint8_t Pressure_ADC_delay=0;
uint8_t pulse_clear_count=0;
uint8_t pulse_clear_flag=0;

extern uint8_t G_sound_level;
extern uint8_t G_bright_level;
extern uint16_t key_pressed;
extern uint16_t lock_time;
extern uint32_t sound_level[10];
extern uint8_t bright_ctrl[5];
extern uint8_t G_calib_run;
extern uint8_t device_check_cnt;
extern uint8_t cuts_sec;
extern uint8_t ondru;
extern uint8_t sy_size;
extern uint8_t G_Bt_Low_timer;
extern uint8_t G_Battery_Set_pin;
extern uint8_t near_to_end_cnt;
extern uint8_t near_to_target_cnt;
extern uint8_t common_warning_cnt;
extern uint16_t G_Battery_err_ver;

uint8_t pulse_counter;
uint8_t counter;
uint8_t calib_start;
uint8_t millisec;
uint8_t G_bol_count;
uint8_t Battery_stat_delay=0;
uint8_t Plunger_data_delay=0;
uint16_t count=1000;
uint8_t dummy=0;
uint32_t _100usec_count=0;
uint16_t _1msec_count=0;
uint16_t _100msec_count=0;
uint16_t _10msec_count=0;
uint16_t _1sec_count=0;
uint8_t auto_lock_time=0;
uint8_t Flag=0;
uint8_t timer_checker=0;
uint8_t ADC_delay;
uint8_t sd_time_delay=0;
volatile uint16_t micro_time_delay=0;
volatile uint16_t milli_time_delay=0;
volatile uint16_t secs_time_delay;
uint16_t Power_Interval_Delay=0;
uint16_t used_hrs_count=0;
uint32_t motor_pulse;
uint32_t MR_VALUE;
uint8_t sd_alarm_count_delay=0;
uint8_t run=0;
uint32_t checking_variable=0;
uint16_t press_run_alarm=0;
uint16_t Pump_idle=0;


extern int8_t attempt_count;
extern uint8_t sec_count;
uint8_t i2c_time_;
extern uint16_t i2c_time_F8;
extern uint8_t i2c0_busy;
extern uint16_t mute_count;

extern uint8_t G_run_count;
extern uint8_t G_calib_count;
extern volatile uint8_t normal_run;
extern volatile uint8_t waitingtime_1 ;

extern uint8_t G_strain_data_read_delay;
extern uint16_t G_strain_sec_count;
extern uint16_t G_store_val;
pulse_control PULSE;
extern uint8_t G_Disc_sw_time;
extern uint8_t G_RL_sw_time;
extern uint8_t siphonic_time;
extern uint8_t ON_Flag;
extern uint8_t G_start_cnt;
extern uint16_t auto_lock;
extern uint8_t G_SD_delay;
extern uint8_t G_warn_count;
extern uint8_t blink_drug_delay;
extern uint16_t sec_blink;
extern uint8_t G_serial_key;
extern uint8_t Bolus_reset_flag;
extern uint8_t anti_Bolus_flag;
extern uint8_t G_load_read_count;
extern ALM alarm_sound;
extern uint8_t purge_device_in;
extern uint8_t low_battery_flag;

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Timer0_Init(  )
{
	SYSCON->AHBCLKCTRLSET[1]|= 1<<26;       // Enables the clock for the Timer 0.
	SYSCON->CTIMERCLKSEL.CTIMERCLKSEL0	= 0x03;

	CTIMER0->CTCR	=	0x00;
	CTIMER0->TC		=	0x00;
	CTIMER0->PR		=	0x00;
	CTIMER0->PC		=	0x00;

	CTIMER0->MR[0]	 = MR_VALUE;
	CTIMER0->MCR		|= 1U<<0;			// Interrupt on Match0 compare
	CTIMER0->MCR		|= 1U<<1;			// Reset timer on Match 0.
	CTIMER0->TCR		|= 1U<<1;			// Manually Reset Timer0
	CTIMER0->TCR		&= ~(1U<<1); 		// Stop resetting the timer.
	CTIMER0->IR			|= 0xFF;			// Clear MR0 interrupt flag

	NVIC_SetPriority(CTIMER0_IRQn, 0);
	NVIC_EnableIRQ(CTIMER0_IRQn);			// Enable timer interrupt
//	NVIC_SetPriority(CTIMER0_IRQn,4);		// Enable timer interrupt
	CTIMER0->TCR		|= 1<<0; 			// Start timer

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Timer1_Init(uint32_t MR_VALUE)
{

	SYSCON->AHBCLKCTRLSET[1]|= 1<<27;      			// Enables the clock for the Timer 1.
	SYSCON->CTIMERCLKSEL.CTIMERCLKSEL1 = 0x03;

	CTIMER1->CTCR	= 0x00;
	CTIMER1->TC		= 0x00;
	CTIMER1->PR		= 0x00;
	CTIMER1->PC		= 0x00;

	CTIMER1->MR[1] = MR_VALUE;				 		// 149999999;
	CTIMER1->MCR	|= 1U<<3;						// Interrupt on Match1 compare
	CTIMER1->MCR	|= 1U<<4;						// Reset timer on Match 1.
	CTIMER1->TCR	|= 1U<<1;						// Manually Reset Timer1
	CTIMER1->TCR	&= ~(1U<<1); 					// Stop resetting the timer.
	CTIMER1->IR		|= 0xFF;						// Clear MR1 interrupt flag

	NVIC_SetPriority(CTIMER1_IRQn, 0);
	NVIC_EnableIRQ(CTIMER1_IRQn);					// Enable timer interrupt
	CTIMER1->TCR	|= 1<<0; 						// Start timer
	//MFB.Min_pulse=0;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Timer2_Init()
{

	SYSCON->AHBCLKCTRLSET[1] |= 1<<22;              // Enables the clock for the Timer 2.
	SYSCON->CTIMERCLKSEL.CTIMERCLKSEL2  = 0x03;

	CTIMER2->CTCR	= 0x00;
	CTIMER2->TC		= 0x00;
	CTIMER2->PR		= 0x00;
	CTIMER2->PC		= 0x00;

	CTIMER2->MR[2] = MR2_VALUE;					   // 149999999;
	CTIMER2->MCR	|= 1U<<6;					   // Interrupt on Match2 compare
	CTIMER2->MCR	|= 1U<<7;					   // Reset timer on Match 2.
	CTIMER2->TCR	|= 1U<<1;					   // Manually Reset Timer2
	CTIMER2->TCR	&= ~(1U<<1);  				   // Stop resetting the timer.
	CTIMER2->IR		|= 0xFF;				       // Clear MR2 interrupt flag

	NVIC_SetPriority(CTIMER2_IRQn,1);
	NVIC_EnableIRQ(CTIMER2_IRQn);				   // Enable timer interrupt
//  NVIC_SetPriority(CTIMER2_IRQn,2);			   // Enable timer interrupt
	CTIMER2->TCR	|= 1<<0; 					   // Start timer

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Timer3_Init()
{

	SYSCON->AHBCLKCTRLSET[2] |= 1<<21;              // Enables the clock for the Timer 3.
	SYSCON->CTIMERCLKSEL.CTIMERCLKSEL3	= 0x03;

	CTIMER3->CTCR	= 0x00;
	CTIMER3->TC		= 0x00;
	CTIMER3->PR		= 0x00;
	CTIMER3->PC		= 0x00;

	CTIMER3->MR[3] = MR3_VALUE;                     // MR3_VALUE;//149999999;
	CTIMER3->MCR	|= 1U<<9;						// Interrupt on Match0 compare
	CTIMER3->MCR	|= 1U<<10;						// Reset timer on Match 3.
	CTIMER3->TCR	|= 1U<<1;						// Manually Reset Timer3
	CTIMER3->TCR	&= ~(1U<<1);  					// Stop resetting the timer.
	CTIMER3->IR		|= 0xFF;						// Clear MR3 interrupt flag

	NVIC_SetPriority(CTIMER3_IRQn, 3);
	NVIC_EnableIRQ(CTIMER3_IRQn);					// Enable timer interrupt

	CTIMER3->TCR	|= 1<<0; 					    // Start timer

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Timer_disable()
{
	NVIC_DisableIRQ(CTIMER1_IRQn);
	DAC__datawrite(0x00,0.0,2);
	DRV8428_DISABLE();
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

//void CTIMER0_IRQHandler(void)//REW_UP
//{
////	static uint8_t count=0;
//
////	if(CTIMER0->IR & 0x01)                   // MR0 interrupt
////		{
////			CTIMER0->IR|=1u<<0;
////		}
//}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void CTIMER1_IRQHandler(void)
{
	if(CTIMER1->IR & 0x02)                   // MR1 interrupt
	{
		CTIMER1->IR|=1u<<1;
		//PULSE.setclr++;

		if(!PULSE.setclr)
		{
			PULSE.setclr=1;
			GPIO->SET[1]|=1<<26 ;
			pulse_clear_count=5;
			pulse_clear_flag=1;
			//run++;
			PULSE.on=1;// off_pulse control flag
			PULSE.micro_sec=0; // off_pulse control flag
			pulse_counter++;

///////////////////////////MFB Verification////////////////////////////////////////////

			MFB.Pulse_count++;       //Motor reverse checking
			MFB.Motor_pulse++;       //Motor struck checking
			MFB.Min_pulse++;         // MFB cuts conform checking

			if(INFUSED.step_count)
			{
				INFUSED.step_count--;
			}

			else
			{
				if((!anti_Bolus_flag) && (G_calib_run!=1) )
				{
					if((normal_run) ||((BOL.mode<=1)) )//REW_UP
					{
						INFUSED.ml++;
					}
				}

				else
				{
					if(INFUSED.ml>1)
					{
						INFUSED.ml--;
					}
				}
					INFUSED.step_count = INFUSED.stepsper_point_1ml;

						if(BOL.run_mode==1)
						{
							BOL.infused_ml++;
						}
			}
		}

		else //if(PULSE.setclr==2)
		{
			GPIO->CLR[1]|=1<<26;
			PULSE.on=0;
			PULSE.micro_sec=0;
			PULSE.setclr=0;
		}
	}
}

/*
 * Function Name : void CTIMER2_IRQHandler(void)
 * Return type	 : void
 * Description   : In this handler function used for HX710 data
 *
 */

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void CTIMER2_IRQHandler(void)
 {
	//static unsigned int count_1;
  if(CTIMER2->IR & 0x04)    			 // MR2 interrupt
   {
	  CTIMER2->IR|=1u<<2;
      HX711_handler();
   }

 }

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void CTIMER3_IRQHandler(void)
{

	if(CTIMER3->IR & 0x08)     // MR3 interrupt
	{
		CTIMER3->IR|=1u<<3;

/*****************100usec count***************************************************/

		_100_us_fun();

		if(_100usec_count)
		{
			_100usec_count--;        	//100 micro
		}

		else
		{

			_100usec_count=9;           //1 mili

/*****************1_msec count******************************************************/
			_1_ms_fun();



/************************************************************************************/
			if(_1msec_count)
			{
				_1msec_count--;
			}
			else
			{
				_1msec_count=9;        //10 mili

/*****************10_msec count******************************************************/
				_10_ms_fun();




/*************************************************************************************/

			if(_10msec_count)
			{
			_10msec_count--;
			}

			else
			{
			_10msec_count=9;   //100 mili

/*****************100_msec count*******************************************************/
			_100_ms_fun();



/**************************************************************************************/

				if(_100msec_count)
				{
				_100msec_count--;
				}
				else
				{
				_100msec_count=9;  //1sec
/*****************1_sec count**********************************************************/
				_1_sec_fun();



/**************************************************************************************/

				if(_1sec_count)
				{
				_1sec_count--;


				}
//	}
				else
				{
				_1sec_count=1;
			//	count++;
				}
				}
			}
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

void _100_us_fun()
{



	if(soundduration)
	{
		if(!soundcount)
		{
			if(soundflag)
			{

			//	sound_level();
				BUZZER_PIN = 0X003;
				pwm_sta(alarm_sound.period,sound_level[G_sound_level]);
				soundcount = soundontime;
				soundflag = 0;

			}
			else
			{

				pwm_sta(alarm_sound.period,0);
				BUZZER_PIN = 0X00;
				soundcount = soundofftime;
				soundflag = 1;
			    soundduration--;

			}
		}
	}

	if(bright_count<15)
	{
		bright_count++;
		if(bright_count==bright_ctrl[G_bright_level])
		{
			GPIO->CLR[1]|=1<<4;//300-micro_on
		}
	}

	else
	{
		bright_count=0;
		GPIO->SET[1]|=1<<4;	   //600-micro_off
	}

	if(micro_time_delay)   //REW_UP
	{
		micro_time_delay--;
	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void _1_ms_fun()
{

	keypad_function();

	if(alarm_sound.sound_cnt)
	{
		alarm_sound.sound_cnt--;
	}

	if(RAMP.timer_interval)
	{
		RAMP.timer_interval--;
	}

	 if(milli_time_delay)
	{
		milli_time_delay--;
	}

	if((normal_run==1)&&(!RAMP.up_flag))
	{
		MFB.cuts_time_diff_cnt++;
	}

	if(G_start_cnt)
	{
		G_start_cnt--;
	}

	if(alarm_sound.sound_cnt)
	{
		alarm_sound.sound_cnt--;
	}



	if(G_Disc_sw_time)
	{
		G_Disc_sw_time--;
	}
	if(G_RL_sw_time)
	{
		G_RL_sw_time--;
	}

	if(cuts_sec)
	{
		cuts_sec--;
	}

	if(alarm_sound.count)
	{
		alarm_sound.count--;
	}

	if(pulse_clear_flag)
	{
			if(pulse_clear_count)
			{
				pulse_clear_count--;
			}
			else
			{
				GPIO->CLR[1]|=1<<26;
				pulse_clear_flag=0;
			}
	}

	if(Power_Interval_Delay)
	{
		Power_Interval_Delay--;
	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void _10_ms_fun()
{

	if(G_SD_delay)
	{
		G_SD_delay--;
	}

	if(G_serial_key)
	{
		G_serial_key--;
	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void _100_ms_fun()
{

	if(G_Battery_err_ver)
	{
		G_Battery_err_ver--;
	}

	if(G_run_count)
	{
		G_run_count--;
	}

	if(count)
	{
		count--;
	}

	if(soundcount)
	{
		soundcount--;
	}

	if(	blink_drug_delay)
	{
		blink_drug_delay--;
	}

	if(G_strain_data_read_delay)
	{
		G_strain_data_read_delay--;
	}

	if(G_load_read_count)
	{
		G_load_read_count--;
	}



//	if(BATT_STAT)
//	{
//		BAT_CHECK.STAT_high++;
//	}
//
//	else
//	{
//		BAT_CHECK.STAT_low++;		               //pin read data=LOW;
//	}
//
//	if(BAT_CHECK.STAT_high>35)
//	{
//		batt_high_flag=0;
//		BAT_CHECK.STAT_high=0;
//		BAT_CHECK.STAT_low=0;
//	}
//
//	else if(BAT_CHECK.STAT_low>35)
//	{
//		batt_high_flag=1;
//		BAT_CHECK.STAT_high=0;
//		BAT_CHECK.STAT_low=0;
//	}



	if(sd_time_delay)
	{
	   sd_time_delay--;
	}

	if(Battery_stat_delay)//REW_UP
	{
	   Battery_stat_delay--;
	}
	if(Plunger_data_delay)
	{
	   Plunger_data_delay--;
	}
	if(power_key_delay)
	{
		power_key_delay--;
	}
	if(rtc_power_read)
	{
		rtc_power_read--;
	}
	if(Switch_power_read)
	{
		Switch_power_read--;
	}
	if(Press_Back_Read)
	{
		Press_Back_Read--;
	}
	if(Bar_power_Read)
	{
		Bar_power_Read--;
	}
	if(Pressure_ADC_delay)
	{
		Pressure_ADC_delay--;
	}

	if(Bolus_reset_flag)
	{
		Bolus_reset_flag--;
	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void _1_sec_fun()
{

	if(common_warning_cnt)
	{
		common_warning_cnt--;
	}

	if(near_to_end_cnt)
	{
		near_to_end_cnt--;
	}

	if(sec_blink)
	{
		sec_blink--;
	}

	if(G_Battery_Set_pin)
	{
		G_Battery_Set_pin--;
	}

//	if(i2c_time_F8==1)
//	{
//		i2c_time_++;
//		if(i2c_time_>=20)
//		{
//			i2c_time_F8=0;
//			i2c_time_=0;
//			i2c0_busy=0;
//		}
//	}

	if(G_Bt_Low_timer)
	{
		G_Bt_Low_timer--;
	}

   if((siphonic_time) && (sy_size))
   {
	   siphonic_time--;
   }

	if(secs_time_delay)
	{
		secs_time_delay--;
	}

	if(G_warn_count)
	{
		G_warn_count--;
	}

//	if(G_zero_psi_cnt)
//	{
//		G_zero_psi_cnt--;
//	}

    if(normal_run)
    {
    	INFUSED.sec++;
    }
	
    if(G_strain_sec_count)
	{
		G_strain_sec_count--;
	}

	if(waitingtime_1)
	{
	  waitingtime_1--;              //long press
	}

//	if(timer_checker)
//	{
//	  timer_checker--;
//	}

	if(ADC_delay)
	{
	  ADC_delay--;
	}

	if(ON_Flag==1)
	{
	  UTILIZED.device_sec_cnt++;
	}

	if(ON_Flag)//testing purpose
	{
	  UTILIZED.battery_sec_cnt++;
	}

	if(normal_run==1)
	{
	  UTILIZED.running_sec_cnt++;
	}
	
   if(attempt_count)
   {
     attempt_count--;
   }
		  
   if(sec_count)
   {
	 sec_count--;
   }

//	if(timer_checker)
//		{
//		timer_checker--;
//		}


	if(key_pressed)
	{
		key_pressed--;
	}

	if(auto_lock)
	{
		auto_lock--;
	}

	if(auto_lock_time)
	{
		auto_lock_time--;
	}


	if(Bolus_reset_flag)
	{
		Bolus_reset_flag--;
	}

	if( (press_run_alarm) && (!normal_run) )
	{
		press_run_alarm--;
	}

	if(purge_device_in)
	{
		purge_device_in--;
	}
	if(device_check_cnt)
	{
		device_check_cnt--;
	}
	if(Pump_idle)
	{
		Pump_idle--;
	}

	if(_1sec_delay)
	{
		 _1sec_delay--;
	}
	if(mute_count)
	{
		mute_count--;
	}
//	if(Battery_run)
//	{
//		Battery_run--;
//	}


}

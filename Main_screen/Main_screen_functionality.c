#include <Alarm.h>
#include <Bolus_Header.h>
#include <Color.h>
#include <Dosage_mode.h>
#include <Driver_Timer.h>
//#include <Dynamic_Pressure.h>
//#include <Events_log.h>
#include <Flowrate_Screen.h>
#include <FR_CALC.h>
#include <infused_calculate.h>
#include <Keypad.h>
#include <Linear_Header.h>
#include <Linear_pot.h>
//#include <Main_Menu.h>
#include <Main_screen.h>
#include <Motor.h>
#include <Occlusion.h>
#include <Power_off.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <Shapes.h>
//#include <STEPPER.h>
//#include <Target_fun.h>
#include <TFT_Commands.h>
#include <TFT_String.h>
#include "Driver_ADC.h"
#include "Power_off.h"
#include <Boot_up.h>
#include "Battery.h"
#include "factory.h"
#include "Driver_I2C.h"

//extern uint32_t  G_minval[7];//old pot adc value
uint16_t auto_lock=0;
uint8_t keylock=0;
uint16_t key_longpress;
uint8_t key_pressed=30;
uint8_t g_size_vol;
uint8_t w_flag=0;
uint8_t  longpress=0;
//uint16_t event1_no;			//25-03
uint8_t quick_run=0;
uint8_t G_mode_exit_flag;
uint8_t  mode_longpress=0;
uint8_t motor_on_flag=0;
uint16_t temp_ADC_values=0;
uint32_t FR_1=0;
uint8_t Bolus_status_flag=0;
uint8_t Bolus_reset_flag=0;
uint8_t press_run_flag=0;
uint8_t pre_flowrate=10;
uint16_t Pump_idle_flag=0;
uint8_t press_clear_flag=0;
uint8_t G_Bolus_target_flag=0;
uint8_t G_Bolus_warning_flag=0;
uint8_t G_Battery_Set_pin=0;
uint32_t check=0;
uint32_t dummy_variable=285164096;
uint8_t G_Long_press_back=0;
uint8_t G_main_screen_flag=0;
uint8_t low_battery_flag=0;
uint8_t low_battery_erase_flag=0;
uint8_t alarm_flag;
uint8_t G_Brand_back_flag=0;
uint8_t G_Complete_reset=0;
uint8_t common_warning_cnt=0;
uint8_t warn_clear_flag=0;
uint16_t temp_ADC_values_2=0;
uint16_t temp_ADC_values_3=0;
uint16_t general_count=0;

extern uint8_t G_switching_flag;
extern uint8_t B_count;
extern uint8_t war_disp;
extern uint8_t warning_flag[3];

extern char local_buffer[10];
extern uint16_t Sample_value;
extern uint8_t run;
extern uint8_t batt_high_flag;
extern uint16_t Pump_idle;
extern uint8_t G_add;

extern uint8_t G_infusion_modes;
extern uint16_t total_events;   //29-03
extern uint16_t event_id;		//25-03
extern uint8_t ssize;
extern uint8_t G_correct_move;
extern uint8_t G_wrong_move;
extern uint16_t G_Remaining_volume;
extern uint8_t siphonic_time;
extern uint8_t G_syringe_size_flag;
extern uint8_t siphonic_time;
extern uint8_t G_Pressure_siphonic;
extern uint8_t G_power_edit;
extern uint16_t strain_data;

void auto_keylock(uint8_t auto_level);
void syringe_disp_status(uint8_t screen);
void Disc_failure_condition(void);
void Calibration_error_condition(void);
void MFB_Reset_data(void);

extern uint8_t G_lock_time;
extern uint8_t brand_select_no;
extern uint8_t syr_brand;
volatile uint8_t normal_run;
extern uint8_t brand_width_disp;

extern uint16_t linear_temp_adc;
extern uint16_t temp_ADC_values_1;
extern uint16_t temp_ADC_values_1;

extern  char *brand_list[17];
extern void Running_symbol(uint8_t X_start, uint8_t Y_start,uint32_t col);
extern uint8_t TFT_ST7789V_Left_Arrow_22pt(uint16_t xpos, uint16_t ypos,  uint8_t arrow, uint32_t boarder_color, uint32_t fill_color);
extern void infused_data(uint8_t screen,uint8_t r_mode);
extern void plunger_based_o_ml_max_ml_calculate();
extern float syringe_nearempty_calculation(uint16_t flowarte);
extern void plunger_alarm_check();

extern uint16_t m_count;
extern uint32_t MR_VALUE;
extern uint8_t Target_mode_setting(void);
uint8_t alarm_flag;
extern uint8_t ON_Flag;
extern void infuse_status(void);
extern void infuse_clr();
extern uint16_t auto_lock;
extern uint8_t G_infusion_mode_opt;
//extern uint32_t G_loaded_adc_val[9];
extern uint8_t siphonic_time;
extern uint8_t G_occl_unit;
extern uint16_t m_count1;
extern uint8_t prev_data_flag;  //ZOOZ_1
extern uint16_t m_count1_1;
extern uint8_t end_flag;
extern uint16_t Pump_idle;
uint8_t home_return_flag;

extern clk time;//ZOOZ_1
extern uint8_t G_warn_flag;//28-03
void  read_last_data(uint8_t mode);
extern uint8_t dose_rate_mode(void);
extern void beep_sound();
extern uint16_t G_con_value;
extern uint8_t sy_size;
extern uint16_t press_run_alarm;
extern uint8_t disc;
extern char disp_para[15];    //ZOOZ_1
extern uint8_t dose_option_no;
extern uint32_t G_pressure_value;
extern uint16_t array_date[50],array_month[50],array_year[50];
extern uint16_t array_hour[50],array_minute[50],array_event_no[50];
extern clk sec_to_time_format(uint32_t sec);
extern uint8_t TFT_ST7789V_keylock4_symbol_16pt(uint16_t xpos, uint16_t ypos,
       uint8_t arrow, uint32_t boarder_color, uint32_t fill_color);

extern Occlusion Occl;
extern uint8_t sy_size;
extern uint8_t release;
extern uint8_t G_mode_switch_flag;
extern uint8_t G_mode_sw_flag;
extern uint8_t near_to_target_flag;
extern uint8_t cuts_sec;
extern uint16_t maxi_lmt[7];
extern uint16_t first_lmt[7];
extern uint8_t Battery_run;
volatile uint8_t waitingtime_1;

uint16_t example_var=0;
uint16_t PSI_temp_value=0;
uint8_t home_flag=0;
uint8_t PSI_Value=0;
uint16_t p_xpos=0;
extern char p_local_buffer[10];

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t Home_screen_functionality(uint8_t mode)
{

	uint16_t PSI_temp_value=0;
	uint8_t home_exit_flag=1;
	uint8_t exit_flag=0;
	uint8_t loop_count=0;
	uint8_t M_nav_flag=1;//common_bug_33
	uint8_t confirm_value=0;
	uint8_t compound_value=0;
	uint16_t battery_checker=0;
	uint16_t Battery_data=0;
	uint16_t xpos=0;
	uint16_t PSI_Value=0;


	POW.power_status_flag=0;

	RAMP.on_off=1;
	POW.power_status_flag=0;	//26-03
	G_power_edit=0;
	FACT.factory[0]=199;

//	if(!mode)
//	{
//		MOT.flowrate=1;
//	}
//	else
//	{
//		MOT.flowrate=0;
//	}
//
//	if(!G_mode_switch_flag)
//	{
//		if(prev_data_flag)
//		{
//			read_last_data(mode);
//			M_nav_flag=1;
//		}
//	}



//	if((!prev_data_flag)||(G_mode_switch_flag))
//	{
//
//		if(mode==0)
//		{
			Rectangle(0,0,320,240,GREEN);
			ON_Flag=1;
			M_nav_flag = Flow_rate_screen(&MOT.flowrate,0,12000,2); //common_bug_33

		//	Rectangle(0,0,320,240,YELLOW);

//		}

//		else if(mode==1)
//		{
//
//			M_nav_flag = Target_mode_setting();						//common_bug_33
//		}
//
//		else if(mode==2)
//		{
//			M_nav_flag =dose_rate_mode();							//common_bug_33
//		}
//
//		if(M_nav_flag)
//		{
//			G_mode_switch_flag =0;
//		}
//
//		if(G_mode_switch_flag)
//		{
//			M_nav_flag = 0;
//			G_mode_switch_flag =0;
//			exit_flag=2;
//		}
//
//		if(G_mode_sw_flag)
//		{
//			exit_flag=2;
//		}
//
//		if((!M_nav_flag) && (!G_switching_flag))
//		{
//			if((G_infusion_mode_opt==3) &&  (!prev_data_flag))//common_bug_1
//			{
//			  G_infusion_modes=3;
//			}
//			exit_flag=2;
//		}
//
//	}
//
//	if((M_nav_flag) || (G_switching_flag))
//	{
//
//		prev_data_flag=0;
//		G_Complete_reset=mode;
//		POW.power_status_flag=1;//27-03
//		siphonic_time=30;
//		exit_flag=0;

/*****************DEFAULT SYR ADC VALUE******************/

	while(home_exit_flag)
	{

	   Power_off();

       if(!ON_Flag) 	//MAIN.main_power_status_flag == 1 )
       {
    	  break;//23-03
       }

       else if(POW.power_status_flag)
	   {

    	   home_flag=1;
   		   G_infusion_modes =mode;
   		   G_power_edit=0;
    	   G_Pressure_siphonic=0;
		   home_return_flag=1;
		   near_to_target_flag=0;
		   G_syringe_size_flag=0;
		   POW.power_status_flag=0;//26-03
		   main_screen_frame(MOT.flowrate,G_infusion_modes);
		   dynamic_pressure(0,1);
		   syringe_disp_status(1);
		   PSI_temp_value=0;
		   SUPPLY_TRIGGER_ON;
		   while(KEY.value);
	   }

       else if(POW.mains_bat_swt_flag)
	   {

			POW.mains_bat_swt_flag=0;

				if(!BATT.mode)
				{
					Battery_symbol();
					plug_symbol(ORANGE);//PLUG_COL
					Notification(MAINS_PLUGIN);
				}

				else
				{
					Battery_symbol();
					plug_symbol(MAIN_FRAME_COL);
					Notification(MAINS_PLUGOUT);
			//		GPIO->SET[1]|=1<<15;
				}

	     }

//

   if(!G_Battery_Set_pin)
   {
    	G_Battery_Set_pin=6;
   }
   else
   {
	   if(G_Battery_Set_pin==1)
	   {
	//	   GPIO->SET[1]|=1<<15;
	   }
   }

      if(GPIO->PIN[1] & (1<<27))
      {
    	   compound_value=1;
      }

	  else
	  {
		  compound_value=0;
	  }

      if(LIN_POT.syr_end_flag)
      {
    	  warning_flag[0]=0;
    	  warning_flag[1]=0;
    	  warning_flag[2]=0;
      }



		syringe_position_check();  //REW_UP
		syringe_disp_status(0);
		plunger_alarm_check();
		Motor_struck_alarm();      //REW_UP

  if(normal_run)
  {

		if(!common_warning_cnt)
		{
			Common_Warning();
		}

  }

	if((!BOL.run_mode) && (!Bolus_status_flag))  //28-03
	{
	   infused_data(0,mode);                   //Display the Infused data in the Main screen
	}

	if(!KEY.value)
	{
	   longpress=0;
	}

		 auto_keylock(G_lock_time);
		 ADC_to_PSI_conversion();  //REW_UP

		if(((!normal_run) && (BOL.mode)) && (BOL.run_mode)  )
		{
			Occlusion_Status();
			infuse_status();
		}

		if((normal_run))//|| (BOL.mode))
		{

			if( (disc) && (normal_run))
			{
			  Alarm(NOT_ENGAGE);
			}



			if((!BOL.run_mode) && (!Bolus_status_flag))
			{
				Running_symbol(8,15,MAIN_FRAME_COL);
			}

			if(BOL.mode<=1)
			{
				Occlusion_Status();
				infuse_status();
			}

		}

	    else
		{
	    	if((!BOL.run_mode) && (!Bolus_status_flag))
			{
				TFT_ST7789V_Left_Arrow_22pt(RUNSYMBOL_POS,18+5,0,MAIN_FRAME_COL,ORANGE);
				Rectangle(18+22+2,RUNSYMBOL_POS,5,21,ORANGE);
				Rectangle(18+32+2,RUNSYMBOL_POS,5,21,ORANGE);
			}



//	    	 	 if(Pump_idle_flag)
//	    		 {
//	    			Pump_idle=15;
//	    		    Pump_idle_flag=0;
//	    		    delay_secs(2);
//				    Warning_Scr_Erase();
//
//	    		 }
//
//				 if((!Pump_idle) && (!BOL.run_mode))
//				 {
//				//	 Notification(PUMP_IDLE);
//					 Warning_screen((uint8_t*)"   Pump Idle",0);
//					 WARN_SOUND(3,1,3);
//					 Pump_idle_flag=1;
//				 }

				 if(((sy_size!=0) && (!disc)) && (MOT.flowrate>0))
	    		 {
					 	 	if(!press_run_flag)
	    			 		{
	    			 			press_run_alarm=180;
	    			 			press_run_flag=1;
	    			 			press_clear_flag=0;
	    			 		}

	    			 		if((!press_run_alarm) && (!BOL.run_mode))
	    			 		{
	    			 		//  Alarm(PRESS_RUN);
	    			 			Warning_screen((uint8_t*)"Press Start to Run",0);
	    			 			WARN_SOUND(3,1,3);
	    			 			delay_secs(3);
	   						    Warning_Scr_Erase();
	   						    press_run_flag=0;
	    			 		}
	    		 }

	    		 else
	    		 {
			 		 press_run_alarm=180;
			 		 if(!press_clear_flag)
					 {
						 Warning_Scr_Erase();
						 press_clear_flag=1;
					 }
	    		 }



	    }

//			 Font_Select(ARIAL_14);
//			 TFT_Number(60,90,mode,YELLOW,RED);
//			 TFT_Number(60,110,G_infusion_modes,YELLOW,RED);

		 if(mode==1)
		 {
			 near_to_target();
			//warn_tone(5);
		 }
//		 else
//		 {
//			 warning_flag[1]=0;
//		 }

		 	 pressure_display(BOL.run_mode,Bolus_status_flag);


	 	 	 	 	if(RAMP.up_flag)
					{
						RAMP_UP(_MILLISEC,RAMP_RPM,RAMP.RPM_control);
					}

					else if(RAMP.down_flag)
					{
						RAMP_DOWN(_MILLISEC,RAMP_RPM);
					}

	 	 	 	 	home_exit_flag=Key_functionality(mode);

					if(!home_exit_flag)
					{
					  exit_flag=3;
					}
	}
	return exit_flag;

}
//}

/****************************************************************************
 *
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t key_main_screen()
{
	uint8_t exit_flag = 1;
	uint8_t fr_flag=0;
    uint8_t loop_count=0;

switch(KEY.value)
{
		case OK_KEY :

		   beep_sound();
		   home_flag=0;
		   press_run_alarm=180;
		   Pump_idle=10;

			if(!keylock)
			{
				key_pressed=30;
				Flow_rate_screen(&MOT.flowrate,0,24000,2);
				G_wrong_move=0;
				if(MOT.flowrate)
				{
					if(normal_run)
					{
						MR_Value_calculate(MOT.flowrate);
						MFB_Reset_data();
					}
				}

				else
				{
					normal_run=0;
					Timer_disable();
				}
				POW.power_status_flag=1;//26-03
			}

			else
			{
				Notification(KEY_LOCK);
			}

		while(KEY.value);
		break;


			case START_STOP_KEY:

			beep_sound();

			Bolus_reset_flag=0;

		    if(!Bolus_reset_flag)
			{
				if ((!keylock)||(normal_run))
				{
					key_pressed=30;
					if(!LIN_POT.syr_end_flag)
					{
						if((normal_run==0) && (!Bolus_status_flag))
						{
							if((MOT.flowrate!=0) && (ssize!=0))
							{
								normal_run=1;
								press_run_alarm=180;
								Pump_idle=60;
								Warning_Scr_Erase();
								plunger_based_o_ml_max_ml_calculate();
								syringe_nearempty_calculation(MOT.flowrate);
								event_no_update(2);
								BOL.run_mode=0;
								G_wrong_move=0;
								RAMP.RPM_control=0;    //ZOOZ_1
								RAMP.inc_dec=0;
								DRV8428_ENABLE();
								stepper_Forward();
								Font_Select(ARIAL_14);
								MR_Value_calculate(MOT.flowrate);
								MFB_Reset_data();
								if(disc)           //REW_UP(start/stop case)
								{
								  Alarm(NOT_ENGAGE);
								}
							}

							else
							{
								if((MOT.flowrate==0) && (ssize==0))
								{

									WARN_SOUND(2,1,2);
									Notification(SET_FLOWRATE);
									fr_flag=1;
								}

								if( (MOT.flowrate==0) && (fr_flag!=1) )
								{
									Notification(SET_FLOWRATE);
								}

								else if(ssize==0)
								{
									Warning_screen((uint8_t*)"Load Syringe",0);
									WARN_SOUND(3,1,3);
									delay_secs(3);
									Warning_Scr_Erase();
								}

							}

						 }

					else
					{
						if(!Bolus_reset_flag)
						{
							sec_to_time_format(INFUSED.sec );
							BOL.run_mode=0;
					//		event_no_update(4);
							siphonic_time=30;
							normal_run=0;
							RAMP.down_flag=0;
							press_run_alarm=180;
							Pump_idle=10;

							if( (RAMP.RPM_control > 50.0) && (RAMP.on_off == 1) ) // RPM ramp on off flag
							{
							   RAMP.down_flag=1;
						//	   RAMP.dec=RAMP.RPM_control/_RPM;  /*CHECK*/
							}

							else
							{
							//	DRV8428_DISABLE();
								Timer_disable();
							}
							RAMP.up_flag=0;
						//	RAMP.inc=0;  /*CHECK*/
						}

							if(!Bolus_reset_flag)
							{
								Rectangle(10,10,60,30,MAIN_FRAME_COL);
							}
							Warning_Scr_Erase();

				 }
			
				}
					else
					{
						//WARN_SOUND(3,1,3);
					}
				}

				else
				{
					Notification(KEY_LOCK);
				}
	}
			while(KEY.value);
		    break;

}
return exit_flag;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t key_main_screen_VTBI()
{
	uint8_t exit_flag=1;
	uint32_t Max_limit=0;



	switch(KEY.value)
	{

		case OK_KEY :

		home_flag=0;
		beep_sound();
		if(!keylock)
		{
			key_pressed=30;
			MFB_Reset_data();
			G_wrong_move=0;
			if(!normal_run)         //12-06-2024
			{
			  Target_mode_setting();
			  POW.power_status_flag=1;	//26-03
			}
		}

		else
		{
			Notification(KEY_LOCK);     //12-06-2024
		}

		while(KEY.value);
		break;

		case START_STOP_KEY:
		beep_sound();
		if((!keylock)||(normal_run))//29-03
		{
			key_pressed=30;
			if(INFUSED.ml==MOT.volume)
			{
				Warning_screen((uint8_t *)"Target reached",0);
				WARN_SOUND(3,1,3);
			}

			else
			{
				if(normal_run==0)
				{
					if(MOT.flowrate!=0)
					{
						 if(ssize!=0)
							{
								DRV8428_ENABLE();
								stepper_Forward();
								RAMP.inc_dec=0;
							//	event_no_update(3);
								MR_Value_calculate(MOT.flowrate);
							    normal_run=1;
								MFB_Reset_data();
								G_wrong_move=0;
								plunger_based_o_ml_max_ml_calculate();
								syringe_nearempty_calculation(MOT.flowrate);
								if(disc)           //REW_UP(start/stop case)
								{
					      		  Alarm(NOT_ENGAGE);
								}
							}
						 	 else
						 	 {
								Warning_screen((uint8_t*)"Load Syringe",0);
								WARN_SOUND(3,1,3);
								delay_secs(3);
								Warning_Scr_Erase();
						 	 }

					}

				else
				{

					WARN_SOUND(2,1,2);
					Notification(SET_FLOWRATE);

				}
				}

				else
				{
					normal_run=0;
					Timer_disable();
					RAMP.up_flag=0;
				}

				Rectangle(10,10,60,30,MAIN_FRAME_COL);
			}
		}

		else
		{
			Notification(KEY_LOCK);
		}
		while(KEY.value);
		break;



	}
return exit_flag;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t key_fun_doserate_mode(void)
{
	uint8_t check_flag=0;
	uint8_t exit_flag=1;




	switch(KEY.value)
	{

		case OK_KEY :
		beep_sound();
		if(!keylock)
		{
			key_pressed=30;
			MFB.twenty_cuts_count=0;
			MFB.cuts_time_diff=0;
			MFB.cuts_time_diff_cnt=0;
			G_wrong_move=0;

			if(!normal_run)
			{
				overview_screen();
			}
			else
			{
				home_flag=0;
				check_flag=Double_Decimal_FR_screen(&dose.drug_dos,100000,5);
				if(check_flag)
				{
					MOT.flowrate=dose.flow_rate/10;
					//MR_Value_calculate(MOT.flowrate);
				}

				else
				{
					overview_screen();
				}

				if(MOT.flowrate)
				{
//					Font_Select(ARIAL_12);
//				    TFT_Number(80,70,dose.flow_rate,YELLOW,RED);

					if(normal_run)
					{
						MR_Value_calculate(MOT.flowrate);//dose.flow_rate);
					}
				}

				else
				{
					normal_run=0;
					Timer_disable();
				}
			}

			POW.power_status_flag=1;//26-03

		}

		else
		{
		//	Notification(KEY_LOCK);
		}
		while(KEY.value);
		break;

		case START_STOP_KEY:

		beep_sound();

		if(!keylock)
		{
			key_pressed=30;

			if(!normal_run)
			{
				if(MOT.flowrate)
				{
					if(ssize!=0)
					{
						normal_run=1;
						press_run_alarm=180;
						Pump_idle=10;
						DRV8428_ENABLE();
						stepper_Forward();
		//				event_no_update(3);
						MOT.flowrate=dose.flow_rate/10;
						MR_Value_calculate(MOT.flowrate);
						plunger_based_o_ml_max_ml_calculate();
						syringe_nearempty_calculation(MOT.flowrate);
						MFB_Reset_data();
						G_wrong_move=0;

						if(disc)
				        {
						  Alarm(NOT_ENGAGE);
						}

					}

					else
					{
						Warning_screen((uint8_t*)"Load Syringe",0);
						WARN_SOUND(3,1,3);
				//		delay_secs(3);
						Warning_Scr_Erase();
					}
				}

				else
				{
					WARN_SOUND(2,1,2);
				}
			}

			else
			{
				 normal_run=0;
				 Timer_disable();
				 //event_no_update(4);
				 RAMP.down_flag=0;
			}
			Rectangle(10,10,60,30,MAIN_FRAME_COL);
		}

		else
		{
			Notification(KEY_LOCK);
		}
		while(KEY.value);
		break;


	}
	return exit_flag;
}

//void auto_keylock(uint16_t lock_time)
//{
//
//	if(key_pressed==0)
//	{
//		auto_lock++;
//
//		if(auto_lock==lock_time)
//		{
//			auto_lock=0;
//
//			keylock=1;
//			Notification(KEY_LOCK);
//		}
//
//	}
//
//}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void auto_keylock(uint8_t auto_level)
{
	static uint8_t lock_check=0;
	uint16_t lock_time[4]={0,60,300,600};

	if( !keylock &&   lock_time[auto_level] )
	{
		if(!auto_lock )
		{
			if(!lock_check)
			{
				lock_check=1;
				auto_lock=lock_time[auto_level];
			}
			else
			{
				lock_check=0;
				auto_lock=0;
				keylock=1;
				Notification(KEY_LOCK);
			}

		}
		else if(KEY.value)
		{
			auto_lock=lock_time[auto_level];
		}
	}
	else if(auto_lock || lock_check)
	{
		auto_lock=0;
		lock_check=0;
	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Disc_failure_condition(void)
{
	uint16_t strain_adc=0;
	uint8_t value=3;
	while(value)
	{
		strain_adc=Pressure_ADC();
		value--;
	}

//	Font_Select(ARIAL_14);
//    TFT_Number(0,70,strain_adc,YELLOW,RED);

//		if(!normal_run) //REW_UP
//		{
//			if(( (strain_adc<=Occl.Zero_PSI) && (sy_size)) && ((!disc) ||(release) ))
//			{
//				Alarm(DISC_ERR);
//			}
//		}

//		if(normal_run)
//		{
//			if(( (strain_adc>Occl.Zero_PSI) || (sy_size)) && ((!disc) ||(!release) ))
//			{
//				Alarm(DISC_ERR);
//			}
//		}


}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Calibration_error_condition(void)//REW_UP
{

	if(ON_Flag)
	{
		if(Occl.Zero_PSI>0)
		{
			if((!sy_size) && (strain_data!=Occl.Zero_PSI))
			{
				if((strain_data <= (Occl.Zero_PSI + TEMPERATURE_BASED_DRIFT_RANGE)) &&
					(strain_data >= (Occl.Zero_PSI - TEMPERATURE_BASED_DRIFT_RANGE)) )
				{
					Occl.Zero_PSI=2000;
					EEPROM_datawrite(EEPROM_Occl_strain_0PSI_value,Occl.Zero_PSI,2);
				}
				else
				{
					Alarm(CALIBRATION_ERR);
				}
			}
		}
	}
//	if(((Occl.Zero_PSI>1990))||(Occl.Zero_PSI<1990))
//	{
//		Alarm(CALIBRATION_ERR);
//
//	}
}

void pressure_display(uint8_t bol_run,uint8_t bol_reset_flg)
{
	uint8_t presure_ratio[5]={51.7,1,6.8,6.8};
//  uint8_t PSI_Value=0;

	if((bol_run!=1) && (!bol_reset_flg))    //REW1F change to function
	{
		 if((PSI_temp_value!=(Occl.PSI_VALUE*presure_ratio[G_occl_unit])))
		 {
			    Font_Select(ARIAL_9);
			    p_xpos=Letters_Alignments(0,75,(uint8_t*)local_buffer,0);
//			    Font_Select(ARIAL_14);
//			    TFT_Number(0,70,(uint8_t*)local_buffer,YELLOW,RED);
				TFT_String(p_xpos,DYN_VAL_POS,(uint8_t*)local_buffer,MAIN_FRAME_COL,MAIN_FRAME_COL);//Hang
			//	TFT_String_align(0,75,DYN_VAL_POS,(uint8_t *)local_buffer,0,MAIN_FRAME_COL,MAIN_FRAME_COL);
				memset(local_buffer,0,6);	//Hang

				if(G_occl_unit!=1)
				{
					sprintf((char *)local_buffer,"%02d",(int)(Occl.PSI_VALUE*presure_ratio[G_occl_unit])/10);
				}

				else
				{
					sprintf((char *)local_buffer,"%.1f",(float)(Occl.PSI_VALUE*presure_ratio[G_occl_unit])/10.0);
				}

				p_xpos=Letters_Alignments(0,75, (uint8_t*)local_buffer,0);
				TFT_String(p_xpos,DYN_VAL_POS,(uint8_t*)local_buffer,MAIN_FRAME_COL,YELLOW);
			//	Font_Select(ARIAL_9);
			//	TFT_String_align(0,75,DYN_VAL_POS,(uint8_t*)local_buffer,0,MAIN_FRAME_COL,YELLOW);
				PSI_Value=Occl.PSI_VALUE*Occl.dynamic_ratio/10;
				dynamic_pressure(PSI_Value,0);
				PSI_temp_value=Occl.PSI_VALUE*presure_ratio[G_occl_unit];
		 }
	 }

}

uint8_t Key_functionality(uint8_t mode)
{
	uint8_t exit_flag = 1;

//		TFT_Number(150,40,disc,BLACK,RED);
//		TFT_Number(150,90,release,BLACK,RED);

		if(BOL.run_mode)
		{
			if(release)
			{
				Alarm(PLUNGER);
			}
			else if(disc)
			{
				Alarm(NOT_ENGAGE);
			}
		}

	     if((BOL.mode) && (BOL.infused_ml==pre_flowrate))
	     {
	    	 Power_off_beep_sound();
	    	 pre_flowrate+=10;
	     }

		if((BOL.run_mode) && (BOL.infused_ml > first_lmt[sy_size]))
		{
			bolus_mode_stop();
			Bolus_status_flag=1;
			Bolus_reset_flag=1;
		}

		if(BOL.run_mode)
		{
		//	Running_symbol(56,3,MAIN_FRAME_COL);
			bolus_fr_screen(BOL.infused_ml);

			if((BOL.mode == 1) && (KEY.value==PURGE_START_STOP_KEY))
			{
				bolus_mode_stop();
				Bolus_status_flag=1;
				Bolus_reset_flag=0;
			}

//		   if((MOT.flowrate>BOL.flowrate) && (!G_Bolus_warning_flag) )
//		   {
//				Frame_Footer_warning(WARNING_COLOR,BLACK,(uint8_t*)"Less Bolus FR",(uint8_t*)"",0);
//				G_Bolus_warning_flag=1;
//		   }

			if(!KEY.value)
			{
				bolus_mode_stop();
				Bolus_status_flag=1;
				Bolus_reset_flag=15;
			}
		}

		if(Bolus_status_flag)
		{
			if(!Bolus_reset_flag)
			{
			//  bolus_mode_stop();
				MFB_Reset_data();
			//	waitingtime_1=2;
			//  CLRSCR(MAIN_FRAME_COL);
				press_run_alarm=180;
				Pump_idle=10;
				POW.power_status_flag=1;
				Bolus_status_flag=0;
			}
		}

		if(!KEY.value)
		{
			longpress=0;
			key_longpress=0;
			mode_longpress=0;        //21-03-2024
		}
		exit_flag = 1;
	switch(KEY.value)
	{

		case UP_KEY:

		if(!keylock)
		{
			key_pressed=30;
		}
		else
		{
			Notification(KEY_LOCK);

		}

		while(KEY.value);
		break;

		case DOWN_KEY:

		if(!keylock)
		{
			key_pressed=30;
		}
		else
		{
			Notification(KEY_LOCK);

		}

		while(KEY.value);
		break;

		case LEFT_KEY:

		if(!keylock)
	    {
			key_pressed=30;
		}
		else
		{
			Notification(KEY_LOCK);

		}
		while(KEY.value);
	    break;

		case RIGHT_KEY:

		if(!keylock)
		{
			key_pressed=30;
		}
		else
		{
			Notification(KEY_LOCK);

		}

		while(KEY.value);
	    break;


		case MENU_KEY:
		beep_sound();
//		if(normal_run==0)
//		{
		//home_flag=0;
			if(!keylock)
			{
				key_pressed=30;
				G_Brand_back_flag=0;
//				Font_Select(ARIAL_14);
//				TFT_Number(0,70,normal_run,YELLOW,RED);
				if((!normal_run) && (!RAMP.down_flag))
				{
					Main_Menu_Screen();
					POW.power_status_flag=1;//26-03
				}
			}

			else
			{
				Notification(KEY_LOCK);
			}

		//}

		while(KEY.value);
		break;

		case BOLUS_KEY:
			if(MOT.flowrate<BOL.flowrate) //&& (!G_Bolus_warning_flag) )
			{
				if(!keylock)
				{
					home_flag=0;

					key_pressed=30;
					if(LIN_POT.syr_end_flag==1 )
					{
						LIN_POT.nr_empty_alarm_flag = 0;
						Warning_Scr_Erase();
						Alarm(SYR_END);
					}
					else if(!BOL.run_mode)
					{
						if(BOL.mode == 0)
						{
							beep_sound();
							G_Bolus_warning_flag=0;
							MFB_Reset_data();
							bolus_fun();  						//auto bolus
						    CLRSCR(MAIN_FRAME_COL);
							POW.power_status_flag=1;
						}

						else if(BOL.mode == 1)
						{
							if(longpress==0)
							{
								longpress=1;
								waitingtime_1=2;
							}

							if((!waitingtime_1) )
							{
								beep_sound();
								G_Bolus_warning_flag=0;

								purge_bolus();
								Bolus_status_flag=0;
								longpress=0;
							}
						}
					}
		      }

		      else
		      {
		    	  Notification(KEY_LOCK);
		      }
			}

		   else
		   {

			   Warning_screen((uint8_t *)"Less Bolus FR",0);
			   WARN_SOUND(2,1,2);
			   delay_secs(2);
			   Warning_Scr_Erase();
			   war_disp=0;
		   }
			break;

		case BACK_KEY:
			//  home_flag=0;
		//	GPIO->SET[1]|=1<<15;

				if(!keylock)
				{
					key_pressed=30;
					if((G_infusion_mode_opt==3) && (!normal_run))
					{
						if(mode_longpress==0)
						{
							waitingtime_1=2;
							mode_longpress=1;
						while(KEY.value==BACK_KEY && mode_longpress)
						{
							if(!waitingtime_1)
							{
								beep_sound();
								G_infusion_modes=3;// To Clear the current mode
								G_Long_press_back=1;
								G_Brand_back_flag=1;
								exit_flag = 0;
								break;             //21-03-2024
							}
						}
					   }
				  }

				}

				else
				{
					Notification(KEY_LOCK);
				}

		//		while(KEY.value);
				break;

		case MUTE_KEY:
					beep_sound();
				//	GPIO->CLR[1]|=1<<15;

					if(keylock==1)
					{
						home_flag=0;//12-04-2024
					//	Notification(KEY_LOCK);
						Notification(KEY_LOCK);
					//	TFT_ST7789V_keylock4_symbol_16pt(110,100,0,WARNING_COLOR, BLACK);
					}

					key_longpress=0;

					if(mode_longpress==0)
					{
						waitingtime_1=1;
						mode_longpress=1;
						while(KEY.value==MUTE_KEY && mode_longpress)//21-03
						{
							if(!waitingtime_1)
							{
								if(keylock)
								{
									keylock=0;
									Notification(KEY_UNLOCK);
								}
								else
								{
									keylock=1;
									Notification(KEY_LOCK);
								}
								break;//21-03
							}
						}
					}

					if(waitingtime_1)
					{
					//	delay_secs(2);
					//	Warning_Scr_Erase();
					}
					while(KEY.value);
					break;

	}

		if(mode==0)
		{
			key_main_screen();	//21-03
		}
		else if(mode==1)
		{
			key_main_screen_VTBI();
		}
		else if(mode==2)
		{
			key_fun_doserate_mode();
		}

	return exit_flag;

 }

void MFB_Reset_data(void)
{
	MFB.Min_cuts=0;
	MFB.Motor_pulse=0;
	MFB.twenty_cuts_count=0;
	MFB.cuts_time_diff=0;
	MFB.cuts_time_diff_cnt=0;
}

void Common_Warning(void)
{
	static uint8_t count=0;
	char* warning_names[]={"Near to End","Near to Target","Battery Low"};

//	 Font_Select(ARIAL_14);
//	 TFT_Number(40,70,count,YELLOW,RED);

	if(warning_flag[count]==1)
	{
		if(!warn_clear_flag)
		{
			Warning_screen((uint8_t*)warning_names[count],0);
			WARN_SOUND(3,1,3);
			warn_clear_flag=1;
		}
		else
		{
			Warning_Scr_Erase();
			warn_clear_flag=0;
			count++;

		}
		common_warning_cnt=2;
	}

	else
	{
		common_warning_cnt=0;
		 count++;
	}

		  if(count>=3)
		  {
			  count=0;
		  }

}


//if(!common_warning_cnt)
//
//{
//
//	common_warning_cnt=2;
//	if((warning_flag[0]==1) && (!w_flag))
//	{
//		Warning_screen((uint8_t*)"Near to End",0);
//	    WARN_SOUND(3,1,3);
//	    w_flag=1;
//		delay_secs(2);
//		Warning_Scr_Erase();
//
//	}
//	else if((warning_flag[1]==1) && (w_flag==1))
//	{
//		Warning_screen((uint8_t*)"Near to Target",0);
//        WARN_SOUND(3,1,3);
//        w_flag=2;
//		delay_secs(2);
//		Warning_Scr_Erase();
//
//	}
//	else if((warning_flag[2]==1) && (w_flag==2))
//	{
//		Warning_screen((uint8_t *)"Battery Low",0);
//		WARN_SOUND(3,1,3);
//		w_flag=0;
//		delay_secs(2);
//		Warning_Scr_Erase();
//
//	}
//	else
//	{
//
//	}


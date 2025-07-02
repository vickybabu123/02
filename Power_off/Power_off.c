
#include "LPC55S16.h"
#include "Color.h"
#include "Shapes.h"
#include "TFT_String.h"
#include "Driver_Timer.h"
#include "fsl_clock.h"
#include "../Menu_Setting/Main_Menu.h"
#include "Driver_ADC.h"
#include "TFT_Commands.h"
#include "Power_off.h"
#include "Bolus_Header.h"
#include"Alarm.h"
#include "Events_log.h"
#include <Consumed_hrs.h>
#include "Power_off.h"
#include "Keypad.h"
#include <Boot_up.h>
#include "Dosage_mode.h"
#include "sound.h"

power_flag POW;
main_flag MAIN;
battery BATT;

volatile uint8_t Confirm_count=0;
uint8_t purge_device_in=0;
uint8_t device_check_cnt;
uint8_t G_mode_power_flag=0;
extern uint8_t G_Fr_sound_flag;

extern uint8_t G_footer_edit_flag;

uint16_t status_of_power_off();

extern uint16_t Power_Interval_Delay;

extern uint8_t normal_run;//12-06-2024
extern uint8_t G_infusion_modes;
extern uint8_t near_to_target_flag;
extern uint8_t war_disp;
extern uint8_t home_flag;
extern uint8_t G_bright_level;
extern uint8_t G_infusion_modes;
extern uint8_t G_main_screen_flag;
extern uint8_t ON_Flag;
extern uint8_t G_KVO_run_flag;
extern uint8_t Switch_power_read;
extern uint8_t Press_Back_Read;
extern uint8_t Bar_power_Read;
extern uint8_t Bolus_reset_flag;
extern uint8_t G_power_edit;

extern char Drug_Names[150][4][20];

extern uint16_t ADC_power_key_sampling(uint16_t Raw_val, uint16_t Data_diff,uint8_t samples);
extern void power_status(void);
extern void batt_stat(void);
extern void battery_status(void);
extern void  write_current_data(uint8_t mode);


/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Power_off()
 {
	volatile uint16_t Output_sample=0;
	volatile uint16_t PWR_values=0;
	uint16_t status_values=0;
	static uint8_t device_off_flag=0;

	power_status();
	battery_status();
	batt_stat();
    usedhrs_status();

    if(Power_Interval_Delay==0)
    {
		Power_Interval_Delay=100;
		PWR_values=ADC_read(ADC_CH_POWER_KEY);
		Output_sample=ADC_power_key_sampling(PWR_values,100,10);


//  Font_Select(ARIAL_14);
//  TFT_Number(120,70,PWR_values,YELLOW,RED);





//	Font_Select(ARIAL_14);
//	TFT_Number(120,90,Output_sample,YELLOW,RED);
//	TFT_Number(120,110,Confirm_count,YELLOW,RED);
	//delay_secs(2);

		if(Output_sample > 750)   //2000)
		{
			if(Confirm_count>3)
			{
				    if((!normal_run)&&(!BOL.run_mode))//12-06-2024
					{
				    	//TFT_Number(120,90,122,YELLOW,RED);

						status_values = status_of_power_off();

						    if(status_values > 110)
							{
							    Timer_disable();
							    EEPROM_usedhrs_write(0);//ALL USED_HRS WRITE WHILE POWER OFF
							    event_no_update(2);
							    write_current_data(G_infusion_modes);
							    home_flag=0;
								G_bright_level=0;
								ON_Flag=0;
								Output_sample=0;
								Confirm_count=0;
								G_mode_power_flag=1;
							    SUPPLY_TRIGGER_OFF;
								Rectangle(0,0,320,240,BLACK);
								while(1)
								{
									PWR_values=ADC_read(ADC_CH_POWER_KEY);
									delay_ms(100);

									if(PWR_values<700)
									break;
								}
							}

						else
						{
							Confirm_count=0;
							POW.power_status_flag=1;
						}
				}


			else
			{
						if(device_off_flag==0)//12-06-2024
						{
							device_off_flag=1;

							if(((normal_run) && (!BOL.run_mode)) && (((!G_KVO_run_flag) && (!Bolus_reset_flag)) && ((!G_power_edit))) )
							{
								//Warning_screen((uint8_t *)"Device in use",0);
								Notification(DEV_IN_USE);
							}

							else if((BOL.run_mode) || (G_power_edit))
							{
								Frame_Footer_warning(WARNING_COLOR,BLACK,(uint8_t*)"Device in use",(uint8_t*)"",0);
								purge_device_in=2;
								WARN_SOUND(3,1,3);

							}

//							if(!purge_device_in)
//							{
//								Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to Stop",(uint8_t*)"BK",1);
//							}

							device_check_cnt=3;
						}

						else
						{
							if(G_infusion_modes==2)
							{
								if(!device_check_cnt)
								{
									if((normal_run) &&(!BOL.run_mode) &&(!G_KVO_run_flag))
									{
										Warning_Scr_Erase();
										TFT_ST7789V__rectangle_curve(95,95,30,185+25,0,NEW_HDR_COL);
										Font_Select(ARIAL_12);
										TFT_String(105,102,(uint8_t*)Drug_Names[(dose.drug_select_no/4)][(dose.drug_select_no%4)],NEW_HDR_COL,BLACK);
									}

									war_disp=0;
									device_off_flag=0;
								}
							}
//							else
//							{
//								device_off_flag=0;
//							}

						}

					}
				}             //12-06-2024
				else
				{
					Confirm_count++;
					//TFT_Number(50,190,Confirm_count,YELLOW,RED);
				}
		}

	else
	{
		Confirm_count=0;
			if(device_off_flag)
			{
				if(!device_check_cnt)
				{
						if( (normal_run<=1) && (home_flag)  && (!G_KVO_run_flag) )
						{
							Warning_Scr_Erase();
						}
							if((!purge_device_in) && (!home_flag) && (!G_KVO_run_flag) )
							{
								if(!G_footer_edit_flag)
								{
									Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to Stop",(uint8_t*)"BK",1,14);
								}
								else
								{
									Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        Confirm",(uint8_t*)"OK",1,14);
								}
							}
								war_disp=0;
								device_off_flag=0;
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

uint16_t status_of_power_off()
{
	uint16_t loop_count=0;
	uint16_t PWR_values=0;
	uint16_t Output_sample=0;
	//uint16_t loop_count_1=0;

	//Rectangle(0,0,320,240,MAIN_FRAME_COL);

	CLRSCR(MAIN_FRAME_COL);

	Font_Select(ARIAL_14);
	Rectangle(30,120,260,1,WHITE);
	Rectangle(30,160,260,1,WHITE);

	Rectangle(30,121,1,40,WHITE);
	Rectangle(290,121,1,40,WHITE);


	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Power Off");
	Frame_Footer_NC(NEW_FTR_COL,HDR_TXT_COL,(uint8_t *)"Keep Press");

	Font_Select(ARIAL_12);
	TFT_String_align(0,319,170,(uint8_t *)"Shutting down...",0,MAIN_FRAME_COL,WHITE);

	for(loop_count=0;loop_count<=120;loop_count++)
	{
//		if(!Bar_power_Read)
//		{
//			Bar_power_Read=1;
			PWR_values=ADC_read(ADC_CH_POWER_KEY);
	//	}
		delay_ms(10);
		Output_sample=ADC_power_key_sampling(PWR_values,100,10);

		if(Output_sample > 70)
		{
			Rectangle(40+(loop_count*2),130,0,20,WHITE);
		}

		else
		{
			 CLRSCR(MAIN_FRAME_COL);
			 break;
		}

//		if(loop_count==120)
//		{
//			GPIO->SET[1]|=1<<15;
//		}



	}
	if(loop_count>110)		//18_03
	{
		Power_off_beep_sound();
	}
//	Power_off_beep_sound();
//	for(loop_count_1=0;loop_count_1<4;loop_count_1++)
//	{
//		beep_sound();
//	}

	return loop_count;
}




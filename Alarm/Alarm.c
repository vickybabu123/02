/****************************************************************************
* File Name    : Alarm
* Developed by :
* Version      : V 1.00
* Description  : i)

*****************************************************************************/
#include "stdint.h"
#include "TFT_Commands.h"
#include "TFT_String.h"
#include <stdio.h>
#include "LPC55S16.h"
#include "Color.h"
#include <FR_CALC.h>
#include "Keypad.h"
//#include "Dynamic_Pressure.h"
#include "Shapes.h"
#include "Alarm.h"
#include "Linear_Header.h"
#include "Motor.h"
#include  "sound.h"
#include "STEPPER.h"
#include "Driver_Timer.h"
#include "Bolus_Header.h"
#include <math.h>
#include "Power_off.h"
//#include "Symbol.h"
//#include "Events_log.h"
#include "TFT_String.h"
#include "infused_calculate.h"
#include "Main_screen.h"
#include "Alarm.h"
#include "Boot_up.h"

uint8_t G_warn_flag=0;//28-03
uint8_t G_alarm_ok_flag=0;
uint8_t G_syringe_size_flag=0;
uint8_t kvo_alter_falg=1;
uint16_t mute_count;

extern uint8_t G_infusion_modes;

extern volatile uint8_t normal_run;
extern uint8_t ON_Flag;
extern uint8_t end_flag;
extern uint8_t plunger_distrubed;
extern uint16_t Pump_idle;


extern uint8_t G_run_flag;
extern void main_screen_frame(uint16_t flowrate1,uint8_t mode);
extern void syringe_disp_status(uint8_t screen);

extern uint8_t G_KVO_run_flag;
extern uint16_t G_KVO_set_fr;
extern void shutting_down(void);

void Alarm_Running(uint8_t L_R_flag);
void Alarm_war_screen(uint8_t state);
void Notif_screen(uint8_t *Notif_name);
extern uint8_t G_run_count;
void Notif_screen(uint8_t *Notif_name);
void Mains_symbol(uint8_t x_pos_adj,uint8_t y_pos_adj);
void alarm_string(uint8_t alarm_no);
uint8_t G_warn_count=0;
extern uint8_t siphonic_time;
extern uint8_t G_fr_wrn_flag;
extern uint8_t home_flag;
extern uint8_t near_to_target_flag;
extern uint8_t sy_size;
extern uint8_t G_pre_sy_size_1[1];
extern uint8_t G_Loop_alarm;
extern uint16_t press_run_alarm;
extern uint8_t TFT_ST7789V_keylock4_symbol_16pt(uint16_t xpos, uint16_t ypos,
       uint8_t arrow, uint32_t boarder_color, uint32_t fill_color);

/****************************************************************************
* Function Name : void Alarm_screen(uint8_t *alarm_name)
* Arguments     : Name of the alarm
* Return type   : void
* Description   : i)   Display the alarm name
*                 ii)  Alarm instruction

*****************************************************************************/
void Alarm_screen(uint8_t *alarm_name)
{

//	uint16_t YPOS=0;
	Rectangle(0,0,320,240,ALARM_COLOR);
	TFT_ST7789V__rectangle_curve(10,65-10,60+20,300,0,LIGHT_GRAY);  //Rectangle Curve Option 1
	Rectangle(10,203,301,1,BLACK);

	Font_Select(ARIAL_20);
//	YPOS=Letters_Alignments(0,0,alarm_name,2);
//	TFT_String(YPOS,80,alarm_name,LIGHT_GRAY,BLACK);
	TFT_String_align(0,0,80,alarm_name,2,LIGHT_GRAY,BLACK);
	Frame_Footer(ALARM_COLOR,WHITE,(uint8_t*)"        Confirm Alarm",(uint8_t*)"OK",1,14);

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void Alarm_screen_1(uint8_t *alarm_name)
{
//	uint16_t YPOS=0;
	Rectangle(0,0,320,240,ALARM_COLOR);
	TFT_ST7789V__rectangle_curve(10,65-10,60+20+20,300,0,LIGHT_GRAY);  //Rectangle Curve Option 1
	Rectangle(10,203,301,1,BLACK);

	Font_Select(ARIAL_20);
//	YPOS=Letters_Alignments(0,0,alarm_name,2);
//	TFT_String(YPOS,70,alarm_name,LIGHT_GRAY,BLACK);
	TFT_String_align(0,0,70,alarm_name,2,LIGHT_GRAY,BLACK);

	TFT_String(85,115,(uint8_t*)"Disturbed",LIGHT_GRAY,BLACK);
	Frame_Footer(ALARM_COLOR,WHITE,(uint8_t*)"        Confirm Alarm",(uint8_t*)"OK",1,14);
}

/****************************************************************************
* Function Name : void Error_screen(uint8_t *Error_name)
* Arguments     : Name of the alarm
* Return type   : void
* Description   : i)   Display the Error code
*                 ii)  Alarm instruction

*****************************************************************************/

void Error_screen(uint8_t *Error_name)//28-03
{
//	uint16_t YPOS=0;
	Rectangle(0,0,320,240,WHITE);

	Font_Select(ARIAL_20);
//	YPOS=Letters_Alignments(0,0,Error_name,2);
//	TFT_String(YPOS,80,Error_name,WHITE,BLACK);
	TFT_String_align(0,0,80,Error_name,2,WHITE,BLACK);
	Frame_Footer(LIGHT_GRAY_4,WHITE,(uint8_t*)"Contact BME",(uint8_t*)"",0,14);
}

/****************************************************************************
* Function Name : void Error_screen(uint8_t *Error_name)
* Arguments     : Name of the alarm
* Return type   : void
* Description   : i)   Display the Error code
*                 ii)  Alarm instruction

*****************************************************************************/

void alarm_string(uint8_t alarm_no)
{
	switch(alarm_no)
		{
			case OCCL:
				//event_no_update(5);
				WARN_SOUND(4,1,2);
				Alarm_screen((uint8_t*)"Occlusion Alarm");
				break;

			case PLUNGER:
				//event_no_update(7);
				WARN_SOUND(4,1,2);
				Alarm_screen((uint8_t*)"Plunger Disturbed");
				break;

			case SYR_DIS:
			//	event_no_update(8);
				WARN_SOUND(4,1,2);
				G_fr_wrn_flag=0;
				Alarm_screen((uint8_t*)"Syringe Disturbed");
				break;

			case NOT_ENGAGE:
				//event_no_update(10);
				WARN_SOUND(4,1,2);
				Alarm_screen((uint8_t*)"Plunger not Engaged");
				break;

			case SIPHONIC:
				WARN_SOUND(4,1,2);
				Alarm_screen((uint8_t*)"Siphonic Alarm");
				break;

			case SYR_END:
			//	event_no_update(9);
				WARN_SOUND(4,1,2);
				Alarm_screen((uint8_t*)"Syringe End");
				break;

			case BATTERY_ALM:
				WARN_SOUND(4,1,2);
				Alarm_screen((uint8_t*)"Battery Critical");
				break;

			case SYR_NOT_ENGAGE:
			//	event_no_update(10);
				WARN_SOUND(4,1,2);
				Alarm_screen((uint8_t*)"Syringe not Eng");
				break;

			case TARGET:

		//  event_no_update(8);
			WARN_SOUND(4,1,2);
			Alarm_screen((uint8_t*)"Target Reached");
			delay_secs(3);

//			if((G_KVO_run_flag))// || (kvo_alter_falg))
//			{
//				Alarm_war_screen(0);
//			}


//              kvo_alter_falg=0;
//	            else
//			    home_flag=1;
//			    Alarm_war_screen(0);
//				kvo_alter_falg=1;
//			}
				break;

	          case MOT_ERR_1://28-03
	        //	event_no_update(6);
				WARN_SOUND(4,1,2);
				Error_screen((uint8_t*)"Err.1001"); //Motor unable to run
				break;

			case MOT_ERR_2:
				//event_no_update(6);
				WARN_SOUND(4,1,2);
				Error_screen((uint8_t*)"Err.1005"); //Motor reverse
				break;

			case MOT_ERR_3:
			//	event_no_update(6);
				WARN_SOUND(4,1,2);
				Error_screen((uint8_t*)"Err.1006"); //Less cuts
				break;

			case MOT_ERR_4:
			//	event_no_update(6);
				WARN_SOUND(4,1,2);
				Error_screen((uint8_t*)"Err.1007"); //Excess cuts
				break;

			case DISC_ERR:
			//	event_no_update(6);
				WARN_SOUND(4,1,2);
				Error_screen((uint8_t*)"Err.1010"); //DISC ERROR
				break;

			case CALIBRATION_ERR:
			//	event_no_update(6);
				WARN_SOUND(4,1,2);
				Error_screen((uint8_t*)"Err.1008"); //DISC ERROR
				break;

			case BATTERY_ERR:
			//	event_no_update(6);
				WARN_SOUND(4,1,2);
				Error_screen((uint8_t*)"Err.1015"); //BATTERY ERROR
				break;
		}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Alarm(uint8_t alarm_no)
{
	uint8_t alarm_loop=1;
	POW.power_status_flag=1;//26-03
	home_flag=0;
	uint8_t batt_cnt=0;


	if(!G_KVO_run_flag)        // kvo RUNNING CONCEPT
	{
	 Timer_disable();
	}

	while(alarm_loop)
	{

		if(!mute_count)
		{
		   alarm_sound_tone();
		}

	//	Power_off();

//		if(G_Loop_alarm)
//		{
//			break;
//		}

		if(!ON_Flag)
		{
		  break;//26-03
		}

		else if(POW.power_status_flag)
		{

		  POW.power_status_flag=0;//26-03
		  alarm_string(alarm_no);
		  while(KEY.value);

		}

			if(alarm_no==11)
			{
				batt_cnt++;
				if(batt_cnt>5)
				{
					batt_cnt=0;
					delay_secs(2);
					shutting_down();
					Rectangle(0,0,320,240,BLACK);
					SUPPLY_TRIGGER_OFF;
				}
			}

//		if(G_KVO_run_flag)
//		{
//		  Alarm_Running(0);
//		}

//		if(!G_syringe_size_flag)
//		{
//			syringe_disp_status(0);
//			plunger_alarm_check();
//		}

		if((KEY.value==START_STOP_KEY)  || (KEY.value==OK_KEY) )
		{
//			if(G_KVO_run_flag)
//			{
//				G_KVO_run_flag=0;
//				Timer_disable();
//			}
//			stepper_Forward();	//REW_UP
//			MFB_count_reset(0);
//			MFB_count_reset(1);
//			MFB_count_reset(2);
//			home_flag=0;
			Timer_disable();
			G_alarm_ok_flag=1;
			alarm_loop=0;
			MFB.Motor_struck=0;
			LIN_POT.syr_end_flag=0;
			normal_run=0;
			POW.power_status_flag=1;
			siphonic_time=30;
			BOL.run_mode=0;//28-03
		// 	buzzer_pwm_stop();
			BUZZER_PIN = 0X00;
			RAMP.up_flag=0;
			press_run_alarm=180;
			Pump_idle=10;
			mute_count=0;
			//ON_Flag=0;
		//	mute_count=20;
			while(KEY.value);
			break;
		}

		if(KEY.value==MUTE_KEY)
		{
			pwm_sta( alarm_sound.period,0);
			mute_count=20;

			while(KEY.value);
			//break;
		}
//		else if(KEY.value==MUTE_KEY)
//		{
//			WARN_SOUND(0,0,0);
//			while(KEY.value);
//			break;
//		}

	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Warning_screen(uint8_t *Warning_name,uint8_t mode)
{
	uint16_t YPOS=0;

	if(mode==0)
	{

	TFT_ST7789V__rectangle_curve(86,92,62,229,0,WARNING_COLOR);

	Font_Select(ARIAL_12);
//	YPOS=Letters_Alignments(86,315-30,Warning_name,0);
//	TFT_String(YPOS,97+2,Warning_name,WARNING_COLOR,BLACK);
	TFT_String_align(86,285,99,Warning_name,0,WARNING_COLOR,BLACK);

	TFT_ST7789V_Warning_symbol_18pt(98,280,0,WARNING_COLOR,BLACK);
	TFT_ST7789V_Exclamatory_9pt_arial(98+6,280+9,0,WARNING_COLOR,BLACK);
//	TFT_ST7789V_Triangle_24pt(97-3,275-5,0,WARNING_COLOR,WHITE);


//	YPOS=Letters_Alignments(86,315-15,(uint8_t*)"        Mute Alarm",0);
//	TFT_String(YPOS,131-2,(uint8_t*)"        Mute Alarm",WARNING_COLOR,BLACK);
	YPOS=TFT_String_align(86,300,129,(uint8_t*)"        Mute Alarm",0,WARNING_COLOR,BLACK);

	TFT_ST7789V_lcd_drawcircle1(YPOS+15,138,14,WARNING_COLOR,BLACK);
	TFT_ST7789V_lcd_drawcircle1(YPOS+15,138,12,WARNING_COLOR,LIGHT_GRAY);

	TFT_ST7789V_Mute_Symbol_12pt(138-7,YPOS+15-8,0,LIGHT_GRAY,BLACK);
	Rectangle(91,122,219,0,BLACK);
	G_warn_flag=1;//28-03
	if(G_infusion_modes==2)
	{
		dose_rate_para(1,3);
		infused_data(1,G_infusion_modes);
	}

	}
	else if(mode==1)
	{
		 Frame_Footer(RED,YELLOW,(uint8_t*)Warning_name,(uint8_t*)"OK",0,14);
	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void warn_tone(uint8_t warn_dura_sec)
{
	G_warn_flag=1;
	if(G_warn_flag)
	{
		if(!G_warn_count)
		{
			WARN_SOUND(3,1,3);
			G_warn_count=warn_dura_sec;
		}

	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Notif_screen(uint8_t *Notif_name)
{
	//uint16_t YPOS=0;
	TFT_ST7789V__rectangle_curve(86,92,62,229,0,WARNING_COLOR);
	Font_Select(ARIAL_12);
//	YPOS=Letters_Alignments(86,315+30,Notif_name,0);
//	TFT_String(YPOS,115,Notif_name,WARNING_COLOR,BLACK);
	TFT_String_align(86,345,115,Notif_name,0,WARNING_COLOR,BLACK);
	Rectangle(135,100,1,45,BLACK);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Notif_screen_1(uint8_t *Notif_name)
{
//	uint16_t YPOS=0;
	TFT_ST7789V__rectangle_curve(36,92,62,250,0,WARNING_COLOR);
	Font_Select(ARIAL_12);
//	YPOS=Letters_Alignments(36,315+30,Notif_name,0);
//	TFT_String(YPOS,115,Notif_name,WARNING_COLOR,BLACK);
	TFT_String_align(36,345,115,Notif_name,0,WARNING_COLOR,BLACK);

////
////	TFT_ST7789V_lcd_drawcircle1(YPOS+15,138,14,WARNING_COLOR,BLACK);
////	TFT_ST7789V_lcd_drawcircle1(YPOS+15,138,12,WARNING_COLOR,LIGHT_GRAY);
//
////	TFT_ST7789V_Mute_Symbol_12pt(138-6,YPOS+15-8,0,LIGHT_GRAY,BLACK);
////	Rectangle(91,122,219,0,BLACK);
//
//
//}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Warning_Scr_Erase()
{
	G_warn_flag=0;//28-03
	near_to_target_flag=0;

	Rectangle(86,92,229,65,MAIN_FRAME_COL);
	Rectangle(120,115,180,0,BLACK); 	//Row Lines

	if(G_infusion_modes==2)
		{
			dose_rate_para(0,3);
		}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Alarm_Running(uint8_t L_R_flag)
{
	uint16_t Y_pos[2][3]={{30,47,64},{236,253,270}};
	uint32_t colour[2][4][3]={
			{{LIGHT_GRAY,LIGHT_GRAY,BLACK},{LIGHT_GRAY,BLACK,BLACK},
									{BLACK,BLACK,BLACK},{LIGHT_GRAY,LIGHT_GRAY,LIGHT_GRAY}
				},
			{{LIGHT_GRAY,LIGHT_GRAY,LIGHT_GRAY},{BLACK,LIGHT_GRAY,LIGHT_GRAY},
								{BLACK,BLACK,LIGHT_GRAY},{BLACK,BLACK,BLACK}
	}

	};
	uint8_t pos;
	uint32_t col=LIGHT_GRAY;
	uint8_t X_pos[2]={92,92};
	static uint8_t state=0;
	 if(!G_run_count)
	 {
		for (pos = 0; pos <= 2; pos++)
		 {
			TFT_ST7789V_ALARM_ARROW_20pt(X_pos[L_R_flag],Y_pos[L_R_flag][pos],0,col,colour[L_R_flag][state][pos],L_R_flag);
		 }
		 if(state<3)
		 {
			 state++;
		 }
		 else
		 {
			 state=0;
		 }
		 G_run_count=5;

	 }

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Alarm_war_screen(uint8_t state)
{
	uint16_t war_sym_pos[2]={260,210};

	//syringe_disp_status(0);


	Rectangle(0,0,320,240,ALARM_COLOR);

//	Font_Select(ARIAL_14);
//	TFT_Number(0,180,home_flag,YELLOW,RED);

	TFT_ST7789V__rectangle_curve(10,40,120,300,0,WARNING_COLOR);
	TFT_ST7789V__rectangle_curve(15,80,40,290,0,LIGHT_GRAY);



	TFT_ST7789V_Warning_symbol_18pt(51,war_sym_pos[state],0,WARNING_COLOR,BLACK);
    TFT_ST7789V_Exclamatory_9pt_arial(51+6,war_sym_pos[state]+9,0,WARNING_COLOR,BLACK);


    TFT_ST7789V_lcd_drawcircle1(60+35,141,14,WARNING_COLOR,BLACK);
	TFT_ST7789V_lcd_drawcircle1(60+35,141,12,WARNING_COLOR,LIGHT_GRAY);
	TFT_ST7789V_Mute_Symbol_12pt(141-7,60+35-8,0,LIGHT_GRAY,BLACK);

	Font_Select(ARIAL_14);
	TFT_String(90+30,130,(uint8_t*)"Mute Alarm ",WARNING_COLOR,BLACK);
	if(!state)
	{
		TFT_String(70,50,(uint8_t*)"Target Reached",WARNING_COLOR,BLACK);
		TFT_String(100,90,(uint8_t*)"KVO in progress",LIGHT_GRAY,BLACK);
		Rectangle(10,193+10,301,1,BLACK);  // Footer Boarder line
		Frame_Footer(ALARM_COLOR,WHITE,(uint8_t*)"        Confirm Alarm",(uint8_t*)"ST",1,14);
	}

	else
	{
		TFT_String(95,50,(uint8_t*)"Occlusion ",WARNING_COLOR,BLACK);
		TFT_String(100,90,(uint8_t*)"Anti Bolus",LIGHT_GRAY,BLACK);
		Rectangle(10,193+10,301,1,BLACK);  // Footer Boarder line
		Frame_Footer(ALARM_COLOR,WHITE,(uint8_t*)"        Confirm Alarm",(uint8_t*)"ST",1,14);
	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Notification(uint8_t notif)
{
	//beep_sound();
	WARN_SOUND(2,1,2);
	switch(notif)
	{
		case KEY_LOCK:
						Notif_screen((uint8_t *)"Unlock Keypad !");
						TFT_ST7789V_keylock4_symbol_16pt(110,100,0,WARNING_COLOR, BLACK);
						break;
		case KEY_UNLOCK:
						Notif_screen((uint8_t *)"Keypad unlocked");
						TFT_ST7789V_keyunlock4_symbol_16pt(110,100,0,WARNING_COLOR, BLACK);
						break;

		case MAINS_PLUGIN:
						Notif_screen((uint8_t *)"Mains Plugin");
		             	Mains_symbol(90,118);
		             	break;

		case MAINS_PLUGOUT:
						Notif_screen((uint8_t *)"Mains Plugout");
		             	Mains_symbol(90,118);
		             	Single_line_fun();
						break;

		case SET_FLOWRATE:
						Notif_screen((uint8_t *)"Set Flowrate");
						TFT_ST7789V_Warning_symbol_18pt(110,100,0,WARNING_COLOR,BLACK);
						TFT_ST7789V_Exclamatory_9pt_arial(110+6,100+9,0,WARNING_COLOR,BLACK);
						break;

	    case SET_FLOWRATE_1:
						Notif_screen_1((uint8_t *)"SET FLOWRATE");
					//	TFT_ST7789V_keylock4_symbol_16pt(110,100,0,WARNING_COLOR, BLACK);
						TFT_ST7789V_Warning_symbol_18pt(110,70,0,WARNING_COLOR,BLACK);
						TFT_ST7789V_Exclamatory_9pt_arial(110+6,70+9,0,WARNING_COLOR,BLACK);
						break;

		case SET_TARGET:
						Notif_screen_1((uint8_t *)"SET TARGET");
					//	TFT_ST7789V_keylock4_symbol_16pt(110,100,0,WARNING_COLOR, BLACK);
						TFT_ST7789V_Warning_symbol_18pt(110,70,0,WARNING_COLOR,BLACK);
						TFT_ST7789V_Exclamatory_9pt_arial(110+6,70+9,0,WARNING_COLOR,BLACK);
						break;

		case PUMP_IDLE:
						Notif_screen((uint8_t *)"Pump Idle");
						break;

		case BATTERY_FULL_1:
						Notif_screen((uint8_t *)"Battery full");
						Mains_symbol(90,118);
						break;

		case SET_FR:
					Notif_screen((uint8_t *)"> max FR");
					TFT_ST7789V_Warning_symbol_18pt(110,100,0,WARNING_COLOR,BLACK);
					TFT_ST7789V_Exclamatory_9pt_arial(110+6,100+9,0,WARNING_COLOR,BLACK);
					break;

		case DEV_IN_USE:
					Notif_screen((uint8_t *)"Device in use");
					TFT_ST7789V_Warning_symbol_18pt(110,100,0,WARNING_COLOR,BLACK);
					TFT_ST7789V_Exclamatory_9pt_arial(110+6,100+9,0,WARNING_COLOR,BLACK);
					break;

		case SYRINGE_END:
							Notif_screen((uint8_t *)"Syringe End");
							TFT_ST7789V_Warning_symbol_18pt(110,100,0,WARNING_COLOR,BLACK);
							TFT_ST7789V_Exclamatory_9pt_arial(110+6,100+9,0,WARNING_COLOR,BLACK);
							break;


	}
	press_run_alarm=180;
	Pump_idle=10;
	delay_ms(2500);
	Warning_Scr_Erase();
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Mains_symbol(uint8_t x_pos_adj,uint8_t y_pos_adj)
{
	TFT_ST7789V_lcd_drawcircle1(x_pos_adj+20,y_pos_adj+5,17,BLACK,BLACK);
	TFT_ST7789V_lcd_drawcircle1(x_pos_adj+20,y_pos_adj+5,14,WARNING_COLOR,WARNING_COLOR);

    TFT_ST7789V_circle1(x_pos_adj+20,y_pos_adj+3,9,BLACK,BLACK);   //left quadrant circle for mains symbol
    TFT_ST7789V_circle3(x_pos_adj+20,y_pos_adj+3,9,BLACK,BLACK);   //right quadrant circle for mains symbol

	Rectangle(x_pos_adj+10,y_pos_adj,20,2,BLACK);            //Bar type line
	Rectangle(x_pos_adj+19,y_pos_adj+10,3,7,BLACK);       //mains symbol line
	Rectangle(x_pos_adj+15,y_pos_adj-5,2,4,BLACK);      //left plugin line
	Rectangle(x_pos_adj+23,y_pos_adj-5,2,4,BLACK);    //right plugin line
	//TFT_ST7789V_thunder_8_pt(y_pos_adj+2,x_pos_adj+17,0,BLACK,WHITE);          //Thunder symbol
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void caution_info(uint8_t *Warning_name)
{
//	uint16_t xpos=0;
	TFT_ST7789V__rectangle_curve(45,80,82,229-15,0,WARNING_COLOR);
	Font_Select(ARIAL_12);
//	xpos=Letters_Alignments(60,315-61,Warning_name,0);
//	TFT_String(xpos,97+2+15,Warning_name,WARNING_COLOR,BLACK);
	TFT_String_align(60,254,114,Warning_name,0,WARNING_COLOR,BLACK);

	TFT_ST7789V_Warning_symbol_18pt(86+12+12,48,0,WARNING_COLOR,BLACK);
	TFT_ST7789V_Exclamatory_9pt_arial(86+12+6+12,48+9,0,WARNING_COLOR,BLACK);
}


void Single_line_fun(void)
{
	/*************************mains unplug line*******************************/

uint16_t angle=0;
float theta=0;
uint8_t radius=46;
int  start_x,start_y;

		for(angle=20;angle>0;angle--)
		{
			theta=angle*(3.14/90);
			start_x=cos(theta)*radius;
			start_y=sin(theta)*radius;



			//if (angle>=15 && angle<=16)
			if(angle==15)
			{
			lcd_drawline(90+start_x,135-start_y,90,135,BLACK);
			lcd_drawline(90+start_x,135-start_y,90,135,BLACK);

			}


		}




	/**************************************************************************/
}

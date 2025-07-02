/*
 * Target_fun.c
 *
 *  Created on: 06-Feb-2024
 *      Author: Software3
 */
#include "LPC55S16.h"
#include "Target_fun.h"
#include <math.h>
#include "Color.h"
#include "TFT_Commands.h"
#include "Shapes.h"
#include "TFT_String.h"
#include "Keypad.h"
#include "Driver_Timer.h"
#include "FR_CALC.h"
#include "Flowrate_Screen.h"
#include "Driver_I2C.h"
#include <STEPPER.h>
#include "Alarm.h"
#include "Main_screen.h"
#include "sound.h"
#include "Events_log.h"				//25-03
#include "Power_off.h"
#include <Boot_up.h>
#include "Main_Menu.h"

const char* Target_disp[3]={"Flowrate","T.volume","T.time"};
const char* Target_unit_disp[3]={"mL/h","mL","hh:mm"};

uint32_t volume_cal(uint32_t time_value , uint32_t flowrate_value);
uint32_t flowrate_cal(uint32_t time_value , uint32_t volume_value);
uint32_t time_cal(uint32_t flowrate_value , uint32_t volume_value);
void Target_mode_frame(void);
void Target_mode_opt_Frame(uint8_t start_opt,uint8_t end_opt);
void Target_mode_cursor(uint8_t prev_option, uint8_t curr_option);
uint8_t Target_mode_setting(void);
uint8_t fr_edit_flag=0;

extern uint8_t edit_screen(uint16_t *Edit_value,uint8_t screen,uint16_t max_value);
extern volatile uint8_t normal_run;
extern void infuse_clr();
extern void Running_symbol(uint8_t X_start, uint8_t Y_start,uint32_t col);
extern uint8_t edit_screen_Time(uint32_t *Edit_value,uint8_t screen,uint16_t max_value);
extern uint8_t ON_Flag;
extern uint8_t key_pressed;
extern uint8_t disc;
extern uint8_t sy_size;
extern uint32_t Flow_rate_screen(uint32_t *flow_rate ,uint8_t Min_Limit,uint32_t Max_Limit,uint8_t screen);
extern uint32_t Flow_rate_screen(uint32_t *flow_rate ,uint8_t Min_Limit,uint32_t Max_Limit,uint8_t screen);

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
uint8_t Target_mode_setting(void)
{
	uint8_t t_loop_flag=1;
	uint8_t t_curr_pos=0;
	uint8_t t_pre_pos=0;
	uint8_t check_flag=0;
	uint8_t curr_max=0;
	uint32_t Max_limit=0;
	uint16_t syr_limit[7]={0,1800,3500,5000,9000,12000,12000};
//	uint32_t VTBI_copy_fr=MOT.flowrate;
//	uint32_t VTBI_copy_ml= MOT.volume;
//	uint16_t VTBI_copy_time=MOT.time;


	Target_mode_frame();
	Target_mode_opt_Frame(0,2);

	if(normal_run)
	{
		curr_max=1;
	}
	else
	{
		curr_max=2;
	}
//	POW.power_status_flag=1;
	while(KEY.value);
	while(t_loop_flag)
	{

	   Power_off();

	   if(!ON_Flag)
	   {
			break;//26-03
	   }

	   else if(POW.power_status_flag)
	   {
			POW.power_status_flag=0;//26-03
			Target_mode_frame();
			Target_mode_opt_Frame(t_curr_pos,2);//26-03
	   }

		if(normal_run)
		{
			Running_symbol(0,0,MAIN_FRAME_COL);
		}

		 else
		 {
			TFT_ST7789V_Left_Arrow_22pt(RUNSYMBOL_POS-5,18+5,0,NEW_HDR_COL,ORANGE);
			Rectangle(18+22+2,RUNSYMBOL_POS-5,5,21,ORANGE);
			Rectangle(18+32+2,RUNSYMBOL_POS-5,5,21,ORANGE);
		 }

		 if(normal_run==1)
		{
			syringe_disp_status(0);
		}


		switch(KEY.value)
		{
			case UP_KEY :
				beep_sound();
				         if(t_curr_pos>0)
				         {
				        	 t_curr_pos--;
				         }
				         else
				         {
				        	 t_curr_pos=curr_max;
				         }
				         Target_mode_cursor(t_pre_pos,t_curr_pos);
				         t_pre_pos=t_curr_pos;

//				         Font_Select(ARIAL_14);
//				         TFT_Number(30,70,t_curr_pos,YELLOW,RED);

				         while(KEY.value);
				         break;

			case DOWN_KEY :
				beep_sound();
						 if(t_curr_pos<curr_max)
						 {
							 t_curr_pos++;
						 }
						 else
						 {
							 t_curr_pos=0;
						 }
						 Target_mode_cursor(t_pre_pos,t_curr_pos);
						 t_pre_pos=t_curr_pos;

//						 Font_Select(ARIAL_14);
//						 TFT_Number(80,70,t_curr_pos,YELLOW,RED);

						 while(KEY.value);
						 break;

			case OK_KEY :

						beep_sound();
						while(KEY.value);
										        check_flag=1;
										        if(!t_curr_pos)
										        {
										        	if(MOT.volume)
										        	{
										        		Max_limit=flowrate_cal(1,MOT.volume);
										        		if(Max_limit>syr_limit[sy_size]) Max_limit=syr_limit[sy_size];
										        	}
										        	else if(MOT.time)
										        	{
										        		Max_limit=flowrate_cal(MOT.time ,20000);
										        		if(Max_limit>syr_limit[sy_size]) Max_limit=syr_limit[sy_size];
										        	}
										        	else
										        	{
										        		Max_limit=syr_limit[sy_size];
										        	}
										        	fr_edit_flag=1;
										        	Flow_rate_screen(&MOT.flowrate,0,Max_limit,2);

										        	if(MOT.flowrate && (MOT.volume || MOT.time))
													{
														if(MOT.volume)
														{
															VTBI_check(3);
														}
														else
														{
															VTBI_check(2);
														}
													}
										        	else if(!MOT.flowrate)
										        	{
										        		fr_edit_flag=0;
										        	}

										        }

										        else if(t_curr_pos==1)
										        {
//										        	 Font_Select(ARIAL_14);
//										             TFT_Number(40,70,fr_edit_flag,YELLOW,RED);

										        	if(fr_edit_flag==1)
										        	{
										        		if(MOT.flowrate)
														{
															Max_limit=volume_cal(9959 , MOT.flowrate);
															if(Max_limit>99999) Max_limit=99999;
														}
//										        		else
//										        		{
//										        			Max_limit=99999;
//										        		}

										        		Flow_rate_screen(&MOT.volume,0,Max_limit,1);

										        		if(MOT.volume)
														{
															VTBI_check(3);
														}
										        	}

										        	else
										        	{

														 if(MOT.time)
														{
															Max_limit=volume_cal(MOT.time , 12000);
															if(Max_limit>99999) Max_limit=99999;
														}
														else
														{
															Max_limit=99999;
														}

														Flow_rate_screen(&MOT.volume,0,Max_limit,1);
														if(MOT.time)
														{
															VTBI_check(1);
														}


										        	}

										        }

										        else
										        {
										        	 Font_Select(ARIAL_14);
										        	 TFT_Number(40,70,fr_edit_flag,YELLOW,RED);

										        	if(fr_edit_flag==1)
													{
										        		if(MOT.volume)
														{
															Max_limit=time_cal(1, MOT.volume);
															if(Max_limit>9959) Max_limit=9959;
														}
										        		 edit_screen_Time(&MOT.time, TIME_HHMM,Max_limit);
														//Flow_rate_screen(&MOT.time,0,Max_limit,1);
														if(MOT.time)
														{
															VTBI_check(2);
														}

													}

													else
													{
														if(MOT.volume)
														{
															Max_limit=time_cal(1, MOT.volume);
															if(Max_limit>9959) Max_limit=9959;
														}

														else
														{
															Max_limit=9959;
														}

														 edit_screen_Time(&MOT.time, TIME_HHMM,Max_limit);

														 if(!MOT.time)
														 {
															if(!fr_edit_flag)
															{
																MOT.flowrate=0;
															}
														 }


														 else if(MOT.volume)
														 {
															 VTBI_check(1);
														 }


													}


										        }
										        POW.power_status_flag=1;	//26-03
									         	break;

			case BACK_KEY :

		    beep_sound();
		    check_flag=0;
		    t_loop_flag=0;
		    while(KEY.value);
		    break;

			case MENU_KEY :

			Main_Menu_Screen();
//			Font_Select(ARIAL_14);
//			TFT_Number(200,150,199,YELLOW,RED);
//			TFT_Number(200,170,ON_Flag,YELLOW,RED);

	        POW.power_status_flag=1;	//26-03

			while(KEY.value);
			break;

			case START_STOP_KEY:

			beep_sound();
		    key_pressed=30;

			if((MOT.flowrate>=1 && MOT.flowrate<=12000)&&( MOT.volume>=1 && MOT.volume<=99999))
			{
				MR_Value_calculate(MOT.flowrate);

				if(!normal_run )
				{
					infuse_clr();
					event_no_update(3);
					normal_run=1;
					DRV8428_ENABLE();
					stepper_Forward();
				}

				t_loop_flag=0;
			}

			else
			{
				WARN_SOUND(2,1,2);
				if(MOT.flowrate==0)
				{
					Notification(SET_FLOWRATE);
				}
				else if (!MOT.volume)
				{
					Notification(SET_TARGET);
				}
				else
				{
					Notification(SET_FR);
				}
					Target_mode_frame();
					Target_mode_opt_Frame(t_curr_pos,2);
			}

				if(disc)
				{
				  Alarm(NOT_ENGAGE);
				}

						while(KEY.value);
						break;


		}
	}
	return check_flag;
}


/**************************************************************************
 *Function Name :void Target_mode_frame(void)
 *Arguments     :void
 *Return        :void
 *Description	:In this function for VTBI frame
***************************************************************************/
void Target_mode_frame(void)
{

	uint8_t menu_count = 0;

 // Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);

	Rectangle(0,0,320,34,NEW_HDR_COL);

	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"VTBI Mode");	// header
	for(menu_count = 1; menu_count <=3 ; menu_count++)				//no of lines
	{
		Rectangle(7,34+(43*menu_count),303,0, BLACK);		// no of rect line
	}

	TFT_ST7789V_lcd_shapes(38+163,38,300+15,306,LIGHT_GRAY_3);  	//Scroll bar                                                                                           //SCROLLING BOX OUTSIDE LAYER
	TFT_ST7789V_lcd_shapes(40+57,40,303+12,306,BLACK);

	Rectangle(0,206,320,34,NEW_FTR_COL);
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to Start",(uint8_t*)"ST",1,14);

}

/**************************************************************************
 *Function Name :void Target_mode_opt_Frame(uint8_t start_opt,uint8_t end_opt)
 *Arguments     :uint8_t start_opt,uint8_t end_opt
 *Return        :void
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

void Target_mode_opt_Frame(uint8_t start_opt,uint8_t end_opt)
{


	uint8_t loop_count=0;
    uint32_t back_colour = 0;
    uint32_t text_colour = 0;
 // uint32_t Target_val_disp[3]={MOT.flowrate,MOT.volume,MOT.time};
    uint32_t Target_val_disp[3]={MOT.flowrate,MOT.volume,MOT.time};

    uint16_t xpos=0;
	char local_buffer[6];
	for(loop_count=0;loop_count<=2;loop_count++)
	{
		if(loop_count == start_opt)//0==0
		{
			back_colour	= LIGHT_GRAY;
			text_colour = BLACK;
			TFT_ST7789V__rectangle_curve(3,35+(43*(start_opt)),41,312,0,back_colour); //0
		}
		else
		{
			back_colour	= MAIN_FRAME_COL;
			text_colour = WHITE;
		}

		Font_Select(ARIAL_14);
		TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
				(uint8_t*)Target_disp[loop_count],back_colour,text_colour);

		TFT_String(9+110,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
				(uint8_t*)":",back_colour,text_colour);

		if(loop_count!=2)
		{
			sprintf(local_buffer,"%.1f",((float)Target_val_disp[loop_count]/10.0));    //store the integer variables in to string using sprintf
			xpos=Right_Alignments((uint8_t*)local_buffer,263);
			TFT_writenumber_float_1d(xpos-50,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
					Target_val_disp[loop_count],back_colour,text_colour);
		}
		else
		{
			sprintf(local_buffer,"%04d",Target_val_disp[loop_count]);    			   //store the integer variables in to string using sprintf
			xpos=Right_Alignments((uint8_t*)local_buffer,263);
			TFT_Time_disp(xpos-55,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
					Target_val_disp[loop_count],back_colour,text_colour);
		}
		Font_Select(ARIAL_12);
		TFT_String((9+110+20+90),INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
				(uint8_t*)Target_unit_disp[loop_count],back_colour,text_colour);

	}

}

/**************************************************************************
 *Function Name :void Target_mode_cursor(uint8_t prev_option, uint8_t curr_option)
 *Arguments     :uint8_t prev_option, uint8_t curr_option
 *Return        :void
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

void Target_mode_cursor(uint8_t prev_option, uint8_t curr_option)
{

	uint8_t loop = 0;
	uint8_t opt_no  = 0;
	uint32_t back_colour = 0;
	uint32_t text_colour = 0;
	uint32_t Target_val_disp[3]={MOT.flowrate,MOT.volume,MOT.time};
	uint16_t xpos=0;
	char local_buffer[6];

	for(loop = 0; loop<2; loop++)
	{
		if(!loop)
		{
			back_colour = MAIN_FRAME_COL;
			text_colour = WHITE;
			opt_no		= prev_option;
		}
		else
		{
				back_colour = LIGHT_GRAY;
				text_colour = BLACK;
				opt_no= curr_option;
		}


		TFT_ST7789V__rectangle_curve(3,35+(43*(opt_no)),41,312,0,back_colour);

		Font_Select(ARIAL_14);

		TFT_String(9,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
				(uint8_t*)Target_disp[opt_no],back_colour,text_colour);

		TFT_String(9+110,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
			(uint8_t*)":",back_colour,text_colour);


		if(opt_no!=2)
		{
			sprintf(local_buffer,"%.1f",((float)Target_val_disp[opt_no]/10.0));    //store the integer variables in to string using sprintf
			xpos=Right_Alignments((uint8_t*)local_buffer,263);    //(uint8_t*)letter
			TFT_writenumber_float_1d(xpos-50,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
							Target_val_disp[opt_no],back_colour,text_colour);
		}
		else
		{
			sprintf(local_buffer,"%04d",Target_val_disp[opt_no]);    //store the integer variables in to string using sprintf
			xpos=Right_Alignments((uint8_t*)local_buffer,263);
			TFT_Time_disp(xpos-55,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
					Target_val_disp[opt_no],back_colour,text_colour);
		}
		Font_Select(ARIAL_12);
		TFT_String((9+110+20+90),INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
		(uint8_t*)Target_unit_disp[opt_no],back_colour,text_colour);


	}
}
/**
**************************************************************************
  Function Name : uint8_t VTBI_check(uint8_t v_mode)
  Description   : In this function to check the Maximum limit and to calculate third parameter.
  Input         : void
  Output        : Error flag
*******************************************************************************
*/
uint8_t VTBI_check(uint8_t v_mode)
{
uint8_t err_flag=0;
uint16_t syr_limit[7]={0,1800,3500,5000,9000,12000,12000};

	if(v_mode==1)
	{
		MOT.flowrate=flowrate_cal(MOT.time,MOT.volume);
//		 Font_Select(ARIAL_14);
//	     TFT_Number(60,70,MOT.flowrate,YELLOW,RED);
		if(MOT.flowrate>syr_limit[sy_size])
		{
			MOT.flowrate=syr_limit[sy_size];
		}
	    //err_flag=1;
	  //   TFT_Number(60,110,MOT.flowrate,YELLOW,RED);

	}
	else if(v_mode==2)
	{
		MOT.volume= volume_cal(MOT.time ,MOT.flowrate);
		if(MOT.volume>100000) err_flag=1;
	}

	else
	{

		MOT.time=time_cal(MOT.flowrate,MOT.volume);
		if(MOT.time>9959)
		{
			MOT.time=9959;
			err_flag=1;
		}
	}

	return err_flag;
	}
/**
**************************************************************************
  Function Name : uint32_t flowrate(uint16_t time_value , uint32_t volume_value)
  Description   :	to calculate flowrate
  Input         : target time & volume
  Output        : Flowrate
  Note          :
*******************************************************************************
*/

uint32_t flowrate_cal(uint32_t time_value , uint32_t volume_value)
{
	uint32_t result=0;
	float factor_1,factor_2;
	factor_1 = volume_value * 60L;
	factor_2 = ((time_value / 100) * 60 + time_value % 100);
	result = ceil(factor_1 / factor_2 );
	return result;
}

/**
**************************************************************************
  Function Name : uint16_t timecal(uint32_t flowrate_value , uint32_t volume_value)
  Description   :	to calculate target volume
  Input         : flowrate & volume
  Output        : target time
  Note          :
*******************************************************************************
*/

uint32_t time_cal(uint32_t flowrate_value , uint32_t volume_value)
{
	uint32_t result=0,factor_3=0;
	float factor_1,factor_2;

	factor_1 = volume_value*60;
	factor_2 =	flowrate_value;
	factor_3 = ceil(factor_1 / factor_2);
	factor_1 = ceil(factor_3 / 60);
	factor_2 = ceil(factor_3 % 60);
	result =(factor_1 * 100)+factor_2;
	return result;
}

/**
**************************************************************************
  Function Name : uint32_t volume(uint16_t time_value , uint32_t flowrate_value)
  Description   :	to calculate target volume

  Input         : target time & flowrate
  Output        : target volume
  Note          :
*******************************************************************************
*/

uint32_t volume_cal(uint32_t time_value , uint32_t flowrate_value)
{
	uint32_t result=0,factor_3=0;
	float factor_1,factor_2;

	factor_3 = ((time_value / 100) * 60 + time_value % 100);
	factor_1 = flowrate_value * factor_3;
	factor_2 = 60;
	result = ceil(factor_1 / factor_2 );
	return result;

}

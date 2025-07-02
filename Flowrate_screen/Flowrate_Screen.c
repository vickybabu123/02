#include "LPC55S16.h"
#include "Color.h"
#include "Keypad.h"
#include "TFT_String.h"
#include "TFT_Commands.h"
#include "Shapes.h"
#include "Flowrate_Screen.h"
#include "Power_off.h"
#include "FR_CALC.h"
//#include "Dynamic_Pressure.h"
#include "Dosage_mode.h"
#include "Driver_Timer.h"
#include "Bolus_Header.h"
#include "Alarm.h"
#include "Motor.h"
#include "SD_Calib.h"
#include "sound.h"
#include "STEPPER.h"
#include <Boot_up.h>
#include "Linear_Header.h"

uint8_t condition=1;
//uint8_t add_flag=0;
//uint8_t position_1=0;
uint8_t array_dig1[5];
//extern uint8_t power_flag;
//uint16_t con_value=0;
uint32_t G_con_value=0;
uint16_t xpos=0;
uint8_t G_fr_wrn_flag;
uint8_t G_fr_wrn_flag_1;
uint8_t G_power_edit=0;
uint8_t G_Fr_sound_flag=0;
uint8_t G_footer_edit_flag=0;

extern uint8_t disc;
extern uint8_t release;
typedef struct
{
    char* headerText;
    char* headerText_1;
    char* footerText;
} ScreenConfig;

extern uint8_t auto_lock_time;//common_bug  //ZOOZ_1

extern uint32_t G_KVO_fr;
extern uint8_t G_opt_no;
extern uint8_t G_page_no;
extern uint8_t weight_opt_no;
extern uint8_t w_unit;
extern uint8_t drug_no;
//extern uint8_t G_infusion_modes;
extern char dose_rate_unit[3][13];
extern uint8_t dose_option_no;
extern char* disp_para[20];
extern float time_value[4];
extern  char* drug_unit[4][4];
extern volatile uint8_t normal_run;
extern uint8_t VTBI_check(uint8_t v_mode);
extern void dynamic_pressure(uint8_t pressure,uint8_t screen);
extern uint8_t ON_Flag;
//extern uint8_t G_infusion_mode_opt;
extern uint8_t D_xpos;
extern uint8_t DF_xpos;//24-04
uint8_t Prev_DF_xpos=0;
extern void Notification(uint8_t notif);
extern uint8_t Bol_fr_flag;
extern uint16_t press_run_alarm;
extern void plunger_based_o_ml_max_ml_calculate();
extern float syringe_nearempty_calculation(uint16_t flowarte);
extern void event_no_update(uint8_t event_no);
extern uint8_t G_pre_sy_size_1[1];
extern void syringe_disp_status(uint8_t screen);
extern uint8_t G_pre_sy_size_1[1];
extern uint8_t sy_size;
extern uint8_t Bolus_rate_flag;
extern uint16_t Pump_idle;
extern uint8_t G_infusion_modes;
extern uint8_t G_mode_switch_flag;
extern uint8_t home_flag;
extern uint8_t siphonic_time;

void Screen_frame(ScreenConfig* screen,uint32_t conValue)
{
	//if(conValue)
	{
    Frame_Header(NEW_HDR_COL, HDR_TXT_COL, (uint8_t*)screen->headerText);
    Font_Select(ARIAL_12);
    TFT_String(260, 44, (uint8_t*)screen->headerText_1, MAIN_FRAME_COL, WHITE);
    Frame_Footer(NEW_FTR_COL, HDR_TXT_COL, (uint8_t*)screen->footerText, (uint8_t*)"OK", 1,14);
	}
	//else
	{
		//Frame_Footer(RED, YELLOW, (uint8_t*)"    Invalid FR", (uint8_t*)"", 0);
	}
}

void Footer_datas(uint32_t conValue, uint8_t screen, uint8_t* frFlag)
{
    if (screen == 1 && conValue == 0 && *frFlag)
    {
        *frFlag = 0;
        Frame_Footer(RED, YELLOW, (uint8_t*)"    Invalid Volume", (uint8_t*)"", 0,14);
    } else if (screen != 1 && conValue == 0 && *frFlag)
    {
        *frFlag = 0;
        Frame_Footer(RED, YELLOW, (uint8_t*)"    Invalid FR", (uint8_t*)"", 0,14);
    } else if ((conValue >= 1) && (conValue <=12000) && *frFlag != 1)
    {
        *frFlag = 1;
        Frame_Footer(NEW_FTR_COL, HDR_TXT_COL, (uint8_t*)"        to confirm", (uint8_t*)"OK", 1,14);
    }
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void FR_split_frame()
{
	 uint8_t loop_count=0;
	 uint8_t loop=0;
	// CLRSCR(MAIN_FRAME_COL);

	 for(loop_count=0;loop_count<=4;loop_count++)
		 {
		     Rectangle(40+(45*loop_count),68,0,115,BLACK);
	     }
	 for(loop=4;loop<=5;loop++)
	 {
		Rectangle(40+(45*loop)+15,68,0,115,BLACK);
	 }
	  Font_Select(CALIBRI_35);
	  TFT_String(221+5,100+10,(uint8_t*)".",MAIN_FRAME_COL,WHITE);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Digit_Spiliting(uint32_t Value)
 {
	char letter[2]={'\0','\0'} ;
	uint8_t space=0;
	uint8_t loop_count=0;
	uint8_t position_1=0;
	position_1=0;

    letter[0]='0';

    if(Value==0)
    {
    	for(loop_count=0;loop_count<5;loop_count++)
    	{
    		array_dig1[position_1]=0;
    		position_1++;
    	}
    }

    else
    {
	 while(Value>0)
	     {
			 array_dig1[position_1]=Value%10;
			 Value=Value/10;
			 position_1++;
	     }
    }

	for(loop_count=0;loop_count<position_1;loop_count++)
     {
//		if(loop_count==0)
//		{
//			space=15;
//		}
//		else
//		{
//			space=0;
//		}

		 Font_Select(CALIBRI_43);
		 letter[0] =	 array_dig1[loop_count]+48;
		 xpos=Letters_Alignments(40+(45*(4-loop_count)),
    		  	  	40+(45*(5-loop_count)), (uint8_t*)letter,0);

//   Font_Select(CALIBRI_43);
	if(loop_count>0)  		//REW1
	{
		TFT_Number(xpos,CALIB_EDT_YPOS,array_dig1[loop_count],MAIN_FRAME_COL,WHITE);
	}
   }
	letter[0] =	 0+48;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void flowrate_option_frame(uint8_t current_cur_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL)
{
	char letter[2]={'\0','\0'} ;
	uint32_t back_colour   = 0;
	uint32_t text_colour   = 0;
	uint8_t   loop		   = 0;
	uint8_t Cursor_no	   = 0;
	uint8_t space		   = 0;
	uint32_t arrow_bg_color	= 0;
	uint32_t arrow_fill_color =  0;
	uint32_t con_value=0;
	uint8_t position_1=0;
	uint8_t fr_pos=0;
	con_value=array_dig1[4]*10000+array_dig1[3]*1000+array_dig1[2]*100+array_dig1[1]*10+array_dig1[0]*1;

	while(con_value>0)
	{
		array_dig1[position_1]=con_value%10;
		con_value=con_value/10;
		position_1++;
	}
	if(position_1 < 2)
	{
		position_1=2;
	}
	if(current_cur_no >= position_1)
	{
		fr_pos=current_cur_no;
	}
	else
	{
		fr_pos=position_1-1;
	}


	for(loop = 0; loop<1; loop++)
	 {
		if(loop!=current_cur_no)
		{
			back_colour		 = MAIN_FRAME_COL;
			text_colour 	 = WHITE;
		//	Cursor_no		 = prev_cursor_no;
			arrow_bg_color	 = MAIN_FRAME_COL;
			arrow_fill_color = MAIN_FRAME_COL;
		}
		else
		{
			back_colour 		= LIGHT_GRAY;
			text_colour  		= BLACK;
		//	Cursor_no			= current_cur_no;
			arrow_bg_color	    = LIGHT_GRAY;
			arrow_fill_color	= BLACK;
		}

	 if(loop==0)
	 {
		space=15;
	 }
	 else
	 {
		space=0;
	 }
		TFT_ST7789V__rectangle_curve(40+1+(45*(4-loop)+space),64,125,43,0,back_colour);
		Font_Select(CALIBRI_43);
		letter[0]=array_dig1[loop]+48;
		xpos=Letters_Alignments(40+(45*(4-loop))+space,
														  85+(45*(4-loop))+space, (uint8_t*)letter,0);
		TFT_Number(xpos,CALIB_EDT_YPOS,array_dig1[loop],back_colour,text_colour);

		TFT_ST7789V_up_down_arrow_20_arial(79,55+(45*(4-loop))+space,0,arrow_bg_color,arrow_fill_color);  		//UP_ARROW
		TFT_ST7789V_up_down_arrow_20_arial(166,55+(45*(4-loop))+space, 1,arrow_bg_color,arrow_fill_color)	;	//DOWN_ARROW
	 }
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void flowrate_option_scroll(uint8_t current_cur_no,uint8_t prev_cursor_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL,uint32_t UP_ARROW_ERASE)
{
	char letter[2]={'\0','\0'} ;
	uint32_t back_colour   = 0;
	uint32_t text_colour   = 0;
	uint8_t   loop		   = 0;
	uint8_t Cursor_no	   = 0;
	uint8_t space		   = 0;
	uint32_t arrow_bg_color	= 0;
	uint32_t arrow_fill_color =  0;

	for(loop = 0; loop<2; loop++)
	{
	 		if(!loop)
	 		{
	 			back_colour		 = MAIN_FRAME_COL;
	 			text_colour 	 = WHITE;
	 			Cursor_no		 = prev_cursor_no;
                arrow_bg_color	 = MAIN_FRAME_COL;
                arrow_fill_color = MAIN_FRAME_COL;
	 		}
	 		else
	 		{
	 			back_colour 		= LIGHT_GRAY;
	 			text_colour  		= BLACK;
	 			Cursor_no			= current_cur_no;
	 			arrow_bg_color	    = LIGHT_GRAY;
				arrow_fill_color	= BLACK;
	 		}

		if(Cursor_no==0)
		{
			space=15;
		}
		else
		{
			space=0;
		}

			TFT_ST7789V__rectangle_curve(40+1+(45*(4-Cursor_no)+space),64,125,43,0,back_colour);
			Font_Select(CALIBRI_43);

			letter[0]=array_dig1[Cursor_no]+48;
			xpos=Letters_Alignments(40+(45*(4-Cursor_no))+space,
												  85+(45*(4-Cursor_no))+space, (uint8_t*)letter,0);
			TFT_Number(xpos,CALIB_EDT_YPOS,array_dig1[Cursor_no],back_colour,text_colour);
			TFT_ST7789V_up_down_arrow_20_arial(79,40+15+(45*(4-Cursor_no)+space),0,arrow_bg_color,arrow_fill_color);  		//UP_ARROW
			TFT_ST7789V_up_down_arrow_20_arial(166,40+15+(45*(4-Cursor_no)+space), 1,arrow_bg_color,arrow_fill_color)	;

	 	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint32_t Flow_rate_screen(uint32_t *flow_rate ,uint8_t Min_Limit,uint32_t Max_Limit,uint8_t screen)
{
	 char letter[2]={'\0','\0'} ;
	 uint16_t syr_limit[7]={0,1800,3500,5000,9000,12000,12000};
     uint8_t Cursor_no=1;
     uint8_t prev_cursor_no=0;
     uint8_t space=0;
     uint8_t loop_count=0;
     uint8_t check_flag=1;
     uint32_t con_value=0;
     uint8_t condition=1;
     uint8_t Err_flag=0;
     uint8_t fr_flag=0;


     uint32_t P_value=*flow_rate;      //That poiter variable store to the local var

     auto_lock_time=AUTO_EXIT_TIME;

     ScreenConfig screens[] =
         	 {
                {"Volume", "mL", "        Confirm"},
                {"Rate", "ml/hr", "        Confirm"},
                {"Bolus Rate", "mL/hr", "        Start"},
				{"Rate","ml/hr", "        Start Infusion"}
         	 };

     con_value=P_value;
     Pump_idle=10;
	 fr_flag=1;
	 G_power_edit=1;
	 G_Fr_sound_flag=1;
	 G_footer_edit_flag=1;
	 home_flag=0;
	 POW.power_status_flag=1;
	 memset(array_dig1, 0, sizeof(array_dig1));
	 prev_cursor_no=1;
//	if(P_value)
//	{
//		press_run_alarm=10;
//	}


     while(KEY.value);
     while(condition)
     {

     Power_off();

    if(!ON_Flag)
	{
		break;//26-03
	}

	else if(POW.power_status_flag)
	{

		POW.power_status_flag=0;//26-03
	    CLRSCR(MAIN_FRAME_COL);

		Screen_frame(&screens[screen - 1],con_value);//, con_value ? 1 : 0);
		Left_Right_Indi(Cursor_no,1);
		FR_split_frame();
		Digit_Spiliting(P_value);
		flowrate_option_frame(Cursor_no,CURSOR_COL,BLACK);
		flowrate_option_scroll(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
		fr_flag=1;

	}
    	if(RAMP.up_flag) //25-03
    	{
    		RAMP_UP(_MILLISEC,RAMP_RPM,RAMP.RPM_control);
    	}
    	else if(RAMP.down_flag)
    	{
    		RAMP_DOWN(_MILLISEC,RAMP_DOWN_RPM);
    	}

//		Font_Select(ARIAL_14);
//
//		TFT_Number(40,130,LIN_POT.syr_end_flag,YELLOW,RED);
//
//		TFT_Number(40,170,normal_run,YELLOW,RED);

	   plunger_alarm_check();
    // syringe_position_check();  //REW_UP

        if((release) && (normal_run))
		{
			Alarm(PLUNGER);
		}
		else if((disc) && (normal_run))
		{
			Alarm(NOT_ENGAGE);
		}
		if((LIN_POT.syr_end_flag==1) && (normal_run) )
		{
			Alarm(SYR_END);
		}
    if(normal_run==1)
    {
    	syringe_disp_status(0);
    }

    sy_size=detect_syringe_size(1);//REW_UP

	if(screen==2)
	{
		Max_Limit=syr_limit[sy_size];
	}

//	 Font_Select(ARIAL_14);
//	 TFT_Number(50,70,con_value,YELLOW,RED);
//	 TFT_Number(50,90,fr_flag,YELLOW,RED);
//	 TFT_Number(50,110,Bol_fr_flag,YELLOW,RED);


	if(((con_value==0) && (fr_flag==1))  && (!Bol_fr_flag) )
	{
   		fr_flag=0;
		Frame_Footer(RED,YELLOW,(uint8_t*)"    FR under range",(uint8_t*)"",0,14);
	}

	if(((con_value>=1) && (con_value<12000)) && (fr_flag!=1)  )
	{
		fr_flag=1;
		Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to confirm",(uint8_t*)"OK",1,14);
	}



	switch(KEY.value)
	{
	 case LEFT_KEY:

		 if(Cursor_no<4)
	  {
	    beep_sound();
		Cursor_no++;
		flowrate_option_scroll(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
		if(Cursor_no !=2 && Cursor_no !=3 )
		{
			Left_Right_Indi(Cursor_no,1);
		}
	  }
		 prev_cursor_no=Cursor_no;
		 while(KEY.value);
		 break;

	 case RIGHT_KEY:

		if(Cursor_no>0)
	   {
		 beep_sound();
		 Cursor_no--;
		 flowrate_option_scroll(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
		 if(Cursor_no !=1 && Cursor_no !=2 )
		 {
			Left_Right_Indi(Cursor_no,1);
		 }
	   }
		prev_cursor_no=Cursor_no;
		while(KEY.value);
		break;

		 case UP_KEY:

			if(array_dig1[Cursor_no]<9)
			{
				beep_sound();
				if(Cursor_no==0)
				{
					space=15;
				}

				else
				{
					space=0;
				}

				Font_Select(CALIBRI_43);
				letter[0]=array_dig1[Cursor_no]+48;

				xpos=Letters_Alignments(40+(45*(4-Cursor_no))+space,
				85+(45*(4-Cursor_no))+space, (uint8_t*)letter,0);
				TFT_Number(xpos,CALIB_EDT_YPOS,array_dig1[Cursor_no],CURSOR_COL,CURSOR_COL);

				if(sy_size!=0)
				{
					array_dig1[Cursor_no]++;
				}
				con_value=array_dig1[4]*10000+array_dig1[3]*1000+array_dig1[2]*100+array_dig1[1]*10+array_dig1[0]*1;
				G_con_value=con_value;
			  // Font_Select(ARIAL_14);
			  //TFT_Number(0,110,con_value,YELLOW,RED);

				if((array_dig1[4]*10000+array_dig1[3]*1000+array_dig1[2]*100+array_dig1[1]*10+array_dig1[0]*1)>Max_Limit)
				{

					array_dig1[Cursor_no]--;
					WARN_SOUND(1,1,2);
				}


				letter[0]=array_dig1[Cursor_no]+48;

				xpos=Letters_Alignments(40+(45*(4-Cursor_no))+space,
				85+(45*(4-Cursor_no))+space, (uint8_t*)letter,0);
				TFT_Number(xpos,CALIB_EDT_YPOS,array_dig1[Cursor_no],CURSOR_COL,BLACK);

			}

			else
			{
					WARN_SOUND(1,1,2);
			}

			 while(KEY.value);
			 break;

         	 case DOWN_KEY:

         		 if(array_dig1[Cursor_no]>0)
         		 {
         			 beep_sound();

         			 if(Cursor_no==0)
         			 {
         				 space=15;
         			 }
         			 else
         			 {
         				 space=0;
         			 }

					letter[0]=array_dig1[Cursor_no]+48;
					Font_Select(CALIBRI_43);
					xpos=Letters_Alignments(40+(45*(4-Cursor_no))+space,
					85+(45*(4-Cursor_no))+space, (uint8_t*)letter,0);
					TFT_Number(xpos,CALIB_EDT_YPOS,array_dig1[Cursor_no],CURSOR_COL,CURSOR_COL);
					array_dig1[Cursor_no]--;

//					Font_Select(ARIAL_14);
//					TFT_Number(60,70,Cursor_no,YELLOW,RED);

//					if((array_dig1[4]*10000+array_dig1[3]*1000+array_dig1[2]*100+array_dig1[1]*10+array_dig1[0]*1))//<Max_Limit)
//					{
//						array_dig1[Cursor_no]--;
//					}
					//array_dig1[Cursor_no]--;

					con_value=array_dig1[4]*10000+array_dig1[3]*1000+array_dig1[2]*100+array_dig1[1]*10+array_dig1[0]*1;
					//TFT_Number(60,150,con_value,YELLOW,RED);

				    G_con_value=con_value;

				 // Font_Select(ARIAL_14);
				 // TFT_Number(0,70,con_value,YELLOW,RED);

//				    if((array_dig1[4]*10000+array_dig1[3]*1000+array_dig1[2]*100+array_dig1[1]*10+array_dig1[0]*1)>Min_Limit)
//					{
//						array_dig1[Cursor_no]++;
//					}
					//TFT_Number(60,90,array_dig1[Cursor_no],YELLOW,RED);

					letter[0]=array_dig1[Cursor_no]+48;
					xpos=Letters_Alignments(40+(45*(4-Cursor_no))+space,
					85+(45*(4-Cursor_no))+space, (uint8_t*)letter,0);
					TFT_Number(xpos,CALIB_EDT_YPOS,array_dig1[Cursor_no],CURSOR_COL,BLACK);


					 if((con_value==0) && (fr_flag==1)  && (!Bol_fr_flag) )
					 {

						 fr_flag=0;
						 Frame_Footer(RED,YELLOW,(uint8_t*)"    FR under range",(uint8_t*)"",0,14);

					 }

					 if(((con_value>1) && (con_value<12000)) && (fr_flag!=1)  )
					 {

						 fr_flag=1;
						 Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to confirm",(uint8_t*)"OK",1,14);

					 }


         		 }

         		 else
         		 {
						WARN_SOUND(1,1,2);
         		 }
     			 while(KEY.value);
     			 break;

         	 case OK_KEY:

			  beep_sound();
			  con_value=array_dig1[4]*10000+array_dig1[3]*1000+array_dig1[2]*100+array_dig1[1]*10+array_dig1[0]*1;
			  G_con_value=con_value;
		//    press_run_alarm=10;
			  check_flag=1;

				if(!Err_flag)
				{
					if (normal_run==0)
					 {
						 *flow_rate=con_value;

						 if(!Bol_fr_flag)// || (Bolus_rate_flag))
						 {
						  *flow_rate=con_value;
						   check_flag=1;
						   condition=0;
						 }
						   else if((Bol_fr_flag) && (con_value))
						   {
							   *flow_rate=con_value;
							   check_flag=1;
							   condition=0;


						   }
						 }

					 if((normal_run==1) &&  (con_value==0))
					 {
							WARN_SOUND(3,1,3);
						   //*flow_rate=con_value;
					 }

					  else
					  {
						  if(normal_run==1)
						  {
							 *flow_rate=con_value;
							  check_flag=1;
							  condition=0;
						  }
					  }

				}

//				   check_flag=1;
//				   condition=0;
			while(KEY.value);
			break;

			case BACK_KEY:

		 	beep_sound();
			check_flag=0;
			siphonic_time=30;
			condition=0;

			while(KEY.value);
			break;

			case START_STOP_KEY:
				con_value=array_dig1[4]*10000+array_dig1[3]*1000+array_dig1[2]*100+array_dig1[1]*10+array_dig1[0]*1;
				G_con_value=con_value;
				*flow_rate=con_value;


				if(!G_infusion_modes)
				{
					if(normal_run==0)
					{
						if(MOT.flowrate!=0)
						{
							normal_run=1;
						//	press_run_alarm=10;
						//	Warning_Scr_Erase();
					//		plunger_based_o_ml_max_ml_calculate();
							syringe_nearempty_calculation(MOT.flowrate);
						//	event_no_update(3);
							BOL.run_mode=0;
							MFB.Motor_pulse=0;
							RAMP.RPM_control=0;    //ZOOZ_1
							DRV8428_ENABLE();
							stepper_Forward();
							MR_Value_calculate(MOT.flowrate);
							condition=0;
							if(disc)           //REW_UP(start/stop case)
							{
						      Alarm(NOT_ENGAGE);
							}
						}
					}

				else
				{
					normal_run=0;
					BOL.run_mode=0;
			//		event_no_update(4);
					Timer_disable();
					RAMP.down_flag=0;
					condition=0;
				}
//					Font_Select(ARIAL_14);
//					TFT_Number(0,100,normal_run,GREEN,RED);
				}
         	}
     }
     return check_flag;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void FR_split_frame_DD()
{
	 uint8_t loop_count=0;
	 uint8_t loop_count1=0;

	 for(loop_count=0;loop_count<=3;loop_count++)
	 {
	    Rectangle(40+(45*loop_count),68,0,115,BLACK);
	 }

	    Rectangle(40+(45*3)+15,68,0,115,BLACK);
	    Rectangle(40+(45*4)+15,68,0,115,BLACK);
	 	Rectangle(40+(45*5)+15,68,0,115,BLACK);
	 	Font_Select(CALIBRI_35);
	    TFT_String(221-41,123,(uint8_t*)".",MAIN_FRAME_COL,WHITE);

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Digit_Spiliting_DD(uint32_t Value)
{
	char letter[2]={'\0','\0'} ;
	uint8_t space=0;
	uint8_t loop_count=0;
	uint8_t position_1=0;
	if(Value==0)
	{
		for(loop_count=0;loop_count<5;loop_count++)
		{
			array_dig1[position_1]=0;
			position_1++;
		}
	}

	else
	{
		while(Value>0)
		{
			array_dig1[position_1]=Value%10;
			Value=Value/10;
			position_1++;
		}
	}

	for(loop_count=0;loop_count<position_1;loop_count++)
	{
		if(loop_count==0 || loop_count==1)
		{
			space=15;
		}
		else
		{
			space=0;
		}

		Font_Select(CALIBRI_43);

		letter[0] =	 array_dig1[loop_count]+48;

		xpos=Letters_Alignments(40+(45*(4-loop_count))+space,
		85+(45*(4-loop_count))+space, (uint8_t*)letter,0);

		Font_Select(CALIBRI_43);
		if(loop_count !=1 && loop_count !=2 )
		{
			TFT_Number(xpos,CALIB_EDT_YPOS,array_dig1[loop_count],MAIN_FRAME_COL,WHITE);
		}
	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void flowrate_option_frame_DD(uint8_t current_cur_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL)
	{
	char letter[2]={'\0','\0'} ;
	uint32_t back_colour   = 0;
	uint32_t text_colour   = 0;
	uint8_t   loop		   = 0;
	uint8_t Cursor_no	   = 0;
	uint8_t space		   = 0;
	uint32_t arrow_bg_color	= 0;
	uint32_t arrow_fill_color =  0;
	uint32_t con_value=0;
	uint8_t position_1=0;
	uint8_t fr_pos=0;
	con_value=array_dig1[4]*10000+array_dig1[3]*1000+array_dig1[2]*100+array_dig1[1]*10+array_dig1[0]*1;

	while(con_value>0)
		     {
		     array_dig1[position_1]=con_value%10;
		     con_value=con_value/10;
		     position_1++;
		     }
	if(position_1 < 3)
	{
		position_1=3;
	}
	if(current_cur_no >= position_1)
	{
		fr_pos=current_cur_no;
	}
	else
	{
		fr_pos=position_1-1;
	}
	for(loop = 0; loop<=fr_pos; loop++)
	 	{
	 		if(loop!=current_cur_no)
	 		{
	 			back_colour		 = MAIN_FRAME_COL;
	 			text_colour 	 = WHITE;
	 		//	Cursor_no		 = prev_cursor_no;
                arrow_bg_color	 = MAIN_FRAME_COL;
                arrow_fill_color = MAIN_FRAME_COL;
	 		}
	 		else
	 		{
	 			back_colour 		= LIGHT_GRAY;
	 			text_colour  		= BLACK;
	 			Cursor_no			= current_cur_no;
	 			arrow_bg_color	    = LIGHT_GRAY;
				arrow_fill_color	= BLACK;
	 		}

 if(loop==0 || loop==1)
 {
	space=15;
 }
 else
 {
	space=0;
 }
    TFT_ST7789V__rectangle_curve(40+1+(45*(4-loop)+space),64,125,43,0,back_colour);

 	Font_Select(CALIBRI_43);
 	letter[0]=array_dig1[loop]+48;
 	xpos=Letters_Alignments(40+(45*(4-loop))+space, 85+(45*(4-loop))+space, (uint8_t*)letter,0);

 	TFT_Number(xpos,CALIB_EDT_YPOS,array_dig1[loop],back_colour,text_colour);
 	if(loop==current_cur_no)
 	{
		TFT_ST7789V_up_down_arrow_20_arial(79,52+(45*(4-Cursor_no))+space,0,arrow_bg_color,arrow_fill_color);  		//UP_ARROW
		TFT_ST7789V_up_down_arrow_20_arial(166,52+(45*(4-Cursor_no))+space, 1,arrow_bg_color,arrow_fill_color)	;	//DOWN_ARROW
 	}
	}
	}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void flowrate_option_scroll_DD(uint8_t current_cur_no,uint8_t prev_cursor_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL,uint32_t UP_ARROW_ERASE)
{
	char letter[2]={'\0','\0'} ;
	uint32_t back_colour   = 0;
	uint32_t text_colour   = 0;
	uint8_t   loop		   = 0;
	uint8_t Cursor_no	   = 0;
	uint8_t space		   = 0;
	uint32_t arrow_bg_color	= 0;
	uint32_t arrow_fill_color =  0;

	for(loop = 0; loop<2; loop++)
	{
		if(!loop)
		{
			back_colour		 = MAIN_FRAME_COL;
			text_colour 	 = WHITE;
			Cursor_no		 = prev_cursor_no;
			arrow_bg_color	 = MAIN_FRAME_COL;
			arrow_fill_color = MAIN_FRAME_COL;
		}
		else
		{
			back_colour 		= LIGHT_GRAY;
			text_colour  		= BLACK;
			Cursor_no			= current_cur_no;
			arrow_bg_color	    = LIGHT_GRAY;
			arrow_fill_color	= BLACK;
		}

		if(Cursor_no==0 ||  Cursor_no==1 )
		{
			space=15;
		}


		else
		{
			space=0;
		}

		letter[0]=array_dig1[Cursor_no]+48;
		TFT_ST7789V__rectangle_curve(40+1+(45*(4-Cursor_no))+space,64,125,43,0,back_colour);
		Font_Select(CALIBRI_43);

		xpos=Letters_Alignments(40+(45*(4-Cursor_no))+space,
		85+(45*(4-Cursor_no))+space, (uint8_t*)letter,0);

		TFT_Number(xpos,CALIB_EDT_YPOS,array_dig1[Cursor_no],back_colour,text_colour);
		TFT_ST7789V_up_down_arrow_20_arial(79,52+(45*(4-Cursor_no))+space,0,arrow_bg_color,arrow_fill_color);  		//UP_ARROW
		TFT_ST7789V_up_down_arrow_20_arial(166,52+(45*(4-Cursor_no))+space, 1,arrow_bg_color,arrow_fill_color)	;	//DOWN_ARROW
	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint16_t Double_Decimal_FR_screen(uint32_t *flow_rate, uint32_t Limit ,uint8_t mode)
{
	char letter[2]={'\0','\0'} ;
	uint8_t Cursor_no=2;
	uint8_t prev_cursor_no=1;
	uint8_t space=0;
	uint8_t loop_count=0;
	uint16_t con_value=0;
	uint8_t check_flag=1;
	uint8_t edit_flag=0;
	uint8_t condition=1;
	uint16_t P_value=*flow_rate;      //That poiter variable store to the local var

	G_power_edit=1;

//	Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to Confirm",(uint8_t*)"OK",1,14);
	Font_Select(ARIAL_12);
	if(mode==1)
	{

		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Rate");
		Font_Select(ARIAL_12);
		TFT_String(250,44,(uint8_t*)"ml/h",MAIN_FRAME_COL,WHITE);

	}
	else if(mode==2)
	{

		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Patient  Weight");
		Font_Select(ARIAL_12);
		TFT_String(280,40,(uint8_t*)"kg",MAIN_FRAME_COL,WHITE);

	}
	else if(mode==3)
	{

		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Dose Concentration");
		Font_Select(ARIAL_12);
		Rectangle(260,38,60,22,LIGHT_GRAY);
		TFT_String(265,38,(uint8_t*)drug_unit[G_page_no][G_opt_no],LIGHT_GRAY,BLACK);

	}
	else if(mode==4)
	{

		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Dose Concentration");
		Rectangle(285,38,30,20,LIGHT_GRAY);
		Font_Select(ARIAL_12);
		TFT_String(290,38,(uint8_t*)"ml",LIGHT_GRAY,BLACK);
		TFT_String(10,38,(uint8_t*)"Conc :",MAIN_FRAME_COL,WHITE);
		TFT_String(60,38,(uint8_t*)" = ",MAIN_FRAME_COL,WHITE);

	}
	else if(mode==5)
	{

		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Drug Dosage");
		Font_Select(ARIAL_12);
		Rectangle(203,38,117,25,LIGHT_GRAY);
		TFT_String(210,40,(uint8_t*)dose_rate_unit[dose_option_no],LIGHT_GRAY,BLACK);
		TFT_String(10,38,(uint8_t*)"=",MAIN_FRAME_COL,WHITE);
		Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to Confirm",(uint8_t*)"OK",1,14);
	}

	Left_Right_Indi(Cursor_no,1);

	for(loop_count=0;loop_count<5;loop_count++)
	{
		array_dig1[loop_count]=0;
	}

	FR_split_frame_DD();
	Digit_Spiliting_DD(P_value);
	flowrate_option_scroll_DD(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
	prev_cursor_no=2;
	edit_flag=1;
	while(KEY.value);

	while(condition)
	{


		Power_off();

	    if(!ON_Flag)
		{
			break;		//01-04
		}

		else if(POW.power_status_flag)
		{

			home_flag=0;
			POW.power_status_flag=0;		//01-04
			//Rectangle(0,0,320,240,MAIN_FRAME_COL);
			CLRSCR(MAIN_FRAME_COL);
				Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to Confirm",(uint8_t*)"OK",1,14);	//29-03
			//	Font_Select(ARIAL_12);

				if(mode==1)
				{
					Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Rate");
			//		Font_Select(ARIAL_12);
					TFT_String(250,44,(uint8_t*)"ml/h",MAIN_FRAME_COL,WHITE);
				}

				else if(mode==2)
				{
					Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Patient  Weight");
			//		Font_Select(ARIAL_12);
					TFT_String(280,40,(uint8_t*)"kg",MAIN_FRAME_COL,WHITE);

				}

				else if(mode==3)
				{

					Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Dose Concentration");
			//		Font_Select(ARIAL_12);
					Rectangle(260,38,60,22,LIGHT_GRAY);
					TFT_String(265,38,(uint8_t*)drug_unit[G_page_no][G_opt_no],LIGHT_GRAY,BLACK);

				}

				else if(mode==4)
				{

					Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Dose Concentration");
					Rectangle(285,38,30,20,LIGHT_GRAY);
			//		Font_Select(ARIAL_12);
					TFT_String(290,38,(uint8_t*)"ml",LIGHT_GRAY,BLACK);
					TFT_String(10,38,(uint8_t*)"Conc :",MAIN_FRAME_COL,WHITE);
					TFT_String(60,38,(uint8_t*)" = ",MAIN_FRAME_COL,WHITE);
					dosage_range_limit_fun(mode,con_value);
					Rectangle(80+D_xpos,37,88+20+20+10,25,MAIN_FRAME_COL);
				    TFT_String(80+D_xpos+35,38,(uint8_t*)disp_para,MAIN_FRAME_COL,WHITE);

				}

				else if(mode==5)
				{

					Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Drug Dosage");
					Font_Select(ARIAL_12);
					Rectangle(203,38,117,25,LIGHT_GRAY);
					TFT_String(10,38,(uint8_t*)"=",MAIN_FRAME_COL,WHITE);
					TFT_String(210,40,(uint8_t*)dose_rate_unit[dose_option_no],LIGHT_GRAY,BLACK);
					Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to Confirm",(uint8_t*)"OK",1,14);
					dosage_range_limit_fun(mode,con_value);
					Font_Select(ARIAL_12);

					if(!Prev_DF_xpos)
					{
						TFT_String(80+Prev_DF_xpos+10,38,(uint8_t*)"ml/h",MAIN_FRAME_COL,MAIN_FRAME_COL);
						TFT_String(80+DF_xpos,38,(uint8_t*)"ml/h",MAIN_FRAME_COL,WHITE);
						Prev_DF_xpos=DF_xpos;
					}

					else
					{
						TFT_String(80+Prev_DF_xpos,38,(uint8_t*)"ml/h",MAIN_FRAME_COL,MAIN_FRAME_COL);
						TFT_String(80+DF_xpos,38,(uint8_t*)"ml/h",MAIN_FRAME_COL,WHITE);
						Prev_DF_xpos=DF_xpos;
					}

				}

			FR_split_frame_DD();
			flowrate_option_frame_DD(Cursor_no,CURSOR_COL,BLACK);
			Left_Right_Indi(Cursor_no,0);

		}

	    if(((mode==2)||(mode==4) || (mode==5))  && (edit_flag==1))
		{

    	con_value=array_dig1[4]*10000+array_dig1[3]*1000+array_dig1[2]*100+array_dig1[1]*10+array_dig1[0]*1;
		dosage_range_limit_fun(mode,con_value);

		if(mode==4)
		{
			Rectangle(80+D_xpos,37,88+20+20+10,25,MAIN_FRAME_COL);
			TFT_String(80+D_xpos+35,38,(uint8_t*)disp_para,MAIN_FRAME_COL,WHITE);
		}

		else if(mode==5)
		{

			Font_Select(ARIAL_12);
			if(!Prev_DF_xpos)
			{
				TFT_String(80+Prev_DF_xpos+10,38,(uint8_t*)"ml/h",MAIN_FRAME_COL,MAIN_FRAME_COL);
				TFT_String(80+DF_xpos,38,(uint8_t*)"ml/h",MAIN_FRAME_COL,WHITE);
				Prev_DF_xpos=DF_xpos;
			}

			else
			{
				TFT_String(80+Prev_DF_xpos,38,(uint8_t*)"ml/h",MAIN_FRAME_COL,MAIN_FRAME_COL);
				TFT_String(80+DF_xpos,38,(uint8_t*)"ml/h",MAIN_FRAME_COL,WHITE);
				Prev_DF_xpos=DF_xpos;
			}

		}
		edit_flag=0;
		}

		if(normal_run==1)
		{
			syringe_disp_status(0);
		}
		plunger_alarm_check();

		if((release) && (normal_run))
		{
			Alarm(PLUNGER);
		}
		else if((disc) && (normal_run))
		{
			Alarm(NOT_ENGAGE);
		}
		if((LIN_POT.syr_end_flag==1) && (normal_run))
		{
			Alarm(SYR_END);
		}


		switch(KEY.value)
		{
			case LEFT_KEY:
			beep_sound();
			if(Cursor_no<4)
			{
				Cursor_no++;
				flowrate_option_scroll_DD(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
				if(Cursor_no !=2 && Cursor_no !=3 )
				{
					Left_Right_Indi(Cursor_no,1);
				}
			}
			prev_cursor_no=Cursor_no;
			while(KEY.value);
			break;

			case RIGHT_KEY:
			beep_sound();
			if(Cursor_no>0)
			{
				Cursor_no--;
				flowrate_option_scroll_DD(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
				if(Cursor_no !=1 && Cursor_no !=2 )
				{
					Left_Right_Indi(Cursor_no,1);
				}
			}
			prev_cursor_no=Cursor_no;
			while(KEY.value);
			break;

			case UP_KEY:
			beep_sound();
			edit_flag=1;
			if(array_dig1[Cursor_no]<9)
			{

				if(Cursor_no==0 || Cursor_no==1)
				{
					space=15;
				}

				else
				{
					space=0;
				}
				letter[0]=array_dig1[Cursor_no]+48;

				Font_Select(CALIBRI_43);
				xpos=Letters_Alignments(40+(45*(4-Cursor_no))+space,
				85+(45*(4-Cursor_no))+space, (uint8_t*)letter,0);
				TFT_Number(xpos,CALIB_EDT_YPOS,array_dig1[Cursor_no],CURSOR_COL,CURSOR_COL);

				array_dig1[Cursor_no]++;
				if((array_dig1[4]*10000+array_dig1[3]*1000+array_dig1[2]*100+array_dig1[1]*10+array_dig1[0]*1)>Limit)
				{
					array_dig1[Cursor_no]--;
				}

					letter[0]=array_dig1[Cursor_no]+48;

				//	Font_Select(CALIBRI_43);
					xpos=Letters_Alignments(40+(45*(4-Cursor_no))+space,
					85+(45*(4-Cursor_no))+space, (uint8_t*)letter,0);
					TFT_Number(xpos,CALIB_EDT_YPOS,array_dig1[Cursor_no],CURSOR_COL,BLACK);

			}

			 else
			 {
					WARN_SOUND(1,1,2);
			 }

			while(KEY.value);
			break;

			case DOWN_KEY:

			beep_sound();
			edit_flag=1;
			if(array_dig1[Cursor_no]>0)
			{

				if(Cursor_no==0 || Cursor_no==1)
				{
					space=15;
				}

				else
				{
					space=0;
				}

				letter[0]=array_dig1[Cursor_no]+48;
				Font_Select(CALIBRI_43);
				xpos=Letters_Alignments(40+(45*(4-Cursor_no))+space,85+(45*(4-Cursor_no))+space, (uint8_t*)letter,0);
				TFT_Number(xpos,CALIB_EDT_YPOS,array_dig1[Cursor_no],CURSOR_COL,CURSOR_COL);

				array_dig1[Cursor_no]--;
				letter[0]=array_dig1[Cursor_no]+48;

			//	Font_Select(CALIBRI_43);
				xpos=Letters_Alignments(40+(45*(4-Cursor_no))+space,85+(45*(4-Cursor_no))+space, (uint8_t*)letter,0);
				TFT_Number(xpos,CALIB_EDT_YPOS,array_dig1[Cursor_no],CURSOR_COL,BLACK);

			}

			 else
			 {
					WARN_SOUND(1,1,2);
			 }
			while(KEY.value);
			break;

			case OK_KEY:

			beep_sound();
			if(((mode==5) && ((dose.flow_rate<=120000)&& (dose.flow_rate>10))) || ((mode!=5)))			//(dose.flow_rate>0.0) )
			{

			con_value=array_dig1[4]*10000+array_dig1[3]*1000+array_dig1[2]*100+array_dig1[1]*10+array_dig1[0]*1;
//			Font_Select(ARIAL_12);
//			TFT_Number(0,70,con_value,YELLOW,RED);
//		\\	delay_secs(5);
			*flow_rate=con_value;
			check_flag=1;
			condition=0;

			}

			else
			{
				WARN_SOUND(3,1,5);
			}
			while(KEY.value);
			break;

			case BACK_KEY:

			beep_sound();
			dosage_range_limit_fun(mode,P_value);
			condition=0;
			siphonic_time=30;
			check_flag=0;

			while(KEY.value);
			break;

		}
	}
	return check_flag;;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Left_Right_Indi(uint8_t cursor_pos,uint8_t screen_id)
{
	uint32_t Right_bg_color;
	uint32_t left_bg_color;
	uint8_t cursor_no=0;

    if(screen_id==1)
    {
    	cursor_no=4;
    }
    else
    {
    	cursor_no=3;
    }

	if(cursor_pos==0 )
	{
     Right_bg_color		= LIGHT_GRAY_3;
     left_bg_color		= WHITE;
	}

	else if(cursor_pos==cursor_no)
	{
	 Right_bg_color		= WHITE;
     left_bg_color		= LIGHT_GRAY_3;
	}

	else
	{
	Right_bg_color		= WHITE;
	left_bg_color		= WHITE;
	}

    TFT_ST7789V_lcd_drawcircle1(20,120,12,left_bg_color,left_bg_color);           						//	 Left Circle
    TFT_ST7789V_lcd_drawcircle1(300,120,12,Right_bg_color,Right_bg_color);   			//23-03					// Right Circle

    TFT_ST7789V_left_Right_arrow_14_arial(120-7,20-5,0,left_bg_color,NEON_BLUE_1);      //	Left Arrow
    TFT_ST7789V_left_Right_arrow_14_arial(120-7,303-5,1,Right_bg_color,NEON_BLUE_1);  	//	Right Arrow

}


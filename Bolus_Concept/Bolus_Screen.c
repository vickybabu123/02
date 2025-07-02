/*
 * bolus_screen.c
 *
 *  Created on: Nov 25, 2023
 *      Author: Welcome
 */
//#include <STEPPER.h>
#include <infused_calculate.h>
#include "LPC55S16.h"
#include "Color.h"
#include "TFT_Commands.h"
#include "TFT_String.h"
#include"Keypad.h"
#include"Shapes.h"
#include "Bolus_Header.h"
#include "Driver_Timer.h"
#include "FR_CALC.h"
//#include "Flowrate_Screen.h"
#include "Motor.h"
#include "Power_off.h"
//#include  "sound.h"
//#include "Occlusion.h"
#include "Alarm.h"
//#include "Linear_Header.h"
#include <Boot_up.h>
#include <Occlusion.h>
#include <Linear_Header.h>
const char* bol_set[1][2]={{0,"Volume"}};
uint8_t Bol_fr_flag=0;
uint8_t G_Auto_Bolus_flag=0;

uint32_t G_bol_vol=1;

extern uint8_t G_run_count;
extern uint8_t  longpress;
extern uint8_t run_stop_flag;
extern volatile uint8_t normal_run;
extern uint8_t G_sound_level;
extern uint8_t ON_Flag;
extern uint8_t end_flag;
extern uint8_t disc;
extern uint8_t sy_size;
extern uint8_t G_Bolus_target_flag;
extern uint8_t G_Bolus_warning_flag;
extern uint8_t G_alarm_ok_flag;
extern uint16_t press_run_alarm;
extern uint8_t disc;
extern uint8_t release;
extern uint8_t G_footer_edit_flag;

extern uint16_t G_bol_fr;
extern uint16_t G_bol_fr;
extern uint16_t first_lmt[7];
extern uint16_t second_lmt[1];
extern uint8_t pre_flowrate;
extern uint16_t Pump_idle;
extern uint8_t G_footer_edit_flag;

extern void plunger_alarm_check();
extern void syringe_disp_status(uint8_t screen);
extern uint8_t detect_syringe_size(unsigned int sybrand);
extern void Running_symbol(uint8_t X_start, uint8_t Y_start,uint32_t col);

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void pop_up_info_frame(uint8_t screen, uint32_t color)//common_bug  //ZOOZ_1
{
	uint16_t XPOS=0;
	TFT_ST7789V__rectangle_curve(20,75,105,280,0,color);//70//80//120
	Font_Select(ARIAL_14);
	if(!screen)
	{
//		XPOS=Letters_Alignments(20,20+280,(uint8_t *)"Purge Bolus",0);
//		TFT_String(XPOS,90,(uint8_t *)"Purge Bolus",color,BLACK);
		TFT_String_align(20,300,90,(uint8_t *)"Purge Bolus",0,color,BLACK);

//		XPOS=Letters_Alignments(20,20+280,(uint8_t *)"Completed",0);
//		TFT_String(XPOS,140,(uint8_t *)"Completed",color,BLACK);
		TFT_String_align(20,300,140,(uint8_t *)"Completed",0,color,BLACK);
	}

	else if(screen==1)
	{
		Font_Select(ARIAL_12);
//		XPOS=Letters_Alignments(0,319,(uint8_t *)"EEPROM Fail",0);
//		TFT_String(XPOS,120,(uint8_t *)"EEPROM Fail",color,BLACK);
		TFT_String_align(0,319,120,(uint8_t *)"EEPROM Fail",0,color,BLACK);
		//TFT_String(100,140,(uint8_t *)"Shutting Down ... ",WHITE,BLACK);
		delay_secs(1);

	}

	else if(screen==2)
	{
//		XPOS=Letters_Alignments(20,20+280,(uint8_t *)"Passcode Invalid",0);
//	    TFT_String(XPOS,120,(uint8_t *)"Passcode Invalid",color,BLACK);
		TFT_String_align(20,300,120,(uint8_t *)"Passcode Invalid",0,color,BLACK);
	}

	else if(screen==3)
	{
//		XPOS=Letters_Alignments(20,20+280,(uint8_t *)"Auto Bolus",0);
//		TFT_String(XPOS,90,(uint8_t *)"Auto Bolus",color,BLACK);
		TFT_String_align(20,300,90,(uint8_t *)"Auto Bolus",0,color,BLACK);

//		XPOS=Letters_Alignments(20,20+280,(uint8_t *)"Completed",0);
//		TFT_String(XPOS,140,(uint8_t *)"Completed",color,BLACK);
		TFT_String_align(20,300,140,(uint8_t *)"Completed",0,color,BLACK);

	//  delay_secs(1);
		WARN_SOUND(2,1,2);
	}

	else if(screen==4)
	{
//	 	XPOS=Letters_Alignments(20,20+280,(uint8_t *)"Keypad Fail",0);
//	 	TFT_String(XPOS,120,(uint8_t *)"Keypad Fail",color,BLACK);
		TFT_String_align(20,300,120,(uint8_t *)"Keypad Fail",0,color,BLACK);
		delay_secs(1);
	}

	else if(screen==5)
	{

//	  	XPOS=Letters_Alignments(20,20+280,(uint8_t *)"Auto Bolus",0);
//	  	TFT_String(XPOS,90,(uint8_t *)"Auto Bolus",color,BLACK);
		TFT_String_align(20,300,90,(uint8_t *)"Auto Bolus",0,color,BLACK);

//	  	XPOS=Letters_Alignments(20,20+280,(uint8_t *)"Interrupted",0);
//	  	TFT_String(XPOS,140,(uint8_t *)"Interrupted",color,BLACK);
		TFT_String_align(20,300,140,(uint8_t *)"Interrupted",0,color,BLACK);

	}
	else if(screen==6)
		{

			TFT_String_align(20,300,120,(uint8_t *)"No Battery",0,color,BLACK);
			delay_secs(1);
		}

	delay_secs(1);

}
//}//common_bug

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void bolus_frame()
{
	Font_Select(ARIAL_14);
	TFT_writenumber_float_1d(170,213,BOL.flowrate,NEW_FTR_COL,BLACK);//195//common_bug
	TFT_String(245,212,(uint8_t*)"mL/h",NEW_FTR_COL,BLACK);//260
	TFT_writenumber_float_1d(180,INITIAL_TEXT_POS+(1*VER_TEXT_SPACE)-5,G_bol_vol,LIGHT_GRAY,BLACK);
//	Font_Select(ARIAL_14);
	TFT_String(220,INITIAL_TEXT_POS+(1*VER_TEXT_SPACE)-5,(uint8_t*)"mL",LIGHT_GRAY,BLACK);//common_bug
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void bolus_fun(void)
{
	uint8_t exit_flag=1;
	uint8_t check_flag=0;
//	uint8_t status=0;
	uint32_t syr_max=0;

	G_footer_edit_flag=0;
	POW.power_status_flag=1;
	BOL.run_mode=0;
	Bol_fr_flag=1;

	while(exit_flag)
	{
		syringe_disp_status(0);
		plunger_alarm_check();
		syringe_position_check();

		sy_size=detect_syringe_size(1);
		syr_max=Bolus_Limit_syringe(sy_size);

		Occlusion_Status();

//		if(G_alarm_ok_flag)
//		{
//			POW.power_status_flag=0;
//			G_alarm_ok_flag=0;
//			break;
//		}



		Power_off();

		if(!ON_Flag)
		{
			break;//26-03
		}

		else if(POW.power_status_flag)  //ZOOZ_1
		{
			POW.power_status_flag=0;
			check_flag=Flow_rate_screen(&G_bol_vol,0,syr_max,1);
			BOL.run_mode=0;
			Bol_fr_flag=0;
			while(KEY.value);//28-03
		}
		if(release)
		{
			Alarm(PLUNGER);
			break;
		}
		else if(!disc)
		{
			Alarm(NOT_ENGAGE);
			break;
		}
		if(LIN_POT.syr_end_flag==1 )
		{
			Alarm(SYR_END);
			break;
		}

//		Font_Select(ARIAL_14);
//		TFT_Number(10,70,check_flag,YELLOW,RED);
//		TFT_Number(10,90,BOL.run_mode,YELLOW,WHITE);

		if(check_flag)
		{
			if(!BOL.run_mode)
			{
					Rectangle(5,38,320,170,MAIN_FRAME_COL);
					bolus(BOL.mode);
					bolus_run_frame();
//					Font_Select(ARIAL_14);
//				    TFT_Number(1000,70,G_Bolus_warning_flag,YELLOW,RED);
					bolus_FR_spliting(BOL.infused_ml,WHITE);
			}
		}

		else
		{
			exit_flag=0;
			break;
		}

		if(RAMP.up_flag)
		{
			RAMP_UP(_MILLISEC,RAMP_RPM,RAMP.RPM_control);  //ZOOZ_1
		}
		else if(RAMP.down_flag)
		{
			RAMP_DOWN(_MILLISEC,RAMP_RPM);//ZOOZ_1
		}

//		if((MOT.flowrate>BOL.flowrate) && (!G_Auto_Bolus_flag) )
//		   {
//				Frame_Footer_warning(WARNING_COLOR,BLACK,(uint8_t*)"Less Bolus FR",(uint8_t*)"",0);
//				G_Auto_Bolus_flag=1;
//		   }

		if(BOL.run_mode)
		{

			bolus_fr_screen( BOL.infused_ml);
		// 	Running_symbol(56,3,MAIN_FRAME_COL);
			ADC_to_PSI_conversion();
			Occlusion_Status();


		     	if(BOL.infused_ml >= G_bol_vol)
				 {
					   MOT.flowrate=BOL.temp_flowrate;
					   BOL.run_mode=0;
					   exit_flag=0;
					   Timer_disable();
				//	   Rectangle(0,0,320,240,MAIN_FRAME_COL);		//21-03-2024
					   CLRSCR(MAIN_FRAME_COL);
					   pop_up_info_frame(3, WHITE);//common_bug  //ZOOZ_1
					   G_Bolus_target_flag=1;
					   delay_secs(2);

						   if(normal_run==1)
							{
							  bolus_to_normal_run();
							  exit_flag=0;
							}
				 }
							}

		switch(KEY.value)
		{

		case BOLUS_KEY:

		pop_up_info_frame(5,ORANGE);
		beep_sound();
	   if(normal_run==1)
		{
		   bolus_to_normal_run();
		   //exit_flag=0;
		}
		else
		{
		  Timer_disable();
		}
		   G_Bolus_target_flag=1;
		   BOL.run_mode=0;
		   press_run_alarm=180;
		   Pump_idle=10;
		   exit_flag=0;

		while(KEY.value);
		break;

		case START_STOP_KEY:

		   pop_up_info_frame(5,ORANGE);
		   beep_sound();
		   if(normal_run==1)
			{
			   bolus_to_normal_run();
			  //exit_flag=0;
			}
			else
			{
			  Timer_disable();
			}
			   BOL.run_mode=0;
			   G_Bolus_target_flag=1;
			   press_run_alarm=180;
			   Pump_idle=10;
			   exit_flag=0;

		while(KEY.value);
		break;

		}
	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

 void bolus_fr_screen(uint16_t flowrate )
 {

	 static uint16_t prev_value=0;

	if(prev_value!=flowrate)
	{
		bolus_FR_spliting(prev_value,MAIN_FRAME_COL);
		bolus_FR_spliting(flowrate,WHITE);
		prev_value=flowrate;
	}

 }

 /****************************************************************************
 * Function Name :
 * Arguments     :
 * Return type   :
 * Description   :

 *****************************************************************************/

void bolus_run_frame(void)
{
	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Delivering Bolus");
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Stop Bolus",(uint8_t*)"",0,14);
	TFT_ST7789V_lcd_drawcircle1(70,223,16,MAIN_FRAME_COL,MAIN_FRAME_COL);
	Font_Select(ARIAL_9);
	TFT_String(56,218,(uint8_t*)"BOL",MAIN_FRAME_COL,WHITE);
	Rectangle(7,34+(43*3),290,0, BLACK);
	Font_Select(ARIAL_14);
	TFT_String(18,56+(2*VER_TEXT_SPACE)-5,(uint8_t*)"Bolus Volume",MAIN_FRAME_COL,WHITE);
	TFT_String(270,56+(2*VER_TEXT_SPACE)-5,(uint8_t*)"mL",MAIN_FRAME_COL,WHITE);
	TFT_String(18,56+(3*VER_TEXT_SPACE)-5,(uint8_t*)"Bolus Rate",MAIN_FRAME_COL,WHITE);
	TFT_String(150,56+(3*VER_TEXT_SPACE)-5,(uint8_t*)":",MAIN_FRAME_COL,WHITE);
	//Font_Select(ARIAL_14);
	TFT_writenumber_float_1d(180,56+(3*VER_TEXT_SPACE)-5,BOL.flowrate,MAIN_FRAME_COL,WHITE);
	TFT_String(255,56+(3*VER_TEXT_SPACE)-5,(uint8_t*)"mL/h",MAIN_FRAME_COL,WHITE);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void purge_frame(void)
{

	Rectangle(0,35,320,170,MAIN_FRAME_COL);
	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Delivering Bolus");
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to Stop",(uint8_t*)"BK",1,14);
	Rectangle(7,34+(43*3),290,0, BLACK);
	Font_Select(ARIAL_14);
	TFT_String(18,56+(2*VER_TEXT_SPACE)-5,(uint8_t*)"Bolus",MAIN_FRAME_COL,WHITE);
	TFT_String(270,56+(2*VER_TEXT_SPACE)-5,(uint8_t*)"mL",MAIN_FRAME_COL,WHITE);
	TFT_String(18,56+(3*VER_TEXT_SPACE)-5,(uint8_t*)"Bolus Rate",MAIN_FRAME_COL,WHITE);
	TFT_String(150,56+(3*VER_TEXT_SPACE)-5,(uint8_t*)":",MAIN_FRAME_COL,WHITE);
	//Font_Select(ARIAL_14);
	TFT_writenumber_float_1d(180,56+(3*VER_TEXT_SPACE)-5,BOL.flowrate,MAIN_FRAME_COL,WHITE);
	TFT_String(255,56+(3*VER_TEXT_SPACE)-5,(uint8_t*)"mL/h",MAIN_FRAME_COL,WHITE);

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void purge_bolus(void)
{
	G_footer_edit_flag=0;
	pre_flowrate=10;
	purge_frame();
	bolus_FR_spliting(BOL.infused_ml,WHITE);
	bolus(BOL.mode);

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void bolus_layout(void)
{

	//Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);

	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Bolus");    // to create header

	Rectangle(0,206,320,34,NEW_FTR_COL);
	TFT_String(65,212,(uint8_t*)"Bolus rate :",NEW_FTR_COL,BLACK);

	TFT_ST7789V__rectangle_curve(10,68,(41*2)+1+20,300,0,LIGHT_GRAY);
	Rectangle(15,120,285,0, BLACK);
	TFT_ST7789V_lcd_drawcircle1(30,56+(1*VER_TEXT_SPACE)-3,16,MAIN_FRAME_COL,MAIN_FRAME_COL);
	TFT_ST7789V_lcd_drawcircle1(30,56+(1*VER_TEXT_SPACE)-3,14,LIGHT_GRAY,LIGHT_GRAY);

	Font_Select(ARIAL_9);
	TFT_String(22,56+6+(1*VER_TEXT_SPACE)-13,(uint8_t*)"OK",LIGHT_GRAY,MAIN_FRAME_COL);
	TFT_ST7789V_lcd_drawcircle1(30,56+(2*VER_TEXT_SPACE)+5,17,MAIN_FRAME_COL,MAIN_FRAME_COL);
	TFT_String(15,56+(2*VER_TEXT_SPACE),(uint8_t*)"BOL",MAIN_FRAME_COL,WHITE);

	Font_Select(ARIAL_14);
	TFT_String(55,INITIAL_TEXT_POS+(1*VER_TEXT_SPACE)-5,(uint8_t*)"Volume",LIGHT_GRAY,BLACK);
	TFT_String(150,INITIAL_TEXT_POS+(1*VER_TEXT_SPACE)-5,(uint8_t*)":",LIGHT_GRAY,BLACK);

	TFT_String(55,INITIAL_TEXT_POS+(2*VER_TEXT_SPACE)+5,(uint8_t*)"Run",LIGHT_GRAY,BLACK);
}


/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void bolus_frame_Option(uint8_t page,uint8_t starting_count,uint8_t ending_count)
{
	uint32_t back_colour = 0;
	uint32_t text_colour = 0;
	uint8_t loop_count=0;

	for(loop_count=1;loop_count<=3;loop_count++)
	{
		if(loop_count == starting_count)//0==0
		{
			back_colour	= LIGHT_GRAY;
			text_colour = BLACK;
			TFT_ST7789V__rectangle_curve(3,35+(43*(starting_count)),41,290,0,back_colour); //0
		}
		else
		{
			back_colour	= MAIN_FRAME_COL;
			text_colour = WHITE;
		}

		Font_Select(ARIAL_14);
		TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
				(uint8_t*)bol_set[page][loop_count],back_colour,text_colour);

	}


}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void bolus_popup_frame()
{
		Rectangle(5,39,320,170,MAIN_FRAME_COL);
		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Do you want exit?");    // to create header

		Rectangle(0,206,320,34,NEW_FTR_COL);
		Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Bolus rate  :",(uint8_t*)"",0,14);

		TFT_ST7789V__rectangle_curve(10,68,(41*2)+1+20,300,0,LIGHT_GRAY);
		Rectangle(15,120,285,0, BLACK);
		TFT_ST7789V_lcd_drawcircle1(30,56+(1*VER_TEXT_SPACE)-3,18,MAIN_FRAME_COL,MAIN_FRAME_COL);
		TFT_ST7789V_lcd_drawcircle1(30,56+(1*VER_TEXT_SPACE)-3,16,LIGHT_GRAY,LIGHT_GRAY);

		Font_Select(ARIAL_9);
		TFT_String(22,56+6+(1*VER_TEXT_SPACE)-13,(uint8_t*)"OK",LIGHT_GRAY,MAIN_FRAME_COL);
		TFT_ST7789V_lcd_drawcircle1(30,56+(2*VER_TEXT_SPACE)+5,18,MAIN_FRAME_COL,MAIN_FRAME_COL);
		TFT_String(18,56+(2*VER_TEXT_SPACE),(uint8_t*)"BAK",MAIN_FRAME_COL,WHITE);

		Font_Select(ARIAL_14);
		TFT_String(55,INITIAL_TEXT_POS+(1*VER_TEXT_SPACE)-5,(uint8_t*)"To Stop",LIGHT_GRAY,BLACK);
		TFT_String(55,INITIAL_TEXT_POS+(2*VER_TEXT_SPACE)+5,(uint8_t*)"To Continue",LIGHT_GRAY,BLACK);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t bolus_popup(void)
{
	uint8_t check_flag=0;
	uint8_t exit_flag=1;

	bolus_popup_frame();
	while(exit_flag)
	{
		switch(KEY.value)
		{
		case OK_KEY:

		beep_sound();  //ZOOZ_1
		bolus_mode_stop();
	//  auto_bolus_stop();
		check_flag=0;
		exit_flag=0;

		while(KEY.value);
		break;

		case BACK_KEY:

			beep_sound();  //ZOOZ_1
			check_flag=1;
			exit_flag=0;

			while(KEY.value);
			break;

		}

	}

	return  check_flag;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void bolus_FR_spliting(uint16_t flowrate,uint32_t color)
{

	uint16_t xpos=0;
	char BR_buffer[6];
	uint16_t flowrate_view = 0;
	uint16_t flowrate_decimal=0;

	Font_Select(CALIBRI_43);
	flowrate_view = flowrate/10;//400
	flowrate_decimal =flowrate%10;

//	Font_Select(ARIAL_14);
//	TFT_Number(26,110,flowrate_view,NAVY,WHITE);
//
//	Font_Select(ARIAL_14);
//  TFT_Number(52,110,flowrate_decimal,NAVY,WHITE);


	sprintf(BR_buffer,"%d",flowrate_view);
	xpos=Flow_rate_Alignments((uint8_t*)BR_buffer);


//    if(flowrate_view < first_lmt[sy_size])
//    {
		Font_Select(CALIBRI_43);
		TFT_Number(xpos,50+7,flowrate_view,MAIN_FRAME_COL,color);
  //  }

//    else
//    {
//    	if(!flowrate_view)
//    	{
//    		Font_Select(CALIBRI_43);
//    		TFT_Number(xpos,50+7,flowrate_view,MAIN_FRAME_COL,color);
//    	}
//
//    	else
//    	{
//    		break;
//    	}
//    }
	//Font_Select(CALIBRI_48);

	TFT_String(256,50+7,(uint8_t *)".",MAIN_FRAME_COL,color);

//    if(flowrate_decimal<second_lmt[sy_size])
//    {
//		Font_Select(CALIBRI_35);
//		TFT_Number(269,60,flowrate_decimal,MAIN_FRAME_COL,color);
//    }
//    else
//    {
//		if(second_lmt[sy_size] == 0)
//		{
//			//break;
//		}
//		else
//		{
			Font_Select(CALIBRI_35);
			TFT_Number(269,60,flowrate_decimal,MAIN_FRAME_COL,color);
	//	}
   // }
 }

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint16_t Bolus_Limit_syringe(uint8_t size)
{
	uint16_t syr_max_limit=0;
	if(size==1)
	{
		syr_max_limit=20;
	}
	else if(size==2)
	{
		syr_max_limit=50;
	}
	else if(size==3)
	{
		syr_max_limit=100;
	}
	else if(size==4)
	{
		syr_max_limit=200;
	}
	else if(size==5)
	{
		syr_max_limit=300;
	}
	else if(size==6)
	{
		syr_max_limit=500;
	}
	return syr_max_limit;
}

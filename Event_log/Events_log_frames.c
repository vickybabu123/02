/*
 * Events_log_frames.c
 *
 *  Created on: 09-Mar-2024
 *      Author: SoftwareRND
 */
#include "LPC55S16.h"
#include "Color.h"
#include "Keypad.h"
#include "TFT_String.h"
#include "TFT_Commands.h"
#include "Shapes.h"
#include "Power_off.h"
#include "Driver_Timer.h"
#include "Events_log.h"
#include <string.h>
#include <Boot_up.h>

extern uint8_t G_ending_event;

char *event_alarm1[35]={
		 	 	 	 	 	 	 	 	 	 	 	    "No Alarm      ",//0
														"Device ON     ",//1
														"Device OFF    ",//2
														"Motor run     ",//3
														"Motor stop    ",//4
														"Occlusion     ",//5
														"Motor Error   ",//6
														"Plunger Distu.",//7
														"Syr load Err  ",//8
														"End of syringe",//9
														"Plunger not Eng"//10
														"Syringe not Eng"//11

//	                                                    "No Alarm      ",//0
//														"yes Alarm     ",//1
//														"Syr Distrbed  ",//2
//														"Tar Vol.Rech  ",//3
//														"Tar.TimeRech  ",//4
//														"Batt Low      ",//5
//														"Batt critical ",//6
//														"Syr End !     ",//7
//														"PCA Prb Unplg ",//8
//														"Occlusion !   ",//9
//														"Plung not eng ",//10
//                                                        "Inf.start     ",//11
//														"Inf.stop      ",//12
//														"Syr DisEng    ",//13
//														"FR Exceeds!   ",//14
//														"FR Exceeds!   ",//15
//														"FR is changed ",//16
//														"Occl Error!   ",//17
//														"FSR may Fail  ",//18
//														"FR is changed ",//19
//														"Motor reverse ",//20
//														"Motor undrive ",//21
//														"Machine Start ",//22
//														"Machine Stop  ",//23
//														"Syr distrub   ",//24
//														"calib error   ",//25
//														"charge IC fail",//26
//														"load cell fail",//27
//														"Syr.Load Err! ",//28
//														"Occl.lvlchang ",//29
//														"Occl.lvlchang ",//30
//														"Occl.lvlchang ",//31
//														"Occl.lvlchang " //32
								};

void events_option_scroll(uint8_t prev_option,uint8_t curr_option,uint8_t page,uint16_t array[20],
		uint16_t array1[20],uint16_t array2[20]);
void event_info_option_frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void events_split_screen(void);
void events_option_frame1(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void events_info_scroll(uint8_t prev_option,uint8_t curr_option,uint8_t page,uint16_t array[20],
		uint16_t array1[20],  char* array2[35]);
void events_option_frame1(uint8_t page,uint8_t start_opt,uint8_t end_opt);

extern uint16_t event_filter_day[20];
extern uint16_t event_filter_month[20];
extern uint16_t event_filter_year[20];
extern uint16_t event_info[10][10];
extern uint16_t array_hour[50];
extern uint16_t array_minute[50];
extern uint8_t starting_event;
extern uint16_t array_event_no[50];
extern uint16_t array_date[50];

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void events_split_screen(void)
{

	uint8_t menu_count = 0;
   //	Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
   	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Event   log");	// header

//	for(menu_count = 1; menu_count <=3 ; menu_count++)				//no of lines
//	{
//		Rectangle(7,34+(43*menu_count),290,0, BLACK);		// no of rect line
//	}
   	Rectangle_Line_function(1,3);

	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to enter",(uint8_t*)"OK",2,14);

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void split_screen_info(uint16_t count)
{
		uint8_t menu_count = 0;
		char event_buffer[20];
		//Rectangle(0,0,320,240,MAIN_FRAME_COL);
		CLRSCR(MAIN_FRAME_COL);
	   	for(menu_count = 1; menu_count <=3 ; menu_count++)		//no of lines
		{
			Rectangle(7,34+(43*menu_count),290,0, BLACK);		// no of rect line
		}

	    sprintf((char *)event_buffer,"Events  (%02d-%02d-%02d)",
		event_filter_day[count],
		event_filter_month[count],event_filter_year[count]);
	    Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)event_buffer);	// header
		Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to Exit",(uint8_t*)"BK",2,14);

}


/**************************************************************************
 *Function Name :void Main_Menu_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
 *Arguments     :uint8_t page,uint8_t start_opt,uint8_t end_opt
 *Return        :void
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

void events_option_frame1(uint8_t page,uint8_t start_opt,uint8_t end_opt)
{

    uint8_t loop_count=0;
    uint32_t back_colour=0;
    uint32_t text_colour=0;
    char event_buffer[20];
	for(loop_count=0;loop_count<=end_opt;loop_count++)
	{
		if(loop_count == start_opt)
		{
			back_colour	= LIGHT_GRAY;
			text_colour = BLACK;
			TFT_ST7789V__rectangle_curve(3,35+(43*(start_opt)),41,290,0,back_colour); //0
		}
		else
		{
			back_colour	= MAIN_FRAME_COL;
			text_colour = WHITE;
		}

		Font_Select(ARIAL_14);
		sprintf((char *)event_buffer,"%02d",event_filter_day[(page*4)+loop_count]);
		TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),(uint8_t*)event_buffer,back_colour,text_colour);
		TFT_String(42,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE)
				       				,(uint8_t*)"-",back_colour,text_colour);
        sprintf((char *)event_buffer,"%02d",event_filter_month[(page*4)+loop_count]);

		TFT_String(55,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),(uint8_t*)event_buffer,back_colour,text_colour);
		TFT_String(85,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE)
						       				,(uint8_t*)"-",back_colour,text_colour);
		TFT_Number(100,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),event_filter_year[(page*4)+loop_count],back_colour,text_colour);

	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void event_info_option_frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
{
	 	uint8_t loop_count=0;
	    uint32_t back_colour=0;
	    uint32_t text_colour=0;

		for(loop_count=0;loop_count<=end_opt;loop_count++)
		{
			if(loop_count == start_opt)
			{
				back_colour	= LIGHT_GRAY;
				text_colour = BLACK;
				TFT_ST7789V__rectangle_curve(3,35+(43*(start_opt)),41,290,0,back_colour); //0
			}
			else
			{
				back_colour	= MAIN_FRAME_COL;
				text_colour = WHITE;
			}

			Font_Select(ARIAL_14);

			TFT_Time_disp(15,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
			((array_hour[(G_ending_event+starting_event)-((page*4)+loop_count)]*100)+array_minute[starting_event+((page*4)+loop_count)]),back_colour,text_colour);    //25-03  for Time display

			TFT_String(105,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE)
									,(uint8_t*)event_alarm1[array_event_no[(G_ending_event+starting_event)-((page*4)+loop_count)]],back_colour,text_colour);
		}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void events_option_scroll(uint8_t prev_option,uint8_t curr_option,uint8_t page,uint16_t array[20],
		uint16_t array1[20],uint16_t array2[20])
 {
	uint32_t back_colour = 0;
    uint32_t text_colour = 0;
	uint8_t loop		 = 0;
	uint8_t opt_no		 = 0;
    char event_buffer[20];


	for(loop = 0; loop<2; loop++)
	{
		if(!loop)
		{
			back_colour     = MAIN_FRAME_COL;
			text_colour 	= WHITE;
			opt_no			= prev_option;
		}
		else
		{
			back_colour   = LIGHT_GRAY;
			text_colour   = BLACK;
			opt_no		  = curr_option;
    	}


	    TFT_ST7789V__rectangle_curve(3,35+(43*(opt_no)),41,290,0,back_colour);

	    Font_Select(ARIAL_14);
		sprintf((char *)event_buffer,"%02d",event_filter_day[(page*4)+opt_no]);
	    		TFT_String(9,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),(uint8_t*)event_buffer,back_colour,text_colour);
	    		TFT_String(42,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE)
	    				       				,(uint8_t*)"-",back_colour,text_colour);
        sprintf((char *)event_buffer,"%02d",event_filter_month[(page*4)+opt_no]);

	    		TFT_String(55,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),(uint8_t*)event_buffer,back_colour,text_colour);
	    		TFT_String(85,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE)
	    						       				,(uint8_t*)"-",back_colour,text_colour);
	    		TFT_Number(100,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),event_filter_year[(page*4)+opt_no],back_colour,text_colour);
	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void events_info_scroll(uint8_t prev_option,uint8_t curr_option,uint8_t page,uint16_t array[20],
							uint16_t array1[20], char* array2[35])
 {
	uint32_t back_colour = 0;
    uint32_t text_colour = 0;
	uint8_t loop		 = 0;
	uint8_t opt_no		 = 0;
//	char local_buffer[6];


	for(loop = 0; loop<2; loop++)
	{
		if(!loop)
		{
			back_colour     = MAIN_FRAME_COL;
			text_colour 	= WHITE;
			opt_no			= prev_option;
		}
		else
		{
			back_colour   = LIGHT_GRAY;
			text_colour   = BLACK;
			opt_no		  = curr_option;
    	}


	    TFT_ST7789V__rectangle_curve(3,35+(43*(opt_no)),41,290,0,back_colour);

	    Font_Select(ARIAL_14);
	    TFT_Time_disp(15,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
			((array_hour[(G_ending_event+starting_event)-((page*4)+opt_no)]*100)+array_minute[(G_ending_event+starting_event)-((page*4)+opt_no)]),back_colour,text_colour);    //25-03  for Time display

	    TFT_String(105,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
	    	   							(uint8_t*)event_alarm1[array_event_no[(G_ending_event+starting_event)-((page*4)+opt_no)]],back_colour,text_colour);


 }
}

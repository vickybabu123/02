/*
 * Dose_frame.c
 *
 *  Created on: Feb 16, 2024
 *      Author: Welcome
 */
#include "Color.h"
#include "keypad.h"
#include "Shapes.h"
#include "fsl_clock.h"
#include "Driver_I2C.h"
#include "TFT_Commands.h"
#include "TFT_String.h"
#include "shapes.h"
#include "Driver_Timer.h"
#include "Dosage_mode.h"
#include <Boot_up.h>

uint8_t drug_no;
uint8_t G_opt_no;
uint8_t G_page_no;
uint8_t drug_no;
uint8_t dose_option_no=0;
uint8_t G_dose_exit_flag;

uint16_t G_concen;           //calculated data

char disp_para[15];    //ZOOZ_1
char dose_rate_unit[3][13];

extern uint8_t current_option_1;
extern uint8_t drug_new_no;
extern uint16_t waitingtime ;
extern uint8_t current_option;
extern const char* dosage_view[4];
extern  char Drug_Names[150][4][20];
extern const char* drug_unit[4][4];


/**************************************************************************
 *Function Name :void Main_Menu_Frame(void)
 *Arguments     :void
 *Return        :void
 *Description	:In this function for Main frame
***************************************************************************/

void drug_unit_Frame(void)
{

	uint8_t menu_count = 0;
  //Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	Rectangle(0,0,320,34,NEW_HDR_COL);

	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Dose  Unit");	// header

	for(menu_count = 1; menu_count <=3 ; menu_count++)				//no of lines
	{
		Rectangle(7,34+(43*menu_count),290,0, BLACK);		// no of rect line
	}

	TFT_ST7789V_lcd_shapes(38+163,38,300+15,306,LIGHT_GRAY_3);  	//Scroll bar                                                                                           //SCROLLING BOX OUTSIDE LAYER
	TFT_ST7789V_lcd_shapes(40+57,40,303+12,306,BLACK);

	Rectangle(0,206,320,34,NEW_FTR_COL);
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to Confirm",(uint8_t*)"OK",1,14);
}

/**************************************************************************
 *Function Name :void Main_Menu_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
 *Arguments     :uint8_t page,uint8_t start_opt,uint8_t end_opt
 *Return        :void
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

void drug_unit_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
{

	uint8_t loop_count=0;
    uint32_t back_colour = 0;
    uint32_t text_colour = 0;

	for(loop_count=0;loop_count<=3;loop_count++)
	{
		if(loop_count == start_opt)//0==0
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
		TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),(uint8_t*)drug_unit[page][loop_count],back_colour,text_colour);
	}

}

/**************************************************************************
 *Function Name :void Menu_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[2][4])
 *Arguments     :uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[2][4]
 *Return        :void
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

void drug_unit_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page)//, const char* array[4][4])
{

	uint8_t loop = 0;
	uint8_t opt_no  = 0;
	uint32_t back_colour = 0;
	uint32_t text_colour = 0;

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


		if ((page<=2) || ((page==3) && (opt_no==0)))
			{
				TFT_ST7789V__rectangle_curve(3,35+(43*(opt_no)),41,290,0,back_colour);
			    Font_Select(ARIAL_14);
				TFT_String(9,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
				(uint8_t*)drug_unit[page][opt_no],back_colour,text_colour);
			}
	}
}


/**************************************************************************
 *Function Name :void Main_Menu_Frame(void)
 *Arguments     :void
 *Return        :void
 *Description	:In this function for Main frame
***************************************************************************/

void dose_unit_parameter_Frame(void)
{

	uint8_t menu_count = 0;
   //	Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	Rectangle(0,0,320,34,NEW_HDR_COL);

	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)" Select  Dose  Unit");	// header

	for(menu_count = 1; menu_count <=3 ; menu_count++)				//no of lines
	{
		Rectangle(7,34+(43*menu_count),290,0, BLACK);		// no of rect line
	}

	TFT_ST7789V_lcd_shapes(38+163,38,300+15,306,LIGHT_GRAY_3);  	//Scroll bar                                                                                           //SCROLLING BOX OUTSIDE LAYER
	TFT_ST7789V_lcd_shapes(40+57,40,303+12,306,BLACK);

	Rectangle(0,206,320,34,NEW_FTR_COL);
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to Confirm",(uint8_t*)"OK",1,14);

	TFT_ST7789V_lcd_drawcircle1(223,140,15,MAIN_FRAME_COL,MAIN_FRAME_COL);

}

/**************************************************************************
 *Function Name :void Main_Menu_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
 *Arguments     :uint8_t page,uint8_t start_opt,uint8_t end_opt
 *Return        :void
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

void dose_unit_parameter_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
{


    uint8_t loop_count=0;
    uint32_t back_colour = 0;
    uint32_t text_colour = 0;

	for(loop_count=0;loop_count<end_opt;loop_count++)  //ZOOZ_1
	{
		if(loop_count == start_opt)//0==0
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
		TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),(uint8_t*)dose_rate_unit[loop_count]
																			,back_colour,text_colour);

	}

}

/**************************************************************************
 *Function Name :void Menu_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[2][4])
 *Arguments     :uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[2][4]
 *Return        :void
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

void dose_unit_cursor(uint8_t prev_option, uint8_t curr_option,  char array[3][13])
{

	uint8_t loop = 0;
	static uint8_t opt_no  = 0;
	uint32_t back_colour = 0;
	uint32_t text_colour = 0;

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
			opt_no		= curr_option;
		}


			TFT_ST7789V__rectangle_curve(3,35+(43*(opt_no)),41,290,0,back_colour);

			Font_Select(ARIAL_14);
			TFT_String(9,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
			(uint8_t*)array[opt_no],back_colour,text_colour);


	}
}

/**************************************************************************
 *Function Name :void Main_Menu_Frame(void)
 *Arguments     :void
 *Return        :void
 *Description	:In this function for Main frame
***************************************************************************/

void dosage_overview_parameter_Frame(void)
{

	uint8_t menu_count = 0;
  //Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	Rectangle(0,0,320,34,NEW_HDR_COL);

	Font_Select(ARIAL_14);
	TFT_String(95,6,(uint8_t*)"Parameter",NEW_HDR_COL,HDR_TXT_COL);

	for(menu_count = 1; menu_count <=3 ; menu_count++)				//no of lines
	{
		Rectangle(7,34+(43*menu_count),290,0, BLACK);		// no of rect line
	}

	Rectangle(0,206,320,34,NEW_FTR_COL);
		Font_Select(ARIAL_12);
		TFT_String(10,213,(uint8_t*)"Rate",NEW_FTR_COL,HDR_TXT_COL);
		TFT_String(60,213,(uint8_t*)"=",NEW_FTR_COL,HDR_TXT_COL);

		if((dose.flow_rate>10 && dose.flow_rate<=120000))
		{
			TFT_writenumber_float(75,213,dose.flow_rate,NEW_FTR_COL,HDR_TXT_COL );
			TFT_String(170,213,(uint8_t*)"mL/Hr",NEW_FTR_COL,HDR_TXT_COL);
		}
		else
		{
			TFT_writenumber_float(75,213,dose.flow_rate,NEW_FTR_COL,RED );
			TFT_String(170,213,(uint8_t*)"mL/Hr",NEW_FTR_COL,RED);
		}
	//	Font_Select(ARIAL_12);
	//	TFT_String(170,213,(uint8_t*)"mL/Hr",NEW_FTR_COL,HDR_TXT_COL);


	//	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        Start Infusion",(uint8_t*)"ST",1);

		TFT_ST7789V_lcd_drawcircle1(250,223,15,MAIN_FRAME_COL,MAIN_FRAME_COL);
		Font_Select(ARIAL_9);
		TFT_String(243,218,(uint8_t*)"ST",MAIN_FRAME_COL,WHITE);
		Font_Select(ARIAL_12);
		TFT_String(278,213,(uint8_t*)"Run",NEW_FTR_COL,BLACK);
	//	TFT_ST7789V_lcd_drawcircle1(150,223,15,MAIN_FRAME_COL,MAIN_FRAME_COL);
	//	Font_Select(ARIAL_9);

	//	TFT_ST7789V_lcd_drawcircle1(223,210,14,MAIN_FRAME_COL,MAIN_FRAME_COL);
	//	TFT_String(200,210,(uint8_t*)"OK",MAIN_FRAME_COL,WHITE);
}

/**************************************************************************
 *Function Name :void Main_Menu_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
 *Arguments     :uint8_t page,uint8_t start_opt,uint8_t end_opt
 *Return        :void
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

void dosage_parameter_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
{


	uint8_t loop_count=0;
	uint16_t dose_data[4]={dose.drug_name,dose.conc_value,dose.pat_weight,dose.drug_dos};
	const char *drug_para[4] = {NULL, disp_para, "kg", dose_rate_unit[dose_option_no]}; // Units mapped by loop_count
	uint32_t back_colour = 0;
	uint32_t text_colour = 0;

	for(loop_count=0;loop_count<=3;loop_count++)  //local var
	{
		if(loop_count == start_opt)
		{
			back_colour	= LIGHT_GRAY;
			text_colour = BLACK;
			TFT_ST7789V__rectangle_curve(3,35+(43*(start_opt)),41,310,0,back_colour); //0
		}
		else
		{
			back_colour	= MAIN_FRAME_COL;
			text_colour = WHITE;
		}

	//	value = dose_data[loop_count];

		Font_Select(ARIAL_14);
		TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
		(uint8_t*)dosage_view[loop_count],back_colour,text_colour);

		TFT_String(80,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
		(uint8_t*)":",back_colour,text_colour);

		if(loop_count==0)
		{
			TFT_String(95,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
				(uint8_t*)Drug_Names[(dose.drug_select_no/4)][(dose.drug_select_no%4)],back_colour,text_colour);
		}
		else
		{
			Font_Select(ARIAL_14);
			TFT_writenumber_float(95,INITIAL_TEXT_POS+((loop_count)*VER_TEXT_SPACE),
				 dose_data[loop_count],back_colour,text_colour);
		}
		 if (drug_para[loop_count] != NULL)
		{
			Font_Select(ARIAL_12);
			TFT_String(176, INITIAL_TEXT_POS + (loop_count * VER_TEXT_SPACE),
				   (uint8_t *)drug_para[loop_count], back_colour, text_colour);
		}

//		switch(loop_count)
//		{
//
//		case 1:
//
//			Font_Select(ARIAL_12);
//			TFT_String(176,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
//										(uint8_t*)disp_para,back_colour,text_colour);
//
//			break;
//
//		case 2:
//			Font_Select(ARIAL_12);
//			TFT_String(176,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
//								(uint8_t*)"kg",back_colour,text_colour);
//			break;
//
//		case 3:
//			Font_Select(ARIAL_12);
//			TFT_String(176,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
//								(uint8_t*)dose_rate_unit[dose_option_no],back_colour,text_colour);
//			break;
//		}
	}

}

/**************************************************************************
 *Function Name :void Menu_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[2][4])
 *Arguments     :uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[2][4]
 *Return        :void
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

void dosage_overview_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[4])
{

	    uint8_t loop = 0;
		uint8_t opt_no  = 0;
		uint16_t dose_data[4]={dose.drug_name,dose.conc_value,dose.pat_weight,dose.drug_dos};
		uint32_t back_colour = 0;
		uint32_t text_colour = 0;

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
			TFT_ST7789V__rectangle_curve(3,35+(43*(opt_no)),41,310,0,back_colour);

			Font_Select(ARIAL_14);
			TFT_String(9,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
			(uint8_t*)array[opt_no],back_colour,text_colour);


			TFT_String(80,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
			(uint8_t*)":",back_colour,text_colour);

			if(opt_no==0)
			{
				TFT_String(95,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
									(uint8_t*)Drug_Names[(dose.drug_select_no/4)][(dose.drug_select_no%4)],back_colour,text_colour);
			}
//			else if(opt_no==2)
//			{
//				TFT_String(95,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
//													(uint8_t*)dose.pat_weight,back_colour,text_colour);
//			}
			else
			{

				TFT_writenumber_float(95,INITIAL_TEXT_POS+((opt_no)*VER_TEXT_SPACE),
								  			    dose_data[opt_no],back_colour,text_colour);
			}

			switch(opt_no)
				{

				case 1:
					Font_Select(ARIAL_12);
					TFT_String(176,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
							(uint8_t*)disp_para,back_colour,text_colour);

					break;

				case 2:
					Font_Select(ARIAL_12);
					TFT_String(176,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
										(uint8_t*)"kg",back_colour,text_colour);
					break;

				case 3:
					Font_Select(ARIAL_12);
					TFT_String(176,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
										(uint8_t*)dose_rate_unit[dose_option_no],back_colour,text_colour);
					break;
				}
		}
}

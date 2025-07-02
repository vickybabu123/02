/*
 * Rec_frame.c
 *
 *  Created on: Feb 16, 2024
 *      Author: Welcome
 */
#include "stdio.h"
#include "stdint.h"
#include "Color.h"
#include "keypad.h"
#include "Shapes.h"
#include "fsl_clock.h"
#include "Driver_I2C.h"
#include "TFT_Commands.h"
#include "TFT_String.h"
#include "shapes.h"
#include "Drug_List.h"
#include "Main_screen.h"
#include "Driver_Timer.h"
#include "Dosage_mode.h"
#include <Boot_up.h>

extern char recent_drug_list[5][4][20];
extern uint16_t drug_num[11];
extern  char Drug_Names[150][4][20];//29-03

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void recent_drug_Frame(void)
{
	uint8_t menu_count = 0;
	 //  	Rectangle(0,0,320,240,MAIN_FRAME_COL);
	    CLRSCR(MAIN_FRAME_COL);
		Rectangle(0,0,320,34,NEW_HDR_COL);

		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Recently Used");	// header
	   	Rectangle_Line_function(1,3);

//		for(menu_count = 1; menu_count <=3 ; menu_count++)				//no of lines
//		{
//			Rectangle(7,34+(43*menu_count),290,0, BLACK);		// no of rect line
//		}

		TFT_ST7789V_lcd_shapes(38+163,38,300+15,306,LIGHT_GRAY_3);  	//Scroll bar                                                                                           //SCROLLING BOX OUTSIDE LAYER
		TFT_ST7789V_lcd_shapes(40+57,40,303+12,306,BLACK);

		Rectangle(0,206,320,34,NEW_FTR_COL);
		Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to confirm",(uint8_t*)"OK",2,14);

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void recent_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
{

	uint8_t loop_count=0;
    uint32_t back_colour = 0;
   	uint32_t text_colour = 0;
   	uint32_t rec_star_colour=0;//27-03

	for(loop_count=0;loop_count<=end_opt;loop_count++)
	{
		if(loop_count == start_opt)//0==0
		{
			back_colour	= LIGHT_GRAY;
			text_colour = BLACK;
			rec_star_colour=MAIN_FRAME_COL;
			TFT_ST7789V__rectangle_curve(3,35+(43*(start_opt)),41,290,0,back_colour); //0
		}
		else
		{
			back_colour	= MAIN_FRAME_COL;
			text_colour = WHITE;
			rec_star_colour=GOLD;
		}


		Font_Select(ARIAL_14);
		TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
				(uint8_t*)Drug_Names[drug_num[((page*4)+loop_count)]/4][drug_num[((page*4)+loop_count)]%4],back_colour,text_colour);//29-03

		if(dose.drug_select_no==drug_num[((page*4)+loop_count)])	//27-03
		//if((page*4)+loop_count == dose.drug_select_no )	//27-03
		{
			  TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS)+(loop_count)*VER_TEXT_SPACE_1,250,0,back_colour,rec_star_colour);
		}
	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void recent_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page,  char array[5][4][20])
{

	uint8_t loop = 0;
	uint8_t opt_no  = 0;
	uint32_t back_colour = 0;
	uint32_t text_colour = 0;
	uint32_t rec_star_colour=0;//27-03


	for(loop = 0; loop<2; loop++)
	{
		if(!loop)
		{
			back_colour = MAIN_FRAME_COL;
			text_colour = WHITE;
			rec_star_colour=GOLD;
			opt_no		= prev_option;
		}
		else
		{
			back_colour = LIGHT_GRAY;
			text_colour = BLACK;
			rec_star_colour=MAIN_FRAME_COL;
			opt_no= curr_option;
		}

		TFT_ST7789V__rectangle_curve(3,35+(43*(opt_no)),41,290,0,back_colour);
		Font_Select(ARIAL_14);
			
		TFT_String(9,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
								(uint8_t*)Drug_Names[drug_num[((page*4)+opt_no)]/4][drug_num[((page*4)+opt_no)]%4],back_colour,text_colour);//29-03
		if(dose.drug_select_no == drug_num[((page*4)+opt_no)])	//27-03
		{
			TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS)+(opt_no)*VER_TEXT_SPACE_1,250,0,back_colour,rec_star_colour);
		}
	}
}

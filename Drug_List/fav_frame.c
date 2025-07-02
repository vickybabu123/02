
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
#include "Dosage_mode.h"	//22-03
#include <Boot_up.h>

extern char Drug_Names[150][4][20];

extern uint16_t fav_drug_list[11];
extern uint16_t drug_new_no;	//22-03

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void favourite_Frame(void)
{
		uint8_t menu_count = 0;
	 //  	Rectangle(0,0,320,240,MAIN_FRAME_COL);
		CLRSCR(MAIN_FRAME_COL);
		Rectangle(0,0,320,34,NEW_HDR_COL);

		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Favourites");	// header

//		for(menu_count = 1; menu_count <=3 ; menu_count++)				//no of lines
//		{
//			Rectangle(7,34+(43*menu_count),290,0, BLACK);		// no of rect line
//		}
	   	Rectangle_Line_function(1,3);

		Rectangle(0,206,320,34,NEW_FTR_COL);
		Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to confirm",(uint8_t*)"OK",2,14);

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void favourite_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
{

	uint8_t loop_count=0;
    uint32_t back_colour = 0;
   	uint32_t text_colour = 0;
   	uint32_t fav_star_colour=0;//ZOOZ_2

	for(loop_count=0;loop_count<=end_opt;loop_count++)
	{
		if(loop_count == start_opt)
		{
			back_colour	= LIGHT_GRAY;
			text_colour = BLACK;
			fav_star_colour=MAIN_FRAME_COL;//ZOOZ_2
			TFT_ST7789V__rectangle_curve(3,35+(43*(start_opt)),41,290,0,back_colour); //0
		}
		else
		{
			back_colour	= MAIN_FRAME_COL;
			text_colour = WHITE;
			fav_star_colour=GOLD;//ZOOZ_2
		}

		Font_Select(ARIAL_14);

		TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
		(uint8_t*)Drug_Names[fav_drug_list[((page*4)+loop_count)]/4][fav_drug_list[((page*4)+loop_count)]%4],back_colour,text_colour);

		 //if( ((page*4)+loop_count) == dose.drug_select_no)
			if(dose.drug_select_no==fav_drug_list[((page*4)+loop_count)])//ZOOZ_2
			  {
				  TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS)+(loop_count)*VER_TEXT_SPACE_1,250,0,back_colour,fav_star_colour);
			  }
	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void favourite_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page)//,  char* array[5][4][20])
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


			TFT_ST7789V__rectangle_curve(3,35+(43*(opt_no)),41,290,0,back_colour);

			Font_Select(ARIAL_14);

			TFT_String(9,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),


			(uint8_t*)Drug_Names[fav_drug_list[((page*4)+opt_no)]/4][fav_drug_list[((page*4)+opt_no)]%4],back_colour,text_colour);



			if(dose.drug_select_no == fav_drug_list[((page*4)+opt_no)])	//22-03
			{
				 TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS)+(opt_no)*VER_TEXT_SPACE_1,250,0,back_colour,GOLD);
			}



	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void fav_edit_subsetting_frame(void)
{
	Font_Select(ARIAL_14);
	Rectangle(0,206,320,34,NEW_FTR_COL);

	TFT_String(65,210,(uint8_t *)" SEL",NEW_FTR_COL,HDR_TXT_COL);
	TFT_String(220,210,(uint8_t *)" DEL",NEW_FTR_COL,HDR_TXT_COL);

	TFT_ST7789V_lcd_drawcircle1(40,223,15,MAIN_FRAME_COL,MAIN_FRAME_COL);    //	 Left Circle
	TFT_ST7789V_lcd_drawcircle1(190,223,15,MAIN_FRAME_COL,MAIN_FRAME_COL);

	TFT_ST7789V_Mute_Symbol_12pt(218,182,0,MAIN_FRAME_COL,WHITE);
	Font_Select(ARIAL_9);

	TFT_String(30,218,(uint8_t*)"OK",MAIN_FRAME_COL,WHITE);

}



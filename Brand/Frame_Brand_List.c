#include "LPC55S16.h"
#include "Color.h"
#include "keypad.h"
#include "Shapes.h"
#include "TFT_Commands.h"
#include "Driver_Timer.h"
#include "TFT_String.h"


/**********************************************************************************
 *                         global_variable
***********************************************************************************/

char Brand_Names[6][4][15] ={
										{"DISPO VAN",		"BD",		 "BBraun",    "Nipro"},
										{"Baxter","Teleflex", "Romson",   "Terumo"}
//								{"BBRAUN",		"BD",		 "JMS",    "JNS"},
//								{"Polymed",  "Romson", "Safeti",   "Termuo"}
                                };

//char *brand_list[17]={"BBRAUN","BD", "JMS", "JNS",
//					  "Polymed",   "Romson",  "Safeti",  "Termuo"
//					   };
//
//char *brand_1[4][4]={	{"Dispo",	"BD",		 "BBRAUN",    "Nipro"},
//						{"JMS",      "Romson","Baxter", "Got Bul"},
//						{"MX Rad",    "Esthl",   "Termu","Telef"}
//					};

extern uint8_t brand_select_no;//22-03
/**********************************************************************************
 *                         extern_variable
***********************************************************************************/

void Brand_List_layout ();
void  Brand_List_option(uint8_t page,uint8_t starting_count,uint8_t Final_count);
void Brand_list_option_scroll(uint8_t prev_option,uint8_t curr_option,uint8_t page, const char array[6][4][15]);



/**************************************************************************
                            extern Functions Call
***************************************************************************/

extern void TFT_ST7789V_14arial_writestr_New(uint16_t xpos, uint16_t ypos,const uint8_t *asciistr,
		uint32_t boarder_color,uint32_t fill_color);
extern void Frame_Header(uint32_t BG_color, uint32_t TXT_color ,uint8_t *word);
////extern void Frame_Footer(uint32_t BG_color, uint32_t TXT_color,uint8_t *word,uint8_t *circle_word,uint8_t circle_pos);

extern void TFT_ST7789V__rectangle_curve(uint16_t xpos1, uint16_t ypos1, uint16_t width,uint16_t height,
		uint16_t radius,uint32_t colour);
extern void Font_Select(uint8_t Font_Size);
extern uint16_t TFT_String(uint16_t xpos, uint16_t ypos,const uint8_t *asciistr,uint32_t BG_COL,uint32_t TXT_COL);
extern void Rectangle(uint16_t x_axis,uint16_t y_axis,uint16_t Length,uint16_t Height,uint32_t Color);
extern uint8_t TFT_ST7789V_tick_symbol_14pt(uint16_t xpos, uint16_t ypos,    //22-03
	       uint8_t arrow, uint32_t boarder_color, uint32_t fill_color);//ZOOZ_2

/**************************************************************************
                               Function
***************************************************************************/



/*----------------------------------------------------------------
 * Function_name:Brandlistlayout
 * Arguments    :void
 * return       :void
 * Description  :Able to provide frame for the entire brand screen
------------------------------------------------------------------- */

void Brand_List_layout ()
{
	uint8_t loop=0;
	Rectangle(0,36,320,169,MAIN_FRAME_COL);

	 Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Syringe Brand");
	 Rectangle_Line_function(1,3);

//	 for(loop=1;loop<=3;loop++)
//	 {
//		 Rectangle(7,34+(43*loop),290,0, BLACK);
////		 Rectangle(7,34+(43*2),290,0,BLACK);
////		 Rectangle(7,34+(43*3),290,0,BLACK);
//	 }
	 Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to Select",(uint8_t*)"OK",2,14);  //   TFT_ST7789V_lcd_drawcircle1(150,223,15,MAIN_FRAME_COL,MAIN_FRAME_COL);

}

/*----------------------------------------------------
 * Function_name:Brandlistoption
 * Arguments    :pageno,starting count,finalcount
 * return       :void
 * Description  :Able to provide option based on counts
-------------------------------------------------------- */

void  Brand_List_option(uint8_t page,uint8_t starting_count,uint8_t Final_count)
{
	    uint8_t loop_count=0;
	    uint32_t back_colour = 0;
		uint32_t text_colour = 0;
		uint32_t tick_color = 0;


//		Font_Select(ARIAL_14);
//		TFT_Number(50,150,Final_count,YELLOW,RED);

      for(loop_count=0;loop_count<=Final_count;loop_count++)
		{
	    	if(loop_count == starting_count)
	    	{
//	    		Font_Select(ARIAL_14);
//	    		TFT_Number(50,170,starting_count,YELLOW,RED);
	    		back_colour	= LIGHT_GRAY;
				text_colour=  BLACK;
				tick_color = MAIN_FRAME_COL;
				TFT_ST7789V__rectangle_curve(3,35+(43*(starting_count)),41,290,0,back_colour);
	    	}
	    	else
	    	{
	    		tick_color = GOLD;
				back_colour	= MAIN_FRAME_COL;
				text_colour =WHITE;
	    	}

	    	  Font_Select(ARIAL_14);

			  TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE_1),
			  (uint8_t*)Brand_Names[page][loop_count],back_colour,text_colour);

			  // delay_secs(1);
			  if(((page*4)+loop_count )== brand_select_no)   //22-03
			  {
				  TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS)+((loop_count)*VER_TEXT_SPACE_1),250,0,back_colour,tick_color);
			  }
		}
}

/*---------------------------------------------
 * Function_name:Brand_list_option_scroll
 * Arguments    :prev option,curr_option,page
 * return       :void
 * Description  :Able to scroll the option
----------------------------------------------- */

void Brand_list_option_scroll(uint8_t prev_option,uint8_t curr_option,uint8_t page, const char array[6][4][15])
 {
	uint32_t back_colour = 0;
    uint32_t text_colour = 0;
	uint8_t loop		 = 0;
	uint8_t opt_no		 = 0;
	uint32_t tick_color = 0;

	for(loop = 0; loop<3; loop++)
	{
		if(!loop)
		{
			back_colour     = MAIN_FRAME_COL;
			text_colour 	= WHITE;
			opt_no			= prev_option;
			tick_color		=GOLD;
		}
		else
		{
			back_colour   = LIGHT_GRAY;
			text_colour   = BLACK;
			opt_no		  = curr_option;
			tick_color	  =MAIN_FRAME_COL;
    	}


	    TFT_ST7789V__rectangle_curve(3,35+(43*(opt_no)),41,290,0,back_colour);

	    Font_Select(ARIAL_14);
	    TFT_String(9,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
							(uint8_t*)array[page][opt_no],back_colour,text_colour);
		if((page*4)+opt_no == brand_select_no)
		{
			TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS)+(opt_no)*VER_TEXT_SPACE_1,250,0,back_colour,tick_color);
		}

 }
}

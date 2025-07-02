#include "LPC55S16.h"
#include "Shapes.h"
#include "Color.h"
#include"Keypad.h"
#include "TFT_Commands.h"
//#include "Main_Menu.h"
#include "TFT_String.h"
//#include "Flowrate_Screen.h"
#include "Brand.h"
//#include "Drug_List.h"
#include "Occlusion.h"
#include "Driver_I2C.h"
#include "SD_Calib.h"
#include <Boot_up.h>

extern unsigned long int keyvalue;

extern void Font_Select(uint8_t Font_Size);
extern void Frame_Header(uint32_t BG_color, uint32_t TXT_color ,uint8_t *word);
extern void TFT_Number(uint16_t xpos,uint16_t ypos,uint32_t number,uint32_t boarder_color,uint32_t fill_color);
//extern void Frame_Footer(uint32_t BG_color, uint32_t TXT_color,uint8_t *word,uint8_t *circle_word,uint8_t circle_pos);
extern uint16_t ADC_sdcalib(uint16_t Raw_val, uint16_t Data_diff,uint8_t samples );
extern uint16_t TFT_String(uint16_t xpos, uint16_t ypos,const uint8_t *asciistr,uint32_t BG_COL,uint32_t TXT_COL);

uint8_t SD_Calibration(void);
uint8_t pop_up_screen(void);

uint16_t syringe_noise_filter(void);

void sd_cursor_sel(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[2][4]);
void SD_layout(void);
void sy_siz(unsigned int Pos);
void sy_size_setting(void);
void sd_baseval_check(void);
void pot_calibration(void);
void ADC_read(uint8_t adc_input);
void syringe_selection_screen(void);
void frames_syringe_option(uint8_t page,uint8_t starting_count,uint8_t ending_count);
void syringe_adc_val(uint8_t *syringe_size);
void live_adc_calib(void);
void scroll_bar(uint8_t option_no,uint8_t page_no,uint8_t total_option);                                      //(uint8_t prev_option, uint8_t curr_option, uint8_t page)
void calib_all_frame(uint8_t s_size);

uint8_t detect_syringe_size(unsigned int sybrand);

extern char *Brand_Names[3][4];
extern char* syringe_settings[2][4];
extern char* syringe_min_max[2][4];
extern char* syringe[7];

extern uint8_t brand;
extern uint8_t syringe_1;
extern uint8_t diff_val[9];

extern uint8_t brand_select_no;

extern uint16_t G_loaded_adc_val[9];
//extern uint32_t  G_minval[8];
extern uint16_t G_maxval[8];
extern uint32_t G_Syr_size_val[2][4];
extern uint16_t  G_adcval[8];//={0,585,752,1035,1355,1870,2250};

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void SD_layout()
{
	uint8_t loop=0;
	for(loop=1;loop<=3;loop++)
	{
		Rectangle(7,34+(43*loop),290,0, BLACK);

	}
//	Rectangle(7,34+(43*2),290,0,BLACK);
//	Rectangle(7,34+(43*3),290,0,BLACK);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t syr_place_screen(uint8_t* s_size1)	//REW_UP
{
	uint8_t s_size_loop=0;
    uint8_t check_flag=0;
    uint8_t s_size=*s_size1;
	//Rectangle(0,0,320,240,MAIN_FRAME_COL);
    CLRSCR(MAIN_FRAME_COL);

	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Syringe size ADC");

	TFT_ST7789V_lcd_drawcircle1(165,223,16,MAIN_FRAME_COL,MAIN_FRAME_COL);
	//Font_Select(ARIAL_9);//REW_UP
	TFT_ST7789V__rectangle_curve(40,44,154,240,0,WHITE);//58,200

	Font_Select(ARIAL_12);
//	TFT_String(57,70,(uint8_t*)"Place the ",WHITE,BLACK);
	TFT_String(230,70,(uint8_t*)syringe[s_size],WHITE,BLACK);
	sd_calib_placement_frames();
//	TFT_String(194,70,(uint8_t*)" syringe ",WHITE,BLACK);
//	TFT_String(150,115,(uint8_t*)"&",WHITE,BLACK);
//	TFT_String(60,145,(uint8_t*)"Press ok to calibrate",WHITE,BLACK);

	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to confirm",(uint8_t*)"OK",2,14);
	s_size_loop=1;
	while(s_size_loop)    //REW_UP
		{

			switch(KEY.value)
			{

				case OK_KEY:

				beep_sound();
				check_flag=1;
				s_size_loop=0;
				while(KEY.value);
				break;

			    case BACK_KEY:

				beep_sound();
				check_flag=0;
				s_size_loop=0;
				while(KEY.value);
				break;

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

void min_max_val_header_footer()
{
	uint8_t loop_count=0;
//	Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	Rectangle(0,0,320,34,NEW_HDR_COL);
	Font_Select(ARIAL_14);
	TFT_String(18,11,(uint8_t*)"Syr              Min            Max",NEW_HDR_COL,HDR_TXT_COL);

//	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Syr    min     max   val");

   	Rectangle_Line_function(1,3);
   	Font_Select(ARIAL_9);
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to Exit",(uint8_t*)"BK",2,14);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void syringe_adc_val(uint8_t *syringe_size)
{

	uint8_t loop_count = 0;
	uint8_t syr_size=0;

	syr_size=*syringe_size;

	//Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Syringe size");

	for(loop_count = 2; loop_count <3 ; loop_count++)
	{
		Rectangle(7,77+(43*loop_count),290,0, BLACK);
		TFT_String(160,88+(43*loop_count),(uint8_t*)":",MAIN_FRAME_COL,WHITE);
	}

	Font_Select(ARIAL_12);
	TFT_String(85,174,(uint8_t*)"Size",MAIN_FRAME_COL,WHITE);
	TFT_String(181,174,(uint8_t*)syringe[syr_size],MAIN_FRAME_COL,WHITE);
	TFT_ST7789V_lcd_drawcircle1(150,223,15,MAIN_FRAME_COL,MAIN_FRAME_COL);
	Font_Select(ARIAL_9);
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to confirm",(uint8_t*)"OK",2,14);
	*syringe_size=syr_size;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t pop_up_screen(void)
{
	//Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Syringe size");
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to confirm",(uint8_t*)"OK",2,14);
	Font_Select(ARIAL_14);
	TFT_ST7789V__rectangle_curve(20,55,105,280,0,WHITE);//70//80//120
	TFT_String(110,96,(uint8_t*)"Calibrated",WHITE,BLACK);
	return 0;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t pop_up_erase()
{
	TFT_ST7789V__rectangle_curve(40,44,154,240,0,WHITE);//58,200
	TFT_String(110,96,(uint8_t*)"Calibrated",WHITE,WHITE);
	return 0;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void syringe_selection_screen(void)
{
	uint8_t loop_count = 0;
//	uint8_t page=0;
 //   uint8_t option=0;
//	TFT_ST7789V_lcd_shapes(0,240,0,320,MAIN_FRAME_COL);             //DRAW A SHAPES
//	Rectangle(0,0,320,240,NEW_HDR_COL);
//	Rectangle(0,0,320,240,MAIN_FRAME_COL);
//	CLRSCR(MAIN_FRAME_COL);
	CENTERSCR();
//	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Syr Size calib");
//	TFT_String(20,11,(uint8_t*)Brand_Names[page/4][option%4],NEW_HDR_COL,HDR_TXT_COL);

//	for(loop_count = 1; loop_count <=3 ; loop_count++)//REW_UP
//	{
//		Rectangle(7,34+(43*loop_count),290,0, BLACK);
//	}
   	Rectangle_Line_function(1,3);

//  Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press          to change");//
//	TFT_ST7789V_lcd_drawcircle1(150,223,15,MAIN_FRAME_COL,MAIN_FRAME_COL);     //REW_UP

	//Font_Select(ARIAL_9);//REW_UP
//	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to confirm",(uint8_t*)"OK",2,14);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void frames_syringe_option(uint8_t page,uint8_t starting_count,uint8_t ending_count)
{
	//	uint16_t data[4]={2,5,10,20};
	//	uint16_t data1[4]={30,50};

	//uint16_t value = 0;
	uint8_t loop_count=0;
	uint32_t back_colour = 0;
	uint32_t text_colour = 0;

	//	Rectangle(0,0,320,240,MAIN_FRAME_COL);



	for(loop_count=0;loop_count<=ending_count;loop_count++)
	{
	//   if((page == 0 )|| (page == 1 && loop_count<3))//loop count minimum means here create the empty space for upcoming rows
	//	{
		if(loop_count == starting_count)
		{
			back_colour	= LIGHT_GRAY;
			text_colour= BLACK;
			TFT_ST7789V__rectangle_curve(3,35+(43*(loop_count)),41,297,0,back_colour);
		}
		else
		{
			back_colour	= MAIN_FRAME_COL;
			text_colour = WHITE;
		}

	//if((page == 0)|| (page = 1))//loop count minimum means here create the empty space for upcoming rows  //REW_UP
	{
		Font_Select(ARIAL_14);
		TFT_String( 9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
				(uint8_t*)syringe_settings[page][loop_count],back_colour,text_colour);



	if((page==0)||(page==1 && loop_count<=1))
	{
//		TFT_Number(170,INITIAL_TEXT_POS+((loop_count)*VER_TEXT_SPACE),
//					(uint8_t*)G_Syr_size_val[(page)][(loop_count)],back_colour,text_colour);

		TFT_Number(170,INITIAL_TEXT_POS+((loop_count)*VER_TEXT_SPACE),
						G_loaded_adc_val[((page*4)+loop_count)+1],back_colour,text_colour);

		TFT_String(150,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
							(uint8_t*)":",back_colour,text_colour);


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
void sd_cursor_sel(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[2][4])
{

    uint32_t back_colour = 0;
	uint32_t text_colour	= 0;
	uint8_t loop		    = 0;
	uint8_t opt_no		    = 0;

	for(loop=0; loop<2; loop++)
	{
		if(!loop)
		{
			back_colour = MAIN_FRAME_COL;
			text_colour 	= WHITE;
			opt_no			= prev_option;
		}
		else
		{
			back_colour = LIGHT_GRAY;
			text_colour   = BLACK;
			opt_no		     = curr_option;
		}


    TFT_ST7789V__rectangle_curve(3,35+(43*(opt_no)),41,297,0,back_colour);

    Font_Select(ARIAL_14);

    TFT_String(9,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
						(uint8_t*)array[page][opt_no],back_colour,text_colour);

    if((page == 0) ||(page == 1 && opt_no<=1))
        {
		TFT_String(150,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
				 (uint8_t*)":", back_colour,text_colour);

//	TFT_Number(170,INITIAL_TEXT_POS+((opt_no)*VER_TEXT_SPACE),
//			(uint8_t*) G_Syr_size_val[page][opt_no],back_colour,text_colour);  //Right side data values
		TFT_Number(170,INITIAL_TEXT_POS+((opt_no)*VER_TEXT_SPACE),
				G_loaded_adc_val[((page*4)+opt_no)+1],back_colour,text_colour);  //Right side data values

       }

  }
}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void pull_in_frame()
{

//	Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Syringe size calib");

	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to confirm",(uint8_t*)"OK",2,14);
	Rectangle(10,34+(43*1),290,0,BLACK);

	TFT_ST7789V__rectangle_curve(10,35,41,300,0,LIGHT_GRAY);
	Font_Select(ARIAL_14);

	TFT_String(34,50,(uint8_t*)"Pull in",LIGHT_GRAY,BLACK);
	TFT_String(150,50,(uint8_t*)":",LIGHT_GRAY,BLACK);



}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void pullin_popup()
{

	uint8_t x_pos=0;

	Font_Select(ARIAL_12);
	TFT_ST7789V__rectangle_curve(20,90,100,280,0,WHITE);//70//80//120

	x_pos=Letters_Alignments(0,0,(uint8_t*)"INSTRUCTION",2);
	TFT_String(x_pos,97,(uint8_t*)"INSTRUCTION",WHITE,RED);

	x_pos=Letters_Alignments(0,0,(uint8_t*)"Ensure no syringe placed &",2);
	TFT_String(x_pos,126,(uint8_t*)"Ensure no syringe placed &",WHITE,BLACK);

	x_pos=Letters_Alignments(0,0,(uint8_t*)"Syr holder placed inside",2);
	TFT_String(x_pos,156,(uint8_t*)"Syr holder placed inside",WHITE,BLACK);

}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void pull_out_frame()
{

//	Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Syr Size Calibration");

	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to confirm",(uint8_t*)"OK",2,14);
	Rectangle(7,34+(43*1),290,0,BLACK);

	TFT_ST7789V__rectangle_curve(10,35,41,300,0,LIGHT_GRAY);

	Font_Select(ARIAL_14);
	TFT_String(34,50,(uint8_t*)"Pull out",LIGHT_GRAY,BLACK);
	TFT_String(150,50,(uint8_t*)":",LIGHT_GRAY,BLACK);


}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void pull_out_popup()
{
	uint8_t x_pos=0;

	Font_Select(ARIAL_12);
	TFT_ST7789V__rectangle_curve(20,90,100,280,0,WHITE);//70//80//120

	x_pos=Letters_Alignments(0,0,(uint8_t*)"INSTRUCTION",2);
	TFT_String(x_pos,96,(uint8_t*)"INSTRUCTION",WHITE,RED);

	x_pos=Letters_Alignments(0,0,(uint8_t*)"Pull out the syringe holder",2);
	TFT_String(x_pos,126,(uint8_t*)"Pull out the syringe holder",WHITE,BLACK);

	x_pos=Letters_Alignments(0,0,(uint8_t*)"and twist it to lock",2);
	TFT_String(x_pos,156,(uint8_t*)"and twist it to lock",WHITE,BLACK);

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void calib_all_frame(uint8_t s_size)
{
//	Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Syringe size calibration");
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to confirm",(uint8_t*)"OK",2,14);
//	Rectangle(7,34+(43*1),290,0,BLACK);
//	TFT_ST7789V__rectangle_curve(10,35,41,300,0,LIGHT_GRAY);

	Font_Select(ARIAL_12);
	Rectangle(7,34+(43*3),290,0,BLACK);

	TFT_String(12,180,(uint8_t*)"Ensure",MAIN_FRAME_COL,WHITE);
	//Font_Select(ARIAL_12);

//	TFT_String(77,180,(uint8_t*)syringe[s_size],MAIN_FRAME_COL,BLACK);
//	TFT_Number(180,51,s_size,MAIN_FRAME_COL,BLACK);

	TFT_String(139,180,(uint8_t*)"syringe is placed",MAIN_FRAME_COL,WHITE);

}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void calibrate_popup()
{
//	uint8_t page_no;
//	uint8_t option_no;
//	Rectangle(0,0,320,240,MAIN_FRAME_COL);
	uint8_t x_pos=0;

	Font_Select(ARIAL_14);

	TFT_ST7789V__rectangle_curve(20,90,100,280,0,YELLOW);//70//80//120
	x_pos=Letters_Alignments(0,0,(uint8_t*)"Value not in range",2);
	TFT_String(x_pos,130,(uint8_t*)"Value not in range",YELLOW,BLACK);

//	TFT_String(65,120,(uint8_t*)"Value",YELLOW,BLACK);
//	TFT_String(100,150,(uint8_t*)"not in range",YELLOW,BLACK);

}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void calibrate_popup_erase()
{
	TFT_ST7789V__rectangle_curve(20,60,100,280,0,WHITE);//70//80//120
}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void minval_adc_option_screen(uint8_t page,uint8_t starting_count,uint8_t ending_count)
{
	uint8_t loop_count=0;
	uint32_t back_colour = 0;
	uint32_t text_colour = 0;

	for(loop_count=0;loop_count<=ending_count;loop_count++)
	{

			back_colour	= MAIN_FRAME_COL;
			text_colour = WHITE;

	if((page == 0)|| (page = 1 && loop_count<=1))//loop count minimum means here create the empty space for upcoming rows
	{
		Font_Select(ARIAL_14);
		TFT_String( 9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
				(uint8_t*)syringe_min_max[page][loop_count],back_colour,text_colour);



	if((page==0)||(page==1 && loop_count<=1))
	{

		TFT_Number(120,INITIAL_TEXT_POS+((loop_count)*VER_TEXT_SPACE),
				G_adcval[((page*4)+loop_count)+1],back_colour,text_colour);
		TFT_String(100,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
							(uint8_t*)":",back_colour,text_colour);
		TFT_String(180,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
									(uint8_t*)":",back_colour,text_colour);
		TFT_Number(220,INITIAL_TEXT_POS+((loop_count)*VER_TEXT_SPACE),
				G_maxval[((page*4)+loop_count)+1],back_colour,text_colour);


	}
    }
  }
}

void sd_calib_placement_frames()
{
	Font_Select(ARIAL_12);
	TFT_String(54,70,(uint8_t*)"Place the syringe:",WHITE,BLACK);
//	TFT_String(194,70,(uint8_t*)" syringe ",WHITE,BLACK);
	TFT_String(150,110,(uint8_t*)"&",WHITE,BLACK);
	TFT_String(60,145,(uint8_t*)"Press ok to calibrate",WHITE,BLACK);

}

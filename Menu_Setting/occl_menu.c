/*
 * occl_menu.c
 *
 *  Created on: 02-Mar-2024
 *      Author: 7303
 */

#include "LPC55S16.h"
#include "Shapes.h"
#include "Color.h"
#include "Keypad.h"
#include "TFT_Commands.h"
#include "TFT_String.h"
#include "Flowrate_Screen.h"
//#include "Brand.h"
#include "Drug_List.h"
#include "Occlusion.h"
#include "Bolus_Header.h"
#include "Power_off.h"
#include "Main_Menu.h"
#include"Driver_I2C.h"
#include"Driver_Timer.h"
#include "Power_off.h"
#include "sound.h"
#include <Boot_up.h>



/**************************************************************************
                          Global Variables
***************************************************************************/

uint8_t G_occl_unit=0;
//uint8_t G_occl_unit1=0;

uint8_t G_occl_level=0;

extern uint8_t auto_lock_time;  //ZOOZ_1

extern uint8_t auto_exit_mode;//common_bug   
const char* occl_menu[3]={"Pressure Unit","Occlusion Lvl"};
const char* occl_values[3][10]={{"mmHg",  "PSI",  "kPa",  "bar"},
								{"1","2","3","4","5","6","7","8","9","10"}
							   };

const char* unit_value[4][10]={{"100","200","300","400","500","600","700","800","900","1000"},
							   {"2","4","6","8","10","12","14","16","18","20"},
							   {"13.3","26.6","39.9","53.3","66.6","79.9","93.3","106.6","119.9","132.2"},
							   {"0.13","0.26","0.39","0.5","0.6","0.7","0.9","1.0","1.1","1.3"}
							  };


extern uint8_t ON_Flag;

/**************************************************************************
 *Function Name :void Occl_Screen()
 *Arguments     :void
 *Return        :void
 *Description	:In this function to enter the Bolus option
***************************************************************************/

uint8_t Occlusion_setting()
{
	uint8_t page_no=0;
	uint8_t option_no=0;
	uint8_t prev_option = 0;
	uint8_t occl_variable=1;
	uint8_t edit_flag;
	uint8_t occl_level=0;	//common_bug
	uint8_t occl_unit=0;	//common_bug
    uint16_t arrow_pos[2]={280,280};
	edit_flag=0;
	occl_level=G_occl_level;//common_bug
	occl_unit=G_occl_unit;	//common_bug
	edit_flag=0;
	const uint32_t occ_col[2][2] =
		{
		    {LIGHT_GRAY, BLACK},
		    {LIGHT_GRAY, LIGHT_GRAY}
		};
	POW.power_status_flag=1;
// 	auto_lock_time=30;//common_bug  //ZOOZ_1

while(KEY.value)
{

}

	while(occl_variable)
	{

		Power_off();

		if(!ON_Flag) 	//MAIN.main_power_status_flag == 1 )
		{
			G_occl_level=occl_level;//common_bug
			G_occl_unit=occl_unit;//common_bug
			break;//23-03
		}

		else if(POW.power_status_flag)
		{
			POW.power_status_flag=0;//26-03
			Occl_Frame();
			Occl_Opt_Frame(page_no,option_no,2);

			if(edit_flag)
			{
				if(option_no==0)
				{
					TFT_ST7789V_left_Right_arrow_14_arial(50,190,0,LIGHT_GRAY,BLACK);
					TFT_ST7789V_left_Right_arrow_14_arial(50,280,1,LIGHT_GRAY,BLACK);
				}
				else if(option_no==1)
				{
					TFT_ST7789V_left_Right_arrow_14_arial(50+40,190,0,LIGHT_GRAY,BLACK);
					TFT_ST7789V_left_Right_arrow_14_arial(50+40,280,1,LIGHT_GRAY,BLACK);
				}
				edit_subsetting_frame();
			}
		}
					if(KEY.value)//common_bug  //ZOOZ_1
					{
						auto_lock_time=AUTO_EXIT_TIME;
					}
					else if(!auto_lock_time)
					{
						//	auto_lock_time=45;
							G_occl_level=occl_level;//common_bug
							G_occl_unit=occl_unit;	//common_bug
							break;
					}							//common_bug


		switch(KEY.value)
		{
		case DOWN_KEY :			//DOWN_KEY
				beep_sound();
			if(!edit_flag)
			{
				if(!option_no)
				{
					option_no=1;
				}
				else
				{
					option_no=0;
				}
					if(option_no!=prev_option)
					{
						Occl_cursor(prev_option,option_no,page_no,occl_menu);
						prev_option = option_no;
					}
			}
				while(KEY.value);
				break;

			case UP_KEY:			//UP_KEY
				beep_sound();
			if(!edit_flag)
			{
				if(option_no)
					option_no=0;

			else
			{
				option_no=1;
			}
				if(option_no!=prev_option)
				{
					Occl_cursor(prev_option,option_no,page_no,occl_menu);
					prev_option = option_no;
				}
			}
			while(KEY.value);
			break;

			case LEFT_KEY:				 //LEFT_KEY:
				beep_sound();
				if(edit_flag)
				{
					occl_subsetting( option_no,0);
				}

			while(KEY.value);
			break;

			case RIGHT_KEY:				 //RIGHT_KEY:
				beep_sound();
			if(edit_flag)
			{
				occl_subsetting( option_no,1);
			}

			while(KEY.value);
			break;

			case OK_KEY: 					 //OK_KEY

			beep_sound();

//			if(!edit_flag)
//			{
//				if(option_no==0)
//				 {
//					TFT_ST7789V_left_Right_arrow_14_arial(50,190,0,LIGHT_GRAY,BLACK);
//					TFT_ST7789V_left_Right_arrow_14_arial(50,280,1,LIGHT_GRAY,BLACK);
//				 }
//				else if(option_no==1)
//				 {
//					TFT_ST7789V_left_Right_arrow_14_arial(50+40,190,0,LIGHT_GRAY,BLACK);
//					TFT_ST7789V_left_Right_arrow_14_arial(50+40,230,1,LIGHT_GRAY,BLACK);
//				 }
//				edit_subsetting_frame();
//				edit_flag = 1;
//			}
//
//			else
//			{
//				edit_flag = 0;
//
//					if(option_no==0)
//					{
//						TFT_ST7789V_left_Right_arrow_14_arial(50,190,0,LIGHT_GRAY,LIGHT_GRAY);
//						TFT_ST7789V_left_Right_arrow_14_arial(50,280,1,LIGHT_GRAY,LIGHT_GRAY);
//
//						TFT_ST7789V_left_Right_arrow_14_arial(50+40,190,0,MAIN_FRAME_COL,MAIN_FRAME_COL);
//						TFT_ST7789V_left_Right_arrow_14_arial(50+40,230,1,MAIN_FRAME_COL,MAIN_FRAME_COL);
//					}
//					else if(option_no==1)
//					{
//						TFT_ST7789V_left_Right_arrow_14_arial(50,190,0,MAIN_FRAME_COL,MAIN_FRAME_COL);
//						TFT_ST7789V_left_Right_arrow_14_arial(50,280,1,MAIN_FRAME_COL,MAIN_FRAME_COL);
//
//						TFT_ST7789V_left_Right_arrow_14_arial(50+40,190,0,LIGHT_GRAY,LIGHT_GRAY);
//						TFT_ST7789V_left_Right_arrow_14_arial(50+40,230,1,LIGHT_GRAY,LIGHT_GRAY);
//					}
//			Font_Select(ARIAL_14);
//			TFT_Number(0,70,arrow_pos[option_no],YELLOW,RED);


				if (!edit_flag)
				{
					TFT_ST7789V_left_Right_arrow_14_arial(50 + (option_no ? 40 : 0), 190, 0, occ_col[0][0], occ_col[0][1]);
					TFT_ST7789V_left_Right_arrow_14_arial(50 + (option_no ? 40 : 0),arrow_pos[option_no], 1, occ_col[0][0], occ_col[0][1]);
					edit_subsetting_frame();
					edit_flag = 1;
				}

				else
				{
					edit_flag = 0;
					TFT_ST7789V_left_Right_arrow_14_arial(50 + (option_no ? 40 : 0), 190, 0, occ_col[1][0], occ_col[1][1]);
					TFT_ST7789V_left_Right_arrow_14_arial(50 + (option_no ? 40 : 0), arrow_pos[option_no], 1, occ_col[1][0], occ_col[1][1]);
					Occl.PSI_level = (G_occl_level + 1) * 2;

					Occl.dynamic_ratio = 54 / Occl.PSI_level;
					edit_flag = 0;
					Frame_Footer(NEW_FTR_COL, HDR_TXT_COL, (uint8_t*)"        to edit", (uint8_t*)"OK", 1,14);
				}

					EEPROM_datawrite(EEPROM_G_occl_unit ,G_occl_unit,1);//22-03
					EEPROM_datawrite(EEPROM_G_occl_level ,G_occl_level,1);

					occl_level=G_occl_level;//common_bug
					occl_unit=G_occl_unit;//common_bug


			while(KEY.value);
			break;

			case BACK_KEY:

				beep_sound();
				if(edit_flag)
				{
					G_occl_level=occl_level;//common_bug  //ZOOZ_1
					G_occl_unit=occl_unit;//common_bug
				}
				occl_variable=0;

				while(KEY.value);
				break;
		}
	}
	return 0;
}

/**************************************************************************
 *Function Name :void Occl_Frame(void)
 *Arguments     :void
 *Return        :void
 *Description	:In this function for Occlusion main frame
***************************************************************************/

void Occl_Frame(void)
{
	uint8_t occl_count = 0;
	Rectangle(0,36,320,169,MAIN_FRAME_COL);
	Rectangle(0,0,320,34,NEW_HDR_COL);
	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Occlusion");	// header
   	Rectangle_Line_function(1,2);

//	for(occl_count = 1; occl_count <=2 ; occl_count++)				//no of lines
//	{
//		Rectangle(7,34+(43*occl_count),290,0, BLACK);		// no of rect line
//	}

	Rectangle(0,206,320,34,NEW_FTR_COL);
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to edit",(uint8_t*)"OK",1,14);

}

/**************************************************************************
 *Function Name :void Occl_Opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
 *Arguments     :uint8_t page,uint8_t start_opt,uint8_t end_opt
 *Return        :void
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

void Occl_Opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
{
	uint16_t occl[3]={G_occl_unit,G_occl_level};
	uint16_t value = 0;
	uint32_t back_colour = 0;
	uint32_t text_colour = 0;
	uint8_t loop_count=0;

	for(loop_count=0;loop_count<=1;loop_count++)
	{
		if(loop_count == start_opt)
		{
			back_colour	= LIGHT_GRAY;
			text_colour = BLACK;
			TFT_ST7789V__rectangle_curve(3,35+(43*(start_opt)),41,290,0,back_colour);
		}
		else
		{
			back_colour	= MAIN_FRAME_COL;
			text_colour = WHITE;
		}

		value = occl[loop_count];

		Font_Select(ARIAL_14);
		TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE)
		,(uint8_t*)occl_menu[loop_count],back_colour,text_colour);

		TFT_String(180,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE)
		,(uint8_t*)":",back_colour,text_colour);

		TFT_String_align(190,280,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),(uint8_t *)occl_values[loop_count][value],0,back_colour,text_colour);

//		TFT_String(205,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
//		(uint8_t*)occl_values[loop_count][value],back_colour,text_colour);

		if(start_opt==1)
		{
			Font_Select(ARIAL_14);
			TFT_ST7789V__rectangle_curve(60,145,50,190,0,back_colour);

			TFT_String(94,160,(uint8_t*)unit_value[G_occl_unit][G_occl_level],back_colour, text_colour);//
			TFT_String(150,160,(uint8_t*)occl_values[0][G_occl_unit],back_colour, text_colour);//
		}
	}

}

/**************************************************************************
 *Function Name :void Occl_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[3])
 *Arguments     :uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[3]
 *Return        :void
 *Description	:In this function to change the current cursor position
***************************************************************************/

void Occl_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[3])
{
	uint8_t occlusion[3]={G_occl_unit,G_occl_level};
	uint8_t loop = 0;
	uint8_t opt_no  = 0;
	uint32_t back_colour = 0;
	uint32_t text_colour = 0;
	uint32_t back_colour1 = 0;
	uint32_t text_colour1 = 0;


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
		(uint8_t*)array[opt_no],back_colour,text_colour);

		TFT_String_align(190,280,INITIAL_TEXT_POS+((opt_no)*VER_TEXT_SPACE),(uint8_t *)occl_values[opt_no][occlusion[opt_no]],0,back_colour,text_colour);

//		TFT_String(205,INITIAL_TEXT_POS+((opt_no)*VER_TEXT_SPACE),
//		(uint8_t*)occl_values[opt_no][occlusion[opt_no]],back_colour,text_colour);

		TFT_String(180,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE)
		,(uint8_t*)":",back_colour,text_colour);
	}


	if(!opt_no)
		{
			back_colour1 = MAIN_FRAME_COL;
			text_colour1 = MAIN_FRAME_COL;
		}
		else
		{
			back_colour1 = LIGHT_GRAY;
			text_colour1 = BLACK;
		}

		TFT_ST7789V__rectangle_curve(60,145,50,190,0,back_colour1);

		TFT_String(94,160,(uint8_t*)unit_value[G_occl_unit][G_occl_level],back_colour1, text_colour1);//
		TFT_String(155,160,(uint8_t*)occl_values[0][G_occl_unit],back_colour1, text_colour1);//
}

/**************************************************************************
 *Function Name :void occl_subsetting(uint8_t option_no,uint8_t page_no, uint8_t INC_flag)
 *Arguments     :uint8_t option_no,uint8_t page_no, uint8_t INC_flag
 *Return        :void
 *Description	:In this function array arguments print as right side
***************************************************************************/

void occl_subsetting(uint8_t option_no, uint8_t INC_flag)
{

	uint8_t* occl_data[3] = {&G_occl_unit,&G_occl_level};
	uint8_t max_value[2] =  {3,9};
	uint8_t cur_value = 0;
	uint8_t pre_value = 0;

	cur_value	= *occl_data[option_no];

	pre_value	= cur_value;
	Font_Select(ARIAL_14);

	if(INC_flag)
	{
		if(cur_value < max_value[option_no])
		{
			cur_value++;
		}
		else
		{
			if(option_no==0)
		{
			cur_value=0;
		}
		else
		{
			cur_value=0;
		}
		}
	}
	else
	{
		if(cur_value)
		{
			cur_value--;
		}
		else
		{
			if(option_no==0)
			{
				cur_value=3;
			}
			else
			{
				cur_value=9;
			}
		}
	}

	if(pre_value != cur_value)
	{

	   Font_Select(ARIAL_14);
	   TFT_String_align(190,280,INITIAL_TEXT_POS+((option_no)*VER_TEXT_SPACE),(uint8_t *)occl_values[option_no][pre_value],0,LIGHT_GRAY,LIGHT_GRAY);

//		TFT_String(205,INITIAL_TEXT_POS+((option_no)*VER_TEXT_SPACE),
//		(uint8_t*)occl_values[option_no][pre_value],LIGHT_GRAY,LIGHT_GRAY);

	  //Font_Select(ARIAL_14);
	  TFT_String_align(190,280,INITIAL_TEXT_POS+((option_no)*VER_TEXT_SPACE),(uint8_t *)occl_values[option_no][cur_value],0,LIGHT_GRAY,BLACK);

//		TFT_String(205,INITIAL_TEXT_POS+((option_no)*VER_TEXT_SPACE),
//		(uint8_t*)occl_values[option_no][cur_value], LIGHT_GRAY,BLACK);
	}

	if(option_no)
	{
		TFT_String(94,160,(uint8_t*)unit_value[G_occl_unit][pre_value],LIGHT_GRAY,LIGHT_GRAY);
		TFT_String(94,160,(uint8_t*)unit_value[G_occl_unit][cur_value],LIGHT_GRAY,BLACK);
	}

	*occl_data[option_no] = cur_value;
}


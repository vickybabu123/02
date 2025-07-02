/**************************************************************************
 *File Name			:Main_menu.c
 *Description		:In this file have main menu settings functionality
 *Developed By		:7303
 *Version			:V1
***************************************************************************/

#include <TFT_Commands.h>
#include "LPC55S16.h"
#include "Shapes.h"
#include "Color.h"
#include "Keypad.h"
#include "TFT_String.h"
#include "Flowrate_Screen.h"
//#include "Brand.h"
#include "Drug_List.h"
#include "Occlusion.h"
#include "Bolus_Header.h"
#include "Power_off.h"
#include "Main_Menu.h"
#include"Driver_I2C.h"		//25-03
#include "Main_screen.h"
//#include "Last_infusion.h"
#include <Boot_up.h>
#include "Driver_Timer.h"
//#include "Bolus_Header.h"


/**************************************************************************
                          Global Variables
***************************************************************************/




uint8_t G_page=0;
uint8_t option=0;
//uint8_t G_bright_level=0;
//uint8_t G_sound_level=0;
//uint8_t G_device_info=0;
uint8_t edit_flag = 0;
uint8_t G_last_infusion=0;
uint8_t menu_brand_flag=0;
//uint8_t G_bolus_FR=0;
//uint8_t G_pro_name;
//uint8_t G_pro_model;
//uint8_t G_sw_version;
//uint8_t G_used_hrs;

uint32_t back_colour = 0;
uint32_t text_colour = 0;

extern uint8_t auto_lock_time;
extern uint8_t home_flag;
extern uint8_t ON_Flag;
extern uint16_t press_run_alarm;
extern uint8_t brand_power_flag;
extern uint8_t G_infusion_modes;
extern uint8_t siphonic_time;
extern uint8_t G_Fr_sound_flag;

void Menu_layout();

extern uint8_t infusion_mode_screen(uint8_t id);
extern uint8_t last_infused_data(uint8_t modes);
extern void Power_off();

extern uint16_t Pump_idle;



//const char* main_menu[3][4]={{"Syringe Brand","Occlusion","KVO","Bolus"},
//							 {"Drug Archive","Infusion mode","Event log","System Setting"},
//							 {"Device Setting"}};

const char* main_menu[3][4]={{"Bolus Setting","Occlusion Setting","Syringe Brand","Infused data clear"},
							 {"Drug Archive","KVO Setting","Event log","Infusion mode"},
							 {"System Setting","Device Setting"}};




/**************************************************************************
                            Functions Declaration
***************************************************************************/





/**************************************************************************
                            Functions Definations
***************************************************************************/

/**************************************************************************
 *Function Name :void Menu_layout()
 *Arguments     :void
 *Return        :void
 *Description	:In this function is menu layout of pages
***************************************************************************/

void Main_Menu_Screen()
{
	uint8_t page_no=0;
	uint8_t end_opt_no=0;
	uint8_t option_no=0;
	uint8_t prev_option = 0;
	uint8_t menu_variable=1;
//  uint8_t time_interval=30;
	uint8_t down_opt_arr[3]={3,3,2};
	uint8_t up_opt_arr[3][2]={	{3,3},
								{3,3},
								{1,1}
							 };
	auto_lock_time=AUTO_EXIT_TIME;
	end_opt_no=3;
	Pump_idle=10;
	home_flag=0;
    press_run_alarm=180;
    Pump_idle=10;
	POW.power_status_flag=1;
	G_Fr_sound_flag=0;

	while(KEY.value);
	while(menu_variable)
	{
		Power_off();
//		Font_Select(ARIAL_14);
//	    TFT_Number(50,70,G_infusion_modes,YELLOW,RED);
//		Font_Select(ARIAL_14);
//		TFT_Number(30,70,BATT.low,YELLOW,RED);

		if(!ON_Flag)
		{
			break; //26-03
		}

		else if(POW.power_status_flag)
		{
			home_flag=0;
			POW.power_status_flag=0;
			Main_Menu_Frame();
			Main_Menu_opt_Frame(page_no,option_no,end_opt_no);
			scroll_bar(page_no,option_no,10);//26-03
		}
			if(KEY.value)
			{
			 //while(KEY.value);
			   auto_lock_time=AUTO_EXIT_TIME;
			}
			if(!auto_lock_time)
			{
			  menu_variable=0;
//			  break;
			}

		switch(KEY.value)
		{

			case DOWN_KEY :

			 beep_sound();

			if(((page_no<=1)&&(option_no<3)) || ((page_no==2)&&(option_no<1)))
			{
				option_no++;
			}
			else
			{
				page_no++;
//				if(page_no==1)
//				{
//					option_no=0;
//					prev_option=0;
//					end_opt_no=3;
//				}
//				else if(page_no==2)
//				{
//					option_no=0;
//					prev_option=0;
//					end_opt_no=1;
//				}
//				else
//				{
//					option_no=0;
//					page_no=0;
//					prev_option=0;
//					end_opt_no=3;
//				}
				if(page_no>2)
				{
					page_no=0;
				}
				option_no=0;
				prev_option=option_no;
				end_opt_no=down_opt_arr[page_no];  //REW1

				Menu_layout();
				Main_Menu_opt_Frame(page_no,option_no,end_opt_no);
			}

			if(option_no!=prev_option)
			{
				Menu_cursor(prev_option,option_no,page_no,main_menu);
				prev_option = option_no;
			}
			scroll_bar(page_no,option_no,10);//23-03

			while(KEY.value);
			break;

			case UP_KEY:

		      beep_sound();

			if(option_no)
			{
				option_no--;
			}

			else
			{
				if(page_no)
				{
					page_no--;
//					option_no=3;
					prev_option=3;
//					end_opt_no=3;
				}

				else
				{
					page_no=2;
//					option_no=1;
					prev_option=1;
//					end_opt_no=1;
				}

				option_no=up_opt_arr[page_no][0];
				end_opt_no=up_opt_arr[page_no][1];

				Menu_layout();
				Main_Menu_opt_Frame(page_no,option_no,end_opt_no);

			}



			if(option_no!=prev_option)
			{
				Menu_cursor(prev_option,option_no,page_no,main_menu);
				prev_option = option_no;
			}

			scroll_bar(page_no,option_no,10);//23-03


			while(KEY.value);
			break;

			case OK_KEY:

			beep_sound();
			end_opt_no=3;
			G_last_infusion=1;
			menu_brand_flag=1;
			brand_power_flag=0;
			menu_fun(page_no,option_no);

			if(auto_lock_time)
			{
				POW.power_status_flag=1;
			}

			while(KEY.value);
			break;

			case BACK_KEY:
			beep_sound();
		    menu_variable=0;
		    siphonic_time=30;
	 		press_run_alarm=180;


			while(KEY.value);
			break;
		}
	}
}

/**************************************************************************
 *Function Name :void Menu_layout()
 *Arguments     :void
 *Return        :void
 *Description	:In this function is menu layout of pages
***************************************************************************/

void Menu_layout()
{
	uint8_t loop=0;
	Rectangle(3,36,300,169,MAIN_FRAME_COL);
	for(loop=1;loop<=3;loop++)
	{
		Rectangle(7,34+(43*loop),290,0, BLACK);
//		Rectangle(7,34+(43*2),290,0,BLACK);
//		Rectangle(7,34+(43*3),290,0,BLACK);
	}
}
/**************************************************************************
 *Function Name :void Main_Menu_Frame(void)
 *Arguments     :void
 *Return        :void
 *Description	:In this function for Main frame
***************************************************************************/

void Main_Menu_Frame(void)
{

	uint8_t menu_count = 0;
   	//Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
   	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Main   Menu");	// header

//	for(menu_count = 1; menu_count <=3 ; menu_count++)				//no of lines
//	{
//		Rectangle(7,34+(43*menu_count),290,0, BLACK);		// no of rect line
//	}
   	Rectangle_Line_function(1,3);
	TFT_ST7789V_lcd_shapes(38+163,38,300+15,306,LIGHT_GRAY_3);  	//Scroll bar                                                                                           //SCROLLING BOX OUTSIDE LAYER
	TFT_ST7789V_lcd_shapes(40+57,40,303+12,306,BLACK);
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to enter",(uint8_t*)"OK",2,14);

}

/**************************************************************************
 *Function Name :void Main_Menu_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
 *Arguments     :uint8_t page,uint8_t start_opt,uint8_t end_opt
 *Return        :void
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

void Main_Menu_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
{
	uint8_t loop_count=0;

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
		TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),(uint8_t*)main_menu[page][loop_count],back_colour,text_colour);

	}

}

/**************************************************************************
 *Function Name :void Menu_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[2][4])
 *Arguments     :uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[2][4]
 *Return        :void
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

void Menu_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[3][4])
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

		if((page==0)||(page==1)||((page==2)&&(opt_no<2)))
		{
			TFT_ST7789V__rectangle_curve(3,35+(43*(opt_no)),41,290,0,back_colour);

			Font_Select(ARIAL_14);

			TFT_String(9,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
			(uint8_t*)array[page][opt_no],back_colour,text_colour);
		}

	}
}

/**************************************************************************
 *Function Name :void menu_fun(uint8_t page_no ,uint8_t option_no)
 *Arguments     :uint8_t page_no ,uint8_t option_no
 *Return        :void
 *Description	:In this function for sub menu setting
***************************************************************************/

void menu_fun(uint8_t page_no ,uint8_t option_no)
{
	uint8_t (*fun_ar[3][4])()={ {Bolus_Screen,Occlusion_setting,Brand_List,last_infused_data},
						 	    {Dosage_setting,KVO_Screen,event_display,infusion_mode_screen},
							    {sys_sett_Screen,device_sett_Screen,0}
							  };  //25-03


	if((page_no==1)&&(option_no==1))
	{
		fun_ar[page_no][option_no](1);
	}

	else if((page_no==0)&&(option_no==3))
	{
		fun_ar[page_no][option_no](1);
	}
	else if((page_no==0)&&(option_no==2))
	{
		fun_ar[page_no][option_no](0);
	}
	else if((page_no==1)&&(option_no==3))
	{
		fun_ar[page_no][option_no](1);
	}
	else
	{
		fun_ar[page_no][option_no]();
	}

}

/**************************************************************************
 *Function Name :void edit_subsetting_frame(void)
 *Arguments     :void
 *Return        :void
 *Description	:In this function to change frame footer string
***************************************************************************/

void edit_subsetting_frame(void)
{
	Font_Select(ARIAL_14);
	Rectangle(0,206,320,34,NEW_FTR_COL);
	TFT_String(90,210,(uint8_t *)"change",NEW_FTR_COL,HDR_TXT_COL);
	TFT_String(220,210,(uint8_t *)"confirm",NEW_FTR_COL,HDR_TXT_COL);

	TFT_ST7789V_lcd_drawcircle1(20,223,15,MAIN_FRAME_COL,MAIN_FRAME_COL);    //	 Left Circle
	TFT_ST7789V_lcd_drawcircle1(60,223,15,MAIN_FRAME_COL,MAIN_FRAME_COL);    // Right Circle
	TFT_ST7789V_left_Right_arrow_14_arial(215,15,0,MAIN_FRAME_COL,WHITE);    //	Left Arrow
	TFT_ST7789V_left_Right_arrow_14_arial(215,59,1,MAIN_FRAME_COL,WHITE);    //	Right Arrow

	TFT_ST7789V_lcd_drawcircle1(190,223,15,MAIN_FRAME_COL,MAIN_FRAME_COL);
	Font_Select(ARIAL_9);
	TFT_String(182,218,(uint8_t*)"OK",MAIN_FRAME_COL,WHITE);
}



void Rectangle_Line_function(uint8_t start_point,uint8_t end_point)
{
	uint8_t menu_count=0;
	for(menu_count = start_point; menu_count <=end_point ; menu_count++)				//no of lines
		{
			Rectangle(7,34+(43*menu_count),290,0, BLACK);		// no of rect line
		}
}

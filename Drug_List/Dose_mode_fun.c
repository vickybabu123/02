#include "LPC55S16.h"
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
#include "Power_off.h"
#include <Boot_up.h>
#include "Driver_Timer.h"
char* modes_list[2][4]={{"All Drugs","Favourites","Recently Used","Custom Drug"},
		 	 	 	 	 {"Category"}};
extern char Drug_Names[150][4][20];

extern uint8_t custom_drug_List(void );
extern uint8_t category_screen(void);

extern uint8_t ON_Flag;
extern uint8_t self_option_flag;
extern uint8_t home_flag;
extern uint8_t auto_lock_time;  //ZOOZ_1
extern uint8_t G_bootup_flag;

extern uint8_t recent_drug_fun();
extern uint8_t favourite_func();

uint8_t Dosage_setting();
uint8_t Drug_fun(uint8_t page,uint8_t option_no);

void Drug_mode_fun(void);
void drug_mode_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page,  char* array[3]);
void drug_mode_Frame(void);
void drug_mode_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void Dosage_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page,  char* array[2][4]);

extern void Dosage_Frame(void);
extern void Dosage_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
extern void scroll_bar(uint8_t page_no,uint8_t option_no,uint8_t total_option);    //23-03                                  //(uint8_t prev_option, uint8_t curr_option, uint8_t page)
extern void beep_sound();

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t Drug_fun(uint8_t page,uint8_t option_no)
{
	uint8_t check_flag=0;
	uint8_t (*fun_array[2][4])()={{Drug_List,favourite_func,recent_drug_fun,custom_drug_List},
							   	   {category_screen}};
	check_flag=fun_array[page][option_no]();
	return check_flag;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t Dosage_setting()
{
	uint8_t page_no=0;
	uint8_t option_no=0;
	uint8_t prev_option = 0;
	uint8_t exit_flag=1;
	uint8_t edit_flag=0;
	uint8_t check_flag=0;
	uint8_t end_opt_no=3;
	uint8_t dosage_exit_flag=0;
	uint8_t total_option=5; // 22-03
	uint8_t down_opt_arr[3]={3,3,2};
	uint8_t up_opt_arr[2][2]= {	{3,3},
								{0,0},
							  };
	auto_lock_time=AUTO_EXIT_TIME;
//  uint8_t time_interval=30;//common_bug //ZOOZ_1

	home_flag=0;
	POW.power_status_flag=1;
//  auto_lock_time=30;//common_bug //ZOOZ_1

	while(KEY.value);
	while(exit_flag)
	{
		Power_off();

		if(!ON_Flag)
		{
			break;//26-03
		}

		else if(POW.power_status_flag)
		{
			POW.power_status_flag=0;//26-03
			Dosage_Frame();
			Dosage_opt_Frame(page_no,option_no,end_opt_no);
			scroll_bar(page_no,option_no,total_option);  //23-03
			while(KEY.value);//28-03//ZOOZ_1
		}

			if(KEY.value)//common_bug//ZOOZ_1
			{
			//	while(KEY.value);
				auto_lock_time=AUTO_EXIT_TIME;
			}

			 if(!auto_lock_time)
			{
				break;
			}//common_bug

		switch(KEY.value)
		{
		case DOWN_KEY :

			beep_sound();
			if(!edit_flag)
			{
				if( (page_no==0 && option_no<3)  )
				{
					option_no++;
					if(option_no!=prev_option)
					{
						Dosage_cursor(prev_option,option_no,page_no,modes_list);
						prev_option = option_no;
					}
				}

				else
				{
					page_no++;
//					if(page_no==1)
//					{
//						option_no=0;
//						prev_option=0;
//						end_opt_no=0;
//					}
//					else
//					{
//						option_no=0;
//						page_no=0;
//						prev_option=0;
//						end_opt_no=3;
//					}
					    if(page_no>1)
					    {
						  page_no=0;
					    }
					    option_no=0;
					    prev_option=option_no;
					    end_opt_no=down_opt_arr[page_no];  //REW1

						//Dosage_Frame();
					  CENTERSCR();
					  Rectangle_Line_function(1,3);
					  Dosage_opt_Frame(page_no,option_no,end_opt_no);

				}


						scroll_bar(page_no,option_no,5);//23-03
			}
				while(KEY.value);
				break;

		case UP_KEY:
			beep_sound();
			if(!edit_flag)
			{
				if((page_no==0 && option_no>0))
				{
					option_no--;
					if(option_no!=prev_option)
					{
						Dosage_cursor(prev_option,option_no,page_no,modes_list);
						prev_option = option_no;
					}
				}

				else
				{
					//page_no--;

					if(!page_no)
					{
						page_no++;
	//					option_no=0;
    // 					end_opt_no=0;
					}
					else
					{
						page_no--;
						prev_option=3;
//						option_no=3;
//						page_no=0;
//						end_opt_no=3;
					}
					option_no=up_opt_arr[page_no][0];
					end_opt_no=up_opt_arr[page_no][1];

						//Dosage_Frame();
					  CENTERSCR();
					  Rectangle_Line_function(1,3);
					  Dosage_opt_Frame(page_no,option_no,end_opt_no);
				}


						scroll_bar(page_no,option_no,5);//23-03
			}

					while(KEY.value);
					break;

		case OK_KEY:

			beep_sound();
			dosage_exit_flag=2;
			check_flag = Drug_fun(page_no,option_no);

			if(auto_lock_time)
			{
				POW.power_status_flag=1;
			}

			while(KEY.value);
			break;

			case BACK_KEY:

				beep_sound();
				dosage_exit_flag=0;
				exit_flag=0;

			while(KEY.value);
			break;

			}

		}
		return dosage_exit_flag;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Dosage_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page,  char* array[2][4])
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
			(uint8_t*)array[page][opt_no],back_colour,text_colour);

	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Dosage_Frame(void)
{

	uint8_t menu_count = 0;

	CENTERSCR();
	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Drug Archive");	// header


   	Rectangle_Line_function(1,3);

	TFT_ST7789V_lcd_shapes(38+163,38,300+15,306,LIGHT_GRAY_3);  	//Scroll bar                                                                                           //SCROLLING BOX OUTSIDE LAYER
	TFT_ST7789V_lcd_shapes(40+57,40,303+12,306,BLACK);

	Rectangle(0,206,320,34,NEW_FTR_COL);
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to confirm",(uint8_t*)"OK",2,14);

}

/**************************************************************************
 *Function Name :void Main_Menu_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
 *Arguments     :uint8_t page,uint8_t start_opt,uint8_t end_opt
 *Return        :void
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

void Dosage_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
{
	uint8_t loop_count=0;
    uint32_t back_colour = 0;
   	uint32_t text_colour = 0;

	for(loop_count=0;loop_count<=end_opt;loop_count++)
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

			Font_Select(ARIAL_14);
			TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),(uint8_t*)modes_list[page][loop_count],back_colour,text_colour);
	}

}

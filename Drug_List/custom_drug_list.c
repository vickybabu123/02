

#include "LPC55S16.h"		//22-03
#include "Color.h"
#include "keypad.h"
#include "Shapes.h"
#include "TFT_Commands.h"
#include "Driver_Timer.h"
#include "TFT_String.h"
#include <string.h>
#include "Driver_I2C.h"
#include "Power_off.h"
#include "Dosage_mode.h"
#include "Brand.h"
#include  "sound.h"
#include "Main_screen.h"
#include "Brand.h"
#include  "sound.h"
#include <Boot_up.h>

void custom_List_layout ();
void custom_drug_Frame();
void custom_drug_List_option(uint8_t page,uint8_t starting_count,uint8_t Final_count);
void custom_list_option_scroll(uint8_t prev_option,uint8_t curr_option,uint8_t page);//, char array[150][4][15])

extern void add_data_base(uint8_t ID_flag,uint16_t brand_sel_no);
extern char Drug_Names[150][4][20];
extern uint8_t auto_lock_time;  //ZOOZ_1
extern uint8_t ON_Flag;

uint8_t current_cus_option=4;
uint8_t custom_drug_count=0;

uint16_t custom_set(uint8_t total_option);
uint16_t custom_new_no=0;
uint16_t total_drugs=500;
uint16_t default_drug_count=500;
uint16_t drug_variable=0;
uint16_t drug_select_no=0;

 /****************************************************************************
 * Function Name :
 * Arguments     :
 * Return type   :
 * Description   :

 *****************************************************************************/

uint8_t  custom_drug_List(void )
{
	uint8_t prev_option = 0;
	uint8_t option_number=0;
	uint8_t max_option=0;
	uint8_t end_count=0;
	uint8_t start_count=0;
	uint8_t custom_drug_variable=1;
	uint8_t scroll_bar_lt=0;
	uint8_t  check_flag=0;

	uint16_t max_pageout=0;
	uint16_t page_no=0;

	POW.power_status_flag=1;//27-03

	custom_drug_count=total_drugs-default_drug_count;

	max_pageout=(total_drugs-default_drug_count)/4;

	max_option=(total_drugs-default_drug_count)%4;


	if(page_no==max_pageout)
	{
		end_count=max_option;
	}
	else
	{
		end_count=3;
	}

	POW.power_status_flag=1; //27-03     //ZOOZ_1
	auto_lock_time=AUTO_EXIT_TIME;//common_bug

	while(KEY.value);
	while(custom_drug_variable)
	{
		Power_off();

		if(!ON_Flag)
		{
			break;//26-03
		}

		else if(POW.power_status_flag)//27-03
		{
			POW.power_status_flag=0;//26-03
			custom_drug_Frame();
			custom_drug_List_option(page_no+125,option_number,end_count);

			if(max_pageout) //27-03
			{
				if(total_drugs<600)
				{
					scroll_bar_lt=total_drugs-default_drug_count+1;
				}
				else
				{
					scroll_bar_lt=total_drugs-default_drug_count;
				}
				scroll_bar(page_no,option_number,scroll_bar_lt);
			}
		}

				if(KEY.value)     //ZOOZ_1
				{
				//  while(KEY.value);
					auto_lock_time=AUTO_EXIT_TIME;//common_bug
				}
				else if(!auto_lock_time)
				{
					custom_drug_variable=0;
					break;
				}//common_bug

		switch(KEY.value)
		{
		case OK_KEY:
			beep_sound();  //ZOOZ_1
			custom_new_no=custom_set((page_no*4)+option_number);

			if(custom_new_no<total_drugs)
			{
				dose.drug_select_no=custom_new_no;
				recently_used_fun(dose.drug_select_no);
				custom_drug_variable = 0;
				check_flag=1;
			}

			else
			{
				if(custom_new_no>=500)
				{
					add_data_base(0,custom_new_no);//ZOOZ_2
					if(auto_lock_time)
					{
						POW.power_status_flag=1;
					}
					start_count=custom_new_no%4;
					custom_drug_count=total_drugs-default_drug_count;
					max_pageout=(total_drugs-default_drug_count)/4;
					max_option=(total_drugs-default_drug_count)%4;

					if(page_no==max_pageout)
					{
						end_count=max_option;
					}
					else
					{
						end_count=3;
					}
					option_number = custom_new_no%4;
					//POW.power_status_flag=1;//27-03
				}

			}

			while(KEY.value);
			break;
			case  MUTE_KEY://ZOOZ_2

				beep_sound();
				custom_new_no=custom_set((page_no*4)+option_number);

				if((custom_new_no>=500)&& (custom_new_no <total_drugs))
				{
					add_data_base(0,custom_new_no);
					max_pageout=(total_drugs-default_drug_count)/4;
					max_option=(total_drugs-default_drug_count)%4;
					option_number = custom_new_no%4;
					POW.power_status_flag=1;//26-03
				}

			while(KEY.value);
			break;

			case DOWN_KEY:

				beep_sound();

				if(((option_number<3)&&(page_no<max_pageout))||(option_number<max_option))
				{
					option_number++;
				}
				else
				{
					if(page_no<max_pageout)
					{
						page_no++;
					}
					else
					{
						page_no=0;
					}

					option_number=0;
					prev_option=option_number;
					start_count=option_number;

						if(page_no==max_pageout)
						{
							end_count=max_option;
						}

						else
						{
							end_count=3;
						}

							brand__drug_split_screen(max_pageout);
							custom_drug_List_option(page_no+125,start_count,end_count);
				}

				if(option_number!=prev_option)
				{
					custom_list_option_scroll(prev_option,option_number,page_no+125);//,Drug_Names);

					if(max_pageout)
					{
						scroll_bar(page_no,option_number,scroll_bar_lt);
					}
					prev_option = option_number;
				}

				if(max_pageout)
				{
				  scroll_bar(page_no,option_number,scroll_bar_lt);//23-03
				}

			while(KEY.value);
			break;


			case UP_KEY:

				beep_sound();

				if(option_number>0)
				{
					option_number--;
				}

				else
				{
					if(page_no>0)
					{
						page_no--;
						option_number=3;
					}

					else
					{
						page_no=max_pageout;
						option_number=max_option;
					}

						prev_option=option_number;
						start_count=option_number;
						end_count=option_number;

						brand__drug_split_screen(max_pageout);
						custom_drug_List_option(page_no+125,start_count,end_count);
				}

						if(option_number!=prev_option)
						{
							custom_list_option_scroll(prev_option,option_number,page_no+125);//,Drug_Names);
							prev_option = option_number;
						}

						if(max_pageout)
						{
							scroll_bar(page_no,option_number,scroll_bar_lt);//23-03
						}
			while(KEY.value);
			break;


			case BACK_KEY:

			beep_sound();
			custom_drug_variable=0;
		//	Rectangle(3,36,300,169,MAIN_FRAME_COL);
			check_flag=0;

			while(KEY.value);
			break;

		}
	}

return   check_flag;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint16_t custom_set(uint8_t total_option)
{
	uint16_t customno=0;
	customno=((4*125)+total_option);				//125*4=500+0
	return customno;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void custom_list_option_scroll(uint8_t prev_option,uint8_t curr_option,uint8_t page)//, char array[150][4][15])
 {
	uint32_t back_colour = 0;
    uint32_t text_colour = 0;
	uint8_t loop		 = 0;
	uint8_t opt_no		 = 0;
	uint32_t fav_star_colour=0;

	for(loop = 0; loop<2; loop++)
	{
		if(!loop)
		{
			back_colour     = MAIN_FRAME_COL;
			text_colour 	= WHITE;
			fav_star_colour =GOLD;
			opt_no			= prev_option;
		}
		else
		{
			back_colour   = LIGHT_GRAY;
			text_colour   = BLACK;
			fav_star_colour=MAIN_FRAME_COL;
			opt_no		  = curr_option;
    	}

		TFT_ST7789V__rectangle_curve(3,35+(43*(opt_no)),41,290,0,back_colour);
		Font_Select(ARIAL_14);
	    TFT_String(9,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),(uint8_t*)Drug_Names[page][opt_no],back_colour,text_colour);

	    if(dose.drug_select_no==((page*4)+opt_no)  )
		{
		  TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS)+(opt_no)*VER_TEXT_SPACE_1,250,0,back_colour,fav_star_colour);
		}//ZOOZ_2

	}
 }

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void custom_drug_Frame(void)
{
	uint8_t custom_count = 0;

//	Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	Rectangle(0,0,320,34,NEW_HDR_COL);

	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Custom Drug");	// header

//	for(custom_count = 1; custom_count <=3 ; custom_count++)				//no of lines
//	{
//		Rectangle(7,34+(43*custom_count),290,0, BLACK);		// no of rect line
//	}
   	Rectangle_Line_function(1,3);


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

void custom_drug_List_option(uint8_t page,uint8_t starting_count,uint8_t Final_count)
{
	uint8_t loop_count=0;
	uint32_t back_colour = 0;
	uint32_t text_colour = 0;
    uint32_t fav_star_colour=0;

	for(loop_count=0;loop_count<=Final_count;loop_count++)
	{
		if(loop_count == starting_count)
		{

			back_colour	= LIGHT_GRAY;
			text_colour=  BLACK;
			fav_star_colour=MAIN_FRAME_COL;
			TFT_ST7789V__rectangle_curve(3,35+(43*(starting_count)),41,290,0,back_colour);

		}

		else
		{

			back_colour	= MAIN_FRAME_COL;
			text_colour = WHITE;
			fav_star_colour=GOLD;

		}



		Font_Select(ARIAL_14);
		TFT_String(10,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE_1),
		(uint8_t*)Drug_Names[page][loop_count],back_colour,text_colour);

		if(dose.drug_select_no==((page*4)+loop_count) )//ZOOZ_1
		 {
			 TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS)+(loop_count)*VER_TEXT_SPACE_1,250,0,back_colour,fav_star_colour);
		 }
	}
}


#include "LPC55S16.h"
#include "stdio.h"
#include "stdint.h"
#include "Color.h"
#include "keypad.h"
#include "Shapes.h"
#include "fsl_clock.h"
#include "Driver_I2C.h"
#include "TFT_Commands.h"
#include "Power_off.h"
#include "sound.h"
#include "Main_screen.h"
#include "Brand.h"
#include "Driver_Timer.h"
#include "Boot_up.h"
vanakam mapla
/**********************************************************************************
 *                         global_variable
***********************************************************************************/



uint8_t page_no=0;
uint8_t gain_flag;
uint8_t brand;
uint8_t current_option=4;
uint8_t ret_data=0;
uint16_t new_brnd=0;
uint8_t page=0;
uint8_t total_brand=8;
uint8_t brand_select_no=0;
uint8_t brand_select_home=0;
uint8_t prev_brand_select_no=0;//ZOOZ_2

 /**********************************************************************************
                          extern_variable
 ***********************************************************************************/


extern  char Brand_Names[6][4][15];
extern char brand_list[17];
extern uint32_t back_colour;
extern uint32_t text_colour;
extern char add_data1[15];
extern uint8_t add_enter_flag;
extern void add_brand(uint8_t brand_sel_no);
extern uint8_t option_no;
extern uint8_t auto_lock_time;    //ZOOZ_1
extern uint8_t home_flag;
extern uint8_t G_last_infusion;
extern uint8_t brand_power_flag;
extern uint8_t menu_brand_flag;
extern uint8_t G_Long_press_back;
extern uint8_t G_Brand_back_flag;
extern volatile uint8_t Confirm_count;

extern void EEPROM_SD_READ(void);
extern void Pressure_EEPROM_read();



 /**************************************************************************
                             Functions Call
 ***************************************************************************/


uint8_t Brand_List(uint8_t id_flag);
uint16_t brand_set(uint8_t total_option,uint8_t page_no,uint8_t option_no);
int branddisplay(uint8_t brand_update_no );
void brand__drug_split_screen(uint8_t page_no);



/**************************************************************************
                       extern Functions Call
 ***************************************************************************/

extern void Brand_list_option_scroll(uint8_t prev_option,uint8_t curr_option,uint8_t page, const char array[6][4][15]);
extern void Brand_List_layout (void);
extern void  Brand_List_option(uint8_t page,uint8_t Initial_count,uint8_t Final_count);
extern void Brand_Columns(void);
//extern uint32_t EEPROM_dataread(uint16_t addrs, uint16_t byte_val);
//extern uint32_t EEPROM_datawrite(uint16_t addrs, uint32_t data, uint16_t bytes_val);
extern void TFT_Number(uint16_t xpos,uint16_t ypos,uint32_t number,uint32_t boarder_color,uint32_t fill_color);
extern void Font_Select(uint8_t Font_Size);

extern uint8_t ON_Flag;

uint8_t G_bootup_flag;
extern uint8_t TFT_ST7789V_tick_symbol_14pt(uint16_t xpos, uint16_t ypos,    //22-03
       uint8_t arrow, uint32_t boarder_color, uint32_t fill_color);//ZOOZ_2
extern void add_data_base (uint8_t ID_flag,uint16_t db_sel_no);
extern void SL_EEPROM_read();

/**************************************************************************
                               Function
***************************************************************************/

/*-------------------------------------------------------------
 * Function_name:Brandlist
 * Arguments    :void
 * return       :void
 * Description  :over all brand inc/dec fun based on page number
---------------------------------------------------------------*/


uint8_t Brand_List(uint8_t id_flag)
{

	uint8_t prev_option = 0;
	uint8_t Brand_variable =1;
	uint8_t page_no=0;
	uint8_t option_no=0;
	uint8_t scroll_bar_lt=0;
	uint8_t end_opt_no=3;
	uint16_t max_page=0;
	uint16_t max_option=0;
	uint8_t skip_count=0;
    uint8_t brand_exit_flag=0;
    uint8_t brand_new_no=0;
    uint8_t loop_count=0;
    uint8_t brand_display_hm=0;


    uint8_t down_opt_arr[3]={3,3,2};

    uint8_t up_opt_arr[3][2]={	{3,3},
    							{3,3},
    							{1,1}
    						 };

    auto_lock_time=AUTO_EXIT_TIME;
	char* add_data3="(+).Add Brand";

    if(total_brand<=19)		//22-03
	{
		 for(loop_count=0;loop_count<15;loop_count++)//22-03
		 {
			Brand_Names[total_brand/4][total_brand%4][loop_count]=add_data3[loop_count];
		 }
	}

	if(!id_flag)
	{
		if(total_brand<20)
		{
			skip_count=1;
		}

		else
		{
			skip_count=0;
		}

	}
	else
	{
		skip_count=0;
	}

	max_page=(total_brand-skip_count)/4;
	max_option=(total_brand-skip_count)%4;
	home_flag=0;
	POW.power_status_flag=1;//26-03
	brand_new_no=brand_select_no;
	brand_display_hm=brand_new_no;

	while(KEY.value);

	while(Brand_variable)
	{
//		if ((!menu_brand_flag) && (!brand_power_flag))
//		{
		  Power_off();
//		}

		if(!ON_Flag)
		{
			break;//26-03
		}

		else if(POW.power_status_flag)
		{

			POW.power_status_flag=0;                   //26-03



			Brand_List_layout();
			Brand_List_option(page_no,option_no,end_opt_no);

			if(max_page)
			{

				if(total_brand<20)
				{
					scroll_bar_lt=total_brand+1;
				}

				else
				{
					scroll_bar_lt=total_brand;
				}
				scroll_bar(page_no,option_no,scroll_bar_lt);//23-03

			}
		}

		if(KEY.value)//common_bug//ZOOZ_1
		{
			auto_lock_time=AUTO_EXIT_TIME;
		}

		if((!auto_lock_time) && (G_last_infusion))
		{
			G_last_infusion=0;
			Brand_variable=0;
		}

switch(KEY.value)
{

	case OK_KEY:

		beep_sound();
		brand_new_no=brand_set(current_option,page_no,option_no);

//		Font_Select(ARIAL_14);
//		TFT_Number(100,70,brand_new_no,YELLOW,RED);
//		delay_secs(3);

		if(brand_new_no<total_brand)
		{
			if(!id_flag)
			{
				brand_select_no = brand_new_no;
			}
			else
			{
				brand_select_no=brand_display_hm;
			}

			EEPROM_datawrite(EEPROM_BRAND_NO,brand_select_no,1);
			EEPROM_SD_READ();
			SL_EEPROM_read();
			Pressure_EEPROM_read();

			if(!id_flag)
			{
				if(prev_brand_select_no!=brand_select_no)
				{
					prev_brand_select_no=brand_select_no;
				}
			}
			Brand_variable = 0;
			brand_exit_flag=1;
		}

		else
		{
			if((page_no==max_page) && (total_brand<=20))
			{
				if((option_no==max_option))
				{
					add_data_base(1,brand_new_no);//ZOOZ_2
					max_page =(total_brand)/4;
					max_option =(total_brand)%4;
				//	option_no  = total_brand/4;
					option_no = brand_new_no%4;
					end_opt_no = (total_brand)%4;

//					Font_Select(ARIAL_14);
//					TFT_Number(290,50,end_opt_no,NAVY,WHITE);

					if((page_no==4)&&(end_opt_no==3)||(!end_opt_no))
					{
						page_no++;
					}

					if(page_no==5)
					{
						page_no=0;
						option_no=0;
						prev_option=0;

					}


					if((page_no<=4) && (option_no==3))
					{
						option_no=0;
						prev_option=0;
					}

					POW.power_status_flag=1;//26-03
				}
			}

		}
		while(KEY.value);
		break;

	case START_STOP_KEY:

		beep_sound();

		brand_new_no=brand_set(current_option,page_no,option_no);
		if(brand_new_no<total_brand)
		{
			brand_select_no = brand_new_no;
			Brand_variable = 0;
		}
		else
		{
			if((brand_new_no>=8))
			{
				if(option_no!=max_option)
				{
//					add_data_base(1,brand_new_no);//ZOOZ_2
					max_page=(total_brand)/4;
					max_option=(total_brand)%4;
					option_no = brand_new_no%4;

					POW.power_status_flag=1;//26-03
				}
			}
		}

		while(KEY.value);
		break;

case DOWN_KEY:

	beep_sound();
	if(((option_no<3)&&(page_no<max_page))||(option_no<max_option))
	{
		option_no++;
	}

	else
	{

		if(page_no<max_page)
		{
			page_no++;
		}
		else
		{
			page_no=0;
		}



		if(page_no==max_page)			////18_3
		{
			//end_opt_no=down_opt_arr[page_no];
			end_opt_no = (total_brand - skip_count)%4;
		}
		else
		{
			end_opt_no= 3;	//down_opt_arr[page_no];
		}

		option_no=0;
		prev_option=0;
		brand__drug_split_screen(page_no);
		Brand_List_option(page_no,option_no,end_opt_no);
	//  POW.power_status_flag=1;
	}


	if(option_no!=prev_option)
	{
		Brand_list_option_scroll(prev_option,option_no,page_no,Brand_Names);
		if(max_page)
		{
		}
		prev_option = option_no;
	}

//	Font_Select(ARIAL_14);
////    TFT_Number(40,70,total_brand,YELLOW,RED);
//	TFT_Number(50,110,page_no,YELLOW,RED);

	scroll_bar(page_no,option_no,scroll_bar_lt);

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
			  option_no=3;
			}
			else
			{
			  page_no=max_page;
			  option_no=max_option;
			}

			end_opt_no=option_no;
			prev_option=option_no;

			brand__drug_split_screen(page_no);
			Brand_List_option(page_no,option_no,end_opt_no);

		}


		if(option_no!=prev_option)
		{

			Brand_list_option_scroll(prev_option,option_no,page_no,Brand_Names);

			if(max_page)
			{
			}

			prev_option = option_no;
		}
		scroll_bar(page_no,option_no,scroll_bar_lt);

//		Font_Select(ARIAL_14);
//		TFT_Number(50,110,page_no,YELLOW,RED);

		while(KEY.value);
		break;

	case BACK_KEY:

		if((!G_bootup_flag) && (!G_Brand_back_flag))
		{

			beep_sound();
			Brand_variable=0;
			option_no=0;
			page_no=0;
			brand_exit_flag=0;
			while(KEY.value);
			break;

		}


	}

	}
	return brand_exit_flag;

}


/*------------------------------------
 * Function_name:Brandset
 * Arguments    :No of option per page
 * return       :Brandno
 * Description  :Able to return brandno
-------------------------------------- */

uint16_t brand_set(uint8_t total_option,uint8_t page_no,uint8_t option_no)
{
	uint16_t brandno=0;
	brandno=(page_no*4)+option_no;
	return brandno;
}

/*------------------------------------------------------
 * Function_name:Brand_drug_split_screen

 * Arguments    :void
 * return       :void
 * Description  :Able to split the screen based on width
-------------------------------------------------------- */
void brand__drug_split_screen(uint8_t page_no)
{
	 uint8_t loop=0;
	 CENTERSCR();
	// Rectangle(3,36,300,169,MAIN_FRAME_COL);//blue background

	for(loop=1;loop<=3;loop++)
	{
		 Rectangle(7,34+(43*loop),290,0, BLACK);//line seperation black
	}

//	 Rectangle(7,34+(43*1),290,0, BLACK);//line seperation black
//	 Rectangle(7,34+(43*2),290,0,BLACK);//line seperation black
//	 Rectangle(7,34+(43*3),290,0,BLACK);//line seperation black

}


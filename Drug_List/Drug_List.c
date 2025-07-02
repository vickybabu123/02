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
#include "Dosage_mode.h"
#include "Driver_Timer.h"
#include "Power_off.h"
#include "sound.h"


extern uint8_t total_recent;	//22-03
extern uint8_t G_bootup_flag;
extern uint16_t total_drugs;
extern uint8_t ON_Flag;
extern uint8_t auto_lock_time;//ZOOZ_1
extern uint8_t G_Long_press_back;
extern uint8_t G_infusion_modes;

extern uint8_t Drug_name_search();

extern void recent_eeprom_write(void);//29-03
extern void fav_eeprom_write(void);//29-03
extern void Drug_search_List_layout();
extern void scroll_bar(uint8_t page_no,uint8_t option_no,uint8_t total_option);     //23-03                                  //(uint8_t prev_option, uint8_t curr_option, uint8_t page)

/**********************************************************************************
 *                         global_variable
***********************************************************************************/

uint8_t page_no_1=0;
uint8_t gain_flag_1=0;
uint8_t drug=0;
uint8_t drugno=0;
uint8_t current_option_1=4;
uint8_t drugno;
uint8_t drug;
uint16_t drug_new_no=0;	//22-03
uint8_t G_serial_key=0;

/**********************************************************************************
 *                         extern_variable
***********************************************************************************/

extern  char Drug_Names[150][4][20];
extern char* Drug_list[20];
extern uint8_t fav_check[600];
extern uint8_t total_fav;


/**************************************************************************
                            Functions Call
***************************************************************************/

/**************************************************************************
                           extern Functions Call
***************************************************************************/
extern void navigation_for_drug_search();
extern void brand__drug_split_screen(void);
extern void Drug_List_layout ();
extern void drug_List_option(uint16_t page,uint8_t starting_count,uint8_t Final_count);
extern void Rectangle(uint16_t x_axis,uint16_t y_axis,uint16_t Length,uint16_t Height,uint32_t Color);

extern uint8_t recently_used_fun(uint16_t drug_no);	//22-03
extern uint8_t favourite_functionality(uint16_t drug_no,uint8_t pos);
extern uint8_t TFT_ST7789V_star_14(uint16_t xpos, uint16_t ypos,
       uint8_t arrow, uint32_t boarder_color, uint32_t fill_color) ;
extern uint8_t TFT_ST7789V_tick_symbol_14pt(uint16_t xpos, uint16_t ypos,    //22-03
	   uint8_t arrow, uint32_t boarder_color, uint32_t fill_color);//ZOOZ_2
/**************************************************************************
                               Function
***************************************************************************/

/*------------------------------------
 * Function_name:drugset
 * Arguments    :No of option per page
 * return       :drugno
 * Description  :Able to return drugno
-------------------------------------- */

uint16_t fixed_value(uint8_t total_option,uint8_t page_no,uint8_t option_no )
{
	uint16_t value=0;
	value=(page_no*4)+option_no;
	return value;
}

/*-------------------------------------------------------------
 * Function_name:druglist
 * Arguments    :void
 * return       :void
 * Description  :over all brand inc/dec fun based on page number
---------------------------------------------------------------*/

uint8_t Drug_List(void )
{
    uint16_t page_no=0;				//ZOOZ_2
    uint8_t option_no=0;
    uint8_t end_opt_no=3;
	uint8_t prev_option = 0;
	uint8_t Drug_variable=1;
	uint8_t check_flag=0;
	uint16_t max_page=0;
	uint16_t max_option=0;

	max_page=(total_drugs-1)/4;
	max_option=(total_drugs-1)%4;

	POW.power_status_flag=1;
	auto_lock_time=AUTO_EXIT_TIME;	//common_bug//ZOOZ_1

		while(KEY.value);

		while(Drug_variable)
		{
			Power_off();

			if(!ON_Flag)
			{
				break;//26-03
			}

			else if(POW.power_status_flag)
			{
				POW.power_status_flag=0;//26-03
				Drug_search_List_layout();	//22-03
				drug_List_option(page_no,option_no,end_opt_no);
				scroll_bar(page_no,option_no,total_drugs);//27-03
			}

			if(KEY.value)//common_bug//ZOOZ_1
			{
			//	while(KEY.value);
				auto_lock_time=AUTO_EXIT_TIME;
			}

			else if(!auto_lock_time)
			{
				break;
			}//c

			switch(KEY.value)
			{

			case DOWN_KEY:                     // TARGET :
				beep_sound();

				if(((option_no<3)&&(page_no<max_page))||(option_no<max_option))
				{
					option_no++;
				}

				else
				{
					if(page_no<max_page)		//124 --Dhaya
					{
						page_no++;
					}

					else
					{
						page_no=0;
					}

						if(page_no==max_page)
						{
							end_opt_no=max_option;
						}

						else
						{
							end_opt_no=3;
						}

							option_no=0;
							prev_option=0;
							brand__drug_split_screen();
							drug_List_option(page_no,option_no,end_opt_no);
				}

				if(option_no!=prev_option)
				{
					drug_list_option_scroll(prev_option,option_no,page_no);//,Drug_Names);
					prev_option = option_no;//1
				}

				scroll_bar(page_no,option_no,total_drugs);//23-03
				G_serial_key=20;

				while((KEY.value) && (G_serial_key));//22-03
				break;

			case UP_KEY:						//RUN_STOP:
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

					brand__drug_split_screen();
					drug_List_option(page_no,option_no,end_opt_no);
				}

						if(option_no!=prev_option)
						{
								drug_list_option_scroll(prev_option,option_no,page_no);//,Drug_Names);
								prev_option = option_no;//1
						}
						scroll_bar(page_no,option_no,total_drugs);//23-03
						G_serial_key=20;

						scroll_bar(page_no,option_no,total_drugs);//23-03

				while((KEY.value) && (G_serial_key));	//22-03
				break;


			case  OK_KEY:  					//SET:
				beep_sound();

				if((option_no!=0) || (page_no!=0))
				{
					TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS+((dose.drug_select_no%4)*VER_TEXT_SPACE_1)),250,0,MAIN_FRAME_COL,MAIN_FRAME_COL);//ZOOZ_2
					dose.drug_select_no=fixed_value(current_option_1,page_no,option_no);		//current_option_1);
					TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS)+((option_no)*VER_TEXT_SPACE_1),250,0,LIGHT_GRAY,MAIN_FRAME_COL);//ZOOZ_2
					recently_used_fun(dose.drug_select_no);
				}
				// if(G_Long_press_back==1)
				// {
					// G_infusion_modes=3;
				// }
				Drug_variable=0;
				check_flag=2;

				while(KEY.value);
				break;

			case BOLUS_KEY:	//22-03

				check_flag=Drug_name_search();
				if(check_flag && G_bootup_flag)
				{
					Drug_variable=0;
				}

				else
				{
					page_no=dose.drug_select_no/4;
					option_no=dose.drug_select_no%4;
					end_opt_no=3;
					prev_option=option_no;
					POW.power_status_flag=1;
				}
				while(KEY.value);
				break;

			case BACK_KEY:
			beep_sound();

			Drug_variable=0;
			option_no=0;
			page_no=0;
			check_flag=0;

			while(KEY.value);
			break;

			case MUTE_KEY:////27-03//due to mute key issue start stop key in used

				beep_sound();
				drug_new_no=fixed_value(current_option_1,page_no,option_no);

//				Font_Select(ARIAL_12);
//				TFT_Number(50,70,drug_new_no,YELLOW,RED);
//				TFT_Number(50,90,total_fav,YELLOW,RED);

//				if( (total_fav<=20))
//				{
					if((option_no!=0) || (page_no!=0))
					{
						favourite_functionality(drug_new_no,((page_no*4)+option_no));
					}
			//	}
//
//				else
//				{
//					WARN_SOUND(1,1,2);
//				}
				while(KEY.value);
				break;
			}
		}
		
		//fav_eeprom_write();//29-03
		//recent_eeprom_write();
		return check_flag;
}


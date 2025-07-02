/*
 * Rec_drug_list.c
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
#include "Power_off.h"
#include "Dosage_mode.h"
#include "sound.h"
#include "Brand.h"

char recent_drug_list[5][4][20];

uint8_t total_recent=0;
uint16_t drug_num[11];

extern char Drug_Names[150][4][20];

extern uint8_t auto_lock_time;//common_bug  //ZOOZ_1
extern uint8_t ON_Flag;

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t recent_drug_fun(void)
{
	uint8_t page_no=0;
	uint8_t option_no=0;
	uint8_t end_opt_no=3;
	uint8_t prev_option = 0;
	uint8_t exit_flag=1;
	uint8_t  max_rec_page=0;
	uint8_t  max_rec_opt=0;
	uint8_t  check_flag=0;
//	uint8_t time_interval=30;//common_bug    //ZOOZ_1
//	uint8_t edit_flag=0;
	auto_lock_time=AUTO_EXIT_TIME;


	if(!total_recent)
	{
		 recent_drug_Frame();//ZOOZ_2
		 TFT_ST7789V__rectangle_curve(30,65,110,255,0,LIGHT_GRAY);
		 Font_Select(ARIAL_14);
		 TFT_String_align(65,240,110,(uint8_t *)"No Recents",0,LIGHT_GRAY,BLACK);
		// TFT_String(85,110,(uint8_t *)"No Recents",LIGHT_GRAY,BLACK);
		 delay_secs(2);
		 exit_flag=0;
	}

	else
	{
		if(page_no<total_recent/4)
		{
			end_opt_no=3;
		}
		else
		{
			end_opt_no=((total_recent-1)%4);
		}

		max_rec_page=(total_recent-1)/4;
		max_rec_opt=(total_recent-1)%4;
		POW.power_status_flag=1;//27-03
	}
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
					recent_drug_Frame();//27-03
					recent_opt_Frame(page_no,option_no,end_opt_no);
					if(max_rec_page)
					{
					  scroll_bar(page_no,option_no,total_recent);//23-03
					}
			    }

				if(KEY.value)//common_bug   //ZOOZ_1
				{
					auto_lock_time=AUTO_EXIT_TIME;
				}

				if(!auto_lock_time)
				{
					exit_flag=0;
				}

				switch(KEY.value)
				{

				    case DOWN_KEY :   //DOWN_KEY

					beep_sound();
						if((option_no<3 && page_no<max_rec_page) || (option_no <max_rec_opt))
						{
							option_no++;
						}


						else //if(max_rec_page>=1)//22-03
						{

								if(page_no<max_rec_page)
								{
									page_no++;
								}
								else
								{
									page_no = 0;
								}



									if(page_no== max_rec_page)
									{
										end_opt_no = max_rec_opt;
									}
									else
									{
										end_opt_no = 3;
									}
									option_no = 0;
									prev_option = option_no;


									brand__drug_split_screen(page_no);
									recent_opt_Frame(page_no,option_no,end_opt_no);
						}

						if(option_no!=prev_option)
						{
							recent_cursor(prev_option,option_no,page_no,recent_drug_list);
							prev_option = option_no;
						}

						if(max_rec_page)
						{
							scroll_bar(page_no,option_no,total_recent);//23-03
						}

						while(KEY.value);
						break;



						case UP_KEY:
							beep_sound();
							if(option_no>0)
							{
								option_no--;
							}

							else
							{
								if(page_no)
								{
									page_no--;
								}
								else
								{
									page_no = max_rec_page;
								}



								if(page_no== max_rec_page)
								{
									end_opt_no = max_rec_opt;
								}
								else
								{
									end_opt_no = 3;
								}
									option_no = end_opt_no;
									prev_option = option_no;


									brand__drug_split_screen(page_no);
									recent_opt_Frame(page_no,option_no,end_opt_no);
							}

							if(option_no!=prev_option)
							{
								recent_cursor(prev_option,option_no,page_no,recent_drug_list);
								prev_option = option_no;//1
							}

							if(max_rec_page)
							{
								scroll_bar(page_no,option_no,total_recent);//23-03
							}


						while(KEY.value);
						break;

					case OK_KEY: 					 //OK_KEY

						beep_sound();
						if((option_no!=0) || (page_no!=0))
						{
							TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS+((dose.drug_select_no%4)*VER_TEXT_SPACE_1)),250,0,MAIN_FRAME_COL,MAIN_FRAME_COL);
							dose.drug_select_no=drug_num[((page_no*4)+option_no)];
							TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS)+((option_no)*VER_TEXT_SPACE_1),250,0,LIGHT_GRAY,GOLD);
							recently_used_fun(dose.drug_select_no);
							exit_flag=0;
							check_flag=1;
						}
						while(KEY.value);
						break;


					case BACK_KEY: 					 //BACK_KEY

						beep_sound();
						exit_flag=0;
						check_flag=0;
					//	Rectangle(3,36,300,169,MAIN_FRAME_COL);

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

uint8_t recently_used_fun(uint16_t drug_no)
{

	uint8_t loop_count=0;
	uint8_t status=0;
	uint8_t drug_no_count=0;
	uint8_t Total_drug_no=0;

		if(total_recent==0)
		{
		  drug_num[0]=drug_no;
		  total_recent++;//22-03
		}

		else
		{
			for(loop_count=0;loop_count<total_recent;loop_count++)
			{
				if(drug_no==drug_num[loop_count])
				{
					status=1;
					drug_no_count=loop_count;
					break;
				}
			}

			if(status==1)
			{
				Total_drug_no=drug_no_count;
			}

			else
			{
				Total_drug_no=total_recent;
				total_recent++;//22-03
			}

			for(loop_count=Total_drug_no;loop_count>0;loop_count--)
			{
				drug_num[loop_count]=drug_num[loop_count-1];
			}

			drug_num[0]=drug_no;

		}


		if(total_recent>10)
		{
			total_recent=10;
		}



 	 return 0;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void recent_eeprom_write(void)//29-03
{

	uint8_t loop_count=0;	EEPROM_datawrite(EEPROM_TOTAL_RECENT,total_recent,1);
		for(loop_count=0;loop_count<total_recent;loop_count++)
		{
			EEPROM_datawrite(EEPROM_RECENT_DRUG_LIST+(loop_count*2),drug_num[loop_count],2);
		}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void recent_eeprom_read(void)//29-03
{

		uint8_t loop_count=0;

		total_recent=EEPROM_dataread(EEPROM_TOTAL_RECENT,1);
		if(total_recent>10)
		{
			total_recent=0;
		}

		for(loop_count=0;loop_count<total_recent;loop_count++)
			{
			drug_num[loop_count]=EEPROM_dataread(EEPROM_RECENT_DRUG_LIST+(loop_count*2),2);
				if(drug_num[loop_count]>600)
				{
					drug_num[loop_count]=0;
					total_recent=0;
	                break;

				}
			}
}

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
#include "Main_screen.h"
#include "Driver_Timer.h"
#include "Power_off.h"
#include  "Brand.h"
#include  "sound.h"

void fav_drug_fb_load(void);
void fav_eeprom_read(void);
void fav_eeprom_write(void);//29-03

uint16_t fav_drug_list[11];
uint8_t fav_check[600];		//8-05-2024
uint8_t total_fav=0;

extern char Drug_Names[150][4][20];
extern uint8_t auto_lock_time; //ZOOZ_1
extern uint8_t ON_Flag;
extern uint16_t drug_num[11];

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t favourite_func(void)
{
	uint8_t page_no=0;
	uint8_t option_no=0;
	uint8_t prev_option = 0;
	uint8_t exit_flag=1;
	uint8_t  max_fav_page=0;
	uint8_t  max_fav_opt=0;
	uint8_t end_option_no=3;
	uint8_t check_flag=0;

	auto_lock_time=AUTO_EXIT_TIME;//common_bug//ZOOZ_1


	if(!total_fav)
	{
		favourite_Frame();//ZOOZ_2
		TFT_ST7789V__rectangle_curve(30,65,110,255,0,LIGHT_GRAY);
		Font_Select(ARIAL_14);
		TFT_String(85,110,(uint8_t *)"No favourites",LIGHT_GRAY,BLACK);
		delay_secs(2);
		exit_flag=0;//ZOOZ_2
	}

	else
	{
		max_fav_page=(total_fav-1)/4;
		max_fav_opt=(total_fav-1)%4;

		if(page_no == max_fav_page)
		{
			end_option_no = max_fav_opt;
		}

		else
		{
			end_option_no = 3;
		}

	}
		POW.power_status_flag=1;//27-03

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
			favourite_Frame();//27-03
			favourite_opt_Frame(page_no,option_no,end_option_no);//27-03

			if(max_fav_page)
			{
				scroll_bar(page_no,option_no,total_fav);//23-03
				while(KEY.value);//28-03
			}

		}

		if(KEY.value)//common_bug  //ZOOZ_1
		{
			auto_lock_time=AUTO_EXIT_TIME;
		}

		else if(!auto_lock_time)
		{
			break;
		}//common_bug

		switch(KEY.value)
		{


		case DOWN_KEY :   //DOWN_KEY

			beep_sound();

				if((option_no<3 && page_no<max_fav_page)||(option_no < max_fav_opt))				// page_no<max_fav_page) || (option_no <max_fav_opt))
				{
					option_no++;
				}


				else 		//if(max_fav_page)
				{

					if(page_no<max_fav_page)
					{
						page_no++;
					}

					else
					{
						page_no=0;
					}


					if(page_no == max_fav_page)
					{
						end_option_no = max_fav_opt;
					}
					else
					{
						end_option_no = 3;
					}

					option_no = 0;
					prev_option=option_no;

					brand__drug_split_screen(page_no);
					favourite_opt_Frame(page_no,option_no,end_option_no);
				}

				if(option_no!=prev_option)
				{
					favourite_cursor(prev_option,option_no,page_no);//,fav_drug_list);
					prev_option = option_no;
				}

					if(max_fav_page)
						{
							scroll_bar(page_no,option_no,total_fav);//23-03
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
								page_no=max_fav_page;

							}

							if(page_no==max_fav_page)
							{
								end_option_no=max_fav_opt;
							}
							else
							{
								end_option_no=3;


							}
							option_no=end_option_no;
							prev_option=option_no;
							brand__drug_split_screen(page_no);
							favourite_opt_Frame(page_no,option_no,end_option_no);

						}

					if(option_no!=prev_option)
						{
							 if(option_no<3)
							  {
								 favourite_cursor(prev_option,option_no,page_no);//,fav_drug_list);
							  }

							prev_option = option_no;//1

						}

								if(max_fav_page)
								{
									scroll_bar(page_no,option_no,total_fav);//23-03
								}
				while(KEY.value);
				break;

			case OK_KEY: 					 //OK_KEY

				beep_sound();
				TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS+((dose.drug_select_no%4)*VER_TEXT_SPACE_1)),250,0,MAIN_FRAME_COL,MAIN_FRAME_COL);//ZOOZ_2
				dose.drug_select_no=fav_drug_list[((page_no*4)+option_no)];
				TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS)+((option_no)*VER_TEXT_SPACE_1),250,0,LIGHT_GRAY,GOLD);//ZOOZ_2
				recently_used_fun(dose.drug_select_no);
				exit_flag=0;
				check_flag=1;

				while(KEY.value);
				break;


			case BACK_KEY:

				beep_sound();
				exit_flag=0;
				check_flag=0;



			while(KEY.value);
			break;

		}
	   }
	return check_flag;//ZOOZ_2
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t favourite_functionality(uint16_t drug_no,uint8_t pos)
{

	uint8_t loop_count=0;
	uint8_t exit_count=0;

	if( fav_check[drug_no]==1)
	{
		fav_check[drug_no]=0;

		TFT_ST7789V_star_14((INITIAL_TEXT_POS)+((pos%4)*VER_TEXT_SPACE_1),
		270,1,LIGHT_GRAY,LIGHT_GRAY);

		for(loop_count=0;loop_count<total_fav;loop_count++)
		{
			if(fav_drug_list[loop_count]==drug_no)
			{
				exit_count=loop_count;
				break;
			}
		}

		for(loop_count=exit_count;loop_count<(total_fav-1);loop_count++)
		{
			fav_drug_list[loop_count]=fav_drug_list[loop_count+1];
		}

		total_fav--;
	}

	else
	{
		if(total_fav<20)
		{
			fav_check[drug_no]=1;
			TFT_ST7789V_star_14((INITIAL_TEXT_POS)+((pos%4)*VER_TEXT_SPACE_1),
			270,1,LIGHT_GRAY,MAIN_FRAME_COL);
			fav_drug_list[total_fav]=drug_no;
			total_fav++;
		}
		else
		{
		    WARN_SOUND(1,1,2);
		}
	}

	if(total_fav>21)
	{
	  total_fav=20;
	}
	return 0;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void fav_eeprom_write(void)//29-03
{
	uint8_t loop_count=0;
	EEPROM_datawrite(EEPROM_TOTAL_FAV,total_fav,1);
	for(loop_count=0;loop_count<total_fav;loop_count++)
	{
		EEPROM_datawrite(EEPROM_FAV_DRUG_LIST+(loop_count*2),fav_drug_list[loop_count],2);
	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void fav_eeprom_read(void)//29-03
{
	uint8_t loop_count=0;

	total_fav=EEPROM_dataread(EEPROM_TOTAL_FAV,1);
	if(total_fav>10)
	{
		total_fav=0;
	}

	for(loop_count=0;loop_count<total_fav;loop_count++)
		{
			fav_drug_list[loop_count]=EEPROM_dataread(EEPROM_FAV_DRUG_LIST+(loop_count*2),2);
			if(fav_drug_list[loop_count]>600)
			{
				fav_drug_list[loop_count]=0;
				total_fav=0;
                break;

			}
		}
	fav_drug_fb_load();
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void fav_drug_fb_load(void)
{
	uint8_t loop_count=0;

	for(loop_count=0;loop_count<total_fav;loop_count++)
	{
		fav_check[fav_drug_list[loop_count]]=1;
	}

}

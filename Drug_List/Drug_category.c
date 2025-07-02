  /*
 * Drug_category.c
 *
 *  Created on: Feb 21, 2024
 *      Author: Welcome
 */
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
#include "Main_screen.h"
#include "Driver_Timer.h"
#include "Power_off.h"
#include "Dosage_mode.h"
#include  "Brand.h"
#include "sound.h"
#include <Boot_up.h>

void category_Frame(void);
void category_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void category_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, char* array[2][4]);

void category_list_Frame(uint8_t cate_no);
void category_opt_list_Frame(uint16_t page,uint8_t start_opt,uint8_t end_opt,uint8_t cate_no);//ZOOZ_2
void category_list_cursor(uint8_t prev_option, uint8_t curr_option, uint16_t page,uint8_t cate_no);//, char* array[2][4]);//ZOOZ_2

uint8_t category_list_fun(uint8_t cate_no);
uint8_t category_screen(void);

extern uint8_t TFT_ST7789V_tick_symbol_14pt(uint16_t xpos, uint16_t ypos,    //22-03
       uint8_t arrow, uint32_t boarder_color, uint32_t fill_color);//ZOOZ_2

extern char Drug_Names[150][4][20];

extern uint8_t ON_Flag;
extern uint8_t auto_lock_time;
extern uint8_t G_bootup_flag;
extern uint8_t fav_check[600];		//8-05-2024
extern uint8_t auto_lock_time;



char* category_list[2][4]={{"Benzodiazepines", "Muscle relaxant", "Opioids" ,"Anticholinergic Agents"},
		{"Vasopressor "}};

uint8_t total_cate_drug[4]={5,5,5,5};
uint8_t prev_cate_num=0;	//ZOOZ_2
uint16_t pin_drug_cate[4][5]={{18,157,201,458,497},{10,53,64,150,221},
								{97,192,285,356,477},{54,79,201,330,361}};
uint16_t prev_cate_opt=0;	//ZOOZ_2


/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t category_screen(void)
{
	uint8_t page_no=0;
	uint8_t option_no=0;
	uint8_t prev_option = 0;
	uint8_t exit_flag=1;
	uint8_t check_flag=0;
	uint8_t edit_flag=0;
	uint8_t end_opt=3;
	uint8_t category_no=0;
	uint8_t max_cat_page=0;//25-03
	uint8_t max_cat_opt=0;
	uint8_t total_cat=5;

//	uint8_t time_interval=30;  //ZOOZ_1

	POW.power_status_flag=1;//27-03
	max_cat_page=(total_cat-1)/4;  //25-03		//6-1=5 5/4=1
	max_cat_opt=(total_cat-1)%4;   //25-03         //6-1=5 6%4=2
	auto_lock_time=AUTO_EXIT_TIME;//common_bug

	while(exit_flag)
	{
//		 Font_Select(ARIAL_14);
//		 TFT_Number(0,70,max_cat_page,YELLOW,RED);
//
//		 Font_Select(ARIAL_14);
//		 TFT_Number(0,170,max_cat_opt,YELLOW,RED);


		Power_off();//27-03

		if(!ON_Flag)
		{
			break;//26-03
		}

		else if(POW.power_status_flag)
		{
			POW.power_status_flag=0;//26-03
			category_Frame();
			category_opt_Frame(page_no,option_no,end_opt);//27-03

			if(max_cat_page)
			{
				scroll_bar(page_no,option_no,total_cat);//25-03
			}
		}

			if(KEY.value)//common_bug //ZOOZ_1
			{
			//  while(KEY.value);
				auto_lock_time=AUTO_EXIT_TIME;
			}
			else if(!auto_lock_time)
			{
				break;
			}//common_bug

		switch(KEY.value)
		{

		case DOWN_KEY :
			beep_sound();
			if(!edit_flag)
			{
				if((option_no<3 && page_no<max_cat_page) //ZOOZ_2
					||(option_no<max_cat_opt ))
				{
					option_no++;
				}
				else
				{
					if(page_no<max_cat_page)//if(max_cat_page>page)
					{
						page_no++;
					}
					else
					{
						page_no=0;
					}

					if(page_no==max_cat_page)
					{
						end_opt=max_cat_opt;
					}

					else
					{
						end_opt=3;
					}
					option_no=0;
					prev_option=option_no;
					POW.power_status_flag=1;//27-03//ZOOZ_2
				}

						if(option_no!=prev_option)
						{
							category_cursor(prev_option,option_no,page_no,category_list);
							prev_option = option_no;
						}
			}//ZOOZ_2
							if(max_cat_page)//25-03
							{
								scroll_bar(page_no,option_no,total_cat); //23-03
							}

				while(KEY.value);
				break;

		case UP_KEY:
			beep_sound();
			if(!edit_flag)
			{
				if(option_no>0)
				{
					option_no--;
				}
				else
				{
					if(page_no)
					{
						page_no--;
						end_opt=3;
					}
					else
					{
						page_no=max_cat_page;
						end_opt=max_cat_opt;
					}

						option_no=end_opt;
						prev_option=option_no;
						POW.power_status_flag=1;//27-03

				}

						if(option_no!=prev_option)
						{
							category_cursor(prev_option,option_no,page_no,category_list);
							prev_option = option_no;
						}
			}
							if(max_cat_page)
							{
								scroll_bar(page_no,option_no,total_cat);//25-03
							}
				while(KEY.value);
				break;

		case  OK_KEY:
			beep_sound();
			category_no=((page_no*4)+option_no)	;
			if(category_no!=4)	//IGNORE VASSOPRESSURE//25-03
			{
				check_flag=category_list_fun(category_no);

					if(auto_lock_time)
					{
						POW.power_status_flag=1;
					}

					if((check_flag)&&(G_bootup_flag))//ZOOZ_2
					{
						exit_flag=0;
					}
//					else
//					{
//						POW.power_status_flag=1;//27-03
//					}
			}
			while(KEY.value);
			break;

		case  BACK_KEY:

			beep_sound();
			exit_flag=0;
			check_flag=0;

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

void category_Frame(void)
{
	    uint8_t menu_count = 0;
	 //  	Rectangle(0,0,320,240,MAIN_FRAME_COL);
	    CLRSCR(MAIN_FRAME_COL);
		Rectangle(0,0,320,34,NEW_HDR_COL);

		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"  Category ");	// header
	   	Rectangle_Line_function(1,3);

//		for(menu_count = 1; menu_count <=3 ; menu_count++)				//no of lines
//		{
//			Rectangle(7,34+(43*menu_count),290,0, BLACK);		// no of rect line
//		}
		Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to confirm",(uint8_t*)"OK",2,14);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void category_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
{


    uint8_t loop_count=0;
    uint32_t back_colour = 0;
   	uint32_t text_colour = 0;

	for(loop_count=0;loop_count<=end_opt;loop_count++)
	{
		if(loop_count == start_opt)//0==0
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
		TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
		(uint8_t*)category_list[page][loop_count],back_colour,text_colour);

	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void category_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page,  char* array[2][4])
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

uint8_t category_list_fun(uint8_t cate_no)
{
	uint8_t page_no=0;
	uint8_t option_no=0;
	uint8_t prev_option = 0;
	uint8_t exit_flag=1;
	uint8_t edit_flag=0;
	uint8_t end_opt=3;
	uint8_t max_page=0;
	uint8_t max_opt=0;
	uint8_t check_flag=0;
	uint16_t category_num=0;
	auto_lock_time=AUTO_EXIT_TIME;

	POW.power_status_flag=1;//27-03




	max_page=(total_cate_drug[cate_no]-1)/4;
	max_opt=(total_cate_drug[cate_no]-1)%4;



	while(exit_flag)
	{
		Power_off();//27-03

		if(!ON_Flag)
		{
			break;//26-03
		}

		else if(POW.power_status_flag)//27-03
		{
			POW.power_status_flag=0;//26-03
			category_list_Frame(cate_no);
			category_opt_list_Frame(page_no,option_no,end_opt,cate_no);
			if(max_page)
			{
				scroll_bar(page_no,option_no,total_cate_drug[cate_no]);//25-03
			}
		}
		if(KEY.value)//common_bug //ZOOZ_1
		{
		//	while(KEY.value);
			auto_lock_time=AUTO_EXIT_TIME;
		}
		else if(!auto_lock_time)
		{
			break;
		}//co

		switch(KEY.value)
		{

			case DOWN_KEY :
				beep_sound();
					if(!edit_flag)
					{
						if((option_no<3 && page_no<max_page) || (option_no <max_opt))
						{
							option_no++;
						}
						else
						{
							if(page_no<max_page)
								{
									page_no++;


									if(page_no == max_page)
									{
										end_opt = max_opt;
									}
									else
									{
										end_opt = 3;
									}


									option_no=0;
									prev_option=0;

								 }

								else
								{
									page_no=0;
									option_no=0;
									end_opt=3;
									prev_option=0;
								}
									POW.power_status_flag=1;

						}

						if(option_no!=prev_option)
						{
							category_list_cursor(prev_option,option_no,page_no,cate_no);//,Drug_Names);
							prev_option = option_no;
						}
					}
							if(max_page)
							{
								scroll_bar(page_no,option_no,total_cate_drug[cate_no]);//25-03
							}
					while(KEY.value);
					break;

			case UP_KEY:
				beep_sound();
				if(!edit_flag)
				{
					if(option_no)
					{
						option_no--;
					}
					else
					{
						if(page_no)
						{
							page_no--;
							end_opt=3;
						}
						else
						{
							page_no=max_page;
							end_opt=max_opt;
						}
							option_no=end_opt;//25-03
							prev_option=option_no;
							brand__drug_split_screen(0);
							category_opt_list_Frame(page_no,option_no,end_opt,cate_no);
					}

							if(option_no!=prev_option)
							{
								category_list_cursor(prev_option,option_no,page_no,cate_no);//,Drug_Names);
								prev_option = option_no;
							}
				}

								if(max_page)
								{
									scroll_bar(page_no,option_no,total_cate_drug[cate_no]);//25-03
								}
					while(KEY.value);
					break;

			case  OK_KEY:

				beep_sound();

				if(prev_cate_num==cate_no)
				{
					TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS+((prev_cate_opt%4)*VER_TEXT_SPACE_1)),250,0,MAIN_FRAME_COL,MAIN_FRAME_COL);
				}

				dose.drug_select_no=pin_drug_cate[cate_no][((page_no*4)+option_no)];//ZOOZ_2
				TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS)+((option_no)*VER_TEXT_SPACE_1),250,0,LIGHT_GRAY,GOLD);//ZOOZ_2
				prev_cate_opt=((page_no*4)+option_no);//ZOOZ_2
				prev_cate_num=cate_no;//ZOOZ_2
				recently_used_fun(dose.drug_select_no);//ZOOZ_2
				exit_flag=0;
				check_flag=1;

				while(KEY.value);
				break;

			case  BACK_KEY:
				beep_sound();
				exit_flag=0;
				check_flag=0;

				while(KEY.value);
				break;

			case  MUTE_KEY :
				category_num=pin_drug_cate[cate_no][((page_no*4)+option_no)];//ZOOZ_2
				favourite_functionality(category_num,((page_no*4)+option_no));

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

void category_list_Frame(uint8_t cate_no)
{
	uint8_t menu_count = 0;
	//   	Rectangle(0,0,320,240,MAIN_FRAME_COL);
		CLRSCR(MAIN_FRAME_COL);
	   	Rectangle(0,0,320,34,NEW_HDR_COL);
	   	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)category_list[cate_no/4][cate_no%4]);	// header
	   	Rectangle_Line_function(1,3);

//		for(menu_count = 1; menu_count <=3 ; menu_count++)				//no of lines
//		{
//			Rectangle(7,34+(43*menu_count),290,0, BLACK);		// no of rect line
//		}
		Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to confirm",(uint8_t*)"OK",2,14);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void category_opt_list_Frame(uint16_t page,uint8_t start_opt,uint8_t end_opt,uint8_t cate_no)//ZOOZ_2
{


    uint8_t loop_count=0;
    uint32_t back_colour = 0;
   	uint32_t text_colour = 0;
   	uint32_t tick_color=0;

	for(loop_count=0;loop_count<=end_opt;loop_count++)
	{
		if(loop_count == start_opt)//0==0
		{
			back_colour	= LIGHT_GRAY;
			text_colour = BLACK;
			tick_color=MAIN_FRAME_COL;
			TFT_ST7789V__rectangle_curve(3,35+(43*(start_opt)),41,290,0,back_colour); //0
		}
		else
		{
			back_colour	= MAIN_FRAME_COL;
			text_colour = WHITE;
			tick_color= GOLD;
		}

		Font_Select(ARIAL_14);

		TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
				(uint8_t*)Drug_Names[(pin_drug_cate[cate_no][((page*4)+loop_count)])/4] [(pin_drug_cate[cate_no][((page*4)+loop_count)])%4],back_colour,text_colour);

		if((pin_drug_cate[cate_no][((page*4)+loop_count)])==dose.drug_select_no)  //22-03
		{
			TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS)+((loop_count)*VER_TEXT_SPACE_1),250,0,back_colour,tick_color);//ZOOZ_2
		}

		 if(fav_check[pin_drug_cate[cate_no][((page*4)+loop_count)]]==1)
			  {
				  TFT_ST7789V_star_14((INITIAL_TEXT_POS)+(loop_count)*VER_TEXT_SPACE_1,270,1,back_colour,tick_color);
			  }
	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void category_list_cursor(uint8_t prev_option, uint8_t curr_option, uint16_t page,uint8_t cate_no)//,  char* array[2][4])//ZOOZ_2
{

	uint8_t loop = 0;
	uint8_t opt_no  = 0;
	uint32_t back_colour = 0;
	uint32_t text_colour = 0;
	uint32_t tick_color = 0;

	for(loop = 0; loop<2; loop++)
	{
		if(!loop)
		{
			back_colour = MAIN_FRAME_COL;
			text_colour = WHITE;
			opt_no		= prev_option;
			tick_color= GOLD;
		}
		else
		{
			back_colour = LIGHT_GRAY;
			text_colour = BLACK;
			opt_no= curr_option;
			tick_color= MAIN_FRAME_COL;
		}

			TFT_ST7789V__rectangle_curve(3,35+(43*(opt_no)),41,290,0,back_colour);
			Font_Select(ARIAL_14);

			TFT_String(9,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
							(uint8_t*)Drug_Names[(pin_drug_cate[cate_no][((page*4)+opt_no)])/4] [(pin_drug_cate[cate_no][((page*4)+opt_no)])%4],back_colour,text_colour);

			if(  pin_drug_cate[cate_no][((page*4)+opt_no)]==dose.drug_select_no) //22-03

			{
				TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS)+((opt_no)*VER_TEXT_SPACE_1),250,0,back_colour,tick_color);//ZOOZ_2
			}


			 if(fav_check[pin_drug_cate[cate_no][((page*4)+opt_no)]]==1)
				  {
					  TFT_ST7789V_star_14((INITIAL_TEXT_POS)+(opt_no)*VER_TEXT_SPACE_1,270,1,back_colour,tick_color);
				  }
	}
}



/*
 * nav_search_Drug_result.c
 *
 *  Created on: 11-Mar-2024
 *      Author: Software4
 */

//#include "nav_search_Drug_result.h"
#include "LPC55S16.h"
#include "Keypad.h"
#include "Color.h"
#include "Shapes.h"
#include"TFT_Commands.h"
#include "Dosage_mode.h"
#include "Power_off.h"
#include "TFT_String.h"
#include  "Brand.h"
#include "string.h"
#include <Boot_up.h>

/*
 * 1. COMPILE TIME SEARCH WITH SEARCHED DRUG DISPLAY OPTION
 * VER 0.1
 * 2. edit level 1
 * VER 0.2
 * SEARCH FOR ALL CHARACTERS WITH DELETE STRING & DIPLAY COMPLETED 15-03-2024 SHORTENED SEArCH INCOMPLETED.
 * VER 0.3
 * SEARCH FOR ALL CHARACTERS with errors
 * VER 0.4
 * 16_03_2024 stage 1 code for search and scroll all drugs copy1;
 * VER 0.5
 * 16_03_2024 final migrated code with bug solved 123 code
 * VER 0.5
 *  16_03_2024 decription added.
 *  VER 0.6
 *  18_03_2024 drugname array changed from 2d pointer to 3d array.
 * */

void drug_name_refresh_checking(void);
void searched_drugdisplay();
void frame_realtime_search_drug_option(uint8_t page,uint8_t starting_count,uint8_t Final_count,uint8_t search_count);
void search_result_drug_option_scroll(uint8_t prev_option,uint8_t curr_option,uint8_t page,uint8_t search_count);
void Drug_Search_Layout (uint8_t header,uint8_t *search_str);
void searched_Drug_List_layout ();

uint8_t Drug_name_search();
uint8_t  nav_search_Drug_result(uint8_t totalsearch_times,uint8_t search_count);

extern uint8_t ON_Flag;
extern uint8_t auto_lock_time;  //ZOOZ_1

uint8_t *prev_search_str;
uint16_t name1[100];
uint16_t search_drug[5][100];

struct user
{
	uint8_t name[15];
};

struct user drugname1[500];
extern char Drug_Names[150][4][20];

/**************************************************************************
 *Function Name :Drug_name_search()
 *Arguments     :void
 *Return        :void
 *Description	:In this function, "Drug Name Search," edits and real-time updates
 	 	 	 	 of the drugs searched list are performed.
***************************************************************************/

uint8_t Drug_name_search()
{
	uint8_t data_founded=0;
	uint8_t data_key=0;
	uint8_t page_no=0;
	uint8_t option_no=0;
	uint8_t end_opt_no=3;
	uint8_t realtime_loop=1;
	uint8_t check_flag=0;
	uint8_t name[21]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
	uint8_t name2[21]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
	uint8_t search_count;
	uint8_t text_pos;
	uint8_t search_flag=1;

//  uint8_t time_interval=30;//common_bug//ZOOZ_1
//  uint8_t drug_new_no=0;
//  uint8_t prev_option = 0;
//	uint8_t current_pos=0;
//	uint8_t check_pos=0;

//	uint16_t end_limit=0;
//	uint16_t total_page_no=0;
//	uint16_t last_page_opt_no=0;
//	uint16_t count;
	uint16_t totalsearch_times;
	uint16_t loop_count2;
	uint16_t loop_count1;
	uint16_t loop_count;
	uint16_t overal_val[10]={500,0,0,0,0,0,0,0,0,0};
	uint16_t loop_count_1;
	uint16_t search_times=0;

	name[0]='A';
	text_pos=0;

	for(loop_count1=0; loop_count1<500; loop_count1++)
	{
		for(loop_count2=0; loop_count2<=14; loop_count2++)
		{
			drugname1[ loop_count1 ].name[ loop_count2 ] = Drug_Names[loop_count1/4][loop_count1%4 ][loop_count2];
		}
	}

	search_count=0;
	POW.power_status_flag=1;//26-03

	while(realtime_loop)
	{
		Power_off();

		if(!ON_Flag)
		{
			break;//26-03
		}

		else if(POW.power_status_flag)
		{
			POW.power_status_flag=0;//26-03
			Drug_Search_Layout(1,name);
			search_flag=1;
		}

		if(KEY.value)//common_bug  ////ZOOZ_1
		{
		//	while(KEY.value);
			auto_lock_time=AUTO_EXIT_TIME;
		}
		else if(!auto_lock_time)
		{
			break;
		}




		    if(search_flag)
		    {

		    	if(text_pos >=4)
		    	{
		    		text_pos=4;
		    	}
		    	search_count=text_pos;
				for(loop_count=0;loop_count <= overal_val[search_count]/*overal_val[search_count] */;loop_count ++)
				{
					for(loop_count_1=0; loop_count_1 <=text_pos; loop_count_1++)
					{

						if(!search_count)
						{
							name2[loop_count_1] = drugname1[loop_count].name[loop_count_1];
						}
						else
						{
							name2[loop_count_1] = drugname1[  search_drug[ search_count-1][loop_count] ].name[loop_count_1];
						}
					}


					if(strcasecmp((const char*)name2,(const char*)name)==0)
					{
						if(!search_count)
						{
							search_drug[search_count][search_times] = loop_count;
						}
						else
						{
							search_drug[search_count][search_times]= search_drug[search_count-1][loop_count];
						}

						search_times++;
						data_founded=1;
					}

				}
                if(data_founded)
                {

					overal_val[search_count+1]=search_times-1;
					totalsearch_times=search_times-1;

					page_no=0;
					option_no=0;

					end_opt_no=3;
					if((overal_val[search_count+1]/4)==0)
					{
						end_opt_no=overal_val[search_count+1]%4;
					}
					Drug_Search_Layout(0,name);
					frame_realtime_search_drug_option(page_no,option_no,end_opt_no,search_count);
					search_flag=0; // complete all loop
					search_times=0;
					data_founded=0;
					data_key=1;

                }
                else
                {
                	Rectangle(0,34,320,172,MAIN_FRAME_COL);
                	TFT_String(10+80-5-3,48+(2*42)-30-5,(uint8_t*)"No data found !",MAIN_FRAME_COL,WHITE);
                	TFT_String(58+5,206+8,(uint8_t*)"                                                       ",WHITE,WHITE);

                    TFT_String(58+5,206+8,name,WHITE,BLACK);

                	search_flag=0; // complete all loop
					search_times=0;
					data_founded=0;
					data_key=0;
                }


		    }

			switch(KEY.value)
			{
			case DOWN_KEY:

			if(name[text_pos] > 33)
			{
				name[text_pos]--;
			}
			if(name[text_pos]!=64)
			{
				name[text_pos]=name[text_pos] ;
				search_flag=1;
			}

			while(KEY.value);
			break;

			case UP_KEY:

				if(name[text_pos] < 127)
				{
					name[text_pos]++;
				}

				if(name[text_pos]!=64)
				{
					name[text_pos]=name[text_pos];
					search_flag=1;
				}
				while(KEY.value);
				break;

				case  LEFT_KEY:

					   if(text_pos!=0)
					   {
						   name[text_pos]='\0';
						   name2[text_pos]='\0';
						   text_pos--;
					   }
					   search_flag=1;
						while(KEY.value);
						break;

				case RIGHT_KEY:

					 beep_sound();

					 if(text_pos < 4)text_pos++;
					 name[text_pos]='A';
					 search_flag=1;

						while(KEY.value);
						break;

				case  OK_KEY:

					beep_sound();
					if(data_key)
					{
					    realtime_loop = nav_search_Drug_result( overal_val[search_count+1],search_count);
                        if(realtime_loop)
                        {
                        	POW.power_status_flag=1;//2-04
                        }
                        else
                        {
                        	check_flag=1;
                        }
					}

						while(KEY.value);
						break;

				case BACK_KEY:

					beep_sound();
					realtime_loop=0;
					check_flag=0;

					while(KEY.value);
					break;

				case MUTE_KEY:

					beep_sound();

					while(KEY.value);
					break;
		}
	}
	return check_flag;

}

/**************************************************************************
 *Function Name :nav_search_Drug_result(uint8_t totalsearch_times,uint8_t search_count)
 *Arguments     :uint8_t totalsearch_times,uint8_t search_count
 *Return        :check_flag;
 *Description	:In this function, "inc/dec for result drugs.
***************************************************************************/

uint8_t  nav_search_Drug_result(uint8_t totalsearch_times,uint8_t search_count)
{
	uint8_t check_flag=0;
	uint8_t page_no=0;
	uint8_t option_no=0;
	uint8_t end_opt_no=3;
	uint8_t prev_option = 0;
	uint8_t Result_loop=1;
	uint8_t end_limit=0;

	uint8_t total_page_no;
	uint8_t last_page_opt_no;
	//uint8_t time_interval=30;//common_bug //ZOOZ_1
	//auto_lock_time=30;//common_bug

	page_no=0;
	option_no=0;
	end_opt_no=	3;
	if((totalsearch_times/4)==0)
		{
			end_opt_no=totalsearch_times%4;
		}

//	searched_Drug_List_layout();
	//printf("%d",search_drug[0][0]);
//	frame_realtime_search_drug_option(page_no,option_no,end_opt_no,search_count);
	POW.power_status_flag=1;//26-03

		while(Result_loop)
		{
			Power_off();

			if(!ON_Flag)
			{
				break;//26-03
			}

			else if(POW.power_status_flag)
			{
				POW.power_status_flag=0;//26-03
				searched_Drug_List_layout();
				frame_realtime_search_drug_option(page_no,option_no,end_opt_no,search_count);
				scroll_bar(page_no,option_no,totalsearch_times);//27-03
				while(KEY.value);
			}

			if(KEY.value)//common_bug //ZOOZ_1
			{
			//	while(KEY.value);
				auto_lock_time=AUTO_EXIT_TIME;
			}
			else if(!auto_lock_time)
			{
			//	auto_lock_time=45;
				break;
			}//common_bug

			switch(KEY.value)
			{
				case DOWN_KEY:
					// TARGET :
					beep_sound();
					total_page_no=totalsearch_times/4;
                    last_page_opt_no=totalsearch_times%4;

                    if(option_no<3)
					{
                    	if( (page_no == total_page_no) && (last_page_opt_no==option_no) )
                    	{
                    		page_no=0;
                    		option_no=0;

                    		if(!total_page_no)
                    			{
                    			  end_opt_no=last_page_opt_no;
                    			}
                    		else
                    		{
                    			end_opt_no=3;
                    		}


                    		prev_option=0;
                    		brand__drug_split_screen(0);
                    		frame_realtime_search_drug_option(page_no,option_no,end_opt_no,search_count);
                    	}
                    	else
                    	{
                    		option_no++;
                    	}

					}

					else
					{
						if(page_no  <  (totalsearch_times/4))
						{
							page_no++;
							end_opt_no=3;
							option_no=0;
							prev_option=0;
					     }
						else
						{
							page_no=0;
							option_no=0;
							end_opt_no=3;
							prev_option=0;
						}
						 end_limit =totalsearch_times/4;
						if(page_no == (end_limit) )
						{
							end_opt_no = totalsearch_times%4;
						}
						brand__drug_split_screen(0);
						frame_realtime_search_drug_option(page_no,option_no,end_opt_no,search_count);

					 }

				if(option_no!=prev_option)
				{
					if(option_no!=0)
					{
						search_result_drug_option_scroll(prev_option,option_no,page_no,search_count);
					}
					prev_option = option_no;//1
				}
				 scroll_bar(page_no,option_no,totalsearch_times);//27-03

				//TFT_Number(240,128,search_drug[search_count][(page_no*4)+option_no],BLACK,ORANGE);
				while(KEY.value);
				break;

			case UP_KEY:
				//RUN_STOP:
			beep_sound();
			total_page_no=totalsearch_times/4;
			last_page_opt_no=totalsearch_times%4;

			if(option_no)
			{
				option_no--;
			}

			else
			{
			if(page_no)
			{
			page_no--;
			end_opt_no=3;
		    option_no=3;
			prev_option=3;
			}
			else
			{
				page_no=total_page_no;
				option_no=last_page_opt_no;
				end_opt_no=last_page_opt_no;
				prev_option=last_page_opt_no;
			}
			brand__drug_split_screen(0);
			frame_realtime_search_drug_option(page_no,option_no,end_opt_no,search_count);
		    }
			 if(option_no!=prev_option)
				{
					 if(option_no<3)
					  {
						 search_result_drug_option_scroll(prev_option,option_no,page_no,search_count);
					  }
					prev_option = option_no;//1
				}
			 scroll_bar(page_no,option_no,totalsearch_times);//27-03
			 // TFT_Number(240,128,search_drug[search_count][(page_no*4)+option_no],BLACK,ORANGE);
			 while(KEY.value);
			 break;

			case  OK_KEY:
				//SET:
				beep_sound();
				Result_loop=0;
				check_flag=0;
				dose.drug_select_no = search_drug[search_count][(page_no*4)+option_no];
				while(KEY.value);
				break;

			case BACK_KEY:

				beep_sound();
				Result_loop=0;
				check_flag=1;
				while(KEY.value);
				break;

			case MUTE_KEY:

				beep_sound();
				while(KEY.value);
				break;

			}
		}
 return check_flag;
}

/**************************************************************************
 *Function Name :void frame_realtime_search_drug_option(uint8_t page,uint8_t starting_count,
 				 uint8_t Final_count, uint8_t search_count)
 *Arguments     :uint8_t page,uint8_t starting_count,uint8_t Final_count, uint8_t search_count
 *Return        :void;
 *Description	:In this function,prints the drug names and options;
***************************************************************************/

void frame_realtime_search_drug_option(uint8_t page,uint8_t starting_count,uint8_t Final_count, uint8_t search_count)
{
	    uint8_t loop_count=0;
	    uint32_t back_colour = 0;
		uint32_t text_colour = 0;

		for(loop_count=0;loop_count<=Final_count;loop_count++)
		{
	    	if(loop_count == starting_count)
	    	{
	    		back_colour	= LIGHT_GRAY;
				text_colour=  BLACK;
				TFT_ST7789V__rectangle_curve(3,35+(43*(starting_count)),41,290,0,back_colour);

	    	}
	    	else
	    	{
				back_colour	= MAIN_FRAME_COL;
				text_colour = WHITE;
	    	}



			  Font_Select(ARIAL_14);

			  TFT_String(10,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE_1),
					(uint8_t*) Drug_Names  [       (search_drug  [search_count]  [(page*4)+loop_count])/4  ]   [    (search_drug  [search_count]  [(page*4)+loop_count])%4    ]
																	,back_colour,text_colour);

		}
}

/**************************************************************************
 *Function Name :void search_result_drug_option_scroll(uint8_t prev_option,
 	 	 	 	 uint8_t curr_option,uint8_t page, const char* array[5][4])
 *Arguments     :uint8_t prev_option,uint8_t curr_option,uint8_t page, const char* array[5][4]
 *Return        :void;
 *Description	:In this function,scroll option frame and printing are done.
***************************************************************************/

void search_result_drug_option_scroll(uint8_t prev_option,uint8_t curr_option,uint8_t page,uint8_t search_count)
 {
	uint32_t back_colour = 0;
    uint32_t text_colour = 0;
	uint8_t loop		 = 0;
	uint8_t opt_no		 = 0;


	for(loop = 0; loop<2; loop++)
	{
		if(!loop)
		{
			back_colour     = MAIN_FRAME_COL;
			text_colour 	= WHITE;
			opt_no			= prev_option;
		}
		else
		{
			back_colour   = LIGHT_GRAY;
			text_colour   = BLACK;
			opt_no		  = curr_option;
    	}


	    TFT_ST7789V__rectangle_curve(3,35+(43*(opt_no)),41,290,0,back_colour);

	    Font_Select(ARIAL_14);
	    TFT_String(9,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),(uint8_t*)
	    							Drug_Names[search_drug[search_count][(page*4)+opt_no]/4][search_drug[search_count][(page*4)+opt_no]%4],back_colour,text_colour);
	}
 }

/**************************************************************************
 *Function Name :void Drug_Search_Layout (uint8_t header,uint8_t *search_str)
 *Arguments     :uint8_t header,uint8_t *search_str
 *Return        :void;
 *Description	:In this function,layout for real time searching frame
***************************************************************************/

void Drug_Search_Layout(uint8_t header,uint8_t *search_str)
 {
	uint8_t loop_count=0;

	if(header)
	{
	//	 Rectangle(0,0,320,240,MAIN_FRAME_COL);
		 CLRSCR(MAIN_FRAME_COL);
		 Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"All Drugs");
	}
	else
	{
		 Rectangle(0,34,320,172,MAIN_FRAME_COL);
	}

	for(loop_count=1;loop_count<=3;loop_count++)
	{
		 Rectangle(7,34+(43*loop_count),290,0,BLACK);
	}

	 TFT_ST7789V_lcd_shapes(38+163,38,306,300+15,LIGHT_GRAY_3);                                                                                             //SCROLLING BOX OUTSIDE LAYER
	 TFT_ST7789V_lcd_shapes(40+57,40,306,303+12,BLACK);

	 if(header)
	 {
		 Rectangle(0,206,58,34,NEW_FTR_COL); //small footer sandal
		 TFT_ST7789V_sercch_symbol_24pt(206+2+1,10,0,NEW_FTR_COL ,BLACK);	//22-03
		 Rectangle(58,206,262,34,WHITE);
	 }
	 else
	 {
	 //    TFT_String(58+5,206+8,(uint8_t*)"                                                       ",WHITE,WHITE);
		   Rectangle(58,206,320,34,WHITE);
		   TFT_String(58+5,206+8,search_str,WHITE,BLACK);
		   prev_search_str=search_str;
	 }
}

/**************************************************************************
 *Function Name :void searched_Drug_List_layout ()
 *Arguments     :void
 *Return        :void;
 *Description	:In this function,layout for search result drug list display
***************************************************************************/

void searched_Drug_List_layout ()
 {
	// Rectangle(0,0,320,240,MAIN_FRAME_COL);
	 CLRSCR(MAIN_FRAME_COL);
	 Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"All Drugs - Search Results");

	 Rectangle(7,34+(43*1),290,0, BLACK);
	 Rectangle(7,34+(43*2),290,0,BLACK);
	 Rectangle(7,34+(43*3),290,0,BLACK);

	 Rectangle(0,206,320,34,NEW_FTR_COL);
	 TFT_ST7789V_lcd_shapes(38+163,38,306,300+15,LIGHT_GRAY_3);                                                                                             //SCROLLING BOX OUTSIDE LAYER
	 TFT_ST7789V_lcd_shapes(40+57,40,306,303+12,BLACK);

	 Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to select",(uint8_t*)"OK",2,14);//	 TFT_ST7789V_lcd_drawcircle1(150,223,15,MAIN_FRAME_COL,MAIN_FRAME_COL);
}

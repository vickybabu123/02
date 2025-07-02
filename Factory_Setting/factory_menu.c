
#include "LPC55S16.h"
#include "Shapes.h"
#include "Color.h"
#include "Keypad.h"
#include "TFT_Commands.h"
#include "TFT_String.h"
//#include "Main_Menu.h"
//#include "../Menu_Setting/Main_Menu.h"
#include "Power_off.h"
#include "Driver_Timer.h"
#include "factory.h"
#include"Driver_I2C.h"
#include "Consumed_hrs.h"
#include "Power_off.h"
#include "sound.h"
#include "Boot_up.h"

extern uint8_t ON_Flag;
extern uint8_t password_one_flag;
extern uint8_t password_two_flag;
extern uint8_t password_three_flag;
extern uint8_t password_four_flag;
extern uint8_t auto_lock_time;
extern uint8_t G_infusion_modes;
extern uint8_t edit_flag;
extern volatile uint8_t waitingtime_1;
extern uint16_t Passcode(uint16_t mode);

extern uint16_t xpos;

factorys FACT;

uint8_t G_qc_track=0;
uint8_t packing_variable=0;
uint16_t G_Test_code;
uint32_t serialno;

const char* factory_menu[9]={"Mfg. year","Model","SW version","Serial.no","Reset","QC Track","Used Hours"};

const char* qc_track[27]={"A","B","C","D","E","F","G","H","I",
						 "J","K","L","M","N","O","P","Q","R",
						 "S","T","U","V","W","X","Y","Z"};

const char* used_hrs_info_menu[5]={"Device ON","Battery ON","Battery Run","Factory Test"};//25-03

extern uint8_t ON_Flag;
extern uint8_t month_yr_edit_screen(uint16_t *Edit_value,uint8_t screen,uint16_t max_value);
extern uint8_t edit_screen(uint16_t *Edit_value,uint8_t screen,uint16_t max_value);
extern uint16_t serialno_screen(uint16_t *Value_1, uint32_t Limit);

extern void Packing_reset();
extern void Complete_Reset();
extern void scroll_bar(uint8_t page_no,uint8_t option_no,uint8_t total_option);     //23-03                                  //(uint8_t prev_option, uint8_t curr_option, uint8_t page)


void factory_subsetting(uint8_t option_no,uint8_t page_no, uint8_t INC_flag);
void factory_Opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void factory_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[9]);
void factory_Frame(void);
void factory_setting();

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void factory_layout()
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

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void factory_setting()
{
	uint8_t factory_var=1;
	uint8_t option_no=0;
	uint8_t page_no=0;
	uint8_t exit_flag=0;
	uint8_t prev_option = 0;
	uint8_t end_opt_no=0;
	uint8_t total_option=7;
	serialno=12345;
	uint8_t edit_flag=0;
	uint8_t down_opt_arr[3]={3,2,2};
	uint8_t up_opt_arr[3][2]={	{3,3},
								{2,2},
								{1,1}
							 };
	uint8_t reset_var=0;

//	uint8_t Reset_variable=0;


	end_opt_no=3;
	POW.power_status_flag=1;//27-03
	while(factory_var)
	{
		Power_off();//27-03




		if(!ON_Flag)
		{
			break;//26-03
		}

		else if(POW.power_status_flag)//27-03
		{
			POW.power_status_flag=0;//27-03
			factory_Frame();
			factory_Opt_Frame(page_no,option_no,end_opt_no);
			scroll_bar(page_no,option_no,total_option);
		}

//		if(KEY.value)
//		{
//		 //while(KEY.value);
//		   auto_lock_time=AUTO_EXIT_TIME;
//		}
//		if(!auto_lock_time)
//		{
//		//factory_var=0;
//		  break;
//		}

		switch(KEY.value)
		{

			case RIGHT_KEY:
			beep_sound();
			if(edit_flag)
			{
				factory_subsetting( 1,page_no,1);
			}
			while(KEY.value);
			break;


			case LEFT_KEY:
			beep_sound();
			if(edit_flag)
			{
				factory_subsetting( 1,page_no,0);
			}
			while(KEY.value);
			break;

			case DOWN_KEY :
			beep_sound();
			if(!edit_flag)
			{

				if(((page_no==1)&&(option_no<2))||((page_no==0)&&(option_no<3)))
				{
					option_no++;

					if(option_no!=prev_option)
					{
						factory_cursor(prev_option,option_no,page_no,factory_menu);

						prev_option = option_no;
					}
				}

				else
				{
					page_no++;

//				if(page_no<1)
//				{
//					page_no++;
//					option_no=0;
//					end_opt_no=2;
//					prev_option=0;
//
//
//				}
//				else
//				{
//					page_no=0;
//					option_no=0;
//					end_opt_no=3;
//
//					prev_option=0;
//
//				}
				if(page_no>=2)
				{
					page_no=0;
				}
				option_no=0;
				prev_option=option_no;
				end_opt_no=down_opt_arr[page_no];  //REW1

				factory_layout();
				factory_Opt_Frame(page_no,option_no,end_opt_no);

		}

	}
			scroll_bar(page_no,option_no,total_option);

			while(KEY.value);
			break;

			case UP_KEY:
			beep_sound();
			if(!edit_flag)
			{
				if(option_no)
				{
					option_no--;
					if(option_no!=prev_option)
					{
						factory_cursor(prev_option,option_no,page_no,factory_menu);
						prev_option = option_no;
					}
				}

				else
				{

					if(!page_no)
					{

						page_no++;
						Rectangle(3,36,300,169,MAIN_FRAME_COL);
						//option_no=3;
						prev_option=2;
						//end_opt_no=3;//23-03
						//factory_layout();
						//factory_Opt_Frame(page_no,option_no,end_opt_no);
					}

					else
					{
						page_no--;
						Rectangle(3,36,300,169,MAIN_FRAME_COL);
//						option_no=2;
						prev_option=3;
//						end_opt_no=2;//23-03
//						factory_layout();
//						factory_Opt_Frame(page_no,option_no,end_opt_no);
					}

					option_no=up_opt_arr[page_no][0];
					end_opt_no=up_opt_arr[page_no][1];

					factory_layout();
					factory_Opt_Frame(page_no,option_no,end_opt_no);
				}






			}
			scroll_bar(page_no,option_no,total_option);

			while(KEY.value);
			break;

			case OK_KEY:
			beep_sound();
			if(!page_no)
			{
				if(option_no==0)
				{
					exit_flag=edit_screen(&FACT.factory[(page_no*4)+option_no],4,1299);
					POW.power_status_flag=1;//2-04
				}
				else if(option_no==3)
				{
					exit_flag=serialno_screen(&FACT.factory[(page_no*4)+option_no],99999);
					if(auto_lock_time)
					{
						POW.power_status_flag=1;
					}
				}
				if(option_no==0||option_no==3)
				{
//					if(exit_flag)
//					{
//						POW.power_status_flag=1;//2-04
//					}
				}
			}

			else
			{
				if(option_no == 1)
				{
					if(!edit_flag)
					{
						edit_flag = 1;
						TFT_ST7789V_left_Right_arrow_14_arial(92,190,0,LIGHT_GRAY,BLACK);
						TFT_ST7789V_left_Right_arrow_14_arial(92,260,1,LIGHT_GRAY,BLACK);
						edit_subsetting_frame();
					}

					else
					{
						edit_flag = 0;
						TFT_ST7789V_left_Right_arrow_14_arial(92,190,0,LIGHT_GRAY,LIGHT_GRAY);
						TFT_ST7789V_left_Right_arrow_14_arial(92,260,1,LIGHT_GRAY,LIGHT_GRAY);

						Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to edit",(uint8_t*)"OK",1,14);
					}


				}

				else if(option_no==2)
				{
					used_hrs();
					POW.power_status_flag=1;//2-04

				}
				else if(!option_no)
				{

				   reset_var  = Passcode(1);

//				   Font_Select(ARIAL_14);
//				   TFT_Number(50,70,reset_var,YELLOW,RED);

				   delay_secs(2);
				   if((reset_var==1)||(reset_var==2))
				   {
					   reset_fun(reset_var);
					   shutting_down();
					   ON_Flag=0;
					   CLRSCR(BLACK);
					   break;
				   }
//				      Passcode(0);
//
//					if(password_one_flag)
//					{
//						Packing_reset();
//						password_one_flag=0;
//					}
//
//					else if(password_two_flag)
//					{
//						Complete_Reset();
//						password_two_flag=0;
//					}
//
//					else
//					{
//					//	POW.power_status_flag=1;//2-04
//					}
					POW.power_status_flag=1;

				}
			}
			//POW.power_status_flag=1;//2-04

			EEPROM_datawrite(EEPROM_QC_TRACK,G_qc_track,1);
			EEPROM_datawrite(EEPROM_SERIAL_NO,FACT.factory[3],3);
			EEPROM_datawrite(EEPROM_MFG_MON_YEAR,FACT.factory[0],2);

			while(KEY.value);
			break;


			case BACK_KEY:
			beep_sound();
			factory_var=0;


			while(KEY.value);
			break;

		}
	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void factory_Frame(void)
{
	uint8_t limit_count = 0;

	Rectangle(0,35,317,169,MAIN_FRAME_COL);

	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Factory Setting");	// header
//	for(limit_count = 1; limit_count <=3 ; limit_count++)				//no of lines
//	{
//		Rectangle(7,34+(43*limit_count),290,0, BLACK);		// no of rect line
//	}
   	Rectangle_Line_function(1,3);

	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to edit",(uint8_t*)"OK",1,14);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void factory_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[9])
{

	uint8_t loop = 0;
	uint8_t opt_no  = 0;
	uint32_t back_colour = 0;
	uint32_t text_colour = 0;
	uint32_t value=0;


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

		value = FACT.factory[(page*4)+opt_no];

		TFT_ST7789V__rectangle_curve(3,35+(43*(opt_no)),41,290,0,back_colour);

		Font_Select(ARIAL_14);

		TFT_String(9,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),(uint8_t*)array[(page*4)+opt_no],back_colour,text_colour);



		if( ((page==1) && (opt_no==0)) ||((page==1) && (opt_no==2)))
		{

		}

		else
		{
			TFT_String(170,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),(uint8_t*)":",back_colour,text_colour);
		}


		if(!page)
		{
			Font_Select(ARIAL_14);

			if(opt_no==0)
			{
				TFT_Number(200,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),(value/100),back_colour,text_colour);

				if(value<1000)
				{

					TFT_String(215,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
					(uint8_t*)"/",back_colour,text_colour);

					TFT_Number(225,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
					(value%100),back_colour,text_colour);

				}
				else
				{

					TFT_String(225,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
					(uint8_t*)"/",back_colour,text_colour);

					TFT_Number(235,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
					(value%100),back_colour,text_colour);

				}

			}
			else if(opt_no==1)
			{
				TFT_String(190,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),(uint8_t*)"NEON-S",back_colour,text_colour);
			}

			else if(opt_no==2)
			{
				TFT_String(190,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),(uint8_t*)"0.01",back_colour,text_colour);
			}

			else if(opt_no==3)
			{
				TFT_Number(200,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),value,back_colour,text_colour);
			}
		}

		else
		{
			if(opt_no==1)
			{
				Font_Select(ARIAL_14);
				TFT_String(220,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),(uint8_t*)qc_track[G_qc_track],back_colour,text_colour);
			}
		}


	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void factory_Opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
{


	uint32_t value = 0;
	uint32_t back_colour = 0;
	uint32_t text_colour = 0;
    uint8_t loop_count=0;


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

		value = FACT.factory[(page*4)+loop_count];

		Font_Select(ARIAL_14);

		TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),(uint8_t*)factory_menu[(page*4)+loop_count],back_colour,text_colour);

		if( ((page==1) && (loop_count==0)) ||((page==1) && (loop_count==2)))
		{

		}

		else
		{
		  TFT_String(170,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),(uint8_t*)":",back_colour,text_colour);
		}

		if(!page)
		{
			Font_Select(ARIAL_14);
			if(loop_count==0)
				{
					TFT_Number(200,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),(value/100),back_colour,text_colour);

					if(value<1000)
					{

						TFT_String(215,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
						(uint8_t*)"/",back_colour,text_colour);

						TFT_Number(225,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
						(value%100),back_colour,text_colour);

					}
					else
					{

						TFT_String(225,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
						(uint8_t*)"/",back_colour,text_colour);

						TFT_Number(235,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
						(value%100),back_colour,text_colour);

					}
				}

			else if(loop_count==1)
			{

				TFT_String(190,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),(uint8_t*)"NEON-S",back_colour,text_colour);

			}
			else if(loop_count==2)
			{

				TFT_String(190,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),(uint8_t*)"0.01",back_colour,text_colour);
			}

			else if(loop_count==3)
			{
				TFT_Number(200,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),value,back_colour,text_colour);
			}
		}
		else
		{

			if(loop_count==1)
			{
				Font_Select(ARIAL_14);
				TFT_String(220,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),(uint8_t*)qc_track[G_qc_track],back_colour,text_colour);

			}
		}

	}


}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void factory_subsetting(uint8_t option_no,uint8_t page_no ,uint8_t INC_flag)
{

	uint8_t* factory_data[2] = {0,&G_qc_track};
	uint8_t max_value[2] =  {0,25};
	uint8_t cur_value = 0;
	uint8_t pre_value = 0;

	cur_value	= *factory_data[option_no];
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
			cur_value=0;
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
			cur_value=25;
		}
	}

	Font_Select(ARIAL_14);
	TFT_String(220,INITIAL_TEXT_POS+((option_no)*VER_TEXT_SPACE),(uint8_t*)qc_track[pre_value],LIGHT_GRAY,LIGHT_GRAY);

	TFT_String(220,INITIAL_TEXT_POS+((option_no)*VER_TEXT_SPACE),(uint8_t*)qc_track[cur_value], LIGHT_GRAY,BLACK);

	*factory_data[option_no]=cur_value;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void used_hrs(void)
{
	uint8_t exit_flag=1;
	uint8_t fact_longpress=0;
	//uint8_t check_flag=0;
	POW.power_status_flag=1;//26-03

	while(exit_flag)
	{
		Power_off();

		if(!ON_Flag) 	//MAIN.main_power_status_flag == 1 )
		{
		  break;//23-03
		}

		else if(POW.power_status_flag)
		{
			POW.power_status_flag=0;//26-03
			used_hrs_info_frame();
			used_hrs_info_Opt_Frame();
		}
		if(!KEY.value)
		{
			fact_longpress=0;
		}

		switch(KEY.value)
		{

		case BACK_KEY:

			beep_sound();
			exit_flag=0;

			while(KEY.value);
			break;

		}
	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void used_hrs_info_frame(void)
{
	uint8_t sys_sett_count = 0;
	Rectangle(0,36,320,169,MAIN_FRAME_COL);
	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Used Hours");	// header

	for(sys_sett_count = 1; sys_sett_count <=3 ; sys_sett_count++)	//no of lines
	{
		Rectangle(7,34+(43*sys_sett_count),290,0, BLACK);			// no of rect line
	}

	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to Exit",(uint8_t*)"BK",2,14);

}

/**************************************************************************
 *Function Name :void device_info_Opt_Frame()
 *Arguments     :void
 *Return        :void
 *Description	:In this function to used device info option  frame
***************************************************************************/


void used_hrs_info_Opt_Frame()
{
    uint8_t loop_count=0;
    uint16_t used_hrs_info_data[5]={UTILIZED.device_hrs_cnt,UTILIZED.battery_hrs_cnt,UTILIZED.running_hrs_cnt,UTILIZED.factory_used_hrs};
	uint16_t value = 0;
    uint32_t back_colour=0;
    uint32_t text_colour=0;

	for(loop_count=0;loop_count<4;loop_count++)
	{
		back_colour	= MAIN_FRAME_COL;
		text_colour = WHITE;

		value = used_hrs_info_data[loop_count];
		Font_Select(ARIAL_14);
		TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE)
		,(uint8_t*)used_hrs_info_menu[loop_count],back_colour,text_colour);

		TFT_String(160,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE)
		,(uint8_t*)":",back_colour,text_colour);
		TFT_Number(180,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
		value,back_colour,text_colour);
	}

}

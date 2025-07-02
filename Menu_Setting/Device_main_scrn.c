#include "LPC55S16.h"
#include "Shapes.h"
#include "Color.h"
#include "Keypad.h"
#include "TFT_Commands.h"
#include "TFT_String.h"
#include "Flowrate_Screen.h"
//#include "Brand.h"
//#include "Drug_List.h"
#include "Occlusion.h"
#include "Bolus_Header.h"
#include "Power_off.h"
#include"Driver_I2C.h"    //23-03
#include "FR_CALC.h"
#include "factory.h"
#include "sound.h"
//#include "../Menu_Setting/Main_Menu.h"
//#include "../Menu_Setting/Main_Menu.h"
#include "Header.h"
#include "consumed_hrs.h"
#include "Power_off.h"
//#include "factory.h"
#include "Boot_up.h"


uint8_t G_infusion_mode_opt=0;
uint8_t G_bright_level=0;
uint8_t G_sound_level=0;
uint8_t G_device_info=0;
uint8_t G_infusion_modes;
uint8_t G_drug_list=0;
uint8_t G_lock_time=0;
uint8_t G_last_data=0;

extern uint8_t edit_flag ;
extern uint32_t back_colour ;
extern uint32_t text_colour;
extern volatile uint8_t waitingtime_1;
extern uint8_t ON_Flag;
extern uint8_t auto_lock_time;  //ZOOZ_1
extern uint8_t soundduration;

uint8_t G_pro_name;
uint8_t G_pro_model;
uint8_t G_sw_version;
uint8_t G_used_hrs;
uint8_t bright_ctrl[5]={1,3,5,7,0};



//const char* device_sett_menu[3]={"Brightness  Lvl","Sound  Lvl","Device Info"};

const char* device_sett_menu[2][4]={
		                             {"About(Help)","Bright Level","Sound Level","Auto Lock"},
		                             {"Last data","Infusion modes","Drug List"}
		                           };

const char* infusion_modes_options[4]={"Flowrate","Target","Dose rate","Ask every time"};

const char* device_info_menu[5]={"Product","Model","S.no","SW Ver","Used hrs"};//25-03

const char* device_info_values[2][1]={{"Syringe Pump"},{"NEON-S"}};
									  //{"V-0.01"},{"00.00.00"}};//25-03

const char* device_values[2][4][6]={
									  {
										  {                    },
										  {"1","2", "3","4","5"},//,"6","7","8","9","10"},
										  {"1","2","3","4","5"},
										  {"OFF","1 min","5 min","10 min",""}
									  },

									  {
										  {"ON","OFF","","",""},
										  {"F/R","Target","Dose","Ask",""},
										  {"No","Yes","",""},
										  {"ON","OFF","","",""},
									  }
 	 	 	 	 	 	 	 	 };

const uint32_t dev_col[2][2] =
		{
		    {LIGHT_GRAY, BLACK},
		    {LIGHT_GRAY, LIGHT_GRAY}
		};

extern void device_sett_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[2][4]);
extern uint16_t Passcode(uint16_t mode);//23-03
extern void scroll_bar(uint8_t page_no,uint8_t option_no,uint8_t total_option);     //23-03                                  //(uint8_t prev_option, uint8_t curr_option, uint8_t page)
extern void infusion_sett_Screen();
extern void infusion_mode_sett_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[4]);
extern void factory_setting();
extern void device_sett_frame(void);
extern void device_sett_Opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
extern void edit_subsetting_frame(void);

void about_fun(void);
void Device_sett_EEPROM_write();

uint8_t G_drug_list;//23-03
uint8_t G_screen_saver;

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t device_sett_Screen()
{
	uint8_t page_no=0;
	uint8_t option_no=0;
	uint8_t prev_option = 0;
	uint8_t device_variable=1;
	uint8_t edit_flag=0;
	uint8_t end_opt_no=0;
//	uint8_t fact_longpress=0;
//	uint8_t check_flag=0;
	uint8_t total_option=7;
	uint8_t down_opt_arr[3]={3,2,2};
	uint8_t up_opt_arr[3][2]={	{3,3},
								{2,3},
								{1,1}
							 };
    uint16_t arrow_pos[4]={280,280,280,280};
    uint16_t hor_arrow_pos[4]={0,40,83,124};

	POW.power_status_flag=1;
	auto_lock_time=AUTO_EXIT_TIME;

	while(device_variable)
	{
		  Power_off();

		if(!ON_Flag)
		{
			break; //26-03
		}

		else if(POW.power_status_flag)
		{
			POW.power_status_flag=0;
			device_sett_frame();
			device_sett_Opt_Frame(page_no,option_no,3);//23-03
			scroll_bar(page_no,option_no,total_option); //23-03

			if( (edit_flag)	&& (option_no==1 || option_no==2 || option_no==3) )
			{
			   edit_subsetting_frame();
			}
			if(edit_flag)
			{
				if(option_no)
				{
					TFT_ST7789V_left_Right_arrow_14_arial(50+hor_arrow_pos[option_no],190,0,LIGHT_GRAY,BLACK);
					TFT_ST7789V_left_Right_arrow_14_arial(50+hor_arrow_pos[option_no],280,1,LIGHT_GRAY,BLACK);
				}
			}
			while(KEY.value);
		}

		if(KEY.value)
		{
			auto_lock_time=AUTO_EXIT_TIME;
		}

		if(!auto_lock_time)
		{
			device_variable=0;
			break;
		}

		switch(KEY.value)
		{
			case DOWN_KEY :   //DOWN_KEY

			beep_sound();//23-03
			if(!edit_flag)
			{
				if( (page_no==0 && option_no<3)  || (page_no==1 && option_no<2) )
				{
					option_no++;
					if(option_no!=prev_option)
					{
						device_sett_cursor(prev_option,option_no,page_no,device_sett_menu);
						prev_option = option_no;
					}
				}

				else
				{
					page_no++;

					if(page_no>=2)
					{
						page_no=0;
					}

					option_no=0;
					prev_option=option_no;
					end_opt_no=down_opt_arr[page_no];  //REW1

					//device_sett_frame();
					CENTERSCR();
					Rectangle_Line_function(1,3);
					device_sett_Opt_Frame(page_no,0,end_opt_no);
				}

				scroll_bar(page_no,option_no,total_option);//25-03
			}

			while(KEY.value);
			break;

			case UP_KEY:           //UP_KEY

			beep_sound();	   //23-03

			if(!edit_flag)
			{
				if((page_no==0 && option_no>0)  || (page_no==1 && option_no>0))
				{
					option_no--;
					if(option_no!=prev_option)
					{
						device_sett_cursor(prev_option,option_no,page_no,device_sett_menu);
						prev_option = option_no;
					}
				}

				else
				{

					if(!page_no)
					{
						page_no++;
						prev_option=2;
					}

					else
					{
						page_no--;
						prev_option=3;
					}

					option_no=up_opt_arr[page_no][0];
					end_opt_no=up_opt_arr[page_no][1];

					//device_sett_frame();
					CENTERSCR();
					Rectangle_Line_function(1,3);
					device_sett_Opt_Frame(page_no,option_no,end_opt_no);
				}


			}
				scroll_bar(page_no,option_no,total_option);//25-03

			while(KEY.value);
			break;

			case RIGHT_KEY:				 //LEFT_KEY:

			beep_sound();//23-03
			if(edit_flag)
			{
				device_subsetting( option_no,page_no,1);
			}

			while(KEY.value);
			break;

			case LEFT_KEY:				 //RIGHT_KEY:
			beep_sound();
			if(edit_flag)
			{
				device_subsetting( option_no,page_no,0);
			}

			while(KEY.value);
			break;

			case OK_KEY: 					 //OK_KEY

		  beep_sound();                      //23-03

		  if(page_no==1 && option_no==1)
		  {
			  infusion_sett_Screen();
			  if(auto_lock_time)
			  {
				  POW.power_status_flag=1;
			  }
			  page_no=1;
			  end_opt_no=3;
		  }

		  if ((!edit_flag))	   //&& ((option_no<=3)) )) //&& ((page_no==1) && (!option_no)) )
		  {
              if( ((!page_no) && (option_no))  || ((page_no==1) && (!option_no || option_no==2)) )
              {
				  TFT_ST7789V_left_Right_arrow_14_arial(50 + (option_no ? hor_arrow_pos[option_no] : 0), 190, 0, dev_col[0][0], dev_col[0][1]);
				  TFT_ST7789V_left_Right_arrow_14_arial(50 + (option_no ? hor_arrow_pos[option_no] : 0),arrow_pos[option_no], 1, dev_col[0][0], dev_col[0][1]);
				  edit_subsetting_frame();
				  edit_flag = 1;
              }
		  }

		  else
		  {

			 TFT_ST7789V_left_Right_arrow_14_arial(50 + (option_no ? hor_arrow_pos[option_no] : 0), 190, 0, dev_col[1][0], dev_col[1][1]);
			 TFT_ST7789V_left_Right_arrow_14_arial(50 + (option_no ? hor_arrow_pos[option_no] : 0), arrow_pos[option_no], 1, dev_col[1][0], dev_col[1][1]);
			 Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to edit",(uint8_t*)"OK",1,14);
			 edit_flag = 0;

		  }

			if(option_no==0 && (page_no==0))
			{
				about_fun();//23-03
				edit_flag = 0;
				if(auto_lock_time)
				{
				  POW.power_status_flag=1;
				}
			}

			Device_sett_EEPROM_write();

			while(KEY.value);
			break;

			case BACK_KEY: 					 //BACK_KEY

			beep_sound();
			device_variable=0;

			while(KEY.value);
			break;
		}
	}
	return 0;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void device_sett_frame(void)
{

	uint8_t device_sett_count = 0;

	Rectangle(3,36,300,169,MAIN_FRAME_COL);
	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Device Setting");	// header
	Rectangle_Line_function(1,3);
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to edit",(uint8_t*)"OK",1,14);

}

/**************************************************************************
 *Function Name :void sys_sett_Opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
 *Arguments     :uint8_t page,uint8_t start_opt,uint8_t end_opt
 *Return        :void
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

void device_sett_Opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
{

	 uint8_t device_sett_data[2][4] = {
					 	 	 	 	 	 	 {0,G_bright_level,G_sound_level,G_lock_time},
											 {G_last_data,G_infusion_mode_opt,G_drug_list,G_screen_saver}
									  };

	uint8_t loop_count=0;
	uint16_t value = 0;
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

		value = device_sett_data[page][loop_count];

		Font_Select(ARIAL_14);
		TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE)
		,(uint8_t*)device_sett_menu[page][loop_count],back_colour,text_colour);

		if(  ( (page==0)&& (loop_count==1 || loop_count==2 || loop_count==3) )   || (      (page==1)&& (loop_count==0 || loop_count==1 || loop_count==2) ))
		{

//			TFT_String(200,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
//			(uint8_t*)device_values[page][loop_count][value],back_colour,text_colour);

			TFT_String_align(190,280,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),(uint8_t *)device_values[page][loop_count][value],0,back_colour,text_colour);


			TFT_String(180,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE)
			,(uint8_t*)":",back_colour,text_colour);

		}
	}

}

/**************************************************************************
 *Function Name :void sys_sett_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[3])
 *Arguments     :uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[3]
 *Return        :void
 *Description	:In this function to change the current cursor position
***************************************************************************/

void device_sett_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[2][4])
{
	const uint8_t device[2][4] = {
				 	 	 	 	 	 	 {0,G_bright_level,G_sound_level,G_lock_time},
										 {G_last_data,G_infusion_mode_opt,G_drug_list,G_screen_saver}
								 };
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

	    if(   (page==0 && (opt_no==1 ||  opt_no==2 ||  opt_no==3)  ) ||  (page==1 && (opt_no<=3) ) )
	    {
//		TFT_String(200,INITIAL_TEXT_POS+((opt_no)*VER_TEXT_SPACE),
//		(uint8_t*)device_values[page][opt_no][device[page][opt_no]],back_colour,text_colour);

		TFT_String_align(190,280,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
	    (uint8_t *)device_values[page][opt_no][device[page][opt_no]],0,back_colour,text_colour);

		TFT_String(180,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE)
		,(uint8_t*)":",back_colour,text_colour);
		}

	}
}

/**************************************************************************
 *Function Name :void kvo_subsetting(uint8_t option_no,uint8_t page_no, uint8_t INC_flag)
 *Arguments     :uint8_t option_no,uint8_t page_no, uint8_t INC_flag
 *Return        :void
 *Description	:In this function array arguments print as right side
***************************************************************************/

void device_subsetting(uint8_t option_no,uint8_t page_no, uint8_t INC_flag)
{
	uint8_t* device_data[2][4] = {
			 	 	 	 	 	 	 {0,&G_bright_level,&G_sound_level,&G_lock_time},
									 {&G_last_data,&G_infusion_mode_opt,&G_drug_list}
								 };

	uint8_t max_value[2][4] = {
			                   {0,4,4,3},
							   {1,0,1}//max array elements
							  };
	uint8_t cur_value = 0;
	uint8_t pre_value = 0;
	cur_value	= *device_data[page_no][option_no];//0
	pre_value	= cur_value;

	if(INC_flag)
	{

		if(cur_value < max_value[page_no][option_no])
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
			cur_value=max_value[page_no][option_no];

		}

	}


	if(pre_value != cur_value)
	{
		Font_Select(ARIAL_14);
//		TFT_String(200,INITIAL_TEXT_POS+((option_no)*VER_TEXT_SPACE),
//		(uint8_t*)device_values[page_no][option_no][pre_value],LIGHT_GRAY,LIGHT_GRAY);
		TFT_String_align(190,280,INITIAL_TEXT_POS+(option_no*VER_TEXT_SPACE),
		(uint8_t *)device_values[page_no][option_no][pre_value],0,LIGHT_GRAY,LIGHT_GRAY);

		Font_Select(ARIAL_14);
//		TFT_String(200,INITIAL_TEXT_POS+((option_no)*VER_TEXT_SPACE),
//		(uint8_t*)device_values[page_no][option_no][cur_value],LIGHT_GRAY,BLACK);
		TFT_String_align(190,280,INITIAL_TEXT_POS+(option_no*VER_TEXT_SPACE),
		(uint8_t *)device_values[page_no][option_no][cur_value],0,LIGHT_GRAY,BLACK);

	}
	*device_data[page_no][option_no] = cur_value;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void device_info_frame(void)
{
	uint8_t sys_sett_count = 0;
	Rectangle(0,36,320,203,MAIN_FRAME_COL);
	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Device Info");	// header

//	for(sys_sett_count = 1; sys_sett_count <=4 ; sys_sett_count++)				//no of lines
//	{
//		Rectangle(7,34+(43*sys_sett_count),290,0, BLACK);		// no of rect line
//	}
   	Rectangle_Line_function(1,4);

}

/**************************************************************************
 *Function Name :void device_info_Opt_Frame()
 *Arguments     :void
 *Return        :void
 *Description	:In this function to used device info option  frame
***************************************************************************/

void device_info_Opt_Frame()
{
//	uint16_t device_info_data[5]={G_pro_name,G_pro_model,FACT.factory[3],VERSION,UTILIZED.device_hrs_cnt};
	uint16_t value = 0;
	uint16_t device_info_data[5]={G_pro_name,G_pro_model,FACT.factory[3],VERSION,UTILIZED.device_hrs_cnt};

    uint8_t loop_count=0;

	for(loop_count=0;loop_count<=4;loop_count++)
	{
	back_colour	= MAIN_FRAME_COL;
	text_colour = WHITE;

	value = device_info_data[loop_count];

	Font_Select(ARIAL_14);
	TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE)
	,(uint8_t*)device_info_menu[loop_count],back_colour,text_colour);

	TFT_String(115,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE)
	,(uint8_t*)":",back_colour,text_colour);

	if(loop_count<2)
	{
		TFT_String(125,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
		(uint8_t*)device_info_values[loop_count][value],back_colour,text_colour);
	}

	else if((loop_count==2)||(loop_count==4))
	{
		TFT_Number(125,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
		device_info_data[loop_count],back_colour,text_colour);
	}

	else if(loop_count==3)
		{
		TFT_writenumber_float(125,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),
			device_info_data[loop_count],back_colour,text_colour);
		}
	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void about_fun(void)
{
	uint8_t exit_flag=1;
	uint8_t fact_longpress=0;
	uint8_t check_flag=0;
	POW.power_status_flag=1;

	while(exit_flag)
	{
//		Font_Select(ARIAL_14);
//	    TFT_Number(0,70,100,YELLOW,RED);

		Power_off();//27-03
//		Font_Select(ARIAL_14);
//		TFT_Number(50,70,fact_longpress,YELLOW,RED);

		if(!ON_Flag)
		{
			break;//26-03
		}

		else if(POW.power_status_flag)//27-03
		{
		   POW.power_status_flag=0;//27-03
		   device_info_frame();
		   device_info_Opt_Frame();
		}

			if(KEY.value)
			{
				auto_lock_time=AUTO_EXIT_TIME;
			}

			if(!auto_lock_time)
			{
			 // menu_variable=0;
				break;
			}



		switch(KEY.value)
		{
		case  BOLUS_KEY:                         //MUTE_KEY:
						//check_flag=0;
			beep_sound();
				if(fact_longpress==0)
				{
					waitingtime_1=2;
					fact_longpress=1;
					while(KEY.value==BOLUS_KEY && fact_longpress)
					{
						if(!waitingtime_1)
						{
							check_flag=Passcode(0);
							if(check_flag)
							{
								factory_setting();
							}
							if(auto_lock_time)
							{
								POW.power_status_flag=1;
							}
							fact_longpress=0;
						}
					}
				}
				if(fact_longpress==1)
				{
					fact_longpress=0;
				}
				break;

		case BACK_KEY:

			beep_sound();
			exit_flag=0;
			while(KEY.value);
			break;


		}
	}

}

/**************************************************************************
 *Function Name :void device_info_Opt_Frame()
 *Arguments     :void
 *Return        :void
 *Description	:In this function to used device info option  frame
***************************************************************************/

void infusion_modes_Opt_Frame()
{
	uint8_t device_sett_count = 0;
	Rectangle(0,36,320,169,MAIN_FRAME_COL);
	Rectangle(0,0,320,34,NEW_HDR_COL);

	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Infusion modes");	// header

	for(device_sett_count = 1; device_sett_count <=3 ; device_sett_count++)				//no of lines
	{
		Rectangle(7,34+(43*device_sett_count),290,0, BLACK);		// no of rect line
	}

	Rectangle(0,206,320,34,NEW_FTR_COL);
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to select",(uint8_t*)"OK",1,14);
}

/**************************************************************************
 *Function Name :void sys_sett_Opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
 *Arguments     :uint8_t page,uint8_t start_opt,uint8_t end_opt
 *Return        :void
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

void infusion_mode_sett_Opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
{

	uint32_t back_colour = 0;
	uint32_t text_colour = 0;
    uint8_t loop_count=0;
	uint32_t tick_colour=0;


	for(loop_count=0;loop_count<end_opt;loop_count++)
	{
		if(loop_count == start_opt)//0==0
		{
			back_colour	= LIGHT_GRAY;
			text_colour = BLACK;
			tick_colour=MAIN_FRAME_COL;
			TFT_ST7789V__rectangle_curve(3,35+(43*(start_opt)),41,290,0,back_colour); //0
		}
		else
		{
			back_colour	= MAIN_FRAME_COL;
			text_colour = WHITE;
			tick_colour=GOLD;
		}

		Font_Select(ARIAL_14);
		TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE)
		,(uint8_t*)infusion_modes_options[loop_count],back_colour,text_colour);
		 if(G_infusion_mode_opt==loop_count)
		 {
		  TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS)+(loop_count)*VER_TEXT_SPACE_1,250,0,back_colour,tick_colour);
		 }

	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void infusion_sett_Screen()
{
	uint8_t page_no=0;
	uint8_t option_no=0;
	uint8_t prev_option = 0;
	uint8_t device_variable=1;
	uint8_t edit_flag=0;
	uint8_t end_opt_no=0;
	POW.power_status_flag=1;//27-03

	while(KEY.value);
	while(device_variable)
	{


	  Power_off();//27-03

	if(!ON_Flag)
	{
		break;//26-03
	}

	else if(POW.power_status_flag)//27-03
	{
		POW.power_status_flag=0;//27-03
		infusion_modes_Opt_Frame();
		infusion_mode_sett_Opt_Frame(0,option_no,4);
    }

	if(KEY.value)//common_bug  //ZOOZ_1
	{
	   auto_lock_time=AUTO_EXIT_TIME;
	}

	else if(!auto_lock_time)
	{
		device_variable=0;
	  // break;
	}

		switch(KEY.value)
			{
				case DOWN_KEY :   //DOWN_KEY
					beep_sound();
					if(!edit_flag)
				   {
					if( (page_no==0) && (option_no<3) )
					{
						option_no++;
					}

					else
					{
						option_no=0;
						page_no=0;
					//  prev_option=0;
						end_opt_no=4;
					}

					if(option_no!=prev_option)
					{
						infusion_mode_sett_cursor(prev_option,option_no,page_no,infusion_modes_options);
						prev_option = option_no;
					}

				 }
				while(KEY.value);
				break;

				case UP_KEY:     //UP_KEY
					beep_sound();
					if(!edit_flag)
				  {
					if(page_no==0 && option_no>0)
					{
						option_no--;
					}
					else
					{
						option_no=3;
						page_no=0;
						end_opt_no=4;
					}

					if(option_no!=prev_option)
					{
						infusion_mode_sett_cursor(prev_option,option_no,page_no,infusion_modes_options);
						prev_option = option_no;
					}
				}
				while(KEY.value);
				break;

				case OK_KEY: 					 //OK_KEY
				beep_sound();
				G_infusion_mode_opt=option_no;
				EEPROM_datawrite(EEPROM_G_infusion_modes,G_infusion_mode_opt,1);
				device_variable=0;
				while(KEY.value);
				break;

				case BACK_KEY: 	//23-03				 //BACK_KEY

				beep_sound();
				device_variable=0;
			//	Rectangle(3,36,300,169,MAIN_FRAME_COL);
				while(KEY.value);
				break;
	}
}
}

/**************************************************************************
 *Function Name :void sys_sett_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[3])
 *Arguments     :uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[3]
 *Return        :void
 *Description	:In this function to change the current cursor position
***************************************************************************/

void infusion_mode_sett_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[4])
{

	uint8_t loop = 0;
	uint8_t opt_no  = 0;
	uint32_t back_colour = 0;
	uint32_t text_colour = 0;
	uint32_t tick_colour=0;

	for(loop = 0; loop<2; loop++)
	{
		if(!loop)
		{
			back_colour = MAIN_FRAME_COL;
			text_colour = WHITE;
			tick_colour=GOLD;
			opt_no		= prev_option;
		}
		else
		{
			back_colour = LIGHT_GRAY;
			text_colour = BLACK;
			tick_colour=MAIN_FRAME_COL;
			opt_no= curr_option;
		}
		TFT_ST7789V__rectangle_curve(3,35+(43*(opt_no)),41,290,0,back_colour);

		Font_Select(ARIAL_14);
		TFT_String(9,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),
		(uint8_t*)array[opt_no],back_colour,text_colour);
		if(G_infusion_mode_opt==opt_no)
				 {
				  TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS)+(opt_no)*VER_TEXT_SPACE_1,250,0,back_colour,tick_colour);
				 }
	}
}

void Device_sett_EEPROM_write()
{
            EEPROM_datawrite(EEPROM_G_bright_level,G_bright_level,1);//23-03
			EEPROM_datawrite(EEPROM_G_sound_level,G_sound_level,1);
			EEPROM_datawrite(EEPROM_G_lock_time,G_lock_time,1);
			EEPROM_datawrite(EEPROM_LAST_DATA,G_last_data,1);
			EEPROM_datawrite(EEPROM_G_drug_list,G_drug_list,1);
			EEPROM_datawrite(EEPROM_SCREEN_SAVER,G_screen_saver,1);
}

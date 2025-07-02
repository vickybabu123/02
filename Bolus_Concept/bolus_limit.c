#include "LPC55S16.h"
#include "Shapes.h"
#include "Color.h"
#include "Keypad.h"
#include "TFT_Commands.h"
#include "TFT_String.h"
#include "Flowrate_Screen.h"
#include "Main_Menu.h"
#include "Bolus_Header.h"
#include "Power_off.h"
#include "Driver_Timer.h"
#include "Power_off.h"
#include "Main_screen.h"
#include "Driver_I2C.h"
#include "sound.h"

extern uint8_t ON_Flag;
extern uint8_t edit_flag;
extern uint16_t xpos;
extern uint8_t auto_lock_time;

const char* bolus_limit_menu[7]={"2ml","5ml","10ml","20ml","30ml","50ml"};

uint16_t maxi_lmt[7]={5,30,40,50,50,50};
uint16_t first_lmt[7]={0,5,30,40,50,50,50};
uint16_t second_lmt[7]={5,0,0,0,0,0};

uint16_t min_limit=5;

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void bolus_limit_layout()
{
uint8_t loop=0;
Rectangle(3,36,315,169,MAIN_FRAME_COL);

for(loop=1;loop<=3;loop++)
{
	Rectangle(7,34+(43*loop),290,0, BLACK);

}
//	Rectangle(7,34+(43*1),290,0, BLACK);
//	Rectangle(7,34+(43*2),290,0,BLACK);
//	Rectangle(7,34+(43*3),290,0,BLACK);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void bolus_limit()
{
	uint8_t bolus_limit_var=1;
	uint8_t option_no=0;
	uint8_t page_no=0;
	uint8_t exit_flag=0;
	uint8_t prev_option = 0;
	uint8_t end_opt_no=0;

	auto_lock_time=AUTO_EXIT_TIME;
	end_opt_no=3;

	POW.power_status_flag=1;

	while(KEY.value);

	while(bolus_limit_var)
	{

		Power_off();

		if(!ON_Flag)

		{
			break;//26-03
		}

		else if(POW.power_status_flag)
		{
			POW.power_status_flag=0;//26-03
			bolus_limit_Frame();
			bolus_limit_Opt_Frame(page_no,option_no,end_opt_no);
			scroll_bar(page_no,option_no,6);//23-03
		}

		if(KEY.value)//common_bug//ZOOZ_1
		{
			auto_lock_time=AUTO_EXIT_TIME;
		}

		 if(!auto_lock_time)
		{
			//bolus_limit_var=0;
		    break;
		}//comm


	switch(KEY.value)
	{

		case DOWN_KEY :

			beep_sound();

		if(((page_no==1)&&(option_no<1))||((page_no==0)&&(option_no<3)))
		{
			option_no++;

			if(option_no!=prev_option)
			{
				bolus_limit_cursor(prev_option,option_no,page_no,bolus_limit_menu);
				prev_option = option_no;
			}
		}

		else
		{

			if(page_no<1)
			{
				option_no=0;
				end_opt_no=1;
				page_no++;
				prev_option=0;


			}
			else
			{
				option_no=0;
				end_opt_no=3;
				page_no=0;
				prev_option=0;

			}

			bolus_limit_layout();
			bolus_limit_Opt_Frame(page_no,option_no,end_opt_no);
		}
		scroll_bar(page_no,option_no,6);//23-03



		while(KEY.value);
		break;

		case UP_KEY:

		beep_sound();

		if(option_no)
		{
			option_no--;
			if(option_no!=prev_option)
			{

				bolus_limit_cursor(prev_option,option_no,page_no,bolus_limit_menu);
				prev_option = option_no;
			}
		}

		else
		{

			if(!page_no)
			{

					page_no=1;
				//	Rectangle(3,36,300,169,MAIN_FRAME_COL);
					option_no=1;
					end_opt_no=1;//22-03
					prev_option=1;
			}
			else
			{
					page_no=0;
				//	Rectangle(3,36,300,169,MAIN_FRAME_COL);
					option_no=3;
					end_opt_no=3;//22-03
					prev_option=3;
			}

			bolus_limit_layout();
			bolus_limit_Opt_Frame(page_no,option_no,end_opt_no);
		}
		scroll_bar(page_no,option_no,6);//23-03

		while(KEY.value);
		break;

		case OK_KEY:

			bolus_limit_Opt_Frame(page_no,option_no,end_opt_no);
			exit_flag=Flow_rate_screen(&BOL.limit[(page_no*4)+option_no],0,maxi_lmt[(page_no*4)+option_no],1);//22-03    min_limit
			if(auto_lock_time)
			{
				POW.power_status_flag=1;
			}
			EEPROM_datawrite(EEPROM_G_bol_limit+0 ,BOL.limit[0],2);
			EEPROM_datawrite(EEPROM_G_bol_limit+2 ,BOL.limit[1],2);
			EEPROM_datawrite(EEPROM_G_bol_limit+4 ,BOL.limit[2],2);

			EEPROM_datawrite(EEPROM_G_bol_limit+(((page_no*4)+option_no)*2) ,BOL.limit[((page_no*4)+option_no)],2);
		//	POW.power_status_flag=1;//26-03

			while(KEY.value);
			break;


		case BACK_KEY:

		bolus_limit_var=0;

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

void bolus_limit_Frame(void)
{
	uint8_t limit_count = 0;
	Rectangle(3,36,320,169,MAIN_FRAME_COL);

	Rectangle(0,0,320,34,NEW_HDR_COL);

	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Bolus limit");	// header

	for(limit_count = 1; limit_count <=3 ; limit_count++)				//no of lines
	{
		Rectangle(7,34+(43*limit_count),290,0, BLACK);		// no of rect line
	}

	Rectangle(0,206,320,34,NEW_FTR_COL);

	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to edit",(uint8_t*)"OK",1,14);

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void bolus_limit_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[7])
{

	uint8_t loop = 0;
	uint8_t opt_no  = 0;
	uint32_t back_colour = 0;
	uint32_t text_colour = 0;
	float value=0;
	char local_buffer[6];



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

		value = BOL.limit[(page*4)+opt_no];


		TFT_ST7789V__rectangle_curve(3,35+(43*(opt_no)),41,308,0,back_colour);


		Font_Select(ARIAL_14);

		TFT_String(9,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),(uint8_t*)array[(page*4)+opt_no],back_colour,text_colour);

		TFT_String(100,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),(uint8_t*)":",back_colour,text_colour);

		sprintf(local_buffer,"%.1f",((float)value/10));    //store the integer variables in to string using sprintf
		xpos=Right_Alignments((uint8_t*)local_buffer,263);    //(uint8_t*)letter

		TFT_writenumber_float_1d(xpos-33,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),value,back_colour,text_colour);

		TFT_String(240,INITIAL_TEXT_POS+(opt_no*VER_TEXT_SPACE),(uint8_t*)"ml",back_colour,text_colour);




	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void bolus_limit_Opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
{
	char local_buffer[6];
	float value = 0;

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


		value =BOL.limit[(page*4)+loop_count];

		Font_Select(ARIAL_14);

		TFT_String(9,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),(uint8_t*)bolus_limit_menu[(page*4)+loop_count],back_colour,text_colour);


		TFT_String(100,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),(uint8_t*)":",back_colour,text_colour);



		sprintf(local_buffer,"%.1f",((float)value/10));    //store the integer variables in to string using sprintf

		xpos=Right_Alignments((uint8_t*)local_buffer,263);    //(uint8_t*)letter


		TFT_writenumber_float_1d(xpos-33,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),value,back_colour,text_colour);

		TFT_String(240,INITIAL_TEXT_POS+(loop_count*VER_TEXT_SPACE),(uint8_t*)"ml",back_colour,text_colour);
	}
}

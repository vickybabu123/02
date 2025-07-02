/*
 * passcode_settings.c
 *
 *  Created on: 11-Oct-2023
 *      Author: SoftwareRND
 */

#include <stdio.h>
#include "LPC55S16.h"
#include "Driver_Timer.h"
#include "Driver_I2C.h"
//#include "Driver_PINT.h"
#include "Driver_ADC.h"
#include "Driver_SPI.h"
#include "Color.h"
#include "stdint.h"
#include "TFT_Commands.h"
#include "TFT_String.h"
#include"Keypad.h"
#include "Power_off.h"

extern uint8_t TFT_ST7789V_left_Right_arrow_14_arial(uint16_t xpos, uint16_t ypos_1,
                                         uint8_t arrow, uint32_t boarder_color, uint32_t fill_color);
extern uint8_t TFT_ST7789V_up_down_arrow_20_arial(uint16_t xpos, uint16_t ypos_1,
       uint8_t arrow, uint32_t boarder_color, uint32_t fill_color);

extern void TFT_Number(uint16_t xpos,uint16_t ypos,uint32_t number,uint32_t boarder_color,uint32_t fill_color);



uint8_t add_flag_1=0;
uint8_t position_2=0;
uint8_t array_dig_1[4];

char letter_1[2]={'\0','\0'} ;
extern uint16_t ypos_1;
extern uint8_t ON_Flag;

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void decimal_split_frame()
{
	uint8_t loop_count=0;
	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Year");
	option_footer_frame();
	for(loop_count=0;loop_count<=4;loop_count++)
	{
		Rectangle(70+(45*loop_count),68,0,115,BLACK);    //69///spliting
	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void decimal_Digit_Spiliting(uint16_t Value)
{
	//char letter_1[2]={'\0','\0'} ;
	uint8_t loop_count=0;
    uint16_t xpos=0;
	position_2=0;

	while(Value>0)
	{
		array_dig_1[position_2]=Value%10;
		Value=Value/10;
		position_2++;
	}


	for(loop_count=0;loop_count<position_2;loop_count++)
	{

		Font_Select(CALIBRI_43);

		letter_1[0] =array_dig_1[loop_count]+48;

		xpos=Letters_Alignments(70+(45*(loop_count)),
		70+(45*(loop_count+1)),(uint8_t*)letter_1,0);

		TFT_Number(xpos,CALIB_EDT_YPOS,array_dig_1[3-loop_count],MAIN_FRAME_COL,WHITE);
	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void decimal_option_scroll(uint8_t current_cur_no,uint8_t prev_cursor_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL,uint32_t UP_ARROW_ERASE)
{
	uint8_t loop	= 0;
	uint8_t Cursor_no   = 0;
	uint16_t xpos=0;
	uint32_t back_colour   = 0;
	uint32_t text_colour= 0;
	uint32_t arrow_fill_color = 0;
	uint32_t arrow_bg_color   = 0;
	char letter1[2]={'\0','\0'} ;
	for(loop = 0; loop<2; loop++)
	{

		if(!loop)
		{
			back_colour			= MAIN_FRAME_COL;
			text_colour 		= WHITE;
			Cursor_no			= prev_cursor_no;
			arrow_bg_color		= MAIN_FRAME_COL;
			arrow_fill_color	= MAIN_FRAME_COL;
		}

		else
		{
			back_colour 		= LIGHT_GRAY;
			text_colour  		= BLACK;
			Cursor_no			= current_cur_no;
			arrow_bg_color		= LIGHT_GRAY;
			arrow_fill_color	= BLACK;
		}

		TFT_ST7789V__rectangle_curve(71+(45*(3-Cursor_no)),64,125,43,0,back_colour);

		Font_Select(CALIBRI_43);
		letter1[0]=array_dig_1[Cursor_no]+48;
		xpos=Letters_Alignments(70+(45*(3-Cursor_no)),115+(45*(3-Cursor_no)),
				(uint8_t*)letter1,0);


		TFT_Number(xpos,CALIB_EDT_YPOS,array_dig_1[Cursor_no],back_colour,text_colour);
		TFT_ST7789V_up_down_arrow_20_arial(79,84+(45*(3-Cursor_no)),0,arrow_bg_color,arrow_fill_color);  		//UP_ARROW
		TFT_ST7789V_up_down_arrow_20_arial(166,84+(45*(3-Cursor_no)),1,arrow_bg_color,arrow_fill_color);
	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint16_t decimal_screen(uint16_t *Edit_value,uint16_t Min_Limit,uint32_t Max_Limit)
{
//	uint8_t Err_flag=0;
	uint8_t Cursor_no=0;
	uint8_t condition=1;
	uint16_t result=0;
	uint8_t prev_cursor_no=0;
	uint8_t space=0;
	uint16_t Value=0;
	uint16_t xpos=0;
	Value=*Edit_value;
	uint8_t loop_count=0;

	 char letter1[2]={'\0','\0'} ;

	for(loop_count=0;loop_count<=3;loop_count++)
	{
		array_dig_1[loop_count]=0;
	}

	decimal_split_frame();
	decimal_Digit_Spiliting(Value);
	decimal_option_scroll(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
	Left_Right_Indi(Cursor_no,0);
	prev_cursor_no=0;

	while(KEY.value);
	while(condition)
	{
		Power_off();//27-03
		if(!ON_Flag)
		{
			break;//26-03
		}

		else if(POW.power_status_flag)//27-03
		{
			POW.power_status_flag=0;//27-03
			decimal_split_frame();
			result=(array_dig_1[3]*1000)+(array_dig_1[2]*100)+(array_dig_1[1]*10)+(array_dig_1[0]*1);
			decimal_Digit_Spiliting(result);
			Left_Right_Indi(Cursor_no,0);
			decimal_option_scroll(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
		}


		switch(KEY.value)
		{
			case LEFT_KEY:

			beep_sound();
			if(Cursor_no<3)
			{
				Cursor_no++;
				decimal_option_scroll(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
				if(Cursor_no !=0 && Cursor_no !=2 )
				{
					Left_Right_Indi(Cursor_no,0);
				}

			}
			prev_cursor_no=Cursor_no;

			while(KEY.value);
			break;

			case RIGHT_KEY:

			beep_sound();
			if(Cursor_no>0)
			{
				Cursor_no--;
				decimal_option_scroll(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
				if(Cursor_no !=1 && Cursor_no !=3 )
				{
					Left_Right_Indi(Cursor_no,0);
				}

			}

			prev_cursor_no=Cursor_no;

			while(KEY.value);
			break;

			case UP_KEY:			//DOWN_KEY:	//22-03

		    beep_sound();
		    if(array_dig_1[Cursor_no]<9)
			{

				Font_Select(CALIBRI_43);
				letter1[0]=array_dig_1[Cursor_no]+48;
				xpos=Letters_Alignments(70+(45*(3-Cursor_no)),
				115+(45*(3-Cursor_no)), (uint8_t*)letter1,0);
				TFT_Number(xpos,CALIB_EDT_YPOS,array_dig_1[Cursor_no],CURSOR_COL,CURSOR_COL);

        		array_dig_1[Cursor_no]++;

				if( (array_dig_1[3]*1000+array_dig_1[2]*100+array_dig_1[1]*10+array_dig_1[0]*1) >Max_Limit)
				{
					array_dig_1[Cursor_no]--;

				}


				letter1[0]=array_dig_1[Cursor_no]+48;
				xpos=Letters_Alignments(70+(45*(3-Cursor_no)),
				115+(45*(3-Cursor_no)), (uint8_t*)letter1,0);

				TFT_Number(xpos,CALIB_EDT_YPOS,array_dig_1[Cursor_no],CURSOR_COL,BLACK);
				space=0;


			}

			else
			{
				WARN_SOUND(1,1,2);
			}

			while(KEY.value);
			break;

			case DOWN_KEY:				//UP_KEY:	//22-03

			beep_sound();

			if(array_dig_1[Cursor_no]>0)
			{


				Font_Select(CALIBRI_43);
				letter1[0]=array_dig_1[Cursor_no]+48;
				xpos=Letters_Alignments(70+(45*(3-Cursor_no))+space,
				115+(45*(3-Cursor_no))+space, (uint8_t*)letter1,0);
				TFT_Number(xpos,CALIB_EDT_YPOS,array_dig_1[Cursor_no],CURSOR_COL,CURSOR_COL);

        		array_dig_1[Cursor_no]--;

				if((array_dig_1[3]*1000+array_dig_1[2]*100+array_dig_1[1]*10+array_dig_1[0]*1) < Min_Limit)
				{
					array_dig_1[Cursor_no]++;
				}


				space=0;
			//	Font_Select(CALIBRI_43);
				letter1[0]=array_dig_1[Cursor_no]+48;
				xpos=Letters_Alignments(70+(45*(3-Cursor_no))+space,
				115+(45*(3-Cursor_no))+space, (uint8_t*)letter1,0);

				TFT_Number(xpos,CALIB_EDT_YPOS,array_dig_1[Cursor_no],CURSOR_COL,BLACK);
			}
			else
			{
				WARN_SOUND(1,1,2);
			}
			while(KEY.value);
			break;

			case OK_KEY:

			beep_sound();
			result=((array_dig_1[3]*1000)+(array_dig_1[2]*100)+(array_dig_1[1]*10)+(array_dig_1[0]*1));

			if(result>=2023)
			{
				*Edit_value=result;
				 condition=0;
			}

			else
			{
				POW.power_status_flag=1;
			}

			while(KEY.value);
			break;

			case BACK_KEY:

			beep_sound();
			condition=0;

			while(KEY.value);
			break;

		}
	}
}

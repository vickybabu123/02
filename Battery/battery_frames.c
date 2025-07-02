/*
 * battery_frame.c
 *
 *  Created on: Jun 22, 2024
 *      Author: Welcome
 */
#include <Boot_up.h>
#include "LPC55S16.h"
#include "Color.h"
#include "Driver_SPI.h"
#include "TFT_Commands.h"
#include "Shapes.h"
#include "TFT_String.h"
#include "clock_config.h"
#include "Main_screen.h"
#include "Bolus_Header.h"
#include "Dosage_mode.h"
#include "Occlusion.h" //23-04
#include "Driver_ADC.h"
#include "Driver_Timer.h"
#include <Power_off.h>
#include "Alarm.h"
#include "sound.h"
//battery BATT;

uint8_t G_Bt_Low_Flag=0;

extern uint8_t _1sec_delay;
extern uint8_t home_flag;
extern uint8_t home_return_flag;
extern uint8_t warning_flag[3];

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void battery_logo(void)
{

	Rectangle(20,BATTERY_POS,34,1,WHITE);				//Battery top line
	Rectangle(20,22+BATTERY_POS,34,1,WHITE);            //Battery Bottom Line
	Rectangle(19,BATTERY_POS,2,23,WHITE);               //First Left side Line
	Rectangle(53,BATTERY_POS,1,23,WHITE);               //Second Left side Line
	Rectangle(54,6+BATTERY_POS,5,10,WHITE);				//Battery outer rect

}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void battery_level(uint16_t xpos,uint8_t batt_lv1)
{

	uint32_t color[4][3]={
							{RED,			MAIN_FRAME_COL,		MAIN_FRAME_COL},
							{ORANGE,		MAIN_FRAME_COL,		MAIN_FRAME_COL},
							{ORANGE,		ORANGE,				MAIN_FRAME_COL},
							{LIGHT_GREEN,	LIGHT_GREEN,		LIGHT_GREEN}
						};

	Rectangle(26,4+xpos,4,14,color[batt_lv1][0]);			    //First  Rectangle Box
	Rectangle(35,4+xpos,4,14,color[batt_lv1][1]);			    //Second Rectangle Box
	Rectangle(44,4+xpos,4,14,color[batt_lv1][2]);               //Third Rectangle Box

}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void battery_charge_lvl(uint16_t xpos,uint8_t batt_lv1)
{

	uint32_t color[4][3]={
							{MAIN_FRAME_COL,	MAIN_FRAME_COL,		MAIN_FRAME_COL},
							{LIGHT_GREEN,		MAIN_FRAME_COL,		MAIN_FRAME_COL},
							{LIGHT_GREEN,		LIGHT_GREEN,		MAIN_FRAME_COL},
							{LIGHT_GREEN,		LIGHT_GREEN,		LIGHT_GREEN}
						};


	Rectangle(26,4+xpos,4,14,color[batt_lv1][0]);			    //First  Rectangle Box
	Rectangle(35,4+xpos,4,14,color[batt_lv1][1]);			    //Second Rectangle Box
	Rectangle(44,4+xpos,4,14,color[batt_lv1][2]);               //Third Rectangle Box

}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void battery_warning(uint8_t batt_lv1)
{
// uint8_t batt_lv1=0;

//	batt_lv1=BATT.percent/25;

//	    Font_Select(ARIAL_14);
//	    TFT_Number(170,70,home_flag,NAVY,RED);
//
//	    Font_Select(ARIAL_14);
//	    TFT_Number(200,70,BATT.mode,YELLOW,RED);
//
//	    Font_Select(ARIAL_14);
//	   	TFT_Number(250,70,batt_lv1,NAVY,WHITE);
//
//	    Font_Select(ARIAL_14);
//	   	TFT_Number(250,110,BATT.critical,NAVY,WHITE);

	if((BATT.percent>=35) && (BATT.percent<99))
	{
		BATT.low=0;
		warning_flag[2]=0;
	}

	if((BATT.mode)&&(home_flag))         //REW_UP
	{
			if((BATT.percent>=15) && (BATT.percent<25))//
			{
				//BATT.verify_cout++;
				if(!batt_lv1)
				{
					if(!BATT.low)						//&&(BATT.mode))
					{
						 BATT.low=1;
						 warning_flag[2]=1;
						 G_Bt_Low_Flag=BATT.low;
						// Warning_screen((uint8_t *)"Battery Low",0);
						// WARN_SOUND(3,1,3);
						 delay_secs(3);
						 Warning_Scr_Erase();
					}
				}
			}

			else if((BATT.percent>=10) && (BATT.percent<15))
			{
				if(!BATT.critical)
				{
				//	BATT.low=0;
					BATT.critical=1;
				//	Warning_Scr_Erase();
					Warning_screen((uint8_t *)"Battery critical",0);
					WARN_SOUND(3,1,3);
				  //warn_tone(5);
				}

			}

	if(BATT.mode)
	{
			 if(BATT.percent<10)
			{
				if(!BATT.empty)
				{

					BATT.low=0;
					BATT.empty=1;
					Alarm(BATTERY_ALM);

				}
			}
	}


	}

//	if(BATT.low)
//	{
//
//		BATT.low=0;
//	}
}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void Battery_symbol(void) //23-04
{
	uint8_t batt_lv1=0;

	batt_lv1=BATT.percent/25;
	battery_warning(batt_lv1);


	if(home_flag)
	{
		if(!BATT.mode)
		{
			if(!_1sec_delay)
			{
				battery_logo();
				if(BATT.full)
				{
					battery_charge_lvl(BATTERY_POS,3);
				}

				else
				{
					if(!BATT.charge_blink)
					{
						battery_charge_lvl(BATTERY_POS,batt_lv1);
						BATT.charge_blink=1;
					}

					else
					{

						if(batt_lv1)
						{
						battery_charge_lvl(BATTERY_POS,batt_lv1-1);
						}

						else
						{
						battery_charge_lvl(BATTERY_POS,batt_lv1+1);
						}
						BATT.charge_blink=0;

					}
				}
			}
			_1sec_delay=1;
		}

		else
		{
			if(((BATT.pre_lvl != batt_lv1) && (BATT.percent%3==0))||(home_return_flag))
			{
				battery_logo();
				home_return_flag=0;
				battery_level(BATTERY_POS,batt_lv1);
				BATT.pre_lvl=batt_lv1;
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
void plug_symbol(uint32_t plug_col) //23-04
{

	int8_t y_pos_adj=BATTERY_POS;
	int8_t x_pos_adj=-9;
	TFT_ST7789V_circle1(20+x_pos_adj,6+y_pos_adj,7,plug_col,plug_col);   //left quadrant circle for mains symbol
	TFT_ST7789V_circle3(20+x_pos_adj,6+y_pos_adj,7,plug_col,plug_col);   //right quadrant circle for mains symbol

	Rectangle(19+x_pos_adj,13+y_pos_adj,2,4,plug_col);               //mains symbol line
	Rectangle(17+x_pos_adj,y_pos_adj,1,3,plug_col);                 //left plugin line
	Rectangle(22+x_pos_adj,y_pos_adj,1,3,plug_col);                 //right plugin line
	Rectangle(16+x_pos_adj,4+y_pos_adj,8,2,plug_col);

	Rectangle(19+x_pos_adj,17+y_pos_adj,8,2,plug_col);
}

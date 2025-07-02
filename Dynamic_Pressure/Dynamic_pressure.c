/****************************************************************************
* File Name    :
* Developed by :
* Version      :
* Description  :

*****************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include "LPC55S16.h"
#include "Occlusion.h"
#include "Driver_Timer.h"
#include "Driver_I2C.h"
#include "Driver_PINT.h"
#include "Driver_ADC.h"
#include "Driver_SPI.h"
#include "Color.h"
#include "stdint.h"
#include "TFT_String.h"
#include "Flowrate_Screen.h"
#include "keypad.h"
//#include "Main_Menu.h"
#include "Main_Menu.h"
#include "Dynamic_Pressure.h"
#include "shapes.h"
#include "Main_screen.h"
//#include "Syringe_calib_header.h"


/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void dynamic_pressure(uint8_t pressure,uint8_t screen) //curved disp
{
	uint8_t loop_count;
	uint8_t loop_count1=0;
	volatile uint8_t dynamic_data[6][2]={
			{9,18},
			{6,12},
			{4,8},
			{2,4},
			{1,2},
			{0,0}
	};
//	volatile uint8_t dynamic_data1[6][2]={
//			{9,18},
//			{6,12},
//			{4,8},
//			{2,4},
//			{1,2},
//			{0,0}
//	};
	if(pressure>52)
	{
		pressure=52;
	}
	else if(pressure<2)
	{
		pressure=2;
	}
	pressure=54-pressure;
	if(screen)
	{
		TFT_ST7789V_lcd_drawcircle1(39,DYN_PRES_POS,16,BAR_COLOR,GRAY);
		Rectangle(24,DYN_PRES_POS,30,28,GRAY);
		TFT_ST7789V_lcd_drawcircle1(39,27+DYN_PRES_POS,16,WHITE,GRAY);
	}

		loop_count1=0;
		for(loop_count=53;loop_count>0;loop_count--)
			{
	          if(loop_count>pressure && loop_count<52)
	          {
				Rectangle(26+2+dynamic_data[loop_count1][0],DYN_PRES_POS-13+loop_count,
						                26-dynamic_data[loop_count1][1]-4,0,(((100+((54-loop_count)*2))<<16)+((200-((54-loop_count)*3))<<8)+(30<<0)));
	          }

//	          else if(loop_count%2==0)
//	      			{
//	      				Rectangle(26+dynamic_data[loop_count1][0],154+loop_count,
//	      										26-dynamic_data[loop_count1][1],0,BAR_COLOR);
//	      			}

	      		else
	      		 {
	      			Rectangle(26+dynamic_data[loop_count1][0],DYN_PRES_POS-13+loop_count,
	      					  26-dynamic_data[loop_count1][1],0,MAIN_FRAME_COL);
	      		 }

//           	delay_ms(50);

				if(loop_count1>0 && loop_count%2==0 && loop_count<11)
				{
				  loop_count1--;
				}

				else if(loop_count1<5 && loop_count%2==0 && loop_count>43)
				{
					loop_count1++;
				}
			}
}

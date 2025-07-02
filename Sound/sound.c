/*
 * sound.c
 *
 *  Created on: 02-Feb-2024
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
//#include "Driver_HX711.h"
#include "Bolus_Header.h"
#include "infused_calculate.h"
//#include "STEPPER.h"
//#include "Keypad.h"
#include  "sound.h"

#define ser_passcode 2167

uint16_t Passcode_screen(uint16_t Value);

void password_settings(void);
void screen_option_scroll(uint8_t current_cur_no,uint8_t prev_cursor_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL,uint32_t UP_ARROW_ERASE);
void password_option_scroll(uint8_t current_cur_no,uint8_t prev_cursor_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL,uint32_t UP_ARROW_ERASE);
void Digit_Spiliting_1(uint16_t Value);
void Pc_split_frame();
extern uint8_t TFT_ST7789V_left_Right_arrow_14_arial(uint16_t xpos, uint16_t ypos_1,uint8_t arrow, uint32_t boarder_color, uint32_t fill_color);
extern uint8_t TFT_ST7789V_up_down_arrow_20_arial(uint16_t xpos, uint16_t ypos_1,uint8_t arrow, uint32_t boarder_color, uint32_t fill_color);
extern void Left_Right_Indi(uint8_t cursor_pos,uint8_t screen_id);
extern const uint8_t POWER_BUTTON_15ptBitmaps[];
extern uint8_t G_sound_level;
extern uint16_t mute_count;

uint32_t time_interval[15]={0,300,100,300,100,300,300,300,100,300,200,300,2000};
uint32_t sound_level[7]={40000,15000,10000,5000,100};
ALM alarm_sound;
uint32_t sound;

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :
*****************************************************************************/

void buzzer_pwm_stop()

{
	CTIMER0->TCR &= ~(1 << 0);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

//void buzzer_pwm()
//{
//
//	        SYSCON->SYSTICKCLKSELX[0] |=0X02;	    // Oscillator 32 kHz clock.
//	    	SYSCON->CTIMERCLKSELX[0] |= 0x00;	    // 0 Main clock.
//	    	CLOCK_AttachClk(kFRO_HF_to_CTIMER0);
//	     	BUZZER_PIN = 0X003; 			    	// FUNC = 3 // CTIMER0_MAT3
//	    	SYSCON->AHBCLKCTRLX[1] |= 1 << 26 ; 	// Enables the clock for the Timer 0.
//	    	SYSCON->PRESETCTRLSET[1] |= 1 << 26 ;   // Timer 0 reset control.
//	    	SYSCON->PRESETCTRLCLR[1] |= 1 << 26 ;   //clears the corresponding position in PRESETCTRL1.
//	    	CTIMER0->CTCR = 0X00;					//Timer mode. Incremented every rising APB bus clock edge
//	    	CTIMER0->PR = 0X00;						//The pre-scale counter is incremented on every APB bus clock
//	   	    alarm_sound.period=65000;
//
//}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :
*****************************************************************************/

void pwm_sta(uint32_t period,uint16_t duty_cycle)
{
	    	CTIMER0->PWMC |= 1 << 3 ;		      // PWM mode is enabled for CTIMERn_MAT3.
	    	CTIMER0->MCR |= 1 << 4 ;			  // Reset on MR1: the TC will be reset if MR1 matches it.
	    	CTIMER0->MR[1] = period;              //35555;//65500;//19350;/*19450*/;//16500;///10000;//450; //490;    //period
	    	CTIMER0->MR[3] =duty_cycle;           //;12000;//6000;//640; //640;								//on_time
	    	CTIMER0->TCR |= 1 << 0; 			  //Enabled. The timer counter and pre-scale counter are enabled
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :
*****************************************************************************/

void alarm_sound_tone()
{
//	if(!alarm_sound.sound_cnt)
//		{
//			alarm_sound.on_off++;
//			if(alarm_sound.on_off%2==1)
//			{
//		    	pwm_sta(alarm_sound.period,sound_level[G_sound_level]);
//			}
//
//			else
//			{
//		    	pwm_sta( alarm_sound.period,0);
//			}
//
//			if(alarm_sound.on_off>=13)
//			{
//				alarm_sound.on_off=0;
//			}
//
//			alarm_sound.sound_cnt=time_interval[alarm_sound.on_off];
//
	        if(!mute_count)
			{
				if(!alarm_sound.count)
				{
					alarm_sound.on_off++;
					if(alarm_sound.on_off%2==1)
					{
						BUZZER_PIN = 0X003;
						pwm_sta(alarm_sound.period,sound_level[G_sound_level]);

					}
					else
					{
						BUZZER_PIN = 0X00;
						pwm_sta( alarm_sound.period,0);
					}

					if(alarm_sound.on_off>=13)
					{
						alarm_sound.on_off=0;

					}
					alarm_sound.count=time_interval[alarm_sound.on_off];


				}
				//mute_flag=5;
			}
//			else
//			{
//				pwm_sta( alarm_sound.period,0);
//				BUZZER_PIN = 0X00;
//			}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :
*****************************************************************************/

void beep_sound()
{
	BUZZER_PIN = 0X003;
	pwm_sta( alarm_sound.period,sound_level[G_sound_level]);
	delay_ms(10);

	pwm_sta( alarm_sound.period,0);
	BUZZER_PIN = 0x00;
	delay_ms(10);

}
///****************************************************************************
//* Function Name :
//* Arguments     :
//* Return type   :
//* Description   :
//*****************************************************************************/

void long_beep_sound()
{
	beep_sound();
	beep_sound();
	beep_sound();
	beep_sound();
	beep_sound();

}

///****************************************************************************
//* Function Name :
//* Arguments     :
//* Return type   :
//* Description   :
//*****************************************************************************/

void Power_off_beep_sound()
{
	BUZZER_PIN = 0X003;
	pwm_sta(alarm_sound.period,sound_level[0]);
	delay_ms(500);

	pwm_sta(alarm_sound.period,0);
	BUZZER_PIN = 0x00;
	//delay_ms(500);
}

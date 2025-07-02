#include <Boot_up.h>
#include "LPC55S16.h"
#include "Color.h"
#include "Driver_SPI.h"
#include "TFT_Commands.h"
#include "Shapes.h"
#include "TFT_String.h"
#include "clock_config.h"
#include "Main_screen.h"
#include "fsl_clock.h"
#include "Driver_Timer.h"
#include  "sound.h"

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
//void PWM_Init()
//{
//
//		SYSCON->SYSTICKCLKSELX[0] |=0X02; 		// Oscillator 32 kHz clock.
//		SYSCON->CTIMERCLKSELX[0] |= 0x00; 		// 0 Main clock.
//		CLOCK_AttachClk(kFRO_HF_to_CTIMER0);
//		IOCON->PIO[1][2] = 0X003; 				// FUNC = 3 // CTIMER0_MAT1
//		SYSCON->AHBCLKCTRLX[1] = 1 << 26 ; 		// Enables the clock for the Timer 0.
//		SYSCON->PRESETCTRLSET[1] = 1 << 26 ; 	// Timer 0 reset control.
//		SYSCON->PRESETCTRLCLR[1] = 1 << 26 ; 	//clears the corresponding position in PRESETCTRL1.
//		CTIMER0->CTCR = 0X00;					//Timer mode. Incremented every rising APB bus clock edge
//		CTIMER0->PR   = 0X00;					//The pre-scale counter is incremented on every APB bus clock
//		CTIMER0->PWMC = 1 << 1 ;				// PWM mode is enabled for CTIMERn_MAT1.
//		CTIMER0->MCR  = 1 << 10 ;				// Reset on MR3: the TC will be reset if MR3 matches it.
//		CTIMER0->MR[3] = 640;					//;12000;//6000;//640; //640;
//		CTIMER0->MR[1] = 450;					//65500;//19350;/*19450*/;//16500;///10000;//450; //490;
//		CTIMER0->TCR |= 1 << 0; 				//Enabled. The timer counter and pre-scale counter are enabled
//
//}

void buzzer_pwm()
{

	        SYSCON->SYSTICKCLKSELX[0] |=0X02; // Oscillator 32 kHz clock.
	    	SYSCON->CTIMERCLKSELX[0] |= 0x00; // 0 Main clock.
	    	CLOCK_AttachClk(kFRO_HF_to_CTIMER0);
	    	BUZZER_PIN = 0X003;                  // FUNC = 3 // CTIMER0_MAT3
	    	SYSCON->AHBCLKCTRLSET[1] |= 1 << 26 ; // Enables the clock for the Timer 0.
	    	SYSCON->PRESETCTRLSET[1] |= 1 << 26 ; // Timer 0 reset control.
	    	SYSCON->PRESETCTRLCLR[1] |= 1 << 26 ; //clears the corresponding position in PRESETCTRL1.
	    	CTIMER0->CTCR = 0X00;//Timer mode. Incremented every rising APB bus clock edge
	    	CTIMER0->PR = 0X00;//The pre-scale counter is incremented on every APB bus clock
	    	alarm_sound.period= 45000;    //60000;    //65000;

}

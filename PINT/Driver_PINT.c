#include "LPC55S16.h"
#include "Driver_PINT.h"
#include "Motor.h"
#include "Bolus_Header.h"
#include "fsl_inputmux.h"
#include "color.h"
#include <TFT_Commands.h>
//#include "fsl_inputmux.h"
#include "Battery.h"
#include "TFT_String.h"

  #define PINT_PIN_INT_LEVEL              0x10U
//#define PINT_PIN_INT_EDGE               0x00U
  #define PINT_PIN_INT_FALL_OR_HIGH_LEVEL 0x02U
  #define PINT_PIN_INT_RISE               0x01U
//#define PINT_PIN_RISE_EDGE              (PINT_PIN_INT_EDGE | PINT_PIN_INT_RISE)
//#define PINT_PIN_FALL_EDGE              (PINT_PIN_INT_EDGE | PINT_PIN_INT_FALL_OR_HIGH_LEVEL)
  #define PINT_PIN_BOTH_EDGE              (PINT_PIN_INT_EDGE | PINT_PIN_INT_RISE | PINT_PIN_INT_FALL_OR_HIGH_LEVEL)
//#define PINT_PIN_LOW_LEVEL              (PINT_PIN_INT_LEVEL)
//#define PINT_PIN_HIGH_LEVEL             (PINT_PIN_INT_LEVEL | PINT_PIN_INT_FALL_OR_HIGH_LEVEL)


  #define DEMO_PINT_PIN_INT0_SRC    kINPUTMUX_GpioPort0Pin17ToPintsel
  #define DEMO_PINT_PIN_INT1_SRC    kINPUTMUX_GpioPort1Pin27ToPintsel


  #define RISING_EDGE				0x01U
  #define FALLING_EDGE				0x02U
  #define RISING_FALLING_EDGE	 	(RISING_EDGE | FALLING_EDGE)

//#define LOW_LEVEL					0x10U
//#define HIGH_LEVEL				LOW_LEVEL | 0x02U

//#define PORT0_PIN15				PINT_PIN_INT0
//#define PINSEL0					0xC0
  #define PINSEL0_MUX_L_SFT_20		0xC000000					 //	(PINSEL0 << 20) 20 - MUX SHIFT



//#define PORT0_PIN0			(PINSEL0_MUX_L_SFT_20 | PORT0 | PIN0)
//#define PORT0_PIN1			(PINSEL0_MUX_L_SFT_20 | PORT0 | PIN1)
//#define PORT0_PIN10			(PINSEL0_MUX_L_SFT_20 | PORT0 | PIN10)
  #define PORT0_PIN17			(PINSEL0_MUX_L_SFT_20 | PORT0 | PIN17)
//#define PORT0_PIN18			(PINSEL0_MUX_L_SFT_20 | PORT0 | PIN18)
  #define PORT0_PIN19			(PINSEL0_MUX_L_SFT_20 | PORT0 | PIN19)

  #define PORT1_PIN27			(PINSEL0_MUX_L_SFT_20 | PORT1 | PIN27)
//#define PORT1_PIN2			(PINSEL0_MUX_L_SFT_20 | PORT1 | PIN2)



//#define PINT_PIN_INT0       (0xC000000 |0x11 )

  #define PORT0							0x00					//PIN 0 - 31 (INT PIN 0 - 1)
  #define PORT1							0x20					//PIN 0 - 31 (INT PIN 32 - 65)

//#define PIN0							0x00
//#define PIN1							0x01
//#define PIN2							0x02
//#define PIN3							0x03
//#define PIN4							0x04
//#define PIN5							0x05
//#define PIN6							0x06
//#define PIN7							0x07
//#define PIN8							0x08
//#define PIN9							0x09
//#define PIN10							0x0A
//#define PIN11							0x0B
//#define PIN12							0x0C
//#define PIN13							0x0D
//#define PIN14							0x0E
//#define PIN15							0x0F
//
//#define PIN16							0x10
  #define PIN17							0x11
//#define PIN18							0x12
  #define  PIN19							0x13
//#define PIN20							0x14
//#define PIN21							0x15
//#define PIN22							0x16
//#define PIN23							0x17
//#define PIN24							0x18
//#define PIN25							0x19
//#define PIN26							0x1A
  #define PIN27							0x1B
//#define PIN28							0x1C
//#define PIN29							0x1D
//#define PIN30							0x1E
//#define PIN31							0x1F

uint16_t m_count1=0;
uint16_t m_count1_1=0;
uint8_t cuts_sec=0;
uint8_t B_count=0;

extern volatile uint8_t normal_run;
extern uint8_t batt_high_flag;

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void PINT_EXT_Init1(void)
{

	SYSCON->AHBCLKCTRLSET[0]=1<<11;

	//	IOCON->PIO[0][17] &= (~(0xFU | 0x100U));			//Drop IR Sensor
	//	IOCON->PIO[0][17]	|= (0x00| 0x100);


	//	IOCON->PIO[1][2] &= (~(0xFU | 0x100U));				// MFB IR Sensor
	//	IOCON->PIO[1][2]	|= (0x00| 0x100);

		IOCON->PIO[0][17] &= (~(0xFU | 0x100U));			//Airbubble IR Sensor
		IOCON->PIO[0][17] |= (0x00| 0x100);
	//
	//
//		IOCON->PIO[1][27] &= (~(0xFU | 0x100U));			//stat pin
//		IOCON->PIO[1][27] |= (0x00| 0x100);

	//	IOCON->PIO[0][19] &= (~(0xFU | 0x100U));			//stat pin
	//	IOCON->PIO[0][19] |= (0x00| 0x100);

		INPUTMUX_AttachSignal(INPUTMUX, 1, PORT0_PIN17);
//		INPUTMUX_AttachSignal(INPUTMUX, 0, PORT1_PIN27);
	//	INPUTMUX_AttachSignal(INPUTMUX, 1, PORT1_PIN2);
	//	INPUTMUX_AttachSignal(INPUTMUX, 2, PORT0_PIN18);

		SYSCON->AHBCLKCTRLCLR[0]=1<<11;

		SYSCON->AHBCLKCTRLSET[0] |= 1<<18;               	//Enable clock for PINT
		SYSCON->PRESETCTRLSET[0] |= 1<<18;              	//PeripheralReset -set
		SYSCON->PRESETCTRLCLR[0] |= 1<<18;              	//PeripheralReset-clear
		PINT->PMCFG = 0X00;                           		//Pin interrupt 0 in the NVIC is raised

	//	PINT_Config(0,FALLING_EDGE,PINT_EXT_IRQ_Drop);
	//	PINT_Config(1,FALLING_EDGE,PINT_EXT_IRQ_MFB);

		PINT_Config(1,FALLING_EDGE);     					//(PINT_EXT_IRQ_Air);
	//	PINT_Config(1,RISING_EDGE);                         ////28-03

		NVIC_ClearPendingIRQ(PIN_INT1_IRQn);
	//	NVIC_ClearPendingIRQ(PIN_INT0_IRQn);//28-03

	//	NVIC_ClearPendingIRQ(PIN_INT1_IRQn);
	//	NVIC_ClearPendingIRQ(PIN_INT2_IRQn);


		NVIC_SetPriority(PIN_INT1_IRQn, 0);
//		NVIC_SetPriority(PIN_INT0_IRQn, 1);//28-03

	//	NVIC_SetPriority(PIN_INT1_IRQn, 0);
	//	NVIC_SetPriority(PIN_INT2_IRQn, 6);

		NVIC_EnableIRQ(PIN_INT1_IRQn);
//		NVIC_EnableIRQ(PIN_INT0_IRQn);//28-03

	//	EnableIRQ(4);
	//	EnableIRQ(PIN_INT1_IRQn);
	//	EnableIRQ(PIN_INT2_IRQn);

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void PINT_Config( uint8_t Intr_No, uint8_t INT_Type)	//, pint_cb_t callback)
{

	PINT->RISE |= (1UL << (uint32_t)Intr_No);
	PINT->FALL |= (1UL << (uint32_t)Intr_No);

	//	s_pintCallback[Intr_No] = callback;

	PINT->ISEL =(PINT->ISEL & ~(1UL << (uint32_t)Intr_No)) |
	((((uint32_t)INT_Type & PINT_PIN_INT_LEVEL) != 0U) ? (1UL << (uint32_t)Intr_No) : 0U);

	/* enable rising or level interrupt */


	if (((unsigned)INT_Type & (PINT_PIN_INT_LEVEL | PINT_PIN_INT_RISE)) != 0U)
	{
		PINT->SIENR = 1UL << (uint32_t)Intr_No;
	}
	else
	{
		PINT->CIENR = 1UL << (uint32_t)Intr_No;
	}

	/* Enable falling or select high level */
	if (((unsigned)INT_Type & PINT_PIN_INT_FALL_OR_HIGH_LEVEL) != 0U)
	{
		PINT->SIENF = 1UL << (uint32_t)Intr_No;
	}
	else
	{
		PINT->CIENF = 1UL << (uint32_t)Intr_No;
	}
	//EnableIRQ(4);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void PIN_INT1_IRQHandler(void)
 {

	if( (PINT->IST & (1<<1))==0x02U )// && ((PINT->ISEL & (1<<0))==0X0U) )//REW_UP
	{
			B_count++;

//
			 if((normal_run)||(BOL.run_mode))
		  	 {
				 if(MFB.Min_pulse>300)
				 {
		  			MFB.Min_pulse = 0;
					MFB_check();
		  			MFB.Min_pulse=0;
				 }
		  	 }
	 	PINT->IST |=(1<<1);
	}

  }

/****************************************************************************
* Function Name :void PIN_INT1_IRQHandler(void)
* Arguments     :void
* Return type   :void
* Description   :This is PINT1 handler functionality

*****************************************************************************/

//void PIN_INT0_IRQHandler(void)
//{
//	Font_Select(ARIAL_14);
//	TFT_Number(0,70,100,NAVY,WHITE);
//	if ((PINT->ISEL & 0x01U) == 0x01U)
//	{
//
//		//if(((PINT->IST & (1<<1))!=0x0U) && ((PINT->ISEL & (1<<1))==0x0U))
//		{
//
//			if(((BAT_CHECK.STAT_high>=8) && (BAT_CHECK.STAT_high<=20))&&((BAT_CHECK.STAT_low>=8) && (BAT_CHECK.STAT_low<=20)))
//			{
//				batt_high_flag=2;
//				BAT_CHECK.STAT_high=0;
//				BAT_CHECK.STAT_low=0;
//
//			}
//
//		}
//		PINT->IST |=(1<<1);
//
//	}
//}

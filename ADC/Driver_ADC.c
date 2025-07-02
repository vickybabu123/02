#include "LPC55S16.h"
#include "fsl_clock.h"
#include "Driver_ADC.h"
//#include "TFT_Commands.h"
//#include "Color.h"
//#include "Driver_Timer.h"

//uint16_t POWER_KEY_VOLTAGE = 0;
//uint16_t RS2_VOLTAGE  = 0;

//extern uint16_t linear_temp_adc;
//extern uint16_t SD_temp_adc;
//extern uint16_t temp_ADC_values_1;

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint16_t  ADC_read(uint8_t adc_input)
   {

		uint16_t ADC_result	= 0;
		ADC_trig_config(adc_input);
		ADC_result=ADC_conv(adc_input);
		return ADC_result;
   }

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void CLOCK_SetDiv(clock_div_name_t div_name, uint32_t divided_by_value, bool reset)
	{

		volatile uint32_t *pClkDiv;
		pClkDiv = &(SYSCON->SYSTICKCLKDIV0);
		SYSCON->SYSTICKCLKDIV0= 1UL << 29U;
	    ((volatile uint32_t *)pClkDiv)[(uint8_t)div_name] = (divided_by_value - 1U);

	}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void LPADC_Init(uint8_t ADC_no)
	{

		SYSCON->AHBCLKCTRL.AHBCLKCTRL0|=1u<<27;
		CLOCK_SetDiv(kCLOCK_DivAdcAsyncClk, 2U, true);
		CLOCK_AttachClk(kFRO_HF_to_ADC_CLK);
		POWER_DisablePD(kPDRUNCFG_PD_LDOGPADC);

	  if(ADC_no == ADC_CH_SD_POT)
	   {
			IOCON->PIO[0][16]=0X400;
			GPIO->DIR[0] &=~(1U<<16);  // for channel 8
	   }

	 else if(ADC_no==ADC_CH_PLUNGER_POT)																					//Mandatory configuration to configure IO as ADC PIN
		{
			IOCON->PIO[1][9]=0X400;
			GPIO->DIR[1]&=~(1U<<9);    // for channel 12
		}
	 else if(ADC_no==ADC_CH_BATTERY)
		{
			IOCON->PIO[1][0]=0X400;
			GPIO->DIR[1] &=~(1U<<0);   // for channel 4
		}
	 else if(ADC_no==ADC_CH_POWER_KEY)
		{
			IOCON->PIO[0][15]=0X400;
			GPIO->DIR[0] &=~(1U<<15);  // for channel 8  //21-03-2024
		}

	  	ADC0->CFG 	|=	0x10800042;	  //(0X10010040) | (0X80 << 16);
		ADC0->CTRL 	|=	0x00070001;	  // Enable ADC bit after configure CFG register
		ADC_cmd_config(ADC_no);

	}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void ADC_cmd_config(uint32_t commandId)
{

		uint32_t tmp32 = 0;

      if(commandId==ADC_CH_SD_POT)
		{

		ADC0->CMD[0].CMDL =0xA0;		// High resolution. Single-ended 16-bit conversion; Differential 16-bit conversion with 2’s complement output.													//Channel 8 -> 8-8 = 0   (A- 16-bit conv & channel B, 0 - Channel 0)
		tmp32 =0x7700; 						//	0x01007000;
		ADC0->CMD[0].CMDH =tmp32;

		}


       else if(commandId==ADC_CH_PLUNGER_POT)
    	{

		ADC0->CMD[1].CMDL=0xA4;    //0xA4; 0X80;  //Channel 2
		tmp32 =0x7700; 			   //0x02007000;		   //Commands should have the value of next ADC channel for chain read reaction
		ADC0->CMD[1].CMDH = tmp32; //Incase of using multiple channel

		}
//
		else if(commandId==ADC_CH_BATTERY)						  // (8- 16-bit conv & channel A, 4 - Channel 4)
		{

		ADC0->CMD[2].CMDL=  0xA3;   // High resolution. Single-ended 16-bit conversion; Differential 16-bit conversion with 2’s complement output.
		tmp32 =0x7700; 				//0x03007000;
		ADC0->CMD[2].CMDH  =  tmp32;

		}
		else if(commandId==ADC_CH_POWER_KEY)//21-03-2024
		{

		ADC0->CMD[3].CMDL =0x82;	 //	// High resolution. Single-ended 16-bit conversion; Differential 16-bit conversion with 2’s complement output.													//Channel 8 -> 8-8 = 0   (A- 16-bit conv & channel B, 0 - Channel 0)
		tmp32 =0x7700;				 // 0x01007000;
		ADC0->CMD[3].CMDH =tmp32;

		}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void ADC_trig_config(uint32_t triggerId)
{
		if(triggerId == ADC_CH_SD_POT)
		{
			ADC0->TCTRL[0]=	0x00000000 | ((1+0)<< 24);
			ADC0->SWTRIG = 1<<0;
		}
		else if(triggerId == ADC_CH_PLUNGER_POT)
		{
			ADC0->TCTRL[1]=	0x00000000 | ((1+1)<< 24);
			ADC0->SWTRIG = 1<<1;

		}
		else if(triggerId == ADC_CH_BATTERY)
		{
			ADC0->TCTRL[2]=	0x00000000 | ((1+2)<< 24);
			ADC0->SWTRIG = 1<<2;

		}
		else if(triggerId == ADC_CH_POWER_KEY)
		{
			ADC0->TCTRL[3]=	0x00000000 | ((1+3)<< 24);
			ADC0->SWTRIG = 1<<3;

		}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint16_t ADC_conv(uint8_t index)
{
		uint32_t Result_ADC_value	=	0;
		uint16_t Final_Output		=	0;


		while(0U == (ADC_RESFIFO_VALID_MASK & Result_ADC_value))
		{
				Result_ADC_value = ADC0->RESFIFO[0];

		}
		if(index<ADC_CH_PLUNGER_POT)
		{
			Final_Output		=	 ((uint16_t)(Result_ADC_value& ADC_RESFIFO_D_MASK)>>4 );    // & ADC_RESFIFO_D_MASK)>>4);
		}

		else
		{
			Final_Output	= Result_ADC_value& ADC_RESFIFO_D_MASK;
		}

		if(index	==	ADC_CH_SD_POT)
		{
		//	Final_Output		=	 ((uint16_t)(Result_ADC_value & ADC_RESFIFO_D_MASK)>>4);
			Final_Output        =	 4095-(Final_Output);
		}


//		else if(index	==	ADC_CH_PLUNGER_POT)
//		{
//			Final_Output	=	 ((uint16_t)(Result_ADC_value & ADC_RESFIFO_D_MASK));
//		}
//
//		else if(index	==	ADC_CH_BATTERY)
//		{
//			Final_Output	   = ((uint16_t)(Result_ADC_value & ADC_RESFIFO_D_MASK)>>4);
//
//		}
//
//		else if(index	==	ADC_CH_POWER_KEY)
//		{
//			Final_Output	=	((uint16_t)(Result_ADC_value & ADC_RESFIFO_D_MASK)>>4); //SL //21-03-2024
//		}
//
//		else if(index	==	ADC_CH_MAINS)
//		{
//			Final_Output	  =	 ((uint16_t)(Result_ADC_value & ADC_RESFIFO_D_MASK)>>4); //SD //21-03-2024
//		}

		return Final_Output;
}


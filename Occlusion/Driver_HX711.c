#include <Driver_HX711.h>
#include "LPC55S16.h"
#include "Driver_Timer.h"
#include "Color.h"

LOC HX711;


/*
 * Function Name : uint16_t strain_data_read()
 * Return type	 : This function to return the 24 bit ADC value
 * Description   :i) In this function used to calculate strain data read value(24 bit ADC)
 *        		  ii) The maximum pressure value is 8388
 *
 */

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint16_t strain_data_read()
 {
	uint64_t bit_pos = 1;
	uint8_t loop_count = 0;
	uint8_t loadcell_loop = 0;
	static uint8_t load_flag = 0;
 // uint8_t load_flag = 0;
	uint64_t bin_to_dec =0;

	if(!load_flag)
	{
		load_flag = 1;
		HX711.reset_flag = 1;
		HX711.reset_time = 0;
		NVIC_EnableIRQ(CTIMER2_IRQn);
	}

// while(HX711.reset_flag);

	if(!HX711.reset_flag)
	{
		load_flag = 0;

		while(HX711_DAT_PIN);        			 //loadcell data
		HX711.clk_flag = 1;
		loadcell_loop = 1;



		while(loadcell_loop)
		{

			if(HX711.clk_Count >= HX711_GAIN)
			{
				NVIC_DisableIRQ(CTIMER2_IRQn);
				HX711.conv_flag = 1;
				HX711_CLK_CLR;
			}

			if(HX711.conv_flag == 1)
				{
					HX711.clk_Count = 0;
					HX711.conv_flag = 0;
					bin_to_dec = 0;

					if(HX711.data[0])
						{
							HX711.data[0]=0;
						}

					for(loop_count=24;loop_count>0;loop_count--)
					{
						if(HX711.data[loop_count-1])
						{
							bin_to_dec += bit_pos;
						}

						bit_pos *= 2;
						HX711.data[loop_count-1] = 0;
					}
						loadcell_loop = 0;
						bin_to_dec=bin_to_dec/1000;
				}

		}
	}
		return bin_to_dec;
 }

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

 void HX711_handler(void)
 {

	 if(HX711.reset_flag == 1)				/* To make HX710 in Power Down and Reset Mode */
	  {

		  if(HX711.reset_time)
			{
			HX711_CLK_SET;              	//loadcell clk enable
			HX711.reset_time--;
			}
		  else
			{
			HX711_CLK_CLR;             		//loadcell clk disable
			HX711.reset_flag = 0;
			HX711.clk_flag = 0;
	  }

	 	     }
	 	 else										/* To Enter into Normal Mode */
	 		{
	 		if(HX711.clk_flag)
	 				{
	 				if(HX711.clk_Count <= HX711_GAIN)
	 						{
	 					HX711.clock_transition++;

	 						if(HX711.clock_transition == CLK_TRANSITION)
	 								{
	 									HX711_CLK_CLR;
	 									HX711.clock_transition = 0;
	 									HX711.clk_Count++;

	 									if(HX711.clk_Count <= (HX711_GAIN - 1))
	 										{
	 										if(HX711_DAT_PIN)      	//loadcell_data read
	 											HX711.data[HX711.clk_Count-1] = 1;
	 										else
	 											HX711.data[HX711.clk_Count-1] = 0;
	 										}
	 								}
	 						else if(HX711.clock_transition == 1)
	 								{
	 								  HX711_CLK_SET;
	 								}
	 						}
	 				else
	 					HX711.clk_flag = 0;
	 				}
	 		}
 }

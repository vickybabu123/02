/****************************************************************************
* File Name    :
* Developed by :
* Version      :
* Description  :

*****************************************************************************/
#include <stdio.h>
#include "stdint.h"
#include "fsl_clock.h"
#include "Color.h"
 /**************************************************************************
                               Macros
 ***************************************************************************/

/*#define DISC_ON     (GPIO->PIN[0] & (1<<18))
#define DISC_OFF   !(GPIO->PIN[0] & (1<<18))

#define RLSW_ON    (GPIO->PIN[0] & (1<<19))
#define RLSW_OFF  !(GPIO->PIN[0] & (1<<19))*/

#define DISC_OFF     (GPIO->PIN[0] & (1<<18))
#define DISC_ON   !(GPIO->PIN[0] & (1<<18))

#define RLSW_OFF    (GPIO->PIN[0] & (1<<19))
#define RLSW_ON  !(GPIO->PIN[0] & (1<<19))
 /**************************************************************************
                          Global Variables
 ***************************************************************************/
uint8_t G_Disc_sw_time=0;
uint8_t G_RL_sw_time=0;


typedef struct sample{
uint8_t current_pos;
uint8_t count;
uint8_t Err_flag;
uint8_t Err_count;
uint8_t Fail_count;
uint16_t Sample_data;
uint16_t Raw_data[20];
uint32_t cumm_data;
}str;

/**************************************************************************
                            Functions Call
***************************************************************************/
uint16_t Data_sampling(uint16_t Raw_val, uint16_t Data_diff,uint8_t samples );
bool DISC_sample(uint8_t s_sample);
bool RLSW_sample(uint8_t s_sample);
void plunger_alarm_check();

/**************************************************************************
                               Function
***************************************************************************/

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
uint16_t Data_sampling(uint16_t Raw_val, uint16_t Data_diff,uint8_t samples )
{

	static str strain;
	strain.cumm_data=0;
	if(!strain.current_pos)
	{
		for(strain.count=0;strain.count<samples;strain.count++)
		{
			strain.Raw_data[strain.count]=Raw_val;
		}
		strain.current_pos=samples-1;
		strain.Err_flag=0;
		strain.Fail_count=0;
		strain.Sample_data=Raw_val;
	}
	else if((Raw_val>Data_diff && Raw_val>strain.Raw_data[strain.current_pos]-Data_diff
			&& Raw_val<strain.Raw_data[strain.current_pos]+Data_diff ) ||
			( Raw_val<=Data_diff && Raw_val>0 &&
			Raw_val<strain.Raw_data[strain.current_pos]+Data_diff ))
	{
		if(strain.Err_flag )
		{
			if( strain.Err_count<3)
			{
				strain.Err_count++;
			}
			else
			{
				strain.Err_count=0;
				strain.current_pos=0;
				strain.Fail_count=0;
			}
		}
		else
		{
			for(strain.count=0;strain.count<samples-1;strain.count++)
			{
				strain.Raw_data[strain.count]=strain.Raw_data[strain.count+1];
			}

			strain.Raw_data[strain.current_pos]=Raw_val;

			for(strain.count=0;strain.count<samples;strain.count++)
			{
				strain.cumm_data+=strain.Raw_data[strain.count];
			}

			strain.Sample_data=strain.cumm_data/samples;

		}

	}
	else
	{
		strain.Raw_data[strain.current_pos]=Raw_val;
		strain.Err_flag=1;
		strain.Err_count=0;
		strain.Fail_count++;
		if(strain.Fail_count>10)
		{
			//print_string_lcd((uint8_t*)"Load cell fail!..",ROW2);
		}
	}
	return strain.Sample_data;

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

bool DISC_sample(uint8_t s_sample)
{
	static uint8_t press_count=0;
	static uint8_t sw_result=0;
	if(!G_Disc_sw_time)
	{
		G_Disc_sw_time=20;   // Checking time 100ms
		if(DISC_ON)
		{

			if(press_count<s_sample)
			{
				press_count++;
			}
			else
			{
				sw_result=0;
			}

		}
		else
		{
			sw_result=1;
			G_Disc_sw_time=0;
		}
	}
	return sw_result;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

bool RLSW_sample(uint8_t s_sample)
{
	static uint8_t press_count=0;
	static uint8_t sw_result=0;

	if(!G_RL_sw_time)
	{
		G_RL_sw_time=100;   // Checking time 100ms
		if(RLSW_ON )
		{
			if(press_count<s_sample)
			{
				press_count++;
			}
			else
			{
				sw_result=1;
			}
		}
		else
		{
			sw_result=0;
			G_RL_sw_time=0;
		}
	}
	return sw_result;
}

/****************************************************************************
* File Name    :
* Developed by :
* Version      :
* Description  :

*****************************************************************************/

#include "Alarm.h"
#include "LPC55S16.h"
#include "Keypad.h"
#include "Shapes.h"
#include "TFT_String.h"
#include "Occlusion.h"
#include "Alarm.h"
#include <FR_CALC.h>
#include "Bolus_Header.h"
#include "STEPPER.h"
//#include "Pressure_calib.h"

 /**************************************************************************
                               Macros
 ***************************************************************************/

#define PSI  1
#define MMHG 2
#define KPA  3
#define BAR  4

#define PSI_TO_MMHG_CONV_FAC   51.7
#define PSI_TO_KPA_CONV_FAC    6.8
										//	RPM
#define ANTIBOLUS_MLPEHR_2ML   26181    //
#define ANTIBOLUS_MLPEHR_5ML   28421
#define ANTIBOLUS_MLPEHR_10ML  21176
#define ANTIBOLUS_MLPEHR_20ML  22857
#define ANTIBOLUS_MLPEHR_30ML  0
#define ANTIBOLUS_MLPEHR_50ML  26181








 /**************************************************************************
                          Global Variables
 ***************************************************************************/

uint8_t G_Pressure_unit=0;
uint8_t anti_Bolus_flag=0;
uint16_t strain_data=0;
uint32_t G_Rev_count=0;
uint16_t strain_20PSI_val[7];

 uint8_t G_run_count;
/**************************************************************************
                            Functions Call
***************************************************************************/
void auto_update(void);
void anti_bolus(void);
void Anti_Bolus_Screen(void);
//void Anti_bolus_Running();
extern void Alarm_war_screen(uint8_t state);
extern void Alarm_Running(uint8_t L_R_flag);
extern uint8_t g_size_vol;
extern uint8_t sy_size;
extern void Timer1_Init(uint32_t MR_VALUE);
extern volatile uint8_t normal_run;
extern uint8_t Bolus_status_flag;
extern uint8_t Pressure_ADC_delay;

Occlusion Occl;

/**************************************************************************
                               Function
***************************************************************************/

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void ADC_to_PSI_conversion(void)
{

//	uint16_t loop_cnt=0;
//	uint16_t temp_val=0;
	uint16_t strain_value = 0;
	uint16_t zero_psi_value = 0;
	float cal_step=0.0;

	if(Occl.Zero_PSI > 0 && strain_20PSI_val[g_size_vol]> Occl.Zero_PSI)
	{
		if(!Pressure_ADC_delay)
		{
			strain_value = Pressure_ADC();
			strain_data=strain_value;


		if(strain_value > Occl.Zero_PSI)
		{
			Occl.pressure_adc_diff = strain_value - Occl.Zero_PSI;
		}

		else
		{
			Occl.pressure_adc_diff = 0;
		}

//		zero_psi_value = Occl.Zero_PSI+Occl.strain_20PSI_value;
		zero_psi_value = Occl.Zero_PSI;
//		if(syringe_size == _5ML_ )
//		{
//			zero_psi_value += 10;
//		}
//		else if(syringe_size == _10ML_)
//		{
//			zero_psi_value += 20;
//		}
//		else if(syringe_size == _20ML_ )
//		{
//			zero_psi_value += 40;
//		}
//		else if(syringe_size == _30ML_ )
//		{
//			zero_psi_value += 50;
//		}
//		else if(syringe_size == _50ML_ )
//		{
		//	zero_psi_value += 20;
//		}

		/*
		 * Check strain value within range of 0PSI to 0PSI+5000
		 */

		if((strain_value > zero_psi_value) && (strain_20PSI_val[g_size_vol] > zero_psi_value)
	    && (zero_psi_value > 0)&& ((strain_value - zero_psi_value) <= 5000))
		{

			cal_step=(float)((float)(strain_value - zero_psi_value)/
					(float)(strain_20PSI_val[g_size_vol] - zero_psi_value));
			Occl.PSI_VALUE =((float)cal_step*20.0*10.0 );
		}
		else
		{
			Occl.PSI_VALUE = 0;
		}

		if(Occl.PSI_VALUE > 500)
		{
			Occl.PSI_VALUE = 500;
		}
//		else
//		{
//			Occl.PSI_VALUE = 0;
//
//		}

	else
	{
		/*
		 * Error alarm for calib fail 0,20 psi
		 * reset 0,20psi value
		 */
//		Occl.Zero_PSI=0;
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

void auto_update(void)
{
	//	if(Zero_PSI >0 && !pump_on_flag && mode==STOPSTATE &&  ENGAGE_OFF )
	//	{
	//		baseval = syringe_noise_filter();
	//		print_number(psi_check_count,4,0,0,1);
	//		if((!syringe_size) && (baseval<minval1) && (strain_value!=Zero_PSI))         // compared with strain data because to process avg data 20 psi value is required
	//		{
	//			if(!zero_psi_check)  //strain gauge value get drift(variation) based on temperature
	//			{
	//				zero_psi_check=1;
	//				psi_check_count=10;               //-so when no syringe(N/A) read strain gauge value.
	//			}
	//			else if(	(strain_value <= (Zero_PSI + DRIFT_VALUE)) &&
	//				(strain_value >= (Zero_PSI - DRIFT_VALUE)) && !psi_check_count)
	//			{
	//				zero_psi_check=0;
	//
	//				for(loop_cnt=EEPROM_AKAS_16PSI_5ML; loop_cnt<=EEPROM_CUST_16PSI_50ML;loop_cnt+=2)
	//				{
	//					temp_val=i2c_dataread(loop_cnt,2);                 //20 psi value also update while zero psi value update
	//				if(temp_val)
	//				{
	//					if(Zero_PSI>strain_value) temp_val=temp_val-(Zero_PSI-strain_value);
	//					else temp_val=temp_val+(strain_value-Zero_PSI);
	//					i2c_datawrite(loop_cnt,temp_val,2);
	//				}
	//
	//				}
	//				Zero_PSI=strain_value;
	//				i2c_datawrite(EEPROM_ZERO_PSI,Zero_PSI , 2);
	//
	//			}
	//
	//		}
	//		else if(zero_psi_check)
	//		{
	//			zero_psi_check=0;              //-so when no syringe(N/A) read strain gauge value.
	//		}
	//
	//	}


	//	/*strain gauge zero PSI update based on temperature */  //Zero psi update for 50 deviation
	//	if(pump_on_flag)
	//	{
	//		if((!syringe_size) && (Zero_PSI!= strain_value)&& (Zero_PSI!=0) && (mode==STOPSTATE)) 			//Condition included for power off delay
	//		{
	//			baseval = syringe_noise_filter();
	//			if(baseval < minval1)
	//			{
	//				zero_PSI_update();//strain_value);
	//			}
	//		}
	//		pump_on_flag=0;
	//	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Occlusion_Status(void)
{
	static uint8_t preoccl_value_count;
	static uint8_t occl_value_count=0;
	uint8_t Occl_check_range=0;
	uint16_t occl_level_check=0;
	uint16_t Occl_range=0;
	uint16_t Pre_occl_check=0;

	if((Occl.PSI_level>0 && Occl.PSI_level<=15)&& BOL.run_mode)
	{
		occl_level_check=15;
	}

	else
	{
		occl_level_check=Occl.PSI_level;
	}


	if(occl_level_check)
	{

		Occl_range=Occl.PSI_VALUE;
		Pre_occl_check=((occl_level_check * 0.75))*10;

		if(Occl_range >=Pre_occl_check) //75% of the occlusion value
		{
//			Font_Select(ARIAL_14);
//		    TFT_Number(0,70,99,YELLOW,RED);
			if(preoccl_value_count>=5)
			{
				if(!Occl.pre_occl_flag)
				{
					Occl.pre_occl_flag=1;
					if( ((normal_run<=1) && (!BOL.run_mode)) && ((!Bolus_status_flag)) )
					{
						Warning_screen((uint8_t*)"Pre-Occlusion",0);
					}

					else
					{
						Frame_Footer_warning(WARNING_COLOR,BLACK,(uint8_t*)"Pre-Occlusion",(uint8_t*)"",0);
					}
				}
			}
			else
			{
				preoccl_value_count++;
			}
		}

		else if((preoccl_value_count || Occl.pre_occl_flag) && (BOL.mode) )
		{
			Warning_Scr_Erase();
			preoccl_value_count=0;
			Occl.pre_occl_flag=0;
		}

		Occl_check_range=3;
		Occl_range=Occl.PSI_VALUE;

		if(Occl_range >= (occl_level_check*10))
		{
			occl_value_count++;
		}

		else
		{
			occl_value_count=0;
		}


		if(occl_value_count>=Occl_check_range)
		{
			occl_value_count=0;
			if((normal_run<=1) || (BOL.run_mode))
			{
			  anti_bolus();
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

void anti_bolus(void)
{
	uint16_t ref_value = 0;
	uint8_t antib_loop_flag=1;
	uint32_t anti_bolus_flowrate = 0;
	uint16_t antib_check_val=0;
    uint32_t anti_bolus_fr[7]={0,26181,28421,21176,22857,0,26181};

	/*
	 * Enable motor reverse flag
	 */

	 anti_Bolus_flag=1;
	 ref_value=10;
	 Alarm_war_screen(1);
	 stepper_Reverse();

//	 Font_Select(ARIAL_14);
//	 TFT_Number(30,70,sy_size,YELLOW,RED);

	 anti_bolus_flowrate=anti_bolus_fr[sy_size];



//	switch(sy_size)
//	{
//		case SYRINGE_2ML:
//					anti_bolus_flowrate = ANTIBOLUS_MLPEHR_2ML;//REW_UP
//					break;
//		case SYRINGE_5ML:
//					anti_bolus_flowrate = ANTIBOLUS_MLPEHR_5ML;
//					break;
//		case SYRINGE_10ML:
//		      	  	anti_bolus_flowrate = ANTIBOLUS_MLPEHR_10ML;
//					break;
//		case SYRINGE_20ML:
//					anti_bolus_flowrate = ANTIBOLUS_MLPEHR_20ML;
//					break;
//		case SYRINGE_30ML:
//					anti_bolus_flowrate = ANTIBOLUS_MLPEHR_30ML;
//					break;
//		case SYRINGE_50ML:
//					anti_bolus_flowrate = ANTIBOLUS_MLPEHR_50ML;
//					break;
//	}


		  Timer1_Init(anti_bolus_flowrate);
		  G_Rev_count = (5000 + ((((float)anti_bolus_flowrate)/15000.0)
			* 6000.0) + (300.0 *  Occl.PSI_level));

	while(antib_loop_flag)
	{
		/*
		 * power, syringe and check status functionality
		 */

		ADC_to_PSI_conversion();	//REW_UP
//		Anti_bolus_Running();
		antib_check_val=Occl.PSI_VALUE;
		Alarm_Running(1);

		Font_Select(ARIAL_14);
//	    TFT_Number(70,70,antib_check_val,YELLOW,RED);
//	    TFT_Number(70,120,ref_value,YELLOW,RED);

		if(!G_Rev_count|| !antib_check_val || !ref_value || antib_check_val<ref_value
	    /*|| nearemptyflag*/ ||(KEY.value==START_STOP_KEY) )
		{
			/*
			 * Motor stop and exit function
			 */
			anti_Bolus_flag=0;
			antib_loop_flag=0;
			while(KEY.value);
		}

	}
	stepper_Forward();	//REW_UP
	Alarm(OCCL);


}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
//void Anti_bolus_Running()
//{
//	uint16_t Y_pos[3]={120,150,180};
//	uint32_t colour[4][3]={{GRAY,GRAY,GRAY},{ALARM_COLOR,GRAY,GRAY},{ALARM_COLOR,ALARM_COLOR,GRAY},
//			{ALARM_COLOR,ALARM_COLOR,ALARM_COLOR}};
//	uint8_t pos;
//	uint32_t col=LIGHT_GRAY;
//	uint8_t X_pos=80+60;
//	static uint8_t state=0;
//	 if(!G_run_count)
//	 {
//		 for(pos=0;pos<=2;pos++)
//		 {
//				TFT_ST7789V_ALARM_ARROW_20pt(X_pos[L_R_flag],Y_pos[L_R_flag][pos],0,col,colour[L_R_flag][state][pos],L_R_flag);
//		 }
//		 if(state<3)
//		 {
//			 state++;
//		 }
//		 else
//		 {
//			 state=0;
//		 }
//		 G_run_count=5;
//
//	 }
//
//}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
//void Anti_Bolus_Screen(void)
//{
//	Rectangle(0,0,320,240,ALARM_COLOR);
//	TFT_ST7789V__rectangle_curve(10,37+10,146,300,0,LIGHT_GRAY);
//
//	Rectangle(10,193+10,301,1,BLACK);  // Header Boarder line
//	Rectangle(10,36,301,1,BLACK);      // Footer Boarder line
//
//	Font_Select(ARIAL_20);
//	TFT_String(90,80,(uint8_t*)"Anti Bolus",LIGHT_GRAY,BLACK);
//	Frame_Header(ALARM_COLOR,WHITE,(uint8_t*)"Occlusion");
//	Frame_Footer(ALARM_COLOR,WHITE,(uint8_t*)"        Confirm Alarm",(uint8_t*)"OK",1);;
//
//}

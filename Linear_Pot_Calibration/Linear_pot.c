
#include "Linear_Header.h"
#include "Driver_ADC.h"
#include "Color.h"
#include "TFT_String.h"
#include "TFT_Commands.h"
//#include "SD_Calib.h"
#include "Motor.h"
#include "Alarm.h"
#include "Bolus_Header.h"
#include "SD_Calib.h"
#include "Driver_Timer.h"
#include "Power_off.h"

uint8_t end_flag=0;
uint8_t verify_count=0;
uint8_t near_to_end_cnt=0;
uint8_t near_to_end_flag=0;
uint8_t warning_flag[3];
uint16_t Sample_value=0;
 LINEAR_POT  LIN_POT;
extern uint16_t linear_temp_adc;
SYRINGE SYR;
extern volatile int ssize;
extern volatile uint8_t normal_run;
extern uint8_t Plunger_data_delay;

int remaining_volume_in_syringe();
void read_eeprom_all_sizsyr();
extern volatile uint16_t value_l[8];
extern volatile uint16_t value_c[8];

/****************************************************************************
* Function Name : float syringe_nearempty_calculation(uint16_t flowarte)
* Arguments     : flowarate
* Return type   : void
* Description   : these function calculate near empty adc value for all size syringes

*****************************************************************************/

float syringe_nearempty_calculation(uint16_t flowarte)
{
		float volume_for_1_min;
		float for_1_ml_adc;
		float Near_Emty_ml_for_a_minute;
		float  syringe_volume[7]={0,2.0,5.0,10.0,20.0,30.0,50.0};
		uint8_t ssize=0;

		ssize=detect_syringe_size(1);
		volume_for_1_min  = flowarte/MINUTE_60;
		for_1_ml_adc      = (float)(LIN_POT.syr_max_pos[ssize]-LIN_POT.syr_end_pos[ssize])/syringe_volume[ssize];

		Near_Emty_ml_for_a_minute =  volume_for_1_min*THREE;
		Font_Select(ARIAL_14);
//		TFT_writenumber_float_1d(70,70,for_1_ml_adc,YELLOW,RED);
//		TFT_writenumber_float_1d(70,90,Near_Emty_ml_for_a_minute,YELLOW,RED);
		LIN_POT.adc_value_for_a_Minute_ml =(unsigned int)((Near_Emty_ml_for_a_minute * for_1_ml_adc) +  LIN_POT.syr_end_pos[ssize]);
 //   	TFT_Number(70,110,LIN_POT.adc_value_for_a_Minute_ml ,YELLOW,RED);

		return 0;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void display_funtion()
{
		   /* Rectangle(0,0,320,240,MAIN_FRAME_COL);
		    Rectangle(0,0,320,35,NEW_HDR_COL);
		    Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Accuracy Calibration");

		    Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press         to Calibrate");
		    TFT_ST7789V_lcd_drawcircle1(221+1,150-11,15,MAIN_FRAME_COL,MAIN_FRAME_COL);

		    Font_Select(ARIAL_9);
		    TFT_String(216+1,141-11,(uint8_t*)"OK",MAIN_FRAME_COL,WHITE);


		    TFT_ST7789V__rectangle_curve(45,7,305,150,0,WHITE); // SCREEN

			Font_Select(ARIAL_14);
			TFT_String(80+15,30-10,(uint8_t*)" 1.  Ensure the plunger is",WHITE,BLACK);

			if(disp_1)
			{
				TFT_String(105+15,43,(uint8_t*)" fully in",WHITE,BLACK);
			}
			else
			{
				TFT_String(105+15,43,(uint8_t*)" fully out",WHITE,BLACK);
			}

		    TFT_String(140+15,30-10,(uint8_t*)" 2. Ensure no Syringe",WHITE,BLACK);

		     TFT_String(53,130,(uint8_t*)"Warning",WHITE,BLACK);

		     TFT_ST7789V__rectangle_curve(50,100,25,25,0,YELLOW);
		     TFT_String(53,112,(uint8_t*)"!",YELLOW,BLACK);  */

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void motor_stop()
{
//	NVIC_DisableIRQ(CTIMER0_IRQn);
	//printf("\n syringe end ");
	normal_run=0;
}

/*void linear_pot_calibration(void)
{
   int   syringe_volume=50;
   float one_ml_adc_resolution;
//	//printf("\n place the syringe  ");
//	//printf("\n place the syringe start positon ");
	LIN_POT.syr_max_pos[ssize] = samplings_LINEAR_POT(adcch0); // 50ml pos syr
//	//printf("\n press ok to store adc value ");
//  //printf("\n place the syringe end positon ");
    LIN_POT.syr_end_pos[ssize] = samplings_LINEAR_POT(adcch0); // 0ml pos syr
//	//printf("\n press ok to store adc value ");
    one_ml_adc_resolution = (float)(LIN_POT.syr_max_pos[ssize]-LIN_POT.syr_end_pos[ssize])/syringe_volume;
    // load in eeprom "one_ml_adc_resolution"
}*/

//void adc_value_for_induvidual_syringe()
//{
//	int syringe=0;
//	unsigned int count=45;
//    unsigned int hint=100;
//
//	for(  syringe=0; syringe <=4 ; syringe++ )
//	{
//		LIN_POT.syr_max_pos[ssize]= count++;/* eeprom_syringe.starting_adc*/
//
//		LIN_POT.syr_end_pos[ssize]= hint++;/* eeprom_syringe.end_adc*/
//	}
//
//	for(  syringe=0; syringe <=4 ; syringe++ )
//	{
//		//printf("\n eeprom_syringe.starting_adc=%d ",SYR.start_pos[syringe]);/* eeprom_syringe.starting_adc*/
//		//printf("\n eeprom_syringe.end_adc=%d ",SYR.end_pos[syringe]);/*
//		/*eeprom_syringe.starting_adc*/
//		//printf("\n");
//	}
//
//}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

//void read_eeprom_all_sizsyr()
//{
//	 for(int a=1;a<7;a++)
//	 {
//		 value_l[a]=a+800;
//	     value_c[a]=a+100;
//	 }
//
//}

/****************************************************************************
* Function Name : void syringe_end_check()
* Arguments     : void
* Return type   : void
* Description   : these function checks the syringe end adc value for all size syringes

*****************************************************************************/

void syringe_end_check(uint16_t plunger_ADC_val)
{

	//uint16_t var=550;
	uint16_t Linear_pot_ADC=plunger_ADC_val;
	if ((LIN_POT.syr_end_pos[ssize]+1500)  >= (Linear_pot_ADC) )
    {
    	LIN_POT.syr_end_verify_count++;
		//verify_count++;
    }

     if(Linear_pot_ADC > (LIN_POT.syr_end_pos[ssize]+1500))
    {
    	LIN_POT.syr_end_verify_count =0;
    	//verify_count=0;
    	LIN_POT.syr_end_flag=0;
    }

   // TFT_Number(230,110,LIN_POT.syr_end_verify_count,YELLOW,BLACK);

     if(LIN_POT.syr_end_verify_count >= 5)
    // if(verify_count >= 5)
    {
    	LIN_POT.syr_end_flag=1;
    	LIN_POT.syr_end_verify_count=5;
    	//verify_count=5;
    }
//      Font_Select(ARIAL_14);
//      TFT_Number(50,70,LIN_POT.syr_end_flag,YELLOW,RED);

    if(LIN_POT.syr_end_flag==1 )
    {

    	if((normal_run||BOL.run_mode))                 // && (!end_flag))
    	{
    		Alarm(SYR_END);
    	}

    	else if(!end_flag )
    	{
//          Warning_screen((uint8_t *)"Syringe end",0);
    		Notification(SYRINGE_END);
          end_flag=1;
    	}
    }
    else
    {
    	if(end_flag)
    	{
    		end_flag=0;
        	Warning_Scr_Erase(); //CHECK
    	}
    }
}

/****************************************************************************
* Function Name : void near_empty_check(void)
* Arguments     : void
* Return type   : void
* Description   : these function checks the near empty  adc value for all size syringes

*****************************************************************************/

void near_empty_check(uint16_t plunger_ADC_val)
{

//	TFT_Number(100,120,linear_temp_adc,MAIN_FRAME_COL,MAIN_FRAME_COL);
//	linear_temp_adc = ADC_read(ADC_CH_PLUNGER_POT);
//	Font_Select(ARIAL_9);
//	TFT_Number(100,120,linear_temp_adc,MAIN_FRAME_COL,WHITE);
//  delay_us(100);


//	Font_Select(ARIAL_14);
//    TFT_Number(70,130,plunger_ADC_val,YELLOW,RED);


	if((LIN_POT.adc_value_for_a_Minute_ml   >= plunger_ADC_val) && (!LIN_POT.syr_end_flag))
	{
		LIN_POT.nr_empty_verify_count++ ; // have to verify the initialization
	}

	else
	{
		//TFT_String(10,80,(uint8_t *)"                                                   ",RED,NAVY);

		LIN_POT.nr_empty_verify_count=0;

		if(LIN_POT.nr_empty_alarm_flag)
		{
			if((LIN_POT.adc_value_for_a_Minute_ml) < plunger_ADC_val)
			{
			 	Warning_Scr_Erase();
				LIN_POT.nr_empty_alarm_flag=0;
				warning_flag[0]=0;
			}
		}
	}

	if(LIN_POT.nr_empty_verify_count >= 5)
	{
		if((!LIN_POT.nr_empty_alarm_flag) && (normal_run))
		{
			warning_flag[0]=1;
//			Warning_screen((uint8_t*)"Near to End",0);
//			WARN_SOUND(3,1,3);
		//  warn_tone(50);
			LIN_POT.nr_empty_alarm_flag = 1;
		}
		LIN_POT.nr_empty_verify_count=5;
		LIN_POT.near_empty_count++;
	}
//if(normal_run)
//{
//	if(LIN_POT.nr_empty_alarm_flag)
//	{
//		if(!near_to_end_cnt)
//		{
//			near_to_end_cnt=2;
//
//			if(!near_to_end_flag)
//			{
//				Warning_screen((uint8_t*)"Near to End",0);
//				WARN_SOUND(3,1,2);
//				near_to_end_flag=1;
//			}
//
//			else
//			{
//					Warning_Scr_Erase();
//					near_to_end_flag=0;
//					//	near_to_end_cnt=0;
//			}
//		}
//	}
//}
//	if(LIN_POT.nr_empty_alarm_flag == 1  && LIN_POT.near_empty_count==1)
//	{
//		LIN_POT.syr_end_flag=0;
//
//
//	//  TFT_String(160,120,(uint8_t *)"near empty occured ",NAVY,NAVY);
//	//	TFT_String(160,180,(uint8_t *)"Near empty occured ",NAVY,YELLOW);
//
//
//
//		LIN_POT.nr_empty_alarm_flag == 0;
//
		//WARNING_SCREEN();
//	}

}

//int remaining_volume_in_syringe()
//{
//	float remaining_volume;
//	float one_ml_adc_resolution=0;
////  read data  from eeprom for size and brand automaticalyy
////  remaining_volume = ((ADC_read(3) - LIN_POT.syr_end_pos[ssize] )/one_ml_adc_resolution);
//
//    return remaining_volume;
//}

/****************************************************************************
* Function Name : void syringe_position_check()
* Arguments     : void
* Return type   : void
* Description   : these function checks the near empty  adc ,syringe end  value for all size syringes

*****************************************************************************/

void syringe_position_check()
{
	uint16_t ADC_plunger=0;
	if(!Plunger_data_delay)
	{
		ADC_plunger = ADC_read(ADC_CH_PLUNGER_POT);
		Sample_value = ADC_plunger;

		if(!LIN_POT.syr_end_flag)            //&& end_flag==0)
		{
			near_empty_check(ADC_plunger);
		}
		  ssize=detect_syringe_size(1);

	    syringe_end_check(ADC_plunger);
	    Plunger_data_delay=1;
//		ssize=detect_syringe_size(1);
	}
}

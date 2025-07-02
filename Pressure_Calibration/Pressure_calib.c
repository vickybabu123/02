/****************************************************************************
* File Name    :
* Developed by :
* Version      :
* Description  :

*****************************************************************************/

#include <FR_CALC.h>
#include "Occlusion.h"
#include <stdio.h>
#include <stdbool.h>
#include <STEPPER.h>
#include "LPC55S16.h"
#include "Driver_Timer.h"
#include "Driver_I2C.h"
//#include "Driver_PINT.h"
#include "Driver_ADC.h"
#include "Driver_SPI.h"
#include "Color.h"
#include "stdint.h"
#include "TFT_String.h"
#include "Flowrate_Screen.h"
#include "keypad.h"
//#include "Syringe_calib_header.h"
#include "Driver_HX711.h"
#include "TFT_Commands.h"
//#include "Main_Menu.h"
#include "Main_Menu.h"
#include "Shapes.h"
#include "Power_off.h"
#include"Driver_I2C.h"
#include "sound.h"
#include "SD_calib.h"
#include <Boot_up.h>


 /**************************************************************************
                               Macros
 ***************************************************************************/

#define MIN_TWENTY_PSI_DIFF  80
#define MAX_TWENTY_PSI_DIFF  3000
#define Sample_diff1 50
#define Sample_diff2 400
#define Sample_diff3 800
#define Data_samples 5
 /**************************************************************************
                          Global Variables
 ***************************************************************************/

uint8_t G_strain_data_read_delay=0;
uint8_t G_start_cnt=0;
uint16_t G_strain_sec_count=0;
uint16_t G_store_val=0;
uint8_t G_load_read_count=0;
uint32_t G_pressure_value=0;
uint8_t G_calib_run=0;
uint8_t G_Pressure_siphonic=0;

extern uint8_t TFT_ST7789V_Left_Arrow_22pt(uint16_t xpos, uint16_t ypos,
       uint8_t arrow, uint32_t boarder_color, uint32_t fill_color);
extern uint8_t G_run_count;
extern uint8_t TFT_ST7789V_Exclamatory_9pt_arial(uint16_t xpos, uint16_t ypos,
                                         uint8_t arrow, uint32_t boarder_color, uint32_t fill_color);
extern void swap_sysize_glow(uint8_t currentOption,uint8_t prev_sysize);
extern uint8_t g_size_vol;
extern int ssize;
extern uint8_t ON_Flag;
extern uint8_t brand_select_no;
extern uint8_t disc;
extern uint8_t release;
extern uint8_t siphonic_time;

/**************************************************************************
                            Functions Call
***************************************************************************/

// extern uint16_t Data_sampling( uint16_t Raw_val,
// uint16_t Data_diff,uint8_t samples );

void frame_Pressure_calib(uint8_t cursor, uint8_t screen);
void warning_screen_0PSI( );
void warning_screen_20PSI( );
bool Zero_psi_calibration(void);
bool Twenty_PSI_Calibration(void);
void INFO_Screen_0PSI(uint8_t screen);
void frame_syringe_size_glow(uint8_t state);
extern uint8_t edit_screen(uint16_t *Edit_value,uint8_t screen,uint16_t max_value);
void INFO_Screen_20PSI();
void Running_symbol(uint8_t X_start, uint8_t Y_start,uint32_t col);
uint16_t X_pos_align(uint16_t value);
void main_screen_frame(uint16_t flowrate);
uint16_t Pressure_ADC(void);
extern uint16_t Data_sampling(uint16_t Raw_val, uint16_t Data_diff,uint8_t samples );
void Pressure_EEPROM_read();
extern uint32_t MR_VALUE;

/**************************************************************************
                               Function
***************************************************************************/

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
uint16_t Pressure_ADC(void)
{
	uint16_t strain_adc=0;

	/*
	 * Strain data read function
	 */
	strain_adc=strain_data_read();

	if(strain_adc<G_store_val)
	{
		strain_adc= strain_adc+(8388-G_store_val);
	}

	else
	{
		strain_adc=strain_adc-G_store_val;
	}

   strain_adc=Data_sampling(strain_adc,Sample_diff2,Data_samples);

	return strain_adc;


}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void Pressure_calib_setting(void)
{
	uint8_t P_calib_loop=1;
	uint8_t calib_scroll=0;
	uint16_t live_data=0;
	uint16_t temp_live_data=0;
	uint16_t y_pos=0;
	POW.power_status_flag=1;
	G_Pressure_siphonic=1;
//	frame_Pressure_calib(calib_scroll,1);
	while(KEY.value);
	while(P_calib_loop)
	{
		Power_off();//27-03


			if(!ON_Flag)
			{
				break;//26-03
			}

			else if(POW.power_status_flag) //27-03
			{
				POW.power_status_flag=0;   //27-03
				frame_Pressure_calib(calib_scroll,1);
			}

		if(!G_strain_data_read_delay)//REW_UP
		{
		   live_data = Pressure_ADC();
		   G_strain_data_read_delay = 1; //100ms
		}

		if(temp_live_data!=live_data)
		{
			Font_Select(CALIBRI_43);
			y_pos = X_pos_align(temp_live_data);
			TFT_Number(y_pos,45,temp_live_data,MAIN_FRAME_COL,MAIN_FRAME_COL);

			y_pos = X_pos_align(live_data);
			TFT_Number(y_pos,45,live_data,MAIN_FRAME_COL,WHITE);
			temp_live_data=live_data;
		}

		else
		{
			Font_Select(CALIBRI_43);
			y_pos = X_pos_align(live_data);
			TFT_Number(y_pos,45,live_data,MAIN_FRAME_COL,WHITE);//REW_UP
		}

		if(KEY.value==DOWN_KEY || KEY.value==UP_KEY)
		{
			if(Occl.Zero_PSI)
			{
				calib_scroll^=1;
				frame_Pressure_calib(calib_scroll,0);
			}

			while(KEY.value);
		}
		else if(KEY.value == OK_KEY)
		{
			if(!calib_scroll)
			{
				Zero_psi_calibration();
			}
			else
			{
				Twenty_PSI_Calibration();
			}

			POW.power_status_flag=1;
			while(KEY.value);
		}
		else if(KEY.value==BACK_KEY)
		{
			beep_sound();
			P_calib_loop=0;
			while(KEY.value);
		}
	}
}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
bool Zero_psi_calibration(void)
{
	/*
	 * Calibration display with dynamic pressure data
	 */
	uint8_t calib_loop=1;
    uint16_t raw_strain_data=0;
    uint8_t Err_flag_0PSI=0;
	G_strain_data_read_delay=0;
	POW.power_status_flag=1;
//	warning_screen_0PSI();
	while(KEY.value);
	while(calib_loop)
	{
		Power_off();
		if(!ON_Flag)
		{
		break;//26-03
		}

		else if(POW.power_status_flag)
		  {
				POW.power_status_flag=0;//27-03
				warning_screen_0PSI();
		  }


		/*
		 * power status and syringe status
		 */

		if(!G_strain_data_read_delay)
		{
			raw_strain_data = Pressure_ADC();
			if(G_store_val) G_strain_data_read_delay = 1; //100ms

		}
		if(!G_store_val)
		{

			if(raw_strain_data>2000)
			{
				G_store_val=raw_strain_data-2000;
			}
			else
			{
				G_store_val=8388-(2000-raw_strain_data);
			}


			G_strain_sec_count=2;
		}
		/* Live Value display*/

		if(KEY.value==OK_KEY)
		{
			INFO_Screen_0PSI(2);
//			if(1/*(baseval < minval1) && !manual_syru_select_flag && !syringe_size*/)//REW_UP
//			{
				G_store_val=0;
				G_strain_sec_count=9;

				while(G_strain_sec_count)
				{
					Font_Select(ARIAL_20);
					TFT_Number(165,120,G_strain_sec_count,MAIN_FRAME_COL,YELLOW);
				//	Rectangle(160,115,30,35,MAIN_FRAME_COL);		//21-03-2024

					//TFT_Number(165,120,G_strain_sec_count,MAIN_FRAME_COL,MAIN_FRAME_COL);
					if(G_strain_sec_count!=3)
					{
						raw_strain_data = Pressure_ADC();
					}
					else if(!G_store_val)
					{
						if(raw_strain_data>2000)
						{
							G_store_val=raw_strain_data-2000;
						}
						else
						{
							G_store_val=8388-(2000-raw_strain_data);
						}
					}
					/* G_store_val store in EEPROM
					 * i2c_datawrite(EEPROM_BASE_PSI,G_store_val,TWO_BYTE);*/

					EEPROM_datawrite(EEPROM_LOAD_CELL_VAL,G_store_val,2);


				}

                /* Zero PSI value store*/


				if(raw_strain_data>=1990 && raw_strain_data<=2010)
				{
					Occl.Zero_PSI=raw_strain_data;
					INFO_Screen_0PSI(1);
				}
				else
				{
					INFO_Screen_0PSI(0);
				}
				delay_secs(1);
				calib_loop=0;
			//}
//			else
//			{
//				/* Invalid Operation sound*/
//			}
			EEPROM_datawrite(EEPROM_Occl_strain_0PSI_value,Occl.Zero_PSI,2);

		}
		else if(KEY.value==BACK_KEY)
		{
			beep_sound();
			calib_loop=0;
			while(KEY.value);
		}

	}

	calib_loop=0;
   return Err_flag_0PSI;
}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
bool Twenty_PSI_Calibration(void)
{
	/*
	 * Twenty psi calibration screen
	 */
	uint8_t calib_loop1=1;
	uint16_t Display_ADC=0;
	uint16_t _1PSI_value=0;
	uint8_t pressure_dis_flag=0;
	uint8_t Err_flag_20PSI=0;
	uint16_t _20PSI=2000;
	uint16_t temp_live_data=0;
	uint16_t y_pos=0;
	uint8_t syr_size=0;
	uint8_t adc_error_flag=0;
	uint8_t prev_sysize=0;
	uint8_t check_flag=0;
	uint32_t MR_value_syringes[2]={56842,96000};


	frame_syringe_size_glow(0);

	while(KEY.value);

	while(calib_loop1)
	{

	  syr_size=detect_syringe_size(1);//REW_UP

	  plunger_alarm_check();

//	  Font_Select(ARIAL_14);
//	  TFT_Number(90,70,siphonic_time,YELLOW,RED);

	if((!pressure_dis_flag))
	{
//		Font_Select(ARIAL_14);
//		TFT_Number(0,70,syr_size,YELLOW,RED);
//		TFT_Number(0,90,prev_sysize,YELLOW,RED);

		if((prev_sysize != syr_size))
		{


				swap_sysize_glow(syr_size,prev_sysize);

				if(syr_size)
				{
					Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Calibrated value:             ",(uint8_t*)0,0,14);
					Font_Select(ARIAL_14);
					TFT_Number(227,214,Occl.strain_20PSI_value[syr_size],NEW_FTR_COL,HDR_TXT_COL);
				}
				else if(!syr_size)
				{
					Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Place syringe!..",(uint8_t*)0,0,14);

				}
				prev_sysize=syr_size;

		}


			if(KEY.value==OK_KEY)
			{
					if(syr_size)
					{
						pressure_dis_flag=1;
						prev_sysize=syr_size;
						warning_screen_20PSI();
					}

					else
					{
						long_beep_sound();
					}
					 while(KEY.value);
			}
		}

	else
	{
     if(G_calib_run)
     {
//		if((prev_sysize!=syr_size) || ((disc) ||(release)) )
//		{
//				 INFO_Screen_0PSI(0);
//				 delay_secs(2);
//				 Err_flag_20PSI=1;
//				 pressure_dis_flag=0;
//				 adc_error_flag=0;
//				 G_calib_run=0;
//    			 calib_loop1=0;
//        		 Timer_disable();
//		}
     }

		if((G_calib_run))
		{
			if(!G_strain_data_read_delay ) // only runstate
			{
				Display_ADC = Pressure_ADC();
				G_strain_data_read_delay = 1; //100ms
			}

			if(temp_live_data!=Display_ADC)
			{
				Font_Select(CALIBRI_43);
				y_pos = X_pos_align(temp_live_data);
				TFT_Number(y_pos,45,temp_live_data,MAIN_FRAME_COL,MAIN_FRAME_COL);

				y_pos = X_pos_align(Display_ADC);
				TFT_Number(y_pos,45,Display_ADC,MAIN_FRAME_COL,WHITE);
				temp_live_data=Display_ADC;
			}

			else
			{
				Font_Select(CALIBRI_43);
				y_pos = X_pos_align(Display_ADC);
				TFT_Number(y_pos,45,Display_ADC,MAIN_FRAME_COL,WHITE);
			}

			Running_symbol(0,0,NEW_HDR_COL);
		}

         if((KEY.value==START_STOP_KEY))
         {
        	 if(!G_calib_run)
        	 {
        		 G_calib_run=1;
        		 RPM_to_DAC(100);
        		 DRV8428_ENABLE();
				 stepper_Forward();

        		 if((syr_size==1) || (syr_size==2))
        		 {
        			 Timer1_Init(MR_value_syringes[1]);
            		 TFT_Number(0,70,MR_value_syringes[0],YELLOW,RED);
        		 }

        		 else
        		 {
        			 if(syr_size!=0)
        			 {
        				 Timer1_Init(MR_value_syringes[0]);
        	        	 TFT_Number(0,100,MR_value_syringes[1],YELLOW,RED);
        			 }
        		 }
        		 INFO_Screen_20PSI();
        	 }

        	 else
        	 {
        		 G_calib_run=0;
        		 Timer_disable();
        		 if((Display_ADC>Occl.Zero_PSI+MIN_TWENTY_PSI_DIFF)
        		 						 && (Display_ADC<Occl.Zero_PSI+MAX_TWENTY_PSI_DIFF))
				 {
        			 INFO_Screen_0PSI(3);
        			 delay_secs(3);
        			 check_flag=edit_screen(&_20PSI, 3,2599);
        			 calib_loop1=0;
        		     if(_20PSI<1800 ||  _20PSI>2200 )
            		 {
            			 INFO_Screen_0PSI(0);
                		 Timer_disable();
                		 delay_secs(1);
            			 Err_flag_20PSI=1;
            		 }

            		 else
            		 {
            			 _1PSI_value=Display_ADC-Occl.Zero_PSI;
            			 _1PSI_value=(_1PSI_value*100)/_20PSI;
            			 strain_20PSI_val[syr_size]=(_1PSI_value*20)+Occl.Zero_PSI;
            			 INFO_Screen_0PSI(1);
            			 Err_flag_20PSI=0;
 //           			 calib_loop1=0;
            			 EEPROM_datawrite(EEPROM_Occl_strain_20PSI_value+(brand_select_no*12)+((syr_size-1)*2),strain_20PSI_val[syr_size],2);
//						 Occl.strain_20PSI_value[syr_size]= EEPROM_dataread(EEPROM_Occl_strain_20PSI_value+(brand_select_no*12)+((syr_size-1)*2), 2);
//						 TFT_Number(0,70,Occl.strain_20PSI_value[syr_size],NAVY,WHITE);
//            			 Font_Select(ARIAL_14);
//            			 TFT_Number(0,70,Occl.strain_20PSI_value[syr_size],YELLOW,RED);
//            			 TFT_Number(0,110,brand_select_no,YELLOW,RED);
//            			 delay_secs(5);
            		//	 frame_Pressure_calib(0,1);
            		 }

					 /*
					  * Store the twenty PSI value for corresponding sy size.
					  */
				 }
				 else
				 {
					 INFO_Screen_0PSI(0);
	        		 Timer_disable();
	        		 delay_secs(2);
					 Err_flag_20PSI=1;
// 					 Timer_disable();
//	 				 adc_error_flag=1;
					 calib_loop1=0;
				 }
        		 prev_sysize=1;
        		 pressure_dis_flag=0;
        	 }


        	 while(KEY.value);
         }
	}
         if(KEY.value==BACK_KEY && !G_calib_run)
         {
     		beep_sound();
//     		if(!pressure_dis_flag)
//        	 {
        		 calib_loop1=0;
        	// }

//        	 else
//        	 {
//        		 pressure_dis_flag=0;
//			//	 adc_error_flag=0;
//        	 }
        	 while(KEY.value);
         }
	}
	return Err_flag_20PSI;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void frame_Pressure_calib(uint8_t cursor, uint8_t screen)
{
	int loop_count=0;
	uint8_t syr_size=0;
	char* str[2]={"0 PSI Calibration     :","20 PSI Calibration  :"};
	unsigned int   txt_color[2]={WHITE,BLACK};
	unsigned int   bg_color[2]={WHITE,MAIN_FRAME_COL};
	syr_size=detect_syringe_size(1);

	if(screen)
	{
	//	Rectangle(0,0,320,240,MAIN_FRAME_COL);
		CLRSCR(MAIN_FRAME_COL);
		Rectangle(0,0,320,35,NEW_HDR_COL);
		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Pressure Calibration");
		Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to Edit",(uint8_t*)"OK",2,14);
	}
	else
	{

		 if(cursor)
		 {
			 Rectangle(7,36+45+40+(43*0),290+16,40,MAIN_FRAME_COL);
		 }

		 else
		 {
			 Rectangle(7,36+45+40+(43*1),290+16,40,MAIN_FRAME_COL);
		 }

	}
	Font_Select(ARIAL_14);

//  TFT_ST7789V__rectangle_curve(41+(43*cursor),7,290+16,35,0,WHITE);
	TFT_ST7789V__rectangle_curve(7,45+40+36+(43*cursor),40,290+16,0,WHITE);

	for(loop_count = 1; loop_count <=2 ; loop_count++)
		{
		//	Rectangle(7,34+(43*loop_count),290+16,0, BLACK);// line
			Rectangle(7,34+40+(43*loop_count),290+16,0, BLACK);// line
		}
	if(cursor==1)
	{
	   TFT_String(15,45+45+40+(43*0),(uint8_t *)str[0],bg_color[1],txt_color[0]);
	   TFT_String(15,45+45+40+(43*1),(uint8_t *)str[1],bg_color[0],txt_color[1]);
	   TFT_Number(15+220,45+45+40+(43*0),Occl.Zero_PSI,bg_color[1],txt_color[0]);
	   TFT_Number(15+220,45+45+40+(43*1),strain_20PSI_val[syr_size],bg_color[0],txt_color[1]);
	}
	else
	{
		TFT_String(15,45+45+40+(43*0),(uint8_t *)str[0],bg_color[0],txt_color[1]);
	    TFT_String(15,45+45+40+(43*1),(uint8_t *)str[1],bg_color[1],txt_color[0]);
	    TFT_Number(15+220,45+45+40+(43*0),Occl.Zero_PSI,bg_color[0],txt_color[1]);
	    TFT_Number(15+220,45+45+40+(43*1),strain_20PSI_val[syr_size],bg_color[1],txt_color[0]);
	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void warning_screen_0PSI( )
{
	//    Rectangle(0,0,320,240,MAIN_FRAME_COL);
		CLRSCR(MAIN_FRAME_COL);
	    Rectangle(0,0,320,35,NEW_HDR_COL);
	    Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"0 PSI Calibration");

	    Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press         to Calibrate",(uint8_t*)"OK",2,14);
//	    TFT_ST7789V_lcd_drawcircle1(221+1,150-11,15,MAIN_FRAME_COL,MAIN_FRAME_COL);
//
//	    Font_Select(ARIAL_9);
//	    TFT_String(216+1,141-11,(uint8_t*)"OK",MAIN_FRAME_COL,WHITE);


	    TFT_ST7789V__rectangle_curve(7,45,150,305,0,WHITE); // SCREEN

		Font_Select(ARIAL_14);
		TFT_String(30-10,80+15,(uint8_t*)" 1.  Don't touch the Plunger",WHITE,BLACK);


		TFT_String(43,105+15,(uint8_t*)" Disc",WHITE,BLACK);


	    TFT_String(30-10,140+15,(uint8_t*)" 2. Ensure No Syringe",WHITE,BLACK);
	    TFT_ST7789V_Triangle_24pt(50,90,0,WHITE,WARNING_COLOR);
	    TFT_String(130,53,(uint8_t*)"Warning",WHITE,BLACK);
	    TFT_ST7789V_Exclamatory_9pt_arial(59,101,0,WARNING_COLOR,BLACK);

}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void warning_screen_20PSI( )
{
	    Rectangle(0,36,320,240,MAIN_FRAME_COL);
//	    Rectangle(0,0,320,35,NEW_HDR_COL);
//	    Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"20 PSI Calibration");

	    Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press         to Start calib",(uint8_t*)"ST",2,14);
//	    TFT_ST7789V_lcd_drawcircle1(221+1,150-11,16,MAIN_FRAME_COL,MAIN_FRAME_COL);
//
//	    Font_Select(ARIAL_9);
//	    TFT_String(216+1,141-11,(uint8_t*)"ST",MAIN_FRAME_COL,WHITE);


	    TFT_ST7789V__rectangle_curve(7,45,150,305,0,WHITE); // SCREEN

		Font_Select(ARIAL_14);
		TFT_String(30-10,80+15,(uint8_t*)" 1.  Ensure the priming of",WHITE,BLACK);


		TFT_String(43,105+15,(uint8_t*)"Syringe",WHITE,BLACK);


	    TFT_String(30-10,140+15,(uint8_t*)" 2. Connect the PG",WHITE,BLACK);

	    TFT_ST7789V_Triangle_24pt(50,90,0,WHITE,WARNING_COLOR);
		TFT_String(130,53,(uint8_t*)"Warning",WHITE,BLACK);
		TFT_ST7789V_Exclamatory_9pt_arial(59,101,0,WARNING_COLOR,BLACK);


}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void INFO_Screen_0PSI(uint8_t screen)
{
	uint8_t x_pos=0;
	Rectangle(0,36,320,240,MAIN_FRAME_COL);

	Font_Select(ARIAL_20);
	if(screen==3)
	{
		Rectangle(0,40,320,160,MAIN_FRAME_COL);
		TFT_ST7789V__rectangle_curve(7,45,150,305,0,WHITE);

		TFT_String_align(0,0,75,(uint8_t *)" Enter the PSI",2,WHITE,BLACK);
		TFT_String_align(0,0,115,(uint8_t *)" value display",2,WHITE,BLACK);
		TFT_String_align(0,0,155,(uint8_t *)"in the PG..",2,WHITE,BLACK);

	}
	else if(screen==2)
	{
		x_pos=Letters_Alignments(0,0,(uint8_t*)"Wait For         Secs...",2);
		TFT_String(x_pos,120,(uint8_t*)"Wait For         Secs...",MAIN_FRAME_COL,WHITE);
	}
	else if(screen==1)
	{
		TFT_ST7789V__rectangle_curve(7,45,185,305,0,WHITE);
		x_pos=Letters_Alignments(0,0,(uint8_t*)"Calibrated",2);
		TFT_String(x_pos,120,(uint8_t*)"Calibrated",WHITE,BLACK);
	}
	else
	{
		TFT_ST7789V__rectangle_curve(7,45,185,305,0,WHITE);
		x_pos=Letters_Alignments(0,0,(uint8_t*)"Calibration Fail!",2);
		TFT_String(x_pos,120,(uint8_t*)"Calibration Fail!",WHITE,BLACK);
	}

}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void INFO_Screen_20PSI()
{
	Rectangle(0,36,320,240,MAIN_FRAME_COL);
//	Rectangle(0,0,320,35,NEW_HDR_COL);
//	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"20 PSI Calibration");
	Font_Select(ARIAL_14);
	TFT_String(10,80+30+10,(uint8_t*)"*",MAIN_FRAME_COL,YELLOW);
	TFT_String(40,80+30+10,(uint8_t*)"Stop the Motor Once ",MAIN_FRAME_COL,WHITE);
	TFT_String(40,105+30+10+10,(uint8_t*)"20 PSI Reached in PG",MAIN_FRAME_COL,WHITE);
//	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press         to Calibrate",(uint8_t*)"ST",1);
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press         to Store",(uint8_t*)"ST",2,14);
}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void Running_symbol(uint8_t X_start, uint8_t Y_start,uint32_t col)
{

	uint8_t Y_pos[3]={5,20,35};

//  uint32_t col=0x505050;
//	uint32_t colour[4][3]={{LIGHT_GRAY,LIGHT_GRAY,YELLOW},{LIGHT_GRAY,YELLOW,YELLOW},
//			               {YELLOW,YELLOW,YELLOW},{LIGHT_GRAY,LIGHT_GRAY,LIGHT_GRAY}};

	uint32_t colour[4][3]={{DARK_GRAY,DARK_GRAY,LIGHT_GREEN},{DARK_GRAY,LIGHT_GREEN,LIGHT_GREEN},
				               {LIGHT_GREEN,LIGHT_GREEN,LIGHT_GREEN},{DARK_GRAY,DARK_GRAY,DARK_GRAY}};
	uint8_t pos;
	uint8_t X_pos=4;
	static uint8_t state=0;

	 if(!G_run_count)
	 {

		 for(pos=0;pos<=2;pos++)
		 {
			 TFT_ST7789V_Left_Arrow_22pt(X_pos+X_start,Y_pos[pos]+Y_start,0,col,colour[state][pos]);		//corner
		 }

		 if(state<3)
		 {
			 state++;
		 }
		 else
		 {
			 state=0;
		 }

		 G_run_count=2;

	 }
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint16_t X_pos_align(uint16_t value)
{
	uint16_t x_pos = 0;

	if(value<=9)
	{
		x_pos = 135;
	}
	else if(value<=99)
	{
		x_pos = 120;
	}

	else if(value<=999)
	{
		x_pos = 100;
	}
	else
	{
		x_pos = 85;
	}

return x_pos;
}

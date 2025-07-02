/*
 * SYR_length_frame.c
 *
 *  Created on: 29-Feb-2024
 *      Author: Software4
 */
#include "Linear_Header.h"
#include "Syringe_calib_header.h"
#include "Driver_ADC.h"
#include "color.h"
#include "TFT_Commands.h"
#include "TFT_String.h"
#include "Keypad.h"
#include "Shapes.h"
#include "Power_off.h"
#include "Driver_Timer.h"
#include "Driver_I2C.h"
#include "Occlusion.h"
#include "SD_Calib.h"
#include <Boot_up.h>

extern uint8_t brand_select_no;

extern volatile uint16_t value_l[8];
extern volatile uint16_t value_c[8];
extern uint16_t sl_pullout_ADC;
extern uint16_t sl_pullin_ADC;
extern uint16_t linear_temp_adc;
extern uint16_t Syr_Lenght_min_Limit[7];//={0,0,200,350,450,500,550};
extern uint16_t Syr_Length_max_Limit[7];//={0,0,550,700,800,1000,1100};
extern uint16_t length_l[8];
void swap_sysize_glow(uint8_t currentOption,uint8_t prev_sysize);
extern void frame_footer_press_ok_to_edit();

uint16_t temp_sl_pull_in=0;
uint16_t temp_sl_pull_out=0;

/*****************************************************************************
* Function Name : void frame_syr_len_and_plunger_adc_main(uint8_t cursor,uint8_t screen)
* Arguments     : cursor,screen
* Return type   : void
* Description   : these function display the main screen of and navigation sl calibration.

*****************************************************************************/

void frame_syr_len_and_plunger_adc_main(uint8_t cursor,uint8_t screen)
{
	uint8_t loop_count=0;
	char* str[2]={"Syringe Length calibration"};   //,"Plunger ADC calibration"};//REW_UP
	uint32_t   txt_color[2]={WHITE,BLACK};
	uint32_t   bg_color[2]={WHITE,MAIN_FRAME_COL};

    if(screen)
    {
    	   // Rectangle(0,0,320,240,MAIN_FRAME_COL);
    		CLRSCR(MAIN_FRAME_COL);
    	 //   Rectangle(0,0,320,35,NEW_HDR_COL);
    	    Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"SL Calibration");
    	    frame_footer_press_ok_to_edit();
    }

    else
    {
    	Rectangle(7,5+36+(43*0),290+16,40,MAIN_FRAME_COL);
    }

	TFT_ST7789V__rectangle_curve(7,5+36+(43*0),40,290+16,0,WHITE);

//	for(loop_count = 1; loop_count < 2 ; loop_count++)
//		{
//			Rectangle(7,5+34+(43*loop_count),290+16,0, BLACK);// line
//		}
   	    Rectangle_Line_function(1,0);

		Font_Select(ARIAL_14);

		TFT_String(15,5+45+(43*0),(uint8_t *)str[0],bg_color[0],txt_color[1]);
	    TFT_String(15,5+45+(43*1),(uint8_t *)str[1],bg_color[1],txt_color[0]);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void frame_syringe_size_glow(uint8_t state)
{
	int row=0,col=0;
	int sysize=1;

	uint8_t acutual_size;
	acutual_size=detect_syringe_size(1);            //detect_syringe_size(2);

	unsigned int   color[2]={GRAY,WHITE};
	int sel=0;
	char* mat[7]={"789"," 2 mL"," 5 mL","10 mL","20 mL","30 mL","50 mL"};

	//Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	if(state==1)
	{
		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"SL Calibration");
		Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press         to Confirm",(uint8_t*)"OK",2,14);

	}
	else if((state==0))
	{
		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"20 PSI Calibration");
	}

	Font_Select(ARIAL_14);

	 for(row=0;row<1;row++)
	 {
		 for(col=0;col<3;col++)
			{
 			 if(acutual_size == sysize)
			 {
			   sel=1;
			 }
			  else sel=0;

			 TFT_ST7789V__rectangle_curve(25+(95*col),62,50,80,0,color[sel]); // cursor box // caution window -- Y   X 1

			 TFT_String(40+(95*col),75,(uint8_t *)mat[sysize],color[sel],BLACK);

			 if(acutual_size == sysize+3)
			 {
			   sel=1;
			 }

			 else
			   sel=0;

			 TFT_ST7789V__rectangle_curve(25+(95*col),130,50,80,0,color[sel]); // cursor box // caution window -- Y   X 1
			 TFT_String(35+(95*col),145,(uint8_t *)mat[sysize+3],color[sel],BLACK);
			 sysize++;
		   }
	  }
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void swap_sysize_glow(uint8_t currentOption,uint8_t prev_sysize1)
{
	uint8_t row1=0,col1=0;
	uint8_t row2=0,col2=0;

//	uint8_t sysize=0;

	uint8_t acutual_size=currentOption;            //detect_syringe_size(2);

	uint32_t   color[2]={GRAY,WHITE};

	uint8_t sel=0;

	char* mat[7]={"789"," 2 mL"," 5 mL","10 mL","20 mL","30 mL","50 mL"};


	Font_Select(ARIAL_14);


	if (acutual_size >= 1 && acutual_size <= 6)
	{
		 row1 = (acutual_size - 1) / 3;
		 col1 = (acutual_size - 1) % 3;
	}
	if (prev_sysize1 >= 1 && prev_sysize1 <= 6)
	{
		 row2 = (prev_sysize1 - 1) / 3;
		 col2 = (prev_sysize1 - 1) % 3;
	}
  //  printf("\n acutual_size = %d prev_sysize = %d",acutual_size,prev_sysize);

	if(!acutual_size)
	{
	  sel=0;
	}
	else
	{
	  sel=1;
	}

	TFT_ST7789V__rectangle_curve(25+(95*col1),62+(68*row1),50,80,0,color[sel]);

	if(acutual_size)
	{
		TFT_String(40+(row1*-5)+(95*col1),75+(row1*70),(uint8_t *)mat[acutual_size],color[sel],BLACK);
	}
	else
	{
		TFT_String(40+(row1*-5)+(95*col1),75+(row1*70),(uint8_t *)mat[1],color[sel],BLACK);
	}

	sel=0;

	if(prev_sysize1)
	{
		TFT_ST7789V__rectangle_curve(25+(95*col2),62+(68*row2),50,80,0,color[sel]);
		TFT_String(40+(row2*-5)+(95*col2),75+(row2*70),(uint8_t *)mat[prev_sysize1],color[sel],BLACK);
	}

}


/****************************************************************************
* Function Name : void syringe_length_and_collar_main_screen(uint8_t cursor,uint8_t screen)
* Arguments     : cursor,screen
* Return type   : void
* Description   : these function display the main screen of syringe length and collar main screen

*****************************************************************************/



void syringe_length_and_collar_main_screen(uint8_t cursor,uint8_t screen)
{
//	    uint8_t sel=0;
		uint8_t loop_count=0;
		char* str[2]={"Syr Length (mm)","Col Length (mm)"};
		uint32_t   txt_color[2]={WHITE,BLACK};
		uint32_t   bg_color[2]={WHITE,MAIN_FRAME_COL};
		float length_disp[8];
		float collar_disp[8];
		volatile uint8_t syrs_size=0;

		syrs_size=detect_syringe_size(1);


		value_l[syrs_size]= EEPROM_dataread(EEPROM_SL_LEN_VAL+(brand_select_no)*12+((syrs_size-1)*2), 2);

		if(value_l[syrs_size] > Syr_Length_max_Limit[syrs_size])
		{
			value_l[syrs_size] = Syr_Length_max_Limit[syrs_size];
			EEPROM_datawrite(EEPROM_SL_LEN_VAL+(brand_select_no)*12+((syrs_size-1)*2),value_l[syrs_size], 2);
		}

	   value_c[syrs_size]= EEPROM_dataread(EEPROM_SL_COL_VAL+(brand_select_no)*12+((syrs_size-1)*2), 2);

		if(value_c[syrs_size] > 300)
		{
			value_c[syrs_size] = 300;
			EEPROM_datawrite(EEPROM_SL_COL_VAL+(brand_select_no)*12+((syrs_size-1)*2),value_c[syrs_size], 2);
		}

		length_disp[syrs_size]=value_l[syrs_size];
		collar_disp[syrs_size]=value_c[syrs_size];


//		TFT_Number(85,50,length_l[1],MAIN_FRAME_COL,RED);
//		delay_secs(2);

		if(screen)
        {
       // 	Rectangle(0,0,320,240,MAIN_FRAME_COL);
			CLRSCR(MAIN_FRAME_COL);
			Rectangle(0,0,320,35,NEW_HDR_COL);
			Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"SL Calibration");
			frame_footer_press_ok_to_edit();
        }
		if(cursor)
		{
			Rectangle(7,5+36+(43*0),290+16,40,MAIN_FRAME_COL);
		}
		else
		{
			Rectangle(7,5+36+(43*1),290+16,40,MAIN_FRAME_COL);
		}

		Font_Select(ARIAL_14);

		for(loop_count = 1; loop_count <=2 ; loop_count++)
		{
			Rectangle(7,5+34+(43*loop_count),290+16,0, BLACK);
		}

		TFT_ST7789V__rectangle_curve(7,5+36+(43*cursor),40,290+16,0,WHITE); // cursor

		if(cursor==1)
		{
		   TFT_String(15,5+45+(43*0),(uint8_t *)str[0],bg_color[1],txt_color[0]);
		   TFT_String(15,5+45+(43*1),(uint8_t *)str[1],bg_color[0],txt_color[1]);

		   TFT_String(200,5+43,(uint8_t *)":",bg_color[1],txt_color[0]);
		   TFT_String(200,5+86,(uint8_t *)":",bg_color[0],txt_color[1]);

		   TFT_writenumber_float_1d(210+15,5+45+(43*0),length_disp[syrs_size],bg_color[1],txt_color[0]);
		   TFT_writenumber_float_1d(210+15,5+45+(43*1),collar_disp[syrs_size],bg_color[0],txt_color[1]);

		}

		else
		{
		  TFT_String(15,5+45+(43*0),(uint8_t *)str[0],bg_color[0],txt_color[1]);
		  TFT_String(15,5+45+(43*1),(uint8_t *)str[1],bg_color[1],txt_color[0]);

		  TFT_String(200,5+43,(uint8_t *)":",bg_color[0],txt_color[1]);
		  TFT_String(200,5+86,(uint8_t *)":",bg_color[1],txt_color[0]);

		  TFT_writenumber_float_1d(210+15,5+45+(43*0),length_disp[syrs_size],bg_color[0],txt_color[1]);
		  TFT_writenumber_float_1d(210+15,5+45+(43*1),collar_disp[syrs_size],bg_color[1],txt_color[0]);
		}


}

/////////////////////////////////////////////////////////////////////////////////////
/****************************************************************************
* Function Name : void plunger_adc_live_main_screen()
* Arguments     : void
* Return type   : void
* Description   : this function display pull in pull out navigation screen  with cureent loaded value.

*****************************************************************************/

void plunger_adc_screen(uint8_t cursor,uint8_t screen)
{



		if(screen)
		{

		//  Rectangle(0,0,320,240,MAIN_FRAME_COL);
			CLRSCR(MAIN_FRAME_COL);
			Rectangle(0,0,320,35,NEW_HDR_COL);
			Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Accuracy Calibration");
			Font_Select(CALIBRI_48);

			//*********************************4_Menu_Alignments***********************************//
			Rectangle(7,118,290,0,BLACK);
			Rectangle(7,162,290,0,BLACK);
			Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press          to Calibrate",(uint8_t*)"OK",2,14);

		}

			TFT_ST7789V__rectangle_curve(5 ,120+(40*0),40,310,0,MAIN_FRAME_COL);
			TFT_ST7789V__rectangle_curve(5 ,120+(40*1),40,310,0,MAIN_FRAME_COL);
			TFT_ST7789V__rectangle_curve(5 ,120+(40*cursor),40,310,0,WHITE);  //Rectangle Curve Option 1
			Font_Select(ARIAL_14);

		if(!cursor)
		{

			TFT_String(10,131,(uint8_t *)"Pull out ADC",WHITE,BLACK); //-1
			TFT_String(180,131,(uint8_t *)":",WHITE,BLACK);
			TFT_Number(210,131,sl_pullout_ADC,WHITE,BLACK);
			TFT_String(10,172,(uint8_t *)"Pull in ADC",MAIN_FRAME_COL,WHITE);
			TFT_String(180,172,(uint8_t *)":",MAIN_FRAME_COL,WHITE);
			TFT_Number(210,172,sl_pullin_ADC,MAIN_FRAME_COL,WHITE);

		}

		else
		{

			TFT_String(10,131,(uint8_t *)"Pull out ADC",MAIN_FRAME_COL,WHITE);//-2
			TFT_String(10,131,(uint8_t *)"Pull out ADC",MAIN_FRAME_COL,WHITE);
			TFT_String(180,131,(uint8_t *)":",MAIN_FRAME_COL,WHITE);
			TFT_Number(210,131,sl_pullout_ADC,MAIN_FRAME_COL,WHITE);
			TFT_String(10,172,(uint8_t *)"Pull in ADC",WHITE,BLACK);
			TFT_String(180,172,(uint8_t *)":",WHITE,BLACK);
			TFT_Number(210,172,sl_pullin_ADC,WHITE,BLACK);

		}

}

/****************************************************************************
* Function Name : void warning_screen_ADC( uint8_t disp_1)
* Arguments     : disp_1
* Return type   : void
* Description   : these function display the warning screen for pull in & pull out

*****************************************************************************/

void warning_screen_ADC( uint8_t disp_1)
{

	 //   Rectangle(0,0,320,240,MAIN_FRAME_COL);
		CLRSCR(MAIN_FRAME_COL);
	    Rectangle(0,0,320,35,NEW_HDR_COL);
	    Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Accuracy Calibration");

	    Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press         to Calibrate",(uint8_t*)"OK",2,14);


	    TFT_ST7789V__rectangle_curve(7,45,150,305,0,WHITE); // SCREEN

		Font_Select(ARIAL_14);
		TFT_String(30-10,80+15,(uint8_t*)" 1.  Ensure the plunger is",WHITE,BLACK);

		if(disp_1)
		{
			TFT_String(43,105+15,(uint8_t*)" fully in",WHITE,BLACK);
		}
		else
		{
			TFT_String(43,105+15,(uint8_t*)" fully out",WHITE,BLACK);
		}

	    TFT_String(30-10,140+15,(uint8_t*)" 2. Ensure no Syringe",WHITE,BLACK);
	    TFT_String(130,53,(uint8_t*)"Warning",WHITE,BLACK);
	    TFT_ST7789V__rectangle_curve(100,50,25,25,0,YELLOW);
	    TFT_String(112,53,(uint8_t*)"!",YELLOW,BLACK);

}

/****************************************************************************
* Function Name : void warning_calibrated_screen( uint8_t cursor)
* Arguments     : cursor
* Return type   : void
* Description   : these function display the warning calibrated screen for pull in & pull out

*****************************************************************************/

void warning_calibrated_screen( uint8_t cursor)
{


//	    Rectangle(0,0,320,240,MAIN_FRAME_COL);
		CLRSCR(MAIN_FRAME_COL);
	    Rectangle(0,0,320,35,NEW_HDR_COL);
	    Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Accuracy Calibration");
	    Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press         to Calibrate",(uint8_t*)"OK",2,14);

	    TFT_ST7789V__rectangle_curve(7,45,150,305,0,WHITE); // SCREEN

	     if(cursor)
	     {
	    	 temp_sl_pull_in=linear_temp_adc;
	     }
	     else
	     {
	    	 temp_sl_pull_out=linear_temp_adc;
	     }

//	     Font_Select(ARIAL_14);
//	     TFT_Number(0,90,temp_sl_pull_out,YELLOW,RED);
//	     TFT_Number(0,110,temp_sl_pull_in,YELLOW,RED);
//
//	     delay_secs(2);

		// if(temp_sl_pull_in<temp_sl_pull_out)

	     if(!cursor)
	     {

			 if( (temp_sl_pull_out<62900) && (60800<temp_sl_pull_out) )
			 {
				 sl_pullout_ADC=linear_temp_adc;
				 EEPROM_datawrite(EEPROM_SL_PULL_OUT,sl_pullout_ADC,2);
				 Font_Select(ARIAL_20);
				 TFT_String(30+10+10,110,(uint8_t*)"        Calibrated   ",WHITE,BLACK);
			 }
			 else
			 {
				 Font_Select(ARIAL_20);
			     TFT_String(30+10+10,110,(uint8_t*)"Calibration Failed",WHITE,BLACK);
			 }

	     }

	     else
	     {

			 if( (temp_sl_pull_in<4500) && (1500<temp_sl_pull_in) )
			 {
				 sl_pullin_ADC=linear_temp_adc;
				 EEPROM_datawrite(EEPROM_SL_PULL_IN,sl_pullin_ADC,2);
				 Font_Select(ARIAL_20);
				 TFT_String(30+10+10,110,(uint8_t*)"        Calibrated   ",WHITE,BLACK);
			 }

			 else
			 {
				 Font_Select(ARIAL_20);
				 TFT_String(30+10+10,110,(uint8_t*)"Calibration Failed",WHITE,BLACK);
			 }

		}


}

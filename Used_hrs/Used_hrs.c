/****************************************************************************
* File Name    :
* Developed by :
* Version      :
* Description  :

*****************************************************************************/

#include "LPC55S16.h"
#include "Color.h"
#include "TFT_Commands.h"
#include "TFT_String.h"
#include "clock_config.h"
#include "Driver_Timer.h"
#include "Main_Menu.h"
#include <FR_CALC.h>
#include <Consumed_hrs.h>
#include "Motor.h"
#include"Driver_I2C.h"
#include <Shapes.h>
#include "Power_off.h"
#include "Dosage_mode.h"
#include <infused_calculate.h>
#include "Bolus_Header.h"
#include <Boot_up.h>

uint8_t minute=0;
uint8_t hrs=0;
uint8_t factory_reset_flag=0;

extern uint16_t temp_ADC_values;
extern uint8_t warning_flag[3];

Reached UTILIZED;

extern uint8_t ON_Flag;
extern uint16_t used_hrs_count;
extern uint8_t G_occl_unit;
extern uint32_t G_kvo;	//22-03
extern uint32_t G_KVO_fr;
extern uint8_t brand_select_no;
extern uint8_t G_infusion_modes;
extern uint8_t G_drug_list;
extern uint8_t total_fav;
extern uint8_t total_recent;
extern uint16_t total_events;//29-03
extern uint8_t G_bright_level;
extern uint8_t G_sound_level;
extern uint8_t G_lock_time;
extern uint8_t G_infusion_mode_opt;
extern uint16_t maxi_lmt[7];
extern uint8_t G_occl_level;
extern uint8_t G_last_data;

extern volatile uint8_t normal_run;
void usedhrs_status(void);
void Packing_reset_frame(void);
void Reset_loading(uint8_t loading_level);
void Complete_Reset();
void Complete_reset_frame(void);
void FR_and_Elapsed_data(void);

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void machine_on_used_hrs(void)
{

		if(UTILIZED.device_sec_cnt>2)
		{
			UTILIZED.device_sec_cnt=0;
			UTILIZED.device_min_cnt++;
		}

		if(UTILIZED.device_min_cnt>2)
		{
			UTILIZED.device_min_cnt=0;
			UTILIZED.device_hrs_cnt++;
	//		factory_reset_flag=0;
		}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void battery_used_hrs(void)
{
	if(UTILIZED.battery_sec_cnt>2)
	{
		UTILIZED.battery_sec_cnt=0;
		UTILIZED.battery_min_cnt++;
	}

	if(UTILIZED.battery_min_cnt>2)
	{
		UTILIZED.battery_min_cnt=0;
		UTILIZED.battery_hrs_cnt++;
	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void run_stop_used_hrs(void)
{

	if(UTILIZED.running_sec_cnt>2)
	{
		UTILIZED.running_sec_cnt=0;
		UTILIZED.running_min_cnt++;
	}

	if(UTILIZED.running_min_cnt>2)
	{
		UTILIZED.running_min_cnt=0;
		UTILIZED.running_hrs_cnt++;
	}

}

void usedhrs_status(void)
{
	run_stop_used_hrs();
	machine_on_used_hrs();
	if(BATT.mode)
	{
		battery_used_hrs();
	}

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

//void Packing_reset()
//{
////	uint8_t  max_fav_page=0;
////  uint8_t  max_fav_opt=0;
////  uint8_t page=0;
////  uint8_t page_no=0;
////  uint8_t end_option_no=0;
//    uint8_t loop_count=0;
//
////	max_fav_page=(total_fav-1)/4;
////	max_fav_opt=(total_fav-1)%4;
////
////	if(page_no == max_fav_page)
////	{
////		end_option_no = max_fav_opt;
////	}
////
////	else
////	{
////		end_option_no = 3;
////	}
////
////	for(loop_count=0;loop_count<=end_option_no;loop_count++)
////	 {
////		 if( ((page*4)+loop_count) == dose.drug_select_no)
////		 {
////			TFT_ST7789V_tick_symbol_14pt((INITIAL_TEXT_POS)+(loop_count)*VER_TEXT_SPACE_1,250,0,MAIN_FRAME_COL,MAIN_FRAME_COL);
////		 }
////	 }
//
//	 Packing_reset_frame();
//	 Reset_loading(1);
//
//	 /****************************LEVEL1*******************************/
//
//	 /*****************************************************************/
//	 Reset_loading(2);
//	 /****************************LEVEL2*******************************/
//
//	 /*****************************************************************/
//	 Reset_loading(3);
//	 /****************************LEVEL3*******************************/
//
//	 /*****************************************************************/
//	 Reset_loading(4);
//	 /****************************LEVEL4*******************************/
//
//	 /*****************************************************************/
//	 Reset_loading(5);
//	 /****************************LEVEL5******************************/
//
//	 /*****************************************************************/
//	 Reset_loading(6);
//	 /****************************LEVEL6*******************************/
//
//	 /*****************************************************************/
//	// Reset_loading(7);
//
///*************************************USED_HRS_RESET*************************/
//
//	if(!factory_reset_flag)
//	{
//		UTILIZED.factory_used_hrs=UTILIZED.device_hrs_cnt;
//		EEPROM_datawrite(EEPROM_FACTORY_HRS,UTILIZED.factory_used_hrs,2);
//		factory_reset_flag=1;
//		EEPROM_datawrite(EEPROM_FACTORY_RST,factory_reset_flag,1);
//	}
//	EEPROM_usedhrs_write(2);//EXCEPT FACTORY USED HRS RESET TO ZERO(PASSING VALUE 2)
//
////***************************FR and Elapsed Data***************************//
////
//		   MOT.flowrate=00;
//		   dose.flow_rate=00;
//		   MOT.time=00;
//		   MOT.volume=00;
//		   INFUSED.ml=0;
//
////***************************Menu_Settings*********************************//
//
//			BOL.mode=1;                             //Bolus
//			BOL.flowrate=1000;
//
//			for(loop_count=0;loop_count<=5;loop_count++)
//			{
//				BOL.limit[loop_count]=maxi_lmt[loop_count];
//			}
//
//			G_occl_unit=0;							//Occlusion
//			G_occl_level=0;
//
//			G_kvo=0;								//KVO
//			G_KVO_fr=1;
//
//			brand_select_no=0;						//Syringe_Brand
//
//			G_infusion_modes=0;                     //Modes
//
//
//			G_drug_list=1; 							//Drug Archive
//			total_fav=0;
//			total_recent=0;
//
//			total_events=0;							//Event Log
//
//	//		G_date_mnth=0;                          //Date and Month
//	//		G_year=0;								//Year
//	//		G_time=0;								//Time
//	//		G_time_format=0;						//Format
//
////****************************System_Setting****************************//
//
//			G_bright_level=5;						//Brightness Level
//			G_sound_level=5;						//Sound Level
//			G_lock_time=0;							//Auto Lock
//			G_infusion_mode_opt=3;					//Infusion Modes
//			G_drug_list=0;							//Drug List
//			G_last_data=1;
///*****************************************************************************/
//
//
//
//
//
//	 Reset_loading(7);
//
//}

void Packing_reset_frame(void)
{
	uint8_t xpos=0;
	//Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	Font_Select(ARIAL_14);

	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"PACKING RESET");

	Frame_Footer_NC(NEW_FTR_COL,HDR_TXT_COL,(uint8_t *)"Please wait");

//	Font_Select(ARIAL_14);
	xpos=Letters_Alignments(0,320, (uint8_t*)"Reset Processing...",0);
	TFT_String(xpos,170,(uint8_t *)"Reset Processing..." ,MAIN_FRAME_COL,WHITE);

}

void Complete_reset_frame(void)
{
	uint8_t xpos=0;
//	Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	Font_Select(ARIAL_14);

	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"COMPLETE RESET");

	Frame_Footer_NC(NEW_FTR_COL,HDR_TXT_COL,(uint8_t *)"Please wait");

//	Font_Select(ARIAL_14);
	xpos=Letters_Alignments(0,320, (uint8_t*)"Reset Processing...",0);
	TFT_String(xpos,170,(uint8_t *)"Reset Processing..." ,MAIN_FRAME_COL,WHITE);

}

void Reset_loading(uint8_t loading_level)
{
	uint8_t loading_cnt=0;
	uint8_t loop_count=0;
	loading_cnt=loading_level*20;
	if(loading_cnt>140)
	{
		loading_cnt=140;
	}
	for(loop_count=loading_cnt-20;loop_count<=loading_cnt;loop_count++)
	{
		Rectangle(20+(loop_count*2),120,0,30,WHITE);
		delay_us(20);
	}

}

void EEPROM_usedhrs_write(uint8_t default_write)
{
	if(default_write)
	{
		UTILIZED.device_sec_cnt=0;
		UTILIZED.device_min_cnt=0;
		UTILIZED.device_hrs_cnt=0;

		UTILIZED.battery_sec_cnt=0;
		UTILIZED.battery_min_cnt=0;
		UTILIZED.battery_hrs_cnt=0;

		UTILIZED.running_sec_cnt=0;
		UTILIZED.running_min_cnt=0;
		UTILIZED.running_hrs_cnt=0;

	if(default_write==1)
	{

		UTILIZED.factory_used_hrs=0;
	    //TFT_Number(100,70,61,YELLOW,RED);

		EEPROM_datawrite(EEPROM_FACTORY_HRS,UTILIZED.factory_used_hrs,2);
	   // TFT_Number(112,70,62,YELLOW,RED);

	}
	}
	// TFT_Number(100,70,61,YELLOW,RED);
	EEPROM_datawrite(EEPROM_DEVICE_SEC,UTILIZED.device_sec_cnt,1);
	EEPROM_datawrite(EEPROM_DEVICE_MIN,UTILIZED.device_min_cnt,1);
	EEPROM_datawrite(EEPROM_DEVICE_HRS,UTILIZED.device_hrs_cnt,2);
//
	EEPROM_datawrite(EEPROM_BATTERY_SEC,UTILIZED.battery_sec_cnt,1);
	EEPROM_datawrite(EEPROM_BATTERY_MIN,UTILIZED.battery_min_cnt,1);
	EEPROM_datawrite(EEPROM_BATTERY_HRS,UTILIZED.battery_hrs_cnt,2);
//
	EEPROM_datawrite(EEPROM_RUNNING_SEC,UTILIZED.running_sec_cnt,1);
	EEPROM_datawrite(EEPROM_RUNNING_MIN,UTILIZED.running_min_cnt,1);
	EEPROM_datawrite(EEPROM_RUNNING_HRS,UTILIZED.running_hrs_cnt,2);

}

void EEPROM_usedhrs_read(void)
{
			UTILIZED.device_sec_cnt=EEPROM_dataread(EEPROM_DEVICE_SEC,1);
			UTILIZED.device_min_cnt=EEPROM_dataread(EEPROM_DEVICE_MIN,1);
			UTILIZED.device_hrs_cnt=EEPROM_dataread(EEPROM_DEVICE_HRS,2);
			if(UTILIZED.device_sec_cnt<1 || UTILIZED.device_min_cnt<1 ||
					UTILIZED.device_hrs_cnt<1 )
			{
				UTILIZED.device_sec_cnt=0;
				UTILIZED.device_min_cnt=0;
				UTILIZED.device_hrs_cnt=0;
			}

			UTILIZED.battery_sec_cnt=EEPROM_dataread(EEPROM_BATTERY_SEC,1);
			UTILIZED.battery_min_cnt=EEPROM_dataread(EEPROM_BATTERY_MIN,1);
			UTILIZED.battery_hrs_cnt=EEPROM_dataread(EEPROM_BATTERY_HRS,2);
			if(UTILIZED.battery_sec_cnt>60 || UTILIZED.battery_min_cnt>60 ||
							UTILIZED.battery_hrs_cnt>10000 )
			{
				UTILIZED.battery_sec_cnt=0;
				UTILIZED.battery_min_cnt=0;
				UTILIZED.battery_hrs_cnt=0;
			}

			UTILIZED.running_sec_cnt=EEPROM_dataread(EEPROM_RUNNING_SEC,1);
			UTILIZED.running_min_cnt=EEPROM_dataread(EEPROM_RUNNING_MIN,1);
			UTILIZED.running_hrs_cnt=EEPROM_dataread(EEPROM_RUNNING_HRS,2);

			if(UTILIZED.running_sec_cnt>60 || UTILIZED.running_min_cnt>60 ||
										UTILIZED.running_hrs_cnt>10000 )
			{
				UTILIZED.running_sec_cnt=0;
				UTILIZED.running_min_cnt=0;
				UTILIZED.running_hrs_cnt=0;
			}


			UTILIZED.factory_used_hrs=EEPROM_dataread(EEPROM_FACTORY_HRS,2);
			if(UTILIZED.factory_used_hrs>10000)
			{
				UTILIZED.factory_used_hrs=0;
			}
}

void reset_fun(uint8_t type_rest)
{

	reset_frame(type_rest);

	 //Packing_reset_frame();
	 Reset_loading(1);
	 /****************************LEVEL1*******************************/

	 /*****************************************************************/
	 Reset_loading(2);
	 /****************************LEVEL2*******************************/

	 /*****************************************************************/
	 Reset_loading(3);
	 /****************************LEVEL3*******************************/

	 /*****************************************************************/
	 Reset_loading(4);
	 /****************************LEVEL4*******************************/

	 /*****************************************************************/
	 Reset_loading(5);
	 /****************************LEVEL5******************************/

	 /*****************************************************************/
	 Reset_loading(6);
	 /****************************LEVEL6*******************************/

	 /*****************************************************************/
	 //Reset_loading(7);

/*************************************USED_HRS_RESET*************************/
	 if(type_rest==2)
	 {
		 EEPROM_occul_write_data();
		 EEPROM_Plunger_tuning_calib_write();
		 EEPROM_SL_calib_write();
		 EEPROM_SD_calib_write();
		 UTILIZED.factory_used_hrs=0;
		 EEPROM_datawrite(EEPROM_FACTORY_HRS,UTILIZED.factory_used_hrs,2);
		 factory_reset_flag=1;
	 }
	 else
	 {
		 factory_reset_flag=0;

	 }

	 Font_Select(ARIAL_14);
	 TFT_Number(50,70,factory_reset_flag,YELLOW,RED);

	delay_secs(3);
	if(!factory_reset_flag)
	{
		UTILIZED.factory_used_hrs=UTILIZED.device_hrs_cnt;
		EEPROM_datawrite(EEPROM_FACTORY_HRS,UTILIZED.factory_used_hrs,2);
		factory_reset_flag=1;
		EEPROM_datawrite(EEPROM_FACTORY_RST,factory_reset_flag,1);
	}



	EEPROM_usedhrs_write(2);//EXCEPT FACTORY USED HRS RESET TO ZERO(PASSING VALUE 2)
	EEPROM_menu_sett_write();
	Device_sett_EEPROM_write();
	EEPROM_fact_write();
	FR_and_Elapsed_data();
	//Default

/*****************************************************************************/
	 Reset_loading(7);

}

void reset_frame(uint8_t Reset_mode)
{
	//uint8_t xpos=0;
	CLRSCR(MAIN_FRAME_COL);
	Font_Select(ARIAL_14);

	if(Reset_mode==1)
	{
		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"PACKING RESET");
	}
	else
	{
		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"COMPLETE RESET");
	}



	Frame_Footer_NC(NEW_FTR_COL,HDR_TXT_COL,(uint8_t *)"Please wait");

	Font_Select(ARIAL_14);
//	xpos=Letters_Alignments(0,320, (uint8_t*)"Reset Processing...",0);
//	TFT_String(xpos,170,(uint8_t *)"Reset Processing..." ,MAIN_FRAME_COL,WHITE);

	TFT_String_align(0,320,170,(uint8_t *)"Reset Processing..." ,0,MAIN_FRAME_COL,WHITE);



}


void FR_and_Elapsed_data()
{
	 MOT.flowrate=00;
	 dose.flow_rate=00;
	 MOT.time=00;
	 MOT.volume=00;
	 INFUSED.ml=00;
	 dose.pat_weight=00;
	 dose.conc_value=00;
	 dose.drug_select_no=00;
}

void VTBI_clear_data(void)
{
	 MOT.time=00;
	 MOT.volume=00;
	 warning_flag[1]=0;
}

//#include <stdio.h>
//#include "board.h"
//#include "peripherals.h"
//#include "pin_mux.h"
//#include "clock_config.h"
#include "LPC55S16.h"
#include "Color.h"
#include "Driver_SPI.h"
#include <TFT_Commands.h>
#include <Shapes.h>
#include "Driver_ADC.h"
#include "Font.h"
#include "TFT_String.h"
#include "Bolus_Header.h"
#include "Dosage_mode.h"
#include "Keypad.h"
#include "Driver_Timer.h"
#include <FR_CALC.h>
#include "Main_screen.h"
#include "Drug_List.h"
#include "Brand.h"
#include "Boot_up.h"
#include "Driver_I2C.h"
#include "Power_off.h"



uint8_t temporary_variable=2;
uint8_t frequent_variable=5;
uint8_t prev_data_flag=0;
uint8_t ON_Flag=0;	//21-03-2024

uint16_t power_key_values=0;

extern uint8_t G_infusion_modes;
extern uint8_t G_infusion_mode_opt;
extern uint8_t G_mode_switch_flag;
extern uint8_t G_drug_list;
extern uint8_t total_brand;
extern uint8_t G_Long_press_back;
extern uint8_t G_mode_sw_flag;
extern uint8_t power_key_delay;
uint16_t length_l[7]={0,330,380,510,630,0,750}; //Syringe Length

extern uint8_t G_mode_power_flag;
extern uint16_t total_drugs;
extern uint8_t G_Brand_back_flag;
extern void BOARD_BootClockPLL150M(void);
extern uint32_t DAC__datawrite(uint16_t addrs1,float voltage, uint16_t bytes_val);

extern uint8_t infusion_mode_screen(uint8_t id);
extern void infuse_clr();

extern char Drug_Names[150][4][20];
extern char Brand_Names[6][4][15];//22-03
void loading_data(void);
/**/
//uint32_t Target_val_disp[3]={MOT.flowrate,MOT.volume,MOT.time};

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
/*
 * @brief   Application entry point.
 */
int main(void)
{
	//  uint8_t *lnf_sw_txt[3]={"Switch to FR Mode","Switch to VTBI Mode","Switch to Dosage Mode"};
		char *lnf_sw_txt[3]={"Switch to FR Mode","Switch to VTBI Mode","Switch to Dosage Mode"};

		uint8_t xpos=0;
		uint8_t exit_flag=1;
		uint8_t option_selection_no=0;
		uint16_t loop_count=0;
		uint8_t flag=0;
		uint32_t ac_val=0;
		G_Brand_back_flag=1;

		uint32_t Target_val_disp[3]={MOT.flowrate,MOT.volume,flag,MOT.time};

		/* Init board hardware. */

		BOL.flowrate=1000;
		BOL.bolus_limit=1000;

		dose.drug_con=1;
		dose.drug_con_ml=1;
		dose.pat_weight=6000;

		BOARD_BootClockPLL150M();
		IOCON->PIO[1][4]|=0X100;       		//LED Back Light
		GPIO->DIR[1]|=1<<4;
		GPIO->CLR[1]|=1<<4;
		Boot_up();
		Rectangle(0,0,320,240,RED);
		Home_screen_functionality(0);

}
//		while(temporary_variable)		//21-03-2024
//		{
//
//			 if(GPIO->PIN[1] & (1<<8))
//			 {
//				 ON_Flag=0;
//			 }
//
//			 else
//			 {
//				 ON_Flag=1;
//				 SUPPLY_TRIGGER_ON;
//				 delay_ms(100);
//			 }
//			 temporary_variable--;
//
//		}
//
//		loading_data();
//
//
//
//		while(1)
//		{
//
//		 if(ON_Flag==1)
//		 {
//			 if(G_mode_sw_flag!=1)
//			 {
//				   self_test_process();
//
//			 }
//			 option_selection_no=0;
//			 if(prev_data_flag)
//			 {
//				 option_selection_no=3;
//			 }
//
//			 else
//			 {
//				 option_selection_no=0;
//			 }
//
//		 while(ON_Flag)//home_flag<3)
//		 {
//
//
//
//			 switch(option_selection_no)
//			 {
//
//				 case 0:
//
//					 option_selection_no=Brand_List(0);
//
//					 break;
//
//				 case 1:
//
//					 if((G_drug_list) && (!prev_data_flag))
//					 {
//						 option_selection_no=Drug_List();	//Dosage_screen();
//
//					 }
//
//					 else
//					 {
//						 option_selection_no++;
//					 }
//					 break;
//
//				 case 2:
//					 if((G_infusion_mode_opt==3)&&(!prev_data_flag) &&  (G_infusion_modes>2))	//	 &&  G_infusion_modes>2 ))//||(1))
//					 {
//						 option_selection_no=infusion_mode_screen(0);
//
//
//
//						 if(G_Long_press_back==1)
//						 {
//							 option_selection_no=1;
//							 G_mode_sw_flag=0;
//							 G_Long_press_back=0;
//						 }
//
//						 if(option_selection_no!=1)
//						 {
//							 option_selection_no=3;
//						 }
//
//						 else
//						 {
//							 if( (G_drug_list) && (!G_Long_press_back) )
//							 {
//								 option_selection_no = 1;
//							 }
//
//							 else
//							 {
//								 option_selection_no = 0;
//							 }
//						 }
//
//					 }
//
//					 else
//					 {
//						 option_selection_no=3;
//					 }
//
//					 break;
//
//				 case 3:
//
//
//
//					 if(G_mode_sw_flag!=1)
//					 {
//						option_selection_no=Home_screen_functionality(G_infusion_modes);	//26-03-2024
//
//						if((!option_selection_no) && (!G_mode_power_flag))
//						{
//							G_mode_switch_flag=1;
//							G_mode_power_flag=0;
//						}
//
//					 }
//
//					 else
//					 {
//						 option_selection_no=1;
//					 }
////
////						 Font_Select(ARIAL_14);
////						 TFT_Number(200,70,G_mode_switch_flag,YELLOW,RED);
////						 TFT_Number(200,90,option_selection_no,YELLOW,RED);
//
//						// delay_secs(2);
//
//					 	 if(G_mode_switch_flag)
//				 	 	 {
//				 		    infuse_clr();                           //After switching to one mode to clear the infusion data
//				 		    CLRSCR(MAIN_FRAME_COL);
//							Font_Select(ARIAL_14);
//
//							Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Switching Mode");
//							Frame_Footer_NC(NEW_FTR_COL,HDR_TXT_COL,(uint8_t *)"Please wait");
//							Font_Select(ARIAL_14);
//							xpos=Letters_Alignments(0,
//									320, (uint8_t*)lnf_sw_txt[G_infusion_modes],0);
//							TFT_String(xpos,170,(uint8_t *)lnf_sw_txt[G_infusion_modes],MAIN_FRAME_COL,WHITE);
//
//							for(loop_count=0;loop_count<=140;loop_count++)
//							{
//								Rectangle(20+(loop_count*2),120,0,30,WHITE);
//								delay_us(20);
//							}
//								VTBI_clear_data();
//								option_selection_no=2;
//								G_mode_sw_flag=0;
//								ON_Flag=1;
//				 	 	 }
//
//					 	 else if(option_selection_no==2)
//					 	 {
//					 		G_mode_switch_flag = 1;
//					 	 }
//					 	 else if(option_selection_no==3)
//					 	 {
//					 		option_selection_no=2;
//					 	 }
////					 	 else if(option_selection_no==0)
////					 	 {
////					 		option_selection_no=3;
////						 	G_mode_switch_flag = 1;
////					 	 }
//
//					 	 break;
//			 }
//	 	 frequent_variable = 30;	//21-03-2024
//
//		 }
//	 }
//
//
//	else	//21-03-2024
//	 {
//		 while(frequent_variable)	//21-03-2024
//		 {
//			 power_key_values=ADC_read(ADC_CH_POWER_KEY);
//			 frequent_variable--;
//		 }
//
////		 if(!power_key_delay)
////		 {
//		//	 power_key_delay=1;
//			 power_key_values=ADC_read(ADC_CH_POWER_KEY);
//	//   }
//
//	 	 if(power_key_values>700)   //FOR DEBUG TEST
//		 {
//			SUPPLY_TRIGGER_ON;
//			ON_Flag=1;
//			power_key_values=0;
//			G_mode_power_flag=0;
//
//		 }
//	 }
//
//	 }
//			 return 0;
//	}

	//***************************WRITE_NUMBER-ARIAL******************************************//

	// Font_Select(ARIAL_9);
	// TFT_Number(50,60,PULSE.setclr++,YELLOW,BLACK);

	// Font_Select(ARIAL_14);
	// TFT_Number(0,70,100,YELLOW,RED);

	// Font_Select(ARIAL_20);
	// TFT_Number(100,60,150,YELLOW,BLACK);

	// Font_Select(ARIAL_36);
	// TFT_Number(150,60,250,YELLOW,BLACK);

	//***************
//	/* Init board hardware. */
//
//    uint16_t check_variable=0;
//	  BOARD_InitBootPins();
//    BOARD_InitBootClocks();
//    BOARD_InitBootPeripherals();
//
//	LPADC_Init(ADC_CH_POWER_KEY);
//	SPI5_Init();
//	TFT_ST7789V_init();
//  Rectangle(0,0,320,240,RED);
//  //  TFT_ST7789V_sercch_symbol_24pt(20,30,1,MAIN_FRAME_COL,BLACK);
//    while(1)
//    {
//    	 check_variable=ADC_read(ADC_CH_POWER_KEY);
//    	 Font_Select(ARIAL_14);
//    	 TFT_Number(0,70,check_variable,YELLOW,BLACK);
//
//    	 if(check_variable>1500)
//    	 {
//			Rectangle(0,0,320,240,MAIN_FRAME_COL);
//			ZOOZ_LOGO(75,60,0,MAIN_FRAME_COL,WHITE);
//    	 }
//
//    }

void loading_data(void)
{
	uint16_t loop_count=0;
	char* custom_data2="(+).Add drug";//create a separate function//Neon V
	char* add_data3="(+).Add Brand";

	if(total_brand<=19)		//22-03
	 {
		 for(loop_count=0;loop_count<15;loop_count++)//22-03
		 {
			Brand_Names[total_brand/4][total_brand%4][loop_count]=add_data3[loop_count];
		 }
	 }

	 for(loop_count=0;loop_count<15;loop_count++)//22-03
	 {
		 Drug_Names[total_drugs/4][total_drugs%4][loop_count]=custom_data2[loop_count];
	 }
}


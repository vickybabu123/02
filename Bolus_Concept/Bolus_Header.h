/*
 * Bolus_Header.h
 *
 *  Created on: 21-Sep-2023
 *      Author: Software4
 */
#include "LPC55S16.h"


//#define _MILLISEC 1000

//#define version 0.1  //rampup base code  28-09-2023
//#define version 0.2  //rampup program shorted 28-09-2023
//#define version 0.3  //rampup & rampdowm program in all run & stop (motor) 29-09-2023
//#define version 0.4 // rampup & rampdowm program COMPLETED & SEPERATE FILE & STRUCTURE
/*final code for rampup & rampdowm*/
//#define version 0.5 // rampup & rampdowm  -bug solved
//#define version 0.6  // The rpm limit is 400
//#define version 0.7  //RAMPING ON OFF SWITCH CONTROLL ADDED
//#define version 0.8 //RAMPING BUG IN BOLUS SOLVED-// NOT TO RAMP DOWN WHILE STARTING THE MOTOR
//#define version 0.9   //ramp inc_dec merged && ramp variables name changed
//#define version 1.0  //infused sec-// universal time logic concept
//#define version 1.1 //VARIABLES ARE STRUCTURED & RAMP BUG IDENTIFIED & ramp up solved in bolus to normal run
//#define version 1.2// bolus 3 type for single key in progress
//#define version 1.3 // bolus 3 type for single key completed (auto has to be change in both) --evk destroyed holded
//#define version 1.4 // BOL.infused_ml ADDED IN INFUSED CONCEPT INFUSED VARIABLE REWRITE AFETR INTERFACE
typedef struct
{
	uint8_t  run_mode;
	uint8_t  auto_purg_flag;
	uint32_t flowrate;
	uint16_t target_ml;
	uint16_t infused_ml;
	uint16_t temp_flowrate;
	uint8_t  mode;
	uint32_t bolus_limit;
	uint32_t	two_ml;
	uint32_t	five_ml;
	uint32_t	ten_ml;
	uint32_t	twent_ml;
	uint32_t limit[7];
	//uint16_t max_lmt[7];
} BOLUS;

//#define _RPM 50

extern BOLUS BOL;

void bolus_limit_Opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void bolus_limit_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[7]);
void bolus_limit_Frame(void);
void bolus_limit();
void bolus_limit_layout();


void bolus_frame();
void bolus_fun(void);
void bolus_fr_screen(uint16_t flowrate);
void bolus_run_frame(void);
void purge_frame(void);
void purge_bolus(void);
void bolus_layout(void);
void bolus_frame_Option(uint8_t page,uint8_t starting_count,uint8_t ending_count);
void bolus_popup_frame(void);
uint8_t bolus_popup(void);
void bolus_FR_spliting(uint16_t flowrate,uint32_t color);

void auto_bolus_stop();
void bolus(uint8_t bolus_mode);
void bolus_mode_stop(void);
void bolus_to_normal_run(void);
void bolus_complete_screen(uint8_t screen, uint32_t color);//common_bug  //ZOOZ_1
uint16_t Bolus_Limit_syringe(uint8_t size);








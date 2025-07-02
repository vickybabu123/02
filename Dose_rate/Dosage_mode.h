/*
 * Dosage_mode.h
 *
 *  Created on: Feb 16, 2024
 *      Author: Welcome
 */
#include "LPC55S16.h"
typedef struct
{
	uint32_t pat_weight;
	uint32_t drug_con;
	uint32_t drug_con_ml;
	uint32_t drug_dos;
	//uint16_t pat_height;
	float conc_value;
	float prev_conc_value;
	uint8_t drug_name;
	float flow_rate;
	uint16_t drug_select_no;
}drug_lib;

extern drug_lib  dose;

void drug_unit_Frame(void);
void drug_unit_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void drug_unit_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page);//, const char* array[4][4]);

void dose_unit_parameter_Frame(void);
void dose_unit_cursor(uint8_t prev_option, uint8_t curr_option,  char array[3][13]);
void dose_unit_parameter_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);

uint8_t dose_conc_setting(void);
uint8_t edit_patient_weight(void);
uint8_t dose_conc_setting_ml(void);
uint8_t dose_unit_Screen(void);
uint8_t drug_unit_settings(void);
uint8_t overview_screen(void);

void dosage_range_limit_fun(uint8_t mode,uint16_t current_value);
void dosage_parameter_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void dosage_overview_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[4]);
void dosage_overview_parameter_Frame(void);

float dose_rate_calculation(float pat_weight,float dosage,float conc_val);

uint8_t recently_used_fun(uint16_t drug_no);    //ZOOZ_1
uint8_t dosage_fun(void);
uint8_t pat_weight_fun(void);

//extern void main_screen_frame(uint16_t flowrate1,uint8_t mode);

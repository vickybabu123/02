/*
 * Linear_Header.h
 *
 *  Created on: 18-Dec-2023
 *      Author: Software6
 */

#ifndef LINEAR_HEADER_H_
#define LINEAR_HEADER_H_



#endif /* LINEAR_HEADER_H_ */
#include "LPC55S16.h"
#define   SY_SIZE  50   // ML
#define   SY_LEN   73   //50 ML
#define   ml_pos_adc_50  55672   // ML
#define   ml_pos_adc_0   37574   //50 ML
#define   LIVE_POT_VAL   46623
#define   MINUTE_60  600.0
#define   THREE  0.60

extern uint32_t adcch0;
//uint8_t nr_empty_alarm_flag=0;
//uint8_t syr_end_verify_count=0;
//uint8_t syr_end_flag=0;
extern volatile uint8_t normal_run;


typedef struct //LINEARpOT
{
	uint16_t syr_max_pos[8];
	uint16_t syr_end_pos[8];
	uint16_t adc_value_for_a_Minute_ml;
	uint8_t nr_empty_verify_count;
	uint8_t syr_end_flag;
	uint8_t nr_empty_alarm_flag;
	uint8_t syr_end_verify_count;
	uint8_t near_empty_count;
}LINEAR_POT;

extern LINEAR_POT LIN_POT;

typedef struct // SYR_adc_val
{
    unsigned int start_pos[6];
    unsigned int end_pos[6];
}SYRINGE;

extern SYRINGE SYR;

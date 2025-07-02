/*
 * infused_calculate.h
 *
 *  Created on: 25-Sep-2023
 *      Author: Software4
 */
#include<stdint.h>

#ifndef INFUSED_CALCULATE_H_
#define INFUSED_CALCULATE_H_

typedef struct infused_ml
{
	uint16_t step_count;
	uint32_t stepsper_point_1ml;
	uint16_t ml;
	uint16_t mill_sec;
	uint16_t sec;

}infuse;

extern infuse INFUSED;

typedef struct tim  //ZOOZ_1
{
	uint8_t hour;
    uint8_t minute;
    uint8_t seconds;
} clk;

extern clk time;

void infused_data(uint8_t screen,uint8_t r_mode);		//28-03
void infuse_status(void);
void infused_data(uint8_t screen,uint8_t r_mode);  //28-03
void infuse_clr();
void infuseD_ml(uint32_t pulse_to_one_ml);
void near_to_target();
void Target_ml_clear(void);

#endif /* INFUSED_CALCULATE_H_ */


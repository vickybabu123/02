/*
 * Target_fun.h
 *
 *  Created on: 06-Feb-2024
 *      Author: Software3
 */

#ifndef TARGET_FUN_H_
#define TARGET_FUN_H_

uint8_t VTBI_check(uint8_t v_mode);
uint32_t volume_cal(uint32_t time_value , uint32_t flowrate_value);
uint32_t time_cal(uint32_t flowrate_value , uint32_t volume_value);
uint32_t flowrate_cal(uint32_t time_value , uint32_t volume_value);
void Target_mode_cursor(uint8_t prev_option, uint8_t curr_option);
void Target_mode_opt_Frame(uint8_t start_opt,uint8_t end_opt);
void Target_mode_frame(void);
uint8_t Target_mode_setting(void);


#endif /* TARGET_FUN_H_ */

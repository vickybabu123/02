/*
 * Motor.h
 *
 *  Created on: 04-Mar-2024
 *      Author: Software6
 */

#ifndef MOTOR_H_
#define MOTOR_H_

typedef struct{
	uint8_t motor_on;
	uint8_t Min_cuts;
	uint8_t twenty_cut_count;
	uint8_t Motor_struck;
	uint16_t Min_pulse;
	uint16_t Motor_pulse;
	uint16_t Pulse_count;
	uint16_t Prev_pulse_count;
	uint16_t twenty_cuts_count;  //AL3 concept change(based on pulse)
	uint32_t cuts_time_diff;
	uint32_t cuts_time_diff_cnt;
	float rpm_decode;
}EXT;
extern EXT MFB;
void Motor_struck_alarm(void);
void MFB_check(void);
void run_stop_used_hrs(void);
void MFB_count_reset(uint8_t reset_flag);

#endif /* MOTOR_H_ */

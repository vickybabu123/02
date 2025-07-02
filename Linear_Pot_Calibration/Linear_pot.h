/*
 * Linear_Pot.h
 *
 *  Created on: 08-Jan-2024
 *      Author: Software6
 */

#ifndef LINEAR_POT_H_
#define LINEAR_POT_H_

float syringe_nearempty_calculation(uint16_t flowarte);
void display_funtion();
void motor_stop();
void adc_value_for_induvidual_syringe();
void syringe_end_check(uint16_t plunger_ADC_val);
void near_empty_check(uint16_t plunger_ADC_val);
int remaining_volume_in_syringe();
void syringe_position_check();



#endif /* LINEAR_POT_H_ */

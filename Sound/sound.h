/*
 * sound.h
 *
 *  Created on: 02-Feb-2024
 *      Author: SoftwareRND
 */

#ifndef SOUND_H_
#define SOUND_H_

#define PERIOD 60000

void buzzer_pwm();
void pwm_sta(uint32_t period,uint16_t duty_cycle);
void alarm_sound_tone();
void beep_sound();
void long_beep_sound();
void buzzer_pwm_stop();
void Power_off_beep_sound();


typedef struct alarm
{
	uint32_t period;
	uint8_t on_off;
	uint16_t sound_cnt;
	uint16_t count;

}ALM;

extern ALM alarm_sound;

#endif /* SOUND_H_ */

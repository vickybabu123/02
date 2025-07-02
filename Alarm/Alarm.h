/*
 * Alarm.h
 *
 *  Created on: 27-Nov-2023
 *      Author: Software3
 */

#ifndef ALARM_H_
#define ALARM_H_

#include "stdint.h"

#define OCCL       1
#define PLUNGER    2
#define SIPHONIC   3
#define NOT_ENGAGE 4
#define SYR_END    5
#define MOT_ERR_1  6
#define MOT_ERR_2  7
#define MOT_ERR_3  8
#define MOT_ERR_4  9
#define TARGET   10
#define BATTERY_ALM  11
//#define BATTERY_FULL_1  12

//#define SIPHONIC 12
#define SYR_DIS  14
#define DISC_ERR 15
#define SYR_NOT_ENGAGE 16
#define PRESS_RUN 17
#define CALIBRATION_ERR 18
#define BATTERY_ERR 19

/************Notification Macros**************************/

#define KEY_LOCK        1
#define KEY_UNLOCK      2
#define MAINS_PLUGIN    3
#define MAINS_PLUGOUT   4
#define SET_FLOWRATE    5
#define SET_FLOWRATE_1  6
#define SET_TARGET	    7
#define PUMP_IDLE 		8
#define BATTERY_FULL_1  9
#define SET_FR 			12
#define DEV_IN_USE      13
#define SYRINGE_END        14


void Alarm_screen(uint8_t *alarm_name);
void Alarm(uint8_t alarm_no);
void Warning_screen(uint8_t *Warning_name,uint8_t mode);
void Warning_Scr_Erase();
void caution_info(uint8_t *Warning_name);
void warn_tone(uint8_t warn_dura_sec);
void Notification(uint8_t notif);
void Notif_screen(uint8_t *Notif_name);
void Single_line_fun(void);

#endif /* ALARM_H_ */

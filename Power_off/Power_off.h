/*
 * Power_off.h
 *
 *  Created on: 24-Jan-2024
 *      Author: Software6
 */

#ifndef POWER_OFF_H_
#define POWER_OFF_H_
#define AUTO_EXIT_TIME 200// 2 MINS

void Power_off();

typedef struct
 {
 	uint16_t power_status_flag;
 	uint8_t mains_bat_swt_flag;
 }power_flag;

 typedef struct
 {
	 uint16_t main_power_status_flag;
 }main_flag;

 typedef struct
     {
	 	 uint8_t full:1;
    	 uint8_t critical:1;
    	 uint8_t low:1;
    	 uint8_t mode:1;
    	 uint8_t charge_blink:1;
       	 uint8_t empty:1;
       	 uint8_t percent;
    	 uint8_t pre_lvl;
    	 uint8_t verify_cout;
     }battery;

extern  battery BATT;
extern power_flag POW;
extern main_flag MAIN;
void Power_off();

#define  SUPPLY_TRIGGER_ON		GPIO->CLR[1]|=1<<12
#define  SUPPLY_TRIGGER_OFF		GPIO->SET[1]|=1<<12

#endif /* POWER_OFF_H_ */

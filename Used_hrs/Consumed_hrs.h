/*
 * Used_hrs.h
 *
 *  Created on: 05-Mar-2024
 *      Author: Software6
 */

#ifndef CONSUMED_HRS_H_
#define CONSUMED_HRS_H_

#include "LPC55S16.h"

typedef struct
{
	uint8_t device_sec_cnt;
	uint8_t device_min_cnt;
	uint16_t device_hrs_cnt;

	uint8_t battery_sec_cnt;
    uint8_t battery_min_cnt;
	uint16_t battery_hrs_cnt;

	uint8_t running_sec_cnt;
	uint8_t running_min_cnt;
    uint16_t running_hrs_cnt;

    uint16_t factory_used_hrs;

}Reached;

extern Reached UTILIZED;
void machine_on_used_hrs(void);
void battery_used_hrs(void);
void EEPROM_usedhrs_write(uint8_t default_write);
void EEPROM_usedhrs_read(void);
void reset_fun(uint8_t type_rest);
void usedhrs_status(void);
void VTBI_clear_data(void);


#endif /* CONSUMED_HRS_H_ */

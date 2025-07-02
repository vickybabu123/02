/*
 * factory.h
 *
 *  Created on: 16-Feb-2024
 *      Author: 7303
 */
#include "LPC55S16.h"


typedef struct
{
	uint16_t  manu_month;
	uint16_t  prod_model;
	uint16_t swre_version;
	uint16_t SI_no;
	uint16_t reset;
	uint16_t team;
	uint8_t  used_hrs;
	uint16_t factory[9];

} factorys;



extern factorys FACT;

void used_hrs(void);
void used_hrs_info_frame(void);
void used_hrs_info_Opt_Frame();
//void factory_setting();


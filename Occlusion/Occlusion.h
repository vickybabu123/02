/*
 * Occlusion.h
 *
 *  Created on: 09-Oct-2023
 *      Author: Software3
 */

#ifndef OCCLUSION_H_
#define OCCLUSION_H_

#include <stdio.h>
#include "stdint.h"
#include "fsl_clock.h"
#include "Color.h"
#include "stdint.h"
#include "TFT_Commands.h"
#include "TFT_String.h"

#define SYRINGE_2ML  1
#define SYRINGE_5ML  2
#define SYRINGE_10ML 3
#define SYRINGE_20ML 4
#define SYRINGE_30ML 5
#define SYRINGE_50ML 6


typedef struct{
 uint8_t pre_occl_flag;
  uint16_t  PSI_VALUE;
 uint8_t PSI_level;
 uint16_t Zero_PSI;
 uint16_t strain_20PSI_value[7];
 uint16_t pressure_adc_diff;
 uint16_t mmHg_level;
 uint16_t kPa_level;
 float dynamic_ratio;

}Occlusion;

extern Occlusion Occl;

extern uint16_t strain_20PSI_val[7];

void ADC_to_PSI_conversion(void);
void Occlusion_Status(void);
extern uint16_t Pressure_ADC(void);

#endif /* OCCLUSION_H_ */

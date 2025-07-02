#include "fsl_power.h"

#ifndef DRIVER_ADC_H_
#define DRIVER_ADC_H_



#define ADC_CH_POWER_KEY	2
#define ADC_CH_MAINS		4
#define ADC_CH_SD_POT		8
#define ADC_CH_BATTERY		11
#define ADC_CH_PLUNGER_POT	12

#define SEC_DELAY       500
#define POWER_KEY_SAMPLING 2000


void LPADC_Init(uint8_t ADC_no);
void ADC_cmd_config(uint32_t commandId);
void ADC_trig_config(uint32_t triggerId);
void ADC_SW_trig(uint8_t trig);
void CLOCK_SetDiv(clock_div_name_t div_name, uint32_t divided_by_value, bool reset);
uint16_t ADC_read(uint8_t adc_input);
uint16_t ADC_conv(uint8_t index);

typedef struct sampling{
	uint16_t Result;
}analog;

extern analog  ADC;
#endif /* DRIVER_ADC_H_ */

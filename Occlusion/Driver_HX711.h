#include "LPC55S16.h"



//#define GAUGE_TOTAL_PULSES		25
//#define NUMBER_OF_TRANSITION	2

#define HX711_GAIN			25
#define CLK_TRANSITION		2

uint16_t strain_data_read();
void HX711_handler(void);


//#define LOAD_CLK   (1<<13)
//#define LOAD_DATA  (1<<14)
//
//#define LOAD_SET    GPIO->SET[0]|=(1<<13)
//#define LOAD_CLR    GPIO->CLR[0]|=(1<<13)


#define HX711_CLK_SET	GPIO->SET[0]|=(1<<13)
#define HX711_CLK_CLR	GPIO->CLR[0]|=(1<<13)

#define HX711_DAT_PIN	((GPIO->PIN[0])&=(1<<14))


typedef struct
{

	uint8_t conv_flag:1;
	uint8_t reset_flag:1;
	uint8_t clk_flag:1;
	uint8_t clock_transition;
	uint8_t clk_Count;
	uint8_t data[24];
	uint8_t reset_time;



}LOC;

extern LOC HX711;



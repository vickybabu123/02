#include "stdint.h"

#ifndef TFT_COMMANDS_H_
#define TFT_COMMANDS_H_

#define GLCD_BACK_LIGHT_ON   	 GPIO->B[1][4]=1         // GPIO->B[0][14] = 1;     // FSTN ON
#define GLCD_BACK_LIGHT_OFF   	 GPIO->B[1][4]=0         // GPIO->B[0][14] = 0;     // FSTN OFF

#define RES_ENABLE	   	     	 GPIO->B[1][10] =1       // GPIO->B[0][13] = 1      // HIGH
#define RES_DISABLE	          	 GPIO->B[1][10] =0 	     // GPIO->B[0][13] = 0	    // LOW

#define A0_COMMAND	    	     GPIO->B[1][3] =0	     // GPIO->B[1][0] = 0	      //GPIO->B[0][12] = 0      // LOW
#define A0_DATA               	 GPIO->B[1][3] =1        // GPIO->B[1][0] =1

#define ARIAL_9  	1
#define ARIAL_12	2
#define ARIAL_14	3
#define ARIAL_20    4
#define ARIAL_36    5

#define CALIBRI_35	6
#define CALIBRI_43	7
#define CALIBRI_45	8
#define CALIBRI_48	9

#define _16_BIT		15
#define _8_BIT		7

#define CALIB_EDT_YPOS 103

void TFT_ST7789V_init(void);
void TFT_ST7789V_BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend) ;
//void SPI_transfer(uint32_t txvalue,uint8_t length);


void SPI_cmd(uint8_t value,uint8_t length);
void SPI_data(uint8_t value,uint8_t length);
void delay_us(unsigned int data);
void delay(unsigned int data);

#endif /* TFT_COMMANDS_H_ */



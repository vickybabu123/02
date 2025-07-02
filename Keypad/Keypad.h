
#include "LPC55S16.h"
#ifndef KEYPAD_H_
#define KEYPAD_H_



#define Column1  1<<24
#define Column2  1<<25
#define Column3  1<<26
#define Column4  1<<27

#define Row1 1<<20
#define Row2 1<<21
#define Row3 1<<22

#define KEY_SC_PIN  GPIO->PIN[0]
#define KEY_PORT_SCAN 	GPIO->PIN[0]&0XF700000


//********************************NEON_S KEYPAD_VALUES***********************//

#define OK_KEY           	 190840832
#define LEFT_KEY         	 240123904
#define RIGHT_KEY	     	 223346688
#define UP_KEY		    	 241172480
#define DOWN_KEY	     	 224395264
#define MENU_KEY         	 238026752
#define BACK_KEY         	 221249536
#define MUTE_KEY         	 123731968
#define BOLUS_KEY	     	 187695104
#define START_STOP_KEY   	 189792256
#define PURGE_START_STOP_KEY 185597952

#define _150MHZ_CPU_FREQ_ 150000000

void Keypad_Init();
void keypad_function();




typedef struct
{
	uint8_t  on_flag;
	uint8_t  count1;//KEY FLAG
	uint8_t  count2;//KEY PRESSED FLAG

	uint16_t counter;

	uint32_t scan; // KEY_SCAN
	volatile uint32_t value;//KEY.value
//	uint32_t prev_scan;
}Keys;



extern Keys KEY;

//**************************************************************************//
//#define LEFT_KEY    	   	    	 3670054
//#define RIGHT_KEY             	 3671046
//#define DOWN              	     3671074		//2 CROSS 2
//#define UP            		     3671076


//#define LEFT_KEY    	   	     	 240123904
//#define RIGHT_KEY             	 123731968
//#define DOWN              		 224395264		//3671074//2 CROSS 2
//#define UP            			 241172480




//#define OK_KEY            		 190840832
//#define BOLUS_KEY         		 3277830
//#define START_STOP_KEY 			 3277858//2 CROSS 2
//#define MENU_CHANGE				 3277860//2 CROSS 2


//
//#define OK_KEY                     3276838
//#define BOLUS_KEY            	     3277830
//#define START_STOP_KEY	     	 3277858//2 CROSS 2
//#define MENU_CHANGE		         3277860//2 CROSS 2

//#define MENU_CHANGE_1				 2752550
//#define S10 						 2753542
//#define S11						 2753570
//#define S12 						 2753572
//
//#define S13                        1703974
//#define S14                        1704966
//#define S15                        1704994
//#define S16                        1704996
//*****************************************************************************//
							// 4*3 Dotted Keypad_p1_23(Row 3)
//#define S1						 245366784
//#define S2						 228589568
//#define S3						 195035136
//#define S4						 127926272
//
//
//#define S5					     244318208
//#define S6						 227540992
//#define S7						 193986560
//#define S8						 126877696
//
//#define S9						 238026752
//#define S10				   		 219152384
//#define S11						 187695104
//#define S12						 120586240
//*************************************************************************//
                              //IX3 Board Keypad(Default keypad pins for IX3 board)

//#define MENU								103809024//38797312
//#define ADULT_MICRO				22020096
//#define TARGET							36700160
//#define SET									190840832//39845888
//
//#define RUN_STOP					189792256//23068672
//#define DROP_ML						19922944

//**************************************************************************//
                                 //Main Keypad in the 3D Protocol

//#define UP_KEY  106954752
//#define DOWN_KEY  901775362
//#define RIGHT_KEY 891289602
//#define LEFT_KEY 105906176
//#define OK_KEY 190840832


#endif /* KEYPAD_H_ */

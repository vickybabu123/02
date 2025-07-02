/*
 * DETECT.h
 *
 *  Created on: 17-Oct-2023
 *      Author: SoftwareRND
 */

#ifndef SD_CALIB_H_
#define SD_CALIB_H_
#define BASEVAL_MIN		0			//ver 7.52 - 18/5/17
#define BASEVAL_MAX		580
#define MAX_LIMIT       3
#define MIN_LIMIT       0
//#define DOSAGE_KEY      	230144
//#define RUNDELAYTIMER			60
//#define SET_KEY         	181504
//#define MODEWAITTIME    1200    /* 2 Min */
//#define	SYRINGE_DETECT	4

#define SYRINGE_2_SYRINGE_DIFF		100 //200/*150*/ changed 2ml detection issue.
#define SYRINGE_5_SYRINGE_DIFF		150
#define SYRINGE_10_SYRINGE_DIFF		150
#define SYRINGE_20_SYRINGE_DIFF		150
#define SYRINGE_30_SYRINGE_DIFF		150
#define SYRINGE_50_SYRINGE_DIFF		150

#define _2ML_				1
#define _5ML_				2
#define _10ML_			    3
#define _20ML_		     	4
#define _30ML_		    	5
#define _50ML_		    	6
#define _FOUT_			    7


#define SYRINGE2ML     1
#define SYRINGE5ML     2
#define SYRINGE10ML    3
#define SYRINGE20ML    4
#define SYRINGE30ML    5
#define SYRINGE50ML    6

#define		DISPOVAN_SD_2ML_MIN			641//640//150 	//961
#define		DISPOVAN_SD_5ML_MIN			892//880   //310 	//961
#define		DISPOVAN_SD_10ML_MIN	    1152      //	790 	//1341
#define		DISPOVAN_SD_20ML_MIN		1457          //1255 	//1841
#define		DISPOVAN_SD_30ML_MIN		1943// 2007 	//2426
#define		DISPOVAN_SD_50ML_MIN		2332 	//3081

#define		DISPOVAN_SD_2ML_MAX			881//309 	//1340
#define		DISPOVAN_SD_5ML_MAX			1161//789 	//1340
#define		DISPOVAN_SD_10ML_MAX		1461//1254 	//1840
#define		DISPOVAN_SD_20ML_MAX		1825//2006 	//2425
#define		DISPOVAN_SD_30ML_MAX		2142//2331 	//3080
#define		DISPOVAN_SD_50ML_MAX		3000 	//3725

#define		DISPOVAN_SD_2ML_DEFAULT_	   735
#define		DISPOVAN_SD_5ML_DEFAULT_	   1060
#define		DISPOVAN_SD_10ML_DEFAULT_	   1270
#define		DISPOVAN_SD_20ML_DEFAULT_	   1650
#define		DISPOVAN_SD_30ML_DEFAULT_	   2040
#define		DISPOVAN_SD_50ML_DEFAULT_	   2455
#define     DISPOVAN_SD_FOUT_MIN_DEFAULT_  2685
#define	    FULL_OUT_MAX                   3080


extern unsigned int battery_critic;
extern unsigned int minval1,minval2,minval3,minval4,minval5,minval6,minval7;
uint8_t detect_syringe_size(unsigned int sybrand);
void pull_in_frame();
void pullin_popup();
void calibrate_popup();
void SD_layout();
uint8_t syr_place_screen(uint8_t* s_size1);
void min_max_val_header_footer();
void syringe_adc_val(uint8_t *syringe_size);
uint8_t pop_up_screen(void);
uint8_t pop_up_erase();
void syringe_selection_screen(void);
void frames_syringe_option(uint8_t page,uint8_t starting_count,uint8_t ending_count);
void sd_cursor_sel(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[2][4]);
void calibrate_popup_erase();
void minval_adc_option_screen(uint8_t page,uint8_t starting_count,uint8_t ending_count);

void EEPROM_SD_READ(void);
void pull_out_frame();
void pull_out_popup();

#endif /* SD_CALIB_H_ */



// /*
// * DETECT.h
// *
// *  Created on: 17-Oct-2023
// *      Author: SoftwareRND
// */
//
//#ifndef SD_CALIB_H_
//#define SD_CALIB_H_
//#define BASEVAL_MIN		0			//ver 7.52 - 18/5/17
//#define BASEVAL_MAX		555
//#define MAX_LIMIT       3
//#define MIN_LIMIT       0
////#define DOSAGE_KEY      	230144
////#define RUNDELAYTIMER			60
////#define SET_KEY         	181504
////#define MODEWAITTIME    1200    /* 2 Min */
////#define	SYRINGE_DETECT	4
//
//#define SYRINGE_2_SYRINGE_DIFF		100 //200/*150*/ changed 2ml detection issue.
//#define SYRINGE_5_SYRINGE_DIFF		150
//#define SYRINGE_10_SYRINGE_DIFF		150
//#define SYRINGE_20_SYRINGE_DIFF		150
//#define SYRINGE_30_SYRINGE_DIFF		150
//#define SYRINGE_50_SYRINGE_DIFF		150
//
//#define _2ML_				1
//#define _5ML_				2
//#define _10ML_			    3
//#define _20ML_		     	4
//#define _30ML_		    	5
//#define _50ML_		    	6
//#define _FOUT_			    7
//
//
//#define SYRINGE2ML     1
//#define SYRINGE5ML     2
//#define SYRINGE10ML    3
//#define SYRINGE20ML    4
//#define SYRINGE30ML    5
//#define SYRINGE50ML    6
//
//#define		DISPOVAN_SD_2ML_MIN			641//640//150 	//961
//#define		DISPOVAN_SD_5ML_MIN			892//880   //310 	//961
//#define		DISPOVAN_SD_10ML_MIN	    1152      //	790 	//1341
//#define		DISPOVAN_SD_20ML_MIN		1457          //1255 	//1841
//#define		DISPOVAN_SD_30ML_MIN		1943// 2007 	//2426
//#define		DISPOVAN_SD_50ML_MIN		2332 	//3081
//
//#define		DISPOVAN_SD_2ML_MAX			881//309 	//1340
//#define		DISPOVAN_SD_5ML_MAX			1161//789 	//1340
//#define		DISPOVAN_SD_10ML_MAX		1461//1254 	//1840
//#define		DISPOVAN_SD_20ML_MAX		1825//2006 	//2425
//#define		DISPOVAN_SD_30ML_MAX		2142//2331 	//3080
//#define		DISPOVAN_SD_50ML_MAX		3000 	//3725
//
//#define		DISPOVAN_SD_2ML_DEFAULT_	   735
//#define		DISPOVAN_SD_5ML_DEFAULT_	   1060
//#define		DISPOVAN_SD_10ML_DEFAULT_	   1270
//#define		DISPOVAN_SD_20ML_DEFAULT_	   1650
//#define		DISPOVAN_SD_30ML_DEFAULT_	   2040
//#define		DISPOVAN_SD_50ML_DEFAULT_	   2455
//#define     DISPOVAN_SD_FOUT_MIN_DEFAULT_  2685
//#define	    FULL_OUT_MAX                   3080
//
//
//extern unsigned int battery_critic;
//extern unsigned int minval1,minval2,minval3,minval4,minval5,minval6,minval7;
//
//#endif /* SD_CALIB_H_ */
//

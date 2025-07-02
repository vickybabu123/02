#ifndef DRIVER_I2C_H_
#define DRIVER_I2C_H_
#include <stdio.h>
#include "stdint.h"
#include "Header.h"

#ifndef NULL
#define NULL 0
#endif

#define I2SCHL 75
#define I2SCLL 75

#define I2C_PINSEL            LPC_PINCON->PINSEL1

#define I2C_FUNCMASK          0X03C00000
#define I2C_FUNCBIT           0X01400000

//    24c512 SETTINGS   //

#define M24C512_ADDR        0
#define DATA_ADDR           0

//    I2C CONTROL CLEAR FLAG    //

#define I2C_FLAG_AAC         (1<<2)
#define I2C_FLAG_SIC         (1<<3)
#define I2C_FLAG_STAC        (1<<5)
#define I2_FLAGC_I2ENC       (1<<6)

//    I2C CONTROL SET FLAG    //

#define  I2C_FLAG_AA        (1<<2)
#define  I2C_FLAG_SI        (1<<3)
#define  I2C_FLAG_STO       (1<<4)
#define  I2C_FLAG_STA       (1<<5)
#define  I2C_FLAG_I2EN      (1<<6)

//---- I2C Speed
#define  I2C_SPEED_100   0
#define  I2C_SPEED_400   1

//--- Errors

#define  I2C_NO_ERR                    0
#define  I2C_ERR_NO_RESPONSE           1
#define  I2C_ERR_WRONG_PARAM           2
#define  I2C_ERR_24XX_WR_TIMEOUT       3
#define  I2C_ERR_24XX_BAD_ADDR         4
#define  I2C_ERR_24XX_BAD_TYPE         5
#define  I2C_ERR_24XX_BAD_PAGESIZE     6
#define  I2C_ERR_24XX_WRONG_NUM        7
#define  I2C_ERR_LM75_WRONG_REGISTER   8
#define  SLAVE_ADDRESS_EEPROM    0XA8        //EEPROM new address changed A2,A1,A0-> 1,0,0.
                                                   //New mother boart correction.
                                                        

//--- EEPROM 24xx write timeout ( > 5 mS)

#define  I2C_WR_24XX_TIMEOUT     10000



void i2c_Init(uint16_t mode);
uint32_t EEPROM_datawrite(uint16_t addrs, uint32_t data, uint16_t bytes_val);
uint32_t EEPROM_dataread(uint16_t addrs, uint16_t byte_val);

/**************************previous data parameters************************************/
#define EEPROM_SOFTWARE_VERSION			VERSION                           //2 Byte

//**********************************Menu_Setting***************************************

#define EEPROM_G_bolus_mode				EEPROM_SOFTWARE_VERSION 	+2   /* 1 byte*/
#define EEPROM_G_bol_fr					EEPROM_G_bolus_mode  		+1   /* 2 byte*/
#define EEPROM_G_bol_limit				EEPROM_G_bol_fr      		+2   /*2*6=12 byte*/
#define EEPROM_G_occl_unit				EEPROM_G_bol_limit   		+12  /* 1 byte*/
#define EEPROM_G_occl_level				EEPROM_G_occl_unit   		+1   /* 1 byte*/
#define EEPROM_BRAND_NO					EEPROM_G_occl_level 		+1	 /*1 byte*/
#define EEPROM_G_drug_list				EEPROM_BRAND_NO 			+1 	 /*1 BYTE*/
#define EEPROM_CUSTOM_DRUG_LIST  		EEPROM_G_drug_list 			+1 	 /* 2 bytes*/
#define EEPROM_FAV_DRUG_LIST     		EEPROM_CUSTOM_DRUG_LIST 	+2 	 /* 10*2= 20 bytes*///29-03
#define EEPROM_TOTAL_FAV        		EEPROM_FAV_DRUG_LIST 		+20  /*1 byte*/
#define EEPROM_TOTAL_RECENT      		EEPROM_TOTAL_FAV 			+1 	 /*1 byte*///29-03
#define EEPROM_RECENT_DRUG_LIST  		EEPROM_TOTAL_RECENT 		+1 	 /*10*2=20 bytes*/
#define EEPROM_G_kvo           			EEPROM_RECENT_DRUG_LIST    	+20  /* 2*6 byte*/
#define EEPROM_G_KVO_fr        			EEPROM_G_kvo         		+12  /* 2 byte*/
#define EEPROM_G_infusion_modes 		EEPROM_G_KVO_fr 			+2   /*1 BYTE*/


//******************************System_Setting*************************************//
//#define EEPROM_SD_LOADED_ADC_VAL  	EEPROM_G_infusion_modes 	+1   /*12 byte*/ //each syringe has adc val of 2 byte this array having 6 elements so 6*2=12
//#define EEPROM_DISPO_MIN_VAL1    		EEPROM_SD_LOADED_ADC_VAL 	+12  /*12 byte*/ //each syringe has adc val of 2 byte this array having 6 elements so 6*2=12
#define EEPROM_SD_BASE_VAL				EEPROM_G_infusion_modes			+1	 /*2 byte*/
#define EEPROM_SD_PULL_OUT				EEPROM_SD_BASE_VAL				+2	 /*2 byte*/
#define EEPROM_BRAND1_2ML_SYR_ADC		EEPROM_SD_PULL_OUT  			+2 	 /*12*20=240byte*/ //2 byte for 20 brand (ALL SYRINGE ml)
#define EEPROM_BRAND1_2ML_SYR_MIN_ADC	EEPROM_BRAND1_2ML_SYR_ADC		+240 /*12*20=240byte*/ //2 byte for 20 brand (ALL SYRINGE ml)
#define EEPROM_SL_PULL_OUT				EEPROM_BRAND1_2ML_SYR_MIN_ADC	+240 /*2 byte*/
#define EEPROM_SL_PULL_IN				EEPROM_SL_PULL_OUT				+2	 /*2 byte*/
#define EEPROM_SL_LEN_VAL				EEPROM_SL_PULL_IN  	    		+2 	 /*12*20*=240 byte*/ //12 byte for 20 brand (all ml)
#define EEPROM_SL_COL_VAL				EEPROM_SL_LEN_VAL  	    		+240 /*12*20*=240 byte*/ //12 byte for 20 brand (all ml)
#define EEPROM_Occl_strain_0PSI_value  	EEPROM_SL_COL_VAL 				+240 /*2 byte */
#define EEPROM_Occl_strain_20PSI_value  EEPROM_Occl_strain_0PSI_value 	+2 /* 20s.brand*6s.sisz*2 -240 BYTE*/
#define EEPROM_LOAD_CELL_VAL     		EEPROM_Occl_strain_20PSI_value 	+240 /* 2 BYTE*/

#define EEPROM_G_bright_level   		EEPROM_LOAD_CELL_VAL      		+2 /*1 byte*/
#define EEPROM_G_sound_level    		EEPROM_G_bright_level			+1 	/*1 byte*/
#define EEPROM_G_date_mnth      		EEPROM_G_sound_level 			+1 	/*2 byte*/
#define EEPROM_G_year           		EEPROM_G_date_mnth 				+2 	/*2 byte*/
#define EEPROM_G_time           		EEPROM_G_year      				+2	/*2 byte*/
#define EEPROM_G_time_format    		EEPROM_G_time      				+2 	/*2 byte*/
#define EEPROM_G_lock_time      		EEPROM_G_time_format 			+2 	/*1 BYTE*/
#define EEPROM_LAST_IFMODE           	EEPROM_G_lock_time         		+1  /* 1 byte*/
#define EEPROM_LAST_DATA				EEPROM_LAST_IFMODE				+1	/* 1 byte*/
#define EEPROM_SCREEN_SAVER				EEPROM_LAST_DATA				+1	/* 1 byte*/
#define EEPROM_MFG_MON_YEAR     		EEPROM_SCREEN_SAVER    			+1  /* 2 BYTE*/
#define EEPROM_SERIAL_NO        		EEPROM_MFG_MON_YEAR 			+2 	/* 3 BYTE*/

#define EEPROM_QC_TRACK         		EEPROM_SERIAL_NO    			+3 		/*1 BYTE*/
#define EEPROM_DEVICE_SEC				EEPROM_QC_TRACK					+1		/*1 byte*/
#define EEPROM_DEVICE_MIN				EEPROM_DEVICE_SEC				+1		/*1 byte*/
#define EEPROM_DEVICE_HRS				EEPROM_DEVICE_MIN				+1		/*2 byte*/
#define EEPROM_BATTERY_SEC				EEPROM_DEVICE_HRS				+2		/*1 byte*/
#define EEPROM_BATTERY_MIN				EEPROM_BATTERY_SEC				+1		/*1 byte*/
#define EEPROM_BATTERY_HRS				EEPROM_BATTERY_MIN				+1		/*2 byte*/
#define EEPROM_RUNNING_SEC				EEPROM_BATTERY_HRS				+2		/*1 byte*/
#define EEPROM_RUNNING_MIN				EEPROM_RUNNING_SEC				+1		/*1 byte*/
#define EEPROM_RUNNING_HRS				EEPROM_RUNNING_MIN				+1		/*2 byte*/
#define EEPROM_FACTORY_HRS				EEPROM_RUNNING_HRS				+2		/*2 byte*/
#define EEPROM_FACTORY_RST				EEPROM_FACTORY_HRS				+2		/*1 byte*/

//*************************************************************************//

//******************************Events*************************************//

#define EEPROM_TOTAL_EVENTS     		EEPROM_FACTORY_RST 				+1  	/*2 byte*/
#define EEPROM_EVT_DATE    				EEPROM_TOTAL_EVENTS 			+2    	/*1000*1byte=1000*/
#define EEPROM_EVT_MONTH				EEPROM_EVT_DATE					+1000 	/*1000*1byte=1000*/
#define EEPROM_EVT_YEAR					EEPROM_EVT_MONTH				+1000 	/*1000*2byte=2000*/
#define EEPROM_EVT_HOUR					EEPROM_EVT_YEAR					+2000 	/*1000*1byte=1000*/
#define EEPROM_EVT_MIN					EEPROM_EVT_HOUR					+1000 	/*1000*1byte=1000*/
#define EEPROM_EVT_ID					EEPROM_EVT_MIN					+1000 	/*1000*1byte=1000*/

//*************************************************************************//
							/*FLOW RATE MODE */
#define EEPROM_PD_FRFLOWRATE         EEPROM_EVT_ID     		+1000	/* 4 byte*/
#define EEPROM_PD_FRVOLUME           EEPROM_PD_FRFLOWRATE   +4	    /* 4 byte*/
#define EEPROM_PD_FRINFUSED_ml    	 EEPROM_PD_FRVOLUME     +4		/* 2 byte*/
#define EEPROM_PD_FRINFUSED_SEC		 EEPROM_PD_FRINFUSED_ml	+2      /* 2 byte*/

							/*DOSE RATE MODE */
#define EEPROM_PD_DRDRUG_SELECT     EEPROM_PD_FRINFUSED_SEC +2 		/* 2 byte*/
#define EEPROM_PD_DRCONC_VALUE      EEPROM_PD_DRDRUG_SELECT +2      /* 4 byte*/
#define EEPROM_PD_DRPAT_WEIGHT      EEPROM_PD_DRCONC_VALUE  +4      /* 4 byte*/
#define EEPROM_PD_DRDRUG_DOS    	EEPROM_PD_DRPAT_WEIGHT  +4      /* 4 byte*/
#define EEPROM_PD_DRrate_unit       EEPROM_PD_DRDRUG_DOS   	+4    	/* 1 byte*/
#define EEPROM_PD_DRdisp_para       EEPROM_PD_DRrate_unit    +1     /* 10 byte*/
#define EEPROM_Drug_unit            EEPROM_PD_DRdisp_para	+10     /* 1 byte*/


/**************************************************************************************/

//#define EEPROM_MFG_MON_YEAR     EEPROM_Drug_unit    +2 	/* 2BYTE*/
//#define EEPROM_SERIAL_NO        EEPROM_Drug_unit 	+1 		/* 3 BYTE*/
//#define EEPROM_QC_TRACK         EEPROM_SERIAL_NO    +3 		/*2 BYTE*/
#define	EEPROM_TOTAL_BRAND		EEPROM_Drug_unit	+1 		// 3 byte
#define	EEPROM_TOTAL_DRUG 		EEPROM_TOTAL_BRAND	+3 		// 1 byte
#define	EEPROM_BRAND_NAMES		EEPROM_TOTAL_DRUG 	+1 		// 180 byte
#define	EEPROM_DRUG_NAMES		EEPROM_BRAND_NAMES	+180	// 320 byte//22-03

//////////////////////////////////////////////////////////////

//#define EEPROM_Occl_strain_0PSI_value  	EEPROM_DRUG_NAMES + 320 /* 2 BYTE*/
//#define EEPROM_Occl_strain_20PSI_value  EEPROM_Occl_strain_0PSI_value + 2 /* 3 BYTE*/
//#define EEPROM_LOAD_CELL_VAL     		EEPROM_Occl_strain_20PSI_value +240 /* 2 BYTE*/

//////////////////////////////////////////
//#define EEPROM_G_occl_unit      EEPROM_LOAD_CELL_VAL          + 2 /* 1 byte*/
//#define EEPROM_G_occl_level     EEPROM_G_occl_unit  + 1   /* 1 byte*/
//#define EEPROM_G_bolus_mode     EEPROM_G_occl_level + 1   /* 1 byte*/
//#define EEPROM_G_bol_fr         EEPROM_G_bolus_mode  +1   /* 2 byte*/
//#define EEPROM_G_bol_limit      EEPROM_G_bol_fr      +2
//#define EEPROM_G_kvo           EEPROM_G_bol_limit    +12   /* 2*6 byte*/
//#define EEPROM_G_KVO_fr        EEPROM_G_kvo         +1  /* 2 byte*/
//#define EEPROM_G_bright_level   EEPROM_LOAD_CELL_VAL      +2 /*1 byte*/
//#define EEPROM_G_sound_level    EEPROM_G_bright_level+1 /*1 byte*/
//#define EEPROM_G_date_mnth      EEPROM_G_sound_level + 1 /*2 byte*/
//#define EEPROM_G_year           EEPROM_G_date_mnth +  2 /*2 byte*/
//#define EEPROM_G_time           EEPROM_G_year      +  2 /*2 byte*/
//#define EEPROM_G_time_format    EEPROM_G_time      +  2 /*2 byte*/
//#define EEPROM_G_lock_time      EEPROM_G_time_format +1 /*1 BYTE*/
//#define EEPROM_G_infusion_modes EEPROM_G_lock_time +1   /*1 BYTE*/
//#define EEPROM_G_drug_list      EEPROM_G_infusion_modes +1 /*1 BYTE*/
//#define EEPROM_BRAND_NO         EEPROM_G_drug_list + 1/*1 byte*/
//#define EEPROM_SD_LOADED_ADC_VAL  EEPROM_G_lock_time + 1 /*12 byte*/ //each syringe has adc val of 2 byte this array having 6 elements so 6*2=12
//#define EEPROM_DISPO_MIN_VAL1    EEPROM_G_lock_time + 12 /*12 byte*/ //each syringe has adc val of 2 byte this array having 6 elements so 6*2=12

//#define EEPROM_CUSTOM_DRUG_LIST  EEPROM_DISPO_MIN_VAL1 +12 /* 2 bytes*/
//#define EEPROM_FAV_DRUG_LIST     EEPROM_CUSTOM_DRUG_LIST + 2 /* 10*2= 20 bytes*///29-03
//#define EEPROM_TOTAL_FAV         EEPROM_FAV_DRUG_LIST + 20 /*1 byte*/
//#define EEPROM_TOTAL_RECENT      EEPROM_TOTAL_FAV + 1 /*1 byte*///29-03
//#define EEPROM_RECENT_DRUG_LIST  EEPROM_TOTAL_RECENT + 1 /*10*2=20 bytes*/

/************************************Events*****************************************/
//#define EEPROM_TOTAL_EVENTS     EEPROM_RECENT_DRUG_LIST +20 		/*2 byte*/
//#define EEPROM_EVT_DATE    		EEPROM_TOTAL_EVENTS 	+2  		/*1000*1byte=1000*/
//#define EEPROM_EVT_MONTH		EEPROM_EVT_DATE			+1000 		/*1000*1byte=1000*/
//#define EEPROM_EVT_YEAR			EEPROM_EVT_MONTH		+1000 		/*1000*2byte=2000*/
//#define EEPROM_EVT_HOUR			EEPROM_EVT_YEAR			+2000 		/*1000*1byte=1000*/
//#define EEPROM_EVT_MIN			EEPROM_EVT_HOUR			+1000 		/*1000*1byte=1000*/
//#define EEPROM_EVT_ID			EEPROM_EVT_MIN			+1000 		/*1000*1byte=1000*/

/**************************************USED_HRS**************************************/
//#define EEPROM_DEVICE_SEC		EEPROM_DRUG_NAMES	+320	/*1 byte*/
//#define EEPROM_DEVICE_MIN		EEPROM_DEVICE_SEC	+1		/*1 byte*/
//#define EEPROM_DEVICE_HRS		EEPROM_DEVICE_MIN	+1		/*2 byte*/
//#define EEPROM_BATTERY_SEC		EEPROM_DEVICE_HRS	+2		/*1 byte*/
//#define EEPROM_BATTERY_MIN		EEPROM_BATTERY_SEC	+1		/*1 byte*/
//#define EEPROM_BATTERY_HRS		EEPROM_BATTERY_MIN	+1		/*2 byte*/
//#define EEPROM_RUNNING_SEC		EEPROM_BATTERY_HRS	+2		/*1 byte*/
//#define EEPROM_RUNNING_MIN		EEPROM_RUNNING_SEC	+1		/*1 byte*/
//#define EEPROM_RUNNING_HRS		EEPROM_RUNNING_MIN	+1		/*2 byte*/
//#define EEPROM_FACTORY_HRS		EEPROM_RUNNING_HRS	+2		/*2 byte*/
//#define EEPROM_FACTORY_RST		EEPROM_FACTORY_HRS	+2		/*1 byte*/

/*************************************************************************************/

/***********************************SD_CALIBRATION***********************************************/
//#define EEPROM_SD_BASE_VAL				EEPROM_FACTORY_RST				+1			/*2 byte*/
//#define EEPROM_SD_PULL_OUT				EEPROM_SD_BASE_VAL				+2			/*2 byte*/
//#define EEPROM_SD_ADC_LOADED_VAL		EEPROM_SD_PULL_OUT  			+2 			/*12*20=240byte*/ //2 byte for 20 brand (ALL SYRINGE ml)
//#define EEPROM_SD_ADC_MIN_VAL			EEPROM_SD_ADC_LOADED_VAL		+240		/*12*20=240byte*/ //2 byte for 20 brand (ALL SYRINGE ml)

/*************************************************************************************/

/***********************************SL_CALIBRATION***********************************************/
//#define EEPROM_SL_PULL_OUT		EEPROM_SD_ADC_MIN_VAL	+240		/*2 byte*/
//#define EEPROM_SL_PULL_IN		EEPROM_SL_PULL_OUT		+2			/*2 byte*/
//#define EEPROM_SL_LEN_VAL		EEPROM_SL_PULL_IN  	    +2 			/*12*20*=240 byte*/ //12 byte for 20 brand (all ml)
//#define EEPROM_SL_COL_VAL		EEPROM_SL_LEN_VAL  	    +240        /*12*20*=240 byte*/ //12 byte for 20 brand (all ml)

	


#endif
/*****************************************************************
					        									End of file                                       			   
******************************************************************/


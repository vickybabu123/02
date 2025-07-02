/* stage 1 succes
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

//#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_rtc.h"
#include "Color.h"
#include <stdbool.h>
#include "fsl_power.h"
#include "TFT_Commands.h"
#include "RTC_driver.h"
#include "Shapes.h"
#include "TFT_String.h"
#include "Driver_ADC.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define RTC_CLOCK_ENABLE			0x01U
#define RTC_CLOCK_DISABLE			0x00U
#define RTC_SWRESET_BIT				0x01U
#define RTC_OSC_PD_BIT				0x100
#define RTC_TIMER_CLK_ENABLE		0x80
#define ENABLE						1
#define DISABLE						0
#define VALID_DATE_TIME				1
#define ERROR_IN_DATE_TIME			0
#define SECONDS_PER_DAY    			86400
#define SECONDS_PER_HOUR   			3600
#define SECONDS_PER_MINUTE 			60
#define NO_DAYS_PER_YEAR      		365
#define STARTING_YEAR	    		2022
#define ENDING_YEAR     	 		2157
#define AM_TIME_FLAG				1
#define PM_TIME_FLAG				0

void RTC_init(void);
void RTC_Enable(uint8_t enable);
void set_date_time(const rtc_datetime_t *datetime);
uint8_t Check_Datetime_Format(const rtc_datetime_t *datetime);
uint32_t Convert_Datetime_To_Seconds(const rtc_datetime_t *datetime);
void ConvertSecondsToDatetime(uint32_t seconds, rtc_datetime_t *datetime);
void get_date_time(rtc_datetime_t *datetime);
uint32_t get_rtc_timer_count(void);
void RTC_INIT_time (void);
void RTC_date_time_update();
uint8_t RTC_FLAG=0;
uint8_t G_RTC_COUNT_FLAG=0;

uint8_t time_display_flag = 0;
uint32_t currSeconds = 0;
uint32_t prev_second = 0;
rtc_datetime_t date;
extern uint16_t power_key_values;
extern uint8_t rtc_power_read;

/*!
 * @brief ISR for Alarm interrupt
 *
 * This function changes the state of busyWait.
 */

uint16_t sec_blink;
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void RTC_IRQHandler(void)
{
    if (RTC_GetStatusFlags(RTC) & kRTC_AlarmFlag)
    {
        RTC_FLAG = 1;
        /*start*/
        get_date_time(&date);
       	if(RTC_FLAG==1)
           	{
           		//PRINTF("\n handler called");
                currSeconds = get_rtc_timer_count();


//                Font_Select(ARIAL_14);
//                TFT_Number(0,70,currSeconds,YELLOW,RED);
                /* Add alarm seconds to current time */
                //currSeconds += 1;

                /* Set alarm time in seconds */
                RTC_SetSecondsTimerMatch(RTC, (currSeconds+1));

                /* Get alarm time */
              //  RTC_GetAlarm(RTC, &date);
               // PRINTF("\n currSeconds in handler %d= ",currSeconds);
//                if(currSeconds != date.second)
//                         {
//                         	if(date.hour == 0)
//                         	{
//                         		date.hour = 12;
//                         		time_display_flag = AM_TIME_FLAG;
//                         	}
//                         	else if(date.hour == 12)
//                         	{
//                         		time_display_flag = PM_TIME_FLAG;
//                         	}
//                         	else if(date.hour > 12)
//                         	{
//                         		date.hour = date.hour - 12;
//                         		time_display_flag = PM_TIME_FLAG;
//                         	}
//                         	else
//                         	{
//                         		time_display_flag = AM_TIME_FLAG;
//                         	}
//
//                 			/* print default time */
//                 		//	PRINTF("Current datetime: %04d-%02d-%02d %02d:%02d:%02d\t", date.year, date.month, date.day, date.hour,
//                 				//   date.minute, date.second);
//                 			if(time_display_flag == AM_TIME_FLAG)
//                 			{
//                 			//	PRINTF("AM\r\n");
//                 			}
//                 			else
//                 			{
//                 			//	PRINTF("PM\r\n");
//                 			}
//                 			currSeconds = prev_second;
//                         }
           		////////
           	}
        /*end*/
        /* Clear alarm flag */
       	RTC_FLAG=0;

        RTC_ClearStatusFlags(RTC, kRTC_AlarmFlag);
    }
    SDK_ISR_EXIT_BARRIER;
}

/*
 ******************************************************************************
Function name : RTC_init(void)
Description   : This function Initialize RTC clock configuration
Input         : void
Output        : void
 ******************************************************************************
 */
void RTC_init(void)
{
	SYSCON->AHBCLKCTRLSET[0]|= 1 << 23;	//Set 23rd bit to Enable the bus clock for the RTC
	RTC->CTRL &= ~RTC_SWRESET_BIT;		//Clear software set bit before initiating the RTC operations
	RTC->CTRL &= ~RTC_OSC_PD_BIT;		//Clear RTC oscillator power down mode
}

/*
 ******************************************************************************
Function name : RTC_Enable(uint8_t enable)
Description   : This function enable or disable RTC timer
Input         : Enable or disable flag
Output        : void
 ******************************************************************************
 */
void RTC_Enable(uint8_t enable)
{
	if(enable)
	{
		RTC->CTRL |= RTC_TIMER_CLK_ENABLE;
	}
	else
	{
		RTC->CTRL &= ~RTC_TIMER_CLK_ENABLE;
	}
}

/*
 *********************************************************************************
Function name : set_date_time(const rtc_datetime_t *datetime)
Description   : This function helps to set the RTC counter starting date and time
Input         : Date, month, year, hour, minute and second
Output        : void
 *********************************************************************************
 */
void set_date_time(const rtc_datetime_t *datetime)
{
	if(Check_Datetime_Format(datetime))
	{
	    /* RTC time counter has to be stopped before setting the date & time in the TSR register */
	    RTC_Enable(DISABLE);
		/* Set time in seconds */
		RTC->COUNT = Convert_Datetime_To_Seconds(datetime);
	    /* Start the RTC time counter */
	    RTC_Enable(ENABLE);
	}
}

/*
 *********************************************************************************
Function name : Check_Datetime_Format(const rtc_datetime_t *datetime)
Description   : This function helps to validate the provided date and time format
Input         : Date, month, year, hour, minute and second
Output        : Validation result as valid or not
 *********************************************************************************
 */
uint8_t Check_Datetime_Format(const rtc_datetime_t *datetime)
{
    /* Table of days in a month for a non leap year. First entry in the table is not used,
     * valid months start from 1
     */
    uint8_t daysPerMonth[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

    /* Check year, month, hour, minute, seconds */
    if ((datetime->year < STARTING_YEAR) || (datetime->year > ENDING_YEAR) || (datetime->month > 12U) ||
        (datetime->month < 1U) || (datetime->hour >= 24U) || (datetime->minute >= 60U) || (datetime->second >= 60U))
    {
        /* If not correct then return error*/
        return ERROR_IN_DATE_TIME;
    }

    /* Adjust the days in February for a leap year */
    if ((((datetime->year & 3U) == 0U) && (datetime->year % 100U != 0U)) || (datetime->year % 400U == 0U))
    {
        daysPerMonth[2] = 29U;
    }

    /* Check the validity of the day */
    if ((datetime->day > daysPerMonth[datetime->month]) || (datetime->day < 1U))
    {
    	/* If not correct then return error*/
        return ERROR_IN_DATE_TIME;
    }

    return VALID_DATE_TIME;
}

/*
 **************************************************************************************
Function name : Convert_Datetime_To_Seconds(const rtc_datetime_t *datetime)
Description   : This function helps to convert the provided date and time into seconds
Input         : Date, month, year, hour, minute and second
Output        : Converted seconds
 **************************************************************************************
 */
uint32_t Convert_Datetime_To_Seconds(const rtc_datetime_t *datetime)
{
    /* Number of days from begin of the non Leap-year*/
    uint16_t monthDays[] = {0U, 0U, 31U, 59U, 90U, 120U, 151U, 181U, 212U, 243U, 273U, 304U, 334U};
    uint32_t seconds;

    /* Compute number of days from 20222 till given year*/
    seconds = ((uint32_t)datetime->year - 2022) * NO_DAYS_PER_YEAR;
    /* Add leap year days */
    seconds += (((uint32_t)datetime->year / 4) - (2022 / 4));
    /* Add number of days till given month*/
    seconds += monthDays[datetime->month];
    /* Add days in given month. We subtract the current day as it is
     * represented in the hours, minutes and seconds field*/
    seconds += ((uint32_t)datetime->day - 1);
    /* For leap year if month less than or equal to Febraury, decrement day counter*/
    if (((datetime->year & 3) == 0x00) && (datetime->month <= 2))
    {
        seconds--;
    }

    seconds = (seconds * SECONDS_PER_DAY) + (datetime->hour * SECONDS_PER_HOUR) +
              (datetime->minute * SECONDS_PER_MINUTE) + datetime->second;

    return seconds;
}

/*
 *********************************************************************
Function name : get_date_time(rtc_datetime_t *datetime)
Description   : This function provides the current RTC date and time
Input         : Date, month, year, hour, minute and second
Output        : void
 *********************************************************************
 */
void get_date_time(rtc_datetime_t *datetime)
{
	uint32_t seconds = 0;
	//Get current RTC count
	seconds = get_rtc_timer_count();
	//Convert current RTC count to date & time
	ConvertSecondsToDatetime(seconds, datetime);
}

/*
 ******************************************************************************
Function name : get_rtc_timer_count(void)
Description   : This function provides the current RTC count in seconds format
Input         : void
Output        : Current RTC count in seconds
 ******************************************************************************
 */
uint32_t get_rtc_timer_count(void)
{
	uint32_t prev_count = 0, curr_count = 0;
	uint16_t holdtime = 0;

	/* Follow the RF document to read the RTC default seconds timer (1HZ) counter value. */
	//Read RTC count register 2 times and cross check with each-other - recommended in datasheet
	do
	{
		prev_count = RTC->COUNT;
		curr_count = RTC->COUNT;
		holdtime++;					//Timeout
		if(holdtime > 1000)
		{
			holdtime = 0;
			curr_count = 0;			//Return RTC count as ZERO if count didn't match until 1000
			break;
		}

	}while(prev_count != curr_count);

	return curr_count;
}

/*
 **************************************************************************************
Function name : ConvertSecondsToDatetime(uint32_t seconds, rtc_datetime_t *datetime)
Description   : This function helps to convert the RTC count in seconds into date and
				time format (year-month-date hour-minute-second)
Input         : Date, month, year, hour, minute, second and RTC count in seconds
Output        : void
 **************************************************************************************
 */
void ConvertSecondsToDatetime(uint32_t seconds, rtc_datetime_t *datetime)
{
    uint8_t find_month = 0;
    uint16_t daysInYear = 0, find_year = 0;
    uint32_t secondsRemaining = 0;
    uint32_t days = 0;
    /* Table of days in a month for a non leap year. First entry in the table is not used,
     * valid months start from 1
     */
    uint8_t daysPerMonth[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

    /* Start with the seconds value that is passed in to be converted to date time format */
    secondsRemaining = seconds;

    /* Calcuate the number of days, we add 1 for the current day which is represented in the
     * hours and seconds field
     */
    days = secondsRemaining / SECONDS_PER_DAY + 1U;

    /* Update seconds left*/
    secondsRemaining = secondsRemaining % SECONDS_PER_DAY;

    /* Calculate the datetime hour, minute and second fields */
    datetime->hour   = (uint8_t)(secondsRemaining / SECONDS_PER_HOUR);
    secondsRemaining = secondsRemaining % SECONDS_PER_HOUR;
    datetime->minute = (uint8_t)(secondsRemaining / 60U);
    datetime->second = (uint8_t)(secondsRemaining % SECONDS_PER_MINUTE);

    /* Calculate year */
    daysInYear     = NO_DAYS_PER_YEAR;
    datetime->year = STARTING_YEAR;

    for(find_year = (STARTING_YEAR + 1); (days > daysInYear); find_year++)
    {
        /* Decrease day count by a year and increment year by 1 */
        days -= daysInYear;
        datetime->year = find_year;

        /* Adjust the number of days for a leap year */
        if ((find_year & 3U) != 0x00U)
        {
            daysInYear = NO_DAYS_PER_YEAR;
        }
        else
        {
            daysInYear = NO_DAYS_PER_YEAR + 1U;
        }
    }

	/* Adjust the days in February for a leap year */
	if ((datetime->year & 3U) == 0x00U)
	{
		daysPerMonth[2] = 29;
	}

	for (find_month = 1; find_month <= 12; find_month++)
	{
		if (days <= daysPerMonth[find_month])
		{
			datetime->month = find_month;
			break;
		}
		else
		{
			days -= daysPerMonth[find_month];
		}
	}

	datetime->day = (uint8_t)days;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void RTC_INIT_time (void)
{
	/* Init RTC */
	RTC_init();
	//RTC_Init(RTC);
	get_date_time(&date);
/* Set a start date time and start RT */
//	date.year   = 2024;
//	date.month  = 3U;
//	date.day    = 6U;
//	date.hour   = 4U;
//	date.minute = 20;
//	date.second = 00;
//	currSeconds = 00;
//
//	/* Set RTC time to default */
//	set_date_time(&date);

	EnableIRQ(RTC_IRQn);

	/* This loop will display the RTC time for every 1 second */
	currSeconds = get_rtc_timer_count();

	/* Add alarm seconds to current time */
	// currSeconds += 1;

	/* Set alarm time in seconds */
	RTC_SetSecondsTimerMatch(RTC, currSeconds+1);
}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void RTC_date_time_update()
{
	 set_date_time(&date);
	 EnableIRQ(RTC_IRQn);
	 currSeconds = get_rtc_timer_count();
	 RTC_SetSecondsTimerMatch(RTC, currSeconds+1);
}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void time_screen_saver()
{
	/*date.year   = 2024;
	date.month  = 8U;
	date.day    = 14U;
	date.hour   = 18U;
	date.minute = 59U;*/
	char *months[13] = {    "no mon",
							"Jan",
							"Feb",
							"Mar",
							"Apr",
							"May",
							"Jun",
							"Jul",
							"Aug",
							"Sep",
							"Oct",
							"Nov",
							"Dec"
						};
	uint8_t LEFT=13;
	uint8_t RIGHT=0;
	uint16_t prev[5]={0,0,0,0};

//	uint8_t LEFT_G=10;
//	uint8_t RIGHT_G=0;

	G_RTC_COUNT_FLAG=1;
	//Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	Font_Select(ARIAL_20);
	TFT_String(120+65+2+3/*leftwright*/,140/*height*/,(uint8_t *)",",MAIN_FRAME_COL,RED);

	while(power_key_values>700);

while(1)
{
	if(!rtc_power_read)
	{
		 rtc_power_read=1;
		 power_key_values=ADC_read(ADC_CH_POWER_KEY);
	}

	 if(power_key_values>700)
		{
		  break;
		}

	if((prev[0]!=date.hour)  || (prev[1]!=date.minute)  || (G_RTC_COUNT_FLAG==1))
	{
		TFT_screen_saver_Time_disp(87+20-LEFT+RIGHT,100-5-30,(prev[0]*100)+prev[1],MAIN_FRAME_COL,MAIN_FRAME_COL);

		TFT_screen_saver_Time_disp(87+20-LEFT+RIGHT,100-5-30,(date.hour*100)+date.minute,MAIN_FRAME_COL,WHITE);

		if(prev[0]!=date.hour)
			{
			  prev[0]=date.hour;
			}

		if(prev[1]!=date.minute)
			{
				prev[1]=date.minute;
			}
	//	G_RTC_COUNT_FLAG=0;
	}


//	Font_Select(ARIAL_36);
//	if((!sec_blink) || (G_RTC_COUNT_FLAG==1))
//	{
//	   TFT_String(120+57+10-LEFT+RIGHT+5/*leftwright*/,100-5-30+5+2/*height*/,(uint8_t *)":",MAIN_FRAME_COL,WHITE);
//	   sec_blink=2;
//	}
//	else if((sec_blink==1) || (G_RTC_COUNT_FLAG==1))
//	{
//	   TFT_String(120+57+10-LEFT+RIGHT+5/*leftwright*/,100-5-30+5+2/*height*/,(uint8_t *)":",MAIN_FRAME_COL,RED);
//	  // sec_blink=2;
//	}

		Font_Select(ARIAL_36);
		if((!sec_blink))
		{
		   TFT_String(120+57+10-LEFT+RIGHT+5/*leftwright*/,100-5-30+5+2/*height*/,(uint8_t *)":",MAIN_FRAME_COL,WHITE);
		   sec_blink=2;
		}
		else if(sec_blink==1)
		{
		   TFT_String(120+57+10-LEFT+RIGHT+5/*leftwright*/,100-5-30+5+2/*height*/,(uint8_t *)":",MAIN_FRAME_COL,MAIN_FRAME_COL);
		  // sec_blink=2;
		}

	Font_Select(ARIAL_20);

    if((prev[2]!=date.month) || (G_RTC_COUNT_FLAG==1))
    {
    	TFT_String(87-2+5/*leftwright*/,140/*height*/,(uint8_t *)months[prev[2]],MAIN_FRAME_COL,MAIN_FRAME_COL);
    	TFT_String(87-2+5/*leftwright*/,140/*height*/,(uint8_t *)months[date.month],MAIN_FRAME_COL,RED);
    	prev[2]=date.month;
	//	G_RTC_COUNT_FLAG=0;

    }

    if((prev[3]!=date.day) || (G_RTC_COUNT_FLAG==1))
        {
    	   // TFT_Number(120+30+5/*leftwright*/,140/*height*/,prev[3],BLACK,BLACK);
        	//TFT_Number(120+30+5/*leftwright*/,140/*height*/,date.day,BLACK,RED);
    	TFT_Number_month(120+30+5/*leftwright*/,140/*height*/,prev[3],MAIN_FRAME_COL,MAIN_FRAME_COL);
    	TFT_Number_month(120+30+5/*leftwright*/,140/*height*/,date.day,MAIN_FRAME_COL,RED);
        	prev[3]=date.day;
    		//G_RTC_COUNT_FLAG=0;

        }


    //TFT_String(120+65+2+3/*leftwright*/,140/*height*/,(uint8_t *)",",BLACK,RED);

	if((prev[4]!=date.year) || (G_RTC_COUNT_FLAG==1))
	{
		TFT_Number(120+65+10+8/*leftwright*/,140/*height*/,prev[4],MAIN_FRAME_COL,MAIN_FRAME_COL);
		TFT_Number(120+65+10+8/*leftwright*/,140/*height*/,date.year,MAIN_FRAME_COL,RED);
		prev[4]=date.year;
		G_RTC_COUNT_FLAG=0;

	}

//	return 0;
}

}


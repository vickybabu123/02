/*
 * RTC_driver.h
 *
 *  Created on: 06-Mar-2024
 *      Author: Software4
 */
#include "LPC55S16.h"
#include <stdio.h>


void RTC_IRQHandler(void);
void RTC_init(void);
void RTC_Enable(uint8_t enable);
void set_date_time(const rtc_datetime_t *datetime);
uint8_t Check_Datetime_Format(const rtc_datetime_t *datetime);
uint32_t Convert_Datetime_To_Seconds(const rtc_datetime_t *datetime);
void get_date_time(rtc_datetime_t *datetime);
uint32_t get_rtc_timer_count(void);
void ConvertSecondsToDatetime(uint32_t seconds, rtc_datetime_t *datetime);
void RTC_INIT_time (void);
void RTC_date_time_update();
void time_screen_saver();

//typedef struct _rtc_datetime
//{
//    uint16_t year;  /*!< Range from 1970 to 2099.*/
//    uint8_t month;  /*!< Range from 1 to 12.*/
//    uint8_t day;    /*!< Range from 1 to 31 (depending on month).*/
//    uint8_t hour;   /*!< Range from 0 to 23.*/
//    uint8_t minute; /*!< Range from 0 to 59.*/
//    uint8_t second; /*!< Range from 0 to 59.*/
//} rtc_datetime_t;

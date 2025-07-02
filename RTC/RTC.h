/*
 * RTC.h
 *
 *  Created on: 28-Dec-2023
 *      Author: Software6
 */

#ifndef RTC_H_
#define RTC_H_

void RTC_screen(void);
void RTC_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page);//, const char* array[3]);
void format_subsetting(uint8_t option_no, uint8_t INC_flag);
void Digit_Spiliting1(uint16_t Value,uint8_t cur_no,uint8_t prev_no);
void option_footer_frame();
void option_footer_frame();



















#endif /* RTC_H_ */

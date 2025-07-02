/*
 * Calibration_Screen.h
 *
 *  Created on: 06-Jan-2024
 *      Author: Software6
 */

#ifndef CALIBRATION_SCREEN_H_
#define CALIBRATION_SCREEN_H_

void Calibration_screen();
void Warning_Frame();
void Zero_PSI_Calibration();
void Indication_Frame();
uint8_t edit_screen(uint16_t *Edit_value,uint8_t screen,uint16_t max_value);
void edit_option(uint8_t current_cur_no,uint8_t prev_cursor_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL,uint32_t UP_ARROW_ERASE);
void Digit_Spiliting1(uint16_t Value,uint8_t cur_no,uint8_t prev_no);
void edit_split_frame(uint8_t screen);
uint8_t edit_screen_Time(uint32_t *Edit_value,uint8_t screen,uint16_t max_value);
void edit_option_frame(uint8_t current_cur_no,uint8_t prev_cursor_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL,uint32_t UP_ARROW_ERASE);

#endif /* CALIBRATION_SCREEN_H_ */

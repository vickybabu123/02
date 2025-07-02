/*
 * Password.h
 *
 *  Created on: 14-Feb-2024
 *      Author: SoftwareRND
 */

#ifndef PASSWORD_H_
#define PASSWORD_H_

void Digit_Spiliting_passcode(uint16_t Value);
uint16_t Passcode(uint16_t mode);
void passcode_header_footer_frame();
void Pc_split_frame();
void Left_Right_Indi_passcode(uint8_t cursor_pos);
void password_option_frame(uint8_t Cursor_no);
void password_option_scroll(uint8_t current_cur_no,uint8_t prev_cursor_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL,uint32_t UP_ARROW_ERASE);
void password_up_key_fun(uint8_t Cursor_no );
void password_down_key_fun(uint8_t Cursor_no);

typedef struct password{


		uint8_t position_3;
		char letter_3[2] ;
		uint8_t array_dig_2[4];
		uint8_t previous_atmpt_count;
}pas_var;

extern pas_var password ;

#endif /* PASSWORD_H_ */

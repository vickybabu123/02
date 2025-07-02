


#ifndef FLOWRATE_SCREEN_H_
#define FLOWRATE_SCREEN_H_

uint32_t Flow_rate_screen(uint32_t *flow_rate,uint8_t Min_Limit,uint32_t Max_Limit,uint8_t screen);
void Frame_Header(uint32_t BG_color, uint32_t TXT_color ,uint8_t *word);
//void Frame_Footer(uint32_t BG_color, uint32_t TXT_color,uint8_t *word,uint8_t *circle_word,uint8_t circle_pos);
void flowrate_option_scroll(uint8_t current_cur_no,uint8_t prev_cursor_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL,uint32_t UP_ARROW_ERASE);
void Digit_Spiliting(uint32_t Value);
void Left_Right_Indi(uint8_t cursor_pos,uint8_t screen_id);


uint16_t Double_Decimal_FR_screen(uint32_t *flow_rate, uint32_t Limit ,uint8_t mode);
void flowrate_option_scroll_DD(uint8_t current_cur_no,uint8_t prev_cursor_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL,uint32_t UP_ARROW_ERASE);
void Digit_Spiliting_DD(uint32_t Value);
//void Left_Right_Indi_DD(uint8_t cursor_pos);

#endif /* FLOWRATE_SCREEN_H_ */

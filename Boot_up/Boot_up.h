#include "LPC55S16.h"

#ifndef BOOT_UP_H
#define BOOT_UP_H


void Boot_up();
void self_test_process();
uint16_t  TFT_String_align(uint16_t x_start,uint16_t x_end,uint16_t YPOS,uint8_t *popup_message,uint8_t center,uint32_t back_col,uint32_t txt_col);    //REW1
void EEPROM_menu_sett_write(void);
void EEPROM_SL_calib_write(void);
void EEPROM_Plunger_tuning_calib_write(void);
void EEPROM_occul_write_data(void);
void EEPROM_fact_write(void);
void EEPROM_SD_calib_write(void);

void EEPROM_menu_sett_read(void);
void Plunger_Tuning_EEPROM_read(void);
void Pressure_EEPROM_read();
void EEPROM_SD_READ(void);
void SL_EEPROM_read();
void EEPROM_fact_sett_read(void);
void shutting_down(void);
uint16_t  TFT_String_align(uint16_t x_start,uint16_t x_end,uint16_t YPOS,uint8_t *popup_message,uint8_t center,uint32_t back_col,uint32_t txt_col);    //REW1


#define CLRSCR(X)    Rectangle(0,0,320,240,X);
#define CENTERSCR()	 Rectangle(3,36,317,169,MAIN_FRAME_COL);

//void progress_bar(uint16_t strat_x,uint16_t end_x,uint16_t y_pos,uint8_t space,uint8_t height, uint32_t color);

#endif /* BOOT_UP_H */

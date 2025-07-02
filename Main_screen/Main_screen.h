

#define SYMBOL_SPACE 	12

#define RUNSYMBOL_POS  	SYMBOL_SPACE
#define ADL_PED_POS   	RUNSYMBOL_POS	+	SYMBOL_SPACE	+22
#define BATTERY_POS   	ADL_PED_POS		+	SYMBOL_SPACE	+30
#define DYN_PRES_POS  	BATTERY_POS		+	SYMBOL_SPACE	+28+12
#define DYN_VAL_POS	  	DYN_PRES_POS	+	SYMBOL_SPACE	+44
#define DYN_UNIT_POS  	DYN_VAL_POS		+	SYMBOL_SPACE	+12
#define TEMPERATURE_BASED_DRIFT_RANGE 10

void main_screen_frame(uint16_t flowrate1,uint8_t mode);
void FR_spliting(uint16_t flowrate);
void FR_Lines(void);
uint8_t Home_screen_functionality(uint8_t mode);
uint8_t key_main_screen(void);
uint8_t key_main_screen_VTBI(void);
uint8_t key_fun_doserate_mode(void);
void scroll_bar(uint8_t option_no,uint8_t page_no,uint8_t total_option);                                       //(uint8_t prev_option, uint8_t curr_option, uint8_t page)
void Battery_symbol(void);
void dose_rate_para(uint8_t start_cnt, uint8_t end_cnt);
void scroll_bar(uint8_t page_no,uint8_t option_no,uint8_t total_option);     //23-03                                  //(uint8_t prev_option, uint8_t curr_option, uint8_t page)
void pressure_display(uint8_t bol_run,uint8_t bol_reset_flg);
uint8_t Key_functionality(uint8_t mode);
void Common_Warning(void);
void scroll_bar(uint8_t page_no,uint8_t option_no,uint8_t total_option);    //23-03                                  //(uint8_t prev_option, uint8_t curr_option, uint8_t page)

uint8_t Brand_List(uint8_t id_flag);

void Main_Menu_Screen();
void Main_Menu_Frame(void);
void Main_Menu_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void Menu_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[3][4]);

void iv_line_setting();

uint8_t Occlusion_setting();
void Occl_Frame(void);
void Occl_Opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void Occl_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[3]);
void occl_subsetting(uint8_t option_no, uint8_t INC_flag);
//void occl_subsetting_frame(void);
uint16_t Passcode(uint16_t mode);


void Air_Screen();
void air_Frame(void);
void air_Opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void air_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[3]);
void air_subsetting(uint8_t option_no, uint8_t INC_flag);



uint8_t Bolus_Screen();
void Bolus_Frame(void);
void Bolus_Opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void bolus_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page);//, const char* array[4])
void bolus_subsetting(uint8_t option_no,uint8_t page_no, uint8_t INC_flag);
//void bolus_subsetting_frame(void);

uint8_t KVO_Screen();
uint8_t KVO_Frame(uint8_t status);
void KVO_Opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void KVO_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[3]);
void kvo_subsetting(uint8_t option_no,uint8_t page_no, uint8_t INC_flag);
void edit_subsetting_frame(void);
void menu_fun(uint8_t page_no ,uint8_t option_no);


uint8_t device_sett_Screen();
void device_sett_frame(void);
void device_sett_Opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void device_sett_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page, const char* array[2][4]);
void device_subsetting(uint8_t option_no,uint8_t page_no, uint8_t INC_flag);
void device_info_frame(void);
void device_info_Opt_Frame();

uint8_t sys_sett_Screen();
void sys_sett_Opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void sys_sett_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page);//, const char* array[3]);
void sys_sett_frame(void);
void sys_sett_fun(uint8_t option_no);
void Rectangle_Line_function(uint8_t start_point,uint8_t end_point);
void edit_subsetting_frame(void);

uint8_t Dosage_setting();
extern uint8_t event_display();
		//25-03

//int brand_set(uint8_t total_option);
//int branddisplay(uint8_t brand_update_no);
//void brand__drug_split_screen(uint8_t page_no);
//int Brand_List(void);
//int branddisplay(uint8_t brand_update_no);
////void brand__drug_split_screen(uint8_t page_no);
//
//void Brand_List_layout ();
//void  Brand_List_option(uint8_t page,uint8_t starting_count,uint8_t Final_count);
//uint32_t Brand_list_option_scroll(uint8_t prev_option,uint8_t curr_option,uint8_t page, const char* array[3][4]);
//void Drug_List(void);

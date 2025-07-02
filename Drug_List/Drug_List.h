int drug_set(uint8_t total_option);
uint8_t Drug_List(void );
void Drug_List_layout();
void drug_List_option(uint16_t page,uint8_t starting_count,uint8_t Final_count);//ZOOZ_2
void drug_list_option_scroll(uint8_t prev_option,uint8_t curr_option,uint16_t page);//, const char* array[4][4]);

////////////////////////Favourite and recent drug functions///////////////////////////////////////////

uint8_t favourite_func(void);
void favourite_Frame(void);
void favourite_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void fav_edit_subsetting_frame(void);
void favourite_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page);//,  char* array[5][4][20])


uint8_t recent_drug_fun(void);
void recent_drug_Frame(void);
void recent_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void recent_cursor(uint8_t prev_option, uint8_t curr_option, uint8_t page,  char array[5][4][20]);

uint8_t favourite_functionality(uint16_t drug_no,uint8_t pos);
uint8_t recently_used_fun(uint16_t drug_no);


uint8_t category_a_screen(void);
//////////////////////////////////////////////////////////////////////////////////////////////////////

//extern const char* drug_unit[4][4];
extern const char* patient_weight_unit[3];


//typedef struct
//{
//	uint32_t pat_weight;
//	uint32_t drug_con;
//	uint32_t drug_con_ml;
//	uint32_t drug_dos;
//	//uint16_t pat_height;
//	float conc_value;
//	uint8_t drug_name;
//	float flow_rate;
//	uint8_t drug_select_no;
//
//}drug_lib;
//
//extern drug_lib dose;

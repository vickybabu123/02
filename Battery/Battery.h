


void batt_pin_init(void);
void batt_stat(void);
void power_status(void);
void battery_status(void);

void battery_level(uint16_t xpos,uint8_t batt_perc);
void battery_logo(void);
void plug_symbol(uint32_t plug_col);
void Battery_symbol(void);


typedef struct
{
	uint16_t mains;
	uint16_t batt;
	uint16_t STAT_high;
	uint16_t STAT_low;
	uint16_t PG_high;
	uint16_t PG_low;
	uint8_t error_cnfm;

	uint8_t STAT_PIN_flag;
	uint8_t PG_PIN_flag;
	uint8_t error_code;
}bat_status;

 extern bat_status  BAT_CHECK;

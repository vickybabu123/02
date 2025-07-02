

#define RUN_STOP_KEY   3671076
#define PURGE_KEY      3671072
#define AUTO_BOLUS     3277856
#define SET_KEY        3277860

#define TIME_HHMM 2
#define COLON_ON  1
#define COLON_OFF 0

#define BUZZER_PIN	IOCON->PIO[1][2]         // pwm buzzer pin

#define WARN_SOUND(on,off,dura)     		 {if(1) {soundontime=on; soundofftime=off; soundduration=dura;}}


#define delay_100us(micro)       	{micro_time_delay= micro; while(micro_time_delay);}
#define delay_ms(milli)        		{milli_time_delay=milli; while(milli_time_delay);}
#define delay_secs(secs)      		{secs_time_delay=secs; while(secs_time_delay);}

void Timer0_Init( );
void Timer1_Init(uint32_t MR_VALUE);
void Timer2_Init();
void Timer3_Init();
void Timer_disable();

void CTIMER0_IRQHandler(void);
void CTIMER1_IRQHandler(void);
void CTIMER2_IRQHandler(void);
void CTIMER3_IRQHandler(void);

extern volatile uint16_t micro_time_delay;
extern volatile uint16_t milli_time_delay;
extern volatile uint16_t secs_time_delay;

extern uint8_t buzzercount;
extern uint8_t soundontime;
extern uint8_t soundofftime;
extern uint8_t soundflag;
extern uint8_t soundduration;

void _1_sec_fun();
void _100_us_fun();
void _1_ms_fun();
void _10_ms_fun();
void _100_ms_fun();

#define  BATT_STAT		    ((GPIO->PIN[1] & 1<<27)==1<<27)
#define  BATT_PG			((GPIO->PIN[1] & 1<<28)==1<<28)

#define MAINS_UP 	        3600			//NEED TO UPDATE SYR BAT ADC

#define BATTERY_CRITICAL 	700.0
#define BATTERY_FULL	 	900.0
#define AIR_PIN       ((GPIO->PIN[0] & 1<<23)==1<<23)

//typedef struct
//{
//	uint8_t _10ms_count;
//	uint8_t _100ms_count;
//	uint8_t _1sec_count;
//	uint8_t  min_count;
//	uint8_t  hr_count;
//} Timer;
//
//extern Timer TIM;

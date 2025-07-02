
extern void delay_us(unsigned int data);
uint32_t DAC__datawrite(uint16_t addrs1,float voltage, uint16_t bytes_val);
void DAC_i2c_start(int rw_bit);
void DAC_i2c_Stop(void);
uint16_t calculateADCResult(float voltage, unsigned int resolution);

#define DAC_SLAVE_ADD		0XC0
#define WRITE_BIT			0x00
#define READ_BIT			0x01

#define LATCH_PIN			31
#define LATCH_PIN_PORT	    1

#define RESOLUTION 1024



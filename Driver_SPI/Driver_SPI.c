#include "LPC55S16.h"
//#include "Color.h"
#include "fsl_clock.h"
#include "fsl_reset.h"
#include "Driver_SPI.h"
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void SPI5_Init(void)
{

	CLOCK_AttachClk(kMAIN_CLK_to_FLEXCOMM5);     //Flexcomm 5 initialization
	RESET_PeripheralReset(kFC5_RST_SHIFT_RSTn);

/**********************Master Intialization *************************************************/

	SYSCON->AHBCLKCTRLSET[1]|=1<<16;			//Enables the clock for the Flexcomm 5
	IOCON->PIO[0][7]|=(0x03|0x20|0x100);		//SCK, enable pullup,Digit_mode //PIO[0][7]
	IOCON->PIO[0][8]|=(0x03|0x20|0x100);		//MOSI,Digit_mode               //PIO[0][8]
	IOCON->PIO[1][14]|=(0x04|0x20|0x100);	    //Chip select- SSEL0,Digit_mode
	FLEXCOMM5->PSELID =2; 			            //SPI selection
	SPI5->DIV = SPI_DIV_DIVVAL(2);              //fclK(12Mhz)/23(divval)  // divval = ((srcClock_Hz* 10U) / baudrate_Bps + 5U) / 10U - 1U;

	//srcClock_Hz=12Mhz,baudrate_Bps=500000U

	SPI5->CFG = 0x4;							//Master enable
	SPI5->FIFOCFG|=(0x1|0x10000);				//Enabled bits - ENABLETX,ENABLERX,EMPTYTX,EMPTYRX

	SPI5->FIFOTRIG|=(0X1|0X2);				    //Enabled bits - TXLVLENA,RXLVLENA
	SPI5->CFG |= 0X1;							//SPI enable

/***********************************************************************************************/

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void SPI_transfer(uint32_t txvalue,uint16_t length)
{
	uint8_t demo=17;
	/* clear tx/rx errors and empty FIFOs */
	SPI5->FIFOCFG |=(0x10000|0x20000);

//	while(((SPI5->STAT) & (0X1F00)));

	/* transmit if txFIFO is not full and data to receive does not exceed FIFO depth */

	if((((SPI5->FIFOSTAT) & (SPI_FIFOSTAT_TXNOTFULL_MASK)))!=0)
	{
		/* send data */
		SPI5->FIFOWR |= ((1<<20)|txvalue|(length<<24));
		//SPI_FIFOWR_LEN(dataWidth) //data length- 8 bit(0t0 7)
	}
	while(!((SPI5->STAT) & (1<<8)));

//	while(demo--)
//	{
//
//	}

}





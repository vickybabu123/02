#include "LPC55S16.h"
#include"FR_CALC.h"
#include <infused_calculate.h>
//#include "Last_infusion.h"
#include "Power_off.h"
#include "Dosage_mode.h"

uint8_t last_infused_data(uint8_t modes);
void VTBI_reset(void);
void Dosage_value_reset();

extern uint8_t  previous_data(uint8_t mode);
extern uint16_t G_Remaining_volume;
extern uint8_t G_drug_unit_no;  //ZOOZ_1
extern uint8_t warning_flag[3];
extern char* drug_unit[4][4];

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t last_infused_data(uint8_t modes)
{

uint8_t last_infusion_flag=0;
last_infusion_flag=previous_data(1);

	if(last_infusion_flag)
	{
		if(modes==0)
		{
			INFUSED.ml=0;
			INFUSED.sec=0;
//			G_Remaining_volume=0;
//			MOT.volume=0;
		}
		else if(modes==1)
		{

			//G_Remaining_volume=0;
			INFUSED.ml=0;
			MOT.volume=0;
			INFUSED.sec=0;

		}
		else if(modes==2)
		{
			INFUSED.ml=0;
		//	MOT.volume=0;
		//	G_Remaining_volume=0;
		}

	}
		//POW.power_status_flag=1;
		return 0;
}

void VTBI_reset(void)
{
	MOT.volume=0;
	MOT.time=0;
	warning_flag[1]=0;

}

void Dosage_value_reset()
{
	dose.drug_con=1;
	dose.drug_con_ml=1;
	dose.drug_dos=1;
	dose.pat_weight=6000;
}

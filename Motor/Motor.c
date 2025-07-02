/****************************************************************************
* File Name    :
* Developed by :
* Version      :
* Description  :

*****************************************************************************/
#include "LPC55S16.h"
#include "Motor.h"
#include "Alarm.h"
#include "Bolus_Header.h"
#include "TFT_Commands.h"
#include "TFT_String.h"
#include "Color.h"


#define MIN_OF_CUTS_COMPARE        45
#define MAX_OF_CUTS_COMPARE        55

uint8_t G_correct_move=0;
uint8_t G_wrong_move=0;
uint8_t G_accept_rotate_count=0;
//extern uint8_t normal_run;
EXT MFB;

extern uint8_t normal_run;
extern uint8_t disc;
extern uint8_t release;
extern uint16_t m_count1;

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void MFB_check(void)
{

//	static uint8_t wrong_move_flag=0;
	static uint8_t MFB_pos=0;
	static uint8_t prev_MFB_pos=0;
	static uint8_t Ignore_flag=0;

	uint16_t Prev_Pulse_check[3][2]={
									{800, 960},
									{400, 750},
									{1300,1550}
									};

	uint16_t Pulse_check[3][2]={
									{400, 750},
									{1300, 1550},
									{800, 960}
							   };


		/***motor reverse check-err.2 alarm concept***/

	if (MFB.Prev_pulse_count == 0)
	{
		if(Ignore_flag)
		{
			MFB.Prev_pulse_count = MFB.Pulse_count;

			if(MFB.Prev_pulse_count>=Prev_Pulse_check[0][0] &&
					MFB.Prev_pulse_count<=Prev_Pulse_check[0][1])
				{
					MFB_pos=0;
				}
			else if(MFB.Prev_pulse_count>=Prev_Pulse_check[1][0] &&
					MFB.Prev_pulse_count<=Prev_Pulse_check[1][1])
				{
					MFB_pos=1;
				}
			else if(MFB.Prev_pulse_count>=Prev_Pulse_check[2][0] &&
					MFB.Prev_pulse_count<=Prev_Pulse_check[2][1])
				{
					MFB_pos=2;
				}
	   }

		else
		{
			Ignore_flag=1;
		}
		MFB.Pulse_count = 0;
	}

    else
	{

//		if(wrong_move_flag == 0)
//		{

		/* Motor pulses between the wrong cuts checking. 6 wrong movement*/

			if(MFB.Prev_pulse_count>=Prev_Pulse_check[MFB_pos][0] &&
					MFB.Prev_pulse_count<=Prev_Pulse_check[MFB_pos][1])
			{
				if(MFB.Pulse_count>=Pulse_check[MFB_pos][0] &&
						MFB.Pulse_count<=Pulse_check[MFB_pos][1])
				{
					G_correct_move++;

					if(MFB_pos==prev_MFB_pos)
					{
						G_accept_rotate_count++;
					}

					else
					{
						G_accept_rotate_count=0;
					}

				}
				else
				{
					G_wrong_move++;
					G_correct_move=0;
//					wrong_move_flag = 1;
					G_accept_rotate_count=0;
				}
				prev_MFB_pos=MFB_pos;
			}


			if(MFB_pos<2)
			{
				MFB_pos++;
			}

			else
			{
				MFB_pos=0;
			}
//
//		}
//		else
//		{
//			wrong_move_flag = 0;
//		}

		/*copy pulse count for next comparision*/

		MFB.Prev_pulse_count = MFB.Pulse_count;

		MFB.Pulse_count = 0;

		if(G_accept_rotate_count >= 6)
		{
			MFB_count_reset(0);
		}

		/**
		 * If correct movement goes above 10 both correct and wrong count are reset.
		 * If wrong movement goes 6 err.2 flag set and alarm came.
		 **/

		else if(G_correct_move >= 10)
		{
			MFB_count_reset(0);
		}
		/*more than 6 wrong count err.2 alarm flag*/
		else if(G_wrong_move >= 3)
		{
			MFB_count_reset(0);
			MFB.Motor_struck = 1;       // Motor reverse alarm
		}
	}
	/* AL3.1 concept change(based on pulse)*/
	MFB.twenty_cuts_count++;
	MFB.Min_cuts++;
}

/****************************************************************************
* Function Name :  void Motor_struck_alarm(void)
* Arguments     :  void
* Return type   :  void
* Description   :  To check the Motor struck alarm, Motor reverse alarm
*                  Less cuts alarm and Excess cuts alarm
*****************************************************************************/

void Motor_struck_alarm(void)
{

	uint8_t min_cuts_check=0;
    uint8_t max_cuts_check=0;
	uint8_t cuts_multiples=0;

	if((normal_run)||(BOL.run_mode))
	{
//		Font_Select(ARIAL_14);
//		TFT_Number(50,10,MFB.Min_cuts,WHITE,RED);
//		TFT_Number(50,40,MFB.Motor_pulse,YELLOW,RED);

		/*check the motor pulse*/

		if(MFB.Motor_pulse >1400)
		{

			if(MFB.Min_cuts)
			{
				MFB_count_reset(1);
			}

			else
			{
				MFB_count_reset(1);
				MFB.Motor_struck=2;
				Alarm(MOT_ERR_1);//Motor unable to run alarm
			}

		}

        /*
         *  Check cuts for every  TWENTY_CUT_PULSES_COUNT_AL3 pulses
         */
//		 Font_Select(ARIAL_14);
//		 TFT_Number(30,120,MFB.rpm_decode,GREEN,RED);

		if(MFB.rpm_decode<2)   //Less than 2 rpm. compare->1 cut
		{
			cuts_multiples=1;
			min_cuts_check=1;
			max_cuts_check=2;
		}
		else if(MFB.rpm_decode<20) //Less than 20 rpm. compare->10 cut
		{
//			cuts_multiples=10;
//			min_cuts_check=7;
//			max_cuts_check=13;
			cuts_multiples=15;
			min_cuts_check=12;
			max_cuts_check=18;
		}
		else if(MFB.rpm_decode<50)//Less than 50 rpm. compare->20 cut
		{
//			cuts_multiples=20;
//			min_cuts_check=17;
//			max_cuts_check=23;
			cuts_multiples=25;
			min_cuts_check=22;
			max_cuts_check=28;
		}
		else                       //above than 50 rpm. compare->50 cut
		{
//			cuts_multiples=50;
//			min_cuts_check=40;
//			max_cuts_check=60;
			cuts_multiples=60;
			min_cuts_check=50;
			max_cuts_check=70;
		}

//		Font_Select(ARIAL_14);
//		TFT_Number(80,160,MFB.cuts_time_diff,BLUE,WHITE);
//
//		Font_Select(ARIAL_14);
//		TFT_Number(150,160,MFB.cuts_time_diff_cnt,GREEN,WHITE);
//
//      TFT_Number(220,160,MFB.twenty_cuts_count,NAVY,RED);
//
//      TFT_Number(80,130,min_cuts_check,NAVY,RED);
//
 //     TFT_Number(60,160,max_cuts_check,NAVY,RED);
//
//  	TFT_Number(60,180,G_wrong_move,NAVY,WHITE);

		if(((MFB.cuts_time_diff * cuts_multiples)< MFB.cuts_time_diff_cnt)
				&& MFB.cuts_time_diff)
		{


			if(MFB.twenty_cuts_count<min_cuts_check)
			{
				MFB_count_reset(2);
				MFB.Motor_struck=3;
				Alarm(MOT_ERR_3);     // Less cuts alarm
			}

			else if(MFB.twenty_cuts_count>max_cuts_check)
			{
				MFB_count_reset(2);
				MFB.Motor_struck=4;
				Alarm(MOT_ERR_4);     //Excess cuts alarm
			}

			else
			{
				MFB_count_reset(2);   // cuts reset
			}
		}

//		else if(MFB.cuts_time_diff==0)
//		{
//		//	Alarm(MOT_ERR_1);     // Less cuts alarm
//		}

       if(MFB.Motor_struck==1)
       {
    	   Alarm(MOT_ERR_2);    //Motor reverse alarm
       }

//       if(disc==0)           //REW_UP(start/stop case)
//       {
//    	   Alarm(NOT_ENGAGE);
//       }

//       if(disc==1)
//       {
//    	   Alarm(DISC_ERR);
//       }
	}

}
/****************************************************************************
* Function Name : void MFB_count_reset(uint8_t reset_flag)
* Arguments     : reset_flag
* Return type   : void
* Description   : To reset the count and cuts value to Zero

*****************************************************************************/
void MFB_count_reset(uint8_t reset_flag)
{
	/*
	 * clear variables after continuous correct cuts movement reached
	 */
	if(!reset_flag)
	{
		G_wrong_move = 0;
		G_correct_move = 0;
		G_accept_rotate_count=0;
	}
	/*
	 * clear variables after check the minimum cuts reached
	 */
	else if(reset_flag==1)
	{
		MFB.Min_cuts=0;
		MFB.Motor_pulse=0;
//		m_count1++;
	}
	/*
	 * clear variables after less and excess cuts alarm compare
	 */
	else if(reset_flag==2)
	{
	    MFB.twenty_cuts_count = 0;
		MFB.cuts_time_diff_cnt=0;
	}
}



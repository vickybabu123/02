
/*
 * Dosage_mode.c
 *
 *  Created on: Feb 16, 2024
 *      Author: Welcome
 */

#include "LPC55S16.h"
#include "stdio.h"
#include "stdint.h"
#include "Color.h"
#include "keypad.h"
#include "Shapes.h"
#include "fsl_clock.h"
#include "Driver_I2C.h"
#include "TFT_Commands.h"
#include "TFT_String.h"
#include "shapes.h"
//#include "Drug_List.h"
//#include "Main_screen.h"
#include "Driver_Timer.h"
#include "Dosage_mode.h"
//#include "Flowrate_Screen.h"
#include "FR_CALC.h"
#include "Power_off.h"
///#include <STEPPER.h>
//#include "Events_log.h"				//25-03
//#include "Brand.h"
#include "sound.h"
//#include "Main_frame.h"
#include "Alarm.h"

//extern uint8_t first_entry_flag;


drug_lib  dose;

 char* drug_unit[4][4]={	 {"mg",		"µg",		"ng",		"cal"},
							 {"kcal",	"mol",		"kmol",		"mmol"},
							 {"umol",	"nmol",		"IU  ",		"KU  "},
							 {"U"}
							};
const char* dosage_view[4]={"Drug","Conc","Wt.","Dose"};

float time_value[4]={1.0,60.0,0.042};  //ZOOZ_1

uint8_t D_xpos=0;
uint8_t DF_xpos=0;//24-04
uint8_t G_drug_unit_no=0;  //ZOOZ_1

extern uint8_t G_dose_exit_flag;
extern uint8_t dose_option_no;
extern uint8_t G_opt_no;
extern uint8_t G_page_no;
extern uint8_t current_option_1;
extern uint8_t array_dig1[5];
extern uint8_t auto_lock_time;  //ZOOZ_1
extern uint8_t home_flag;
extern uint8_t ON_Flag;
extern uint8_t prev_data_flag;   //ZOOZ_1
extern uint8_t disc;

extern uint8_t Home_screen_functionality(uint8_t mode);//ZOOZ_1

extern volatile uint16_t waitingtime_1 ;
extern uint16_t Dosage_Alignments(uint8_t *asciichar);  //ZOOZ_1

extern char dose_rate_unit[3][13];
extern char disp_para[15];//ZOOZ_1

extern volatile uint8_t normal_run;

/***********************************************************************************
 *Function Name :void dose_rate_mode(void)
 *Arguments     :void
 *Return        :void
 *Description	:In this function used to perform the dose rate mode wizard function
 				 using function pointer
*************************************************************************************/

uint8_t dose_rate_mode(void)
{
	uint8_t exit_flag=1;
	uint8_t status=2;
	uint8_t value=0;
	//uint8_t time_interval=30;  //ZOOZ_1

//	auto_lock_time=30;

	uint8_t(* dose_mode_fun[8])()={drug_unit_settings,dose_conc_setting ,dose_conc_setting_ml,pat_weight_fun        //,patient_weight_unit_Screen

	          ,dose_unit_Screen,dosage_fun,overview_screen};

	if(prev_data_flag)  //ZOOZ_1
	{
		value=6;
	}
	while(exit_flag)
	{

		Power_off();	//26-03
		if(!ON_Flag)
		{
			break;
		}		//26-03

		else if(POW.power_status_flag) //ZOOZ_1
		{
			POW.power_status_flag=0;
			while(KEY.value);//28-03

		}

		status=dose_mode_fun[value]();


		if(status==1)
		{
		value++;
		}
		else if(status==0)
		{
			if(value)
			{
				value--;
			}
			else
			{
				exit_flag=0;
			}
		}
		else if(status==2 && value==6)
		{
			exit_flag=0;
		}
	}

	exit_flag=0;
	return status;
}

/*******************************************************************************************
 *Function Name :uint8_t dose_conc_setting(void)
 *Arguments     :void
 *Return        :check_flag (This flag used to  decide increment or decrement to the next function)
 *Description	:In this function used to edit the dose conc.in dose uint and dose conc.in mL
*********************************************************************************************/

uint8_t dose_conc_setting(void)
{

	uint8_t check_flag=0;
	check_flag=Double_Decimal_FR_screen(&dose.drug_con,100000,3);
//	dose.conc_value=(dose.drug_con/dose.drug_con_ml);
	return check_flag;

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t dose_conc_setting_ml(void)
{
	uint8_t check_flag=0;
	check_flag=Double_Decimal_FR_screen(&dose.drug_con_ml,100000,4);
	return check_flag;
}

/******************************************************************************************
 *Function Name :uint8_t pat_weight_fun(void)
 *Arguments     :void
 *Return        :check_flag (This flag used to  decide increment or decrement to the next function)
 *Description	:In this function used to edit the patient weight
*******************************************************************************************/

uint8_t pat_weight_fun(void)
{
	uint8_t check_flag=0;
	check_flag=Double_Decimal_FR_screen(&dose.pat_weight,100000,2);
	return check_flag;
}

/************************************************************************************************
 *Function Name :uint8_t drug_unit_settings(void)
 *Arguments     :void
 *Return        :check_flag(This flag used to  decide increment or decrement to the next function)
 *Description	:In this function used for drug unit navigation and select that respective drug
************************************************************************************************/

uint8_t drug_unit_settings(void)
{
	uint8_t option_no=0;
	uint8_t page_no=0;
	uint8_t prev_option = 0;
	uint8_t exit_flag=1;
	uint8_t check_flag=0;

	home_flag=0;
	POW.power_status_flag=1;	//26-03
	memset(disp_para,0,20);

	strcat((char *)disp_para,(char *)drug_unit[G_drug_unit_no/4][G_drug_unit_no%4]);
	strcat((char *)disp_para,(char *)" / mL");

	while(exit_flag)
	{
		Power_off();
		if(!ON_Flag)
		{
		 break;//26-03
		}

		else if(POW.power_status_flag)
		{
			home_flag=0;
			POW.power_status_flag=0;//26-03
			drug_unit_Frame();
			drug_unit_opt_Frame(page_no,option_no,3);
			memset(disp_para,0,20);  //ZOOZ_1
			strcat((char *)disp_para,(char *)drug_unit[G_page_no][G_opt_no]);
			strcat((char *)disp_para,(char *)" / mL");
			while(KEY.value);//28-03
		}

        switch(KEY.value)
		{
			case DOWN_KEY :   //DOWN_KEY

			beep_sound();
			if((option_no<3)&&(page_no<3))
			{
				option_no++;
//				Font_Select(ARIAL_14);
//				TFT_Number(70,70,option_no,YELLOW,RED);
//				TFT_Number(70,90,prev_option,YELLOW,RED);

				G_opt_no=option_no;
			}

			else
			{


				if(page_no<3)
				{
					page_no++;
					G_page_no=page_no;
					G_opt_no=option_no;
					Rectangle(3,36,300,169,MAIN_FRAME_COL);

					brand__drug_split_screen(page_no);
					drug_unit_opt_Frame(page_no,0,0);
					option_no=0;
//					prev_option=0;

				}
				else
				{
					page_no=0;
					G_page_no=page_no;
					option_no=0;
					G_opt_no=option_no;
					Rectangle(3,36,300,169,MAIN_FRAME_COL);
					brand__drug_split_screen(page_no);
					drug_unit_opt_Frame(page_no,0,0);
				}
			}


			if(option_no!=prev_option)
			{
				if(option_no!=0)
				{
					drug_unit_cursor(prev_option,option_no,page_no);//,drug_unit);
				}
				prev_option = option_no;
				G_page_no=page_no;
				G_opt_no=prev_option;
			}

			while(KEY.value);
			break;



			case UP_KEY:
				beep_sound();
				if(option_no>0)
					{
						option_no--;
						G_opt_no=option_no;
					}

					else
					{
						if(page_no>0)
						{
						page_no--;
						G_page_no=page_no;
						Rectangle(3,36,300,169,MAIN_FRAME_COL);
						brand__drug_split_screen(page_no);
						option_no=3;
						G_opt_no=option_no;
						}
						else
						{
							page_no=3;
							G_page_no=page_no;
							option_no=0;
							G_opt_no=option_no;
							Rectangle(3,36,300,169,MAIN_FRAME_COL);
							brand__drug_split_screen(page_no);
						}

						if(page_no<3)
						{
							drug_unit_opt_Frame(page_no,3,0);
						}
						else
						{
							drug_unit_opt_Frame(page_no,0,0);
						}
				     }

					if(option_no!=prev_option)
					{
						 if(option_no<3)
						  {
							 drug_unit_cursor(prev_option,option_no,page_no);//,drug_unit);
						  }
							prev_option = option_no;//1
							G_page_no=page_no;
							G_opt_no=prev_option;
					}
			while(KEY.value);
			break;

			case OK_KEY:
				beep_sound();
				memset(disp_para,0,20);
				strcat((char *)disp_para,(char *)drug_unit[G_page_no][G_opt_no]);
				strcat((char *)disp_para,(char *)"/mL");
				check_flag=1;
				exit_flag=0;
				while(KEY.value);
				break;

			case BACK_KEY:
				beep_sound();
				exit_flag=0;
				check_flag=0;
				while(KEY.value);
				break;
		}
	}
	return check_flag;
}

/***********************************************************************************************
 *Function Name :uint8_t dosage_fun(void)
 *Arguments     :void
 *Return        :status (This flag used to  decide increment or decrement to the next function)
 *Description	:In this function used to edit the drug dose value and overview
 				 screen for dose rate mode functionality
************************************************************************************************/

uint8_t dosage_fun(void)
{

	uint8_t check_flag=0;
	check_flag=Double_Decimal_FR_screen(&dose.drug_dos,100000,5);
	return check_flag;

}

/**************************************************************************
 *Function Name :uint8_t dose_unit_Screen(void)
 *Arguments     :void
 *Return        :check_flag(This flag used to  decide increment or decrement to the next function)
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

uint8_t dose_unit_Screen(void)
{
	uint8_t page_no=0;
	static uint8_t prev_option = 0;
	uint8_t exit_flag=1;
	uint8_t check_flag=0;
	uint8_t end_opt=0; //ZOOZ_1
	dose.drug_dos=1;
	home_flag=0;

	POW.power_status_flag=1;


	memset(dose_rate_unit, 0, sizeof(dose_rate_unit));

	strcat(dose_rate_unit[0],drug_unit[G_page_no][G_opt_no]);      //[G_drug_unit_no/4][G_drug_unit_no%4]); //ZOOZ_1

	strcat(dose_rate_unit[0],"/");
	strcat(dose_rate_unit[0],"kg");
	strcat(dose_rate_unit[0],"/");

	strcpy(dose_rate_unit[1],dose_rate_unit[0]);
	strcpy(dose_rate_unit[2],dose_rate_unit[0]);

	strcat(dose_rate_unit[0],"h");
	strcat(dose_rate_unit[1],"min");
	strcat(dose_rate_unit[2],"24h");

	end_opt=3;  //ZOOZ_1

	while(exit_flag)
	{
		Power_off();

		if(!ON_Flag)
		{
			break;//26-03
		}

		else if(POW.power_status_flag)
		{
			home_flag=0;
			POW.power_status_flag=0;//26-03
			dose_unit_parameter_Frame();
			dose_unit_parameter_opt_Frame(page_no,dose_option_no,end_opt);
			while(KEY.value);//28-03  //  //ZOOZ_1
		}

		switch(KEY.value)
		{

		case DOWN_KEY:
			beep_sound();
					if(dose_option_no<2)
					{
						dose_option_no++;
					}

					else
					{
						dose_option_no=0;
					}

					if(dose_option_no!=prev_option)
					{
					   dose_unit_cursor(prev_option,dose_option_no,dose_rate_unit);
					}
					prev_option = dose_option_no;

				while(KEY.value);
				break;

				case UP_KEY:     //UP
					beep_sound();
					if(dose_option_no)
					{
						dose_option_no--;
					}
					else
					{
						dose_option_no=2;
					}

					if(dose_option_no!=prev_option)
					{
						dose_unit_cursor(prev_option,dose_option_no,dose_rate_unit);
					}

					prev_option = dose_option_no;
					while(KEY.value);
					break;
			case OK_KEY:
				beep_sound();
				G_drug_unit_no=(G_page_no*4)+G_opt_no;    //ZOOZ_1
				exit_flag=0;
				check_flag=1;
				while(KEY.value);
				break;


			case BACK_KEY:
				beep_sound();
				dose_option_no=0;
				prev_option=0;
				exit_flag=0;
				end_opt=0;    //ZOOZ_1
				check_flag=0;
				page_no=0;

				while(KEY.value);
				break;
		}
	}
	return check_flag;
}

/**************************************************************************
 *Function Name :void Main_Menu_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
 *Arguments     :uint8_t page,uint8_t start_opt,uint8_t end_opt
 *Return        :void
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

uint8_t overview_screen(void)
{
	uint8_t page_no=0;
	uint8_t option_no=0;
	uint8_t prev_option = 0;
	uint8_t exit_flag=1;
	uint8_t check_flag=0;
	uint8_t edit_flag=0;
	uint8_t dose_longpress=0;
	uint8_t time_interval=30;//common_bug    //ZOOZ_1
	auto_lock_time=AUTO_EXIT_TIME;//common_bug
	home_flag=0;
	POW.power_status_flag=1;	//26-03    //ZOOZ_1

	if(!KEY.value)
	{
		dose_longpress=0;
	}


	while(exit_flag)
	{
		Power_off();
		if(!ON_Flag)
		{
		  break;//26-03
		}

		else if(POW.power_status_flag)
		{
			home_flag=0;
			POW.power_status_flag=0;//26-03
			dosage_overview_parameter_Frame();
			dosage_parameter_opt_Frame(page_no,option_no,3);
			while(KEY.value);
		}



		switch(KEY.value)
		{

		case DOWN_KEY :
			beep_sound();
					if(!edit_flag)
					{

						if(option_no<3)
						{
							option_no++;
						}
						else
						{
							option_no=0;
						}

						if(option_no!=prev_option)
						{
							dosage_overview_cursor(prev_option,option_no,page_no,dosage_view);
							prev_option = option_no;
						}
					}

					while(KEY.value);
					break;

					case UP_KEY:
						beep_sound();
					if(!edit_flag)
					{
						if(option_no>0)
						{
							option_no--;
						}
						else
						{
							option_no=3;
						}

						if(option_no!=prev_option)
						{
							dosage_overview_cursor(prev_option,option_no,page_no,dosage_view);
							prev_option = option_no;
						}
					}
					while(KEY.value);
					break;
			case OK_KEY:
				beep_sound();
				if(option_no==0)
				{
					Drug_List();
				}
				else if(option_no==1)
				{
					dose_conc_setting();
					dose_conc_setting_ml();   //ZOOZ_1
				}
				else if(option_no==2)
				{
					Double_Decimal_FR_screen(&dose.pat_weight,10000,2);
				}
				else if(option_no==3)
				{
					dosage_fun();
				}

				POW.power_status_flag=1;//26-03

				while(KEY.value);
				break;


			case START_STOP_KEY:
				beep_sound();
				if(dose.flow_rate)    //ZOOZ_1
				{
					normal_run=1;
					DRV8428_ENABLE();
					stepper_Forward();
					MOT.flowrate=dose.flow_rate/10;
					MR_Value_calculate(MOT.flowrate);
					check_flag=2;
					delay_secs(2);
					exit_flag=0;
				}

				if(disc)
				{
				  Alarm(NOT_ENGAGE);
				}
					while(KEY.value);
					break;

			case BACK_KEY:
				beep_sound();
				if(prev_data_flag)    //ZOOZ_1
					{
						check_flag=2;
						exit_flag=0;
						while(KEY.value);
						break;
					}
					else
					{
						check_flag=0;
					}

				exit_flag=0;
				if(dose_longpress==0)
				{
					waitingtime_1=2;
					dose_longpress=1;
					while(KEY.value==BACK_KEY && dose_longpress)
					{
						if(!waitingtime_1)
						{
							G_dose_exit_flag=1;
							dose_longpress=0;
						}

					}


				}
				break;

			case MENU_KEY:

				Main_Menu_Screen();

				while(KEY.value);
				break;


		}
	}
	return check_flag;
}

/**************************************************************************
 *Function Name :void Main_Menu_opt_Frame(uint8_t page,uint8_t start_opt,uint8_t end_opt)
 *Arguments     :uint8_t page,uint8_t start_opt,uint8_t end_opt
 *Return        :void
 *Description	:In this function goto the next parameter in current position
***************************************************************************/

void dosage_range_limit_fun(uint8_t mode,uint16_t current_value)
{

	static uint8_t check_flag=0;
	uint16_t prev_flowrate=0;
	char DR_buffer[6];//24-04-2024

	if(mode==4)
	{

		dose.drug_con_ml=current_value;

		if(dose.drug_con!=0 && dose.drug_con_ml!=0 )
		{
			dose.conc_value=(((float)dose.drug_con/(float)dose.drug_con_ml))*100;
		}

		else
		{
			dose.conc_value=0.0;
		}


		if(dose.conc_value)      //!=temp_con_value)
		{

			Font_Select(ARIAL_12);
			sprintf((char*)DR_buffer,"%.2f",dose.conc_value/100.0);         //27-03
			D_xpos=Dosage_Alignments((uint8_t*)DR_buffer);
			Font_Select(ARIAL_12);
			TFT_writenumber_float(80,38,dose.prev_conc_value,MAIN_FRAME_COL,MAIN_FRAME_COL);
			TFT_writenumber_float(80,38,dose.conc_value,MAIN_FRAME_COL,WHITE);
			dose.prev_conc_value=dose.conc_value;

		}

		else
		{

			dose.conc_value=0.0;
			Font_Select(ARIAL_12);
			TFT_writenumber_float(80,38,dose.conc_value,MAIN_FRAME_COL,WHITE);

		}

	}


	else if(mode==5)
	{

		dose.drug_dos =current_value;

		if(dose.pat_weight!=0 && dose.conc_value!=0 && dose.drug_dos!=0 )
		{
//			Font_Select(ARIAL_14);
//            TFT_writenumber_float(0,70,dose.flow_rate,YELLOW,RED);
//            TFT_Number(0,70,dose.pat_weight,YELLOW,RED);
//            TFT_Number(0,70,dose.drug_dos,YELLOW,RED);


			dose.flow_rate=(((float)dose.pat_weight*(float)dose.drug_dos)/dose.conc_value);
			dose.flow_rate=(dose.flow_rate*time_value[dose_option_no]);
            Font_Select(ARIAL_14);
//          TFT_writenumber_float(0,70,prev_flowrate,YELLOW,RED);
//          Font_Select(ARIAL_14);
//          TFT_writenumber_float(0,70,dose.flow_rate,YELLOW,RED);
		    prev_flowrate=dose.flow_rate;
			 if(dose.flow_rate<=120000)
			 {
			   MOT.flowrate=dose.flow_rate;
			 }

			 else
			 {
			   dose.flow_rate=0;
			 }
		}

		else
		{
			dose.flow_rate=0.0;    //ZOOZ_1
		}


		if(dose.flow_rate>=0)
		{

			Font_Select(ARIAL_12);
			sprintf(DR_buffer,"%.2f",dose.flow_rate/100);         //27-03
			DF_xpos=Dosage_Alignments((uint8_t*)DR_buffer);
		    Font_Select(ARIAL_12);
		    TFT_writenumber_float(37,40,dose.prev_conc_value,MAIN_FRAME_COL,MAIN_FRAME_COL);
		    TFT_writenumber_float(37,40,dose.flow_rate,MAIN_FRAME_COL,WHITE);
			dose.prev_conc_value=dose.flow_rate;

		}



		if ((dose.flow_rate>=120000)&&(check_flag!=2))
		{
			check_flag=2;
			Frame_Footer(RED,YELLOW,(uint8_t*)"    Invalid FR",(uint8_t*)"",0,14);
		}

		else if((dose.flow_rate<=10)&&(check_flag!=1))
		{
			check_flag=1;
			Frame_Footer(RED,YELLOW,(uint8_t*)"    Invalid FR",(uint8_t*)"",0,14);
		}

		else if(dose.flow_rate>10 && dose.flow_rate<=120000)
		{
			if(check_flag!=3)
			{
				check_flag=3;
				Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        to confirm",(uint8_t*)"OK",1,14);
			}
		}


	}

	else if(mode==2)
	{
		dose.pat_weight=current_value;
	}

	if(dose.pat_weight!=0 && dose.conc_value!=0 && dose.drug_dos!=0 )
	{
		dose.flow_rate=(((float)dose.pat_weight*(float)dose.drug_dos)/dose.conc_value);
		dose.flow_rate=(dose.flow_rate*time_value[dose_option_no]);
		MOT.flowrate = dose.flow_rate;
	}

	else
	{
		dose.flow_rate=0.0;    //ZOOZ_1
	}
}

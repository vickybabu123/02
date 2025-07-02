                                                                                                                                                                                                                                                                                                                                                                                                                                                   #include "LPC55S16.h"
#include "Shapes.h"
#include "Color.h"
#include "Keypad.h"
#include "TFT_Commands.h"
#include "TFT_String.h"
#include "Flowrate_Screen.h"
#include "Brand.h"
//#include "Drug_List.h"
#include "Occlusion.h"
//#include "Main_Menu.h"
#include "Bolus_Header.h"
#include "Power_off.h"
#include "Driver_I2C.h"
#include "Driver_Timer.h"
#include "FR_CALC.h"
#include <infused_calculate.h>
#include "Dosage_mode.h"
#include "modes.h"
#include "Alarm.h"
#include "sound.h"
#include <Boot_up.h>

uint8_t prev_mode_val;
uint8_t G_mode_switch_flag=0;
uint8_t G_mode_sw_flag=0;
uint8_t G_switching_flag=0;
extern char disp_para[15];  //ZOOZ_1
extern char dose_rate_unit[3][13];
extern char* drug_unit[4][4];

extern uint8_t dose_option_no;
extern uint8_t G_drug_unit_no;
extern uint8_t auto_lock_time;
extern uint8_t G_warn_flag;
extern uint8_t home_flag;
extern uint8_t G_infusion_modes;
extern uint8_t ON_Flag;	//26-03-2024
extern uint8_t G_last_infusion;
extern uint8_t G_Long_press_back;
extern void VTBI_reset(void);

uint8_t infusion_mode_screen(uint8_t id);

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void infusion_mode_boot()
{
	uint16_t xpos=0;
	uint8_t row=0;
	uint8_t	col=0;

	char* str[2][2]={	{"Flowrate",	"VTBI"},
							{"Dosage",	"Ramp"}
	                        };
	uint32_t box_fill_Color[2][2]={{ORANGE,GRAY},
		 	 	 	 	 	 	 {GRAY,DARK_GRAY}//GRAY+(1000*2)}
 	 	 	 	 	 	 	 	  };
	//Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	//Rectangle(0,0,320,35,NEW_HDR_COL);
	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Infusion Modes");
	Rectangle(0,35,320,170,MAIN_FRAME_COL); // MAIN SHEET
	Font_Select(ARIAL_12);

	for(row=0;row <=1; row++)       //Neon-V
	{
		for(col=0;col <=1; col++)
		{
			TFT_ST7789V__rectangle_curve(15+(15*col)+(137*col),55+(15*row)+(73*row),73,137,1,box_fill_Color[row][col]);
			xpos=Letters_Alignments(15+(15*col)+(137*col),15+(15*col)+(137*col)+137,(uint8_t*)str[row][col],0);
			TFT_String(xpos,55+(15*row)+(73*row)+30,(uint8_t*)str[row][col],box_fill_Color[row][col],BLACK);
		}
	}
	prev_mode_val=0;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void infusion_mode_boot_cursor(int current_val)
{
	uint8_t row=0,col=0,str_val;
	uint16_t xpos=0;

	char
	* str[2][2]={	{"Flowrate",	"VTBI"},
							{"Dosage",	"Ramp"}
					   };
	if(prev_mode_val !=current_val)
	{

	Font_Select(ARIAL_12);

	row = prev_mode_val / 2;
	col = prev_mode_val % 2;

	TFT_ST7789V__rectangle_curve(15+(15*col)+(137*col),55+(15*row)+(73*row),73,137,1,GRAY);
	xpos=Letters_Alignments(15+(15*col)+(137*col),15+(15*col)+(137*col)+137,(uint8_t*)str[row][col],0);
	TFT_String(xpos,55+(15*row)+(73*row)+30,(uint8_t*)str[row][col],GRAY,BLACK);

	row = current_val / 2;
	col = current_val % 2;

	TFT_ST7789V__rectangle_curve(15+(15*col)+(137*col),55+(15*row)+(73*row),73,137,1,ORANGE);
	xpos=Letters_Alignments(15+(15*col)+(137*col),15+(15*col)+(137*col)+137,(uint8_t*)str[row][col],0);
	TFT_String(xpos,55+(15*row)+(73*row)+30,(uint8_t*)str[row][col],ORANGE,BLACK);
	prev_mode_val =current_val;
	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t infusion_mode_screen(uint8_t id)
{
	uint8_t cursor=0;
	uint8_t inf_loop=1;
	uint8_t check_flag=0;
	home_flag=0;
    POW.power_status_flag=1;
	auto_lock_time=AUTO_EXIT_TIME;//common_bug

	while(inf_loop)
	{
		Power_off();

		if(!ON_Flag)
		{
			break;//26-03
		}

		else if(POW.power_status_flag)
		{
			POW.power_status_flag=0;//26-03
			infusion_mode_boot();
			while(KEY.value);//28-03
		}

//		 Font_Select(ARIAL_14);
//		 TFT_Number(70,70,160,YELLOW,RED);
//		 delay_secs(3);

//		if(KEY.value)
//		{
//		 //while(KEY.value);
//		   auto_lock_time=AUTO_EXIT_TIME;
//		}
//		if(!auto_lock_time)
//		{
//			inf_loop=0;
//		}

		switch (KEY.value)
		{
		case OK_KEY :

			beep_sound();

			if( (G_infusion_modes!=cursor)  || (!id) )
			{
			    //Font_Select(ARIAL_14);
				//TFT_Number(70,70,20,YELLOW,RED);

				VTBI_reset();

				Dosage_value_reset();
				G_infusion_modes=cursor;
				G_Long_press_back=0;
				G_switching_flag=1;

				if(id)
				{
					ON_Flag=0;
					G_mode_switch_flag=1;
					G_mode_sw_flag=1;
					inf_loop=0;
				}
				inf_loop=0;
				//TFT_Number(70,70,20,YELLOW,RED);
			}

			else
			{
				cursor=0;
				caution_info("Already Selected");
				delay_secs(2);
				POW.power_status_flag=1;
			}

			while(KEY.value);
			break;

		case UP_KEY :

			if(cursor==2)
			{
				beep_sound();
				cursor=0;
				infusion_mode_boot_cursor(cursor);
				while(KEY.value);
			}
			break;

		case DOWN_KEY :

			if(cursor<=1 )
			{
				beep_sound();
				cursor=2;
				infusion_mode_boot_cursor(cursor);
				while(KEY.value);
			}
			break;

		case LEFT_KEY :

			if(cursor==1)
			{
				beep_sound();
				cursor=0;
				infusion_mode_boot_cursor(cursor);
				while(KEY.value);
			}
			break;

		case RIGHT_KEY :

			if(cursor==0)
			{
				beep_sound();
				cursor=1;
				infusion_mode_boot_cursor(cursor);
				while(KEY.value);
			}
			break;

		case BACK_KEY:

			if( (!id) )//||    //(!check_flag) )
			{
				beep_sound();
				check_flag=1;
				inf_loop=0;
			//	G_infusion_modes=cursor;
				while(KEY.value);
			}
			else
			{
				inf_loop=0;
			}
			break;

		}

	}
		G_warn_flag=0;
		infuse_clr();
		//TFT_Number(70,90,G_infusion_modes,NAVY,WHITE);

		return check_flag;

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t  previous_data(uint8_t mode)
{
	uint8_t check_flag=0;
	uint8_t pd_loop=1;
//  previous_data_frame();
	auto_lock_time=AUTO_EXIT_TIME;
	POW.power_status_flag=1;


	while(pd_loop)
	{

		Power_off();

		if(!ON_Flag)
		{
			break;//26-03
		}

		else if(POW.power_status_flag)  //ZOOZ_1
		{
			POW.power_status_flag=0;
			previous_data_frame(mode);
			while(KEY.value);//28-03
		}

		if(KEY.value)//common_bug//ZOOZ_1
		{
			auto_lock_time=AUTO_EXIT_TIME;
		}

		 if((!auto_lock_time) && (G_last_infusion))
		{
			G_last_infusion=0;
			pd_loop=0;
		}


	switch(KEY.value)
	{

		case LEFT_KEY:

		beep_sound();
		check_flag=1;
		G_mode_switch_flag=0;
		pd_loop=0;
		break;

		case RIGHT_KEY:

		beep_sound();
		check_flag=0;
		pd_loop=0;
		break;

		case BACK_KEY:  //12-06-2024

		beep_sound();
		pd_loop=0;
		break;
	}
 }
	return check_flag;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void previous_data_frame(uint8_t mode)
{
	Rectangle(0,0,320,240,MAIN_FRAME_COL);
		TFT_ST7789V__rectangle_curve(10,68-17,(41*2)+1+20,300,0,LIGHT_GRAY);
		Font_Select(ARIAL_14);
		if(mode==0)
		{
			//XPOS=Letters_Alignments(55+10,INITIAL_TEXT_POS+(1*VER_TEXT_SPACE)-5+5-3-17,(uint8_t *)"Continue With Old",0);
			TFT_String(55+10,INITIAL_TEXT_POS+(1*VER_TEXT_SPACE)-5+5-3-17,(uint8_t*)"Continue With Old",LIGHT_GRAY,BLACK);
			//XPOS=Letters_Alignments(55+10+30-5,INITIAL_TEXT_POS+(2*VER_TEXT_SPACE)+5-5-3-17,(uint8_t *)"Infusion Data",0);
			TFT_String(55+10+30-5,INITIAL_TEXT_POS+(2*VER_TEXT_SPACE)+5-5-3-17,(uint8_t*)"Infusion Data",LIGHT_GRAY,BLACK);


		}
		else if(mode==1)
		{
			//XPOS=Letters_Alignments(55+10,INITIAL_TEXT_POS+(1*VER_TEXT_SPACE)-5+5-3-17,(uint8_t *)"Do you want to clear",0);
			TFT_String(55+10,INITIAL_TEXT_POS+(1*VER_TEXT_SPACE)-5+5-3-17,(uint8_t*)"Do you want clear",LIGHT_GRAY,BLACK);
			//XPOS=Letters_Alignments(55+10+30-5,INITIAL_TEXT_POS+(2*VER_TEXT_SPACE)+5-5-3-17,(uint8_t *)" infused data?",0);
			TFT_String(55+10+30-5,INITIAL_TEXT_POS+(2*VER_TEXT_SPACE)+5-5-3-17,(uint8_t*)"infused data?",LIGHT_GRAY,BLACK);
		}
		Font_Select(ARIAL_14);
		Rectangle(0,206,320,34,NEW_FTR_COL);

		TFT_String(90-40,210+2,(uint8_t *)"Yes",NEW_FTR_COL,HDR_TXT_COL);
		TFT_String(220+20+5,210+2,(uint8_t *)"No",NEW_FTR_COL,HDR_TXT_COL);


		TFT_ST7789V_lcd_drawcircle1(20,223,15,MAIN_FRAME_COL,MAIN_FRAME_COL);    //	 Left Circle

		TFT_ST7789V_left_Right_arrow_14_arial(215,15,0,MAIN_FRAME_COL,WHITE);    //	Left Arrow

		TFT_ST7789V_lcd_drawcircle1(60+210+20+10,223,15,MAIN_FRAME_COL,MAIN_FRAME_COL);    // Right Circle

		TFT_ST7789V_left_Right_arrow_14_arial(215,59+210+20+10,1,MAIN_FRAME_COL,WHITE);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void  write_current_data(uint8_t mode)
{
	EEPROM_datawrite(EEPROM_LAST_IFMODE,mode,1);

	EEPROM_datawrite(EEPROM_PD_FRFLOWRATE,MOT.flowrate,2);//EEPROM_PD_FRFLOWRATE
	EEPROM_datawrite(EEPROM_PD_FRINFUSED_ml,INFUSED.ml,2);


if(mode<2)
{

	EEPROM_datawrite(EEPROM_PD_FRINFUSED_SEC,INFUSED.sec,2);
	if(mode==1)
	{
		EEPROM_datawrite(EEPROM_PD_FRVOLUME,MOT.volume,4);
	}
}

	else if(mode==2)
	{
		EEPROM_datawrite(EEPROM_PD_DRDRUG_SELECT,dose.drug_select_no,2);
		EEPROM_datawrite(EEPROM_PD_DRCONC_VALUE,(uint16_t)dose.conc_value,4);
		EEPROM_datawrite(EEPROM_PD_DRPAT_WEIGHT,dose.pat_weight,4);
		EEPROM_datawrite(EEPROM_PD_DRDRUG_DOS,(uint16_t)dose.drug_dos,4);

		for(int8_t lop_cnt=0;lop_cnt<10;lop_cnt++)
		{
			EEPROM_datawrite(EEPROM_PD_DRdisp_para+lop_cnt,disp_para[lop_cnt],1);
		}

		EEPROM_datawrite(EEPROM_PD_DRrate_unit,dose_option_no,1);
		EEPROM_datawrite(EEPROM_Drug_unit,G_drug_unit_no,1);
	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void  read_last_data(uint8_t mode)
{

	MOT.flowrate= EEPROM_dataread(EEPROM_PD_FRFLOWRATE,2);//EEPROM_PD_FRFLOWRATE
	INFUSED.ml= EEPROM_dataread(EEPROM_PD_FRINFUSED_ml,2);

	if(mode<2)
	{

		INFUSED.sec= EEPROM_dataread(EEPROM_PD_FRINFUSED_SEC,2);
		if(mode==1)
		{
			MOT.volume= EEPROM_dataread(EEPROM_PD_FRVOLUME,4);
		}
	}

	else if(mode==2)
	{
		dose.drug_select_no=EEPROM_dataread(EEPROM_PD_DRDRUG_SELECT,2);
		dose.conc_value =	EEPROM_dataread(EEPROM_PD_DRCONC_VALUE,4);
		dose.pat_weight = 	EEPROM_dataread(EEPROM_PD_DRPAT_WEIGHT,4);
		dose.drug_dos =	EEPROM_dataread(EEPROM_PD_DRDRUG_DOS,4);
		dose.flow_rate=MOT.flowrate;

		for(uint8_t lp_cnt=0;lp_cnt<10;lp_cnt++)
		{
			disp_para[lp_cnt] =EEPROM_dataread(EEPROM_PD_DRdisp_para+lp_cnt,1);
		}

		dose_option_no =EEPROM_dataread(EEPROM_PD_DRrate_unit,1);
		G_drug_unit_no=EEPROM_dataread(EEPROM_Drug_unit,1);

		memset(dose_rate_unit, 0, sizeof(dose_rate_unit));

		strcat(dose_rate_unit[0],drug_unit[G_drug_unit_no/4][G_drug_unit_no%4]);
		strcat(dose_rate_unit[0],"/");
		strcat(dose_rate_unit[0],"kg");
		strcat(dose_rate_unit[0],"/");

		strcpy(dose_rate_unit[1],dose_rate_unit[0]);
		strcpy(dose_rate_unit[2],dose_rate_unit[0]);

		strcat(dose_rate_unit[0],"h");
		strcat(dose_rate_unit[1],"min");
		strcat(dose_rate_unit[2],"24h");
	}
}

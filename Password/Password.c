#include "LPC55S16.h"
#include "Color.h"
#include "Keypad.h"
#include "TFT_String.h"
#include "TFT_Commands.h"
#include "Shapes.h"
#include "Flowrate_Screen.h"
#include "Power_off.h"
#include "Password.h"
#include"Driver_Timer.h"
#include "sound.h"

uint8_t sec_count;
uint8_t attempt_count;
uint8_t attempt_count1;
uint8_t password_one_flag=0;
uint8_t password_two_flag=0;
uint8_t password_three_flag=0;
uint8_t password_four_flag=0;

extern uint8_t ON_Flag;

pas_var password ;
uint64_t password_set[4]={4321,1234,9870,0116};
extern void passcode_header_footer_popup_frame();
extern void bolus_complete_screen(uint8_t screen, uint32_t color);//common_bug  //ZOOZ_1

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Digit_Spiliting_passcode(uint16_t Value)
 {
	uint8_t loop_count=0;
	password.position_3=0;
	password.letter_3[0]='0';
	 if(Value==0)
	    {
	    	for(loop_count=0;loop_count<4;loop_count++)
	    	{
	    		password.array_dig_2[password.position_3]=0;
	    		password.position_3++;
	    	}
	    }

	 else
	 {
	 while(Value>0)
	     {
		 password.array_dig_2[password.position_3]=Value%10;
	     Value=Value/10;
	     password.position_3++;
	     }
	 }
    }

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint16_t Passcode(uint16_t mode)
{

	uint8_t Cursor_no=0;
	uint8_t prev_cursor_no=0;
	uint16_t  passcode=0000;
	uint8_t trial_count=0;
	uint16_t ypos_3=0;
	char pass_buffer[2]={'\0','\0'};
    uint8_t check_flag=0; //23-03
    uint8_t password_variable=1;

     if((attempt_count)) //23-03
     {

		passcode_header_footer_frame();

				Font_Select(ARIAL_14);
				//TFT_String(70,70,(uint8_t *)"Attempt after ",MAIN_FRAME_COL,WHITE);
				TFT_String_align(0,319,70,(uint8_t *)"Attempt after",0,MAIN_FRAME_COL,WHITE);
				TFT_String_align(0,305,160,(uint8_t *)"secs",0,MAIN_FRAME_COL,WHITE);
				//TFT_String(125,160,(uint8_t *)"secs ",MAIN_FRAME_COL,WHITE);
				sec_count=3;
				while(sec_count)
				{
					if(password.previous_atmpt_count!=attempt_count)
						{

							TFT_Number(140,120,password.previous_atmpt_count,MAIN_FRAME_COL,MAIN_FRAME_COL);
							TFT_Number(140,120,attempt_count,MAIN_FRAME_COL,ORANGE);
							password.previous_atmpt_count=attempt_count;
							check_flag=0; //23-03

						}
					if(KEY.value==BACK_KEY)	break;// return; //23-03
				}
     }

    else if((!attempt_count)) //23-03
    {

	POW.power_status_flag=1;
	Digit_Spiliting_passcode(0);
	check_flag=0; //23-03
	prev_cursor_no=0;

	while(password_variable)
	{


		Power_off();	//26-03

		if(!ON_Flag)
		{
			break;
		}		//26-03
		else if(POW.power_status_flag)
		{

			POW.power_status_flag=0;
			passcode_header_footer_frame();
			Pc_split_frame();
			password_option_frame(Cursor_no);
			Left_Right_Indi(3-Cursor_no,0);
			while(KEY.value);

		}

		switch(KEY.value)
		{

		case RIGHT_KEY:

		beep_sound();
		if(Cursor_no<3)
		{
			Cursor_no++;
			password_option_scroll(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);

			if(Cursor_no !=0 && Cursor_no !=2 )
			{
				Left_Right_Indi(3-Cursor_no,0);
			}

		}
		prev_cursor_no=Cursor_no;

		while(KEY.value);
		break;

		case LEFT_KEY:

		beep_sound();
		if(Cursor_no>0)
		{
			Cursor_no--;
			password_option_scroll(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);

			if(Cursor_no !=1 && Cursor_no !=3 )
			{
				Left_Right_Indi(3-Cursor_no,0);
			}
		}
		prev_cursor_no=Cursor_no;

		while(KEY.value);
		break;

		case UP_KEY:

		beep_sound();
		password_up_key_fun(Cursor_no);
		while(KEY.value);
		break;

		case DOWN_KEY:

		beep_sound();
		password_down_key_fun(Cursor_no);
		while(KEY.value);
		break;


		case OK_KEY:

		beep_sound();
		passcode=password.array_dig_2[0]*1000+password.array_dig_2[1]*100+password.array_dig_2[2]*10+password.array_dig_2[3]*1;
		passcode_header_footer_popup_frame();

		if(passcode== password_set[mode])
		{
			check_flag=1;
		}

		else if((mode) && (passcode== password_set[mode+1]))
		{
			check_flag=2;
		}

	   // TFT_Number(80,70,check_flag,YELLOW,RED);

		if(trial_count<3)
		{
			if(check_flag)
			{
				password_variable=0;
			}

			else
			{
				while(KEY.value);
				pop_up_info_frame(2,WHITE);
				trial_count++;
				Digit_Spiliting_passcode(0);
				Cursor_no=0;
				prev_cursor_no=0;
				POW.power_status_flag=1;
			}
		}

		else
		{
			Font_Select(ARIAL_14);
			//TFT_String(70,70,(uint8_t *)"attempt after ",MAIN_FRAME_COL,WHITE);

			TFT_String_align(0,319,70,(uint8_t *)"Attempt after",0,MAIN_FRAME_COL,WHITE);
			TFT_String_align(0,319,120,(uint8_t *)"1",0,MAIN_FRAME_COL,ORANGE);
			TFT_String_align(0,317,160,(uint8_t *)"min",0,MAIN_FRAME_COL,WHITE);

			//TFT_String(140,120,(uint8_t *)"1",MAIN_FRAME_COL,ORANGE);
			//TFT_String(125,160,(uint8_t *)"min ",MAIN_FRAME_COL,WHITE);

			delay_us(1000);
			password_variable=0;
			attempt_count=60;
			check_flag=0; //23-03
		}


		while(KEY.value);
		break;

		case BACK_KEY:
		beep_sound();
		password_variable=0;
		password_one_flag=0;
		check_flag=0; //23-03
		while(KEY.value);
		break;

		} //23-03

		}
    }
return check_flag; //23-03
}

void password_up_key_fun(uint8_t Cursor_no )
{
	uint16_t ypos_3=0;
	char pass_buffer[2]={'\0','\0'};
			if(password.array_dig_2[Cursor_no]<9)
			{
				Font_Select(CALIBRI_43);
				pass_buffer[0]=password.array_dig_2[Cursor_no]+48;
				ypos_3=Letters_Alignments(70+(45*(Cursor_no)),
							             70+(45*(Cursor_no+1)), (uint8_t*)pass_buffer,0);
				TFT_Number(ypos_3,CALIB_EDT_YPOS,password.array_dig_2[Cursor_no],CURSOR_COL,CURSOR_COL);
				password.array_dig_2[Cursor_no]++;
				pass_buffer[0]=password.array_dig_2[Cursor_no]+48;
			    ypos_3=Letters_Alignments(70+(45*(Cursor_no)),
						                 70+(45*(Cursor_no+1)), (uint8_t*)pass_buffer,0);
				TFT_Number(ypos_3,CALIB_EDT_YPOS,password.array_dig_2[Cursor_no],CURSOR_COL,BLACK);
			}

}

void password_down_key_fun(uint8_t Cursor_no)
{
	uint16_t ypos_3=0;
	char pass_buffer[2]={'\0','\0'};

	if(password.array_dig_2[Cursor_no]>0)
	{
		Font_Select(CALIBRI_43);
		pass_buffer[0]=password.array_dig_2[Cursor_no]+48;
		ypos_3=Letters_Alignments(70+(45*(Cursor_no)),
								70+(45*(Cursor_no+1)), (uint8_t*)pass_buffer,0);
		TFT_Number(ypos_3,CALIB_EDT_YPOS,password.array_dig_2[Cursor_no],CURSOR_COL,CURSOR_COL);
		password.array_dig_2[Cursor_no]--;
		pass_buffer[0]=password.array_dig_2[Cursor_no]+48;
		ypos_3=Letters_Alignments(70+(45*(Cursor_no)),
								70+(45*(Cursor_no+1)), (uint8_t*)pass_buffer,0);
		TFT_Number(ypos_3,CALIB_EDT_YPOS,password.array_dig_2[Cursor_no],CURSOR_COL,BLACK);
	}
}

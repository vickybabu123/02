#include "LPC55S16.h"
#include "Color.h"
#include "TFT_Commands.h"
#include "TFT_String.h"
#include "Keypad.h"
#include "Driver_Timer.h"
#include <Shapes.h>
#include "Calibration_Screen.h"
#include "Power_off.h"
#include  "sound.h"
#include "Flowrate_Screen.h"
#include <Boot_up.h>



volatile uint8_t array_dig2[6];
extern uint8_t ON_Flag;

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Calibration_screen()
{
        // Rectangle(0,0,320,240,MAIN_FRAME_COL);
		 CLRSCR(MAIN_FRAME_COL);
         Rectangle(0,0,320,35,NEW_HDR_COL);
	     Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Pressure_Calibration");

	     Font_Select(CALIBRI_48);
         TFT_Number(48,85,2010,MAIN_FRAME_COL,WHITE);

//*********************************4_Menu_Alignments***********************************//
         Rectangle(7,118,290,0,BLACK);
         Rectangle(7,162,290,0,BLACK);
         TFT_ST7789V__rectangle_curve(119,5,290,40,0,LIGHT_GRAY);  //Rectangle Curve Option 1

         Font_Select(ARIAL_14);
         TFT_String(131,10,(uint8_t *)"0 PSI",LIGHT_GRAY,BLACK);

         TFT_String(131,180,(uint8_t *)"-",LIGHT_GRAY,BLACK);

         TFT_String(131,210,(uint8_t *)"2010",LIGHT_GRAY,BLACK);

         TFT_String(172,10,(uint8_t *)"20 PSI",MAIN_FRAME_COL,BLACK);

         TFT_String(172,180,(uint8_t *)"-",MAIN_FRAME_COL,BLACK);

         TFT_String(172,210,(uint8_t *)"2560",MAIN_FRAME_COL,BLACK);

    	 Frame_Footer(NEW_FTR_COL,BLACK,(uint8_t*)"Press        to change",(uint8_t*)"OK",2,14);

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Zero_PSI_Calibration()
{
     //Rectangle(0,0,320,240,MAIN_FRAME_COL);
	 CLRSCR(MAIN_FRAME_COL);
     Rectangle(0,0,320,35,NEW_HDR_COL);

    Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"0 PSI Calibration");


    Font_Select(CALIBRI_43);
    TFT_String(63,85,(uint8_t *)2010,MAIN_FRAME_COL,WHITE);

   Rectangle(7,162,290,0,BLACK);
   TFT_ST7789V__rectangle_curve(165,5,290,34,0,LIGHT_GRAY);  //Rectangle Curve Option 1

   Frame_Footer(NEW_FTR_COL,BLACK,(uint8_t*)"Press        to change",(uint8_t*)"OK",2,14);

   Font_Select(ARIAL_14);
   TFT_String(36+(4*34),110,(uint8_t*)"Calibrate",LIGHT_GRAY,BLACK);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Warning_Frame()
{
   // Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
    Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"0 PSI Calibration");
    TFT_String(65,25,(uint8_t *)"i)  Remove the Syringe",MAIN_FRAME_COL,YELLOW);
    TFT_String(105,25,(uint8_t *)"ii) Don't touch the",MAIN_FRAME_COL,YELLOW);
    TFT_String(135,45,(uint8_t *)"Plunger Disc",MAIN_FRAME_COL,YELLOW);
    Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        Confirm",(uint8_t*)"OK",1,14);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Indication_Frame()
{
 //Rectangle(0,0,320,240,MAIN_FRAME_COL);
 CLRSCR(MAIN_FRAME_COL);
 TFT_ST7789V__Bottom_curve(0,30,320-60,30,500,HDR_BG_COL);                                         //DRAW A RECTANGULAR CURVE IN THE TOP OF THE TFT DISPLAY

  Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"0 PSI Calibration");

 TFT_ST7789V__rectangle_curve(60,30,255,110,0,LIGHT_GRAY);

 TFT_String(105,100,(uint8_t *)"Calibrated",LIGHT_GRAY,BLACK);

 Frame_Footer(YELLOW,BLACK,(uint8_t*)"        Confirm",(uint8_t*)"OK",1,14);
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t edit_screen(uint16_t *Edit_value,uint8_t screen,uint16_t max_value)

{
	        uint8_t prev_cursor_no=1;
			uint8_t space=0;
			uint8_t Cursor_no=2;
			uint8_t max_arr[4];

			uint16_t result=0;
			uint8_t condition=1;
			uint8_t xpos=0;
			uint16_t Value=0;
			uint8_t Err_flag=0;
		//	uint8_t Err_Chk_flag=0;
			uint8_t loop_cnt=0;
			Value=*Edit_value;
			char letter1[2]={'\0','\0'} ;



			edit_split_frame(screen);
			Digit_Spiliting1(Value,Cursor_no,prev_cursor_no);
			Left_Right_Indi(Cursor_no,0);
			while(max_value)
			{
				max_arr[loop_cnt]=max_value%10;
				max_value=max_value/10;
				loop_cnt++;
			}

			edit_option(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
			prev_cursor_no=2;


			while(KEY.value)
			{

			}

			while(condition)
			{
				Power_off();	//26-03
				if(!ON_Flag)
				{
					break;
				}		//26-03

				else if(POW.power_status_flag)
				{
					POW.power_status_flag=0;
					edit_split_frame(screen);
					result=(array_dig2[3]*1000)+(array_dig2[2]*100)+(array_dig2[1]*10)+array_dig2[0];
					Digit_Spiliting1(result,Cursor_no,prev_cursor_no);
					Left_Right_Indi(Cursor_no,0);
					edit_option(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
					while(KEY.value); //23-03
				}

				switch(KEY.value)
				{
					case LEFT_KEY:
						beep_sound();
					if(Cursor_no<3)
					{
						Cursor_no++;
						edit_option(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
						if(Cursor_no !=2 && Cursor_no !=0 )
						{
								Left_Right_Indi(Cursor_no,0);
						}
					}
					prev_cursor_no=Cursor_no;
					while(KEY.value);
					break;

					case RIGHT_KEY:
						beep_sound();
					if(Cursor_no>0)
					{
						Cursor_no--;
						edit_option(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
						if(Cursor_no !=1 && Cursor_no !=3 )
						{
							   Left_Right_Indi(Cursor_no,0);
						}
					}
					prev_cursor_no=Cursor_no;
					while(KEY.value);
					break;

					case UP_KEY:
						beep_sound();
						if(Cursor_no<2)
						{
							space=15;

						}

						else
						{
							space=0;

						}
						Font_Select(CALIBRI_43);
						letter1[0]=array_dig2[Cursor_no]+48;
						xpos=Letters_Alignments(63+(45*(3-Cursor_no))+space,
						106+(45*(3-Cursor_no))+space, (uint8_t*)letter1,0);
						TFT_Number(xpos,CALIB_EDT_YPOS,array_dig2[Cursor_no],CURSOR_COL,CURSOR_COL);

						if( (Cursor_no==3) || (Cursor_no==1) )
							{
								if(array_dig2[Cursor_no-1]<=max_arr[Cursor_no-1])
								{
									if(array_dig2[Cursor_no]<max_arr[Cursor_no])
									{
										array_dig2[Cursor_no]++;
									}
									else
									{
										WARN_SOUND(1,1,2);
									}
								}
								else
								{
									if(array_dig2[Cursor_no]<max_arr[Cursor_no]-1)
									{
										array_dig2[Cursor_no]++;
									}
									else
									{
										WARN_SOUND(1,1,2);
									}
								}
							}

							else if((Cursor_no==2)||(Cursor_no==0))
							{
								if(array_dig2[Cursor_no+1]<max_arr[Cursor_no+1])
								{
									if(array_dig2[Cursor_no]<9)
									{
										array_dig2[Cursor_no]++;
									}
									else
									{
										WARN_SOUND(1,1,2);
									}
								}

								else
								{
									if(array_dig2[Cursor_no]<max_arr[Cursor_no])
									{
										array_dig2[Cursor_no]++;
									}
									else
									{
										WARN_SOUND(1,1,2);
									}
								}
							}

					Font_Select(CALIBRI_43);
					letter1[0]=array_dig2[Cursor_no]+48;
					xpos=Letters_Alignments(63+(45*(3-Cursor_no))+space,
					106+(45*(3-Cursor_no))+space, (uint8_t*)letter1,0);
					TFT_Number(xpos,CALIB_EDT_YPOS,array_dig2[Cursor_no],CURSOR_COL,BLACK);

					while(KEY.value);
					break;

					case DOWN_KEY:
						beep_sound();

						if(Cursor_no<2)
						{
							space=15;

						}

						else
						{
							space=0;
						}
						Font_Select(CALIBRI_43);
						letter1[0]=array_dig2[Cursor_no]+48;
						xpos=Letters_Alignments(63+(45*(3-Cursor_no))+space,
						106+(45*(3-Cursor_no))+space, (uint8_t*)letter1,0);
						TFT_Number(xpos,CALIB_EDT_YPOS,array_dig2[Cursor_no],CURSOR_COL,CURSOR_COL);

					if(((Cursor_no==2)||(Cursor_no==0) )&& screen==1)
					{
						if(array_dig2[Cursor_no]>0)// 1 change to 0 //23-03
						{

							array_dig2[Cursor_no]--;

						}
						else
						{
							WARN_SOUND(1,1,2);
						}
					}
					else
					{

						if(array_dig2[Cursor_no]>0)
						{
							array_dig2[Cursor_no]--;
						}
						else
						{
							WARN_SOUND(1,1,2);
						}
					}

					Font_Select(CALIBRI_43);
					letter1[0]=array_dig2[Cursor_no]+48;
					xpos=Letters_Alignments(63+(45*(3-Cursor_no))+space,
					106+(45*(3-Cursor_no))+space, (uint8_t*)letter1,0);
					TFT_Number(xpos,CALIB_EDT_YPOS,array_dig2[Cursor_no],CURSOR_COL,BLACK);



					while(KEY.value);
					break;

					case OK_KEY:
					beep_sound();
					result=(array_dig2[3]*1000)+(array_dig2[2]*100)+(array_dig2[1]*10)+array_dig2[0];
					*Edit_value=result;
					Err_flag=1;
					condition=0;
					while(KEY.value);
					break;

					case BACK_KEY:
					beep_sound();
					condition=0;
					Err_flag=0;
					while(KEY.value);
					break;


				}
			}
			return Err_flag;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void edit_split_frame(uint8_t screen)
{
uint8_t loop_count=0;
//Rectangle(0,0,320,240,MAIN_FRAME_COL);
CLRSCR(MAIN_FRAME_COL);
for(loop_count=0;loop_count<=2;loop_count++)
{
	Rectangle(62+(45*loop_count),68,0,115,BLACK);
}

for(loop_count=2;loop_count<5;loop_count++)
{
	Rectangle(62+15+(45*loop_count),68,0,115,BLACK);
}
Font_Select(ARIAL_9);
	if(screen==1)
	{

	Font_Select(ARIAL_12);//common_bug3
	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Date & Month");
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        Confirm",(uint8_t*)"OK",1,14);

	TFT_String(80,40,(uint8_t*)"D",MAIN_FRAME_COL,OLIVE);
	TFT_String(125,40,(uint8_t*)"D",MAIN_FRAME_COL,OLIVE);

	TFT_String(185,40,(uint8_t*)"M",MAIN_FRAME_COL,OLIVE);
	TFT_String(230,40,(uint8_t*)"M",MAIN_FRAME_COL,OLIVE);
	}
	else if(screen==2)
	{
		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Time");
		Font_Select(ARIAL_9);//common_bug3
		TFT_String(190,16,(uint8_t*)"(HH:MM)",NEW_HDR_COL,WHITE);

		Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        Confirm",(uint8_t*)"OK",1,14);
		TFT_String(80,40,(uint8_t*)"H",MAIN_FRAME_COL,WHITE);
		TFT_String(125,40,(uint8_t*)"H",MAIN_FRAME_COL,WHITE);

		TFT_String(185,40,(uint8_t*)"M",MAIN_FRAME_COL,WHITE);
		TFT_String(230,40,(uint8_t*)"M",MAIN_FRAME_COL,WHITE);
	}
	else if(screen==3)
	{
		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"20 PSI edit");
		Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"          to edit",(uint8_t*)"OK",1,14);
	}
	else if(screen==4)
	{
		Font_Select(ARIAL_12);//common_bug3
		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Month and Year");
		Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"        Confirm",(uint8_t*)"OK",1,14);

		TFT_String(80,40,(uint8_t*)"M",MAIN_FRAME_COL,OLIVE);
		TFT_String(125,40,(uint8_t*)"M",MAIN_FRAME_COL,OLIVE);

		TFT_String(185,40,(uint8_t*)"Y",MAIN_FRAME_COL,OLIVE);
		TFT_String(230,40,(uint8_t*)"Y",MAIN_FRAME_COL,OLIVE);
	}
	else
	{
		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Edit Collected mL");
		Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press         to Confirm",(uint8_t*)"OK",2,14);
	}

    if((screen==2))//common_bug
    {
//		TFT_String(185,40,(uint8_t*)"Y",MAIN_FRAME_COL,OLIVE);
//		TFT_String(230,40,(uint8_t*)"Y",MAIN_FRAME_COL,OLIVE);
		Font_Select(ARIAL_20);
		TFT_String(156,112,(uint8_t*)":",MAIN_FRAME_COL,WHITE);
	}
    else
    {
    	Font_Select(ARIAL_20);
    	TFT_String(156,119,(uint8_t*)"-",MAIN_FRAME_COL,WHITE);
    }

}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void Digit_Spiliting1(uint16_t Value,uint8_t cur_no,uint8_t prev_no)
 {
	uint8_t space=0;
	uint8_t loop_count=0;
    uint8_t position_2=0;
	char letter1[2]={'\0','\0'} ;


    uint16_t ypos1=0;

    if(!Value)
	{
		for(position_2=0;position_2<=3;position_2++)
		{
			array_dig2[position_2]=0;
		}
	}

	while(Value>0)
	{
		 array_dig2[position_2]=Value%10;
		 Value=Value/10;
		 position_2++;
	}

    if(position_2==3)
    {
    	array_dig2[3]=0;
    }

    else if(position_2==2)
    {
    	array_dig2[2]=0;
    	array_dig2[3]=0;
    }
    else if(position_2==1)
    {
    	array_dig2[1]=0;
    	array_dig2[2]=0;
    	array_dig2[3]=0;
    }

//    Font_Select(ARIAL_14);
//    TFT_Number(70,130,position_2,NAVY,WHITE);
//    delay_secs(5);

	for(loop_count=0;loop_count<=3;loop_count++)
     {

		if(loop_count==0|| loop_count==1)
		{
			space=15;
		}

		else
		{
			space=0;
		}

      Font_Select(CALIBRI_43);

      letter1[0] = array_dig2[loop_count]+48;

      ypos1=Letters_Alignments(63+(45*(3-loop_count))+space,
    		  	  	  	  	  	  	  	  	  106+(45*(3-loop_count))+space, (uint8_t*)letter1,0);

   // Font_Select(CALIBRI_43);

      if(loop_count !=cur_no && loop_count !=prev_no )
      {
    	 TFT_Number(ypos1,CALIB_EDT_YPOS,array_dig2[loop_count],MAIN_FRAME_COL,WHITE);
      }

//    if(loop_count==3)
//    {
//    	while(1);
//    }

//      delay_secs(3);

    }
  }

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void edit_option(uint8_t current_cur_no,uint8_t prev_cursor_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL,uint32_t UP_ARROW_ERASE)
{
	uint32_t back_colour   = 0;
	uint32_t text_colour		= 0;
	uint8_t loop= 0;
	uint8_t Cursor_no		= 0;
	uint8_t space				= 0;
	uint32_t arrow_bg_color	= 0;
	uint32_t arrow_fill_color =  0;
	uint8_t ypos1=0;
	char letter1[2]={'\0','\0'} ;

	for(loop = 0; loop<2; loop++)
	{
		if(!loop)
		{
			back_colour			= MAIN_FRAME_COL;
			text_colour 		= WHITE;
			Cursor_no			= prev_cursor_no;
			arrow_bg_color		= MAIN_FRAME_COL;
			arrow_fill_color	= MAIN_FRAME_COL;
		}
		else
		{
			back_colour 		= LIGHT_GRAY;
			text_colour  		= BLACK;
			Cursor_no			= current_cur_no;
			arrow_bg_color		= LIGHT_GRAY;
			arrow_fill_color	= BLACK;
		}

		if(Cursor_no<2)
		{
			space=15;
		}
		else
		{
			space=0;
		}

		TFT_ST7789V__rectangle_curve(1+62+(45*(3-Cursor_no))+space,64,125,43,0,back_colour);

		Font_Select(CALIBRI_43);

		letter1[0]=array_dig2[Cursor_no]+48;

		ypos1=Letters_Alignments(62+(45*(3-Cursor_no))+space,
		106+(45*(3-Cursor_no))+space, (uint8_t*)letter1,0);

		TFT_Number(ypos1,CALIB_EDT_YPOS,array_dig2[Cursor_no],back_colour,text_colour);

		TFT_ST7789V_up_down_arrow_20_arial(79,15+62+(45*(3-Cursor_no))+space,0,
		arrow_bg_color,arrow_fill_color);

		TFT_ST7789V_up_down_arrow_20_arial(166,15+62+(45*(3-Cursor_no))+space,1,
		arrow_bg_color,arrow_fill_color);
	    // delay_secs(3);

	}
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint8_t edit_screen_Time(uint32_t *Edit_value,uint8_t screen,uint16_t max_value)
{
	uint8_t prev_cursor_no=1;
	uint8_t space=0;
	uint8_t Cursor_no=2;
	uint8_t condition=1;
	uint8_t xpos=0;
	uint8_t Err_flag=0;
	uint32_t result=0;
	uint32_t Value=0;
	char letter1[2]={'\0','\0'} ;
	Value=*Edit_value;

	edit_split_frame(screen);
	Digit_Spiliting1(Value,Cursor_no,prev_cursor_no);

//	TFT_ST7789V_lcd_drawcircle1(31,128,12,WHITE,WHITE);
//	TFT_ST7789V_lcd_drawcircle1(289,127,12,WHITE,WHITE);
//	TFT_ST7789V_left_Right_arrow_14_arial(121,26,0,WHITE,NEON_BLUE_1);
//	TFT_ST7789V_left_Right_arrow_14_arial(120,287,1,WHITE,NEON_BLUE_1);


	edit_option(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
	prev_cursor_no=2;
	Left_Right_Indi(Cursor_no,0);

	while(condition)
	{
		 Power_off();

				 if(!ON_Flag)
				{
					break;//26-03
				}

				 else if(POW.power_status_flag)
			   {
					POW.power_status_flag=0;//26-03
					edit_split_frame(screen);
					Left_Right_Indi(Cursor_no,0);
					edit_option_frame(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);

			   }

		switch(KEY.value)
		{
			case LEFT_KEY:
				beep_sound();
					if(Cursor_no<3)
					{
						Cursor_no++;
						edit_option(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
						if(Cursor_no !=0 && Cursor_no !=2 )
						{
							Left_Right_Indi(Cursor_no,0);
						}
					}
					prev_cursor_no=Cursor_no;
					while(KEY.value);
					break;

			case RIGHT_KEY:
				beep_sound();
					if(Cursor_no>0)
					{
						Cursor_no--;
						edit_option(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
						if(Cursor_no !=1 && Cursor_no !=3 )
						{
							Left_Right_Indi(Cursor_no,0);
						}
					}
					prev_cursor_no=Cursor_no;
					while(KEY.value);
					break;



			case UP_KEY:
				beep_sound();
				if(Cursor_no<2)
					{
						space=15;

					}

					else
					{
						space=0;
					}
				//	Font_Select(CALIBRI_43);

					letter1[0]=array_dig2[Cursor_no]+48;
					Font_Select(CALIBRI_43);
					xpos=Letters_Alignments(63+(45*(3-Cursor_no))+space,
					106+(45*(3-Cursor_no))+space, (uint8_t*)letter1,0);
					TFT_Number(xpos,CALIB_EDT_YPOS,array_dig2[Cursor_no],CURSOR_COL,CURSOR_COL);
					if((array_dig2[Cursor_no]<9 && Cursor_no!=1) || (array_dig2[Cursor_no]<5 && Cursor_no==1))
					{
						array_dig2[Cursor_no]++;
					}
					if(max_value<((array_dig2[3]*1000)+(array_dig2[2]*100)+(array_dig2[1]*10)+array_dig2[0]))
					{
						array_dig2[Cursor_no]--;
					}

					letter1[0]=array_dig2[Cursor_no]+48;
					Font_Select(CALIBRI_43);
					xpos=Letters_Alignments(63+(45*(3-Cursor_no))+space,
					106+(45*(3-Cursor_no))+space, (uint8_t*)letter1,0);
					TFT_Number(xpos,CALIB_EDT_YPOS,array_dig2[Cursor_no],CURSOR_COL,BLACK);
					while(KEY.value);
					break;

			case DOWN_KEY:
				beep_sound();

					if(Cursor_no<2)
					{
						space=15;

					}

					else
					{
						space=0;
					}
					Font_Select(CALIBRI_43);
					letter1[0]=array_dig2[Cursor_no]+48;
					xpos=Letters_Alignments(63+(45*(3-Cursor_no))+space,
					106+(45*(3-Cursor_no))+space, (uint8_t*)letter1,0);
					TFT_Number(xpos,CALIB_EDT_YPOS,array_dig2[Cursor_no],CURSOR_COL,CURSOR_COL);
					if(array_dig2[Cursor_no]>0)
					{
						array_dig2[Cursor_no]--;
					}

					Font_Select(CALIBRI_43);
					letter1[0]=array_dig2[Cursor_no]+48;
					xpos=Letters_Alignments(63+(45*(3-Cursor_no))+space,
					106+(45*(3-Cursor_no))+space, (uint8_t*)letter1,0);
					TFT_Number(xpos,CALIB_EDT_YPOS,array_dig2[Cursor_no],CURSOR_COL,BLACK);
					while(KEY.value);
					break;

			case OK_KEY:
				beep_sound();
					result=(array_dig2[3]*1000)+(array_dig2[2]*100)+(array_dig2[1]*10)+array_dig2[0];
					*Edit_value=result;
					condition=0;
					while(KEY.value);
					break;

			case BACK_KEY:
				beep_sound();
					condition=0;
					Err_flag=1;
					while(KEY.value);
					break;
		}
	}
	return Err_flag;
}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void edit_option_frame(uint8_t current_cur_no,uint8_t prev_cursor_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL,uint32_t UP_ARROW_ERASE)
{
		char letter1[2]={'\0','\0'} ;
	    uint32_t back_colour   = 0;
		uint32_t text_colour   = 0;
		uint8_t loop		   = 0;
	//	uint8_t Cursor_no	   = 0;
		uint8_t space		   = 0;
		uint32_t arrow_bg_color	= 0;
		uint32_t arrow_fill_color =  0;
		uint8_t xpos=0;

		for(loop = 0; loop<=3; loop++)
		{
			if(loop!=current_cur_no)
			{
				back_colour			= MAIN_FRAME_COL;
				text_colour 		= WHITE;
				//Cursor_no			= prev_cursor_no;
				arrow_bg_color		= MAIN_FRAME_COL;
				arrow_fill_color	= MAIN_FRAME_COL;
			}
			else
			{
				back_colour 		= LIGHT_GRAY;
				text_colour  		= BLACK;
			//	Cursor_no			= current_cur_no;
				arrow_bg_color		= LIGHT_GRAY;
				arrow_fill_color	= BLACK;
			}

			if(loop<2)
			{
				space=15;
			}
			else
			{
				space=0;
			}

			TFT_ST7789V__rectangle_curve(1+62+(45*(3-loop))+space,64,125,43,0,back_colour);

			Font_Select(CALIBRI_43);
			letter1[0]=array_dig2[loop]+48;
			xpos=Letters_Alignments(62+(45*(3-loop))+space,
			106+(45*(3-loop))+space, (uint8_t*)letter1,0);

			TFT_Number(xpos,CALIB_EDT_YPOS,array_dig2[loop],back_colour,text_colour);

			TFT_ST7789V_up_down_arrow_20_arial(79,15+62+(45*(3-loop))+space,0,
			arrow_bg_color,arrow_fill_color);    //UP_ARROW
			TFT_ST7789V_up_down_arrow_20_arial(166,15+62+(45*(3-loop))+space,1,
			arrow_bg_color,arrow_fill_color);  //UP_ARROW

		}
}


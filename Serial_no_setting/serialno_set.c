#include <stdio.h>
#include "LPC55S16.h"
#include "Driver_Timer.h"
#include "Driver_I2C.h"
//#include "Driver_PINT.h"
#include "Driver_ADC.h"
#include "Driver_SPI.h"
#include "Color.h"
#include "stdint.h"
#include "TFT_Commands.h"
#include "TFT_String.h"
#include"Keypad.h"
#include "Power_off.h"
#include <Shapes.h>
#include "sound.h"
#include <Boot_up.h>





uint8_t add_flag_2=0;
uint8_t position_3=0;
uint8_t array_dig_2[5];
char letter_2[2]={'\0','\0'} ;
uint16_t ypos_2=0;
//extern uint32_t serialno;




extern void Rectangle(uint16_t x_axis,uint16_t y_axis,uint16_t Length,uint16_t Height,uint32_t Color);
extern void Left_Right_Indi(uint8_t cursor_pos,uint8_t screen_id);


extern uint8_t ON_Flag;
extern uint8_t auto_lock_time;



int serialno_settings(void);
void sc_split_frame(void);
void Digit_Spiliting_2(uint16_t Value);
void serialno_screen_option_scroll(uint8_t current_cur_no,uint8_t prev_cursor_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL,uint32_t UP_ARROW_ERASE);
uint16_t serialno_screen(uint16_t *Value_1,uint32_t limit);







/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void sc_split_frame()
{
	uint8_t loop_count=0;
//	uint32_t back_colour   = 0;
//	uint32_t text_colour		= 0;
//	uint32_t arrow_bg_color	= 0;
//	uint32_t arrow_fill_color =  0;
//	Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Serial no");
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to change",(uint8_t*)"OK",2,14);

	for(loop_count=0;loop_count<=5;loop_count++)
		{
			Rectangle(47+(45*loop_count),68,0,115,BLACK);
		}

//	for(loop_count=0;loop_count<5;loop_count++)
//	{
//
//
//
//		if(loop_count==0)
//		{
//			back_colour			= LIGHT_GRAY;
//			text_colour 		= BLACK;
//			arrow_bg_color		= LIGHT_GRAY;
//			arrow_fill_color	= BLACK;
//		}
//		else
//		{
//			back_colour 		= MAIN_FRAME_COL;
//			text_colour  		= WHITE;
//			arrow_bg_color		= MAIN_FRAME_COL;
//			arrow_fill_color	= MAIN_FRAME_COL;
//		}
//
//		TFT_ST7789V__rectangle_curve(48+(45*(loop_count)),66,125,43,0,back_colour);
//		Font_Select(CALIBRI_43);
//		TFT_Number(55+(45*(loop_count)),96,array_dig_2[4-loop_count],back_colour,text_colour);
//		TFT_ST7789V_up_down_arrow_20_arial(79,61+(45*(loop_count)),0,arrow_bg_color,arrow_fill_color);  		//UP_ARROW
//		TFT_ST7789V_up_down_arrow_20_arial(176,61+(45*(loop_count)), 1,arrow_bg_color,arrow_fill_color);	//DOWN_ARROW
//
//	}

}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void Digit_Spiliting_2(uint16_t Value)
{

	uint8_t loop_count=0;

	position_3=0;

	if(Value==0)
	{
		for(loop_count=0; loop_count<5; loop_count++)
		{
			array_dig_2[loop_count] = 0;

		}
	}
	else
	{
		while(Value>0)
		{
			array_dig_2[position_3]=Value%10;
			Value=Value/10;
			position_3++;
		}
	}

//	for(loop_count=0;loop_count<position_3;loop_count++)
//	     {
//
//
//	      Font_Select(CALIBRI_43);
//
////		letter_2[0] =	 array_dig_2[loop_count]+48;
////
//////	      ypos1=Letters_Alignments(63+(45*(3-loop_count))+space,
//////	    		  	  	  	  	  	  	  	  	  106+(45*(3-loop_count))+space, (uint8_t*)letter1,0);
////
//	      ypos_2=Letters_Alignments(47+(45*(4-loop_count)),92+(45*(5-loop_count)), (uint8_t*)letter_2,0);
////
////
////	      Font_Select(CALIBRI_43);
////	   //  if(loop_count !=cur_no && loop_count !=prev_no )
////	      {
////
//	    	 TFT_Number(ypos_2,98,array_dig_2[loop_count],MAIN_FRAME_COL,WHITE);
////	      }
//	    }

}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void serial_no_opt_Frame(uint8_t cursor_no)
{


    uint8_t loop_count=0;
    uint32_t text_colour=0;
    uint32_t  back_colour=0;
    char letter_2[2]={'\0','\0'} ;


	for(loop_count=0;loop_count<=4;loop_count++)
	{
		if(loop_count==cursor_no)
		{
			back_colour	= LIGHT_GRAY;
			text_colour = BLACK;
			TFT_ST7789V__rectangle_curve(48+(45*(4-loop_count)),64,125,43,0,back_colour);
			TFT_ST7789V_up_down_arrow_20_arial(79,61+(45*(4-loop_count)),0,back_colour,BLACK);  	//23-03	//UP_ARROW
			TFT_ST7789V_up_down_arrow_20_arial(166,61+(45*(4-loop_count)), 1,back_colour,BLACK);	//DOWN_ARROW


//			TFT_ST7789V_up_down_arrow_20_arial(81,40+15+(45*(4-Cursor_no)+space),0,back_colour,BLACK);  		//UP_ARROW
//			TFT_ST7789V_up_down_arrow_20_arial(168,40+15+(45*(4-Cursor_no)+space), 1,back_colour,BLACK)	;
		}
		else
		{
			back_colour	= MAIN_FRAME_COL;
			text_colour = WHITE;
		}

		Font_Select(CALIBRI_43);

	//	sprintf(letter_2,"%d",array_dig_2[loop_count]);
		letter_2[0] =	 array_dig_2[loop_count]+48;

		ypos_2=Letters_Alignments(48+(45*(4-loop_count)),
								93+(45*(4-loop_count)),(uint8_t*)letter_2,0);

			Font_Select(CALIBRI_43);

		TFT_Number(ypos_2,CALIB_EDT_YPOS,array_dig_2[loop_count],back_colour,text_colour);

	}

}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void serialno_screen_option_scroll(uint8_t current_cur_no,uint8_t prev_cursor_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL,uint32_t UP_ARROW_ERASE)
{

	uint32_t back_colour = 0;
	uint32_t text_colour = 0;
	uint8_t loop		= 0;
	uint8_t Cursor_no  = 0;
	uint32_t arrow_bg_color	= 0;
	uint32_t arrow_fill_color =  0;


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

		TFT_ST7789V__rectangle_curve(48+(45*(4-Cursor_no)),64,125,43,0,back_colour);

		Font_Select(CALIBRI_43);

		sprintf(letter_2,"%d",array_dig_2[Cursor_no]);

		ypos_2=Letters_Alignments(47+(45*(4-Cursor_no)),
								92+(45*(4-Cursor_no)),(uint8_t*)letter_2,0);

		TFT_Number(ypos_2,CALIB_EDT_YPOS,array_dig_2[Cursor_no],back_colour,text_colour);

	//	TFT_Number(ypos_2,98,array_dig_2[Cursor_no],back_colour,text_colour);

		TFT_ST7789V_up_down_arrow_20_arial(79,61+(45*(4-Cursor_no)),0,arrow_bg_color,arrow_fill_color);  		//UP_ARROW
		TFT_ST7789V_up_down_arrow_20_arial(166,61+(45*(4-Cursor_no)), 1,arrow_bg_color,arrow_fill_color);	//DOWN_ARROW

	}







}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

uint16_t serialno_screen(uint16_t *Value_1, uint32_t Limit)
{
     uint8_t Cursor_no=0;
     uint8_t prev_cursor_no=0;
  // uint8_t loop_count=0;
     uint8_t condition=1;
     uint8_t check_flag=1;
     uint16_t P_value=*Value_1;
     uint32_t serialno=0;
	 POW.power_status_flag=1;//2-04
	 auto_lock_time=AUTO_EXIT_TIME;


     Font_Select(ARIAL_12);

//     TFT_ST7789V_lcd_drawcircle1(18,128,12,WHITE,WHITE);
//     TFT_ST7789V_lcd_drawcircle1(297+3,128,12,WHITE,LIGHT_GRAY_3);//23-03
//     TFT_ST7789V_left_Right_arrow_14_arial(121,13,0,WHITE,NEON_BLUE_1);
//     TFT_ST7789V_left_Right_arrow_14_arial(121,295+3,1,LIGHT_GRAY_3,NEON_BLUE_1);//23-03




//     sc_split_frame();
//
     Digit_Spiliting_2(P_value);
//
//   serial_no_opt_Frame(Cursor_no);
//   Left_Right_Indi(Cursor_no,1);
//   while(1);
//   serialno_screen_option_scroll(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
//   screen_option_scroll(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);

     prev_cursor_no=0;

      while(condition)
       {

    	Power_off();

		if(!ON_Flag)
		{
			break;//26-03
		}

		else if(POW.power_status_flag)
		{
			POW.power_status_flag=0;//2-04
			sc_split_frame();
		//	Digit_Spiliting_2(P_value);
			serial_no_opt_Frame(Cursor_no);
			Left_Right_Indi(Cursor_no,1);
			while(KEY.value);
		}

		if(KEY.value)
		{
		   auto_lock_time=AUTO_EXIT_TIME;
		}
		if(!auto_lock_time)
		{
		   break;
		}

	 switch(KEY.value)
	 {
			 case LEFT_KEY:
					beep_sound();

			 if(Cursor_no<4)
			 {
				 Cursor_no++;
				 serialno_screen_option_scroll(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
				if(Cursor_no !=2 && Cursor_no !=3 )
				{
					Left_Right_Indi(Cursor_no,1);
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
				serialno_screen_option_scroll(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
				if(Cursor_no !=1 && Cursor_no !=2 )
				{
					Left_Right_Indi(Cursor_no,1);
				}
			}

			prev_cursor_no=Cursor_no;

			while(KEY.value);
			break;

			case UP_KEY:
				beep_sound();

			if(array_dig_2[Cursor_no]<9)
			{
	//			array_dig_2[Cursor_no]++;

				Font_Select(CALIBRI_43);
				sprintf(letter_2,"%d",array_dig_2[Cursor_no]);

				ypos_2=Letters_Alignments(47+(45*(4-Cursor_no)),92+(45*(4-Cursor_no)), (uint8_t*)letter_2,0);

				TFT_Number(ypos_2,CALIB_EDT_YPOS,array_dig_2[Cursor_no],CURSOR_COL,CURSOR_COL);

							array_dig_2[Cursor_no]++;//23-03

				sprintf(letter_2,"%d",array_dig_2[Cursor_no]);

				ypos_2=Letters_Alignments(47+(45*(4-Cursor_no)),92+(45*(4-Cursor_no)), (uint8_t*)letter_2,0);

				TFT_Number(ypos_2,103,array_dig_2[Cursor_no],CURSOR_COL,BLACK);

			}
			else
			{
					WARN_SOUND(1,1,2);
			}

			while(KEY.value);
			break;

			case DOWN_KEY:
				beep_sound();

			if(array_dig_2[Cursor_no]>0)
			{

			//	array_dig_2[Cursor_no]--;

				Font_Select(CALIBRI_43);

				sprintf(letter_2,"%d",array_dig_2[Cursor_no]);

				ypos_2=Letters_Alignments(47+(45*(4-Cursor_no)),92+(45*(4-Cursor_no)), (uint8_t*)letter_2,0);

				TFT_Number(ypos_2,CALIB_EDT_YPOS,array_dig_2[Cursor_no],CURSOR_COL,CURSOR_COL);

				array_dig_2[Cursor_no]--;//23-03


				sprintf(letter_2,"%d",array_dig_2[Cursor_no]);

				ypos_2=Letters_Alignments(47+(45*(4-Cursor_no)),92+(45*(4-Cursor_no)), (uint8_t*)letter_2,0);

				TFT_Number(ypos_2,103,array_dig_2[Cursor_no],CURSOR_COL,BLACK);

			}

			else
			{
					WARN_SOUND(1,1,2);
			}
			while(KEY.value);
			break;

			case OK_KEY:
				beep_sound();

			serialno=array_dig_2[4]*10000+array_dig_2[3]*1000+array_dig_2[2]*100+array_dig_2[1]*10+array_dig_2[0]*1;
		//    serialno=array_dig_2[4]*1+array_dig_2[3]*10+array_dig_2[2]*100+array_dig_2[1]*1000+array_dig_2[0]*10000;

		//     Rectangle(0,0,320,240,MAIN_FRAME_COL);


		//	TFT_Number(50,100,serialno,CURSOR_COL,BLACK);
		//	while(1);

			//serialno=array_dig_2[0]+array_dig_2[1]*10+array_dig_2[2]*100+array_dig_2[3]*1000+array_dig_2[4]*10000;

			*Value_1=serialno;
			check_flag=1;
			condition=0;


			while(KEY.value);
			break;

			case BACK_KEY:
			beep_sound();
			check_flag=0;
			condition=0;
			while(KEY.value);
			break;

		 }

    }
    return check_flag;
}

//
//#include "LPC55S16.h"
//#include "Shapes.h"
//#include "Color.h"
//#include "Keypad.h"
//#include "TFT_Commands.h"
//#include "TFT_String.h"
////#include "Main_Menu.h"
//
//#include "../Menu_Setting/Main_Menu.h"
//#include "Power_off.h"
//#include "Driver_Timer.h"
//#include "factory.h"
//#include"Driver_I2C.h"
//
//
//extern uint16_t G_date_mnth;
//extern char letter1[2];
//uint8_t array_dig3[6];
//uint16_t manu_dt_yr=0;
//
//void month_yr_edit_split_frame(uint8_t screen);
//void month_yr_Digit_Spiliting1(uint16_t Value,uint8_t cur_no,uint8_t prev_no);
//void month_yr_edit_option(uint8_t current_cur_no,uint8_t prev_cursor_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL,uint32_t UP_ARROW_ERASE);
//
//
//uint8_t month_yr_edit_screen(uint16_t *Edit_value,uint8_t screen,uint16_t max_value)
//
//{
//
//		uint8_t prev_cursor_no=1;
//		uint8_t space=0;
//		uint8_t Cursor_no=2;
//		uint8_t max_arr[4];
//		uint8_t check_flag=1;
//	//	uint16_t result=0;
//		uint8_t condition1=1;
//		uint8_t xpos=0;
//		uint16_t Value=0;
//	//	uint8_t Err_flag=1;
//		uint8_t loop_cnt=0;
//		Value=*Edit_value;
//
//		TFT_ST7789V_lcd_drawcircle1(31,128,12,WHITE,WHITE);
//		TFT_ST7789V_lcd_drawcircle1(289,127,12,WHITE,WHITE);
//		TFT_ST7789V_left_Right_arrow_14_arial(121,26,0,WHITE,NEON_BLUE_1);
//		TFT_ST7789V_left_Right_arrow_14_arial(120,287,1,WHITE,NEON_BLUE_1);
//
//		month_yr_edit_split_frame(screen);
//		month_yr_Digit_Spiliting1(Value,Cursor_no,prev_cursor_no);
//
//		while(max_value)
//		{
//			max_arr[loop_cnt]=max_value%10;
//			max_value=max_value/10;
//			loop_cnt++;
//		}
//
//		month_yr_edit_option(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
//		prev_cursor_no=2;
//		while(KEY.value);
//		while(condition1)
//		{
//		//	while(KEY.value);
//			switch(KEY.value)
//			{
//				case LEFT_KEY:
//				beep_sound();
//				if(Cursor_no<3)
//				{
//					Cursor_no++;
//					month_yr_edit_option(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
//					if(Cursor_no !=2 && Cursor_no !=3 )
//					{
//						//	Left_Right_Indi(Cursor_no);
//					}
//				}
//				prev_cursor_no=Cursor_no;
//				while(KEY.value);
//				break;
//
//				case RIGHT_KEY:
//				beep_sound();
//				if(Cursor_no>0)
//				{
//					Cursor_no--;
//					month_yr_edit_option(Cursor_no,prev_cursor_no,CURSOR_COL,BLACK,BLACK);
//					if(Cursor_no !=1 && Cursor_no !=2 )
//					{
//						//   Left_Right_Indi(Cursor_no);
//					}
//				}
//				prev_cursor_no=Cursor_no;
//				while(KEY.value);
//				break;
//
//
//
//				case UP_KEY:
//					beep_sound();
//					if((Cursor_no==3)||(Cursor_no==1))
//						{
//							if(array_dig3[Cursor_no-1]<=max_arr[Cursor_no-1])
//							{
//								if(array_dig3[Cursor_no]<max_arr[Cursor_no])
//								{
//									array_dig3[Cursor_no]++;
//
//								}
//							}
//							else
//							{
//								if(array_dig3[Cursor_no]<max_arr[Cursor_no]-1)
//							// 	if(array_dig2[Cursor_no]<max_arr[Cursor_no])
//								{
//									array_dig3[Cursor_no]++;
//								}
//							}
//						}
//
//						else if((Cursor_no==2)||(Cursor_no==0))
//						{
//							if(array_dig3[Cursor_no+1]<max_arr[Cursor_no+1])
//							{
//								if(array_dig3[Cursor_no]<9)
//								{
//									array_dig3[Cursor_no]++;
//								}
//							}
//
//							else
//							{
//								if(array_dig3[Cursor_no]<max_arr[Cursor_no])
//								{
//									array_dig3[Cursor_no]++;
//								}
//							}
//						}
//
//
//
//				if(Cursor_no<2)
//				{
//					space=15;
//					Font_Select(CALIBRI_43);
//					xpos=Letters_Alignments(63+(45*(3-Cursor_no))+space,
//					106+(45*(3-Cursor_no))+space, (uint8_t*)letter1,0);
//					TFT_Number(xpos,CALIB_EDT_YPOS,array_dig3[Cursor_no],CURSOR_COL,BLACK);
//				}
//
//				else
//				{
//					space=0;
//					Font_Select(CALIBRI_43);
//					xpos=Letters_Alignments(63+(45*(3-Cursor_no))+space,
//					106+(45*(3-Cursor_no))+space, (uint8_t*)letter1,0);
//					TFT_Number(xpos,CALIB_EDT_YPOS,array_dig3[Cursor_no],CURSOR_COL,BLACK);
//				}
//
//				while(KEY.value);
//				break;
//
//				case DOWN_KEY:
//				beep_sound();
//				if((Cursor_no==2)||(Cursor_no==0))
//				{
//				if(array_dig3[Cursor_no]>1)
//				{
//
//					array_dig3[Cursor_no]--;
//
//				}
//				}
//				else
//				{
//					if(array_dig3[Cursor_no]>0)
//					{
//						array_dig3[Cursor_no]--;
//					}
//				}
//
//				if(Cursor_no<2)
//				{
//					space=15;
//					Font_Select(CALIBRI_43);
//					xpos=Letters_Alignments(63+(45*(3-Cursor_no))+space,
//					106+(45*(3-Cursor_no))+space, (uint8_t*)letter1,0);
//					TFT_Number(xpos,CALIB_EDT_YPOS,array_dig3[Cursor_no],CURSOR_COL,BLACK);
//				}
//
//				else
//				{
//					space=0;
//					Font_Select(CALIBRI_43);
//					xpos=Letters_Alignments(63+(45*(3-Cursor_no))+space,
//					106+(45*(3-Cursor_no))+space, (uint8_t*)letter1,0);
//					TFT_Number(xpos,CALIB_EDT_YPOS,array_dig3[Cursor_no],CURSOR_COL,BLACK);
//				}
//				while(KEY.value);
//				break;
//
//				case BACK_KEY:
//				beep_sound();
//				condition1=0;
//				//Err_flag=1;
//				while(KEY.value);
//				break;
//
//				case OK_KEY:
//					beep_sound();
//					manu_dt_yr=(array_dig3[3]*1000)+(array_dig3[2]*100)+(array_dig3[1]*10)+array_dig3[0];
//				*Edit_value=manu_dt_yr;
//				condition1=0;
//			//	factory_Frame();
//				//	factory_Opt_Frame(0,0,3);
//
//			//	Err_flag=1;
//				while(KEY.value);
//				break;
//
//
//
//			}
//			//	condition1=0;
//
//		}
//		return check_flag;
//}
//
//void month_yr_edit_split_frame(uint8_t screen)
//{
//	uint8_t loop_count=0;
//	Rectangle(0,0,320,240,MAIN_FRAME_COL);
//	for(loop_count=0;loop_count<=2;loop_count++)
//	{
//		Rectangle(62+(45*loop_count),68,0,115,WHITE);
//	}
//	//   Rectangle(40+(45*4)+15,68,0,115,WHITE);
//	for(loop_count=2;loop_count<5;loop_count++)
//	{
//		Rectangle(62+15+(45*loop_count),68,0,115,WHITE);
//	}
//	Font_Select(ARIAL_9);
//	if(screen)
//	{
//		TFT_String(80,40,(uint8_t*)"M",MAIN_FRAME_COL,OLIVE);
//		TFT_String(125,40,(uint8_t*)"M",MAIN_FRAME_COL,OLIVE);
//		TFT_String(185,40,(uint8_t*)"Y",MAIN_FRAME_COL,OLIVE);
//		TFT_String(230,40,(uint8_t*)"Y",MAIN_FRAME_COL,OLIVE);
//		TFT_String(157,112,(uint8_t*)":",MAIN_FRAME_COL,WHITE);
//	}
//	else
//	{
//		TFT_String(157,119,(uint8_t*)".",MAIN_FRAME_COL,WHITE);
//	}
//
//}
//
//void month_yr_Digit_Spiliting1(uint16_t Value,uint8_t cur_no,uint8_t prev_no)
// {
//	uint8_t space=0;
//	uint8_t loop_count=0;
//    uint8_t position_2=0;
//
//
//    uint16_t xpos=0;
//
//	if(!Value)
//		{
//			for(position_2=0;position_2<3;position_2++)
//			{
//				array_dig3[position_2]=0;
//			}
//		}
//	 while(Value>0)
//	     {
//		 array_dig3[position_2]=Value%10;
//	     Value=Value/10;
//	     position_2++;
//	     }
//
//	for(loop_count=0;loop_count<position_2;loop_count++)
//     {
//		if(loop_count==0|| loop_count==1)
//		{
//			space=15;
//		}
//		else
//		{
//			space=0;
//		}
//
//      Font_Select(CALIBRI_43);
//
//      letter1[0] =	 array_dig3[loop_count]+48;
//
//      xpos=Letters_Alignments(63+(45*(3-loop_count))+space,
//    		  	  	  	  	  	  	  	  	  106+(45*(3-loop_count))+space, (uint8_t*)letter1,0);
//
//       Font_Select(CALIBRI_43);
//     if(loop_count !=cur_no && loop_count !=prev_no )
//      {
////       TFT_Number(98,ypos1,array_dig2[loop_count],MAIN_FRAME_COL,WHITE);
//
//       TFT_Number(xpos,CALIB_EDT_YPOS,array_dig3[loop_count],MAIN_FRAME_COL,WHITE);
//      }
//    }
//  }
//
//void month_yr_edit_option(uint8_t current_cur_no,uint8_t prev_cursor_no, uint32_t CUR_COL,uint32_t CUR_BACK_COL,uint32_t UP_ARROW_ERASE)
//{
//	uint32_t back_colour   = 0;
//	uint32_t text_colour		= 0;
//	uint8_t loop		        	= 0;
//	uint8_t Cursor_no		= 0;
//	uint8_t space				= 0;
//	uint32_t arrow_bg_color	= 0;
//	uint32_t arrow_fill_color =  0;
//	uint8_t xpos=0;
//
//	for(loop = 0; loop<2; loop++)
//	{
//		if(!loop)
//		{
//			back_colour			= MAIN_FRAME_COL;
//			text_colour 		= WHITE;
//			Cursor_no			= prev_cursor_no;
//			arrow_bg_color		= MAIN_FRAME_COL;
//			arrow_fill_color	= MAIN_FRAME_COL;
//		}
//		else
//		{
//			back_colour 		= LIGHT_GRAY;
//			text_colour  		= BLACK;
//			Cursor_no			= current_cur_no;
//			arrow_bg_color		= LIGHT_GRAY;
//			arrow_fill_color	= BLACK;
//		}
//
//		if(Cursor_no<2)
//		{
//			space=15;
//		}
//		else
//		{
//			space=0;
//		}
//
//		TFT_ST7789V__rectangle_curve(1+62+(45*(3-Cursor_no))+space,64,125,43,0,back_colour);
//
//		Font_Select(CALIBRI_43);
//		xpos=Letters_Alignments(62+(45*(3-Cursor_no))+space,
//		106+(45*(3-Cursor_no))+space, (uint8_t*)letter1,0);
//
//		TFT_Number(xpos,CALIB_EDT_YPOS,array_dig3[Cursor_no],back_colour,text_colour);
//
//		TFT_ST7789V_up_down_arrow_20_arial(79,15+62+(45*(3-Cursor_no))+space,0,
//		arrow_bg_color,arrow_fill_color);    //UP_ARROW
//		TFT_ST7789V_up_down_arrow_20_arial(166,15+62+(45*(3-Cursor_no))+space,1,
//		arrow_bg_color,arrow_fill_color);  //UP_ARROW
//
//	}
//}
//

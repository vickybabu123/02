#include <infused_calculate.h>

#include <Boot_up.h>
#include "LPC55S16.h"
#include "Color.h"
#include "Driver_SPI.h"
#include "TFT_Commands.h"
#include "Shapes.h"
#include "TFT_String.h"
#include "clock_config.h"
#include "Main_screen.h"
#include "Bolus_Header.h"
#include "Dosage_mode.h"
#include "Occlusion.h"
#include "Driver_ADC.h"
//#include "Alarm.h"
#include "Power_off.h"


char local_buffer[10];

extern uint8_t G_warn_flag;
extern uint8_t G_drug_unit_no;
//extern uint8_t xpos;
extern uint32_t MR_VALUE;
char* dose_para[5]={"FR","Conc.","Infu","P.Wt"};
uint32_t volume_ml=100;
extern uint8_t G_opt_no;
extern uint8_t G_page_no;
extern uint8_t drug_no;
extern uint8_t brand_select_no;
extern  char Brand_Names[6][4][15];
//uint8_t G_warning_flag;//28-03

extern char dose_rate_unit[3][13];
extern uint8_t dose_option_no;
//extern char* Drug_Names[150][4];
extern char Drug_Names[150][4][20];

//extern char* disp_para[20];
extern void Warning_screen(uint8_t *Warning_name,uint8_t mode);
extern uint8_t alarm_flag;
extern char* drug_unit[4][4];
void dose_rate_para(uint8_t start_cnt, uint8_t end_cnt);
extern void infused_data(uint8_t screen,uint8_t r_mode);   //28-03
//extern uint32_t pulse_per_ml;
//void Battery_symbol(void);  //28-03
void FR_spliting_DD(uint16_t flowrate);
//void plug_symbol(void);
extern uint8_t G_occl_unit;
extern uint8_t home_flag;
extern uint8_t home_return_flag;
extern uint8_t G_Bolus_target_flag;
extern uint16_t G_Remaining_volume;
extern uint8_t device_check_cnt;
extern uint8_t brand_display_hm;
extern uint8_t brand_select_home;

uint8_t calculate=0;

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void main_screen_frame(uint16_t flowrate1,uint8_t mode)
{

//	uint16_t loop_count=0;
//	uint32_t ml=1;
	uint16_t xpos=0;
//	uint16_t ml=100;
	char* disp_pres[5]={"mmHg","PSI","kPa","mbar"};
	uint8_t presure_ratio[5]={51.7,1,6.8,6.8};
	FR_Lines();
//	FR_spliting(flowrate1);

	if(mode==0)
	{

		FR_spliting(flowrate1);

		Font_Select(ARIAL_12);
		TFT_String(258,70,(uint8_t *)"mL/Hr",MAIN_FRAME_COL,WHITE);

		TFT_String(100,160,(uint8_t*)"Infused",MAIN_FRAME_COL,WHITE);//28-03
//		TFT_String(100,185,(uint8_t*)"VTBI",MAIN_FRAME_COL,WHITE);   //28-03
		TFT_String(100,160+(25*1),(uint8_t*)"E.Time",MAIN_FRAME_COL,WHITE);
	//	TFT_String(100,160+(25*2),(uint8_t*)"Brand",MAIN_FRAME_COL,NEW_FTR_COL);
		TFT_ST7789V__rectangle_curve(95,205,30,190+25,0,NEW_HDR_COL);
	//	xpos=Right_Alignments((uint8_t*)Brand_Names[brand_select_no/4][brand_select_no%4],310);    //(uint8_t*)letter
//		if(!brand_display_hm)
//		{
////		xpos=Letters_Alignments(95,95+215,(uint8_t*)Brand_Names[brand_select_no/4][brand_select_no%4],0);
//			TFT_String(xpos,162+(25*2),(uint8_t*)Brand_Names[brand_select_no/4][brand_select_no%4],NEW_HDR_COL,BLACK);
			xpos=Letters_Alignments(95,95+215,(uint8_t*)Brand_Names[brand_select_no/4][brand_select_no%4],0);
			TFT_String(xpos,162+(25*2),(uint8_t*)Brand_Names[brand_select_no/4][brand_select_no%4],NEW_HDR_COL,BLACK);
//		}
//
//		else
//		{
//			xpos=Letters_Alignments(95,95+215,(uint8_t*)Brand_Names[brand_select_home/4][brand_select_home%4],0);
//			TFT_String(xpos,162+(25*2),(uint8_t*)Brand_Names[brand_select_home/4][brand_select_home%4],NEW_HDR_COL,BLACK);
//		}

		Font_Select(ARIAL_12);
		TFT_String(285,160,(uint8_t*)"mL",MAIN_FRAME_COL,WHITE);
	 	TFT_String(285,185,(uint8_t*)"hrs",MAIN_FRAME_COL,WHITE);  //28-03
	}

	else if(mode==1)
	{

		FR_spliting(flowrate1);
		Font_Select(ARIAL_12);
		TFT_String(258,70,(uint8_t *)"mL/Hr",MAIN_FRAME_COL,WHITE);

		TFT_String(100,160,(uint8_t*)"Infused",MAIN_FRAME_COL,WHITE);//28-03
		TFT_String(100,185,(uint8_t*)"VTBI",MAIN_FRAME_COL,WHITE);
		TFT_String(100,210,(uint8_t*)"E.Time",MAIN_FRAME_COL,WHITE);

		Font_Select(ARIAL_12);
		TFT_String(285,160,(uint8_t*)"mL",MAIN_FRAME_COL,WHITE);
		TFT_String(285,185,(uint8_t*)"mL",MAIN_FRAME_COL,WHITE);
		TFT_String(285,210,(uint8_t*)"hrs",MAIN_FRAME_COL,WHITE);

	}

		else if(mode==2)
		{

			FR_spliting_DD(dose.drug_dos);
			TFT_ST7789V__rectangle_curve(95,95,30,185+25,0,NEW_HDR_COL);
			Font_Select(ARIAL_12);
			TFT_String(105,102,(uint8_t*)Drug_Names[(dose.drug_select_no/4)][(dose.drug_select_no%4)],NEW_HDR_COL,BLACK);
			TFT_String(180,70,(uint8_t*)dose_rate_unit[dose_option_no],MAIN_FRAME_COL,YELLOW);
			G_warn_flag=0;

			if(G_warn_flag)
			{
				dose_rate_para(1,3);
			}

			else
			{
				dose_rate_para(0,3);
			}

	}
		infused_data(1,mode);//28-03


	//Battery_symbol();
	//plug_symbol();

	/***********************************dynamic pressure display***************************/
		Font_Select(ARIAL_9);
		xpos=Letters_Alignments(0,75, (uint8_t*)disp_pres[G_occl_unit],0);
		TFT_String(xpos,DYN_UNIT_POS,(uint8_t *)disp_pres[G_occl_unit],MAIN_FRAME_COL,WHITE);
		memset(local_buffer,0,6);
		Occl.PSI_VALUE=0;
		if(G_occl_unit!=1)
		{
			sprintf((char *)local_buffer,"%02d",Occl.PSI_VALUE*presure_ratio[G_occl_unit]);
		}

		else
		{
			sprintf((char *)local_buffer,"%.1f",Occl.PSI_VALUE*presure_ratio[G_occl_unit]);
		}

		xpos=Letters_Alignments(0,75, (uint8_t*)local_buffer,0);
		TFT_String(xpos,DYN_VAL_POS,(uint8_t*)local_buffer,MAIN_FRAME_COL,YELLOW);

//		Font_Select(ARIAL_14);
//	    TFT_Number(80,140,xpos,YELLOW,RED);
  //*****************************************Battery_logo*************************************//

		if(!BATT.mode)
		{
			Battery_symbol();
			plug_symbol(PLUG_COL);
		}

	/****************************************PRESSURE BAR*******************************************************/

	/*******************bar with lines*******************/
//	Rectangle(25,140,30,50,BLACK);			//OUTER RECT //136-140
//	Rectangle(29,144,22,42,WHITE);
//	Rectangle(25,146,30,60,BLACK);			//OUTER RECT //136-140
//	Rectangle(29,150,22,50,WHITE);			//inner rect

//	Rectangle(25,160,30,1,BLACK);			// FIRST LINE
//	Rectangle(25,170,30,1,BLACK);			// SEC LINE
//	Rectangle(25,180,30,1,BLACK);			// THIRD LINE
//	Rectangle(25,190,30,1,BLACK);			// FOURTH LINE


//	for(loop_count=0;loop_count<=22;loop_count++)
	//	{
	//		Rectangle(29,191,loop_count,8,YELLOW);
	//		delay_us(1000);
	//	}
	//	for(loop_count=0;loop_count<=22;loop_count++)
	//	{
	//		Rectangle(29,181,loop_count,8,YELLOW);
	//		delay_us(1000);
	//	}
	//	for(loop_count=0;loop_count<=22;loop_count++)
	//	{
	//		Rectangle(29,171,loop_count,8,YELLOW);
	//		delay_us(1000);
	//	}
	//	for(loop_count=0;loop_count<=22;loop_count++)
	//	{
	//		Rectangle(29,161,loop_count,8,YELLOW);
	//		delay_us(1000);
	//	}
	//	for(loop_count=0;loop_count<=22;loop_count++)
	//	{
	//		Rectangle(29,151,loop_count,8,YELLOW);
	//		delay_us(1000);
	//	}

	/**********************************************************************/

//	Rectangle(10,160,30,62,BLACK);			//OUTER RECT //136-140
//
//	Rectangle(14,164,22,54,WHITE);			//inner rect
//
//	for(loop_count=0;loop_count<=40;loop_count++)
//	{
//	Rectangle(14,218-loop_count,22,0,(((100+(loop_count*2))<<16)+((200-(loop_count*3))<<8)+(30<<0)));
//	delay_us(500);
//	}

	//	for(loop_count=0;loop_count<=70;loop_count++)
	//	{
	//		Rectangle(29,150+loop_count,20,0,GREEN+(((loop_count)/5)<<5));
	//
	//		delay_us(700);
	//	}
	//	for(loop_count=0;loop_count<=22;loop_count++)
	//	{
	//		Rectangle(29,161,loop_count,23,YELLOW);
	//		delay_us(500);
	//	}
	//	for(loop_count=0;loop_count<=22;loop_count++)
	//	{
	//		Rectangle(29,150,loop_count,20,RED);
	//		delay_us(1000);
	//	}
	//	for(loop_count=0;loop_count<=22;loop_count++)
	//	{
	//		Rectangle(29,161,loop_count,8,YELLOW);
	//		delay_us(1000);
	//	}
	//	for(loop_count=0;loop_count<=22;loop_count++)
	//	{
	//		Rectangle(29,151,loop_count,8,YELLOW);
	//		delay_us(1000);
	//	}
//	TFT_ST7789V__rectangle_curve(92,86,229,62,0,WARNING_COLOR);

//		if((!G_Remaining_volume) && (G_Bolus_target_flag))
//		{
//			   Alarm(TARGET);
//			   G_Bolus_target_flag=0;
//		}

}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void FR_spliting(uint16_t flowrate)
{

	char FR_buffer[6];
	uint16_t xpos=0;
	uint16_t flowrate_view = 0;

    Font_Select(CALIBRI_43);

	flowrate_view = flowrate/10;//400

	if(flowrate_view == 0)
	{
	   xpos=219;
	}

	else
	{
     sprintf(FR_buffer,"%.d",flowrate_view);
     xpos=Flow_rate_Alignments((uint8_t*)FR_buffer);
    }

     //while(1);
     Font_Select(CALIBRI_43);
   	 TFT_Number(xpos,12+4,flowrate_view,MAIN_FRAME_COL,WHITE);

   	// Font_Select(CALIBRI_48);  //2-04
   	 TFT_String(256,12+4,(uint8_t *)".",MAIN_FRAME_COL,WHITE);		//2-04

   	 Font_Select(CALIBRI_35);
   	 TFT_Number(269,19,flowrate%10,MAIN_FRAME_COL,WHITE);

  }

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void FR_spliting_DD(uint16_t flowrate)
{

	char FR_buffer[6];
	char FR_buffer1[6];

	uint16_t xpos=0;
	uint16_t flowrate_view = 0;

	flowrate_view = flowrate/100;

	Font_Select(CALIBRI_35);

	sprintf(FR_buffer1,"%02d",flowrate%100);
	TFT_String(256,12+4,(uint8_t *)FR_buffer1,MAIN_FRAME_COL,WHITE);

	Font_Select(CALIBRI_43);

	sprintf(FR_buffer,"%d .",flowrate_view);
	xpos=Right_Alignments((uint8_t*)FR_buffer,256);
	TFT_String(xpos-3,12+4,(uint8_t *)FR_buffer,MAIN_FRAME_COL,WHITE);		//2-04


}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void FR_Lines()
{

	//Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	Rectangle(120,115,180,0,BLACK); 				  //Row Lines
	Rectangle(80,20,0,200,BLACK);  					  //Column Lines

}

//void scroll_bar(uint8_t option_no,uint8_t page_no,uint8_t total_option)     //(uint8_t prev_option, uint8_t curr_option, uint8_t page)
//{
//
//    	uint8_t updated_option= 0;
//	    updated_option=option_no+page_no*4;
//		Rectangle(306,38,9,165,WHITE);
//		Rectangle(307,38+((170/total_option)*updated_option),7,14,BLACK);
//
//}

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

void scroll_bar(uint8_t page_no,uint8_t option_no,uint8_t total_option)     //23-03                                  //(uint8_t prev_option, uint8_t curr_option, uint8_t page)
{
	uint8_t total_scroll=164,updated_option=0;
	float y_pos_bar;
	uint8_t height_of_bar=(total_scroll/total_option);


	if(height_of_bar<5)
	{
		height_of_bar=5;
		total_scroll=(total_scroll-height_of_bar);

	}

	        y_pos_bar=((float)total_scroll/total_option);
		    updated_option=(page_no*4)+option_no;
			Rectangle(306,38,9,165,LIGHT_GRAY_2);
			Rectangle(307,(39+(int)((y_pos_bar)*updated_option)),7,height_of_bar,BLACK);
}


/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void dose_rate_para(uint8_t start_cnt, uint8_t end_cnt)
{
	uint8_t loop_count = 0;
	uint16_t xpos=0;
	char local_buffer[10];
	Rectangle(95,(135+(25*start_cnt)),215,239-(135+(25*start_cnt)),MAIN_FRAME_COL);



	for(loop_count=start_cnt;loop_count<=end_cnt;loop_count++)
	{
		Font_Select(ARIAL_12);
		TFT_String(95,(135+(25*loop_count)),(uint8_t*)dose_para[loop_count-start_cnt],MAIN_FRAME_COL,WHITE);

		if(!start_cnt)
		{
			TFT_ST7789V__rectangle_curve(95,95,30,185+25,0,NEW_HDR_COL);
			Font_Select(ARIAL_12);
			TFT_String(105,102,(uint8_t*)Drug_Names[(dose.drug_select_no/4)][(dose.drug_select_no%4)],NEW_HDR_COL,BLACK);
		}

		if((start_cnt+loop_count)<=4)
		{
				if(loop_count==start_cnt)
				{
					Font_Select(ARIAL_12);
					TFT_String(250,(135+(25*loop_count)),(uint8_t*)"mL/Hr",MAIN_FRAME_COL,WHITE);

					sprintf(local_buffer,"%.1f",((float)dose.flow_rate/10.0));   	 //store the integer variables in to string using sprintf
					xpos=Right_Alignments((uint8_t*)local_buffer,230);   				 //(uint8_t*)letter
					TFT_writenumber_float(xpos,(135+(25*loop_count)),dose.flow_rate,MAIN_FRAME_COL,WHITE);
//					TFT_ST7789V__rectangle_curve(95,95,30,185+25,0,NEW_HDR_COL);
//					Font_Select(ARIAL_12);
//					TFT_String(105,102,(uint8_t*)Drug_Names[(dose.drug_select_no/4)][(dose.drug_select_no%4)],NEW_HDR_COL,BLACK);
				}
				else if(loop_count==start_cnt+1)
				{
					TFT_String(250,(135+(25*loop_count)),(uint8_t*)drug_unit[G_page_no][G_opt_no],MAIN_FRAME_COL,WHITE);
					sprintf(local_buffer,"%.1f",((float)dose.conc_value/10.0));    	//store the integer variables in to string using sprintf
					xpos=Right_Alignments((uint8_t*)local_buffer,230);    				//(uint8_t*)letter
					TFT_writenumber_float(xpos,(135+(25*loop_count)),dose.conc_value,MAIN_FRAME_COL,WHITE);
				}

				else if(loop_count==start_cnt+2)
				{
					TFT_String(250,(135+(25*loop_count)),(uint8_t*)"mL",MAIN_FRAME_COL,WHITE);
					sprintf(local_buffer,"%.1f",((float)INFUSED.ml/10.0));    	//store the integer variables in to string using sprintf
					xpos=Right_Alignments((uint8_t*)local_buffer,230);    				//(uint8_t*)letter
					TFT_writenumber_float_1d(xpos,(135+(25*loop_count)),(float)INFUSED.ml,MAIN_FRAME_COL,WHITE);
				}
				else if(loop_count==start_cnt+3)
				{
					TFT_String(250,(135+(25*loop_count)),(uint8_t*)"kg",MAIN_FRAME_COL,WHITE);
					sprintf(local_buffer,"%.1f",((float)dose.pat_weight/10.0));   	 //store the integer variables in to string using sprintf
					xpos=Right_Alignments((uint8_t*)local_buffer,230);   				 //(uint8_t*)letter
					TFT_writenumber_float(xpos,(135+(25*loop_count)),dose.pat_weight,MAIN_FRAME_COL,WHITE);  //28-03
				}
			}

	}



}
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
//void Battery_symbol(void)
//{
//	int8_t y_pos_adj=BATTERY_POS;
//    Rectangle(20,y_pos_adj,34,1,WHITE);				//Battery top line
//    Rectangle(20,22+y_pos_adj,34,1,WHITE);               //Battery Bottom Line
//	Rectangle(19,y_pos_adj,2,23,WHITE);               //First Left side Line
//	Rectangle(53,y_pos_adj,1,23,WHITE);               //Second Left side Line
//
//	Rectangle(54,6+y_pos_adj,5,10,WHITE);				//Battery outer rect
//
//	Rectangle(26,4+y_pos_adj,4,14,LIGHT_GREEN);			    //First  Rectangle Box
//    Rectangle(35,4+y_pos_adj,4,14,LIGHT_GREEN);			    //Second Rectangle Box
//    Rectangle(44,4+y_pos_adj,4,14,LIGHT_GREEN);               //Third Rectangle Box
//
////    TFT_ST7789V_circle1(20,110+y_pos_adj,7,0XD4AA3A,0XD4AA3A);   //left quadrant circle for mains symbol
////    TFT_ST7789V_circle3(20,110+y_pos_adj,7,0XD4AA3A,0XD4AA3A);   //right quadrant circle for mains symbol
////
////    Rectangle(19,117+y_pos_adj,2,2,0XD4AA3A);               //mains symbol line
////    Rectangle(17,103+y_pos_adj,1,4,0XD4AA3A);                 //left plugin line
////    Rectangle(22,103+y_pos_adj,1,4,0XD4AA3A);                 //right plugin line
////    Rectangle(16,108+y_pos_adj,8,2,0XD4AA3A);
//}

//void plug_symbol(void)
//{
//	int8_t y_pos_adj=BATTERY_POS;
//	int8_t x_pos_adj=-9;
//	TFT_ST7789V_circle1(20+x_pos_adj,6+y_pos_adj,7,0XD4AA3A,0XD4AA3A);   //left quadrant circle for mains symbol
//	    TFT_ST7789V_circle3(20+x_pos_adj,6+y_pos_adj,7,0XD4AA3A,0XD4AA3A);   //right quadrant circle for mains symbol
//
//	    Rectangle(19+x_pos_adj,13+y_pos_adj,2,4,0XD4AA3A);               //mains symbol line
//	    Rectangle(17+x_pos_adj,y_pos_adj,1,3,0XD4AA3A);                 //left plugin line
//	    Rectangle(22+x_pos_adj,y_pos_adj,1,3,0XD4AA3A);                 //right plugin line
//	    Rectangle(16+x_pos_adj,4+y_pos_adj,8,2,0XD4AA3A);
//
//	    Rectangle(19+x_pos_adj,17+y_pos_adj,8,2,0XD4AA3A);
//}

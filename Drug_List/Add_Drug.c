
#include "LPC55S16.h"			//22-03
#include "Color.h"
#include "keypad.h"
#include "Shapes.h"
#include "TFT_Commands.h"
#include "Driver_Timer.h"
#include "TFT_String.h"
#include <string.h>
#include "Driver_I2C.h"
#include "Power_off.h"
#include "sound.h"
#include <Boot_up.h>



uint8_t drug_L=0;
uint8_t drug_R=0;
uint16_t blink_drug_delay=0;
uint8_t drug_add=0;
uint8_t blink_drug_rect=0;
uint8_t drug_char_change_flg=0;//ZOOZ_2
uint8_t mute_char_change_flg=0;//ZOOZ_2
uint8_t symbol_flg=0;//ZOOZ_2


char drug_array_R[15]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
char drug_array_L[15]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};

char drug_alpha;
char drug_chr_change_arr[4][2]={
								{97,122},
								{65,90},
								{48,57},
								{45,47}
						};//ZOOZ_2

extern uint16_t total_drugs;
extern  uint16_t custom_new_no;
extern uint8_t brand_select_no;//ZOOZ_2
extern uint8_t total_brand;//ZOOZ_2
extern char Drug_Names[150][4][20];
extern uint8_t auto_lock_time;    //ZOOZ_1
extern char Brand_Names[6][4][15];//ZOOZ_2

extern void Frame_Header(uint32_t BG_color, uint32_t TXT_color ,uint8_t *word);
//extern void Frame_Footer(uint32_t BG_color, uint32_t TXT_color,uint8_t *word,uint8_t *circle_word,uint8_t circle_pos,uint8_t radius)
extern void TFT_ST7789V__rectangle_curve(uint16_t xpos1, uint16_t ypos1, uint16_t width,uint16_t height,uint16_t radius,uint32_t colour);
extern void Font_Select(uint8_t Font_Size);
extern uint16_t TFT_String(uint16_t xpos, uint16_t ypos,const uint8_t *asciistr,uint32_t BG_COL,uint32_t TXT_COL);
extern void Rectangle(uint16_t x_axis,uint16_t y_axis,uint16_t Length,uint16_t Height,uint32_t Color);
extern void TFT_Number(uint16_t xpos,uint16_t ypos,uint32_t number,uint32_t boarder_color,uint32_t fill_color);
extern uint8_t ON_Flag;
//void add_drug_dis(void);
void add_drug_dis(uint8_t ID_flag);//ZOOZ_2


/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void add_data_base (uint8_t ID_flag,uint16_t db_sel_no)
{
//	uint8_t drug_prev_flg=0;
	uint8_t blink_drug_rect=0;
	uint8_t add_drug_variable=1;
 // uint8_t time_interval=30;//common_bug    //ZOOZ_1
	char drug_alpha=0;
//	uint8_t menu_flg=0;
	uint8_t cnt=0;
	uint16_t cursor_end=0;
	uint16_t str_return=8;
	uint16_t loop_count=0;

	char* custom_data1="(+).Add Brand";
	char* custom_data2="(+).Add Drug";

	drug_L=0;
	drug_R=0;

	symbol_flg=0;
	mute_char_change_flg=0;
	drug_char_change_flg=0;
	POW.power_status_flag=1;//26-03

	if(!ID_flag)
	{
		if((db_sel_no!=total_drugs))	// which denoted already edited drug name to present in text field
		{

			for(loop_count=0;loop_count<15;loop_count++)
			{
				drug_array_L[loop_count]=Drug_Names[db_sel_no/4][db_sel_no%4][loop_count];

				drug_array_R[loop_count]='\0';

				if(drug_array_L[loop_count]!='\0')
				{
					drug_L++;

				}
				else
				{
					drug_array_R[loop_count]='\0';
					break;
				}


			}


		}
		else
		{


			for(loop_count=0;loop_count<15;loop_count++)
			{
				drug_array_L[loop_count]='\0';
				drug_array_R[loop_count]='\0';
			}
		}
	}
	else
	{
		if((db_sel_no!=total_brand))
		{
			for(loop_count=0;loop_count<15;loop_count++)
			{
				drug_array_L[loop_count]=Brand_Names[db_sel_no/4][db_sel_no%4][loop_count];
				drug_array_R[loop_count]='\0';

				if(drug_array_L[loop_count]!='\0')
				{
					drug_L++;

				}
				else
				{
					drug_array_R[loop_count]='\0';
					break;
				}


			}


		}
		else
		{


			for(loop_count=0;loop_count<15;loop_count++)
			{
				drug_array_L[loop_count]='\0';
				drug_array_R[loop_count]='\0';
			}
		}

	}



	while(add_drug_variable)
	{
		Power_off();	//02-04
		if(!ON_Flag)
		{
			break;
		}

		else if(POW.power_status_flag)
		{
			POW.power_status_flag=0;
			add_drug_dis(ID_flag);
			Font_Select(ARIAL_20);
			str_return=TFT_String(8,80,(uint8_t *)drug_array_L,WHITE,BLACK);


			if(str_return<8)
			{
				str_return=8;
			}

			TFT_String(str_return,80,(uint8_t *)drug_array_R,WHITE,BLACK);
			while(KEY.value);
		}


		if(!blink_drug_delay)
		{

			if(blink_drug_rect==0)
			{
				Rectangle((str_return-2),108,15,1,BLACK);
				blink_drug_rect=1;

			}
			else if(blink_drug_rect==1)
			{
				Rectangle((str_return-2),108,15,1,WHITE);
				blink_drug_rect=0;
			}
			blink_drug_delay=5;

		}

		            if(KEY.value)
					{
						auto_lock_time=AUTO_EXIT_TIME;
					}
					if(!auto_lock_time)
					{
						add_drug_variable=0;
						break;

					}


		switch(KEY.value)
		{

		case UP_KEY:
					beep_sound();

					Font_Select(ARIAL_20);
					if(drug_array_R)
					{

						TFT_String(str_return,80,(uint8_t *)drug_array_R,WHITE,WHITE);
					}



					if(symbol_flg==0)
					{
						if((drug_alpha<drug_chr_change_arr[mute_char_change_flg+2][1])&&
						(drug_alpha>=drug_chr_change_arr[mute_char_change_flg+2][0]))	//max
						{

							drug_alpha+=1;

						}
						else
						{
							drug_alpha=drug_chr_change_arr[mute_char_change_flg+2][0];

						}
					}
					else
					{
						if((drug_alpha<drug_chr_change_arr[drug_char_change_flg][1])&&
						(drug_alpha>=drug_chr_change_arr[drug_char_change_flg][0]))	//max
						{

							drug_alpha+=1;

						}
						else
						{
							drug_alpha=drug_chr_change_arr[drug_char_change_flg][0];

						}

					}
					drug_array_R[0]=drug_alpha;



					TFT_String(str_return,80,(uint8_t *)drug_array_R,WHITE,BLACK);



					while(KEY.value);
					break;



					case DOWN_KEY:
					beep_sound();

					Font_Select(ARIAL_20);
					if(drug_array_R)
					{
						TFT_String(str_return,80,(uint8_t *)drug_array_R,WHITE,WHITE);
					}

					if(symbol_flg==0)
					{
						if((drug_alpha>drug_chr_change_arr[mute_char_change_flg+2][0])&&
						(drug_alpha<=drug_chr_change_arr[mute_char_change_flg+2][1]))
						{
							drug_alpha-=1;
						}
						else
						{
							drug_alpha=drug_chr_change_arr[mute_char_change_flg+2][1];
						}
					}

					else
					{
						if((drug_alpha>drug_chr_change_arr[drug_char_change_flg][0])&&
						(drug_alpha<=drug_chr_change_arr[drug_char_change_flg][1]))
						{
							drug_alpha-=1;
						}
						else
						{
							drug_alpha=drug_chr_change_arr[drug_char_change_flg][1];
						}
					}

					drug_array_R[0]=drug_alpha;


					TFT_String(str_return,80,(uint8_t *)drug_array_R,WHITE,BLACK);

					while(KEY.value);
					break;



			case MENU_KEY:

			beep_sound();


			//Font_Select(ARIAL_20);

			TFT_String(str_return,80,(uint8_t *)drug_array_R,WHITE,WHITE);
			//if(drug_prev_flg<2)
			//drug_prev_flg=drug_char_change_flg;
			if(!symbol_flg)
			{
				symbol_flg=1;
				TFT_ST7789V__rectangle_curve(108,160,40,103,0,WHITE);
				TFT_ST7789V_lcd_drawcircle1(130,180,19,MAIN_FRAME_COL,MAIN_FRAME_COL);
				Font_Select(ARIAL_9);
				TFT_ST7789V_Mute_Symbol_12pt(174,121,0,MAIN_FRAME_COL,WHITE);

				Font_Select(ARIAL_14);

				if(!mute_char_change_flg)
				{
					TFT_String(160,170,(uint8_t*)"12",WHITE,BLACK);
				}
				else
				{
					TFT_String(160,170,(uint8_t*)"/#",WHITE,BLACK);
				}



				Font_Select(ARIAL_9);

				TFT_ST7789V__rectangle_curve(3,160,40,103,0,ORANGE);
				TFT_ST7789V_lcd_drawcircle1(25,180,19,WHITE,MAIN_FRAME_COL);
			//	TFT_ST7789V_Mute_Symbol_12pt(175,18,0,MAIN_FRAME_COL,WHITE);
				TFT_String(12,175,(uint8_t*)"Men",MAIN_FRAME_COL,WHITE);
			}

			else
			{
				if(drug_char_change_flg)
				{
					drug_char_change_flg=0;
				}
				else
				{
					drug_char_change_flg=1;
				}
			}

			Font_Select(ARIAL_14);

			if(drug_char_change_flg==0)
			{
				drug_alpha=97;
			//	drug_char_change_flg=1;
				TFT_String(50,170,(uint8_t*)"A-Z",ORANGE,ORANGE);
				TFT_String(50,170,(uint8_t*)"a-z",ORANGE,BLACK);

			}
			else
			{
				drug_alpha=65;
			//	drug_char_change_flg=0;
				TFT_String(50,170,(uint8_t*)"a-z",ORANGE,ORANGE);
				TFT_String(50,170,(uint8_t*)"A-Z",ORANGE,BLACK);

			}

			drug_array_R[0]=drug_alpha;

			Font_Select(ARIAL_20);
			TFT_String(str_return,80,(uint8_t *)drug_array_R,WHITE,BLACK);

			while(KEY.value);
			break;


			case MUTE_KEY:

				beep_sound();
				//	symbol_flg=0;
				Font_Select(ARIAL_20);

				TFT_String(str_return,80,(uint8_t *)drug_array_R,WHITE,WHITE);

				//if(drug_prev_flg>2)
				//drug_prev_flg=drug_char_change_flg;
				if(symbol_flg)
				{
					symbol_flg=0;
					TFT_ST7789V__rectangle_curve(3,160,40,103,0,WHITE);
					TFT_ST7789V_lcd_drawcircle1(25,180,19,WHITE,MAIN_FRAME_COL);
					//TFT_ST7789V_Mute_Symbol_12pt(175,18,0,MAIN_FRAME_COL,WHITE);
					Font_Select(ARIAL_9);
					TFT_String(12,175,(uint8_t*)"Men",MAIN_FRAME_COL,WHITE);

					Font_Select(ARIAL_14);

					if(!drug_char_change_flg)
					{
						TFT_String(50,170,(uint8_t*)"a-z",WHITE,BLACK);
					}
					else
					{
						TFT_String(50,170,(uint8_t*)"A-Z",WHITE,BLACK);
					}


					Font_Select(ARIAL_9);
					TFT_ST7789V__rectangle_curve(108,160,40,103,0,ORANGE);
					TFT_ST7789V_lcd_drawcircle1(130,180,19,MAIN_FRAME_COL,MAIN_FRAME_COL);
					//TFT_String(116,175,(uint8_t*)"Men",MAIN_FRAME_COL,WHITE);
					TFT_ST7789V_Mute_Symbol_12pt(174,121,0,MAIN_FRAME_COL,WHITE);
				}

				else
				{
					if(mute_char_change_flg)
					{
						mute_char_change_flg=0;
					}
					else
					{
						mute_char_change_flg=1;
					}
				}

				Font_Select(ARIAL_14);
				if(mute_char_change_flg==0)
				{
					drug_alpha=48;
					//	mute_char_change_flg=1;
					TFT_String(160,170,(uint8_t*)"/#",ORANGE,ORANGE);
					TFT_String(160,170,(uint8_t*)"12",ORANGE,BLACK);
				}

				else
				{
					drug_alpha=45;
					//	mute_char_change_flg=0;
					TFT_String(160,170,(uint8_t*)"12",ORANGE,ORANGE);
					TFT_String(160,170,(uint8_t*)"/#",ORANGE,BLACK);
				}
				drug_array_R[0]=drug_alpha;
				Font_Select(ARIAL_20);
				TFT_String(str_return,80,(uint8_t *)drug_array_R,WHITE,BLACK);


				while(KEY.value);
				break;

			case BOLUS_KEY:
			if((drug_array_R[0]=='\0')&&(drug_L))
			{
				beep_sound();
				Font_Select(ARIAL_20);

				drug_L--;
				Rectangle(str_return-2,108,15,1,WHITE);
				str_return=TFT_String(8,80,(uint8_t *)drug_array_L,WHITE,WHITE);
				drug_array_L[drug_L]='\0';
				str_return=TFT_String(8,80,(uint8_t *)drug_array_L,WHITE,BLACK);
			}

			while(KEY.value);
			break;


			case RIGHT_KEY:

				beep_sound();
				if(drug_array_R[0]!='\0')
				{
					if(drug_L<=12)
					{
						Font_Select(ARIAL_20);
						drug_array_L[drug_L]=drug_array_R[0];						//	right array first posi shift to left array last posi
						drug_L+=1;										//	left array vari will be inc
						cursor_end=drug_L;
							if(drug_R>0)										//	left array element in greater than 0
							{
								for(cnt=0;cnt<drug_R;cnt++)					//	variable will be decr defs on right side array variable
								{

									drug_array_R[cnt]=drug_array_R[cnt+1];			//added right side varible to store right side data

								}
								drug_array_R[drug_R]='\0';						//right array will be null
								drug_R--;									// right array variable will be dec

									if(!drug_R)
									{
										drug_array_R[0]=65;
									}

									drug_alpha=drug_array_R[0];							//right array first posi to load alpha

							}
							else
							{
								drug_alpha=drug_chr_change_arr[drug_char_change_flg][0];
								drug_alpha=drug_alpha-1;
								drug_array_R[0]='\0';
							}

							Rectangle(str_return-2,108,15,1,WHITE);
							str_return=TFT_String(8,80,(uint8_t *)drug_array_L,WHITE,BLACK);
					}
				}

			while(KEY.value);
			break;

			case OK_KEY:

				beep_sound();
				strcat((char *)drug_array_L,(char *)drug_array_R);
				Font_Select(ARIAL_14);
				drug_add=strlen((char *)drug_array_L);

				if(drug_add) // 27-03
				{
					add_drug_variable=0;
					if(!ID_flag)
					{
						for(loop_count=0;loop_count<15;loop_count++)
						{
							if(loop_count<drug_add)
							{

								Drug_Names[db_sel_no/4][db_sel_no%4][loop_count]=drug_array_L[loop_count];
							}

							else
							{
								Drug_Names[db_sel_no/4][db_sel_no%4][loop_count]='\0';
							}

							EEPROM_datawrite(EEPROM_DRUG_NAMES+((db_sel_no-500)*15)+loop_count,Drug_Names[db_sel_no/4][db_sel_no%4][loop_count],1);  //22-03
						}

							if(db_sel_no==total_drugs)
							{

								total_drugs++;
								Font_Select(ARIAL_14); //22-03
								EEPROM_datawrite(EEPROM_TOTAL_DRUG,total_drugs,2);

							}

							for(loop_count=0;loop_count<15;loop_count++)
							{
								Drug_Names[total_drugs/4][total_drugs%4][loop_count]=custom_data2[loop_count];
							}
							//Rectangle(0,0,320,240,MAIN_FRAME_COL);
							CLRSCR(MAIN_FRAME_COL);
					}

					else
					{
						for(loop_count=0;loop_count<15;loop_count++)
						{
							if(loop_count<drug_add)
							{

								Brand_Names[db_sel_no/4][db_sel_no%4][loop_count]=drug_array_L[loop_count];
							}
							else
							{
								Brand_Names[db_sel_no/4][db_sel_no%4][loop_count]='\0';
							}


							EEPROM_datawrite(EEPROM_BRAND_NAMES+((db_sel_no-8)*15)+loop_count,Brand_Names[db_sel_no/4][db_sel_no%4][loop_count],1); //22-03
						}
						if(db_sel_no==total_brand)   //22-03
						{
							if(db_sel_no<19)
							{
								total_brand++;
								for(loop_count=0;loop_count<15;loop_count++) //22-03
								{
									Brand_Names[total_brand/4][total_brand%4][loop_count]=custom_data1[loop_count];
								}
							}
							Font_Select(ARIAL_14);

							EEPROM_datawrite(EEPROM_TOTAL_BRAND,total_brand,1);


						}
					}
				}


			while(KEY.value);
			break;


			case BACK_KEY:
			beep_sound();
			add_drug_variable=0;
			Rectangle(3,36,320,169,MAIN_FRAME_COL);
			while(KEY.value);
			break;


		}
	}

	}//ZOOZ_2
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
void add_drug_dis(uint8_t ID_flag)//ZOOZ_2
{

	//Rectangle(0,0,320,240,MAIN_FRAME_COL);
	CLRSCR(MAIN_FRAME_COL);
	if(!ID_flag)
	{
		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Add Drug");
	}
	else
	{
		Frame_Header(NEW_HDR_COL,HDR_TXT_COL,(uint8_t*)"Add Brand");
	}
	Frame_Footer(NEW_FTR_COL,HDR_TXT_COL,(uint8_t*)"Press        to confirm",(uint8_t*)"OK",2,14);

	Rectangle(5,60,310,70,WHITE);

	TFT_ST7789V__rectangle_curve(213,160,40,103,0,WHITE);
	TFT_ST7789V_lcd_drawcircle1(235,180,19,MAIN_FRAME_COL,MAIN_FRAME_COL);
	Font_Select(ARIAL_9);
	TFT_String(224,175,(uint8_t*)"Bol",MAIN_FRAME_COL,WHITE);
	Font_Select(ARIAL_14);
	TFT_String(270,170,(uint8_t*)"Del",WHITE,BLACK);

		if(symbol_flg)
		{
			TFT_ST7789V__rectangle_curve(108,160,40,103,0,WHITE);
			TFT_ST7789V_lcd_drawcircle1(130,180,19,MAIN_FRAME_COL,MAIN_FRAME_COL);
			Font_Select(ARIAL_9);
			TFT_ST7789V_Mute_Symbol_12pt(174,121,0,MAIN_FRAME_COL,WHITE);
			Font_Select(ARIAL_14);

			if(!drug_char_change_flg)
			{
				TFT_String(50,170,(uint8_t*)"a-z",WHITE,BLACK);
			}
			else
			{
				TFT_String(50,170,(uint8_t*)"A-Z",WHITE,BLACK);
			}

				Font_Select(ARIAL_9);
				TFT_ST7789V__rectangle_curve(3,160,40,103,0,ORANGE);
				TFT_ST7789V_lcd_drawcircle1(25,180,19,WHITE,MAIN_FRAME_COL);
				TFT_String(12,175,(uint8_t*)"Men",MAIN_FRAME_COL,WHITE);

				Font_Select(ARIAL_14);
				if(mute_char_change_flg==0)
				{
					TFT_String(160,170,(uint8_t*)"12",ORANGE,BLACK);
				}
				else
				{
					TFT_String(160,170,(uint8_t*)"/#",ORANGE,BLACK);
				}
		}

		else
		{
			TFT_ST7789V__rectangle_curve(3,160,40,103,0,WHITE);
			TFT_ST7789V_lcd_drawcircle1(25,180,19,WHITE,MAIN_FRAME_COL);
			Font_Select(ARIAL_9);
			TFT_String(12,175,(uint8_t*)"Men",MAIN_FRAME_COL,WHITE);
			Font_Select(ARIAL_14);
				if(mute_char_change_flg==0)
				{
					TFT_String(50,170,(uint8_t*)"a-z",WHITE,BLACK);
				}
				else
				{
					TFT_String(50,170,(uint8_t*)"A-Z",WHITE,BLACK);
				}


				//1	Font_Select(ARIAL_9);
				TFT_ST7789V__rectangle_curve(108,160,40,103,0,ORANGE);
				TFT_ST7789V_lcd_drawcircle1(130,180,19,MAIN_FRAME_COL,MAIN_FRAME_COL);
				TFT_ST7789V_Mute_Symbol_12pt(174,121,0,MAIN_FRAME_COL,WHITE);

				Font_Select(ARIAL_14);

					if(!drug_char_change_flg)
					{
						TFT_String(160,170,(uint8_t*)"12",ORANGE,BLACK);
					}
					else
					{
						TFT_String(160,170,(uint8_t*)"/#",ORANGE,BLACK);
					}

		}
}

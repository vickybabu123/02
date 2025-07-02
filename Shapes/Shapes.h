#define VER_TEXT_SPACE_1		 		44


#define VER_TEXT_SPACE		 		42          //45
#define VER_TEXT_SPACE_			135
#define INITIAL_TEXT_POS			48          //50

#define INITIAL_SHAPE_POSITION	37
#define END_SHAPE_POSITION			34
#define DIFF_BTW_SHAPES				44

#define INITIAL_SHAPE_POSITION_1 42

#define wide		1
#define Space		65

void Rectangle(uint16_t x_axis,uint16_t y_axis,uint16_t Length,uint16_t Height,uint32_t Color);
uint16_t  __24_bit_to_16_bit_color(uint32_t Color);
void TFT_ST7789V__rectangle_curve(uint16_t xpos1, uint16_t ypos1, uint16_t width,uint16_t height,uint16_t radius,uint32_t colour);
void TFT_ST7789V__rectangle_curve_1(uint16_t xpos1, uint16_t ypos1, uint16_t width,uint16_t height,uint16_t radius,uint32_t colour);
void TFT_ST7789V_circle(uint16_t xpos, uint16_t ypos, uint16_t radius, uint32_t boarder_color, uint32_t fill_color);
void TFT_ST7789V_circle1(uint16_t xpos, uint16_t ypos, uint16_t radius, uint32_t boarder_color, uint32_t fill_color);
void TFT_ST7789V_circle2(uint16_t xpos, uint16_t ypos, uint16_t radius, uint32_t boarder_color, uint32_t fill_color);
void TFT_ST7789V_circle3(uint16_t xpos, uint16_t ypos, uint16_t radius, uint32_t boarder_color, uint32_t fill_color);
void TFT_ST7789V_lcd_drawcircle1(uint16_t xpos, uint16_t ypos, uint16_t radius, uint32_t boarder_color, uint32_t fill_color);
void TFT_ST7789V_lcd_drawcircle1_Battery_Logo(uint16_t xpos, uint16_t ypos, uint16_t radius, uint32_t boarder_color, uint32_t fill_color);
void TFT_ST7789V_lcd_shapes(int x1, int width, int y1, int height, uint32_t ch );
void footer_curve();



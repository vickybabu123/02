#include "LPC55S16.h"
#include "TFT_Commands.h"
#include "Symbol.h"

const uint8_t Left_Right_Arrow_14ptBitmaps[];
const uint8_t up_down_arrow_20ptBitmaps[];
const uint8_t Left_arrow_35ptBitmaps[];
const uint8_t segoeFluentIcons_25ptBitmaps[] ;
const uint8_t segoeUIEmoji_24ptBitmaps[] ;
const uint8_t segoeFluentIcons_12ptBitmaps[];
const uint8_t segoeFluentIcons_9ptBitmaps[];
const uint8_t wingdings3_24ptBitmaps[];
const uint8_t arial_7ptBitmaps[];
const uint8_t webdings_22ptBitmaps[];
const uint8_t wingdings3_R_ARROW_20ptBitmaps[];
const uint8_t Warning_symbol_18ptBitmaps[];
const uint8_t Mute_Symbol_12pt[];
const uint8_t wingdings3_L_ARROW_13ptBitmaps[];
const uint8_t segoeFluentIcons_91ptBitmaps[];
const uint8_t keylock4[];
const uint8_t keyunlock4[];
const uint8_t tick_14[];//22-03
const uint8_t search[];//22-03
const uint8_t segoeFluentIcons_18ptBitmaps[];

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
const uint8_t search[] =
{
	// @0 '' (28 pixels wide)
	0x00, 0xFC, 0x00, 0x00, //         ######
	0x07, 0xFF, 0x80, 0x00, //      ############
	0x0F, 0x03, 0xC0, 0x00, //     ####      ####
	0x1C, 0x00, 0xE0, 0x00, //    ###          ###
	0x38, 0x00, 0x70, 0x00, //   ###            ###
	0x70, 0x00, 0x38, 0x00, //  ###              ###
	0x60, 0x00, 0x18, 0x00, //  ##                ##
	0x60, 0x00, 0x18, 0x00, //  ##                ##
	0xC0, 0x00, 0x0C, 0x00, // ##                  ##
	0xC0, 0x00, 0x0C, 0x00, // ##                  ##
	0xC0, 0x00, 0x0C, 0x00, // ##                  ##
	0xC0, 0x00, 0x0C, 0x00, // ##                  ##
	0xC0, 0x00, 0x0C, 0x00, // ##                  ##
	0xC0, 0x00, 0x0C, 0x00, // ##                  ##
	0x60, 0x00, 0x18, 0x00, //  ##                ##
	0x60, 0x00, 0x18, 0x00, //  ##                ##
	0x70, 0x00, 0x38, 0x00, //  ###              ###
	0x38, 0x00, 0x70, 0x00, //   ###            ###
	0x1C, 0x00, 0xF0, 0x00, //    ###          ####
	0x0F, 0x03, 0xF8, 0x00, //     ####      #######
	0x07, 0xFF, 0x9C, 0x00, //      ############  ###
	0x00, 0xFC, 0x0E, 0x00, //         ######      ###
	0x00, 0x00, 0x07, 0x00, //                      ###
	0x00, 0x00, 0x03, 0x80, //                       ###
	0x00, 0x00, 0x01, 0xC0, //                        ###
	0x00, 0x00, 0x00, 0xE0, //                         ###
	0x00, 0x00, 0x00, 0x70, //                          ###
	0x00, 0x00, 0x00, 0x30, //                           ##
};

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
const uint8_t segoeFluentIcons_18ptBitmaps[] =
{
	// @0 '' (23 pixels wide)
	0x00, 0xC0, 0x00, //         ##
	0x07, 0xFC, 0x00, //      #########
	0x1E, 0x1E, 0x00, //    ####    ####
	0x3C, 0x07, 0x00, //   ####       ###
	0x38, 0x03, 0x80, //   ###         ###
	0x70, 0x01, 0x80, //  ###           ##
	0x60, 0x01, 0xC0, //  ##            ###
	0x60, 0x01, 0xC0, //  ##            ###
	0x60, 0x01, 0xC0, //  ##            ###
	0xE0, 0x01, 0xC0, // ###            ###
	0x60, 0x01, 0xC0, //  ##            ###
	0x70, 0x01, 0xC0, //  ###           ###
	0x70, 0x03, 0x80, //  ###          ###
	0x38, 0x03, 0x00, //   ###         ##
	0x1C, 0x0F, 0x80, //    ###      #####
	0x0F, 0xFF, 0xC0, //     ##############
	0x03, 0xF9, 0xE0, //       #######  ####
	0x00, 0x00, 0xF0, //                 ####
	0x00, 0x00, 0x78, //                  ####
	0x00, 0x00, 0x3C, //                   ####
	0x00, 0x00, 0x1C, //                    ###
	0x00, 0x00, 0x0E, //                     ###
};
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
const uint8_t tick_14[] =                     //22-03
{
			// @0 'a' (13 pixels wide)
			0x00, 0x18, //            ##
			0x00, 0x38, //           ###
			0x00, 0x78, //          ####
			0x00, 0xF8, //         #####
			0xC1, 0xF8, // ##     ######
			0xE3, 0xF8, // ###   #######
			0xF7, 0xF0, // #### #######
			0xFF, 0xE0, // ###########
			0xFF, 0xC0, // ##########
			0xFF, 0x80, // #########
			0x7F, 0x00, //  #######
			0x3E, 0x00, //   #####
			0x1C, 0x00, //    ###


};
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
const uint8_t keylock4[] =
{
	// @0 '' (22 pixels wide)
	0x00, 0xFC, 0x00, //         ######
	0x03, 0xFF, 0x00, //       ##########
	0x07, 0x87, 0x80, //      ####    ####
	0x07, 0x03, 0x80, //      ###      ###
	0x0E, 0x01, 0xC0, //     ###        ###
	0x0E, 0x01, 0xC0, //     ###        ###
	0x0C, 0x00, 0xC0, //     ##          ##
	0x0C, 0x00, 0xC0, //     ##          ##
	0x0C, 0x00, 0xC0, //     ##          ##
	0x0C, 0x00, 0xC0, //     ##          ##
	0x3F, 0xFF, 0xF0, //   ##################
	0x7F, 0xFF, 0xF8, //  ####################
	0x60, 0x00, 0x18, //  ##                ##
	0xE0, 0x00, 0x1C, // ###                ###
	0xE0, 0x00, 0x1C, // ###                ###
	0xE0, 0x00, 0x1C, // ###                ###
	0xE0, 0x00, 0x1C, // ###                ###
	0xE0, 0x78, 0x1C, // ###      ####      ###
	0xE0, 0x78, 0x1C, // ###      ####      ###
	0xE0, 0x78, 0x1C, // ###      ####      ###
	0xE0, 0x00, 0x1C, // ###                ###
	0xE0, 0x00, 0x1C, // ###                ###
	0xE0, 0x00, 0x1C, // ###                ###
	0xE0, 0x00, 0x1C, // ###                ###
	0xE0, 0x00, 0x1C, // ###                ###
	0x7F, 0xFF, 0xF8, //  ####################
	0x3F, 0xFF, 0xF0, //   ##################
};
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
const uint8_t keyunlock4[] =
{
	// @0 '' (22 pixels wide)
	0x00, 0xFC, 0x00, //         ######
	0x03, 0xFF, 0x00, //       ##########
	0x07, 0x87, 0x80, //      ####    ####
	0x07, 0x03, 0x80, //      ###      ###
	0x0E, 0x01, 0xC0, //     ###        ###
	0x0E, 0x00, 0x00, //     ###
	0x0C, 0x00, 0x00, //     ##
	0x0C, 0x00, 0x00, //     ##
	0x0C, 0x00, 0x00, //     ##
	0x0C, 0x00, 0x00, //     ##
	0x3F, 0xFF, 0xF0, //   ##################
	0x7F, 0xFF, 0xF8, //  ####################
	0x60, 0x00, 0x18, //  ##                ##
	0xE0, 0x00, 0x1C, // ###                ###
	0xE0, 0x00, 0x1C, // ###                ###
	0xE0, 0x00, 0x1C, // ###                ###
	0xE0, 0x00, 0x1C, // ###                ###
	0xE0, 0x78, 0x1C, // ###      ####      ###
	0xE0, 0x78, 0x1C, // ###      ####      ###
	0xE0, 0x78, 0x1C, // ###      ####      ###
	0xE0, 0x00, 0x1C, // ###                ###
	0xE0, 0x00, 0x1C, // ###                ###
	0xE0, 0x00, 0x1C, // ###                ###
	0xE0, 0x00, 0x1C, // ###                ###
	0xE0, 0x00, 0x1C, // ###                ###
	0x7F, 0xFF, 0xF8, //  ####################
	0x3F, 0xFF, 0xF0, //   ##################
};
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
const uint8_t Mute_Symbol_12pt[] =
{
	// @0 '' (16 pixels wide)
	0x01, 0x80, //        ##
	0x03, 0x80, //       ###
	0x07, 0x80, //      ####
	0x0F, 0xB3, //     ##### ##  ##
	0xFF, 0xB3, // ######### ##  ##
	0xFF, 0x9E, // #########  ####
	0xFF, 0x8C, // #########   ##
	0xFF, 0x8C, // #########   ##
	0xFF, 0x8C, // #########   ##
	0xFF, 0x9E, // #########  ####
	0xFF, 0xB3, // ######### ##  ##
	0x0F, 0xB3, //     ##### ##  ##
	0x07, 0x80, //      ####
	0x03, 0x80, //       ###
	0x01, 0x80, //        ##
};
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
//const uint8_t Warning_symbol_18ptBitmaps[] =
//{
//	// @0 'r' (25 pixels wide)
//	0x00, 0x1C, 0x00, 0x00, //            ###
//	0x00, 0x1C, 0x00, 0x00, //            ###
//	0x00, 0x3E, 0x00, 0x00, //           #####
//	0x00, 0x77, 0x00, 0x00, //          ### ###
//	0x00, 0x63, 0x00, 0x00, //          ##   ##
//	0x00, 0xE3, 0x80, 0x00, //         ###   ###
//	0x00, 0xC1, 0x80, 0x00, //         ##     ##
//	0x01, 0xC1, 0xC0, 0x00, //        ###     ###
//	0x01, 0x80, 0xC0, 0x00, //        ##       ##
//	0x03, 0x00, 0x60, 0x00, //       ##         ##
//	0x07, 0x00, 0x70, 0x00, //      ###         ###
//	0x06, 0x00, 0x30, 0x00, //      ##           ##
//	0x0E, 0x00, 0x38, 0x00, //     ###           ###
//	0x0C, 0x00, 0x18, 0x00, //     ##             ##
//	0x18, 0x00, 0x0C, 0x00, //    ##               ##
//	0x18, 0x00, 0x0C, 0x00, //    ##               ##
//	0x30, 0x00, 0x06, 0x00, //   ##                 ##
//	0x70, 0x00, 0x07, 0x00, //  ###                 ###
//	0x7F, 0xFF, 0xFF, 0x00, //  #######################
//	0xFF, 0xFF, 0xFF, 0x80, // #########################
//};
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
const uint8_t Warning_symbol_18ptBitmaps[] =
{
	// @0 'r' (25 pixels wide)
	0x00, 0x3E, 0x00,  //           #####
	0x00, 0x7F, 0x00,  //          ### ###
	0x00, 0xE3, 0x80,  //         ###   ###
	0x00, 0xC1, 0x80,  //         ##     ##
	0x01, 0xC1, 0xC0,  //        ###     ###
	0x01, 0x80, 0xC0,  //        ##       ##
	0x03, 0x00, 0x60,  //       ##         ##
	0x03, 0x00, 0x60,  //       ##         ##
	0x07, 0x00, 0x70,  //      ###         ###
	0x06, 0x00, 0x30,  //      ##           ##
	0x06, 0x00, 0x30,  //      ##           ##
	0x0E, 0x00, 0x38,  //     ###           ###
	0x0C, 0x00, 0x18,  //     ##             ##
	0x0C, 0x00, 0x18,  //     ##             ##
	0x18, 0x00, 0x0C,  //    ##               ##
	0x18, 0x00, 0x0C,  //    ##               ##
	0x18, 0x00, 0x0C,  //    ##               ##
	0x30, 0x00, 0x06,  //   ##                 ##
	0x30, 0x00, 0x06,  //   ##                 ##
	0x30, 0x00, 0x06,  //   ##                 ##
	0x1F, 0xFF, 0xFC,  //   #####################
	0x0F, 0xFF, 0xF8,  //    ###################
};
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
const uint8_t Left_Right_Arrow_14ptBitmaps[] =
	{
			// @0 '3' (7 pixels wide)
	0x01, //       #
	0x03, //      ##
	0x07, //     ###
	0x0F, //    ####
	0x1F, //   #####
	0x3F, //  ######
	0x7F, // #######
	0xFF, //########
	0x7F, // #######
	0x3F, //  ######
	0x1F, //   #####
	0x0F, //    ####
	0x07, //     ###
	0x03, //      ##
	0x01, //       #

// @0 '4' (7 pixels wide)
	0x80, // #
	0xC0, // ##
	0xE0, // ###
	0xF0, // ####
	0xF8, // #####
	0xFC, // ######
	0xFE, // #######
	0XFF, // ########
	0xFE, // #######
	0xFC, // ######
	0xF8, // #####
	0xF0, // ####
	0xE0, // ###
	0xC0, // ##
	0x80, // #

	};
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
const uint8_t up_down_arrow_20ptBitmaps[] =
	{
	// @0 '5' (17 pixels wide)

	0x00, 0x80, 0x00, //         #
	0x01, 0xC0, 0x00, //        ###
	0x03, 0xE0, 0x00, //       #####
	0x07, 0xF0, 0x00, //      #######
	0x0F, 0xF8, 0x00, //     #########
	0x1F, 0xFC, 0x00, //    ###########
	0x3F, 0xFE, 0x00, //   #############
	0x7F, 0xFF, 0x00, //  ###############
	0xFF, 0xFF, 0x80, // #################

	// @27 '6' (17 pixels wide)

	0xFF, 0xFF, 0x80,  // #################
	0x7F, 0xFF, 0x00, //  ###############
	0x3F, 0xFE, 0x00,//   #############
	0x1F, 0xFC, 0x00,//    ###########
	0x0F, 0xF8, 0x00,//     #########
	0x07, 0xF0, 0x00,//      #######
	0x03, 0xE0, 0x00,//       #####
	0x01, 0xC0, 0x00,//        ###
	0x00, 0x80, 0x00, //         #

	};
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
const uint8_t Left_arrow_35ptBitmaps[]=
	{
         // @0 '3' (16 pixels wide)
			0x00, 0x01, //                #
			0x00, 0x03, //               ##
			0x00, 0x07, //              ###
			0x00, 0x0F, //             ####
			0x00, 0x1F, //            #####
			0x00, 0x3F, //           ######
			0x00, 0x7F, //          #######
			0x00, 0xFF, //         ########
			0x01, 0xFF, //        #########
			0x03, 0xFF, //       ##########
			0x07, 0xFF, //      ###########
			0x0F, 0xFF, //     ############
			0x1F, 0xFF, //    #############
			0x3F, 0xFF, //   ##############
			0x7F, 0xFF, //  ###############
			0xFF, 0xFF, // ################
			0xFF, 0xFF, // ################
			0x7F, 0xFF, //  ###############
			0x3F, 0xFF, //   ##############
			0x1F, 0xFF, //    #############
			0x0F, 0xFF, //     ############
			0x07, 0xFF, //      ###########
			0x03, 0xFF, //       ##########
			0x01, 0xFF, //        #########
			0x00, 0xFF, //         ########
			0x00, 0x7F, //          #######
			0x00, 0x3F, //           ######
			0x00, 0x1F, //            #####
			0x00, 0x0F, //             ####
			0x00, 0x07, //              ###
			0x00, 0x03, //               ##
			0x00, 0x01, //                #
	};
/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
const uint8_t segoeFluentIcons_25ptBitmaps[] =
{
	// @0 '' (31 pixels wide)
	0x01, 0xFF, 0xFF, 0x00, //        #################
	0x03, 0xFF, 0xFF, 0x80, //       ###################
	0x03, 0xFF, 0xFF, 0x80, //       ###################
	0x07, 0x00, 0x03, 0x80, //      ###              ###
	0x07, 0x00, 0x03, 0x80, //      ###              ###
	0x07, 0x00, 0x03, 0x00, //      ###              ##
	0x06, 0x00, 0x07, 0x00, //      ##              ###
	0x0E, 0x00, 0x07, 0x00, //     ###              ###
	0x0E, 0x00, 0x06, 0x00, //     ###              ##
	0x0E, 0x00, 0x0E, 0x00, //     ###             ###
	0x0C, 0x00, 0x0E, 0x00, //     ##              ###
	0x1C, 0x00, 0x0C, 0x00, //    ###              ##
	0x1C, 0x00, 0x1C, 0x00, //    ###             ###
	0x18, 0x00, 0x1F, 0xFC, //    ##              ###########
	0x38, 0x00, 0x1F, 0xFE, //   ###              ############
	0x38, 0x00, 0x1F, 0xFE, //   ###              ############
	0x38, 0x00, 0x00, 0x0E, //   ###                       ###
	0x30, 0x00, 0x00, 0x1E, //   ##                       ####
	0x70, 0x00, 0x00, 0x3C, //  ###                      ####
	0x70, 0x00, 0x00, 0x78, //  ###                     ####
	0x60, 0x00, 0x00, 0xF0, //  ##                     ####
	0x60, 0x00, 0x01, 0xE0, //  ##                    ####
	0xE0, 0x00, 0x03, 0xC0, // ###                   ####
	0xE0, 0x00, 0x07, 0x80, // ###                  ####
	0xFF, 0x80, 0x0F, 0x00, // #########           ####
	0x7F, 0x80, 0x1E, 0x00, //  ########          ####
	0x03, 0x80, 0x3C, 0x00, //       ###         ####
	0x03, 0x80, 0x78, 0x00, //       ###        ####
	0x03, 0x00, 0x70, 0x00, //       ##         ###
	0x07, 0x00, 0xE0, 0x00, //      ###        ###
	0x07, 0x01, 0xC0, 0x00, //      ###       ###
	0x07, 0x03, 0x80, 0x00, //      ###      ###
	0x06, 0x07, 0x00, 0x00, //      ##      ###
	0x0E, 0x0E, 0x00, 0x00, //     ###     ###
	0x0E, 0x1C, 0x00, 0x00, //     ###    ###
	0x0C, 0x38, 0x00, 0x00, //     ##    ###
	0x0C, 0x70, 0x00, 0x00, //     ##   ###
	0x1C, 0xE0, 0x00, 0x00, //    ###  ###
	0x1D, 0xC0, 0x00, 0x00, //    ### ###
	0x1F, 0x80, 0x00, 0x00, //    ######
	0x1F, 0x00, 0x00, 0x00, //    #####
	0x0E, 0x00, 0x00, 0x00, //     ###
};


/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

// Character bitmaps for Segoe UI Emoji 24pt
const uint8_t segoeUIEmoji_24ptBitmaps[] =
{
	// @0 '⚡' (23 pixels wide)
	0x00, 0x03, 0x00, //               ##
	0x00, 0x07, 0x00, //              ###
	0x00, 0x0F, 0x00, //             ####
	0x00, 0x0F, 0x00, //             ####
	0x00, 0x1F, 0x00, //            #####
	0x00, 0x3F, 0x00, //           ######
	0x00, 0x3F, 0x00, //           ######
	0x00, 0x7F, 0x00, //          #######
	0x00, 0xFF, 0x00, //         ########
	0x01, 0xFF, 0x00, //        #########
	0x01, 0xFF, 0x00, //        #########
	0x03, 0xFF, 0x00, //       ##########
	0x07, 0xFF, 0x00, //      ###########
	0x07, 0xFF, 0x00, //      ###########
	0x0F, 0xFF, 0x00, //     ############
	0x1F, 0xFF, 0x00, //    #############
	0x1F, 0xFF, 0x00, //    #############
	0x3F, 0xFF, 0x00, //   ##############
	0x7F, 0xFF, 0xFE, //  ######################
	0xFF, 0xFF, 0xFC, // ######################
	0xFF, 0xFF, 0xFC, // ######################
	0x01, 0xFF, 0xF8, //        ##############
	0x01, 0xFF, 0xF0, //        #############
	0x01, 0xFF, 0xE0, //        ############
	0x01, 0xFF, 0xE0, //        ############
	0x01, 0xFF, 0xC0, //        ###########
	0x01, 0xFF, 0x80, //        ##########
	0x01, 0xFF, 0x00, //        #########
	0x01, 0xFF, 0x00, //        #########
	0x01, 0xFE, 0x00, //        ########
	0x01, 0xFC, 0x00, //        #######
	0x01, 0xF8, 0x00, //        ######
	0x01, 0xF8, 0x00, //        ######
	0x01, 0xF0, 0x00, //        #####
	0x01, 0xE0, 0x00, //        ####
	0x01, 0xC0, 0x00, //        ###
	0x01, 0xC0, 0x00, //        ###
	0x00, 0x80, 0x00, //         #
};

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
//  Font data for Segoe Fluent Icons 12pt
//

// Character bitmaps for Segoe Fluent Icons 12pt
const uint8_t segoeFluentIcons_12ptBitmaps[] =
{
	// @0 '' (15 pixels wide)
	0x1F, 0xF0, //    #########
	0x10, 0x10, //    #       #
	0x10, 0x10, //    #       #
	0x30, 0x30, //   ##      ##
	0x30, 0x20, //   ##      #
	0x20, 0x20, //   #       #
	0x20, 0x7E, //   #      ######
	0x60, 0x3E, //  ##       #####
	0x40, 0x06, //  #           ##
	0x40, 0x0C, //  #          ##
	0x40, 0x18, //  #         ##
	0xF8, 0x30, // #####     ##
	0x38, 0x60, //   ###    ##
	0x10, 0xC0, //    #    ##
	0x11, 0x80, //    #   ##
	0x13, 0x00, //    #  ##
	0x36, 0x00, //   ## ##
	0x2C, 0x00, //   # ##
	0x38, 0x00, //   ###
	0x30, 0x00, //   ##
};

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/
//  Font data for Segoe Fluent Icons 9pt
//

// Character bitmaps for Segoe Fluent Icons 9pt
const uint8_t segoeFluentIcons_9ptBitmaps[] =
{
	// @0 '' (11 pixels wide)
	0x3F, 0x80, //   #######
	0x20, 0x80, //   #     #
	0x41, 0x00, //  #     #
	0x41, 0x00, //  #     #
	0x41, 0x00, //  #     #
	0x43, 0xE0, //  #    #####
	0x80, 0x60, // #        ##
	0x80, 0xC0, // #       ##
	0xE1, 0x80, // ###    ##
	0x23, 0x00, //   #   ##
	0x26, 0x00, //   #  ##
	0x4C, 0x00, //  #  ##
	0x58, 0x00, //  # ##
	0x70, 0x00, //  ###
	0x60, 0x00, //  ##
};


/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

// Character bitmaps for Webdings 9pt
const uint8_t webdings_9ptBitmaps[] =
{
	// @0 'x' (13 pixels wide)
	0x0F, 0x80, //     #####
	0x38, 0xE0, //   ###   ###
	0x70, 0x30, //  ###      ##
	0x78, 0x30, //  ####     ##
	0xCC, 0x18, // ##  ##     ##
	0xC6, 0x18, // ##   ##    ##
	0xC3, 0x18, // ##    ##   ##
	0xC1, 0x98, // ##     ##  ##
	0x60, 0xF0, //  ##     ####
	0x60, 0x70, //  ##      ###
	0x38, 0xE0, //   ###   ###
	0x0F, 0x80, //     #####
};

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

const uint8_t wingdings3_24ptBitmaps[] =
{
	// @0 'p' (28 pixels wide)
	0x00, 0x06, 0x00, 0x00, //              ##
	0x00, 0x06, 0x00, 0x00, //              ##
	0x00, 0x0F, 0x00, 0x00, //             ####
	0x00, 0x1F, 0x80, 0x00, //            ######
	0x00, 0x1F, 0x80, 0x00, //            ######
	0x00, 0x3F, 0xC0, 0x00, //           ########
	0x00, 0x3F, 0xC0, 0x00, //           ########
	0x00, 0x7F, 0xE0, 0x00, //          ##########
	0x00, 0x7F, 0xE0, 0x00, //          ##########
	0x00, 0xFF, 0xF0, 0x00, //         ############
	0x01, 0xFF, 0xF8, 0x00, //        ##############
	0x01, 0xFF, 0xF8, 0x00, //        ##############
	0x03, 0xFF, 0xFC, 0x00, //       ################
	0x03, 0xFF, 0xFC, 0x00, //       ################
	0x07, 0xFF, 0xFE, 0x00, //      ##################
	0x0F, 0xFF, 0xFF, 0x00, //     ####################
	0x0F, 0xFF, 0xFF, 0x00, //     ####################
	0x1F, 0xFF, 0xFF, 0x80, //    ######################
	0x1F, 0xFF, 0xFF, 0x80, //    ######################
	0x3F, 0xFF, 0xFF, 0xC0, //   ########################
	0x7F, 0xFF, 0xFF, 0xE0, //  ##########################
	0x7F, 0xFF, 0xFF, 0xE0, //  ##########################
	0xFF, 0xFF, 0xFF, 0xF0, // ############################
};
//{
//	// @0 'p' (33 pixels wide)
//	0x00, 0x01, 0xC0, 0x00, 0x00, //                ###
//	0x00, 0x01, 0xC0, 0x00, 0x00, //                ###
//	0x00, 0x03, 0xE0, 0x00, 0x00, //               #####
//	0x00, 0x07, 0xF0, 0x00, 0x00, //              #######
//	0x00, 0x07, 0xF0, 0x00, 0x00, //              #######
//	0x00, 0x0F, 0xF8, 0x00, 0x00, //             #########
//	0x00, 0x0F, 0xF8, 0x00, 0x00, //             #########
//	0x00, 0x1F, 0xFC, 0x00, 0x00, //            ###########
//	0x00, 0x3F, 0xFE, 0x00, 0x00, //           #############
//	0x00, 0x3F, 0xFE, 0x00, 0x00, //           #############
//	0x00, 0x7F, 0xFF, 0x00, 0x00, //          ###############
//	0x00, 0x7F, 0xFF, 0x00, 0x00, //          ###############
//	0x00, 0xFF, 0xFF, 0x80, 0x00, //         #################
//	0x01, 0xFF, 0xFF, 0xC0, 0x00, //        ###################
//	0x01, 0xFF, 0xFF, 0xC0, 0x00, //        ###################
//	0x03, 0xFF, 0xFF, 0xE0, 0x00, //       #####################
//	0x03, 0xFF, 0xFF, 0xE0, 0x00, //       #####################
//	0x07, 0xFF, 0xFF, 0xF0, 0x00, //      #######################
//	0x0F, 0xFF, 0xFF, 0xF8, 0x00, //     #########################
//	0x0F, 0xFF, 0xFF, 0xF8, 0x00, //     #########################
//	0x1F, 0xFF, 0xFF, 0xFC, 0x00, //    ###########################
//	0x1F, 0xFF, 0xFF, 0xFC, 0x00, //    ###########################
//	0x3F, 0xFF, 0xFF, 0xFE, 0x00, //   #############################
//	0x7F, 0xFF, 0xFF, 0xFF, 0x00, //  ###############################
//	0x7F, 0xFF, 0xFF, 0xFF, 0x00, //  ###############################
//	0xFF, 0xFF, 0xFF, 0xFF, 0x80, // #################################
//};

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

const uint8_t arial_7ptBitmaps[] =
{

		// @0 '!' (2 pixels wide)
				0x18, //  ##
				0xFC, // ####
				0xFC, // ####
				0xFC, // ####
				0xFC, // ####
				0x18, //  ##
				0x18, //  ##
				0x18, //  ##
				0x00, //
				0x00, //
				0x18, //  ##
				0x18, //  ##
};

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

const uint8_t webdings_22ptBitmaps[] =
{
	// @0 '3' (12 pixels wide)
	0x00, 0x30, //           ##
	0x00, 0x70, //          ###
	0x00, 0xF0, //         ####
	0x01, 0xF0, //        #####
	0x03, 0xF0, //       ######
	0x07, 0xF0, //      #######
	0x0F, 0xF0, //     ########
	0x1F, 0xF0, //    #########
	0x3F, 0xF0, //   ##########
	0x7F, 0xF0, //  ###########
	0xFF, 0xF0, // ############
	0xFF, 0xF0, // ############
	0x7F, 0xF0, //  ###########
	0x3F, 0xF0, //   ##########
	0x1F, 0xF0, //    #########
	0x0F, 0xF0, //     ########
	0x07, 0xF0, //      #######
	0x03, 0xF0, //       ######
	0x01, 0xF0, //        #####
	0x00, 0xF0, //         ####
	0x00, 0x70, //          ###
	0x00, 0x30, //           ##
};

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

const uint8_t wingdings3_R_ARROW_20ptBitmaps[] =
{
		// @0 'u' (13 pixels wide)
		0x80, 0x00, // #
		0xE0, 0x00, // ###
		0xF0, 0x00, // ####
		0xFC, 0x00, // ######
		0xFF, 0x00, // ########
		0xFF, 0x80, // #########
		0xFF, 0xE0, // ###########
		0xFF, 0xF8, // #############
		0xFF, 0xFC, // ##############
		0xFF, 0xF8, // #############
		0xFF, 0xE0, // ###########
		0xFF, 0x80, // #########
		0xFF, 0x00, // ########
		0xFC, 0x00, // ######
		0xF0, 0x00, // ####
		0xE0, 0x00, // ###
		0x80, 0x00, // #


//	// @0 '' (21 pixels wide)
//	0xC0, 0x00, 0x00, // ##
//	0x70, 0x00, 0x00, //  ###
//	0x78, 0x00, 0x00, //  ####
//	0x3E, 0x00, 0x00, //   #####
//	0x1F, 0x80, 0x00, //    ######
//	0x1F, 0xE0, 0x00, //    ########
//	0x0F, 0xF0, 0x00, //     ########
//	0x0F, 0xFC, 0x00, //     ##########
//	0x07, 0xFF, 0x00, //      ###########
//	0x03, 0xFF, 0xC0, //       ############
//	0x03, 0xFF, 0xE0, //       #############
//	0x01, 0xFF, 0xF8, //        ##############
//	0x03, 0xFF, 0xE0, //       #############
//	0x03, 0xFF, 0xC0, //       ############
//	0x07, 0xFF, 0x00, //      ###########
//	0x0F, 0xFC, 0x00, //     ##########
//	0x0F, 0xF0, 0x00, //     ########
//	0x1F, 0xE0, 0x00, //    ########
//	0x1F, 0x80, 0x00, //    ######
//	0x3E, 0x00, 0x00, //   #####
//	0x78, 0x00, 0x00, //  ####
//	0x70, 0x00, 0x00, //  ###
//	0xC0, 0x00, 0x00, // ##
};

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

const uint8_t wingdings3_L_ARROW_13ptBitmaps[] =
{
// @0 't' (13 pixels wide)
0x00, 0x04, //              #
0x00, 0x1C, //            ###
0x00, 0x3C, //           ####
0x00, 0xFC, //         ######
0x03, 0xFC, //       ########
0x07, 0xFC, //      #########
0x1F, 0xFC, //    ###########
0x7F, 0xFC, //  #############
0xFF, 0xFC, // ##############
0x7F, 0xFC, //  #############
0x1F, 0xFC, //    ###########
0x07, 0xFC, //      #########
0x03, 0xFC, //       ########
0x00, 0xFC, //         ######
0x00, 0x3C, //           ####
0x00, 0x1C, //            ###
0x00, 0x04, //              #
};

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

const uint8_t star_14ptBitmaps[] =			//29-03
{
	// @0 'ê' (17 pixels wide)
	0x00, 0x00,// 0x00,
	0x00, 0x80,// 0x00, //         #
	0x01, 0xC0,// 0x00, //        ###
	0x01, 0xC0,// 0x00, //        ###
	0x03, 0xE0,// 0x00, //       #####
	0x03, 0xE0,// 0x00, //       #####
	//0x3F, 0xFE, 0x00, //   #############
	0x7F, 0xFF,// 0x00, // #################
	0x3F, 0xFE,// 0x00, //   #############
	0x1F, 0xFC,// 0x00, //    ###########
	0x0F, 0xF8,// 0x00, //     #########
	0x0F, 0xF8,// 0x00, //     #########
	0x0F, 0xF8,// 0x00, //     #########
	0x1F, 0xFC,// 0x00, //    ###########
	0x1E, 0x3C,// 0x00, //    ####   ####
	0x18, 0x0C,// 0x00, //    ##       ##
};

/****************************************************************************
* Function Name :
* Arguments     :
* Return type   :
* Description   :

*****************************************************************************/

const uint8_t segoeFluentIcons_91ptBitmaps[] =
{
	// @0 '' (11 pixels wide)
		0x0F, //    #####
		0x1E, //   #####
		0x3C, //  #####
		0x78, // #####
		0xFF, //########
		0x0E, //    ###
		0x1C, //   ###
		0x18, //   ##
		0x30, //  ##
		0x20, //  #

};

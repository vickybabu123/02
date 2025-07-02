/*
 * Driver_PINT.h
 *
 *  Created on: 12-Mar-2024
 *      Author: Software6
 */

#ifndef DRIVER_PINT_H_
#define DRIVER_PINT_H_

void PINT_EXT_Init1(void);
void PINT_Config( uint8_t Intr_No, uint8_t INT_Type);
void PIN_INT0_IRQHandler(void);


#endif /* DRIVER_PINT_H_ */

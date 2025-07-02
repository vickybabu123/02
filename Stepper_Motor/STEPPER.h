/*
 * STEPPER.h
 *
 *  Created on: 12-Mar-2024
 *      Author: Software6
 */

#ifndef STEPPER_H_
#define STEPPER_H_

void stepper_Forward(void);
void stepper_Reverse(void);
void DRV8428_ENABLE(void);
void DRV8428_DISABLE(void);
void DRV8428_Init(void);

#endif /* STEPPER_H_ */

/*
 * InterruptControl.h
 *
 *  Created on: Sep 26, 2024
 *      Author: jeffreya181
 */

#ifndef INTERRUPTCONTROL_H_
#define INTERRUPTCONTROL_H_

#include "STM32F429i.h"

#define EXTI0_IRQ_NUMBER 6
#define EXTI1_IRQ_NUMBER 7
#define EXTI2_IRQ_NUMBER 8
#define EXTI3_IRQ_NUMBER 9
#define EXTI4_IRQ_NUMBER 10

void Interrupt_Enable(uint8_t val);
void Interrupt_Disable(uint8_t val);
void Interrupt_Clear_Pending(uint8_t val);
void Interrupt_Set_Pending(uint8_t val);

void Interrupt_Clear_Pending_EXTI(uint8_t pin);

#endif /* INTERRUPTCONTROL_H_ */

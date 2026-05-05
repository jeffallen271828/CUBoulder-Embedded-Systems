/*
 * InterruptControl.c
 *
 *  Created on: Sep 26, 2024
 *      Author: jeffreya181
 */
#include "InterruptControl.h"
// shift 6
void Interrupt_Enable(uint8_t val) {
	uint8_t IRQ_range = val / 32;
	if(~IRQ_range){
		*NVIC_ISER0_SET_ENABLE |= (0x1 << val);
	} else {
		*NVIC_ISER0_SET_ENABLE |= (0x1 << (val%32));
	}
}

void Interrupt_Disable(uint8_t val) {
	uint8_t IRQ_range = val / 32;
	if(~IRQ_range){
		*NVIC_ISER0_CLEAR_ENABLE |= (0x1 << val);
	} else {
		*NVIC_ISER0_CLEAR_ENABLE |= (0x1 << (val%32));
	}
}

void Interrupt_Set_Pending(uint8_t val) {
	uint8_t IRQ_range = val / 32;
	if(~IRQ_range){
		*NVIC_ISER0_SET_PENDING |= (0x1 << val);
	} else {
		*NVIC_ISER0_SET_PENDING |= (0x1 << (val%32));
	}
}

void Interrupt_Clear_Pending(uint8_t val) {
	uint8_t IRQ_range = val / 32;
	if(~IRQ_range){
		*NVIC_ISER0_CLEAR_PENDING |= (0x1 << val);
	} else {
		*NVIC_ISER0_CLEAR_PENDING |= (0x1 << (val%32));
	}
}

void Interrupt_Clear_Pending_EXTI(uint8_t pin){
	uint8_t IRQ_range = pin / 32;
	if(~IRQ_range){
		EXTI_CUSTOM->PR |= (0x1 << pin);
	} else {
		EXTI_CUSTOM->PR |= (0x1 << (pin%32));
	}
}




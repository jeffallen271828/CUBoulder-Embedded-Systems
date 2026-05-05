/*
 * InterruptControl.h
 *
 *  Created on: Sep 26, 2024
 *      Author: jeffreya181
 */

#ifndef INTERRUPTCONTROL_H_
#define INTERRUPTCONTROL_H_

#include <stdint.h>

#define AHB1_BASE_ADDR 0x40020000
#define APB2_BASE_ADDR 0x40013800

#define SYSCFG_BASE_ADDR (APB2_BASE_ADDR + 0x0)
#define EXTI_BASE_ADDR (APB2_BASE_ADDR + 0x400)

#define EXTI0_IRQ_NUMBER 6
#define EXTI1_IRQ_NUMBER 7
#define EXTI2_IRQ_NUMBER 8
#define EXTI3_IRQ_NUMBER 9
#define EXTI4_IRQ_NUMBER 10

//		NVIC
#define NVIC_BASE_ADDR 0xE000E100
#define NVIC_SET_ENABLE_ADDR (0xE000E100 + 0x0)
#define NVIC_CLEAR_ENABLE_ADDR (0xE000E100 + 0x80)
#define NVIC_SET_PENDING_ADDR (0xE000E100 + 0x100)
#define NVIC_CLEAR_PENDING_ADDR (0xE000E100 + 0x180)

typedef struct {

	volatile uint32_t MEMRMP;		// 0x00
	volatile uint32_t PMC;			// 0x04
	volatile uint32_t EXTICR[4];	// 0x08 - 0x14
	volatile uint32_t reserved[2]; 	// 0x18-0x1c
	volatile uint32_t CMPCR;		// 0x20

} SYSCFG_RegDef_t;

typedef struct {

	volatile uint32_t IMR;		// 0x00
	volatile uint32_t EMR;		// 0x04
	volatile uint32_t RTSR;		// 0x08
	volatile uint32_t FTSR;		// 0x0C
	volatile uint32_t SWIER;	// 0x10
	volatile uint32_t PR;		// 0x14

} EXTI_RegDef_t;

//#define SYSCFG ((SYSCFG_RegDef_t *) SYSCFG_BASE_ADDR)
#define EXTI_CUSTOM ((EXTI_RegDef_t *) EXTI_BASE_ADDR)

#define NVIC_ISER0_SET_ENABLE ((volatile uint32_t*) NVIC_SET_ENABLE_ADDR)
#define NVIC_ISER0_CLEAR_ENABLE ((volatile uint32_t*) NVIC_CLEAR_ENABLE_ADDR)
#define NVIC_ISER0_SET_PENDING ((volatile uint32_t*) NVIC_SET_PENDING_ADDR)
#define NVIC_ISER0_CLEAR_PENDING ((volatile uint32_t*) NVIC_CLEAR_PENDING_ADDR)

void Interrupt_Enable(uint8_t val);
void Interrupt_Disable(uint8_t val);
void Interrupt_Clear_Pending(uint8_t val);
void Interrupt_Set_Pending(uint8_t val);

void Interrupt_Clear_Pending_EXTI(uint8_t pin);

#define SYSCFG_CLK_SHIFT 0xE
//enable/disable clk
#define GPIO_CLK_ENABLE(addr_shift) (RCC->AHB1ENR |= (0x1 << addr_shift))
#define GPIO_CLK_DISABLE(addr_shift) (RCC->AHB1ENR &= ~(0x1 << addr_shift))
#define SYSCFG_CLK_ENABLE() (RCC->APB2ENR |= (0x1 << SYSCFG_CLK_SHIFT))
#define SYSCFG_CLK_DISABLE() (RCC->APB2ENR &= ~(0x1 << SYSCFG_CLK_SHIFT))

#endif /* INTERRUPTCONTROL_H_ */

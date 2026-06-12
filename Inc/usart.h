/*
 * usart.h
 *
 *  Created on: 8 juin 2026
 *      Author: asus
 */

#ifndef USART_H_
#define USART_H_
#include <stdint.h>
#include "base.h"

#define RCC_USART2_OFFSET	(0x40UL)
#define RCC_USART2			(*(volatile uint32_t *)(RCC_BASE+ RCC_USART2_OFFSET))

#define USART2_CR1_OFFSET		(0x0cUL)
#define USART2_STATUS_OFFSET	(0x00UL)
#define USART2_BAUD_OFFSET		(0x08UL)
#define USART2_DR_OFFSET		(0x04UL)

#define USART2_CR1				(*(volatile uint32_t *)(USART2_BASE + USART2_CR1_OFFSET))
#define USART2_STATUS			(*(volatile uint32_t *)(USART2_BASE + USART2_STATUS_OFFSET))
#define USART2_BAUD				(*(volatile uint32_t *)(USART2_BASE + USART2_BAUD_OFFSET))
#define USART2_DR				(*(volatile uint32_t *)(USART2_BASE + USART2_DR_OFFSET))

#define SR_RXNE					(1U<<5)
#define SR_TXE					(1U<<7)
#define CR1_UE					(1U<<13)
#define CR1_TE					(1U<<3)
#define CR1_RE					(1U<<2)

//functions
void usart2_init(void);
void usart2_write(char ch);
void usart2_IRQHandler(void);
char usart2_read(void);
int usart2_data_exist(void);
void usart2_baudrate(uint32_t clock, uint32_t baud_rate);
#endif /* USART_H_ */

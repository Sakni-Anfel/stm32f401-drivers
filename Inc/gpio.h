/*
 * gpio.h
 *
 *  Created on: 8 juin 2026
 *      Author: asus
 */

#ifndef GPIO_H_
#define GPIO_H_


#include <stdint.h>
#include "base.h"
#define GPIO_MODER_OFFSET		(0x00UL)
#define GPIO_ODR_OFFSET			(0x14UL)
#define GPIO_IDR_OFFSET			(0x10UL)
#define GPIO_PUPDR_OFFSET		(0x0cUL)
#define GPIO_OSPEEDR_OFFSET		(0x08UL)
#define GPIO_OTYPER_OFFSET		(0x04UL)
#define GPIO_AFRL_OFFSET		(0x20UL)
//GPIOA
#define GPIOA_MODER		(*(volatile uint32_t *) (GPIOA_BASE + GPIO_MODER_OFFSET))
#define GPIOA_ODR		(*(volatile uint32_t *) (GPIOA_BASE + GPIO_ODR_OFFSET ))
#define GPIOA_IDR		(*(volatile uint32_t *)(GPIOA_BASE + GPIO_IDR_OFFSET))
#define GPIOA_PUPDR		(*(volatile uint32_t *)(GPIOA_BASE + GPIO_PUPDR_OFFSET ))
#define GPIOA_OSPEEDR	(*(volatile uint32_t *) (GPIOA_BASE + GPIO_OSPEEDR_OFFSET))
#define GPIOA_OTYPER	(*(volatile uint32_t *)(GPIOA_BASE + GPIO_OTYPER_OFFSET))
#define GPIOA_AFRL		(*(volatile uint32_t*)(GPIOA_BASE + GPIO_AFRL_OFFSET))
//GPIOB
#define GPIOB_MODER		(*(volatile uint32_t *) (GPIOB_BASE + GPIO_MODER_OFFSET))
#define GPIOB_ODR		(*(volatile uint32_t *) (GPIOB_BASE + GPIO_ODR_OFFSET ))
#define GPIOB_IDR		(*(volatile uint32_t *)(GPIOB_BASE + GPIO_IDR_OFFSET))
#define GPIOB_PUPDR		(*(volatile uint32_t *)(GPIOB_BASE + GPIO_PUPDR_OFFSET ))
#define GPIOB_OSPEEDR	(*(volatile uint32_t *)(GPIOB_BASE + GPIO_OSPEEDR_OFFSET))
#define GPIOB_OTYPER	(*(volatile uint32_t *)(GPIOB_BASE + GPIO_OTYPER_OFFSET))
//GPIOC
#define GPIOC_MODER		(*(volatile uint32_t *) (GPIOC_BASE + GPIO_MODER_OFFSET))
#define GPIOC_ODR		(*(volatile uint32_t *) (GPIOC_BASE + GPIO_ODR_OFFSET ))
#define GPIOC_IDR		(*(volatile uint32_t *) (GPIOC_BASE + GPIO_IDR_OFFSET))
#define GPIOC_PUPDR		(*(volatile uint32_t *)(GPIOC_BASE + GPIO_PUPDR_OFFSET ))
#define GPIOC_OSPEEDR	(*(volatile uint32_t *)(GPIOC_BASE + GPIO_OSPEEDR_OFFSET))
#define GPIOC_OTYPER	(*(volatile uint32_t *)(GPIOC_BASE + GPIO_OTYPER_OFFSET))
//RCC_GPIO
#define RCC_GPIO_OFFSET 	(0x30UL)
#define RCC_GPIO_ENB		(*(volatile uint32_t *)(RCC_BASE + RCC_GPIO_OFFSET))



void gpio_init(void );
void red_led_on(void);
void red_led_off(void);
void green_led_on(void);
void green_led_off(void);
void leds_toggle(void);
void button_state_set(int * prgm_state);
void button_state_dsply(int * prgrm_state);
void delay(int ms);

#endif /* GPIO_H_ */

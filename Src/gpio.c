#include "gpio.h"



#define GPIOA	(1U<<0)
#define GPIOB	(1U<<1)
#define GPIOC	(1U<<2)

#define GPIOA_PA8_LED_RED	(1U<<8)//for the odr
#define GPIOA_PA5_LED		(1U<<5)
#define GPIOB_PB5_LED_GREEN (1U<<5)//for the odr

#define GPIOC_PC13_BUTTON	(1U<<13)//for idr
void gpio_init(void ){

	RCC_GPIO_ENB |=GPIOA;
	RCC_GPIO_ENB |=GPIOB;
	RCC_GPIO_ENB |=GPIOC;
	//GPIOA_MODER |= 0x10000UL;OUTPUT PIN PA8
	GPIOA_MODER |= (1U<<16);
	GPIOA_MODER &= ~(1U<<17);//remember use :to make it 0 cause 1&0 =0 0&0=1 1&1=1
	//GPIOB_MODER |=0x400UL;output pin PB5
	GPIOB_MODER |=(1U<<10);
	GPIOB_MODER &= ~(1U<<11);
	//GPIOC INTPUT PIN P13
	GPIOC_MODER &= ~(1U<<26);
	GPIOC_MODER &= ~(1U<<27);
//PA5
	GPIOA_MODER |=(1U<<10);
	GPIOA_MODER &=~(1U<<11);
	//pa2 tx AF7 for usart
	GPIOA_AFRL |=(1U<<8);
	GPIOA_AFRL |=(1U<<9);
	GPIOA_AFRL |=(1U<<10);
	GPIOA_AFRL &= ~(1U<<11);
	//pa3 rx af7 for usart
	GPIOA_AFRL |=(1U<<12);
	GPIOA_AFRL |=(1U<<13);
	GPIOA_AFRL |=(1U<<14);
	GPIOA_AFRL &= ~(1U<<15);
}


void red_led_on(void){
	GPIOA_ODR |=GPIOA_PA8_LED_RED;

}


void red_led_off(void){
	GPIOA_ODR &= ~(GPIOA_PA8_LED_RED);
}


void green_led_on(void){

GPIOB_ODR |=GPIOB_PB5_LED_GREEN;

}


void green_led_off(void){

GPIOB_ODR &= ~(GPIOB_PB5_LED_GREEN);

}


void leds_toggle(void){

GPIOA_ODR ^=(GPIOA_PA5_LED);
for (int i=0 ; i<1500000;i++);//we added an empty for loop for the delay ,WHY? cause without it the toggle will be so fast we could not be able to see it

}


void button_state_set(int *prgm_state){

if (!(GPIOC_IDR & GPIOC_PC13_BUTTON)){

	if(*prgm_state== OFF){
		*prgm_state== ON;
		for(int i=0; i<1500000;i++);
	}
	else if(*prgm_state== ON){
		*prgm_state == OFF;
		for(int i=0; i<1500000;i++);
	}
}

}


void button_state_dsply(int * prgm_state){
if(*prgm_state== OFF){
	red_led_on();
	green_led_off();
}else if(*prgm_state== ON){
	red_led_off();
	green_led_on();
}


}

void delay(int ms){
	for(int i=0; i<(ms*1500);i++);
}

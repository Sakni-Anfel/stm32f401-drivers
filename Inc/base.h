/*
 * base.h
 *
 *  Created on: 8 juin 2026
 *      Author: asus
 */

#ifndef BASE_H_
#define BASE_H_

#define PERIPHERAL_BASE (0x40000000UL)

#define APB1_OFFSET	(0x0000UL)
#define APB1_PERIPHERAL (PERIPHERAL_BASE + APB1_OFFSET)

#define APB2_OFFSET (0x00010000UL)
#define APB2_PERIPHERAL (PERIPHERAL_BASE + APB2_OFFSET)

#define AHB1_OFFSET (0x00020000UL)
#define AHB1_PERIPHERAL (PERIPHERAL_BASE + AHB1_OFFSET)

#define GPIOA_OFFSET	(0x0000UL)
#define GPIOA_BASE	(AHB1_PERIPHERAL + GPIOA_OFFSET)

#define GPIOB_OFFSET	(0x00000400UL)
#define GPIOB_BASE	(AHB1_PERIPHERAL + GPIOB_OFFSET)

#define GPIOC_OFFSET	(0x00000800UL)
#define GPIOC_BASE	(AHB1_PERIPHERAL + GPIOC_OFFSET)

#define GPIOD_OFFSET	(0x00000C00UL)
#define GPIOD_BASE	(AHB1_PERIPHERAL + GPIOD_OFFSET)

#define ADC_OFFSET	(0x00002000UL)
#define ADC_BASE	(APB2_PERIPHERAL + ADC_OFFSET)

#define USART2_OFFSET	(0x00004400UL)
#define USART2_BASE	(APB1_PERIPHERAL + USART2_OFFSET)

#define RCC_OFFSET	(0x00003800UL)
#define RCC_BASE (AHB1_PERIPHERAL + RCC_OFFSET)

#define BUFFER_SIZE 256
enum State {
	OFF=48,//why 48 and not 1 and 0 cause we are going to send the state in USRAT terminal 48 is 0 in ASCII
	ON=49
};
//rq: we did not use volatile here cause those are base adress we only use volatile with the register that we are going to access
#endif /* BASE_H_ */

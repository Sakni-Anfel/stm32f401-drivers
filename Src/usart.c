
#include <stdint.h>
#include "usart.h"


#define SR_RXNE					(1U<<5)
#define SR_TXE					(1U<<7)
#define CR1_UE					(1U<<13)
#define CR1_TE					(1U<<3)
#define CR1_RE					(1U<<2)
#define CR1_TXEIE				(1U<<7)

#define CLOCK 		16000000//SYSTEM FREQUNCY
#define BAUD_RATE 	9600
static char rx_buffer[BUFFER_SIZE];
static int rx_writeISR_buffer=0;
static int rx_read_buffer=0;

static char tx_buffer[BUFFER_SIZE];
static int tx_write_buffer=0;
static int tx_readISR_buffer=0;

static int tx_buffer_counter=0;
static int rx_buffer_counter=0;

void usart2_init(void){
	RCC_USART2 |= (1U<<17);//enable rcc

	//config pa2 et pa3 altrenate function(which mean that the pin will do somthing speacial instead of in and out )
	//enbale pin tx nd rx ,  AF07 PA2 TX,PA3 RX
	 usart2_baudrate(CLOCK, BAUD_RATE);

	USART2_CR1 |=CR1_TE;
	USART2_CR1 |=CR1_RE;
	USART2_CR1 |=CR1_UE;

	rx_writeISR_buffer=0;
	rx_read_buffer=0;
	tx_write_buffer=0;
	tx_readISR_buffer=0;


}
void usart2_write(char ch){
	while (tx_buffer_counter >= BUFFER_SIZE);// WE HAVE TO WAIT IF IT FULL
	tx_buffer[tx_write_buffer]=ch;//na9raw mil buffer w nhotou fi ch
	tx_write_buffer=(tx_write_buffer + 1)% BUFFER_SIZE;
	tx_buffer_counter ++;
	USART2_CR1 |=CR1_TXEIE;

	/*
while(!(USART2_STATUS & SR_TXE));// to check if the transmiting data register is not empty, it is used to check the usart hardware if its empty in real time, we need to add a buffer checker
USART2_DR=(ch & 0xFF);// to say we are only able to send 8 bits at a time so if its a big data will be splited , base on reference, read directly from the usart
*/
}
int usart2_data_exist(void){
	return rx_buffer_counter > 0;//return the buffer count cause it is the number of byte we are going to read

}
char usart2_read(void){//bch nektbou
	while(rx_buffer_counter==0);
	char ch =rx_buffer[rx_read_buffer];
	rx_read_buffer=(rx_read_buffer +1 )% BUFFER_SIZE;
	rx_buffer_counter --;

	return ch;

/*
while (!(USART2_STATUS & SR_RXNE));//to make sure that the rx register not empty
return USART2_DR;*/
}
void usart2_baudrate(uint32_t clock, uint32_t baud_rate){
	USART2_BAUD= ((clock+ ( baud_rate/2U)) / baud_rate);
}
void usart2_IRQHandler(void){
if (USART2_STATUS & SR_RXNE){
	char data = USART2_DR;
	if(rx_buffer_counter < BUFFER_SIZE){
		rx_buffer[rx_writeISR_buffer]=data;
		rx_writeISR_buffer=(rx_writeISR_buffer+1)% BUFFER_SIZE;
		rx_buffer_counter++;
	}

}

if ((USART2_STATUS & SR_TXE) && (USART2_CR1 & CR1_TXEIE)){
	if (tx_buffer_counter > 0)/// ya3ni fama data bch usart yab3thha
		{
		USART2_DR=tx_buffer[tx_readISR_buffer];
		tx_readISR_buffer=(tx_readISR_buffer+1)%BUFFER_SIZE;
		tx_buffer_counter--;

	}else{
		USART2_CR1 &=~(CR1_TXEIE);
	}

}}


#include <stdint.h>
#include "gpio.h"
#include "usart.h"
#include "base.h"

#define SIZE 3

int prgm_state = OFF;
char rx_line[SIZE];

int main(void)
{
    gpio_init();
    usart2_init();

    usart2_write_string("Press the button to toggle ON/OFF state on the LEDs.\r\n");
    usart2_write_string("Type a line and press Enter to echo it back.\r\n");


    while (1) {
    	leds_toggle();
    	delay(500);
        button_state_set(&prgm_state);
        button_state_dsply(&prgm_state);


        if (usart2_data_exist()) {
            usart2_read_string(rx_line, SIZE);
            usart2_write_string("You typed: ");
            usart2_write_string(rx_line);
            usart2_write_string("\r\n");
        }
    }
}

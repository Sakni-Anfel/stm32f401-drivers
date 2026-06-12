
# stm32f401-drivers

Register-level drivers for STM32F401RE. No HAL, no LL.

---

## What's working

| Driver | Status | Notes |
|--------|--------|-------|
| GPIO   | Done   | PA8 (red), PB5 (green), PC13 (button), PA2/PA3 (USART AF7) |
| USART2 | Done   | 9600 baud, circular buffers, IRQ-driven TX/RX |
| ADC    | WIP    | Headers only, implementation pending |

---

## Memory map

Peripherals accessed via volatile pointers in `base.h`:

```
0x4000 0000  Peripheral base
  + 0x0002 0000  AHB1
    + 0x0000   GPIOA
    + 0x0400   GPIOB
    + 0x0800   GPIOC
    + 0x3800   RCC
  + 0x0000 0000  APB1
    + 0x4400   USART2
```

---

## GPIO

Register definitions for MODER, ODR, IDR, PUPDR, OSPEEDR, OTYPER, AFRL. Each port mapped as volatile dereference:

```c
#define GPIOA_MODER  (*(volatile uint32_t *)(GPIOA_BASE + 0x00UL))
```

LEDs and button abstracted in `gpio.c`:

```c
void red_led_on(void);      // PA8
void red_led_off(void);
void green_led_on(void);    // PB5
void green_led_off(void);
void leds_toggle(void);     // PA5
void button_state_set(int *prgm_state);   // PC13, active low
void button_state_dsply(int *prgm_state); // update LEDs based on state
```

Button state uses ASCII encoding (`OFF=48`, `ON=49`) for direct USART transmission without conversion.

---

## USART2

Full-duplex async, 9600 baud @ 16 MHz system clock. IRQ-driven circular buffers — no blocking polls.

**Buffers:**
- `rx_buffer[256]` — ISR writes, main loop reads
- `tx_buffer[256]` — main loop writes, ISR reads

```c
void usart2_init(void);
void usart2_write(char ch);     // non-blocking, returns immediately
char usart2_read(void);         // blocks until data available
int usart2_data_exist(void);    // check before read
void usart2_baudrate(uint32_t clock, uint32_t baud_rate);
```

**ISR logic:**
- `RXNE` → read `USART2_DR`, push to `rx_buffer` if not full
- `TXE` + `TXEIE` enabled → pop from `tx_buffer`, write to `USART2_DR`
- Buffer empty → clear `TXEIE` to stop TX interrupts

---

## Pinout

| Signal | Pin | Mode |
|--------|-----|------|
| USART_TX | PA2 | AF7 |
| USART_RX | PA3 | AF7 |
| LED_RED  | PA8 | Output |
| LED_GREEN| PB5 | Output |
| LED_TOGGLE| PA5 | Output |
| BUTTON   | PC13 | Input |

---

## Build

Open in STM32CubeIDE, build, flash with ST-Link.

---

## TODO

- [ ] Finish ADC driver (headers ready, need conversion logic)
- [ ] Replace `for()` delay with SysTick timer
- [ ] Add DMA for USART bulk transfer
- [ ] Add GPIO interrupt support for button (currently polled)
```

Copy this into `README.md` in your project root.

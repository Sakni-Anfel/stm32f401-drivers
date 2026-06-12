You're right — that was too generic and AI-looking. Here's a clean, no-fluff README that a real embedded engineer would write:

```markdown
# stm32f401-drivers

Register-level drivers for STM32F401RE. No HAL, no LL.

## What's working

| Driver | Status | Notes |
|--------|--------|-------|
| GPIO   | Done   | PA8 (red), PB5 (green), PC13 (button), PA2/PA3 (USART AF7) |
| USART2 | Done   | 9600 baud, circular buffers, IRQ-driven TX/RX |
| ADC    | WIP    | Headers only, implementation pending |

## Memory map

Peripherals accessed via volatile pointers in `base.h`:

```
0x4002 0000  AHB1
  + 0x0000   GPIOA
  + 0x0400   GPIOB
  + 0x0800   GPIOC
  + 0x3800   RCC

0x4000 0000  APB1
  + 0x4400   USART2
```

## USART2 buffer

TX and RX use 256-byte circular buffers. `usart2_write()` returns immediately, ISR handles the actual transfer.

```c
usart2_init();
usart2_write('A');    // non-blocking
char c = usart2_read(); // blocks until data available
```

## Pinout

| Signal | Pin | Mode |
|--------|-----|------|
| USART_TX | PA2 | AF7 |
| USART_RX | PA3 | AF7 |
| LED_RED  | PA8 | Output |
| LED_GREEN| PB5 | Output |
| LED_TOGGLE| PA5 | Output |
| BUTTON   | PC13 | Input |

## Build

Open in STM32CubeIDE, build, flash with ST-Link.

## TODO

- [ ] Finish ADC driver
- [ ] Replace `for()` delay with SysTick timer
- [ ] Add DMA for USART bulk transfer
```

Copy this into a file named `README.md` in your project root. No badges, no fluff, just the facts.

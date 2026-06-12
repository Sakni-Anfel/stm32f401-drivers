```markdown
# STM32F401RE Drivers

Bare-metal peripheral drivers for the **STM32F401RE** ARM Cortex-M4 microcontroller. Built from scratch using register-level programming — no HAL, no LL, no CMSIS abstraction layers.

## Project Overview

| MCU | STM32F401RETx |
|-----|---------------|
| Core | ARM Cortex-M4 @ 84 MHz |
| Framework | Bare-metal (register direct) |
| Toolchain | STM32CubeIDE / GCC ARM |
| Debug | ST-Link V2 |

## Implemented Drivers

### ✅ GPIO
- Register-mapped access to **GPIOA**, **GPIOB**, **GPIOC**
- Mode configuration (Input, Output, Alternate Function)
- Push-pull / Open-drain, Speed, Pull-up/Pull-down
- Alternate function mapping (AF7 for USART2 on PA2/PA3)
- LED control abstraction (Red: PA8, Green: PB5, PA5 toggle)
- Button state handling (PC13)

### ✅ USART2
- Full-duplex asynchronous communication
- Configurable baud rate (default: 9600 @ 16 MHz)
- **Interrupt-driven circular buffer** for RX/TX
- Non-blocking `usart2_write()` / `usart2_read()`
- IRQ handler for TXE (transmit empty) and RXNE (receive not empty)

### 🚧 ADC (Work in Progress)
- Register definitions prepared in `adc.h`
- Implementation pending

## Project Structure

```
project_led_button/
├── Inc/
│   ├── base.h          # Memory-mapped peripheral base addresses
│   ├── gpio.h          # GPIO register definitions & API
│   ├── usart.h         # USART2 register definitions & API
│   └── adc.h           # ADC register definitions (WIP)
├── Src/
│   ├── main.c          # Application entry point
│   ├── gpio.c          # GPIO driver implementation
│   ├── usart.c         # USART2 driver implementation
│   └── adc.c           # ADC driver (WIP)
├── Startup/
│   └── startup_stm32f401retx.s   # Startup assembly
└── README.md
```

## Key Design Decisions

### Register Access Pattern
All peripherals are accessed via volatile pointer dereferencing to prevent compiler optimization:

```c
#define GPIOA_MODER  (*(volatile uint32_t *)(GPIOA_BASE + GPIO_MODER_OFFSET))
```

### Circular Buffer for USART
TX and RX each use a 256-byte circular buffer with interrupt-driven servicing:
- **Producer** (main loop) writes to buffer, increments counter
- **Consumer** (ISR) reads from buffer, decrements counter
- No polling loops blocking the CPU

### State Machine for Button
Uses ASCII-encoded states (`OFF=48`, `ON=49`) for direct USART transmission without conversion overhead.

## Hardware Connections

| Function | Pin | Description |
|----------|-----|-------------|
| USART2_TX | PA2 | AF7, output |
| USART2_RX | PA3 | AF7, input |
| LED Red | PA8 | Active high |
| LED Green | PB5 | Active high |
| LED Toggle | PA5 | Active high |
| User Button | PC13 | Active low (pull-up) |

## Building & Flashing

1. Open project in **STM32CubeIDE**
2. Build: `Ctrl+B`
3. Flash & Debug: `F11` (ST-Link required)

## Roadmap

- [x] GPIO driver with interrupt-ready structure
- [x] USART2 with DMA-ready circular buffers
- [ ] ADC driver with single/multichannel conversion
- [ ] Timer-based delay (replace `for()` loop blocking)
- [ ] DMA integration for USART bulk transfers
- [ ] Interrupt-driven button debouncing

## License

MIT — use, modify, distribute freely. Attribution appreciated.

---

**Author:** Sakni-Anfel  
**Created:** June 2026
```

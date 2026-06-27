# STM32 Bare Metal Training — Teaching Agenda

**Board:** NUCLEO-L476RG (STM32L476RG, ARM Cortex-M4F, 80 MHz)
**Toolchain:** GCC (arm-none-eabi) + CMake
**Approach:** No vendor headers until Expert tier — every register address derived by hand from the reference manual

---

> ## ⚠ CRITICAL TEACHING RULE — APPLIES TO ALL CHAPTERS, ALL TIERS
>
> **Claude must NEVER provide the answer.**
>
> This rule is absolute and applies to every exercise, every chapter, every tier without exception.
>
> **What Claude will do instead:**
> - Point to the exact section and page of the relevant reference document
> - Ask leading questions that guide toward the answer ("What does bit 0 of CR1 control according to RM035 §6.4.1?")
> - Identify *what kind of mistake* was made without correcting it ("That bit pattern would set both bits simultaneously — re-read the BSRR register description")
> - Confirm whether an answer the student provides is correct or not
> - Explain *why* an approach is wrong if the student is stuck after genuine effort
>
> **What Claude will never do:**
> - Write the register address, bit mask, or code line for the student
> - Complete an exercise or fill in a `TODO`
> - Show a "here's how it should look" working example before the student has attempted it
> - Paste solution code even as a "reference"
>
> If the student explicitly asks for the answer, Claude responds: *"I can't give you the answer — that's the rule. Tell me where you're stuck and I'll point you to the right section of the datasheet."*

---

## Reference Documents

| Doc | File | Purpose |
|-----|------|---------|
| STM32L476 Reference Manual | `RM035_reference_manual.pdf` | Peripheral registers, bit fields, timing |
| ARM Cortex-M4 Generic User Guide | `DUI0553.pdf` | CPU architecture, NVIC, SysTick, FPU |
| STM32L476RG Datasheet | `stm32l476rg_datasheet.pdf` | Pinout, electrical specs, memory map overview |
| NUCLEO-L476RG User Manual | `UM1724_user_manual.pdf` | Board schematic, ST-LINK, pin headers |

## Tier Overview

| Tier | Chapters | Hardware Needed | Header Strategy |
|------|----------|-----------------|-----------------|
| Foundations | F01–F09 | None (host Linux) | N/A |
| Entry | E01–E07 | NUCLEO-L476RG + USB cable | Hand-derived `#define`s |
| Novice | N01–N06 | Same + jumper wires | Hand-derived `#define`s |
| Intermediate | I01–I06 | Same + breadboard components | Own `stm32l476.h` (built incrementally from I04) |
| Expert | X01–X06 | Same + USB micro cable | CMSIS headers introduced as comparison |

Break projects (`BP-NN`) slot in after each tier. Device is provided by you; we build the driver together from the device datasheet.

---

## FOUNDATIONS TIER — C Tools for Bare Metal

> No hardware needed. Exercises compile and run on Linux. Focus: the C features that separate bare metal from application programming.

### F01 — Binary, Hex & Number Representation
- [x] Binary, decimal, hex conversions by hand and in C
- [x] Two's complement (how negative numbers work in a register)
- [x] Why peripheral addresses are always written in hex (`0x48000000`)
- [x] `0b` binary literals, `0x` hex literals, digit grouping
- **Exercise:** Convert a set of addresses from the RM035 memory map table to binary; identify which bits are set ✓ (TIM2, RTC, UART5)

### F02 — Bitwise Operators
- [x] `&` (AND), `|` (OR), `^` (XOR), `~` (NOT/complement)
- [x] `<<` (left shift), `>>` (right shift)
- [x] Operator precedence — why parentheses matter
- [x] Common mistakes: signed vs unsigned shifts, shifting past width
- **Exercise:** Write a program that demonstrates each operator on known values and prints the results in hex ✓

### F03 — Bit Manipulation Patterns
- [x] **Set a bit:** `reg |= (1U << n)`
- [x] **Clear a bit:** `reg &= ~(1U << n)`
- [x] **Toggle a bit:** `reg ^= (1U << n)`
- [x] **Test a bit:** `if ((reg & (1U << n)) == 0)`
- [x] Multi-bit masks: setting/clearing a field (e.g. MODER[1:0])
- [x] The `1U` vs `1` distinction and why it matters at bit 31
- **Exercise:** Simulate a register byte; apply each pattern and verify the result — 🔄 in progress

### F04 — Fixed-Width Integers
- [ ] Why `int` size varies by architecture (16/32/64-bit)
- [ ] `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t` from `<stdint.h>`
- [ ] `int8_t`, `int16_t`, `int32_t` (signed)
- [ ] The `U` suffix: `0x48000000UL` vs `0x48000000`
- [ ] `SIZE_MAX`, `UINT32_MAX` sentinels
- **Exercise:** Declare registers as `volatile uint32_t`; observe what happens with plain `int` in a bit-shift edge case

### F05 — The `volatile` Keyword
- [ ] What the C compiler optimizer assumes about memory
- [ ] Why hardware registers get cached in a CPU register without `volatile`
- [ ] The infinite loop problem: polling a register without `volatile`
- [ ] `volatile` in ISR-shared variables
- [ ] What `volatile` does NOT protect against (not a synchronization primitive)
- **Exercise:** Write a polling loop; compile with `-O2`; inspect the assembly with and without `volatile`

### F06 — Pointers & Memory Addresses
- [ ] Pointer basics review: `*`, `&`, pointer arithmetic
- [ ] Casting an integer to a pointer: `(uint32_t *)0x48000000UL`
- [ ] Adding `volatile`: `(volatile uint32_t *)0x48000000UL`
- [ ] Dereferencing to read/write: `*ptr = value`, `value = *ptr`
- [ ] The complete bare metal register access pattern
- **Exercise:** Write a function `reg_write(uint32_t addr, uint32_t val)` and `reg_read(uint32_t addr)` using volatile pointer casts

### F07 — Macros for Register Access
- [ ] Object-like `#define` for base addresses and offsets
- [ ] Function-like macros with parameters
- [ ] Building `SET_BIT(reg, bit)`, `CLEAR_BIT(reg, bit)`, `READ_BIT(reg, bit)`, `MODIFY_REG(reg, mask, val)`
- [ ] Why CMSIS uses these exact macros (we're building the same thing)
- [ ] Macro pitfalls: missing parentheses, double evaluation
- **Exercise:** Implement the four macros; write a test harness that verifies each against known values

### F08 — Reading Component & Module Markings
- [ ] IC chip markings: manufacturer prefix, part number, package, date code, country
- [ ] Module silkscreen: `1.28" TFT VER1.0 240×240 IC:GC9A01` → GC9A01 is the display controller IC
- [ ] Package types: DIP, SOIC, TQFP, QFN, BGA, SOT-23 — how to identify from footprint
- [ ] Resistor color codes, capacitor markings (EIA codes)
- [ ] How to identify the communication interface from module markings (SPI/I2C/UART/parallel pins)
- **Exercise:** Given three mystery module photos, identify the driver IC and communication interface

### F09 — Finding & Reading External Device Datasheets
- [ ] How to find a datasheet: part number → manufacturer site → datasheet aggregators
- [ ] Datasheet structure for a peripheral IC vs an MCU reference manual
- [ ] Pin description table: signal names, directions, logic levels
- [ ] Electrical characteristics: VDD range, logic thresholds, max current
- [ ] Communication protocol section: SPI/I2C timing diagrams
- [ ] Initialization sequence tables: register writes in order
- [ ] How this maps to what we do in break projects
- **Exercise:** Find the GC9A01 datasheet; locate the SPI timing section and initialization register sequence

---

**→ Break Project BP-01** *(after completing Foundations — device TBD)*

---

## ENTRY TIER — From Toolchain to UART

> All register addresses derived by hand from RM035. No ST or CMSIS headers.

### E01 — Toolchain & CMake Setup
- [ ] Install arm-none-eabi-gcc, cmake, ninja, openocd
- [ ] Write `cmake/arm-none-eabi.cmake` toolchain file (shared, board-agnostic)
- [ ] Write `boards/NUCLEO-L476RG/cmake/stm32l476rg.cmake` (MCU flags: `-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard`)
- [ ] Write a minimal CMakeLists.txt for a chapter project
- [ ] Flash a pre-built `.bin` with OpenOCD to verify the chain works
- **Verify:** ST-LINK connects; OpenOCD flashes without error

### E02 — How to Read the Reference Manual
- [ ] RM035 §1: document conventions, register notation (`Res.`, `rw`, `r`, `w`)
- [ ] Memory map table (RM035 §2.2): how to read base address + offset
- [ ] Register description layout: bit position, name, reset value, access type, description
- [ ] Difference between RM035, datasheet, DUI0553, and UM1724
- [ ] How to search a 1400-page PDF efficiently
- **Exercise:** Locate the GPIOA base address and the MODER register offset; derive the full address manually

### E03 — Memory Map from Scratch
- [ ] Code Flash: `0x0800 0000` – `0x080F FFFF` (1 MB)
- [ ] SRAM1/SRAM2 addresses
- [ ] Peripheral bus addresses: AHB1, AHB2, APB1, APB2
- [ ] Writing a minimal `registers.h` with only base address `#define`s
- [ ] Volatile pointer casting in context (links back to F06)
- **Exercise:** Open RM035 §2.2; write `#define`s for GPIOA, GPIOB, RCC, USART2 base addresses by reading the table

### E04 — Startup Code & Linker Script
- [ ] ARM Cortex-M reset sequence (DUI0553 §2.3): what happens at power-on
- [ ] The vector table: what it is, where it lives (address `0x0800 0000`), how it's structured (DUI0553 §2.3.4)
- [ ] Writing the vector table as a C array with `__attribute__((section(".isr_vector")))`
- [ ] Writing `Reset_Handler`: copy .data from flash to SRAM, zero .bss, call `main()`
- [ ] Writing `STM32L476RGTx_FLASH.ld`: MEMORY regions, SECTIONS (.text, .rodata, .data, .bss)
- **Verify:** Board runs past startup into `main()` (confirm with a GPIO toggle in main)

### E05 — RCC Clock System
- [ ] RCC base address from RM035 §6
- [ ] `RCC_CR`: HSI16 enable/ready bits
- [ ] `RCC_CFGR`: system clock switch, AHB/APB prescalers
- [ ] `RCC_AHB2ENR`: enabling GPIOA clock (bit 0) before touching GPIOA registers
- [ ] Why touching a peripheral without its clock enabled silently does nothing (or hard faults)
- **Exercise:** Enable HSI16, confirm it's ready by polling HSIRDY, switch SYSCLK to HSI16

### E06 — GPIO from the Register Map
- [ ] GPIOA base: `0x4800 0000` (RM035 §8.4)
- [ ] `MODER` (offset 0x00): mode selection — 00 input, 01 output, 10 alt fn, 11 analog
- [ ] `OTYPER` (0x04): push-pull vs open-drain
- [ ] `OSPEEDR` (0x08): output speed
- [ ] `PUPDR` (0x0C): pull-up / pull-down / none
- [ ] `IDR` (0x10): input data register (read-only)
- [ ] `ODR` (0x14): output data register
- [ ] `BSRR` (0x18): atomic set/reset (upper 16 bits = reset, lower 16 = set)
- [ ] NUCLEO schematic (UM1724): identify LED pin (PA5) and button pin (PC13)
- **Verify:** LED blinks at 1 Hz; button press changes blink rate — all via hand-derived register access

### E07 — UART Polling
- [ ] USART2 base: `0x4000 4400` (RM035 §40)
- [ ] Baud rate register `BRR`: baud = PCLK / BRR; calculate for 115200 at 16 MHz HSI
- [ ] `CR1`: USART enable (UE), transmitter enable (TE), receiver enable (RE)
- [ ] `ISR`: TXE (transmit buffer empty), RXNE (receive buffer not empty)
- [ ] `TDR`/`RDR`: transmit/receive data registers
- [ ] Retargeting `_write()` to send printf output over UART to a terminal
- **Verify:** `printf("Hello\n")` appears in minicom/screen at 115200 baud

---

**→ Break Project BP-02** *(after completing Entry — device TBD)*

---

## NOVICE TIER — Interrupts, Timers & Protocols

> Still hand-derived registers. Moving from polling to interrupt-driven design.

### N01 — Interrupts & the NVIC
- [ ] ARM exception model (DUI0553 §2.3): Reset, NMI, HardFault, IRQn
- [ ] NVIC registers: `ISER`, `ICER`, `IPR` (priority) — addresses from DUI0553 §4.2
- [ ] EXTI lines: mapping GPIO pins to EXTI (SYSCFG_EXTICRn), RM035 §14
- [ ] Writing an EXTI ISR: `EXTI15_10_IRQHandler` for PC13 button
- [ ] Priority grouping: preempt priority vs sub-priority
- **Verify:** Button press triggers ISR; toggle LED from inside the ISR

### N02 — SysTick
- [ ] SysTick registers: `SYST_CSR`, `SYST_RVR`, `SYST_CVR` (DUI0553 §4.4)
- [ ] Calculating reload value for 1 ms tick at current SYSCLK
- [ ] `SysTick_Handler` ISR: incrementing a `volatile uint32_t` tick counter
- [ ] Blocking `delay_ms(n)` using the tick counter
- [ ] Non-blocking timeout pattern: `uint32_t start = get_tick(); ... if (get_tick() - start > timeout)`
- **Verify:** LED blinks at precise 500 ms intervals; verify with a stopwatch

### N03 — General Purpose Timers
- [ ] TIM2 base address (RM035 §26)
- [ ] `PSC` (prescaler) and `ARR` (auto-reload register): `f_timer = PCLK / (PSC+1) / (ARR+1)`
- [ ] `CR1`: counter enable (CEN), direction
- [ ] `DIER`: update interrupt enable (UIE)
- [ ] `SR`: update interrupt flag (UIF) — must clear in ISR
- [ ] `TIM2_IRQHandler`: ISR for timer update event
- **Verify:** LED toggles from TIM2 ISR every 250 ms

### N04 — PWM Generation
- [ ] TIM2 output compare mode (RM035 §26.3)
- [ ] `CCMRx`: output compare mode bits → PWM mode 1 (110)
- [ ] `CCRx`: capture/compare register — sets duty cycle
- [ ] `CCER`: output enable
- [ ] Alternate function mapping: PA0 → TIM2_CH1 (AF1) — set MODER to 10, AFRL to 0001
- [ ] Duty cycle formula: `CCR = (duty_percent * (ARR+1)) / 100`
- **Verify:** LED on PA0 dims smoothly as CCR value changes; measure with multimeter or scope

### N05 — UART with Interrupts
- [ ] `USART2_IRQHandler`: reading `RDR` when `RXNE` is set
- [ ] Circular ring buffer: head/tail indices, wrap-around, full/empty detection
- [ ] `CR1` RXNEIE bit: enable receive interrupt
- [ ] Non-blocking `uart_read_byte()` consuming from the ring buffer
- [ ] Thread-safety consideration: `volatile` on head/tail, atomic read of byte
- **Verify:** Echo server — type in terminal, characters echo back; no characters lost at 115200

### N06 — I2C Fundamentals
- [ ] I2C1 base address (RM035 §37)
- [ ] `CR1`: PE (peripheral enable), timing configuration
- [ ] `TIMINGR`: I2C timing register — use ST's timing calculator or formula for 100 kHz
- [ ] `CR2`: SADD (7-bit slave address), NBYTES, START, STOP, RD_WRN
- [ ] `ISR`: TXIS, RXNE, TC (transfer complete), BUSY, NACKF
- [ ] Read sequence: START → address+W → register byte → repeated START → address+R → read data → STOP
- **Verify:** Scan I2C bus; read device ID from an I2C device (use a temp sensor or the one on NUCLEO if present)

---

**→ Break Project BP-03** *(after completing Novice — device TBD)*

---

## INTERMEDIATE TIER — DMA, Analog & Power

> From I04 (DMA) onward, we build `boards/NUCLEO-L476RG/inc/stm32l476.h` incrementally — one peripheral at a time. You write every line; I guide from RM035.

### I01 — SPI Fundamentals
- [ ] SPI1 base address (RM035 §38)
- [ ] `CR1`: CPOL, CPHA, BR (baud rate divisor), MSTR, SPE
- [ ] `CR2`: DS (data size), FRXTH (FIFO threshold), SSOE
- [ ] `SR`: TXE, RXNE, BSY flags
- [ ] `DR`: data register (write to transmit, read to receive)
- [ ] NSS (chip select): software vs hardware control
- [ ] SPI modes (0/1/2/3): CPOL+CPHA combinations and which devices use which
- **Verify:** Send a known byte sequence; observe on logic analyzer (or loopback MOSI→MISO)

### I02 — DMA Controller
- [ ] DMA1/DMA2 base addresses, channel registers (RM035 §11)
- [ ] `CCRx`: EN, DIR, CIRC (circular), MINC, PINC, MSIZE, PSIZE, TEIE, TCIE
- [ ] `CNDTRx`: number of data items
- [ ] `CPARx`: peripheral address, `CMARx`: memory address
- [ ] Request mapping: which DMA channel/request handles which peripheral (RM035 §11.3)
- [ ] DMA ISR: `DMA1_Channel5_IRQHandler` (USART2 RX example)
- [ ] Starting our shared `stm32l476.h` header with DMA defines
- **Verify:** UART RX via DMA in circular mode — receive stream without CPU involvement

### I03 — ADC (Analog to Digital)
- [ ] ADC1 base address (RM035 §16)
- [ ] Calibration sequence: `ADCAL` bit, wait for cal complete
- [ ] `CFGR`: resolution, alignment, continuous mode
- [ ] `SQR1`: sequence length and first channel
- [ ] `SMPR1/2`: sampling time per channel
- [ ] `CR`: ADSTART, ADEN
- [ ] `DR`: data register (result)
- [ ] DMA-triggered ADC: continuous conversion filling a buffer
- **Verify:** Read the internal temperature sensor (ADC channel 17); print value in °C over UART

### I04 — DAC & Waveform Generation
- [ ] DAC1 base address (RM035 §17)
- [ ] `CR`: EN1, BOFF1, TEN1 (trigger enable), TSEL1 (trigger source)
- [ ] `DHR12R1`: 12-bit right-aligned data holding register
- [ ] `DOR1`: output register (read-only, shows current DAC output)
- [ ] Generating a sine wave: pre-computed LUT in flash, DMA feeds DAC, TIM6 triggers
- [ ] Timer trigger source selection for DAC
- **Verify:** Observe sine wave on PA4 with oscilloscope or DMM (should read ~VDD/2 average for sine)

### I05 — Advanced Timers (TIM1)
- [ ] TIM1 base address (RM035 §27) — advanced-control timer differences from TIM2
- [ ] Input capture: measuring pulse width or frequency of an external signal
- [ ] `CCMR1` input capture mode, `CCER` polarity, `CCR1` captured value
- [ ] Output compare with dead-time insertion (complementary outputs)
- [ ] Encoder interface mode: quadrature decoding from a rotary encoder
- **Verify:** Measure button press duration with input capture; display milliseconds over UART

### I06 — Low Power Modes
- [ ] STM32L476 power domains (RM035 §5)
- [ ] Sleep mode: `__WFI()` (Wait For Interrupt) — CPU stops, peripherals run
- [ ] Stop 2 mode: lowest power with SRAM retention, RTC still runs
- [ ] Standby mode: full shutdown, only backup domain alive, wakeup = reset
- [ ] Wakeup sources: EXTI line, RTC alarm, IWDG
- [ ] `PWR_CR1/CR2`: mode selection bits
- [ ] Current measurement: how to measure µA draw with a multimeter in current mode
- **Verify:** Enter Stop 2; wake with button press; confirm UART resumes printing (measure current difference)

---

**→ Break Project BP-04** *(after completing Intermediate — device TBD)*

---

## EXPERT TIER — System Design

> CMSIS headers introduced here as a comparison to `stm32l476.h` you built. Focus shifts from peripheral drivers to firmware system architecture.

### X01 — Watchdog Timers
- [ ] IWDG (Independent Watchdog): `KR`, `PR`, `RLR` registers (RM035 §32)
- [ ] IWDG clock: LSI ~32 kHz (independent of main clock — survives Stop mode)
- [ ] WWDG (Window Watchdog): must refresh within a window, not too early or too late
- [ ] Failure-safe patterns: where to pet the dog, what not to do in the refresh path
- [ ] Using watchdog as a hang detector in a bare metal loop
- **Verify:** Intentionally omit the refresh; confirm IWDG resets the MCU within the expected timeout

### X02 — Internal Flash Programming
- [ ] Flash memory map: pages, banks, erase granularity (RM035 §3)
- [ ] Flash unlock sequence: write `KEY1` then `KEY2` to `FLASH_KEYR`
- [ ] `FLASH_CR`: PG (program), PER (page erase), MER1/2 (mass erase), STRT
- [ ] `FLASH_SR`: BSY, EOP, error flags
- [ ] Double-word (64-bit) write requirement on L476
- [ ] Storing persistent config in the last flash page; reading it back after reset
- **Verify:** Write a value to flash, reset the board, read back the same value over UART

### X03 — Custom Bootloader
- [ ] Dual-region flash layout: bootloader at `0x0800 0000`, application at `0x0801 0000`
- [ ] Application vector table offset: `SCB->VTOR = 0x08010000`
- [ ] Jumping from bootloader to app: function pointer to app reset handler
- [ ] UART firmware update: receive new `.bin` via XMODEM or raw bytes, write to app region
- [ ] Fallback: if app region invalid (first word not a valid stack pointer), stay in bootloader
- **Verify:** Flash bootloader; send new app binary over UART; board boots new app without JTAG

### X04 — USB CDC (Virtual COM Port)
- [ ] STM32L476 USB FS peripheral (RM035 §44)
- [ ] USB descriptor tables: device, configuration, interface, endpoint descriptors
- [ ] Enumeration sequence: host requests, device responses
- [ ] Bulk transfer endpoint setup for CDC data class
- [ ] Replacing UART with USB CDC as the debug console
- [ ] Introduction to ST vendor headers (CMSIS): compare to our `stm32l476.h`
- **Verify:** Board appears as `/dev/ttyACMx` on Linux; send/receive data

### X05 — Bare Metal Cooperative Scheduler
- [ ] Task struct: function pointer, period, last-run tick
- [ ] Round-robin scheduler loop: iterate tasks, check if period elapsed, call if due
- [ ] Cooperative yield: tasks must return promptly; no blocking inside tasks
- [ ] Scheduling LED blink, UART print, and ADC read as separate tasks
- [ ] Limitations vs preemptive RTOS: what breaks, when you need a real RTOS
- **Verify:** Three tasks run concurrently at different rates; verify timing with GPIO toggles on scope

### X06 — FreeRTOS on Bare Metal
- [ ] FreeRTOS port for Cortex-M4: `port.c`, `portmacro.h`
- [ ] Integrating FreeRTOS source into our CMake project (no CubeMX)
- [ ] Tasks: `xTaskCreate`, task function signature, priorities
- [ ] Queues: `xQueueCreate`, `xQueueSend`, `xQueueReceive` for ISR→task comms
- [ ] Semaphores: binary semaphore for ISR notification
- [ ] Comparison to X05 scheduler: what FreeRTOS adds (preemption, stack isolation)
- **Verify:** Two FreeRTOS tasks blink LEDs at independent rates; ISR posts to queue; task processes event

---

**→ Break Project BP-05** *(after completing Expert — device TBD)*

---

## Break Project Format

Break projects are not pre-planned. When you have a device, we follow this sequence:

1. **Identify** — decode the module markings (F08 skills) to find the driver IC part number
2. **Datasheet** — locate and read the datasheet together (F09 skills), identify interface and init sequence
3. **Wire it up** — use UM1724 (NUCLEO schematic) to pick the right pins; check voltage levels
4. **Driver** — write a bare metal driver from scratch using skills from the completed tiers
5. **Demo** — build a small application that uses the device meaningfully
6. **Document** — add a `README.md` to the project folder describing the device, wiring, and what you learned

Break project folder: `boards/NUCLEO-L476RG/projects/break-projects/bpNN-device-name/`

---

## Progress Tracking

Mark chapters complete by checking off the checklist items above, then updating this table:

| Chapter | Status | Date Completed | Notes |
|---------|--------|---------------|-------|
| F01 | ✅ Complete | 2026-06-25 | |
| F02 | ✅ Complete | 2026-06-26 | |
| F03 | 🔄 In progress | — | exercise remaining |
| F04 | ⬜ Not started | — | |
| F05 | ⬜ Not started | — | |
| F06 | ⬜ Not started | — | |
| F07 | ⬜ Not started | — | |
| F08 | ⬜ Not started | — | |
| F09 | ⬜ Not started | — | |
| BP-01 | ⬜ Not started | — | Device: TBD |
| E01 | ⬜ Not started | — | |
| E02 | ⬜ Not started | — | |
| E03 | ⬜ Not started | — | |
| E04 | ⬜ Not started | — | |
| E05 | ⬜ Not started | — | |
| E06 | ⬜ Not started | — | |
| E07 | ⬜ Not started | — | |
| BP-02 | ⬜ Not started | — | Device: TBD |
| N01 | ⬜ Not started | — | |
| N02 | ⬜ Not started | — | |
| N03 | ⬜ Not started | — | |
| N04 | ⬜ Not started | — | |
| N05 | ⬜ Not started | — | |
| N06 | ⬜ Not started | — | |
| BP-03 | ⬜ Not started | — | Device: TBD |
| I01 | ⬜ Not started | — | |
| I02 | ⬜ Not started | — | |
| I03 | ⬜ Not started | — | |
| I04 | ⬜ Not started | — | |
| I05 | ⬜ Not started | — | |
| I06 | ⬜ Not started | — | |
| BP-04 | ⬜ Not started | — | Device: TBD |
| X01 | ⬜ Not started | — | |
| X02 | ⬜ Not started | — | |
| X03 | ⬜ Not started | — | |
| X04 | ⬜ Not started | — | |
| X05 | ⬜ Not started | — | |
| X06 | ⬜ Not started | — | |
| BP-05 | ⬜ Not started | — | Device: TBD |

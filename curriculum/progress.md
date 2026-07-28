# Progress — Mike White

Per-student tracking, split out of `curriculum/agenda.md` so that file can stay a clean template for other students who fork this repo. Read this alongside `agenda.md` at the start of a session to see what chapter is current.

Checklist items below mirror `agenda.md`'s chapter content at the time each chapter was worked — if `agenda.md`'s checklist for a chapter changes later, treat this file's copy as the historical record of what was actually covered, not a live mirror.

---

## Chapter Detail

### F01 — Binary, Hex & Number Representation
- [x] Binary, decimal, hex conversions by hand and in C
- [x] Two's complement (how negative numbers work in a register)
- [x] Why peripheral addresses are always written in hex (`0x48000000`)
- [x] `0b` binary literals, `0x` hex literals, digit grouping
- **Exercise:** Convert a set of addresses from the RM035 memory map table to binary; identify which bits are set — done (TIM2, RTC, UART5)

### F02 — Bitwise Operators
- [x] `&` (AND), `|` (OR), `^` (XOR), `~` (NOT/complement)
- [x] `<<` (left shift), `>>` (right shift)
- [x] Operator precedence — why parentheses matter
- [x] Common mistakes: signed vs unsigned shifts, shifting past width
- **Exercise:** Write a program that demonstrates each operator on known values and prints the results in hex — done

### F03 — Bit Manipulation Patterns
- [x] Set a bit, clear a bit, toggle a bit, test a bit
- [x] Multi-bit masks: setting/clearing a field (e.g. MODER[1:0])
- [x] The `1U` vs `1` distinction and why it matters at bit 31
- **Exercise:** Simulate a register byte; apply each pattern and verify the result — done

### F04 — Fixed-Width Integers
- [x] Why `int` size varies by architecture (16/32/64-bit)
- [x] `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t` from `<stdint.h>`
- [x] `int8_t`, `int16_t`, `int32_t` (signed)
- [x] The `U` suffix: `0x48000000UL` vs `0x48000000`
- [x] `SIZE_MAX`, `UINT32_MAX` sentinels
- **Exercise:** Declare registers as `uint32_t`; observe what happens with plain `int` in a bit-shift edge case — done

### F05 — The `volatile` Keyword
- [x] What the C compiler optimizer assumes about memory
- [x] Why hardware registers get cached in a CPU register without `volatile`
- [x] The infinite loop problem: polling a register without `volatile`
- [x] `volatile` in ISR-shared variables
- [x] What `volatile` does NOT protect against (not a synchronization primitive)
- **Exercise:** Write a polling loop; compile with `-O2`; inspect the assembly with and without `volatile` — done

### F06 — Pointers & Memory Addresses — Partial
- [x] Pointer basics review: `*`, `&`, pointer arithmetic
- [x] Casting an integer to a pointer: `(uint32_t *)0x48000000UL`
- [x] Adding `volatile`: `(volatile uint32_t *)0x48000000UL`
- [x] Dereferencing to read/write: `*ptr = value`, `value = *ptr`
- [ ] The complete bare metal register access pattern
- **Exercise:** Write a function `reg_write(uint32_t addr, uint32_t val)` and `reg_read(uint32_t addr)` using volatile pointer casts — skipped, not attempted

### F07 — Macros for Register Access — Partial
- [x] Object-like `#define` for base addresses and offsets
- [ ] Function-like macros with parameters
- [ ] Building `SET_BIT(reg, bit)`, `CLEAR_BIT(reg, bit)`, `READ_BIT(reg, bit)`, `MODIFY_REG(reg, mask, val)`
- [ ] Why CMSIS uses these exact macros (we're building the same thing)
- [x] Macro pitfalls: missing parentheses, double evaluation
- **Exercise:** Implement the four macros; write a test harness that verifies each against known values — skipped, not attempted

### F08 — Reading Component & Module Markings
- [x] IC chip markings: manufacturer prefix, part number, package, date code, country
- [x] Module silkscreen decode
- [x] Package types: DIP, SOIC, TQFP, QFN, BGA, SOT-23
- [x] Resistor color codes, capacitor markings (EIA codes) — self-reported prior knowledge, not walked through together
- [x] How to identify the communication interface from module markings
- **Exercise:** Given three mystery module photos, identify the driver IC and communication interface — done on real GC9A01 module: driver IC = GC9A01, interface = SPI (4-wire), pins `RST, CS, DC, SDA, SCL, GND, VCC` (SDA/SCL labels are holdovers, actually MOSI/SCK), no BLK pin (backlight hardwired on)

### F09 — Finding & Reading External Device Datasheets
- [ ] How to find a datasheet: part number → manufacturer site → datasheet aggregators
- [ ] Datasheet structure for a peripheral IC vs an MCU reference manual
- [ ] Pin description table: signal names, directions, logic levels
- [ ] Electrical characteristics: VDD range, logic thresholds, max current
- [ ] Communication protocol section: SPI/I2C timing diagrams
- [ ] Initialization sequence tables: register writes in order
- [ ] How this maps to what we do in break projects
- [x] **Exercise:** Find the GC9A01 datasheet; locate the SPI timing section and initialization register sequence — done. Found GC9A01A datasheet (Galaxycore), placed in `break-projects/bp01-gc9a01-display/docs/`; located 4-wire serial timing diagram (p.190) and command list (§6)

### E01 — ELF & Binary Format Fundamentals — Partial
- `main.c` (trivial `int main(){return 0;}`) written and compiled to a native ELF binary in `NUCLEO-L476RG/entry/e01-elf-fundamentals/`
- [ ] `readelf -h/-S/-l` and `objdump -h` analysis exercise — not yet walked through
- Resume here: walk the concepts (ELF header, section header table, program header table, sections vs segments, why `.bin`/`.hex` exist), then have the student run the readelf/objdump commands themselves and interpret the output

---

## Progress Tracking

| Chapter | Status | Date Completed | Notes |
|---------|--------|---------------|-------|
| F01 | ✅ Complete | 2026-06-25 | |
| F02 | ✅ Complete | 2026-06-26 | |
| F03 | ✅ Complete | 2026-06-26 | |
| F04 | ✅ Complete | 2026-07-03 | |
| F05 | ✅ Complete | 2026-07-10 | |
| F06 | 🔶 Partial | 2026-07-10 | Concepts covered; reg_write/reg_read exercise skipped |
| F07 | 🔶 Partial | 2026-07-11 | Object-like #define + parens pitfall covered; function-like macros (SET_BIT etc.) and exercise skipped |
| F08 | ✅ Complete | 2026-07-11 | Chip marking decode, package types, module silkscreen decode, resistor/cap EIA codes (self-reported), comm-interface pin ID all covered; exercise done on real GC9A01 module (SPI, 7 pins, no BLK) |
| F09 | ✅ Complete | 2026-07-11 | Datasheet found (GC9A01A, Galaxycore) and saved to bp01 project folder; located timing + command sections |
| BP-01 | ⏸ Paused | 2026-07-11 | Device: GC9A01 display. Datasheet found and saved; paused before wiring/driver work — overwhelmed by hardware terminology, resuming after Entry tier |
| E01 | 🔶 Partial | 2026-07-27 | ELF & Binary Format Fundamentals. `main.c` compiled to a native ELF; readelf/objdump analysis exercise not yet done — resume here |
| E02 | ⬜ Not started | — | Toolchain & CMake Setup |
| E03 | ⬜ Not started | — | How to Read the Reference Manual |
| E04 | ⬜ Not started | — | Memory Map from Scratch |
| E05 | ⬜ Not started | — | Startup Code & Linker Script |
| E06 | ⬜ Not started | — | RCC Clock System |
| E07 | ⬜ Not started | — | GPIO from the Register Map |
| E08 | ⬜ Not started | — | UART Polling |
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

# Bare Metal C — Cheat Sheet

---

## Number Systems

| Base | Name | Digits | C Prefix | Example |
|------|------|--------|----------|---------|
| 2 | Binary | 0, 1 | `0b` | `0b00001111` |
| 10 | Decimal | 0–9 | *(none)* | `15` |
| 16 | Hex | 0–9, A–F | `0x` | `0x0F` |

### The key relationship
**1 hex digit = exactly 4 bits (a "nibble")**

So a 32-bit value always takes exactly 8 hex digits:

```
0x 4800 0000
   ^^^^ ^^^^
   8 hex digits = 32 bits
```

This is why peripheral addresses are written in hex — you can see the bit groupings at a glance. Decimal gives you no such structure.

---

## Signed vs Unsigned — Two's Complement

Same bit pattern, different interpretation depending on the type.

### 8-bit example

| Bit pattern | Unsigned (`uint8_t`) | Signed (`int8_t`) |
|-------------|----------------------|-------------------|
| `00000000`  | 0                    | 0                 |
| `01111111`  | 127                  | 127               |
| `10000000`  | 128                  | -128              |
| `11111111`  | 255                  | -1                |

### Ranges

| Type | Min | Max |
|------|-----|-----|
| `uint8_t` | 0 | 255 |
| `int8_t` | -128 | 127 |
| `uint32_t` | 0 | 4,294,967,295 |
| `int32_t` | -2,147,483,648 | 2,147,483,647 |

### The trick: -1 is all ones

In two's complement, `-1` is always represented as all bits set — regardless of width:
- 8-bit:  `11111111`
- 16-bit: `1111111111111111`
- 32-bit: `11111111111111111111111111111111`

### Why it matters in embedded

- **Register addresses** → always `uint32_t` (unsigned, no negatives)
- **Control/status bits** → always unsigned (bit fields, not magnitudes)
- **Sensor data** (ADC, temperature, accelerometer) → may be `int32_t` if the value can be negative

Declaring a signed-encoded register value as `uint32_t` will give you the wrong number. The hardware doesn't care — it just stores bits. Your C type determines the interpretation.

---

## Bitwise Operators

| Operator | Symbol | Result is 1 when... | Example |
|----------|--------|---------------------|---------|
| AND | `&` | **both** bits are 1 | `0b1100 & 0b1010 = 0b1000` |
| OR | `\|` | **either** bit is 1 | `0b1100 \| 0b1010 = 0b1110` |
| XOR | `^` | bits are **different** | `0b1100 ^ 0b1010 = 0b0110` |
| NOT | `~` | *(flips every bit)* | `~0b00001100 = 0b11110011` |
| Left shift | `<<` | *(moves bits left, fills 0s on right)* | `0b00000001 << 3 = 0b00001000` |
| Right shift | `>>` | *(moves bits right, fills 0s on left)* | `0b00010000 >> 2 = 0b00000100` |

### Key facts

- `<<  n` is equivalent to multiplying by 2ⁿ
- `>>  n` is equivalent to dividing by 2ⁿ (unsigned)
- `1U << n` puts a single `1` at bit position `n` — used constantly for bit masks

### Operator precedence — always use parentheses

Bitwise operators have lower precedence than `==`. This is a silent bug:

```c
if (reg & 0x01 == 1)    // WRONG: evaluates as reg & (0x01 == 1)
if ((reg & 0x01) == 1)  // CORRECT: AND happens first
```

When in doubt, parenthesize your bitwise operations.

---

## Bit Manipulation Patterns

These four patterns are used in every bare metal peripheral driver.

### Single-bit operations

```c
reg |= (1U << n);              // SET bit n
reg &= ~(1U << n);             // CLEAR bit n
reg ^= (1U << n);              // TOGGLE bit n
if ((reg & (1U << n)) == 0)    // TEST if bit n is clear
if ((reg & (1U << n)) != 0)    // TEST if bit n is set
```

### Multi-bit field (e.g. a 2-bit field at bits 3:2)

```c
reg &= ~((1U << 3) | (1U << 2));   // clear the field (mask covers both bits)
reg |= (value << 2);                // write new value into field position
```

Or combined into one line:
```c
reg = (reg & ~(0x3U << 2)) | (value << 2);
```

### Why `1U` not `1`

`1` is a signed `int`. Shifting it into bit 31 is undefined behavior in C. `1U` is unsigned — no sign bit, no undefined behavior. Always use `1U` in bit masks.

### Why always clear before set (multi-bit fields)

OR-ing without clearing first leaves old bits set. Always clear the field first, then OR in the new value.

---

*(More sections added as chapters are completed)*

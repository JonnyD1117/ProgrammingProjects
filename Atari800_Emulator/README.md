# Atari 800 Emulator (C++)

A modular Atari 800 / 8-bit family emulator written in modern C++.

This project aims to emulate the Atari 800 hardware as accurately as possible while keeping the architecture clean, modular, and data-driven. A major design goal is separating hardware descriptions from implementation logic so components can be generated or modified without rewriting large portions of the emulator.

The emulator includes a 6502 CPU core, memory bus, and implementations of the custom Atari chips.

## Goals

- Accurate emulation of the Atari 800 hardware
- Clean, modular C++ architecture
- Data-driven CPU instruction definitions
- Hardware components that are easy to extend and test
- Avoid large monolithic opcode switch statements
- Provide a platform for experimentation and learning about 8-bit systems

## System Overview

The Atari 800 hardware consists of several major components:

Component	Description
6502 CPU	Main processor running at ~1.79 MHz
ANTIC	Video display processor
GTIA	Graphics and sprite hardware
POKEY	Sound generation, timers, and I/O
PIA	Peripheral Interface Adapter
RAM / ROM	System memory and OS

This emulator models each component as a separate C++ module connected through a shared system bus.
```bash

        +----------------+
        |     6502 CPU   |
        +--------+-------+
                 |
          +------+------+
          |   System Bus |
          +------+------+
                 |
   +------+------+------+------+
   | ANTIC | GTIA | POKEY | RAM |
   +-------+------+-------+-----+
```

## 6502 CPU Design

Instead of implementing the CPU instruction decode using a large switch statement, the emulator uses a data-driven instruction system.

Example:

```
instruction_set:
  # ADD WITH CARRY
  - opcode: 0x6d
    mnemonic: ADC
    mode: absolute
    cycles: 4
    page_boundry_cycles: 0
    affects_flags: [N, V, Z, C]
    handler: add_with_carry

```

## Planned Features

- [ ] Full 6502 instruction support
- [ ] Undocumented opcodes
- [ ] Accurate cycle timing
- [ ] ANTIC display list emulation
- [ ] GTIA graphics modes
- [ ] POKEY audio
- [ ] Disk drive emulation
- [ ] Input devices (keyboard/joystick)
- [ ] Debugger

### Debugging Features (Planned)

- CPU step mode
- Instruction tracing
- Memory inspector
- Breakpoints
- Disassembler
- Inspiration
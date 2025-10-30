# 6502 CPU Emulator

The objective of this project is to construct a 6502 CPU emulator (in the c++ programming language) that is capable of running 6502 executables from old Atari 800/800XL ISOs. The end goal of this project will be the implementation of an Atari 800 emulator whose CPU is th 6502.

![MOS Technology 6502](https://upload.wikimedia.org/wikipedia/commons/4/49/MOS_6502AD_4585_top.jpg)

## 6502 Specs

* 8-Bit Data Bus
* 16-Bit Address Bus
* 16-Bit Control Bus

## Internal Structure

1) ALU
2) Processor Status Flag (P) [8-Bit]
3) Program Counter (PCH & PCL) Higher & Lower 8-bit reg [Contains the address of the next instruction to be run]
4) X Index Register (X) [8-Bits]
5) Y Index Register (Y) [8-Bits]
6) Stack Register (S)

## Instruction Execution Cycle

The processor proceeds using 3-cycles.

1) Fetch
2) Decode
3) Execute

### Fetch

The contents of the program counter are output on the address bus. A read signal is generated. The memory cycles. Perhaps 300 ns later, the instruction at the specified address is deposited on the data-bus. THe microprocessor then reads the data-bus and deposits its contents into a specialized internal register, the IR register. THe IR register is the **instruction-register**. It is 8 bits wide and is used to contain the instruction just fetched from the memory. The fetch cycle is now completed. The 8-bits of the instruction are now physically in the special internal register of the 6502, the IR register.

### Decoding & Execution

Once the insturction is contained in IR. the control-unit of the microprocessor will decode the contents and will be able to generate the correct sequence of internal and external signals for the executation of the specified instruction. Ther is, therefore, a short decoding delay followed by an execution phase, the length of which dpends on the nature of the instruction specified.

## The Stack

A stack is formally called an LIFO structure (Last in First Out). A stack is a set of registers, or memory locations, allocated to this data structure. The essential characteristic of this strucutre is that it is **chonological**. THe first element introduced into the stack is always at the bottom of the stack. The element most recently deposited in the stack is on the top of the stack. The stack is accessible by two functions **push()** & **pop()**.

The availability of a stack is required to implement three programming facilities within the computer system:

1) subroutines
2) interupts
3) temporary data storage

For most general-purpose MPUs the stack is implement as a contiguous block of memory

## Paging

The 6502 has a 16-bit address bus and allows for ~64K combinations of addresses. It is convienent to break up this space into smaller more manageable chunks. A page is simply a block of 256 words. It should be noted that whenever a page boundary is crossed, it will often produce cycle delay.
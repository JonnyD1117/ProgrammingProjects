#include <iostream>
#include "6502_headers.hpp"

using Mem = MOS6502::Memory;
// using namespace MOS6502;
using CPU = MOS6502::CPU;


int main() {

    CPU cpu;            // Instantiate CPU
    Mem mem;            // Instantiate MEMORY

    cpu.Reset(mem);     // Initialize CPU -> initialize memory

    mem[0xFFFC] = CPU::INS_LDA_ZP;
    mem[0xFFFD] = 0x42;
    mem[0x0042] = 0x84;

    cpu.Execute(mem, 3);// Execute 2 Cycles

    std::cout<< "Main Finshed" << std:: endl;
    return 0;
}

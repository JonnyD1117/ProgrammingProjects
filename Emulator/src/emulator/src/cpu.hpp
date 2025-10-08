#pragma once

// std
#include "memory.hpp"
#include <cassert>
#include <iostream>
#include <cstdint>

// MOS6502
#include "status.hpp"
// #include "instruction_set.hpp"

namespace MOS6502
{

struct CPU
{
    // Define 6502 Internal Registers
    uint16_t PC;        // Declare Program Counter
    uint8_t  SP;        // Declare Stack Pointer
    uint8_t  A;         // Declare Accumulator
    uint8_t  X;         // Declare Index Reg. X
    uint8_t  Y;         // Declare Index Reg. Y
    ProcessorStatus P;  // Declare Processor Register

    
};
}
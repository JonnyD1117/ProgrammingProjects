#pragma once

#include <cstdint>

namespace MOS6502
{

struct ProcessorStatus
{
    uint8_t C : 1; // Carry Bit Flag
    uint8_t Z : 1; // Zero Result Flag
    uint8_t I : 1; // Interrupt Disable
    uint8_t D : 1; // Decimal Mode Flag
    uint8_t B : 1; // Break Command
    uint8_t U : 1; // Unused (always 1 when pushed to stack)
    uint8_t V : 1; // Overflow Flag
    uint8_t N : 1; // Negative Flag

    // Carry Helpers
    void setCarryFlag()          { C = 1; }
    void clearCarryFlag()        { C = 0; }
    
    // Zero Helpers
    void setZeroFlag()           { Z = 1; }
    void clearZeroFlag()         { Z = 0; }
    
    // Interrupt Helpers
    void setInterruptDisable()   { I = 1; }
    void clearInterruptDisable() { I = 0; }

    // Break Helpers
    void setBreakFlag()          { B = 1; }
    void clearBreakFlag()        { B = 0; }

    // Overflow Helpers
    void setOverflowFlag ()      { V = 1; }
    void clearOverFlowFlag()     { V = 0; }

    // Negative Helpers
    void setNegativeFlag()       { N = 1; }
    void clearNegativeFlag()     { N = 0; }

};

} // MOS6502
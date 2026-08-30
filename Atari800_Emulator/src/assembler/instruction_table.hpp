
#pragma once 


// std 
#include <cstdint>
#include <string>
#include <unordered_map>


enum class OpCode
{
    ADC=0, 
    AND, 
    ASL,
    BCC,
    BCS,
    BEQ,
    BIT,
    BMI,
    BNE,
    BPL,
    BRK,
    BVC,
    BVS,
    CLC,
    CLD,
    CLI,
    CLV,
    CMP,
    CPX,
    CPY,
    DEC,
    DEX,
    EOR,
    INC,
    INX,
    INY,
    JMP,
    JSR,
    LDA,
    LDX,
    LDY,
    LSR, 
    NOP,
    ORA,
    PHA,
    PHP,
    PLA,
    ROL,
    ROR,
    RTI,
    RTS,
    SBC,
    SEC,
    SED,
    SEI,
    STA,
    STX,
    STY,
    TAX,
    TAY,
    TSX,
    TXA,
    TXS
    TYA
};

enum class AddressingMode 
{
    ACCUMULATOR=0,
    ABSOLUTE,
    ABSOLUTE_X,
    ABSOLUTE_Y,
    IMMEDIATE,
    IMPLIED,
    INDIRECT,
    INDIRECT_X,
    INDIRECT_Y,
    RELATIVE,
    ZEROPAGE, 
    ZEROPAGE_X,
    ZEROPAGE_Y
};

// Assumption "string" representation is assumed to be lower case
static std::unordered_map<std::string, OpCode> opcodeStr2Enum
{
    { "adc",ADC=0}, 
    { "and",AND}, 
    { "asl",ASL},
    { "bcc",BCC},
    { "bcs",BCS},
    { "beq",BEQ},
    { "bit",BIT},
    { "bmi",BMI},
    { "bne",BNE},
    { "bpl",BPL},
    { "brk",BRK},
    { "bvc",BVC},
    { "bvs",BVS},
    { "clc",CLC},
    { "cld",CLD},
    { "cli",CLI},
    { "clv",CLV},
    { "cmp",CMP},
    { "cpx",CPX},
    { "cpy",CPY},
    { "dec",DEC},
    { "dex",DEX},
    { "eor",EOR},
    { "inc",INC},
    { "inx",INX},
    { "iny",INY},
    { "jmp",JMP},
    { "jsr",JSR},
    { "lda",LDA},
    { "ldx",LDX},
    { "ldy",LDY},
    { "lsr",LSR },
    { "nop",NOP},
    { "ora",ORA},
    { "pha",PHA},
    { "php",PHP},
    { "pla",PLA},
    { "rol",ROL},
    { "ror",ROR},
    { "rti",RTI},
    { "rts",RTS},
    { "sbc",SBC},
    { "sec",SEC},
    { "sed",SED},
    { "sei",SEI},
    { "sta",STA},
    { "stx",STX},
    { "sty",STY},
    { "tax",TAX},
    { "tay",TAY},
    { "tsx",TSX},
    { "txa",TXA},
    { "txs",TXS},
    { "tya",TYA},
};


class InstructionTable
{
    public: 

    uint16_t getAddress( const std::string opt)
    {
        return 0;
    }


    private:

    std::unordered_map<std::string, std::string> m_table 
};
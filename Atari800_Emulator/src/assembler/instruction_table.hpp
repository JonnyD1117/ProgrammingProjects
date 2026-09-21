
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
    TXS,
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
    { "adc",OpCode::ADC}, 
    { "and",OpCode::AND}, 
    { "asl",OpCode::ASL},
    { "bcc",OpCode::BCC},
    { "bcs",OpCode::BCS},
    { "beq",OpCode::BEQ},
    { "bit",OpCode::BIT},
    { "bmi",OpCode::BMI},
    { "bne",OpCode::BNE},
    { "bpl",OpCode::BPL},
    { "brk",OpCode::BRK},
    { "bvc",OpCode::BVC},
    { "bvs",OpCode::BVS},
    { "clc",OpCode::CLC},
    { "cld",OpCode::CLD},
    { "cli",OpCode::CLI},
    { "clv",OpCode::CLV},
    { "cmp",OpCode::CMP},
    { "cpx",OpCode::CPX},
    { "cpy",OpCode::CPY},
    { "dec",OpCode::DEC},
    { "dex",OpCode::DEX},
    { "eor",OpCode::EOR},
    { "inc",OpCode::INC},
    { "inx",OpCode::INX},
    { "iny",OpCode::INY},
    { "jmp",OpCode::JMP},
    { "jsr",OpCode::JSR},
    { "lda",OpCode::LDA},
    { "ldx",OpCode::LDX},
    { "ldy",OpCode::LDY},
    { "lsr",OpCode::LSR },
    { "nop",OpCode::NOP},
    { "ora",OpCode::ORA},
    { "pha",OpCode::PHA},
    { "php",OpCode::PHP},
    { "pla",OpCode::PLA},
    { "rol",OpCode::ROL},
    { "ror",OpCode::ROR},
    { "rti",OpCode::RTI},
    { "rts",OpCode::RTS},
    { "sbc",OpCode::SBC},
    { "sec",OpCode::SEC},
    { "sed",OpCode::SED},
    { "sei",OpCode::SEI},
    { "sta",OpCode::STA},
    { "stx",OpCode::STX},
    { "sty",OpCode::STY},
    { "tax",OpCode::TAX},
    { "tay",OpCode::TAY},
    { "tsx",OpCode::TSX},
    { "txa",OpCode::TXA},
    { "txs",OpCode::TXS},
    { "tya",OpCode::TYA},
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
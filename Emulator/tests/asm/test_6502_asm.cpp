#include <gtest/gtest.h>
#include "6502_headers.hpp"
#include <iostream>

/*
 * ADD with Carry (ADC)
 */
TEST(Assm_Instr_Tests, ADC_Immediate)
{
    /// Add Contents of current PC to Accumulator with Carry

    /*
     * Test Adding Value to Accumulator Works correctly
     */
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 2;             // # Cycles ADC_IM takes


    cpu.A = 0;                                  // Zero Accumulator
    memory[cpu.PC] = cpu.INS_ADC_IM;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 255;                     // Next PC addr contains value to be added to Accum

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.A, 255);

    /*
     * Test Overflowing Accumulator Set V-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    memory[cpu.PC] = cpu.INS_ADC_IM;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 128;                     // Next PC addr contains value to be added to Accum

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.V);    // ANDing signed 7th bit should be true

    /*
     * Test Overflowing Accumulator Sets C-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    memory[cpu.PC] = cpu.INS_ADC_IM;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 200;                     // Next PC addr contains value to be added to Accum

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.C);    // ANDing signed 7th bit should be true

    /*
     * Test Accumulator with Value = 0 Sets Z-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    memory[cpu.PC] = cpu.INS_ADC_IM;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0;                     // Next PC addr contains value to be added to Accum

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.Z);    // ANDing signed 7th bit should be true

    /*
     * Test Accumulator with Value < 0 Sets N-flag (2s-Complement)
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 167;                                  // Zero Accumulator
    memory[cpu.PC] = cpu.INS_ADC_IM;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0;                     // Next PC addr contains value to be added to Accum

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.N);    // ANDing signed 7th bit should be true
}

TEST(Assm_Instr_Tests, ADC_Zero_Page)
{
    /// Add Contents of current PC to Accumulator with Carry (ZeroPage)

    /*
     * Test Adding Value to Accumulator Works correctly
     */
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 3;             // # Cycles ADC_IM takes


    cpu.A = 0;                                  // Zero Accumulator
    memory[cpu.PC] = cpu.INS_ADC_ZP;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 125;                     // Next PC addr contains value to be added to Accum
    memory[125] = 55;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.A, 55);

    /*
     * Test Overflowing Accumulator Set V-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    memory[cpu.PC] = cpu.INS_ADC_ZP;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 120;                     // Next PC addr contains value to be added to Accum
    memory[120] = 128;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.V);    // ANDing signed 7th bit should be true

    /*
     * Test Overflowing Accumulator Sets C-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    memory[cpu.PC] = cpu.INS_ADC_ZP;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 120;                     // Next PC addr contains value to be added to Accum
    memory[120] = 152;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.C);    // ANDing signed 7th bit should be true

    /*
     * Test Accumulator with Value = 0 Sets Z-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    memory[cpu.PC] = cpu.INS_ADC_ZP;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 120;                     // Next PC addr contains value to be added to Accum
    memory[120] = 0;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.Z);    // ANDing signed 7th bit should be true

    /*
     * Test Accumulator with Value < 0 Sets N-flag (2s-Complement)
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 167;                                  // Zero Accumulator
    memory[cpu.PC] = cpu.INS_ADC_ZP;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 120;                     // Next PC addr contains value to be added to Accum
    memory[120] = 12;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.N);    // ANDing signed 7th bit should be true
}

TEST(Assm_Instr_Tests, ADC_Zero_Page_X)
{
    /// Add Contents of current PC to Accumulator with Carry (ZeroPage,X)

    /*
     * Test Adding Value to Accumulator Works correctly
     */
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 4;             // # Cycles ADC_IM takes

    cpu.A = 0;                                  // Zero Accumulator
    cpu.X = 50;
    memory[cpu.PC] = cpu.INS_ADC_ZP_X;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 120;                     // Next PC addr contains value to be added to Accum
    memory[120 + 50] = 55;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.A, 55);

    /*
     * Test Overflowing Accumulator Set V-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.X = 50;
    memory[cpu.PC] = cpu.INS_ADC_ZP_X;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 120;                     // Next PC addr contains value to be added to Accum
    memory[120 + 50] = 128;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.V);    // ANDing signed 7th bit should be true

    /*
     * Test Overflowing Accumulator Sets C-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.X = 50;
    memory[cpu.PC] = cpu.INS_ADC_ZP_X;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 120;                     // Next PC addr contains value to be added to Accum
    memory[120 + 50] = 152;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.C);    // ANDing signed 7th bit should be true

    /*
     * Test Accumulator with Value = 0 Sets Z-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.X = 50;
    memory[cpu.PC] = cpu.INS_ADC_ZP_X;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 120;                     // Next PC addr contains value to be added to Accum
    memory[120 + 50] = 0;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.Z);    // ANDing signed 7th bit should be true

    /*
     * Test Accumulator with Value < 0 Sets N-flag (2s-Complement)
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 167;                                  // Zero Accumulator
    cpu.X = 50;
    memory[cpu.PC] = cpu.INS_ADC_ZP_X;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 120;                     // Next PC addr contains value to be added to Accum
    memory[120 + 50] = 12;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.N);    // ANDing signed 7th bit should be true
}

TEST(Assm_Instr_Tests, ADC_ABS)
{
    /// Add Contents of current PC to Accumulator with Carry (Absolute)

    /*
     * Test Adding Value to Accumulator Works correctly
     */
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 4;             // # Cycles ADC_IM takes

    cpu.A = 0;                                  // Zero Accumulator
    memory[cpu.PC] = cpu.INS_ADC_ABS;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xd0;                     // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] =0x07;
    memory[0x07d0] = 125;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.A, 125);

    /*
     * Test Overflowing Accumulator Set V-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    memory[cpu.PC] = cpu.INS_ADC_ABS;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xd0;                     // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] =0x07;
    memory[0x07d0] = 128;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.V);    // ANDing signed 7th bit should be true

    /*
     * Test Overflowing Accumulator Sets C-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    memory[cpu.PC] = cpu.INS_ADC_ABS;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xd0;                     // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] =0x07;
    memory[0x07d0] = 128;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.C);    // ANDing signed 7th bit should be true

    /*
     * Test Accumulator with Value = 0 Sets Z-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    memory[cpu.PC] = cpu.INS_ADC_ABS;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xd0;                     // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] =0x07;
    memory[0x07d0] = 0;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.Z);    // ANDing signed 7th bit should be true

    /*
     * Test Accumulator with Value < 0 Sets N-flag (2s-Complement)
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    memory[cpu.PC] = cpu.INS_ADC_ABS;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xd0;                     // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] =0x07;
    memory[0x07d0] = 128;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.N);    // ANDing signed 7th bit should be true
}

TEST(Assm_Instr_Tests, ADC_ABS_X)
{
    /// Add Contents of current PC to Accumulator with Carry (Absolute,X)

    /*
     * Test Adding Value to Accumulator Works correctly
     */
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 4;             // # Cycles ADC_IM takes

    cpu.A = 0;                                  // Zero Accumulator
    cpu.X = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_X;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xd0;                  // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] =0x07;
    memory[(0x07d0 + cpu.X)] = 125;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.A, 125);

    /*
     * Test Overflowing Accumulator Set V-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.X = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_X;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xd0;                     // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] =0x07;
    memory[(0x07d0 + cpu.X)] = 128;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.V);    // ANDing signed 7th bit should be true

    /*
     * Test Overflowing Accumulator Sets C-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.X = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_X;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xd0;                     // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] =0x07;
    memory[(0x07d0 + cpu.X)] = 128;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.C);    // ANDing signed 7th bit should be true

    /*
     * Test Accumulator with Value = 0 Sets Z-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.X = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_X;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xd0;                     // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] =0x07;
    memory[(0x07d0 + cpu.X)] = 0;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.Z);    // ANDing signed 7th bit should be true

    /*
     * Test Accumulator with Value < 0 Sets N-flag (2s-Complement)
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.X = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_X;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xd0;                     // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] =0x07;
    memory[(0x07d0 + cpu.X)] = 128;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.N);    // ANDing signed 7th bit should be true
}

TEST(Assm_Instr_Tests, ADC_ABS_Y)
{
    /// Add Contents of current PC to Accumulator with Carry (Absolute,Y)

    /*
     * Test Adding Value to Accumulator Works correctly
     */
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 4;             // # Cycles ADC_IM takes

    cpu.A = 0;                                  // Zero Accumulator
    cpu.Y = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_Y;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xd0;                  // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] =0x07;
    memory[(0x07d0 + cpu.Y)] = 125;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.A, 125);

    /*
     * Test Overflowing Accumulator Set V-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.Y = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_Y;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xd0;                     // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] =0x07;
    memory[(0x07d0 + cpu.Y)] = 128;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.V);    // ANDing signed 7th bit should be true

    /*
     * Test Overflowing Accumulator Sets C-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.Y = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_Y;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xd0;                     // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] =0x07;
    memory[(0x07d0 + cpu.Y)] = 128;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.C);    // ANDing signed 7th bit should be true

    /*
     * Test Accumulator with Value = 0 Sets Z-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.Y = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_Y;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xd0;                     // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] =0x07;
    memory[(0x07d0 + cpu.Y)] =0;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.Z);    // ANDing signed 7th bit should be true

    /*
     * Test Accumulator with Value < 0 Sets N-flag (2s-Complement)
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.Y = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_Y;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xd0;                     // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] =0x07;
    memory[(0x07d0 + cpu.Y)] = 128;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.N);    // ANDing signed 7th bit should be true
}

TEST(Assm_Instr_Tests, ADC_INDR_X)
{
    /// Add Contents of current PC to Accumulator with Carry (Indirect,X)

    /*
     * Test Adding Value to Accumulator Works correctly
     */
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 6;             // # Cycles ADC_IM takes

    cpu.A = 0;                                  // Zero Accumulator
    cpu.X = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_INDR_X;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x9B;                  // Next PC addr contains value to be added to Accum
    memory[(0x9B + cpu.X)] = 125;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.A, 125);

    /*
     * Test Overflowing Accumulator Set V-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.X = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_X;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x9B;                     // Next PC addr contains value to be added to Accum
    memory[(0x9B + cpu.X)] = 128;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.V);    // ANDing signed 7th bit should be true

    /*
     * Test Overflowing Accumulator Sets C-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.X = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_X;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x9B;                     // Next PC addr contains value to be added to Accum
    memory[(0x9B + cpu.X)] = 128;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.C);    // ANDing signed 7th bit should be true

    /*
     * Test Accumulator with Value = 0 Sets Z-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.X = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_X;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x9B;                     // Next PC addr contains value to be added to Accum
    memory[(0x9B + cpu.X)] =0;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.Z);    // ANDing signed 7th bit should be true

    /*
     * Test Accumulator with Value < 0 Sets N-flag (2s-Complement)
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.X = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_X;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x9B;                     // Next PC addr contains value to be added to Accum
    memory[(0x9B + cpu.X)] = 128;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.N);    // ANDing signed 7th bit should be true
}

TEST(Assm_Instr_Tests, ADC_INDR_Y)
{
    /// Add Contents of current PC to Accumulator with Carry (Indirect,Y)

    /*
     * Test Adding Value to Accumulator Works correctly
     */
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 5;             // # Cycles ADC_IM takes

    cpu.A = 0;                                  // Zero Accumulator
    cpu.Y = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_INDR_Y;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x9B;                  // Next PC addr contains value to be added to Accum
    memory[0x9B] = 5;
    memory[(5 + cpu.Y)] = 125;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.A, 125);

    /*
     * Test Overflowing Accumulator Set V-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.Y = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_Y;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x9B;                     // Next PC addr contains value to be added to Accum
    memory[(0x9B + cpu.Y)] = 128;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.V);    // ANDing signed 7th bit should be true

    /*
     * Test Overflowing Accumulator Sets C-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.Y = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_Y;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x9B;                     // Next PC addr contains value to be added to Accum
    memory[(0x9B + cpu.Y)] = 128;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.C);    // ANDing signed 7th bit should be true

    /*
     * Test Accumulator with Value = 0 Sets Z-flag
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.Y = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_Y;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x9B;                     // Next PC addr contains value to be added to Accum
    memory[(0x9B + cpu.Y)] =0;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.Z);    // ANDing signed 7th bit should be true

    /*
     * Test Accumulator with Value < 0 Sets N-flag (2s-Complement)
     */
    /// Given:
    cpu.Reset(memory);  // Reset Memory to ALL zeros
    cpu.PC = 0x64;      // Set PC to address 0x64

    cpu.A = 0;                                  // Zero Accumulator
    cpu.Y = 50;                                 // Set X reg to an offset of 50
    memory[cpu.PC] = cpu.INS_ADC_ABS_Y;                    // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x9B;                     // Next PC addr contains value to be added to Accum
    memory[(0x9B + cpu.Y)] = 128;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_TRUE(cpu.N);    // ANDing signed 7th bit should be true
}

/*
 * AND
 */
TEST(Assm_Instr_Tests, AND_Accumulator)
{
    /// AND (Accumulator)

    /*
     * Test AND
     */
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 2;             // # Cycles ADC_IM takes

    cpu.A = 111;                                  // Zero Accumulator
    memory[cpu.PC] = cpu.INS_AND_ACCUM;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0b01000000;                  // Next PC addr contains value to be added to Accum

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.A, 0b01000000);
}

TEST(Assm_Instr_Tests, AND_Zero_Page)
{
    /// AND (Zero_Page)

    /*
     * Test AND
     */
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 3;             // # Cycles ADC_IM takes

    cpu.A = 111;                                  // Zero Accumulator
    memory[cpu.PC] = cpu.INS_AND_ZP;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x40;                  // Next PC addr contains value to be added to Accum
    memory[0x40] = 64;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.A, 0b01000000);
}

TEST(Assm_Instr_Tests, AND_Zero_Page_X)
{
    /// AND (Zero_Page,X)

    /*
     * Test AND
     */
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 4;             // # Cycles ADC_IM takes

    cpu.A = 111;
    cpu.X = 10;
    memory[cpu.PC] = cpu.INS_AND_ZP_X;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x40;                  // Next PC addr contains value to be added to Accum
    memory[(0x40 + cpu.X)] = 64;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.A, 0b01000000);
}

TEST(Assm_Instr_Tests, AND_Absolute)
{
    /// AND (ABS)

    /*
     * Test AND
     */
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 4;             // # Cycles ADC_IM takes

    cpu.A = 111;
    memory[cpu.PC] = cpu.INS_AND_ABS;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xD0;                  // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] = 0x07;
    memory[0x07D0] = 64;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.A, 0b01000000);
}

TEST(Assm_Instr_Tests, AND_Absolute_X)
{
    /// AND (ABS,X)

    /*
     * Test AND
     */
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 4;             // # Cycles ADC_IM takes

    cpu.A = 111;
    cpu.X = 10;
    memory[cpu.PC] = cpu.INS_AND_ABS_X;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xD0;                  // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] = 0x07;
    memory[(0x07D0 + cpu.X)] = 64;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.A, 0b01000000);
}

TEST(Assm_Instr_Tests, AND_Asbolute_Y)
{
    /// AND (ABS,Y)

    /*
     * Test AND
     */
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 4;             // # Cycles ADC_IM takes

    cpu.A = 111;
    cpu.Y = 10;
    memory[cpu.PC] = cpu.INS_AND_ABS_Y;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0xD0;                  // Next PC addr contains value to be added to Accum
    memory[cpu.PC + 2] = 0x07;
    memory[(0x07D0 + cpu.Y)] = 64;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.A, 0b01000000);
}

TEST(Assm_Instr_Tests, AND_Indirect_X)
{
    /// AND (Indirect,X)

    /*
     * Test AND
     */
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 6;             // # Cycles ADC_IM takes

    cpu.A = 111;
    cpu.X = 10;
    memory[cpu.PC] = cpu.INS_AND_INDR_X;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 50;                    // Next PC addr contains value to be added to Accum
    memory[(50 + cpu.X)] = 64;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.A, 0b01000000);
}

TEST(Assm_Instr_Tests, AND_Indirect_Y)
{
    /// AND (Indirect,Y)

    /*
     * Test AND
     */
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 5;             // # Cycles ADC_IM takes

    cpu.A = 111;
    cpu.Y = 10;
    memory[cpu.PC] = cpu.INS_AND_INDR_Y;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 50;                    // Next PC addr contains value to be added to Accum
    memory[50] = 0x9b;
    memory[(0x9b + cpu.Y)] = 64;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.A, 0b01000000);
}

/*
 * ASL - Arithmetic Shift Left
 */
TEST(Assm_Instr_Tests, ASL_Accumulator)
{
    /// ASL (Accumulator)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 2;             // # Cycles ADC_IM takes

    cpu.A = 25;
    memory[cpu.PC] = cpu.INS_ASL_ACC;           // Set Program Counter to ADC_IM hex

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.A, (25 << 1));
}

TEST(Assm_Instr_Tests, ASL_Zero_Page)
{
    /// ASL (ZeroPage)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 5;             // # Cycles ADC_IM takes

    memory[cpu.PC] = cpu.INS_ASL_ZP;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 121;
    memory[121] = 200;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(memory[121], static_cast<uint8_t>(200 << 1));
    EXPECT_EQ(cpu.C, 1);
}

TEST(Assm_Instr_Tests, ASL_Zero_Page_X)
{
    /// ASL (ZeroPage, X)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 6;             // # Cycles ADC_IM takes

    cpu.X = 10;
    memory[cpu.PC] = cpu.INS_ASL_ZP_X;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 121;
    memory[(121 + cpu.X)] = 200;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(memory[121], static_cast<uint8_t>(200 << 1));
    EXPECT_EQ(cpu.C, 1);
}

TEST(Assm_Instr_Tests, ASL_Asbolute)
{
    /// ASL (ABS)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 6;             // # Cycles ADC_IM takes

    cpu.X = 10;
    memory[cpu.PC] = cpu.INS_ASL_ABS;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x2B;
    memory[cpu.PC + 2] = 0x06;
    memory[1579] = 200;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(memory[1579], static_cast<uint8_t>(200 << 1));
    EXPECT_EQ(cpu.C, 1);
}

TEST(Assm_Instr_Tests, ASL_Asbolute_X)
{
    /// ASL (ABS, X)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint32_t num_cycles = 7;             // # Cycles ADC_IM takes

    cpu.X = 10;
    memory[cpu.PC] = cpu.INS_ASL_ABS_X;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x2B;
    memory[cpu.PC + 2] = 0x06;
    memory[(1579 + cpu.X)] = 200;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(memory[1579], static_cast<uint8_t>(200 << 1));
    EXPECT_EQ(cpu.C, 1);
}

/*
 * Branch if Carry Clear (BCC)
 */
TEST(Assm_Instr_Tests, BCC_Relative)
{
    /// BCC (Relative)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint16_t pc_orig = cpu.PC;
    uint16_t pc_p_1 = cpu.PC + 1;
    uint32_t num_cycles = 2;             // # Cycles ADC_IM takes

    cpu.C = 0;
    memory[cpu.PC] = cpu.INS_BCC_REL;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 75;
    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.PC, (pc_p_1 + 75));

    cpu.C = 1;
    cpu.PC = 0x64;                  // Set PC to address 0x64
    memory[cpu.PC] = cpu.INS_BCC_REL;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 75;
    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ((1 + pc_orig), cpu.PC);

}

/*
 * BCS - Branch if Carry Set
 */
TEST(Assm_Instr_Tests, BCS_Relative)
{
    /// BCS (Relative)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint16_t pc_orig = cpu.PC;
    uint16_t pc_p_1 = cpu.PC + 1;
    uint32_t num_cycles = 2;             // # Cycles ADC_IM takes

    cpu.C = 1;
    memory[cpu.PC] = cpu.INS_BCS_REL;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 75;
    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.PC, (pc_p_1 + 75));

    cpu.C = 0;
    cpu.PC = 0x64;                  // Set PC to address 0x64
    memory[cpu.PC] = cpu.INS_BCS_REL;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 75;
    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ((1 + pc_orig), cpu.PC);
}

/*
 * BEQ - Branch if Equal
 */
TEST(Assm_Instr_Tests, BEQ_Relative)
{
    /// BEQ (Relative)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint16_t pc_orig = cpu.PC;
    uint16_t pc_p_1 = cpu.PC + 1;
    uint32_t num_cycles = 2;             // # Cycles ADC_IM takes

    cpu.Z = 1;
    memory[cpu.PC] = cpu.INS_BEQ_REL;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 75;
    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.PC, (pc_p_1 + 75));

    cpu.Z = 0;
    cpu.PC = 0x64;                  // Set PC to address 0x64
    memory[cpu.PC] = cpu.INS_BEQ_REL;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 75;
    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ((1 + pc_orig), cpu.PC);
}

///*
// * Bit Test (BIT)
// */
//TEST(Assm_Instr_Tests, BIT_Zero_Page)
//{
//}
//
//TEST(Assm_Instr_Tests, BIT_Absolute)
//{
//}
//
/*
 * BMI - Branch if Minus
 */
TEST(Assm_Instr_Tests, BMI_Relative)
{
    /// BMI (Relative)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint16_t pc_orig = cpu.PC;
    uint16_t pc_p_1 = cpu.PC + 1;
    uint32_t num_cycles = 2;             // # Cycles ADC_IM takes

    cpu.N = 1;
    memory[cpu.PC] = cpu.INS_BMI_REL;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 75;
    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.PC, (pc_p_1 + 75));

    cpu.N = 0;
    cpu.PC = 0x64;                  // Set PC to address 0x64
    memory[cpu.PC] = cpu.INS_BMI_REL;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 75;
    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ((1 + pc_orig), cpu.PC);
}

/*
 * BNE Branch if Not Equal
 */
TEST(Assm_Instr_Tests, BNE_Relative)
{
    /// BNE (Relative)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint16_t pc_orig = cpu.PC;
    uint16_t pc_p_1 = cpu.PC + 1;
    uint32_t num_cycles = 2;             // # Cycles ADC_IM takes

    cpu.Z = 0;
    memory[cpu.PC] = cpu.INS_BNE_REL;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 75;
    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.PC, (pc_p_1 + 75));

    cpu.Z = 1;
    cpu.PC = 0x64;                  // Set PC to address 0x64
    memory[cpu.PC] = cpu.INS_BNE_REL;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 75;
    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ((1 + pc_orig), cpu.PC);
}

/*
 * Branch if Positive
 */
TEST(Assm_Instr_Tests, BPL_Relative)
{
    /// BPL (Relative)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint16_t pc_orig = cpu.PC;
    uint16_t pc_p_1 = cpu.PC + 1;
    uint32_t num_cycles = 2;             // # Cycles ADC_IM takes

    cpu.N = 0;
    memory[cpu.PC] = cpu.INS_BPL_REL;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 75;
    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.PC, (pc_p_1 + 75));

    cpu.N = 1;
    cpu.PC = 0x64;                  // Set PC to address 0x64
    memory[cpu.PC] = cpu.INS_BPL_REL;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 75;
    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ((1 + pc_orig), cpu.PC);
}

///*
// * BRK - Force Interrupt
// */
//TEST(Assm_Instr_Tests, BRK_Implied)
//{
//}
//
/*
 * BVC - Branch if Overflow Clear
 */
TEST(Assm_Instr_Tests, BVC_Relative)
{
    /// BVC (Relative)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint16_t pc_orig = cpu.PC;
    uint16_t pc_p_1 = cpu.PC + 1;
    uint32_t num_cycles = 2;             // # Cycles ADC_IM takes

    cpu.V = 0;
    memory[cpu.PC] = cpu.INS_BVC_REL;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 75;
    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.PC, (pc_p_1 + 75));

    cpu.V = 1;
    cpu.PC = 0x64;                  // Set PC to address 0x64
    memory[cpu.PC] = cpu.INS_BVC_REL;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 75;
    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ((1 + pc_orig), cpu.PC);
}

/*
 * BVS - Branch if Overflow Set
 */
TEST(Assm_Instr_Tests, BVS_Relative)
{
    /// BVC (Relative)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    uint16_t pc_orig = cpu.PC;
    uint16_t pc_p_1 = cpu.PC + 1;
    uint32_t num_cycles = 2;             // # Cycles ADC_IM takes

    cpu.V = 1;
    memory[cpu.PC] = cpu.INS_BVS_REL;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 75;
    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.PC, (pc_p_1 + 75));

    cpu.V = 0;
    cpu.PC = 0x64;                  // Set PC to address 0x64
    memory[cpu.PC] = cpu.INS_BVS_REL;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 75;
    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ((1 + pc_orig), cpu.PC);
}

/*
 * CLC - Clear Carry Flag
 */
TEST(Assm_Instr_Tests, CLC_Immediate)
{
    /// CLC (Relative)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64

    uint32_t num_cycles = 2;
    cpu.C = 1;
    memory[cpu.PC] = cpu.INS_CLC_IM;           // Set Program Counter to ADC_IM hex

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.C, 0);
}

/*
 * CLD - Clear Decimal Mode
 */
TEST(Assm_Instr_Tests, CLD_Immediate)
{
    /// CLD (Relative)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64

    uint32_t num_cycles = 2;
    cpu.D = 1;
    memory[cpu.PC] = cpu.INS_CLD_IM;           // Set Program Counter to ADC_IM hex

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.D, 0);
}

/*
 * CLI - Clear Interrupt Disable
 */
TEST(Assm_Instr_Tests, CLI_Implied)
{
    /// CLI (Relative)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64

    uint32_t num_cycles = 2;
    cpu.I = 1;
    memory[cpu.PC] = cpu.INS_CLI_IM;           // Set Program Counter to ADC_IM hex

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.I, 0);
}

/*
 * CLV - Clear Overflow Flag
 */
TEST(Assm_Instr_Tests, CLV_Immediate)
{
    /// CLV (Relative)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64

    uint32_t num_cycles = 2;
    cpu.V = 1;
    memory[cpu.PC] = cpu.INS_CLV_IM;           // Set Program Counter to ADC_IM hex

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.V, 0);
}

/*
 * CMP - Compare
 */
TEST(Assm_Instr_Tests, CMP_Immediate)
{
    /// CMP (Immediate)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64

    uint32_t num_cycles = 2;
    cpu.A = 189;
    memory[cpu.PC] = cpu.INS_CMP_IM;           // Set Program Counter to ADC_IM hex

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    //    (A & 0b10000000) ? N = 1 : N = 0;
    EXPECT_EQ(cpu.N, 1);

    /// Given:
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64

    cpu.A = 189;
    memory[cpu.PC] = cpu.INS_CMP_IM;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 156;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.C, 1);

    /// Given:
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    cpu.A = 145;
    memory[cpu.PC] = cpu.INS_CMP_IM;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 145;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.Z, 1);
}

TEST(Assm_Instr_Tests, CMP_Zero_Page)
{
    /// CMP (ZeroPage)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64

    uint32_t num_cycles = 3;
    cpu.A = 189;
    memory[cpu.PC] = cpu.INS_CMP_ZP;           // Set Program Counter to ADC_IM hex

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    //    (A & 0b10000000) ? N = 1 : N = 0;
    EXPECT_EQ(cpu.N, 1);

    /// Given:
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64

    cpu.A = 189;
    memory[cpu.PC] = cpu.INS_CMP_ZP;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 156;
    memory[156] = 125;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.C, 1);

    /// Given:
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    cpu.A = 145;
    memory[cpu.PC] = cpu.INS_CMP_ZP;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 155;
    memory[155] = 145;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.Z, 1);
}

TEST(Assm_Instr_Tests, CMP_Zero_Page_X)
{
    /// CMP (ZeroPage,X)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    cpu.X = 10;

    uint32_t num_cycles = 4;
    cpu.A = 189;
    memory[cpu.PC] = cpu.INS_CMP_ZP_X;           // Set Program Counter to ADC_IM hex

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    //    (A & 0b10000000) ? N = 1 : N = 0;
    EXPECT_EQ(cpu.N, 1);

    /// Given:
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64

    cpu.A = 189;
    memory[cpu.PC] = cpu.INS_CMP_ZP_X;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 156;
    memory[156 + cpu.X] = 125;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.C, 1);

    /// Given:
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    cpu.A = 145;
    memory[cpu.PC] = cpu.INS_CMP_ZP_X;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 155;
    memory[155 + cpu.X] = 145;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.Z, 1);
}

TEST(Assm_Instr_Tests, CMP_Absolute)
{
    /// CMP (Abs)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64

    uint32_t num_cycles = 4;
    cpu.A = 189;
    memory[cpu.PC] = cpu.INS_CMP_ABS;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x1F;
    memory[cpu.PC + 2] = 0x06;
    memory[0x061f] = 214;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    //    (A & 0b10000000) ? N = 1 : N = 0;
    EXPECT_EQ(cpu.N, 1);

    /// Given:
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64

    cpu.A = 189;
    memory[cpu.PC] = cpu.INS_CMP_ABS;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x1F;
    memory[cpu.PC + 2] = 0x06;
    memory[0x061f] = 111;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.C, 1);

    /// Given:
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    cpu.A = 145;
    memory[cpu.PC] = cpu.INS_CMP_ABS;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x1F;
    memory[cpu.PC + 2] = 0x06;
    memory[0x061f] = 145;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.Z, 1);
}

TEST(Assm_Instr_Tests, CMP_Absolute_X)
{
    /// CMP (Abs, X)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    cpu.X = 10;

    uint32_t num_cycles = 4;
    cpu.A = 189;
    memory[cpu.PC] = cpu.INS_CMP_ABS_X;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x1F;
    memory[cpu.PC + 2] = 0x06;
    memory[0x061f + cpu.X] = 214;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    //    (A & 0b10000000) ? N = 1 : N = 0;
    EXPECT_EQ(cpu.N, 1);

    /// Given:
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64

    cpu.A = 189;
    memory[cpu.PC] = cpu.INS_CMP_ABS_X;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x1F;
    memory[cpu.PC + 2] = 0x06;
    memory[0x061f + cpu.X] = 111;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.C, 1);

    /// Given:
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    cpu.A = 145;
    memory[cpu.PC] = cpu.INS_CMP_ABS_X;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x1F;
    memory[cpu.PC + 2] = 0x06;
    memory[0x061f + cpu.X] = 145;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.Z, 1);
}

TEST(Assm_Instr_Tests, CMP_Absolute_Y)
{
    /// CMP (Abs, Y)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    cpu.Y = 10;

    uint32_t num_cycles = 4;
    cpu.A = 189;
    memory[cpu.PC] = cpu.INS_CMP_ABS_Y;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x1F;
    memory[cpu.PC + 2] = 0x06;
    memory[0x061f] = 214 + cpu.Y;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    //    (A & 0b10000000) ? N = 1 : N = 0;
    EXPECT_EQ(cpu.N, 1);

    /// Given:
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64

    cpu.A = 189;
    memory[cpu.PC] = cpu.INS_CMP_ABS_Y;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x1F;
    memory[cpu.PC + 2] = 0x06;
    memory[0x061f] = 111 + cpu.Y;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.C, 1);

    /// Given:
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    cpu.A = 145;
    memory[cpu.PC] = cpu.INS_CMP_ABS_X;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 0x1F;
    memory[cpu.PC + 2] = 0x06;
    memory[0x061f] = 145 + cpu.Y;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.Z, 1);
}

TEST(Assm_Instr_Tests, CMP_Indirect_X)
{
    /// CMP (Indirect, X)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    cpu.X = 10;

    uint32_t num_cycles = 6;
    cpu.A = 189;
    memory[cpu.PC] = cpu.INS_CMP_INDR_X;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 105;

    memory[105 + cpu.X] = 205;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    //    (A & 0b10000000) ? N = 1 : N = 0;
    EXPECT_EQ(cpu.N, 1);

    /// Given:
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64

    cpu.A = 189;
    memory[cpu.PC] = cpu.INS_CMP_INDR_X;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 105;
    memory[105 + cpu.X] = 111;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.C, 1);

    /// Given:
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    cpu.A = 145;
    memory[cpu.PC] = cpu.INS_CMP_INDR_X;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 105;
    memory[105 + cpu.X] = 145;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.Z, 1);
}

TEST(Assm_Instr_Tests, CMP_Indirect_Y)
{
    /// CMP (Indirect, Y)
    /// Given:
    CPU cpu;                        // CPU initialized
    Mem memory;                     // Memory Initialized
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    cpu.Y = 10;

    uint32_t num_cycles = 5;
    cpu.A = 189;
    memory[cpu.PC] = cpu.INS_CMP_INDR_Y;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 105;

    memory[105] = 205 + cpu.Y;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    //    (A & 0b10000000) ? N = 1 : N = 0;
    EXPECT_EQ(cpu.N, 1);

    /// Given:
    cpu.Y = 10;
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64

    cpu.A = 189;
    memory[cpu.PC] = cpu.INS_CMP_INDR_Y;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 105;
    memory[105] = 111 + cpu.Y;

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.C, 1);

    /// Given:
    cpu.Reset(memory);              // Reset Memory to ALL zeros
    cpu.PC = 0x64;                  // Set PC to address 0x64
    cpu.A = 145;
    cpu.Y = 10;
    memory[cpu.PC] = cpu.INS_CMP_INDR_Y;           // Set Program Counter to ADC_IM hex
    memory[cpu.PC + 1] = 105;
    memory[105] = 79;
    memory[79] = (135 + cpu.Y);

    /// When:
    cpu.Execute(memory, num_cycles);           // Execute Instruction

    /// Then:
    EXPECT_EQ(cpu.Z, 1);
}

/*
 * CPX - Compare X Register
 */
TEST(Assm_Instr_Tests, CPX_Immediate)
{
}

TEST(Assm_Instr_Tests, CPX_Zero_page)
{
}

TEST(Assm_Instr_Tests, CPX_Absolute)
{
}

/*
 * CPY - Compare Y Register
 */
TEST(Assm_Instr_Tests, CPY_Immediate)
{
}

TEST(Assm_Instr_Tests, CPY_Zero_Page)
{
}

TEST(Assm_Instr_Tests, CPY_Absolute)
{
}

///*
// * DEC - Decrement Memory
// */
//TEST(Assm_Instr_Tests, DEC_Zero_Page)
//{
//}
//
//TEST(Assm_Instr_Tests, DEC_Zero_Page_X)
//{
//}
//
//TEST(Assm_Instr_Tests, DEC_Absolute)
//{
//}
//
//TEST(Assm_Instr_Tests, DEC_Absolute_X)
//{
//}
//
///*
// * DEX - Decrement X Register
// */
//
//TEST(Assm_Instr_Tests, DEX_Implied)
//{
//}
//
///*
// * DEY - Decrement Y Register
// */
//TEST(Assm_Instr_Tests, DEY_Implied)
//{
//}
//
///*
// * EOR - Exclusive OR
// */
//TEST(Assm_Instr_Tests, EOR_Immediate)
//{
//}
//
//TEST(Assm_Instr_Tests, EOR_Zero_Page)
//{
//}
//
//TEST(Assm_Instr_Tests, EOR_Zero_Page_X)
//{
//}
//
//TEST(Assm_Instr_Tests, EOR_Absolute)
//{
//}
//
//TEST(Assm_Instr_Tests, EOR_Absolute_X)
//{
//}
//
//TEST(Assm_Instr_Tests, EOR_Absolute_Y)
//{
//}
//
//TEST(Assm_Instr_Tests, EOR_Indirect_X)
//{
//}
//
//TEST(Assm_Instr_Tests, EOR_Indirect_Y)
//{
//}
//
///*
// * INC - Increment Memory
// */
//
//TEST(Assm_Instr_Tests, INC_Zero_Page)
//{
//}
//
//TEST(Assm_Instr_Tests, INC_Zero_Page_X)
//{
//}
//
//TEST(Assm_Instr_Tests, INC_Absolute)
//{
//}
//
//TEST(Assm_Instr_Tests, INC_Absolute_X)
//{
//}
//
//
///*
// * INX - Increment X Register
// */
//TEST(Assm_Instr_Tests, INX_Implied)
//{
//}
//
///*
// * INY - Increment Y Register
// */
//TEST(Assm_Instr_Tests, INY_Implied)
//{
//}
//
///*
// * JMP - Jump
// */
//TEST(Assm_Instr_Tests, JMP_Absolute)
//{
//}
//
//TEST(Assm_Instr_Tests, JMP_Indirect)
//{
//}
//
///*
// * JSR - Jump to Subroutine
// */
//TEST(Assm_Instr_Tests, JSR_Absolute)
//{
//}
//
//
///*
// * LDA - Load Accumulator
// */
//
//TEST(Assm_Instr_Tests, LDA_Immediate)
//{
//}
//
//TEST(Assm_Instr_Tests, LDA_Zero_Page)
//{
//}
//
//TEST(Assm_Instr_Tests, LDA_Zero_Page_X)
//{
//}
//
//TEST(Assm_Instr_Tests, LDA_Absolute)
//{
//}
//
//TEST(Assm_Instr_Tests, LDA_Absolute_X)
//{
//}
//
//TEST(Assm_Instr_Tests, LDA_Absolute_Y)
//{
//}
//
//TEST(Assm_Instr_Tests, LDA_Indirect_X)
//{
//}
//
//TEST(Assm_Instr_Tests, LDA_Indirect_Y)
//{
//}
//
///*
// * LDX - Load X Register
// */
//
//TEST(Assm_Instr_Tests, LDX_Immediate)
//{
//}
//
//TEST(Assm_Instr_Tests, LDX_Zero_Page)
//{
//}
//
//TEST(Assm_Instr_Tests, LDX_Zero_Page_X)
//{
//}
//
//TEST(Assm_Instr_Tests, LDX_Absolute)
//{
//}
//
//TEST(Assm_Instr_Tests, LDX_Absolute_Y)
//{
//}
//
///*
// * LDY - Load Y Register
// */
//TEST(Assm_Instr_Tests, LDY_Immediate)
//{
//}
//TEST(Assm_Instr_Tests, LDY_Zero_Page)
//{
//}
//
//TEST(Assm_Instr_Tests, LDY_Zero_Page_X)
//{
//}
//
//TEST(Assm_Instr_Tests, LDY_Absolute)
//{
//}
//
//TEST(Assm_Instr_Tests, LDY_Absolute_X)
//{
//}
//
//
///*
// * LSR - Logical Shift Right
// */
//TEST(Assm_Instr_Tests, LSR_Accumator)
//{
//}
//
//TEST(Assm_Instr_Tests, LSR_Zero_Page)
//{
//}
//
//TEST(Assm_Instr_Tests, LSR_Zero_Page_X)
//{
//}
//
//TEST(Assm_Instr_Tests, LSR_Absolute)
//{
//}
//
//TEST(Assm_Instr_Tests, LSR_Absolute_X)
//{
//}
//
///*
// * NOP - No Operation
// */
//TEST(Assm_Instr_Tests, NOP_Implied)
//{
//}
//
///*
// * ORA - Logical Inclusive OR
// */
//TEST(Assm_Instr_Tests, ORA_Immediate)
//{
//}
//
//TEST(Assm_Instr_Tests, ORA_Zero_Page)
//{
//}
//
//TEST(Assm_Instr_Tests, ORA_Zero_Page_X)
//{
//}
//
//TEST(Assm_Instr_Tests, ORA_Absolute)
//{
//}
//
//TEST(Assm_Instr_Tests, ORA_Absolute_X)
//{
//}
//
//TEST(Assm_Instr_Tests, ORA_Absolute_Y)
//{
//}
//
//TEST(Assm_Instr_Tests, ORA_Indirect_X)
//{
//}
//
//TEST(Assm_Instr_Tests, ORA_Indirect_Y)
//{
//}
//
///*
// * PHA - Push Accumulator
// */
//TEST(Assm_Instr_Tests, PHA_Implied)
//{
//}
//
///*
// * PHP - Push Processor Status
// */
//TEST(Assm_Instr_Tests, PHP_Implied)
//{
//}
//
///*
// * PLA - Pull Accumulator
// */
//TEST(Assm_Instr_Tests, PLA_Implied)
//{
//}
//
///*
// * PLP - Pull Processor Status
// */
//TEST(Assm_Instr_Tests, PLP_Implied)
//{
//}
//
///*
// * ROL - Rotate Left
// */
//TEST(Assm_Instr_Tests, ROL_Accumulator)
//{
//}
//
//TEST(Assm_Instr_Tests, ROL_Zero_Page)
//{
//}
//
//TEST(Assm_Instr_Tests, ROL_Zero_Page_X)
//{
//}
//
//TEST(Assm_Instr_Tests, ROL_Absolute)
//{
//}
//
//TEST(Assm_Instr_Tests, ROL_Abolute_X)
//{
//}
//
///*
// * ROR - Rotate Right
// */
//TEST(Assm_Instr_Tests, ROR_Accumulator)
//{
//}
//
//TEST(Assm_Instr_Tests, ROR_Zero_Page)
//{
//}
//
//TEST(Assm_Instr_Tests, ROR_Zero_Page_X)
//{
//}
//
//TEST(Assm_Instr_Tests, ROR_Absolute)
//{
//}
//
//TEST(Assm_Instr_Tests, ROR_Abolute_X)
//{
//}
//
///*
// * RTI Return from Interrupt
// */
//TEST(Assm_Instr_Tests, RTI_Implied)
//{
//}
//
///*
// * RTS Return from Subroutine
// */
//TEST(Assm_Instr_Tests, RTS_Implied)
//{
//}
//
///*
// * SBC Subtract with Carry
// */
//TEST(Assm_Instr_Tests, SBC_Immediate)
//{
//}
//
//TEST(Assm_Instr_Tests, SBC_Zero_Page)
//{
//}
//
//TEST(Assm_Instr_Tests, SBC_Zero_Page_X)
//{
//}
//
//TEST(Assm_Instr_Tests, SBC_Absolute)
//{
//}
//
//TEST(Assm_Instr_Tests, SBC_Absolute_X)
//{
//}
//
//TEST(Assm_Instr_Tests, SBC_Absolute_Y)
//{
//}
//
//TEST(Assm_Instr_Tests, SBC_Indirect_X)
//{
//}
//
//TEST(Assm_Instr_Tests, SBC_Indirect_Y)
//{
//}
//
///*
// * SEC - Set Carry Flag
// */
//
//TEST(Assm_Instr_Tests, SEC_Implied)
//{
//}
//
///*
// * SED - Set Decimal Flag
// */
//
//TEST(Assm_Instr_Tests, SED_Implied)
//{
//}
//
///*
// * SEI - Set Interrupt Disable
// */
//
//TEST(Assm_Instr_Tests, SEI_Implied)
//{
//}
//
///*
// * STA - Store Accumulator
// */
//TEST(Assm_Instr_Tests, STA_Zero_Page)
//{
//}
//
//TEST(Assm_Instr_Tests, STA_Zero_Page_X)
//{
//}
//
//TEST(Assm_Instr_Tests, STA_Absolute)
//{
//}
//
//TEST(Assm_Instr_Tests, STA_Absolute_X)
//{
//}
//
//TEST(Assm_Instr_Tests, STA_Absolute_Y)
//{
//}
//
//TEST(Assm_Instr_Tests, STA_Indirect_X)
//{
//}
//
//TEST(Assm_Instr_Tests, STA_Indirect_Y)
//{
//}
//
///*
// * STX - Store X Register
// */
//TEST(Assm_Instr_Tests, STX_Zero_Page)
//{
//}
//
//TEST(Assm_Instr_Tests, STX_Zero_Page_X)
//{
//}
//
//TEST(Assm_Instr_Tests, STX_Absolute)
//{
//}
//
///*
// * STY - Store Y Register
// */
//TEST(Assm_Instr_Tests, STY_Zero_Page)
//{
//}
//
//TEST(Assm_Instr_Tests, STY_Zero_Page_X)
//{
//}
//
//TEST(Assm_Instr_Tests, STY_Absolute)
//{
//}
//
///*
// * TAX - Transfer Accumulator to X
// */
//TEST(Assm_Instr_Tests, TAX_Immediate)
//{
//}
//
///*
// * TAY - Transfer Accumulator to Y
// */
//TEST(Assm_Instr_Tests, TAY_Implied)
//{
//}
//
///*
// * TSX - Transfer Stack Pointer to X
// */
//TEST(Assm_Instr_Tests, TSX_Implied)
//{
//}
//
///*
// * TXA - Transfer X to Accumulator
// */
//TEST(Assm_Instr_Tests, TXA_Implied)
//{
//}
//
///*
// * TXS - Transfer X to Stack Pointer
// */
//TEST(Assm_Instr_Tests, TXS_Implied)
//{
//}
//
///*
// * TYA - Transfer Y to Accumulator
// */
//TEST(Assm_Instr_Tests, TYA_Implied)
//{
//}

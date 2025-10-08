

    #pragma once 

    #include<array>
    #include<cstdint>
    #include<functional>
    #include<iostream>
    #include<optional>
    #include<string>
    #include <unordered_map>

    // Instruction Set

    struct Instruction {
        std::string m_name;
        uint8_t m_opcode;
        size_t m_cycles;
        std::function<void()> m_handler;

        // Constructor
        Instruction()=delete;
        Instruction(std::string name, uint8_t opcode, size_t cycles, std::function<void()> handler)
            : m_name(std::move(name)), m_opcode(opcode), m_cycles(cycles), m_handler(std::move(handler)) {}
    };

    std::array<std::optional<Instruction>, 256> dispatch_table = [] {
        std::array<std::optional<Instruction>, 256> table = {};

        table[109] = Instruction("ADC", 109, 4, handler_lookup["add_with_carry"]);
        table[101] = Instruction("ADC", 101, 3, handler_lookup["add_with_carry"]);
        table[105] = Instruction("ADC", 105, 2, handler_lookup["add_with_carry"]);
        table[125] = Instruction("ADC", 125, 4, handler_lookup["add_with_carry"]);
        table[121] = Instruction("ADC", 121, 4, handler_lookup["add_with_carry"]);
        table[97] = Instruction("ADC", 97, 6, handler_lookup["add_with_carry"]);
        table[113] = Instruction("ADC", 113, 5, handler_lookup["add_with_carry"]);
        table[117] = Instruction("ADC", 117, 4, handler_lookup["add_with_carry"]);
        table[45] = Instruction("AND", 45, 4, handler_lookup["logical_and"]);
        table[5] = Instruction("AND", 5, 3, handler_lookup["logical_and"]);
        table[41] = Instruction("AND", 41, 2, handler_lookup["logical_and"]);
        table[61] = Instruction("AND", 61, 4, handler_lookup["logical_and"]);
        table[57] = Instruction("AND", 57, 4, handler_lookup["logical_and"]);
        table[33] = Instruction("AND", 33, 6, handler_lookup["logical_and"]);
        table[49] = Instruction("AND", 49, 5, handler_lookup["logical_and"]);
        table[53] = Instruction("AND", 53, 4, handler_lookup["logical_and"]);
        table[10] = Instruction("ASL", 10, 2, handler_lookup["arithmetic_shift_left"]);
        table[14] = Instruction("ASL", 14, 6, handler_lookup["arithmetic_shift_left"]);
        table[6] = Instruction("ASL", 6, 5, handler_lookup["arithmetic_shift_left"]);
        table[30] = Instruction("ASL", 30, 7, handler_lookup["arithmetic_shift_left"]);
        table[22] = Instruction("ASL", 22, 6, handler_lookup["arithmetic_shift_left"]);
        table[144] = Instruction("BCC", 144, 2, handler_lookup["branch_on_carry_clear"]);
        table[176] = Instruction("BCS", 176, 2, handler_lookup["branch_on_carry_set"]);
        table[240] = Instruction("BEQ", 240, 2, handler_lookup["branch_if_equal_to_zero"]);
        table[44] = Instruction("BIT", 44, 4, handler_lookup["cmpr_mem_bits_with_accumulator"]);
        table[36] = Instruction("BIT", 36, 3, handler_lookup["cmpr_mem_bits_with_accumulator"]);
        table[48] = Instruction("BMI", 48, 2, handler_lookup["branch_on_minus"]);
        table[208] = Instruction("BNE", 208, 2, handler_lookup["branch_on_not_equal_to_zero"]);
        table[16] = Instruction("BPL", 16, 2, handler_lookup["branch_on_plus"]);
        table[0] = Instruction("BRK", 0, 7, handler_lookup["break"]);
        table[80] = Instruction("BVC", 80, 2, handler_lookup["branch_on_overflow_clear"]);
        table[112] = Instruction("BVS", 112, 2, handler_lookup["branch_on_overflow_set"]);
        table[24] = Instruction("CLC", 24, 2, handler_lookup["clear_carry"]);
        table[216] = Instruction("CLD", 216, 2, handler_lookup["clear_decimal_flag"]);
        table[88] = Instruction("CLI", 88, 2, handler_lookup["clear_interrupt_mask"]);
        table[184] = Instruction("CLV", 184, 2, handler_lookup["clear_overflow_flag"]);
        table[205] = Instruction("CMP", 205, 4, handler_lookup["compare_to_accumulator"]);
        table[197] = Instruction("CMP", 197, 3, handler_lookup["compare_to_accumulator"]);
        table[201] = Instruction("CMP", 201, 2, handler_lookup["compare_to_accumulator"]);
        table[221] = Instruction("CMP", 221, 4, handler_lookup["compare_to_accumulator"]);
        table[217] = Instruction("CMP", 217, 2, handler_lookup["compare_to_accumulator"]);
        table[193] = Instruction("CMP", 193, 6, handler_lookup["compare_to_accumulator"]);
        table[209] = Instruction("CMP", 209, 5, handler_lookup["compare_to_accumulator"]);
        table[213] = Instruction("CMP", 213, 4, handler_lookup["compare_to_accumulator"]);
        table[236] = Instruction("CPX", 236, 4, handler_lookup["compare_to_register_x"]);
        table[228] = Instruction("CPX", 228, 3, handler_lookup["compare_to_register_x"]);
        table[224] = Instruction("CPX", 224, 2, handler_lookup["compare_to_register_x"]);
        table[204] = Instruction("CPY", 204, 4, handler_lookup["compare_to_register_y"]);
        table[196] = Instruction("CPY", 196, 3, handler_lookup["compare_to_register_y"]);
        table[192] = Instruction("CPXY", 192, 2, handler_lookup["compare_to_register_y"]);
        table[206] = Instruction("DEC", 206, 6, handler_lookup["decrement"]);
        table[198] = Instruction("DEC", 198, 5, handler_lookup["decrement"]);
        table[222] = Instruction("DEC", 222, 7, handler_lookup["decrement"]);
        table[214] = Instruction("DEC", 214, 6, handler_lookup["decrement"]);
        table[202] = Instruction("DEX", 202, 2, handler_lookup["decrement_x"]);
        table[136] = Instruction("DEY", 136, 2, handler_lookup["decrement_y"]);
        table[77] = Instruction("EOR", 77, 4, handler_lookup["exclusive_or_with_accumulator"]);
        table[69] = Instruction("EOR", 69, 3, handler_lookup["exclusive_or_with_accumulator"]);
        table[73] = Instruction("EOR", 73, 2, handler_lookup["exclusive_or_with_accumulator"]);
        table[93] = Instruction("EOR", 93, 4, handler_lookup["exclusive_or_with_accumulator"]);
        table[89] = Instruction("EOR", 89, 4, handler_lookup["exclusive_or_with_accumulator"]);
        table[65] = Instruction("EOR", 65, 6, handler_lookup["exclusive_or_with_accumulator"]);
        table[81] = Instruction("EOR", 81, 5, handler_lookup["exclusive_or_with_accumulator"]);
        table[85] = Instruction("EOR", 85, 4, handler_lookup["exclusive_or_with_accumulator"]);
        table[238] = Instruction("INC", 238, 6, handler_lookup["increment_memory"]);
        table[230] = Instruction("INC", 230, 5, handler_lookup["increment_memory"]);
        table[254] = Instruction("INC", 254, 7, handler_lookup["increment_memory"]);
        table[246] = Instruction("INC", 246, 6, handler_lookup["increment_memory"]);
        table[232] = Instruction("INX", 232, 2, handler_lookup["increment_x"]);
        table[200] = Instruction("INY", 200, 2, handler_lookup["increment_y"]);
        table[76] = Instruction("JMP", 76, 3, handler_lookup["jump_to_address"]);
        table[108] = Instruction("JMP", 108, 5, handler_lookup["jump_to_address"]);
        table[32] = Instruction("JSR", 32, 6, handler_lookup["jump_to_subroutine"]);
        table[173] = Instruction("LDA", 173, 4, handler_lookup["load_accumulator"]);
        table[165] = Instruction("LDA", 165, 3, handler_lookup["load_accumulator"]);
        table[169] = Instruction("LDA", 169, 2, handler_lookup["load_accumulator"]);
        table[189] = Instruction("LDA", 189, 4, handler_lookup["load_accumulator"]);
        table[185] = Instruction("LDA", 185, 4, handler_lookup["load_accumulator"]);
        table[161] = Instruction("LDA", 161, 6, handler_lookup["load_accumulator"]);
        table[177] = Instruction("LDA", 177, 5, handler_lookup["load_accumulator"]);
        table[181] = Instruction("LDA", 181, 4, handler_lookup["load_accumulator"]);
        table[174] = Instruction("LDX", 174, 4, handler_lookup["load_register_x"]);
        table[166] = Instruction("LDX", 166, 3, handler_lookup["load_register_x"]);
        table[162] = Instruction("LDX", 162, 2, handler_lookup["load_register_x"]);
        table[190] = Instruction("LDX", 190, 4, handler_lookup["load_register_x"]);
        table[182] = Instruction("LDX", 182, 4, handler_lookup["load_register_x"]);
        table[172] = Instruction("LDY", 172, 4, handler_lookup["load_register_y"]);
        table[164] = Instruction("LDY", 164, 3, handler_lookup["load_register_y"]);
        table[160] = Instruction("LDY", 160, 2, handler_lookup["load_register_y"]);
        table[188] = Instruction("LDY", 188, 4, handler_lookup["load_register_y"]);
        table[180] = Instruction("LDY", 180, 4, handler_lookup["load_register_y"]);
        table[74] = Instruction("LSR", 74, 2, handler_lookup["logical_shift_right"]);
        table[78] = Instruction("LSR", 78, 6, handler_lookup["logical_shift_right"]);
        table[70] = Instruction("LSR", 70, 5, handler_lookup["logical_shift_right"]);
        table[94] = Instruction("LSR", 94, 7, handler_lookup["logical_shift_right"]);
        table[86] = Instruction("LSR", 86, 6, handler_lookup["logical_shift_right"]);
        table[234] = Instruction("NOP", 234, 2, handler_lookup["no_operation"]);
        table[13] = Instruction("ORA", 13, 4, handler_lookup["inclusive_or_with_accumulator"]);
        table[5] = Instruction("ORA", 5, 3, handler_lookup["inclusive_or_with_accumulator"]);
        table[9] = Instruction("ORA", 9, 2, handler_lookup["inclusive_or_with_accumulator"]);
        table[29] = Instruction("ORA", 29, 4, handler_lookup["inclusive_or_with_accumulator"]);
        table[25] = Instruction("ORA", 25, 4, handler_lookup["inclusive_or_with_accumulator"]);
        table[1] = Instruction("ORA", 1, 6, handler_lookup["inclusive_or_with_accumulator"]);
        table[17] = Instruction("ORA", 17, 5, handler_lookup["inclusive_or_with_accumulator"]);
        table[21] = Instruction("ORA", 21, 4, handler_lookup["inclusive_or_with_accumulator"]);
        table[72] = Instruction("PHA", 72, 3, handler_lookup["push_accumulator_onto_stack"]);
        table[8] = Instruction("PHP", 8, 3, handler_lookup["push_processor_status_onto_stack"]);
        table[104] = Instruction("PLA", 104, 4, handler_lookup["pull_stack_onto_accumulator"]);
        table[40] = Instruction("PLP", 40, 4, handler_lookup["pull_processor_status_from_stack"]);
        table[42] = Instruction("ROL", 42, 2, handler_lookup["rotate_left_one_bit"]);
        table[46] = Instruction("ROL", 46, 6, handler_lookup["rotate_left_one_bit"]);
        table[38] = Instruction("ROL", 38, 5, handler_lookup["rotate_left_one_bit"]);
        table[62] = Instruction("ROL", 62, 7, handler_lookup["rotate_left_one_bit"]);
        table[54] = Instruction("ROL", 54, 6, handler_lookup["rotate_left_one_bit"]);
        table[106] = Instruction("ROR", 106, 2, handler_lookup["rotate_right_one_bit"]);
        table[110] = Instruction("ROR", 110, 6, handler_lookup["rotate_right_one_bit"]);
        table[102] = Instruction("ROR", 102, 5, handler_lookup["rotate_right_one_bit"]);
        table[126] = Instruction("ROR", 126, 7, handler_lookup["rotate_right_one_bit"]);
        table[118] = Instruction("ROR", 118, 6, handler_lookup["rotate_right_one_bit"]);
        table[64] = Instruction("RTI", 64, 6, handler_lookup["return_from_interrupt"]);
        table[96] = Instruction("RTS", 96, 6, handler_lookup["return_from_subroutine"]);
        table[237] = Instruction("SBC", 237, 4, handler_lookup["subtract_with_carry"]);
        table[229] = Instruction("SBC", 229, 3, handler_lookup["subtract_with_carry"]);
        table[233] = Instruction("SBC", 233, 2, handler_lookup["subtract_with_carry"]);
        table[253] = Instruction("SBC", 253, 4, handler_lookup["subtract_with_carry"]);
        table[249] = Instruction("SBC", 249, 4, handler_lookup["subtract_with_carry"]);
        table[225] = Instruction("SBC", 225, 6, handler_lookup["subtract_with_carry"]);
        table[241] = Instruction("SBC", 241, 5, handler_lookup["subtract_with_carry"]);
        table[245] = Instruction("SBC", 245, 4, handler_lookup["subtract_with_carry"]);
        table[56] = Instruction("SEC", 56, 2, handler_lookup["set_carry"]);
        table[248] = Instruction("SED", 248, 2, handler_lookup["set_decimal_mode"]);
        table[120] = Instruction("SEI", 120, 2, handler_lookup["set_interrupt_disable"]);
        table[141] = Instruction("STA", 141, 4, handler_lookup["store_accumulator_in_memory"]);
        table[133] = Instruction("STA", 133, 3, handler_lookup["store_accumulator_in_memory"]);
        table[157] = Instruction("STA", 157, 5, handler_lookup["store_accumulator_in_memory"]);
        table[153] = Instruction("STA", 153, 5, handler_lookup["store_accumulator_in_memory"]);
        table[129] = Instruction("STA", 129, 6, handler_lookup["store_accumulator_in_memory"]);
        table[145] = Instruction("STA", 145, 6, handler_lookup["store_accumulator_in_memory"]);
        table[149] = Instruction("STA", 149, 4, handler_lookup["store_accumulator_in_memory"]);
        table[142] = Instruction("STX", 142, 4, handler_lookup["store_x_in_memory"]);
        table[134] = Instruction("STX", 134, 3, handler_lookup["store_x_in_memory"]);
        table[150] = Instruction("STX", 150, 4, handler_lookup["store_x_in_memory"]);
        table[140] = Instruction("STY", 140, 4, handler_lookup["store_y_in_memory"]);
        table[132] = Instruction("STY", 132, 3, handler_lookup["store_y_in_memory"]);
        table[148] = Instruction("STY", 148, 4, handler_lookup["store_y_in_memory"]);
        table[170] = Instruction("TAX", 170, 2, handler_lookup["transfer_accumulator_into_x"]);
        table[168] = Instruction("TAY", 168, 2, handler_lookup["transfer_accumulator_into_y"]);
        table[186] = Instruction("TSX", 186, 2, handler_lookup["transfer_s_into_x"]);
        table[138] = Instruction("TXA", 138, 2, handler_lookup["transfer_x_into_accumulator"]);
        table[154] = Instruction("TXS", 154, 2, handler_lookup["transfer_x_into_s"]);
        table[152] = Instruction("TYA", 152, 2, handler_lookup["transfer_y_into_accumulator"]);
        
        return table;
    }();

    
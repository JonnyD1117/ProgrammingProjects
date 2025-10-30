#pragma once

// std
#include <functional>
#include <iostream>
#include <string> 
#include <unordered_map>

void add_with_carry(){ std::cout << "add_with_carry" << std::endl; }

void logical_and(){ std::cout << "logical_and" << std::endl; }

void arithmetic_shift_left(){ std::cout << "arithmetic_shift_left" << std::endl; }

void branch_on_carry_clear(){ std::cout << "branch_on_carry_clear" << std::endl; }

void branch_on_carry_set(){ std::cout << "branch_on_carry_set" << std::endl; }

void branch_if_equal_to_zero(){ std::cout << "branch_if_equal_to_zero" << std::endl; }

void cmpr_mem_bits_with_accumulator(){ std::cout << "cmpr_mem_bits_with_accumulator" << std::endl; }

void branch_on_minus(){ std::cout << "branch_on_minus" << std::endl; }

void branch_on_not_equal_to_zero(){ std::cout << "branch_on_not_equal_to_zero" << std::endl; }

void branch_on_plus(){ std::cout << "branch_on_plus" << std::endl; }

void break_and_interrupt(){ std::cout << "break_and_interrupt" << std::endl; }

void branch_on_overflow_clear(){ std::cout << "branch_on_overflow_clear" << std::endl; }

void branch_on_overflow_set(){ std::cout << "branch_on_overflow_set" << std::endl; }

void clear_carry(){ std::cout << "clear_carry" << std::endl; }

void clear_decimal_flag(){ std::cout << "clear_decimal_flag" << std::endl; }

void clear_interrupt_mask(){ std::cout << "clear_interrupt_mask" << std::endl; }

void clear_overflow_flag(){ std::cout << "clear_overflow_flag" << std::endl; }

void compare_to_accumulator(){ std::cout << "compare_to_accumulator" << std::endl; }

void compare_to_register_x(){ std::cout << "compare_to_register_x" << std::endl; }

void compare_to_register_y(){ std::cout << "compare_to_register_y" << std::endl; }

void decrement(){ std::cout << "decrement" << std::endl; }

void decrement_x(){ std::cout << "decrement_x" << std::endl; }

void decrement_y(){ std::cout << "decrement_y" << std::endl; }

void exclusive_or_with_accumulator(){ std::cout << "exclusive_or_with_accumulator" << std::endl; }

void increment_memory(){ std::cout << "increment_memory" << std::endl; }

void increment_x(){ std::cout << "increment_x" << std::endl; }

void increment_y(){ std::cout << "increment_y" << std::endl; }

void jump_to_address(){ std::cout << "jump_to_address" << std::endl; }

void jump_to_subroutine(){ std::cout << "jump_to_subroutine" << std::endl; }

void load_accumulator(){ std::cout << "load_accumulator" << std::endl; }

void load_register_x(){ std::cout << "load_register_x" << std::endl; }

void load_register_y(){ std::cout << "load_register_y" << std::endl; }

void logical_shift_right(){ std::cout << "logical_shift_right" << std::endl; }

void no_operation(){ std::cout << "no_operation" << std::endl; }

void inclusive_or_with_accumulator(){ std::cout << "inclusive_or_with_accumulator" << std::endl; }

void push_accumulator_onto_stack(){ std::cout << "push_accumulator_onto_stack" << std::endl; }

void push_processor_status_onto_stack(){ std::cout << "push_processor_status_onto_stack" << std::endl; }

void pull_stack_onto_accumulator(){ std::cout << "pull_stack_onto_accumulator" << std::endl; }

void pull_processor_status_from_stack(){ std::cout << "pull_processor_status_from_stack" << std::endl; }

void rotate_left_one_bit(){ std::cout << "rotate_left_one_bit" << std::endl; }

void rotate_right_one_bit(){ std::cout << "rotate_right_one_bit" << std::endl; }

void return_from_interrupt(){ std::cout << "return_from_interrupt" << std::endl; }

void return_from_subroutine(){ std::cout << "return_from_subroutine" << std::endl; }

void subtract_with_carry(){ std::cout << "subtract_with_carry" << std::endl; }

void set_carry(){ std::cout << "set_carry" << std::endl; }

void set_decimal_mode(){ std::cout << "set_decimal_mode" << std::endl; }

void set_interrupt_disable(){ std::cout << "set_interrupt_disable" << std::endl; }

void store_accumulator_in_memory(){ std::cout << "store_accumulator_in_memory" << std::endl; }

void store_x_in_memory(){ std::cout << "store_x_in_memory" << std::endl; }

void store_y_in_memory(){ std::cout << "store_y_in_memory" << std::endl; }

void transfer_accumulator_into_x(){ std::cout << "transfer_accumulator_into_x" << std::endl; }

void transfer_accumulator_into_y(){ std::cout << "transfer_accumulator_into_y" << std::endl; }

void transfer_s_into_x(){ std::cout << "transfer_s_into_x" << std::endl; }

void transfer_x_into_accumulator(){ std::cout << "transfer_x_into_accumulator" << std::endl; }

void transfer_x_into_s(){ std::cout << "transfer_x_into_s" << std::endl; }

void transfer_y_into_accumulator(){ std::cout << "transfer_y_into_accumulator" << std::endl; }

std::unordered_map<std::string,std::function<void()>> handler_lookup 
{
    {"add_with_carry",                   add_with_carry},
    {"logical_and",                      logical_and},
    {"arithmetic_shift_left",            arithmetic_shift_left},
    {"branch_on_carry_clear",            branch_on_carry_clear},
    {"branch_on_carry_set",              branch_on_carry_set},
    {"branch_if_equal_to_zero",          branch_if_equal_to_zero},
    {"cmpr_mem_bits_with_accumulator",   cmpr_mem_bits_with_accumulator},
    {"branch_on_minus",                  branch_on_minus},
    {"branch_on_not_equal_to_zero",      branch_on_not_equal_to_zero},
    {"branch_on_plus",                   branch_on_plus},
    {"break_and_interrupt",              break_and_interrupt},
    {"branch_on_overflow_clear",         branch_on_overflow_clear},
    {"branch_on_overflow_set",           branch_on_overflow_set},
    {"clear_carry",                      clear_carry},
    {"clear_decimal_flag",               clear_decimal_flag},
    {"clear_interrupt_mask",             clear_interrupt_mask},
    {"clear_overflow_flag",              clear_overflow_flag},
    {"compare_to_accumulator",           compare_to_accumulator},
    {"compare_to_register_x",            compare_to_register_x},
    {"compare_to_register_y",            compare_to_register_y},
    {"decrement",                        decrement},
    {"decrement_y",                      decrement_y},
    {"decrement_x",                      decrement_x},
    {"exclusive_or_with_accumulator",    exclusive_or_with_accumulator},
    {"increment_memory",                 increment_memory},
    {"increment_x",                      increment_x},
    {"increment_y",                      increment_y},
    {"jump_to_address",                  jump_to_address},
    {"jump_to_subroutine",               jump_to_subroutine},
    {"load_accumulator",                 load_accumulator},
    {"load_register_x",                  load_register_x},
    {"load_register_y",                  load_register_y},
    {"logical_shift_right",              logical_shift_right},
    {"no_operation",                     no_operation},
    {"inclusive_or_with_accumulator",    inclusive_or_with_accumulator},
    {"push_accumulator_onto_stack",      push_accumulator_onto_stack},
    {"push_processor_status_onto_stack", push_processor_status_onto_stack},
    {"pull_stack_onto_accumulator",      pull_stack_onto_accumulator},
    {"pull_processor_status_from_stack", pull_processor_status_from_stack},
    {"rotate_left_one_bit",              rotate_left_one_bit},
    {"rotate_right_one_bit",             rotate_right_one_bit},
    {"return_from_interrupt",            return_from_interrupt},
    {"return_from_subroutine",           return_from_subroutine},
    {"subtract_with_carry",              subtract_with_carry},
    {"set_carry",                        set_carry},
    {"set_decimal_mode",                 set_decimal_mode},
    {"set_interrupt_disable",            set_interrupt_disable},
    {"store_accumulator_in_memory",      store_accumulator_in_memory},
    {"store_x_in_memory",                store_x_in_memory},
    {"store_y_in_memory",                store_y_in_memory},
    {"transfer_accumulator_into_x",      transfer_accumulator_into_x},
    {"transfer_accumulator_into_y",      transfer_accumulator_into_y},
    {"transfer_s_into_x",                transfer_s_into_x},
    {"transfer_x_into_accumulator",      transfer_x_into_accumulator},
    {"transfer_x_into_s",                transfer_x_into_s},
    {"transfer_y_into_accumulator",      transfer_y_into_accumulator}
}; 
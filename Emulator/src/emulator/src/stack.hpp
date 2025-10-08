/*
----------------------------------------------------------------------------------------
|                           6502 Hardware-Based Stack:                                 |
----------------------------------------------------------------------------------------
The 6502 CPU implements a 256 byte long stack internally managed by cpu hardware.

1) Hardware-Based Stack is "assumed" to use the second page of memory [0x0100 - 0x01FF]
2) At power-up/system-reset the Stack Pointer (SP) will initialize to 0x01FF
3) Stack grows **down** from 0x01FF --> 0x0100
    3.1) Push will decrement SP
    3.2) Pop will increment SP
4) SP will reset from 0x01FF to 0x0100 if Stack Overflow occurs
----------------------------------------------------------------------------------------
*/

#pragma once

#include <cstdint>
#include <cassert>
#include <exception>

namespace MOS6502
{

class StackOverFlowException : public std::exception
{
} inline StackOverFlow;
class StackUnderFlowException : public std::exception
{
} inline StackUnderFlow;

template <typename Memory> 
class Stack
{
  private:
    Memory &memory_; // Reference to system RAM object

    uint32_t end_stack = 0x0100;      // Addr of top of the stack
    uint32_t begin_stack = 0x01FF;    // Addr of bottom of the stack
    uint32_t stack_ptr = begin_stack; // Stack Pointer

  public:
    Stack(Memory &memory) : memory_(memory)
    {
    }

    void Push(uint8_t &data)
    {
        // Check for Stack Overflow (throw exception)
        if (stack_ptr - 1 < end_stack)
            throw StackOverFlow;

        memory_(stack_ptr, data);
        --stack_ptr;
    }

    uint8_t Pop(void)
    {
        // Check for Stack Underflow (throw exception)
        if (stack_ptr + 1 > begin_stack)
            throw StackUnderFlow;

        uint8_t data = memory_[stack_ptr];
        ++stack_ptr;
        return data;
    }
};
} // namespace MOS6502
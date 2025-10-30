/*
----------------------------------------------------------------------------------------
|                          6502 Memory (Random Access Memory)                          |
----------------------------------------------------------------------------------------
The 6502 has a 16-bit "address" bus & a 8-bit "data" bus. It can address 64K (65,535) 
unique bytes of memory (when fully populated - not required) but inside each "slot" of 
memory it can only store a 8-bit value (e.g. a byte).
_______________________________________________________________________________________

1) Mininum Required RAM ~ 8k
2) [0x0000 - 0x00FF] "Zero-Page"
3) [0x0100 - 0x01FF] "The Stack" 
----------------------------------------------------------------------------------------
*/

#pragma once 


// stl
#include <array>
#include <cassert>
#include <cstdint>


namespace MOS6502
{
    class  Memory
    {
        public: 

        // Constructor/Destructor
        Memory()=default;
        ~Memory()=default;

        void clear() { m_data.fill(0); }

        uint8_t operator[](uint32_t address) const      // Define Operator for indexing into Mem STRUCT directly
        {
            assert(address < MAX_MEM);
            return m_data[address];
        }

        uint8_t& operator[](uint32_t address)           // Define Operator for setting values of Memory
        {
            assert(address < MAX_MEM);
            return m_data[address];
        }

        void operator()(uint32_t address, uint8_t data)
        {
            assert(address < MAX_MEM);
            m_data[address] = data;
        }        

        private: 
        static constexpr uint32_t MAX_MEM  {65535}; // Address Bus of 6502 is 16 bits wide
        std::array<uint8_t, MAX_MEM> m_data {};   // Emulators memory abstraction is a fixed size array 
    };
}
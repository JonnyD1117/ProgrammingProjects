/*
----------------------------------------------------------------------------------------
|                                    6502 Emulator                                     |
----------------------------------------------------------------------------------------
This file provides the enacapsulation around the entire 6502 C++ code and creates 
the abstraction that other entities can interact with. 
_______________________________________________________________________________________

CPU 
Memory 
Registers 
Types 

----------------------------------------------------------------------------------------
*/


#pragma once 

#include <fstream>
#include <iostream>
#include <string>

namespace MOS6502
{

    class Emulator {

        public:
        Emulator()=default;
        ~Emulator()=default;

        int run();

        private:

        std::ifstream in;

        

    };

} // namespace MOS6502
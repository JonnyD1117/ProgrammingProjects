
// std
#include <iostream>

// local 
#include "emulator.hpp"

int main ()
{

    MOS6502::Emulator emu;

    emu.run();
  
    return 0;
}
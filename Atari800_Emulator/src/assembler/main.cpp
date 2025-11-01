#include <iostream>
#include "assembler.hpp"
#include <string>


int main(int argc, char *argv[]) 
{
    std::string path = "/home/indy/repos/6502-Emulator/src/assembler/programs/test.S";
    Assembler assem(path);

    std::cout << "Hello 6502 Assembler" << std::endl;
    return 0;
}
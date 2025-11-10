// std
#include <iostream>
#include <string>

// local 
#include "assembler.hpp"

int main(int argc, char *argv[]) 
{
    std::string cwd = std::string(PROJECT_SOURCE_DIR);   // Defined in CMAKE target_compile_definitions()
    std::string path = cwd + "/sample_programs/test.S";

    Assembler assem(path);
    return 0;
}
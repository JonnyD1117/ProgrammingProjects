#include <iostream>
#include "emulator.hpp"
#include <vector>

#include <yaml-cpp/yaml.h>


int main ()
{
    YAML::Node config = YAML::LoadFile("config.yaml");
    std::cout << "Hello 6502 Emulator" << std::endl;

    for (auto instr : config["instruction_set"]) {

        size_t opcode                   = instr["opcode"].as<size_t>();
        std::string mnemonic            = instr["mnemonic"].as<std::string>();
        std::string mode                = instr["mode"].as<std::string>();
        size_t cycles                   = instr["cycles"].as<size_t>();
        size_t page_boundry_cycles      = instr["page_boundry_cycles"].as<size_t>();
        std::vector<char> affects_flags = instr["affects_flags"].as<std::vector<char>>();
        std::string handler             = instr["handler"].as<std::string>();

        std::cout << "################################## "<< "\n";
        std::cout << "0x" << std::hex <<  opcode << "\n";
        std::cout << mnemonic << "\n";
        std::cout << mode << "\n";
        std::cout << cycles << "\n";
        std::cout << page_boundry_cycles << "\n";
        // std::cout << affects_flags << "\n";
        std::cout << handler << "\n";
    }
    return 0;
}
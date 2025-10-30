#pragma once 

// std
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <cstdint>

/*
Assembler Instructions
1) Lines that beging with ';' are ALWAYS full like comments and will be ignored
2) Lines that have instructions but posfix comments to an instruction will be ignore from that symbol to End-of-line

*/



class Assembler
{
    public:
    Assembler()=default;
    ~Assembler()=default;

    Assembler(const std::filesystem::path path) : m_inFile {path}
    {
        if (!std::filesystem::exists(path))
        {
            throw std::runtime_error("Input file does not exists: " + path.string());
        }
        if (!m_inFile.is_open())
        {
            throw std::runtime_error("Failed to open file: " + path.string());
        }

        // Iterate over file line-by-line 
        std::string tmp; 
        while(std::getline(m_inFile, tmp))
        {
            
            // Find first non-whitespace character in line
            auto it = std::find_if(tmp.begin(), tmp.end(), [](unsigned char ch){ return !std::isspace(ch); });

            // If line begins with comment symbol ;
            if( *it == ';') { continue; }

            std::string line (it, tmp.end());

            // parse each line
            for (unsigned char ch : line)
            {   
                // If Line 
                if ( ch == ';') { break; }

                std::cout << ch;
            }
            std::cout << std::endl;
        }
    }

    private:
    std::unordered_map<std::string, std::string> m_symbolTable;
    std::ifstream m_inFile;
    std::ofstream m_outFile;

    std::uint16_t m_currPC;
    
};

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

// local 
#include "lexer.hpp"


class Assembler
{
    public:
    Assembler()=delete;
    ~Assembler()=default;

    Assembler(const std::filesystem::path path) : m_inFile {path}, m_lexer{path}
    {
        if (!std::filesystem::exists(path))
        {
            throw std::runtime_error("Input file does not exists: " + path.string());
        }
        if (!m_inFile.is_open())
        {
            throw std::runtime_error("Failed to open file: " + path.string());
        }

        // Tokenize File Input
        m_lexer.processToken();

        // Parse Tokens
        // m_parser.()

        // 
     
    }

    private:
    std::unordered_map<std::string, std::string> m_symbolTable;
    std::ifstream m_inFile;
    std::ofstream m_outFile;

    std::uint16_t m_currPC;

    Lexer m_lexer;
};

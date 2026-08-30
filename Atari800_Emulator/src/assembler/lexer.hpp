

#pragma once 

//std 
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>


enum class SymbolTypes
{
    INVALID=0,
    INSTRUCTION,
    HASH, 
    HEX, 
    DIRECTIVE,
    COMMENT,
};

struct Token
{
 SymbolTypes m_type {SymbolTypes::INVALID};
 std::string m_data {};
};


class Lexer
{
    public: 
    Lexer( const std::filesystem::path& text_file) : m_file{ text_file }, m_ifile_stream{text_file}
    {

    }

    Token nextToken()
    {
        return processToken();
    }

    private:
    Token processToken()
    {
        // Ignore comments 

        // handle instruction 

        // handle variable 

        // handle label

        // handle directive

        // Iterate over file line-by-line 
        std::string tmp; 
        while(std::getline(m_ifile_stream, tmp))
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
    std::filesystem::path m_file;
    std::ifstream m_ifile_stream;

    Token m_token; 
};
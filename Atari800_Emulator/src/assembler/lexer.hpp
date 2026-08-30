

#pragma once 

//std 
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <vector>


// IDENTIFIER     LOOP
// INSTRUCTION    LDA
// REGISTER       X
// NUMBER         $FF, %10101010, 42
// STRING         "hello"
// CHARACTER      'A'          (if your dialect supports it)
// PUNCTUATION    # , ( ) :
// OPERATOR       + - *
// COMMENT        ; ...
// NEWLINE


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
    Lexer( const std::filesystem::path& text_file) : m_file{ text_file }, m_ifile_stream{text_file} {}
    Lexer()=delete;

    Token nextToken();

    Token processToken();

    private: 

    void handle_begin_file(char next_char)
    {
        if( next_char == ' ' )
        {
            m_state = LexerState::SPACE;
        }
        else if (next_chr == ';')
        {
            m_state = LexerState::COMMENT;
        }
        else if (next_chr == '.')
        {
            m_state = LexerState::DIRECTIVE;
            m_temp += '.';

        }
        else
        {

        }
    }

    void handle_character( char next_char )
    {
        if ( next_char == ' ' )
        {
            // End of INDENTIFIER, directive, label
        }
        else if (next_char == ';')
        {
            // End of INDENTIFIER/Label/Directive 
            // beginning of a commennt 
            m_state = LexerState::COMMENT;
        }
    }

    void consume(char next_char); 

    enum class LexerState
    {
        START=0,
        SPACE,
        COMMENT,
        DIRECTIVE,
        END_OF_LINE,
        INDENTIFIER,
        CHARACTER,
        LABEL,
    };

    std::string m_temp           {""};

    std::filesystem::path m_file {};
    std::ifstream m_ifile_stream {};

    LexerState m_state           {LexerState::START};
    Token m_token                {}; 
    Token m_prev_token           {};
    std::vector<Token> m_tokens  {};
};
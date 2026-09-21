

#pragma once 

//std 
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <cctype>
#include <unordered_map>
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


enum class SymbolType
{
    INVALID=0,
    IDENTIFIER,
    HASH, 
    HEX, 
    LABEL,
    DIRECTIVE,
    COMMENT,
};

static std::unordered_map<SymbolType, std::string> symbolType2String 
{
    {SymbolType::INVALID,    "INVALID"},
    {SymbolType::IDENTIFIER, "IDENTIFIER"},
    {SymbolType::HASH,       "HASH"},
    {SymbolType::HEX,        "HEX"},
    {SymbolType::DIRECTIVE,  "DIRECTIVE"},
    {SymbolType::COMMENT,    "COMMENT"},
    {SymbolType::LABEL,       "LABEL"},

};


struct Token
{
    SymbolType m_type {SymbolType::INVALID};
    std::string m_data {};

    void print()
    {
     std::cout << std::left << std::setw(15) <<  "Token Type: " \
               << std::left << std::setw(15) << symbolType2String[m_type] \
               << std::left << std::setw(15) <<  "Value: "\
               << std::left << std::setw(20) << m_data << std::endl;
    }
};



class Lexer
{
    public: 
    Lexer( const std::filesystem::path& text_file) : m_file{ text_file }, m_ifile_stream{text_file} {}
    Lexer()=delete;

    Token nextToken();

    std::vector<Token> getTokenList() { return m_tokens; }

    void processToken();

    private: 

    // Consume next character in Lexer FSM
    bool consume(char next_char); 

    void handle_space( char next_char);

    void handle_directive( char next_char);

    void handle_hex_literal(char next_char);

    void handle_end_of_line(char next_char);
    
    void handle_identifier(char next_char);
    
    void handle_character( char next_char );

    void handle_comment( char next_char );

    void handle_immediate( char next_char );

    void handle_label(char next_char);

    void handle_digit(char next_char);

    void accumulate_character(char next_char);


    inline void clearToken()
    {
        // Unset/Clear Token Data
        m_symbol_t = SymbolType::INVALID;
        m_temp.clear();
    }

    inline void createToken(SymbolType type, std::string& data)
    {
       m_tokens.push_back( {type, data} );
    }

    void generate_token()
    {   
        // End of Line - Finish any uncompleted tokens
        if( m_state == LexerState::COMMENT)
        {
            // Create COMMENT Token
            createToken(SymbolType::COMMENT, m_temp );
        }
        else if (m_state == LexerState::START_OF_LINE)
        {
            // Empty Line
        }
        else if (m_state == LexerState::HEX)
        {
            createToken(SymbolType::HEX, m_temp );
        }
        else if (m_state == LexerState::HASH)
        {
            createToken(SymbolType::HASH, m_temp );
        }
        else if (m_state == LexerState::LABEL)
        {
            createToken(SymbolType::LABEL, m_temp);
        }
        else if (m_state == LexerState::HEX)
        {
            createToken(SymbolType::HEX, m_temp);
        }
        // Clear Token of Current Data
        clearToken();
    }

    bool is_whitespace_only( const std::string& str )
    {
        return std::all_of(str.begin(), str.end(), [](unsigned char ch){ return std::isspace(ch); });
    }

    bool is_letter(char ch) 
    {
        return std::isalpha(static_cast<unsigned char>(ch));
    }

    bool is_numeric_digit(char ch) {
        return std::isdigit(static_cast<unsigned char>(ch));
    }

    enum class LexerState
    {
        INVALID=0,
        START_OF_FILE,
        START_OF_LINE,
        SPACE,
        COMMENT,
        DIRECTIVE,
        HEX,
        HASH,
        END_OF_LINE,
        INDENTIFIER,
        CHARACTER,
        LABEL,
    };

    std::string m_temp           {""};

    std::filesystem::path m_file {};
    std::ifstream m_ifile_stream {};

    LexerState m_state           {LexerState::START_OF_LINE};
    SymbolType m_symbol_t        {SymbolType::INVALID};
    Token m_token                {}; 
    Token m_prev_token           {};
    std::vector<Token> m_tokens  {};
};
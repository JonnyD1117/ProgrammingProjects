
#include "lexer.hpp"


Token Lexer::nextToken() { return m_tokens[0]; }

Token Lexer::processToken()
{
    // Iterate over file line-by-line 
    std::string tmp; 
    while(std::getline(m_ifile_stream, tmp))
    {
        // Find first non-whitespace character in line
        auto it = std::find_if(tmp.begin(), tmp.end(), [](unsigned char ch){ return !std::isspace(ch); });

        std::string line (it, tmp.end());

        // parse each line (char by char)
        for (unsigned char ch : line)
        {   
            consume( ch );
        }
    }

    return Token();
}


void Lexer::consume(char next_char)
{
    switch( m_state )
    {
        case LexerState::START:
            handle_begin_file( next_char );
            break;
        case LexerState::SPACE:
            handle_space( next_char );
            break;
        case LexerState::COMMENT:
            handle_comment( next_char );
            break;
        case LexerState::END_OF_LINE:
            handle_end_of_line( next_char );
            break;
        case LexerState::DIRECTIVE:
            handle_directive( next_char );
            break;
        case LexerState::CHARACTER:
            handle_character( next_char );
            break;
        default:
            break;
    };
}
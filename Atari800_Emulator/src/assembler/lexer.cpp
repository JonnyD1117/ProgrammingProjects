
#include "lexer.hpp"


Token Lexer::nextToken() { return m_tokens[0]; }

void Lexer::processToken()
{
    // Iterate over file line-by-line 
    std::string tmp; 
    while(std::getline(m_ifile_stream, tmp))
    {
        // Find first non-whitespace character in line
        auto it = std::find_if(tmp.begin(), tmp.end(), [](unsigned char ch){ return !std::isspace(ch); });

        std::string line (it, tmp.end());

        // Skip Empty "lines"
        if( !is_whitespace_only( line ) )
        {
            // parse each line (char by char)
            for (unsigned char ch : line)
            {   
                // Consume next Character 
                consume( ch );
            }

            // End of Line reached - finalize token
            generate_token();
        }
    }
}

bool Lexer::consume(char next_char)
{
    if ( next_char == ' ' )
    {
        handle_space(next_char);
    }
    else if (next_char == ';')
    {
        handle_comment(next_char)        ;
    }
    else if (next_char == '.')
    {
        handle_directive(next_char);
    }
    else if (next_char == '$')
    {
        handle_hex_literal(next_char);
    }
    else if (next_char == '#')
    {
        // Immediate Addressing
        handle_immediate(next_char);
    }
    else if (next_char == ':')
    {
        // Immediate Addressing
        handle_label(next_char);
    }
    else if ( is_letter(next_char) )
    {
        handle_character(next_char);
    }
    // else if ( is_numeric_digit(next_char) )
    // {
    //     handle_digit(next_char);
    //}
    else
    {
        // Accumulate Character into temporary storage
        accumulate_character(next_char);
    }

    return false;
}

void Lexer::handle_character( char next_char )
{
    switch (m_state)
    {
        case LexerState::START_OF_LINE:
        {
            m_state = LexerState::INDENTIFIER;
            accumulate_character(next_char);
            break;
        }
        case LexerState::DIRECTIVE:
        {
            accumulate_character(next_char);
            break;
        }
        case LexerState::COMMENT:
        {
            accumulate_character(next_char);
            break;
        }
        default:
            break;
    }
}

void Lexer::handle_immediate( char next_char )
{
    m_state = LexerState::HASH;
    accumulate_character( next_char );
}

void Lexer::handle_hex_literal(char next_char)
{
    m_state = LexerState::HEX;
    accumulate_character(next_char);
}

void Lexer::handle_directive( char next_char)
{
    // .org .byte .word
    m_state = LexerState::DIRECTIVE;
    accumulate_character(next_char);
}

void Lexer::handle_label(char next_char)
{
    if(m_state == LexerState::CHARACTER)
    {
        m_state = LexerState::LABEL;
        accumulate_character(next_char);
    }
}

void Lexer::handle_space(char next_char)
{

    switch( m_state )
    {
        case LexerState::INVALID:
        {
            // Do Nothing
            break;
        }
        case LexerState::COMMENT:
        {
            m_temp += next_char;
            break;
        }
        case LexerState::START_OF_LINE:
        {
            // Do Nothing
            break;
        }
        case LexerState::DIRECTIVE:
        {
            createToken(SymbolType::DIRECTIVE, m_temp);
            clearToken();
            break;
        }
        case LexerState::INDENTIFIER:
        {
            createToken(SymbolType::IDENTIFIER, m_temp);
            clearToken();
            break;
        }
        case LexerState::HEX:
        {
            createToken(SymbolType::HEX, m_temp);
            clearToken();
            break;
        }
        default:
            break;
    }

    // End of INDENTIFIER, directive, label
        // switch(m_symbol_t)
        // {
        //     case SymbolType::DIRECTIVE:
        //     {
        //         m_tokens.push_back( emitToken() );
        //         break;
        //     }
        //     case SymbolType::HEX:
        //     {
        //         m_tokens.push_back( emitToken() );
        //         break;
        //     }
        //     case SymbolType::COMMENT:
        //     {
        //         m_tokens.push_back( emitToken() );
        //         break;
        //     }
        //     default: 
        //         break;
        // }
}

void Lexer::handle_digit(char next_char)
{
    if(m_state == LexerState::HEX)
    {
        accumulate_character(next_char);
    }
}
void Lexer::handle_comment( char next_char )
{
    // Set Comment State and Accumulate Comment
    m_state = LexerState::COMMENT;
    m_temp+=next_char;
}

void Lexer::accumulate_character(char next_char)
{
    m_temp += next_char;
}
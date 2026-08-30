
// std
#include <utility>

// local 
#include "symbol_table.hpp"

void SymbolTable::insertSymbol( std::string key, std::string value)
{
    m_table[key] = value;
}

bool SymbolTable::symbolExists(std::string key)
{
    auto it = m_table.find(key);

    if ( it != m_table.end())
    {
        return true;
    }

    return false;
}
 

std::pair<std::string, std::string> SymbolTable::getSymbol(std::string key)
{
    auto it = m_table.find(key);

    if ( it != m_table.end())
    {
        // return std::make_pair<std::string, std::string>( key, *it );
    }

    return std::make_pair<std::string,std::string>("","");
}
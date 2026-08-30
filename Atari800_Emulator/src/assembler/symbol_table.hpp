
#pragma once 

// std
#include <string>
#include <unordered_map>


class SymbolTable
{
    public: 

    void insertSymbol(std::string key, std::string value);

    bool symbolExists(std::string key);

    std::pair<std::string, std::string> getSymbol(std::string key);

    private:

    std::unordered_map<std::string, std::string> m_table {};

};
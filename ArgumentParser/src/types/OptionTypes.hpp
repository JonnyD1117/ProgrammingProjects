#pragma once 
// std
#include <vector>
#include <format>
#include <variant>
#include <string>

struct CliOption
{
    std::string                                  m_name;
    std::variant<int, double, std::string, bool> m_value;
    bool                                         m_required;
    std::string                                  m_doc;
    std::string                                  m_prefix {"--"};

    std::string toString()
    {
        return std::format(" {}{} \t : {}", m_prefix ,m_name, m_doc);
    }
};
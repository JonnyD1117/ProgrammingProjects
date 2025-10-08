/**
 * @file stringified_enum.hpp
 * @brief File defines class for defining an ENUM that also maps to strings
 * @author Jonathan Dorsey 
 * @date Creation date: 2025-05-27
 * 
 */

#pragma once 

// std
#include <map>
#include <string>


namespace OpenGlTutorial
{

    class StringifiedEnum
    {
        std::map<std::string, int> m_str2Enum;
        std::map<int, std::string> m_enum2Str;

        std::string getString(int enumeration)
        {
            return m_enum2Str[enumeration];
        }
    };

}

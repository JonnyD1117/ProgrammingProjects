# pragma once 

// std
#include <iostream>
#include <format>
#include <optional>
#include <string>
#include <vector>


class OptionParser
{
    public:

    OptionParser()=default;
    ~OptionParser()=default;

    std::vector<std::pair<std::string, std::optional<std::string>>> getOptionStrings()
    {
        return m_optPairs;
    }

    std::string getCommand()
    {
        return m_command;
    }

    std::vector<std::string>  getRawOptions()
    {
        return m_rawArgs;
    }
    

    void parse_options(int argc, char* argv[])
    {
        // Convert Argv to more useful container
        vectorize_argv(argc, argv);

        std::string name;
        std::string value;

        // Iterate Remaining Options ( 1 -> Nth positions)
        for( auto it = m_rawArgs.begin()+1; it != m_rawArgs.end(); ++it)
        {
            // Extract Option from Prefix (-- or)
            name  = extractOptName(*it);

            auto next_it = it + 1;

            if(containsGlueOpt(name))
            {
                auto glued_opt = extractGluedOptionAndValue(name);
                m_optPairs.emplace_back(glued_opt.first, glued_opt.second);

                if(isBoolOpt(*next_it))
                {
                    throw std::runtime_error(std::format("Glued Option: '{}' Cannot be have trailing VALUE type. (e.g. --my_opt=12 10 is INVALID)", name));
                }
            }

            else if(isBoolOpt(*next_it))
            {
                m_optPairs.emplace_back(name, std::nullopt);
            }

            else
            {
                // Has Value
                value = *next_it;
                m_optPairs.emplace_back(name, value);

                ++it;
            }   
        }
    }

    private:

    void vectorize_argv(int argc, char* argv[])
    {
        m_rawArgs.reserve(argc);

        // Stringify ArgV        
        for(size_t idx=0; idx<argc; idx++)
        {
            m_rawArgs.emplace_back(argv[idx]);
        }

        // Extract Executable Command (0th position)
        m_command = m_rawArgs[0];
    }

    bool isBoolOpt(const std::string& argument)
    {
        bool notBooleanOpt = containsOptLongPrefix(argument) || containsOptShortPrefix(argument);
        return !notBooleanOpt;
    }

    bool containsGlueOpt(const std::string& argument)
    {
        return (argument.find(m_glueInfix) != std::string::npos) ? true : false;
    }

    bool containsOptShortPrefix(const std::string& argument)
    {
        return (argument.substr(0, m_shortPrefix.length()) == m_shortPrefix) ? true : false;
    }

    bool containsOptLongPrefix(const std::string& argument)
    {
        return (argument.substr(0, m_longPrefix.length()) == m_longPrefix) ? true : false;
    }

    std::string extractOptName(const std::string& argument)
    {
        std::string optName; 
        
        if(containsOptLongPrefix(argument))
        {
            optName = argument.substr(m_longPrefix.length());
        }
        else if(containsOptShortPrefix(argument))
        {
            optName = argument.substr(m_shortPrefix.length());
        }
        else
        {
            throw std::runtime_error("Invalid option Prefix");
        }
        return optName;
    }

    std::pair<std::string, std::string> extractGluedOptionAndValue(const std::string& argument)
    {
        std::string name;
        std::string value; 

        size_t glue_pos = argument.find(m_glueInfix);

        if(glue_pos == std::string::npos)
        {
            throw std::runtime_error("Invalid");
        }

        name = argument.substr(0, glue_pos);
        value = argument.substr(++glue_pos);

        return std::make_pair(name, value);
    }

    std::string m_command                   {};

    const std::string m_shortPrefix         {"-"};
    const std::string m_longPrefix          {"--"};
    const std::string m_glueInfix           {"="};

    std::vector<std::string>                                        m_rawArgs;
    std::vector<std::pair<std::string, std::optional<std::string>>> m_optPairs;

};
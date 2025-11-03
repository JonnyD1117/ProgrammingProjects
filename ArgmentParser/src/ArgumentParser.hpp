# pragma once 

// std
#include <any>
#include <iostream>
#include <format>
#include <print>
#include <optional>
#include <string>
#include <unordered_map>
#include <typeinfo>
#include <variant>
#include <vector>

// Container to hold ALL Option Information and value
struct CliOption
{
    std::string                                  m_name;
    std::variant<int, double, std::string, bool> m_value;
    bool                                         m_required;
    std::string                                  m_doc;

    std::string toString()
    {
        return std::format(" --{} \t : {}", m_name, m_doc);
    }
};




class ArgumentParser
{
    public:
    ArgumentParser()=default;
    ~ArgumentParser()=default;

    void parse_options(int argc, char* argv[])
    {
        if(!m_arguments_added)
        {
            std::cout << "No Arguments have been added to parser using 'add_argument(name, default_value, help)' function!" << std::endl;
            exit(EXIT_FAILURE);
        }


        // Stringify ArgV        
        for(size_t idx=0; idx<argc; idx++)
        {
            m_rawArgs.emplace_back(argv[idx]);
        }

        // Extract Executable Command (0th position)
        m_command = m_rawArgs[0];

        std::string name;
        std::string value;
        bool nameSet   = false;

        // Iterate Remaining Options ( 1 -> Nth positions)
        for( auto it = m_rawArgs.begin()+1; it != m_rawArgs.end(); ++it)
        {
            // Check if Option contains a prefixed name ( e.g. --your_option)
            if(!nameSet)
            {
                if(containsOptPrefix(*it))
                {
                    name = (*it).substr(m_prefix.length());
                    nameSet = true;
                }
                else
                {
                    throw std::runtime_error("Bad Option: Cannot pass a value without binding to argument");
                }
            }
            else
            {
                // Name is ALREADY set
                if(containsOptPrefix(*it))
                {
                    // Handle Previous Name 
                    m_optPairs.emplace_back(name, std::nullopt);

                    name = (*it).substr(m_prefix.length());
                    nameSet   = true;
                }
                else
                {
                    value = *it;
                    m_optPairs.emplace_back(name, value);
                    nameSet = false;
                }
            }    
            
            // Prempt Execution if HELP option is added
            if(name == "help" || name == "h")
            {
                print_usage();
                exit(EXIT_SUCCESS);
            }
        }
        
        // Build Option Tree
        registerOptions();
    }
    


    template<typename T>
    void add_argument(const std::string& name, T default_value, const std::string& doc="", bool required=false)
    {
        // Handle Illegal Override of "help" argument
        if(name == "help" || name == "h")
        {
            std::println("Argument: '{}' is reserved & cannot be overwritten!", name);
        }

        // Handle Valid Argument Construction
        if(m_options.find(name) != m_options.end())
        {
            // Exists
            std::print("Argument: '{}', already added. Please remove duplicate!", name);
        }   
        else
        {
            m_options.emplace(name, CliOption{name, default_value, required, doc});
        }   

        m_arguments_added = true;
    }

    template<typename T>
    T get(const std::string& name)
    {
        CliOption opt;

        if(m_options.find(name) != m_options.end())
        {
            opt = m_options[name];
        }

        return std::get<T>(opt.m_value);
    }

    void print_usage()
    {
        
        std::println("\nUsage: {}\n", m_command);
        std::println("Options:");
        for(auto [key, opt] : m_options)
        {
            std::string opt_str = opt.toString();
            std::println("{}",opt_str);
        }
    }

    private:

    void registerOptions()
    {
        for(auto [name, value] : m_optPairs)
        {
            if(value.has_value())
            {
                std::string val = value.value();

                if(m_options.find(name) != m_options.end())
                {
                    if(std::holds_alternative<int>(m_options[name].m_value))
                    {
                        m_options[name].m_value = std::stoi(val);
                    }
                    else if(std::holds_alternative<double>(m_options[name].m_value))
                    {
                        m_options[name].m_value = std::stod(val);
                    }
                    else
                    {
                        m_options[name].m_value = value.value();
                    }                    
                }
            }
            else
            {
                // Handle Boolean Flag
                if(m_options.find(name) != m_options.end())
                {
                    if(std::holds_alternative<bool>(m_options[name].m_value))
                    {
                        bool truth_ness = std::get<bool>(m_options[name].m_value);
                        m_options[name].m_value = !truth_ness;
                    }
                }

            }
        }
    }

    bool containsOptPrefix(const std::string& argument)
    {
        return (argument.substr(0, m_prefix.length()) == m_prefix) ? true : false;
    }
    
    bool m_arguments_added     {false};
    std::string m_command      {""};
    const std::string m_prefix {"--"};

    std::unordered_map<std::string, CliOption>                      m_options;
    std::vector<std::string>                                        m_rawArgs;
    std::vector<std::pair<std::string, std::optional<std::string>>> m_optPairs;

};
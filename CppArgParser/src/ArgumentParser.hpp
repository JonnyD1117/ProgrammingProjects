# pragma once 

// std
#include <any>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>
#include <typeinfo>
#include <variant>
#include <vector>


struct CliOption
{
    std::string name;
    std::any value;
    std::string help;
};


class ArgumentParser
{
    public:
    ArgumentParser()=default;
    ~ArgumentParser()=default;

    template<typename T>
    void add_argument(const std::string& name, T value, std::string& help)
    {
        m_options
    }

    void parse_options();

    template<typename T>
    T get(const std::string& option_name)
    {
        // Find 
        std::any value = m_options[option_name];

        return std::get<T>(value);
    }

    

    private:
    
    std::unordered_map<std::string, std::any> m_options;

};
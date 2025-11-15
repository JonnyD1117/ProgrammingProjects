# pragma once 

// std
#include <iostream>
#include <filesystem>
#include <format>
#include <memory>
#include <optional>
#include <print>
#include <string>
#include <unordered_map>
#include <typeinfo>
#include <variant>
#include <vector>

// local 
#include "IConfigurator.hpp"
#include "OptionParser.hpp"
#include "OptionTypes.hpp"
#include "JsonConfigurator.hpp"
#include "YamlConfigurator.hpp"

// Aliased Namespaces
namespace fs = std::filesystem;


class ArgumentParser
{
    public:

    ArgumentParser()=default;
    ~ArgumentParser()=default;

    void parse_options(int argc, char* argv[])
    {
        // Convert Argv to more useful container
        m_parser.parse_options(argc, argv);

        m_optPairs = m_parser.getOptionStrings();
        m_command  = m_parser.getCommand();
    
        for(auto& [name, _] : m_optPairs)
        {
            // Prempt Execution if HELP option is added
            if(name == "help" || name == "h")
            {
                print_usage();
                exit(EXIT_SUCCESS);
            }
        }

        print_usage();
        
        // Build Option Tree
        registerOptions();
    }
    
    void add_config(const fs::path& path, const std::string& name="config", const std::string& doc ="" )
    {
        // Check that Config Exists
        if(!fs::exists(path))
        {
            std::println("Argument: '{}' requires a 'path' to a configuration file! ", name);
            std::println("  Path '{}' does not exist!", path.string());
            exit(EXIT_FAILURE);
        }

        if(!path.has_extension())
        {
            std::println("Configuration file has NO file extension...");
            exit(EXIT_FAILURE);
        }
        
        // Initialize File Extension Specific Configurator
        std::string ext = path.extension();
        if(ext == ".yaml" || ext == ".yml")
        {
            m_config = std::make_unique<YamlConfigurator>();
        }
        else if(ext == "json")
        {
            m_config = std::make_unique<JsonConfigurator>();
        }
        else
        {
            std::println("Configuration file provided, of type {} is NOT supported. Please use .yaml or .json", ext);
            exit(EXIT_FAILURE);
        }

        // Pass Config Path to Configurator
        m_config->set_config(path);
        
        // Populate Arguments from Validated Options
        for(auto& option : m_config->get_options())
        {
            add_argument(option);
        }
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
            add_argument(CliOption{name, default_value, required, doc});
        }   
    }

    void add_argument(const CliOption& option)
    {
        m_options.emplace(option.m_name, option);
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

    bool m_arguments_added                  {false};
    std::string m_command                   {""};
    std::unique_ptr<IConfigurator> m_config {nullptr};

    OptionParser                                                    m_parser;

    std::unordered_map<std::string, CliOption>                      m_options;
    std::vector<std::string>                                        m_rawArgs;
    std::vector<std::pair<std::string, std::optional<std::string>>> m_optPairs;

};
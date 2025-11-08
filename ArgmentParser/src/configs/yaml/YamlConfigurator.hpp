#pragma once

// std
#include <iostream>
#include <filesystem>

// yaml-cpp
#include <yaml-cpp/yaml.h>

// local
#include "IConfigurator.hpp"
#include "OptionTypes.hpp"
#include "YamlSchema.hpp"

// Aliased Namespaces
namespace fs = std::filesystem;


class YamlConfigurator : public IConfigurator
{
    public:

    YamlConfigurator()  = default;
    virtual ~YamlConfigurator() = default;

    void set_config(const fs::path& path) override
    {
        try
        {
            // Set & Validate Config File
            m_schema.validate(path);

            // Populate Options Vector
            populate_options();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }


    std::vector<CliOption> get_options() override
    {
        return m_configOptions;
    }

    private:

    void populate_options()
    {
        // Iterator of each pair of var name & option YAML::Node
        for(auto& [opt_name, node_sequence] : m_schema.get_valid_nodes() )
        {
            std::string opt_value = ""; 
            std::string opt_help  = "";
            bool opt_required = false;

            // Ensure Node is a list (e.g. sequence)
            if(!node_sequence.IsSequence())
            {
                throw std::runtime_error("Configuration FAILED! YAML Node is NOT of type Sequence");
            }
    
            for(const auto& element : node_sequence)
            {
                // Ensure Node is Map (key:value) pair
                if(!element.IsMap())
                {
                    throw std::runtime_error("Configuration FAILED! YAML Node is NOT of type MAP");
                }

                // Set CliOption values from YAML Node Mapping
                const std::string key   = element.first.as<std::string>();

                if(key == "value")
                {
                    opt_value = element.second.as<std::string>();
                }
                else if(key == "help")
                {
                    opt_help = element.second.as<std::string>();
                }
                else if(key == "required")
                {
                    opt_required = element.second.as<bool>();
                }
                else
                {
                    // Do Nothing
                }
            }

            // Populate Config Option
            m_configOptions.emplace_back(opt_name, opt_value, opt_required, opt_help);
        }
    }

    YamlSchema m_schema;
    std::vector<CliOption> m_configOptions;
};
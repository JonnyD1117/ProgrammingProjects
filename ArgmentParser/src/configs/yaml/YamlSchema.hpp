#pragma once 

// std
#include <expected>
#include <filesystem>
#include <iostream>
#include <format>
#include <string>
#include <utility>
#include <vector>

// yaml-cpp
#include <yaml-cpp/yaml.h>

// local 
#include "OptionTypes.hpp"

// Aliased Namespaces
namespace fs = std::filesystem;

class YamlSchema
{
    public:
    YamlSchema() = default;
    ~YamlSchema() = default;

    void validate(const fs::path& path )
    {
        try 
        {
            // Load Config yaml
            config_root = YAML::LoadFile(path.string());
        }
        catch (const YAML::BadFile& e) 
        {
            throw std::runtime_error(std::format("YamlSchema::validate() could NOT open config file '{}'", path.string()));
        }

        // Parse Config & Compare Against
        validateConfig(config_root);
    }

    std::vector<CliOption> get_valid_options()
    {
        return m_validOpts;
    }

    private:

    void validateConfig(const YAML::Node& node)
    {
        // Extract Option Node (type_map -> sequence)
        const YAML::Node option_node = node["options"];

        // Option Map -> Individual Option Sequences
        for (auto kv : option_node) 
        {
            auto name  = kv.first.as<std::string>(); // Option Name
            auto entry = kv.second[0];               // Option Map to Values

            // Extract Option State
            std::string value = entry["value"].as<std::string>();           
            std::string help  = entry["help"].as<std::string>();
            bool        req   = entry["required"].as<bool>();

            // Add
            m_validOpts.emplace_back(name, value, req, help);
        }
    }

    YAML::Node config_root {};

    std::vector<CliOption> m_validOpts {};    
};

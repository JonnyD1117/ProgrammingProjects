#pragma once 

// std
#include <filesystem>
#include <iostream>
#include <format>
#include <string>
#include <utility>
#include <unordered_map>
#include <vector>

// yaml-cpp
#include <yaml-cpp/yaml.h>

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

    std::unordered_map<std::string, YAML::Node> get_valid_nodes()
    {
        return m_validNodes;
    }

    private:

    void validateConfig(YAML::Node& node)
    {
        // Check if 'options' is defined
        if(!node["options"].IsDefined())
        {
            throw std::runtime_error(std::format("Yaml Validation FAILED! Schema found no Sequence name 'options:' in YAML config!"));
        }

        option_node = node["options"];

        if(option_node.IsSequence() || option_node.IsScalar())
        {
            for(const auto& kv : option_node)
            {
                std::string name = kv.first.as<std::string>();
                YAML::Node  node = kv.second;

                if(node.IsScalar())
                {
                    // Option Node is a LEAF 
                    m_validNodes[name] = node;
                }
                else
                {
                    throw std::runtime_error("YAML Validation FAILED: Schema detected that option map:  (e.g. key : value) is NOT a leaf in config tree");
                }
            }
        }
        else
        {
            throw std::runtime_error("YAML Validation FAILED: Schema detected that option list is EMPTY || is a Map and not a sequence/scalar");
        }

        

        // Detect Option Node 
        // option_node = whatever
    }

    YAML::Node config_root {};
    YAML::Node option_node {};

    std::unordered_map<std::string, YAML::Node> m_validNodes {};    
};

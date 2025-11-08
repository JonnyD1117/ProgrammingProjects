#pragma once

// std
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

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
        m_configOptions = m_schema.get_valid_options();
    }

    YamlSchema m_schema;
    std::vector<CliOption> m_configOptions;
};
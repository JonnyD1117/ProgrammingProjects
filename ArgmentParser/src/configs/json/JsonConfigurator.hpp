#pragma once

// std
#include <iostream>
#include <filesystem>

// jsoncons
#include <jsoncons/json.hpp>
#include <jsoncons_ext/jsonpath/jsonpath.hpp>

// local
#include "IConfigurator.hpp"
#include "OptionTypes.hpp"
#include "JsonSchema.hpp"

// Aliased Namespaces
namespace fs = std::filesystem;

class JsonConfigurator : public IConfigurator
{
    public:
    JsonConfigurator()  = default;
    virtual ~JsonConfigurator() = default;

    void set_config(const fs::path& path) override
    {
        m_config = path;
    }

    std::vector<CliOption> get_options() override
    {
        return m_configOptions;
    }

    private:

    fs::path m_config {""};
    std::vector<CliOption> m_configOptions;
};
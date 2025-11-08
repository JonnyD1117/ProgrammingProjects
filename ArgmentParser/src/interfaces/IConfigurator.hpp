#pragma once

// std
#include <filesystem>
#include <vector>

// local
#include "OptionTypes.hpp"

// Namespace
namespace fs = std::filesystem;

class IConfigurator
{
    public:
    virtual ~IConfigurator()=default;

    virtual void set_config(const fs::path& path) = 0;

    virtual std::vector<CliOption> get_options() = 0;

};
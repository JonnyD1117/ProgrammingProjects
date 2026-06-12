#pragma once 

// std
#include <filesystem>
#include <iostream>
#include <format>
#include <string>

// jsoncons
#include <jsoncons/json.hpp>
#include <jsoncons_ext/jsonpath/jsonpath.hpp>

// Aliased Namespaces
namespace fs = std::filesystem;


const std::string JSON_SCHEMA_PATH = "option_schema.json";


class JsonSchema
{
    public:
    JsonSchema()
    {
        // Assume Schema Always exists & is valid 
        // since it committed in the source directly
    }
    ~JsonSchema() = default;

    bool validate(const fs::path& path)
    {
        return false;
    }
    private:

};

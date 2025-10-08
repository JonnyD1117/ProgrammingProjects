/**
 * @file mesh_parser.hpp
 * @brief MeshParser class which can load a mesh files from different formats
 * @author Jonathan Dorsey
 * @date Creation date: 2025-05-27
 *
 * The goal of the Mesh Parser is to parser out the data from a mesh file and to
 * export that data as verteix
 */

#pragma once

// std
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <type_traits>

// Interfaces
#include "engine_interfaces.hpp"

// Mesh Parser
#include "assimp_parser.hpp"
#include "fbx_parser.hpp"
#include "mesh_types.hpp"
#include "obj_parser.hpp"

namespace OpenGlTutorial
{

// Mesh Format Enumeration & Mapping
enum class MeshFormat : int
{
    INVALID = -1,
    OBJ,
    ASSIMP,
    FBX,
};

// clang-format off
static std::unordered_map<std::string, MeshFormat> meshFormatMapping
{
    {"obj", MeshFormat::OBJ}, 
    {"fbx", MeshFormat::FBX}, 
    {"assimp", MeshFormat::ASSIMP}
};
// clang-format on

class MeshParserFactory
{
  public:
    MeshParserFactory() = default;
    virtual ~MeshParserFactory() = default;

    static std::unique_ptr<IMeshParser> create(const std::string &meshFormat)
    {
        // Type Container for Switch Logic
        MeshFormat type;

        // Search for Mesh Format in Mapping
        auto it = meshFormatMapping.find(meshFormat);

        // Set Parser Type (if Valid) or return invalid type
        type = (it != meshFormatMapping.end()) ? type = it->second : MeshFormat::INVALID;

        // Determine correct Mesh Parser to Use
        switch (type)
        {
        case MeshFormat::ASSIMP:
        {
            return std::unique_ptr<IMeshParser>(std::make_unique<AssimpParser>());
        }
        case MeshFormat::OBJ:
        {
            return std::unique_ptr<IMeshParser>(std::make_unique<ObjParser>());
        }

        case MeshFormat::FBX:
        {
            return std::unique_ptr<IMeshParser>(std::make_unique<FbxParser>());
        }

        case MeshFormat::INVALID:
        {
            throw std::runtime_error("Mesh Parser - ERROR: Invalid MeshFormat string name given!");
            break;
        }

        default:
            throw std::runtime_error("Mesh Parser - ERRO: Unknown mesh parser selected!");
            break;
        }
    }
};

} // namespace OpenGlTutorial
/**
 * @file MeshImporter.hpp
 * @brief MeshImporter class which can load a mesh files from different formats
 * @author Jonathan Dorsey
 * @date Creation date: 2025-10-10
 *
 * MeshImporter handles ALL file-IO operations & parsing of a mesh file into a 
 * mesh object. The importer does NOT orchestrate which mesh to load, but 
 * serves MeshManager as a utility which will return a mesh given a file path
 * on disk.
 * 
 */

#pragma once

// std
#include <algorithm>
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
#include "obj_parser.hpp"
#include "gltf_parser.hpp"

#include "MeshData.hpp"

namespace OpenGlTutorial
{

// Mesh Format Enumeration & Mapping
enum class MeshFormat : int
{
    INVALID = -1,
    OBJ,
    FBX,
    GLTF,
};

// clang-format off
static std::unordered_map<std::string, MeshFormat> meshFormatMapping
{
    {".obj",    MeshFormat::OBJ}, 
    {".fbx",    MeshFormat::FBX}, 
    {".gltf",   MeshFormat::GLTF}
};
// clang-format on


struct MeshParserFactory
{
    static std::unique_ptr<IMeshParser> createParser( std::filesystem::path path,  bool useAssimp )
    {
        
        std::string extension = path.extension();

        bool isSupported  = (meshFormatMapping.find(extension) != meshFormatMapping.end()) ? true  : false ;

        // Use Assimp Parser (Override)
        if(useAssimp || !isSupported)
        {
            return std::make_unique<AssimpParser>();
        }

        // Use Mesh Specific Parser
        switch(meshFormatMapping[extension])
        {
            case MeshFormat::OBJ:
            {
                return std::make_unique<ObjParser>();
                break;
            }
            case MeshFormat::FBX:
            {
                return std::make_unique<FbxParser>();
                break;
            }
            case MeshFormat::GLTF:
            {
                return std::make_unique<GltfParser>();
                break;
            }
            default:
                return std::make_unique<AssimpParser>();
                break;

        }

        return std::make_unique<AssimpParser>();
    }
};

class MeshImporter
{
    public:

    // Constructor & Destructor 
    MeshImporter() = default;
    virtual ~MeshImporter() = default;

    // Public API
    std::shared_ptr<MeshData> loadMesh( const std::filesystem::path mesh_path );

    void setAssimp( bool flag ) { m_useAssimp = flag; }

    private:

    bool m_useAssimp { false };

};

} // namespace OpenGlTutorial
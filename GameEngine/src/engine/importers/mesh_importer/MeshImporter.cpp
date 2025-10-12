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

// stl
#include <format>

// local 
#include "MeshImporter.hpp"


namespace OpenGlTutorial
{

std::shared_ptr<MeshData> MeshImporter::loadMesh( const std::filesystem::path mesh_path )
{
    // Check that Mesh Path Exists
    if(!std::filesystem::exists(mesh_path))
    {
        throw std::runtime_error(std::format("Mesh file not found: {}", mesh_path.string()));
    }
    if(!mesh_path.has_extension())
    {
        throw std::runtime_error("Invalid mesh file does not have a valid file extension");
    }

    // Create Mesh Parser
    std::unique_ptr<IMeshParser> parser = MeshParserFactory::createParser(mesh_path, m_useAssimp);
    
    // Parse Mesh File 
    return parser->parse(mesh_path);
}

} // namespace OpenGlTutorial
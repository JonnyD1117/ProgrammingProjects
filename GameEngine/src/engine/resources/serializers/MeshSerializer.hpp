/**
 * @file MeshData.hpp
 * @brief Raw Mesh Vertex/Index data parsed in from a a mesh file
 * @author Jonathan Dorsey
 * @date Creation date: 2025-10-10
 * 
 * MeshData is intended to provide a portable data-type which the engine
 * can pass around, that does not couple into OpenGL functionality directly.
 * The MeshData class does not directly store the VBO but rather it contains
 * a vector of Vertex objects which will be built into a VBO when passed into
 * the render.
 */

 
#pragma once 

// std
#include <filesystem>
#include <format>
#include <fstream>
#include <vector>

// types 
#include "MeshTypes.hpp"
#include "MeshData.hpp"

namespace OpenGlTutorial
{
    class MeshSerializer
    {
        public:
        static void serialize( const MeshData& mesh, std::ofstream& of );

        static void serialize( const MeshData& mesh, const std::filesystem::path& serialization_path );

        static MeshData deserialize( std::ifstream& in );

        static MeshData deserialize( const std::filesystem::path& serialization_path );
        
    };

} // namespace OpenGlTutorial
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


namespace OpenGlTutorial
{
    class MeshData
    {
        public: 

        MeshData(){}

        // Require Move Semantics for Efficient ownership transfer from Import to MeshData Instance
        MeshData(std::vector<MeshVertex>&& vertices, 
                 std::vector<size_t>&& indices) 
                : vertices { std::move(vertices) }
                , indices  { std::move(indices) } 
        {
        }

        ~MeshData()=default;
        
        std::vector<MeshVertex> vertices {};        // Raw Vertex Structs (not VBOs)
        std::vector<size_t>     indices  {};        // Index Buffer (e.g. IBO/EBO)
    };

} // namespace OpenGlTutorial

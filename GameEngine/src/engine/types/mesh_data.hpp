/**
 * @file MeshData.hpp
 * @brief Raw Mesh Vertex/Index data parsed in from a a mesh file
 * @author Jonathan Dorsey
 * @date Creation date: 2025-10-10
 * 
 * MeshData is intended to provide a portable data-type which the engine
 * can pass around, that does not couple into OpenGL functionality directly.
 */

 
#pragma once 

// std
#include <format>
#include <vector>

// OpenGL
#include <glad/glad.h>



namespace OpenGlTutorial
{

    struct MeshData
    {
        // Require Move Semantics for Efficient ownership transfer from Import to MeshData Instance
        MeshData(std::vector<GLfloat>&& vertices, 
                 std::vector<GLuint>&& indices) 
                : vertices { std::move(vertices) }
                , indices  { std::move(indices) } 
        {
        }

        ~MeshData()=default;
        
        std::vector<GLfloat> vertices {};
        std::vector<GLuint> indices   {};
        
    };

} // namespace OpenGlTutorial

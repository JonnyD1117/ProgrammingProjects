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
#include <vector>

// OpenGL
#include <glad/glad.h>



namespace OpenGlTutorial
{

    struct MeshData
    {
        std::vector<GLfloat> vertices {};
        std::vector<GLuint> indices   {};
    };

} // namespace OpenGlTutorial

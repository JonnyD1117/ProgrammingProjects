/**
 * @file Renderer.hpp
 * @brief Renderer class provides centralized pipeline for drawing scene.
 * @author Jonathan Dorsey
 * @date Creation date: 205-05-07
 */

#pragma once 

// OpenGL
#include <glad/glad.h>

// Local 
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"


namespace OpenGlTutorial
{

class Renderer
{
    public:

    Renderer()=default;
    ~Renderer()=default;

    void Clear() const;

    void Draw(const Mesh& mesh, Shader& shader) const; 

    void Draw(const Mesh& mesh, Shader& shader, Texture& texture); 
};

} // namespace OpenGlTutorial
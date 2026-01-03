/**
 * @file Renderer.cpp
 * @brief Implementation of the class/functions defined in Renderer.hpp
 * @author Jonathan Dorsey 
 * @date Creation date: 2025-05-07
 * 
 * The Renderer class provides a mechanism for abstracting the graphics pipeline
 * out from either raw calls to OpenGL api or thin abstractions and allows a 
 * centralized object to be in control of the rendering process that is responsible
 * for "drawing" the final rendered image of our scene.
 */

#include "Renderer.hpp"


namespace OpenGlTutorial
{
    void Renderer::Clear() const 
    {
        // Clears Buffer & Sets default color after clearing
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 

        // Clear all the data buffers we have created and drawn
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::Draw(const Mesh& mesh, Shader& shader) const
    {
        shader.Bind();
        mesh.Bind();
        glDrawElements(GL_TRIANGLES, mesh.getNumIndices(), GL_UNSIGNED_INT, 0);
    }

    void Renderer::Draw(const Mesh& mesh, Shader& shader, Texture& texture)
    {
        shader.Bind();
        texture.Bind();
        mesh.Bind();
        glDrawElements(GL_TRIANGLES, mesh.getNumIndices(), GL_UNSIGNED_INT, 0);
    }



}
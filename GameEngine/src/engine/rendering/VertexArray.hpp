/**
 * @file VertexArray.hpp
 * @brief VertexArray abstracts OpenGL's concept of a Vertex Array Object
 * @author Jonathan Dorsey
 * @date Creation date: 2025-05-07
 */

#pragma once 

// OpenGL
#include <glad/glad.h>

// Local
#include "VertexBuffer.hpp"


namespace OpenGlTutorial
{
    class VertexArray
    {
        public:
        
        VertexArray();
        ~VertexArray()=default;

        void LinkAttribute(VertexBuffer& vbo, GLuint layout, GLuint numComps, GLenum type, GLsizeiptr stride, void* offset);

        void Bind() const;
        void Unbind() const;
        void Delete() const;

        GLuint ID; 
    };
} // namespace OpenGlTutorial
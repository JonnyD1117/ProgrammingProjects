/**
 * @file VertexBuffer.hpp
 * @brief Abstracts creation and usage of Vertex Buffer Objects in OpenGL.
 * @author Jonathan Dorsey
 * @date Creation date: 2025-05-07
 */

 
#pragma once 

// OpenGL
#include <glad/glad.h>


namespace OpenGlTutorial
{
    class VertexBuffer
    {
        public:
        
        VertexBuffer(GLfloat* vertices, GLsizeiptr size);
        ~VertexBuffer()=default;

        void Bind() const;
        void Unbind() const;
        void Delete() const;

        GLuint ID; 
    };
} // namespace OpenGlTutorial

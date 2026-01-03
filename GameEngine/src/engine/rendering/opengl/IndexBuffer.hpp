/**
 * @file IndexBuffer.hpp
 * @brief File defines class encapsulation of OpenGL IndexBuffer.
 * @author Jonathan Dorsey 
 * @date Creation date: 2025-05-07
 */

#pragma once 

// OpenGL
#include <glad/glad.h>


namespace OpenGlTutorial
{
    class IndexBuffer
    {
        public:
        
        IndexBuffer(GLuint* indices, GLsizeiptr size);
        ~IndexBuffer()=default;

        void Bind() const;
        void Unbind() const;
        void Delete() const;

        GLuint ID; 
    };
    
} // namespace OpenGlTutorial
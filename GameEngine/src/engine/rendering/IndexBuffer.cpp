/**
 * @file IndexBuffer.cpp
 * @brief Implementation of the class/functions defined in IndexBuffer.hpp
 * @author Jonathan Dorsey
 * @date Creation date: 2025-05-07
 * 
 * This class implements an encapsulation around OpenGL IndexBuffers to provide
 * a structure API for interacting with OpenGL index buffer without having to 
 * operate directly on OpenGL's C-style api primatives
 */


#include "IndexBuffer.hpp"


namespace OpenGlTutorial
{
    IndexBuffer::IndexBuffer(GLuint* indices, GLsizeiptr size)
    {
        // Create IndexBuffer Buffer & return IndexBuffer descriptor
        glGenBuffers(1, &ID);
    
        // Bind IndexBuffer ID to Buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

        // Pass buffer vertex data, size of data, and drawing mode
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }

    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::Delete() const
    {
        glDeleteBuffers(1, &ID);
    }
}
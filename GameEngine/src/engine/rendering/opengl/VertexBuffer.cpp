/**
 * @file VertexBuffer.cpp
 * @brief Implementation of the class/functions defined in VertexBuffer.hpp
 * @author Jonathan Dorsey
 * @date Creation date: 2025-05-07
 * 
 * Vertex Buffer class abstracts the concept and construction of a buffer of 
 * vertex points that are to be laid-out and drawn by OpenGL
 */

#include "VertexBuffer.hpp"


namespace OpenGlTutorial
{
    VertexBuffer::VertexBuffer(GLfloat* vertices, GLsizeiptr size)
    {
        // Create VertexBuffer Buffer & return VertexBuffer descriptor
        glGenBuffers(1, &ID);
    
        // Bind VertexBuffer ID to Buffer
        glBindBuffer(GL_ARRAY_BUFFER, ID);

        // Pass buffer vertex data, size of data, and drawing mode
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::Delete() const 
    {
        glDeleteBuffers(1, &ID);
    }
}
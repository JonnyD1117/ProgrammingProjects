/**
 * @file VertexArray.cpp
 * @brief Implementation of the class/functions defined in VertexArray.hpp
 * @author Jonathan Dorsey
 * @date Creation date: 2025-05-07
 * 
 * VertexArray class contains the logic and implementation for an OpenGL 
 * Vertex Array Object that not only binds to a VertexBuffer instance, 
 * abstracts and encapsulate the creation of a VertexArray object, 
 * but also informs OpenGL about the layout of the data stored within
 * the vertex buffer
 */

#include "VertexArray.hpp"


namespace OpenGlTutorial
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &ID);
        Bind();
    }

    void VertexArray::LinkAttribute(VertexBuffer& vbo, GLuint layout, GLuint numComps, GLenum type, GLsizeiptr stride, void* offset)
    {
        vbo.Bind();

        glVertexAttribPointer(layout, numComps, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);

        vbo.Unbind();
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(ID);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0); 
    }

    void VertexArray::Delete() const
    {
        glDeleteVertexArrays(1, &ID);
    }
}
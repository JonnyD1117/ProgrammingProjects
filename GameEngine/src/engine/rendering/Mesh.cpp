/**
 * @file Mesh.cpp
 * @brief Implementation of the class/functions defined in Mesh.hpp
 * @author Jonathan Dorsey
 * @date Creation date: 2025-05-11
 * 
 * This class implements the main abstraction around OpenGL's vertex 
 * buffer, vertex attributes, and index buffers and to just provide 
 * the render system with a consisten interface from which it can 
 * extract vertex information about an object which understands how 
 * to create and bind to the correct buffers with OpenGL. Effectively,
 * this class is responsible for the geometry and layout of each object
 * that we want to render.
 * 
 * Mesh class is NOT responsible for the colors, textures, materials, 
 * uniforms, shaders, or any other information (such as lighting) that
 * is involved in how the object looks when its rendered.
 */

#include "Mesh.hpp"


namespace OpenGlTutorial
{

    Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices)
                : m_vb(vertices.data(), vertices.size()*sizeof(GLfloat))
                , m_ib(indices.data(),  indices.size()*sizeof(GLuint))
    {
        numVerts = vertices.size();
        numInds = indices.size();
    }

    void Mesh::Bind() const
    {
        m_va.Bind();
    }

    void Mesh::buildVAO()
    {
        m_va.Bind();      
        m_vb.Bind();
        m_ib.Bind();

        // Build VAO Attributes 
        for (auto attrib : m_attributes )
        {
            m_va.LinkAttribute(m_vb, attrib.layoutNum, attrib.numComps, GL_FLOAT,   m_stride * sizeof(float), (void*)(attrib.offset * sizeof(float)));
        }

        // Unbinding might be useless here? (See Cherno talk about unbind in OpenGL)
        m_va.Unbind();
        m_vb.Unbind();
        m_ib.Unbind();
    }

    void Mesh::addAttribute(size_t layout_num, size_t num_components)
    {
        // Increment the Number of Attributes
        m_stride += num_components;  // Total size of vertex data for a single vertex
        
        // Store Layout, #elements, total size, stride and offsets
        VaoAttributes attribs; 

        // Populate VaoAttribute Struct
        attribs.layoutNum = layout_num;     
        attribs.numComps  = num_components;
        attribs.offset    = m_offset;

        m_offset += num_components;

        // Att attribute to vector
        m_attributes.push_back(attribs);
    }

} // namespace OpenGlTutorial
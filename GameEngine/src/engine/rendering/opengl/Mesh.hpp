/**
 * @file Mesh.hpp
 * @brief File defines class the concept of a Mesh that can be given to a Renderer to draw.
 * @author Jonathan Dorsey 
 * @date Creation date: 2025-05-11
 */

#pragma once 

// std
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

// opengl
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// local 
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

 namespace OpenGlTutorial
 {
    struct VaoAttributes
    {
       size_t layoutNum;
       size_t numComps;
       size_t offset;

    };

    class Mesh
    {
        public:
        // Mesh(const std::string meshPath);
        Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices);
        // Mesh(const Mesh& mesh);
        // Mesh(const Mesh&& mesh);
        ~Mesh()
        {
            m_va.Delete();
            m_vb.Delete();
            m_ib.Delete();
        }

        size_t getNumIndices() const { return numInds; }


        void Bind() const;

        void buildVAO();
    
        void addAttribute(size_t layout_num, size_t num_components);

        private:

        std::string m_meshPath;

        size_t m_stride = 0;
        size_t m_offset = 0;

        std::vector<VaoAttributes> m_attributes; 
        

        size_t numVerts;
        size_t numInds;

        

        // std::vector<size_t> indices;
        // std::vector<Vertex> vertices;   // Vertex class does not exist yet.

        // Vertex Buffer 
        VertexBuffer m_vb;

        // Vertex Array 
        VertexArray m_va;

        // Index Buffer
        IndexBuffer m_ib;
    };

 } // namespace OpenGlTutorial
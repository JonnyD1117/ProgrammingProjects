/**
 * @file obj_parser.hpp
 * @brief File defines class the concept of a OBJ file parser for mesh creation.
 * @author Jonathan Dorsey 
 * @date Creation date: 2025-05-12
 * 
 * OBJ files are a very easy way to create mesh geometry. This is a class attempts
 * to implement a VERY basic version of a OBJ file parser (for s & g) to prove that 
 * I understand the concept of loading mesh elements in from a well known 3D model 
 * object exchange format.
 */

#pragma once 

// std
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <optional>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>


// opengl
#include <glad/glad.h>
#include <glm/glm.hpp>

// assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// engine
#include "engine_interfaces.hpp"
#include "MeshData.hpp"
#include "MeshTypes.hpp"


namespace OpenGlTutorial
{
    class ObjParser : public virtual IMeshParser
    {
        public: 

        //******************************//
        //  Constructors & Destructors  //
        //******************************//
        ObjParser();
        virtual ~ObjParser()=default;

        //******************************//
        //  Public Methods              //
        //******************************//
        virtual std::shared_ptr<MeshData> parse(const std::filesystem::path& mesh_path) override; 

        private:

        std::vector<std::string> split(const std::string& str, char delimiter) {
            std::vector<std::string> tokens;
            std::stringstream ss(str);
            std::string item;

            while (std::getline(ss, item, delimiter)) {
                tokens.push_back(item);
            }
            return tokens;
        }

        size_t m_faceIdx    {0};
        size_t m_vertexIdx  {0};
        size_t m_normalIdx  {0};
        size_t m_textureIdx {0};

        size_t m_nonTriFaceIdx {0};
        
        std::vector<std::array<float,3>>                m_vertexVec   {};
        std::vector<std::array<float,2>>                m_textureVec  {};
        std::vector<std::array<float,3>>                m_normalVec   {};
        std::vector<std::array<std::optional<size_t>,3>> m_triFaceVec {};
        std::vector<std::string>               m_non_triangular_faces {};

        std::vector<MeshVertex> vertices; 
        std::vector<size_t>     indices;


        bool isFlat { false };
    };    
}
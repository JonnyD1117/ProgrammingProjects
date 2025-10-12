/**
 * @file assimp_parser.hpp
 * @brief Use ASSIMP to parse Mesh files.
 * @author Jonathan Dorsey 
 * @date Creation date: 2025-05-12
 * 
 * ASSIMP is a mesh parsing library that can be used to parse different mesh
 * files. It is useful as a backup parser; however, in this project I want
 * to try a to write my own parsers and merely "default" to ASSIMP as a 
 * backup.
 */

#pragma once 

// std
#include <filesystem>
#include <iostream>
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
    class AssimpParser : public virtual IMeshParser
    {
        public: 

        //******************************//
        //  Constructors & Destructors  //
        //******************************//
        AssimpParser();
        virtual ~AssimpParser()=default;

        //******************************//
        //  Public Methods              //
        //******************************//
        virtual std::shared_ptr<MeshData> parse(const std::filesystem::path& mesh_path) override; 

        private:

        std::vector<MeshVertex> vertices; 
        std::vector<size_t>     indices;

        Assimp::Importer importer;
    };    
}
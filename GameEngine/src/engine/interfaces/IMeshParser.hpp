/**
 * @file IMeshParser.hpp
 * @brief Interace to define a Mesh Parser.
 * @author Jonathan Dorsey 
 * @date Creation date: 2025-05-27
 * 
 */

#pragma once 


// std 
#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>
#include <string> 

// opengl
#include <glad/glad.h>
#include <glm/glm.hpp>

// local 
#include "MeshData.hpp"

namespace OpenGlTutorial
{
    class IMeshParser
    {
        public:
        IMeshParser()=default;
        virtual ~IMeshParser()=default;

        virtual std::shared_ptr<MeshData> parse( const std::filesystem::path& mesh_path) = 0;      

        static constexpr size_t RESERVE_SIZE = 100000;
    };
}
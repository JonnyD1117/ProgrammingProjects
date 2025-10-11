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
#include <algorithm>
#include <array>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

// opengl
#include <glad/glad.h>
#include <glm/glm.hpp>

// engine
#include "engine_interfaces.hpp"

#include "mesh_data.hpp"

namespace OpenGlTutorial
{
    class ObjParser : public virtual IMeshParser
    {
        public:
        ObjParser()=default;
        virtual ~ObjParser()=default;

        virtual std::shared_ptr<MeshData> parse(const std::filesystem::path mesh_path) override; 
        private:

        std::filesystem::path m_path;

    };    
}
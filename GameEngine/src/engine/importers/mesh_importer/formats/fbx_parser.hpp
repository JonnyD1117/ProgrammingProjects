/**
 * @file fbx_parser.hpp
 * @brief File defines class the concept of a FBX file parser for mesh creation.
 * @author Jonathan Dorsey 
 * @date Creation date: 2025-05-12
 * 
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
    class FbxParser : public virtual IMeshParser
    {
        public: 

        FbxParser()=default;
        virtual ~FbxParser()=default;

        virtual std::shared_ptr<MeshData> parse(const std::filesystem::path mesh_path) override;     
    };    
}
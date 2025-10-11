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


// local 
#include "obj_parser.hpp"

namespace OpenGlTutorial
{
    std::shared_ptr<MeshData> ObjParser::parse(const std::filesystem::path mesh_path)
    {
        return nullptr;
    }
}
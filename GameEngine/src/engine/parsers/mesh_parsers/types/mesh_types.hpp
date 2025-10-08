/**
 * @file mesh_types.hpp
 * @brief File defines types which the mesh parser will use.
 * @author Jonathan Dorsey
 * @date Creation date: 2025-05-27
 *
 */

#pragma once

// std
#include <array>
#include <cctype>
#include <list>
#include <map>
#include <string>
#include <vector>

// opengl
#include <glad/glad.h>
#include <glm/glm.hpp>

// engine

namespace OpenGlTutorial
{

struct Vertex
{
    std::array<double, 3> position;
    std::array<double, 2> texCoords;
    std::array<double, 3> normal;
    std::array<double, 3> color;
};

struct VertexCoords
{
    std::array<double, 3> data;
};

struct TextureCoords
{
    std::array<double, 2> data;
};

struct Normal
{
    std::array<double, 3> data;
};

struct Colors
{
    std::array<double, 3> data;
};

enum class FaceTypes : int
{
    INVALID = -1,
    VertexOnly = 1,
    VertexAndTextures = 2,
    VertexAndTexturesAndNormals = 3,
    VertexAndNormals = 4,
};

struct Face
{
    // REFERENCE
    /*
    f v1 v2 v3
    f v1/vt1 v2/vt2 v3/vt3
    f v1//vn1 v2//vn2 v3//vn3
    f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
    */

    // ASSUMPTION:
    // All faces have been "triangularized" before populating faces
    std::array<size_t, 3> m_vertexInds;
    std::array<size_t, 3> m_textureInds;
    std::array<size_t, 3> m_normalInds;

    FaceTypes m_type = FaceTypes::INVALID;

    // void vertexNormals()
};

} // namespace OpenGlTutorial
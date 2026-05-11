/**
 * @file MeshTypes.hpp
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

struct MeshVertex
{
    std::array<float, 3> position;
    std::array<float, 2> texture;
    std::array<float, 3> normal;
    std::array<float, 3> color;
};

struct VertexCoords
{
    std::array<float, 3> data;
};

struct TextureCoords
{
    std::array<float, 2> data;
};

struct Normal
{
    std::array<float, 3> data;
};

struct Colors
{
    std::array<float, 3> data;
};

enum class FaceTypes : int
{
    INVALID = -1,
    VertexOnly = 1,
    VertexAndTextures = 2,
    VertexAndTexturesAndNormals = 3,
    VertexAndNormals = 4,
};

} // namespace OpenGlTutorial
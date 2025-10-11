/**
 * @file Engine.hpp
 * @brief Engine class to run OpenGL tutorial. Handles functions like GLFW setup.
 * @author Jonathan Dorsey
 * @date Creation date: YYYY-MM-DD
 * @date Last modified: YYYY-MM-DD
 */

#pragma once 

// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// std
#include <iostream>
#include <filesystem>
#include <string>
#include <cmath>
#include <vector>

// Local 
#include "Shader.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Texture.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"

// Interfaces
#include "engine_interfaces.hpp"

// MeshManager


namespace OpenGlTutorial
{

struct Engine
{
    Engine();
    ~Engine();

    int run();

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow *window);

    // settings
    const unsigned int SRC_WIDTH = 800;
    const unsigned int SRC_HEIGHT = 800;

    const std::string m_cwd_path = std::filesystem::current_path();
    const std::string src_path = m_cwd_path + "/src";
    const std::string asset_path = src_path + "/assets";
    const std::string mesh_path  = asset_path + "/meshes";
    const std::string engine_path = src_path + "/engine";

    const std::string shader_path = engine_path + "/rendering/shaders/";
    const std::string texture_path = engine_path + "/rendering/textures/";

    GLFWwindow* window;
};

}
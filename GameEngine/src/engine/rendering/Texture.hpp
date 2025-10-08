/**
 * @file Texture.hpp
 * @brief Texture class implements logic around generation and binding of textures in OpenGL
 * @author Jonathan Dorsey
 * @date Creation date: 2025-05-07
 */

#pragma once 

// OpenGL
#include <glad/glad.h>

// std 
#include <iostream>
#include <filesystem>
#include <string>

// stb
#include "stb_image.h"

// engine 
#include "Shader.hpp"



namespace OpenGlTutorial
{
    class Texture
    {
        public:
        
        Texture(std::string texture_path, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
        ~Texture()=default;

        void texUnit(Shader& shader, std::string uniform_name, GLuint unit);

        void Bind();
        void Unbind();
        void Delete();

        GLuint ID; 
        GLenum type;
    };
} // namespace OpenGlTutorial

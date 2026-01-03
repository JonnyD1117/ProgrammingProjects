/**
 * @file Shader.hpp
 * @brief Shader class for OpenGL tutorial series.
 * @author Jonathan Dorsey 
 * @date Creation date: 2025-05-07
 */

#pragma once 

// opengl
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// #include <glm/gtx/rotate_vector.hpp>
// #include <glm/gtx/vector_angle.hpp>

// std
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <sstream>
#include <exception>

namespace OpenGlTutorial
{

class Shader
{
    public: 

    Shader(std::string vertexFile, std::string fragmentFile);
    ~Shader()=default;

    GLuint ID;

    void Bind() const;
    void Delete();

    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void setMatrix4f(const std::string& name, glm::mat4& matrix, glm::vec3 scale=glm::vec3(1.0f)) const;

    void setVect4f(const std::string& name, glm::vec4& vec) const;

    int success;
    char infoLog[512];

    
    private:
    std::string read_file_to_string(std::string filename);
};

} // end namespace OpenGlTutorial
/**
 * @file Shader.cpp
 * @brief Implementation of the class/functions defined in Shader.hpp
 * @author Jonathan Dorsey
 * @date Creation date: 2025-05-07
 * 
 * The Shader class handles of the necessary OpenGL calls and input functions,
 * uniforms, ...etc to compile GPU shader programs from shader files stored
 * locally within the project.
 */

// local
#include "Shader.hpp"

// std
#include <filesystem>


namespace OpenGlTutorial
{
    // Construct a Shader object by passing the vertex & fragment shader files names
    Shader::Shader(std::string vertexFile, std::string fragmentFile)
    {
        // Extract Vertex & Fragment Shader programs to strings
        std::string vertexProgram   = read_file_to_string(vertexFile);
        std::string fragmentProgram = read_file_to_string(fragmentFile);

        // Create Vertex Shader in OpenGL
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const char* vShaderCode = vertexProgram.c_str();

        // Pass vertex shader program into shader context & compile
        glShaderSource(vertexShader, 1, &vShaderCode, NULL);
        glCompileShader(vertexShader);

        // check for shader compile errors
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // Create Fragment Shader in OpenGL
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        const char* fShaderCode = fragmentProgram.c_str();

        // Pass fragment shader program into shader context & compile
        glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
        glCompileShader(fragmentShader);

        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // Create Shader Program
        ID = glCreateProgram();

        // Attach Vertex & Fragment Shaders to Shader Programs
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);

        // Link Shader Program
        glLinkProgram(ID);

        // check for linking errors
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // Now that the Shader is fully compiled (and referenceable via ID variable)...
        // We can delete the working vertex & fragment shaders we used to fully 
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }


    void Shader::Bind() const 
    {
        // Invoke the shader program we have created to in OpenGL
        glUseProgram(ID);
    }

    void Shader::Delete()
    {
        // Delete the shader program
        glDeleteProgram(ID);
    }

    void Shader::setBool(const std::string &name, bool value) const
    {
        Bind();
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string &name, int value) const
    {
        Bind();
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void Shader::setFloat(const std::string &name, float value) const
    {
        Bind();
        glUniform1f(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void Shader::setMatrix4f(const std::string& name, glm::mat4& matrix, glm::vec3 scale) const
    {
        Bind();
        matrix = glm::scale(matrix, scale);
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::setVect4f(const std::string& name, glm::vec4& vec) const
    {
        Bind();
        glUniform4f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y, vec.z, vec.w);
    }

    std::string Shader::read_file_to_string(std::string filename)
    {
        // Create Shader Program string 
        std::string contents;

        if ( std::filesystem::exists(filename) )
        {
            try
            {
                // Read in File and create input file stream
                std::ifstream in(filename, std::ios::binary);
                
                // If ifstream was opened and is valid Read contents to file
                if (in)
                {
                    in.seekg(0, std::ios::end);
                    contents.resize(in.tellg());
                    in.seekg(0, std::ios::beg);
                    in.read(&contents[0], contents.size());
                    in.close();
                }
            }
            catch (const std::exception& e )
            {
                std::cout << e.what() << std::endl;
                throw std::runtime_error("Could not open file");
            }
        }

        return contents;
    }

    
}
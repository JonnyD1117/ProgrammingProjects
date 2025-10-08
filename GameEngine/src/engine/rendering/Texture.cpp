/**
 * @file Texture.cpp
 * @brief Implementation of the class/functions defined in Texture.hpp
 * @author Jonathan Dorsey
 * @date Creation date: 2025-05-07
 * 
 * Texture class handles all of the necessary OpenGL & STB calls to create
 * and populate texture buffer, that is loaded from a custom image file 
 * within this project.
 */

#include "Texture.hpp"

namespace OpenGlTutorial
{
    Texture::Texture(std::string texture_path, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
    {
        // Assigns the type of the texture to the texture object
        type = texType;

        // Texture Dimensions
        int width, height, numChans;

        // Flips the image so it appears right side up
	    stbi_set_flip_vertically_on_load(true);

        // Variable to Store texture data
        unsigned char * textureData;

        // Check if Texture File exists before loading
        if (std::filesystem::exists(texture_path))
        {       
            textureData = stbi_load(texture_path.c_str(), &width, &height, &numChans,0);
        }
        else
        {
            std::cout << "TEXTURE FAILED TO LOAD" << std::endl;
        }

        // Generate Texture from OpenGL
        glGenTextures(1, &ID);

        // Assigns the texture to a Texture Unit
        glActiveTexture(slot);
        glBindTexture(texType, ID);


        // Configures the type of algorithm that is used to make the image smaller or larger
        glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Configures the way the textures repeats (if necessary)
        glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        

        if(textureData)
        {
            glTexImage2D(texType, 0, GL_RGBA, width, height, 0, format, pixelType, textureData);
            glGenerateMipmap(texType);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }

        // Free Texture data created from the raw texture image
        stbi_image_free(textureData);

        glBindTexture(texType, 0);

    }

    void Texture::texUnit(Shader& shader, std::string uniform_name, GLuint unit)
    {
        // Gets the location of the uniform
        GLuint texUni = glGetUniformLocation(shader.ID, uniform_name.c_str());

        // Shader needs to be activated before changing the value of a uniform
        shader.Bind();

        // Sets the value of the uniform
        glUniform1i(texUni, unit);
    }

    void Texture::Bind()
    {
        glBindTexture(type, ID);
    }

    void Texture::Unbind()
    {
        
    }

    void Texture::Delete()
    {
    }
}
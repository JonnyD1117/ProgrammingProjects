/**
 * @file Camera.hpp
 * @brief File defines class the concept of a Camera that controls the view within the scene.
 * @author Jonathan Dorsey 
 * @date Creation date: 2025-05-08
 */

 #pragma once 

 #define GLM_ENABLE_EXPERIMENTAL
// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

// Local 
#include "Shader.hpp"


namespace OpenGlTutorial
{
    class Camera
    {
        public: 
    
            Camera(int width, int height, glm::vec3 position);
            ~Camera()=default;
    
            void setMatrixUniform(Shader& shader, std::string uniform_name);
            
            void setPositionUniform(Shader& shader, std::string uniform_name);

            void updateMatrixParams(float FOVdeg, float nearPlane, float farPlane);
            void Inputs(GLFWwindow* window);
    
            glm::vec3 m_pos;
            glm::vec3 m_orient = glm::vec3(0.0f, 0.0f, -1.0f);
            glm::vec3 m_up     = glm::vec3(0.0f, 1.0f, 0.0f);

            glm::mat4 m_cameraMatrix = glm::mat4(1.0f);
    
            int m_width; 
            int m_height; 
            float m_speed = 0.1f;
            float m_sensitivity = 100.0f;

            // Prevents the camera from jumping around when first clicking left click
	        bool firstClick = true;
    };
}
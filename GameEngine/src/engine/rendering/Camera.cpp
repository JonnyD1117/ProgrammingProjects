/**
 * @file Camera.cpp
 * @brief Implementation of the class/functions defined in Camera.hpp
 * @author Jonathan Dorsey
 * @date Creation date: 2025-05-08
 * 
 * This class implements the main abstraction from local coordinates to camera coordinates
 * via the model, view, and project matrix calculations
 */


#include "Camera.hpp"


namespace OpenGlTutorial
{
	Camera::Camera(int width, int height, glm::vec3 position) : m_width {width}, m_height{height}, m_pos{position}
	{

	}

	void Camera::updateMatrixParams(float FOVdeg, float nearPlane, float farPlane)
	{
		// Initialize TX matrices to non-zero values
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		// Compute Transformations
		view = glm::lookAt(m_pos, m_pos + m_orient, m_up);
		proj = glm::perspective(glm::radians(FOVdeg), (float)(m_width/m_height), nearPlane, farPlane);

		m_cameraMatrix = proj * view;
	}

	void Camera::setMatrixUniform(Shader& shader, std::string uniform_name)
	{
		shader.Bind();
		// Set Camera "proj*view" matrix and export to Shader program
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform_name.c_str()), 1, GL_FALSE, glm::value_ptr(m_cameraMatrix));
	}

	void Camera::setPositionUniform(Shader& shader, std::string uniform_name="camPos")
	{
		shader.Bind();
		// Set Camera Position Uniform
		glUniform3f(glGetUniformLocation(shader.ID, uniform_name.c_str()), m_pos.x, m_pos.y, m_pos.z);
	}

	void Camera::Inputs(GLFWwindow* window)
	{
		// Handles key inputs
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			m_pos += m_speed * m_orient;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			m_pos += m_speed * -glm::normalize(glm::cross(m_orient, m_up));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			m_pos += m_speed * -m_orient;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			m_pos += m_speed * glm::normalize(glm::cross(m_orient, m_up));
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			m_pos += m_speed * m_up;
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			m_pos += m_speed * -m_up;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			m_speed = 0.4f;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		{
			m_speed = 0.1f;
		}


		// Handles mouse inputs
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			// Hides mouse cursor
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			// Prevents camera from jumping on the first click
			if (firstClick)
			{
				glfwSetCursorPos(window, (m_width / 2), (m_height / 2));
				firstClick = false;
			}

			// Stores the coordinates of the cursor
			double mouseX;
			double mouseY;
			// Fetches the coordinates of the cursor
			glfwGetCursorPos(window, &mouseX, &mouseY);

			// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
			// and then "transforms" them into degrees 
			float rotX = m_sensitivity * (float)(mouseY - (m_height / 2)) / m_height;
			float rotY = m_sensitivity * (float)(mouseX - (m_width / 2)) / m_width;

			// Calculates upcoming vertical change in the m_orient
			glm::vec3 newOrientation = glm::rotate(m_orient, glm::radians(-rotX), glm::normalize(glm::cross(m_orient, m_up)));

			// Decides whether or not the next vertical m_orient is legal or not
			if (std::abs(glm::angle(newOrientation, m_up) - glm::radians(90.0f)) <= glm::radians(85.0f))
			{
				m_orient = newOrientation;
			}

			// Rotates the m_orient left and right
			m_orient = glm::rotate(m_orient, glm::radians(-rotY), m_up);

			// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
			glfwSetCursorPos(window, (m_width / 2), (m_height / 2));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			// Unhides cursor since camera is not looking around anymore
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			// Makes sure the next time the camera looks around it doesn't jump
			firstClick = true;
		}
	}

}
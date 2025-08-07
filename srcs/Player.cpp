#include "../includes/Player.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <iostream>

Player::Player(const glm::vec3& pos, float moveSpeed, float mouseSensitivity)
    : Camera(pos, glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), m_firstMouse(true), m_lastX(400), m_lastY(300)
{
    m_speed = moveSpeed;
    m_sensitivity = mouseSensitivity;
}

void Player::update(float deltaTime)
{
    // Update logic can be added here
    // For now, this is where any player-specific updates would go
    (void)deltaTime; // Suppress unused parameter warning
}

void Player::processInput(GLFWwindow* window, float deltaTime)
{
	static bool inPause = false;
    // Handle keyboard input
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
        processKeyboard(FORWARD, deltaTime);
	}
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
        processKeyboard(BACKWARD, deltaTime);
	}
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
        processKeyboard(LEFT, deltaTime);
	}
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
        processKeyboard(RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		if (inPause)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		inPause = -inPause;
	}

        
    // ESC to close
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Player::processMouse(double xpos, double ypos)
{
    if (m_firstMouse)
    {
        initMouseTracking(xpos, ypos);
        return;
    }

    float xoffset = m_lastX - xpos;
    float yoffset = m_lastY - ypos;

    m_lastX = xpos;
    m_lastY = ypos;

    processMouseMovement(xoffset, yoffset);
}

glm::mat4 Player::getProjectionMatrix(float aspect, float fov) const
{
    return glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
}

void Player::initMouseTracking(double xpos, double ypos)
{
    m_lastX = xpos;
    m_lastY = ypos;
    m_firstMouse = false;
}

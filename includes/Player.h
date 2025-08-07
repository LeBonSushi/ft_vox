#pragma once

#include "Camera.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Player : public Camera
{
public:
    // Constructor
    Player(const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 3.0f), 
           float moveSpeed = 5.0f, 
           float mouseSensitivity = 0.1f);
    
    // Update methods
    void update(float deltaTime);
    void processInput(GLFWwindow* window, float deltaTime);
    void processMouse(double xpos, double ypos);
    
    // Render related
    glm::mat4 getProjectionMatrix(float aspect, float fov = 45.0f) const;
    
    // Getters/Setters
    void setPosition(const glm::vec3& pos) { m_position = pos; }
    void setSpeed(float newSpeed) { m_speed = newSpeed; }
    void setSensitivity(float newSensitivity) { m_sensitivity = newSensitivity; }
    
private:
    // Mouse handling
    bool m_firstMouse;
    double m_lastX, m_lastY;
    
    // Initialize mouse tracking
    void initMouseTracking(double xpos, double ypos);
};
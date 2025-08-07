#include "../includes/Camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <algorithm>

Camera::Camera(const glm::vec3& position, const glm::quat& orientation) 
    : m_position(position), m_orientation(orientation), m_speed(5.0f), m_sensitivity(0.1f) {}


glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(m_position, m_position + getFront(), getUp());
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = m_speed * deltaTime;
    
    switch (direction) {
        case FORWARD:
            m_position += getFront() * velocity;
            break;
        case BACKWARD:
            m_position -= getFront() * velocity;
            break;
        case LEFT:
            m_position -= getRight() * velocity;
            break;
        case RIGHT:
            m_position += getRight() * velocity;
            break;
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
    xoffset *= m_sensitivity;
    yoffset *= m_sensitivity;
    
    glm::quat yawRotation = glm::angleAxis(glm::radians(xoffset), glm::vec3(0.0f, 1.0f, 0.0f));
    
    glm::vec3 right = getRight();
    right.y = 0.0f;
    if (glm::length(right) > 0.001f) {
        right = glm::normalize(right);
    } else {
        right = glm::vec3(1.0f, 0.0f, 0.0f);
    }
    
    glm::quat pitchRotation = glm::angleAxis(glm::radians(yoffset), right);
    
    glm::quat newOrientation = pitchRotation * yawRotation * m_orientation;
    
    glm::vec3 newFront = newOrientation * glm::vec3(0, 0, -1);
    float pitchAngle = glm::degrees(asin(glm::clamp(newFront.y, -1.0f, 1.0f)));
    
    if (pitchAngle > -89.0f && pitchAngle < 89.0f) {
        m_orientation = glm::normalize(newOrientation);
        
        glm::vec3 front = getFront();
        glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 correctedRight = glm::normalize(glm::cross(front, worldUp));
        glm::vec3 correctedUp = glm::cross(correctedRight, front);
        
        glm::mat3 rotMatrix(correctedRight, correctedUp, -front);
        m_orientation = glm::normalize(glm::quat_cast(rotMatrix));
    } else {
        m_orientation = glm::normalize(yawRotation * m_orientation);
    }
}
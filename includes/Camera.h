#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

enum CameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera {
public:
    glm::vec3 m_position;
    glm::quat m_orientation;

    float m_speed, m_sensitivity;

	Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), 
           const glm::quat& orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));

    glm::mat4 getViewMatrix();
    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);
private:
    glm::vec3 getFront() const { return m_orientation * glm::vec3(0, 0, -1); }
    glm::vec3 getRight() const { return m_orientation * glm::vec3(1, 0, 0); }
    glm::vec3 getUp() const { return m_orientation * glm::vec3(0, 1, 0); }
};

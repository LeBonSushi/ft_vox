#pragma once

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.h"

class Cube
{
public:
    Cube();
    ~Cube();
    
    // Initialize the cube geometry
    void init();
    
    // Render the cube
    void render(const Shader& shader, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
    
    // Cleanup
    void cleanup();
    
    // Setters for cube properties
    void setColor(const glm::vec3& color) { m_color = color; }
    void setPosition(const glm::vec3& position) { m_position = position; }
    void setScale(const glm::vec3& scale) { m_scale = scale; }
    void setRotation(const glm::vec3& rotation) { m_rotation = rotation; }
    
    // Getters
    glm::vec3 getColor() const { return m_color; }
    glm::vec3 getPosition() const { return m_position; }
    glm::vec3 getScale() const { return m_scale; }
    glm::vec3 getRotation() const { return m_rotation; }
    
    // Calculate model matrix based on transformation
    glm::mat4 getModelMatrix() const;
    
private:
    unsigned int m_VAO, m_VBO, m_EBO;
    bool m_initialized;
    
    // Cube properties
    glm::vec3 m_color;
    glm::vec3 m_position;
    glm::vec3 m_scale;
    glm::vec3 m_rotation; // Euler angles in radians
    
    // Setup cube geometry
    void setupCubeGeometry();
};

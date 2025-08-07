#pragma once

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

class Shader
{
public:
    // Constructor
    Shader();
    ~Shader();
    
    // Shader compilation and linking
    bool loadFromString(const std::string& vertexSource, const std::string& fragmentSource);
    bool loadFromFile(const std::string& vertexPath, const std::string& fragmentPath);
    
    // Use/activate the shader
    void use() const;
    void unbind() const;
    
    // Utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    
    // Getters
    unsigned int getID() const { return m_programID; }
    bool isValid() const { return m_programID != 0; }
    
private:
    unsigned int m_programID;
    mutable std::unordered_map<std::string, int> m_uniformLocationCache;
    
    // Helper methods
    unsigned int compileShader(unsigned int type, const std::string& source);
    bool linkProgram(unsigned int vertexShader, unsigned int fragmentShader);
    int getUniformLocation(const std::string& name) const;
    void checkCompileErrors(unsigned int shader, const std::string& type);
    std::string readFile(const std::string& filepath);
};

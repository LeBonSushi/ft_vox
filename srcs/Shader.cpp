#include "../includes/Shader.h"
#include "../includes/Logger.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader() : m_programID(0)
{
}

Shader::~Shader()
{
    if (m_programID != 0)
    {
        glDeleteProgram(m_programID);
    }
}

bool Shader::loadFromString(const std::string& vertexSource, const std::string& fragmentSource)
{
    // Compile vertex shader
    unsigned int vertex = compileShader(GL_VERTEX_SHADER, vertexSource);
    if (vertex == 0) return false;
    
    // Compile fragment shader
    unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (fragment == 0)
    {
        glDeleteShader(vertex);
        return false;
    }
    
    // Link shaders
    bool success = linkProgram(vertex, fragment);
    
    // Clean up individual shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    return success;
}

bool Shader::loadFromFile(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexSource = readFile(vertexPath);
    std::string fragmentSource = readFile(fragmentPath);
    
    if (vertexSource.empty() || fragmentSource.empty())
    {
        Logger::log(LOG_ERROR, "Failed to read shader files");
        return false;
    }
    
    return loadFromString(vertexSource, fragmentSource);
}

void Shader::use() const
{
    if (m_programID != 0)
    {
        glUseProgram(m_programID);
    }
}

void Shader::unbind() const
{
    glUseProgram(0);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(getUniformLocation(name), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    
    // Check compilation errors
    std::string typeStr = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
    checkCompileErrors(shader, typeStr);
    
    // Check if compilation was successful
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glDeleteShader(shader);
        return 0;
    }
    
    return shader;
}

bool Shader::linkProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    m_programID = glCreateProgram();
    glAttachShader(m_programID, vertexShader);
    glAttachShader(m_programID, fragmentShader);
    glLinkProgram(m_programID);
    
    checkCompileErrors(m_programID, "PROGRAM");
    
    // Check linking
    int success;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glDeleteProgram(m_programID);
        m_programID = 0;
        return false;
    }
    
    return true;
}

int Shader::getUniformLocation(const std::string& name) const
{
    // Check cache first
    auto it = m_uniformLocationCache.find(name);
    if (it != m_uniformLocationCache.end())
    {
        return it->second;
    }
    
    int location = glGetUniformLocation(m_programID, name.c_str());
    m_uniformLocationCache[name] = location;
    
    if (location == -1)
    {
        Logger::log(LOG_WARNING, "Uniform '", name, "' not found in shader");
    }
    
    return location;
}

void Shader::checkCompileErrors(unsigned int shader, const std::string& type)
{
    int success;
    char infoLog[1024];
    
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            Logger::log(LOG_ERROR, "Shader compilation error (", type, "): ", infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            Logger::log(LOG_ERROR, "Program linking error: ", infoLog);
        }
    }
}

std::string Shader::readFile(const std::string& filepath)
{
    std::ifstream file;
    std::stringstream buffer;
    
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try
    {
        file.open(filepath);
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
    }
    catch (std::ifstream::failure& e)
    {
        Logger::log(LOG_ERROR, "Failed to read file: ", filepath, " - ", e.what());
        return "";
    }
}

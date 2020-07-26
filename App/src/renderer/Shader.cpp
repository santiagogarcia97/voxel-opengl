#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"

Shader::Shader(const char* shader_name)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(shadersPath + shader_name + ".vert");
        fShaderFile.open(shadersPath + shader_name + ".frag");
    	
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& ex)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const auto* vShaderCode = vertexCode.c_str();
    const auto* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    check_compile_errors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    check_compile_errors(fragment, "FRAGMENT");
    // shader Program
    m_Id = glCreateProgram();
    glAttachShader(m_Id, vertex);
    glAttachShader(m_Id, fragment);
    glLinkProgram(m_Id);
    check_compile_errors(m_Id, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() const
{
    glUseProgram(m_Id);
}

void Shader::set_bool(const std::string& name, const bool value) const
{
    glUniform1i(glGetUniformLocation(m_Id, name.c_str()), (int)value);
}
void Shader::set_int(const std::string& name, const int value) const
{
    glUniform1i(glGetUniformLocation(m_Id, name.c_str()), value);
}
void Shader::set_float(const std::string& name, const float value) const
{
    glUniform1f(glGetUniformLocation(m_Id, name.c_str()), value);
}
void Shader::set_mat4(const std::string& name, const glm::mat4* value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_Id, name.c_str()), 1, GL_FALSE, glm::value_ptr(*value));
}


void Shader::check_compile_errors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    }
}

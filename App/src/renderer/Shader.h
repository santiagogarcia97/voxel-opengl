#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader
{
public:
    Shader(const char* shader_name);
    void use() const;
    void set_bool(const std::string& name, const bool value) const;
    void set_int(const std::string& name, const int value) const;
    void set_float(const std::string& name, const float value) const;
    void set_mat4(const std::string& name, const glm::mat4* value) const;

private:
    unsigned int m_Id;
    const std::string shadersPath = "res/shaders/";
    static void check_compile_errors(unsigned int shader, std::string type);
};
#endif
#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <string>

class ShaderLoader
{
    public:
        ShaderLoader(const char* vertex_path, const char* frag_path);
        void use();
        void set_bool(const std::string& name, bool value) const;
        void set_int(const std::string& name, int value) const;
        void set_float(const std::string& name, float value) const;
        void set_mat4(const std::string& name, glm::mat4* value) const;

    private:
        unsigned int m_Id;
        void check_compile_errors(unsigned int shader, std::string type);
};
#endif
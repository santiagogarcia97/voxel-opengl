#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <string>

class ShaderLoader
{
    public:
        unsigned int ID;
        ShaderLoader(const char* vertexPath, const char* fragmentPath);
        void use();
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;

    private:
        void checkCompileErrors(unsigned int shader, std::string type);
};
#endif
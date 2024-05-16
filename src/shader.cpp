#include "shader.h"
#include "global_includes.h"
#include <fstream>
#include <iostream>
#include <sstream>

constexpr uint16_t mini_str2int(const char* str) {
    return (static_cast<uint16_t>(*(str))<<8)|static_cast<uint16_t>(*str+1);
}

int Shader::load_and_compile_from_path(const char* path) {
    {
        const char* p = path, *tmp = p;
        while (*(p++));

        if (tmp - p >= 3) {
            switch (mini_str2int(p-2)) {
                case mini_str2int("fs"): shader_type = GL_FRAGMENT_SHADER; break;
                case mini_str2int("vs"): shader_type = GL_VERTEX_SHADER; break;
                default: return -1;
            }
        }
        else return -1;
    }
    std::ifstream fs(path);
        if (!fs || fs.bad())
        {
            std::cout << "Failed to open file" << std::endl;
            return -1;
        }
        std::stringstream buffer;
        std::string line;
        while (std::getline(fs, line))
        {
            buffer << line << std::endl;
        }
        std::string str = buffer.str();
        const char *src = str.c_str();
        shader_id = glCreateShader(shader_type);
        glShaderSource(shader_id, 1, &src, NULL);
        glCompileShader(shader_id);

        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << "PATH: " << path
            << '\n' << infoLog << std::endl;
        }
}

Shader::Shader(const char* path) {
    if (load_and_compile_from_path(path)) {
        throw(std::runtime_error("couldn't load/compile shader from path"));
    }
}

Shader::~Shader() {
    glDeleteShader(shader_id);
}
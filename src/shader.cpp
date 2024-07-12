#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

Shader::Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath)
{
    std::string vertexSource = LoadFromFile(vertexPath);
    std::string fragmentSource = LoadFromFile(fragmentPath);
    if (geometryPath != nullptr)
    {
        std::string geometrySource = LoadFromFile(geometryPath);
        Compile(vertexSource.c_str(), fragmentSource.c_str(), geometrySource.c_str());
    }
    else
    {
        Compile(vertexSource.c_str(), fragmentSource.c_str(), nullptr);
    }
}

Shader::~Shader()
{
    glDeleteProgram(this->ID);
}

Shader &Shader::Use()
{
    glUseProgram(this->ID);
    return *this;
}

void Shader::SetFloat(const char *name, float value, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform1f(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetInteger(const char *name, int value, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform1i(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetVector2f(const char *name, float x, float y, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}
void Shader::SetVector2f(const char *name, const glm::vec2 &value, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}
void Shader::SetVector3f(const char *name, float x, float y, float z, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
void Shader::SetVector3f(const char *name, const glm::vec3 &value, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}
void Shader::SetVector4f(const char *name, float x, float y, float z, float w, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}
void Shader::SetVector4f(const char *name, const glm::vec4 &value, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}
void Shader::SetMatrix4(const char *name, const glm::mat4 &matrix, bool useShader)
{
    if (useShader)
        this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, &matrix[0][0]);
}

void Shader::SetMatrix4Array(const char*name, const glm::mat4* matrices, unsigned count, bool useShader) {
    if (useShader)
        this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), count, false, &matrices[0][0][0]);
}

void Shader::SetIntegerArray(const char*name, const int* values, unsigned count, bool useShader) {
    if (useShader)
        this->Use();
    glUniform1iv(glGetUniformLocation(this->ID, name), count, values);
}

void Shader::SetVector3fArray(const char*name, const glm::vec3* values, unsigned count, bool useShader) {
    if (useShader)
        this->Use();
    glUniform3fv(glGetUniformLocation(this->ID, name), count, &values[0][0]);
}

void Shader::SetTexture(const char *name, GLuint texture, GLint unit, bool useShader)
{
    if (useShader)
        this->Use();
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(this->ID, name), unit);
}

void Shader::SetTextureArray(const char *name, GLuint textureArray, GLint unit, bool useShader)
{
    if (useShader)
        this->Use();
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
    glUniform1i(glGetUniformLocation(this->ID, name), unit);
}

std::string Shader::LoadFromFile(const char *path)
{
    std::ifstream fs(path);
    if (!fs || fs.bad())
    {
        std::cerr << "Failed to open file: " << path << " Reason: " << std::strerror(errno) << std::endl;
        return "";
    }
    std::stringstream buffer;
    std::string line;
    while (std::getline(fs, line))
    {
        buffer << line << std::endl;
    }
    return buffer.str();
}

void Shader::Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource)
{
    unsigned int sVertex, sFragment, gShader;
    // vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");
    // fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");
    // if geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
    }
    this->ID = glCreateProgram();
    glAttachShader(this->ID, sVertex);
    glAttachShader(this->ID, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(this->ID, gShader);
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);
}
void Shader::checkCompileErrors(unsigned int object, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
    }
}
#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "uniform_buffer.h"

class Shader
{
    public:
        unsigned int ID;
        Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath = nullptr);
        ~Shader();
        Shader& Use();
        // geometry source code is optional

        void SetFloat(const char* name, float value, bool useShader = false);
        void SetInteger(const char* name, int value, bool useShader = false);
        void SetVector2f(const char* name, float x, float y, bool useShader = false);
        void SetVector2f(const char* name, const glm::vec2 &value, bool useShader = false);
        void SetVector3f(const char* name, float x, float y, float z, bool useShader = false);
        void SetVector3f(const char* name, const glm::vec3 &value, bool useShader = false);
        void SetVector4f(const char* name, float x, float y, float z, float w, bool useShader = false);
        void SetVector4f(const char* name, const glm::vec4 &value, bool useShader = false);
        void SetMatrix4(const char* name, const glm::mat4 &matrix, bool useShader = false);

        std::vector<UBO_ShaderAttachment*> ubos;
    private:
        std::string LoadFromFile(const char *path);
        void Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr);
        void checkCompileErrors(unsigned int object, std::string type);
};
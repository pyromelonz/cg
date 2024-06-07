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
        virtual Shader& Use();
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

    private:
        std::string LoadFromFile(const char *path);
        void Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr);
        void checkCompileErrors(unsigned int object, std::string type);
};

enum UBO_GLOBALS : uint32_t {
    MVP_BLOCK = 1,
};

template<> uint8_t
bitCount<0> = 0;

template<uint32_t n>
uint8_t bitCount = bitCount<(n>>1)> + (n&1);

template <uint32_t ubo_globals>
class UBO_Shader : public Shader {
    using Shader::Shader;
    UBO_ShaderAttachment ubos[bitCount<ubo_globals>]; //how do I initialise these,
    //it would be cool to associate a type to each UBO_GLOBALS entry.
    template<UBO_GLOBALS g> uint8_t index = bitCount<ubo_globals & (g-1)>;
    public:
    template<UBO_GLOBALS global>
    UBO_ShaderAttachment* global() {
        return static_cast<bool>(global & ubo_globals) * index<global>;
    }
    void Use() override {
        for (auto ubo : ubos)
            ubo->shaderBind(ID);
        return Shader::Use();
    }
    //dear god
    };

typedef UBO_Shader<MVP_BLOCK> Basic3D_Shader;
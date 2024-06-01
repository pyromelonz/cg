#pragma once
#include <glad/glad.h>
#include <cstring>
#include <string>

GLuint uboMatrices;

class UBO_ShaderAttachment {
    unsigned ubo;
    std::string shaderIdentifier;
    public:
    void shaderBind(unsigned shaderProgram);
    UBO_ShaderAttachment(std::string shaderIdentifier);
};

template <typename uboStruct>
struct UniformBuffer : public UBO_ShaderAttachment {
    uboStruct data;
    void uploadBufferData() {
        glBindBuffer(GL_UNIFORM_BUFFER, ubo);
        glBufferData(GL_UNIFORM_BUFFER,sizeof(uboStruct),&data, GL_DYNAMIC_DRAW)
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
    UniformBuffer(std::string shaderIdentifier, uboStruct* data) : UBO_ShaderAttachment(shaderIdentifier) {
        UniformBuffer();
        memcpy(&this->data,data,sizeof(uboStruct));
        uploadBufferData()
    }    
};
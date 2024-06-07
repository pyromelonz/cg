#pragma once
#include <glad/glad.h>
#include <cstring>
#include <string>
#include <global_defines.h>

GLuint uboMatrices;

class UBO_ShaderAttachment {
    unsigned ubo;
    std::string shaderIdentifier;
    public:
    void shaderBind(unsigned shaderProgram);
    UBO_ShaderAttachment(std::string shaderIdentifier);
    ~UBO_ShaderAttachment();
};

template <typename uboStruct>
struct UniformBuffer : public UBO_ShaderAttachment {
    uboStruct data;
    void uploadBufferData() {
        glBindBuffer(GL_UNIFORM_BUFFER, ubo);
        glBufferData(GL_UNIFORM_BUFFER,sizeof(uboStruct),&data, GL_DYNAMIC_DRAW)
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
    UniformBuffer(std::string shaderIdentifier) : UBO_ShaderAttachment(shaderIdentifier) {}
    UniformBuffer(std::string shaderIdentifier, uboStruct* data) : UBO_ShaderAttachment(shaderIdentifier) {
        memcpy(&this->data,data,sizeof(uboStruct));
        uploadBufferData()
    }
};

struct MVP_Block {
    CGMAT4 model, view, projection;
};

typedef UniformBuffer<MVP_Block> MVP_Block_Buffer;

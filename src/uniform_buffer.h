#pragma once
#include <glad/glad.h>
#include <cstring>
#include <string>
#include <global_defines.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class UBO_ShaderAttachment {
    protected:
    unsigned ubo;
    std::string shaderIdentifier;
    public:
    virtual void shaderBind(unsigned shaderProgram);
    UBO_ShaderAttachment(std::string shaderIdentifier);
    ~UBO_ShaderAttachment();
};

template <typename uboStruct>
struct UniformBuffer : public UBO_ShaderAttachment {
    uboStruct data;
    void uploadBufferData() {
        glBindBuffer(GL_UNIFORM_BUFFER, ubo);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(uboStruct),&data, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
    UniformBuffer(std::string shaderIdentifier) : UBO_ShaderAttachment(shaderIdentifier) {}
    UniformBuffer(std::string shaderIdentifier, uboStruct* data) : UBO_ShaderAttachment(shaderIdentifier) {
        memcpy(&this->data,data,sizeof(uboStruct));
        uploadBufferData();
    }
};

struct MVP_Block {
    CGMAT4 model = CGMAT4(),
        view = glm::lookAt(CGXYZ(0), CGXYZ(0), CGXYZ(0.0,1.0,0.0)),
        projection = glm::perspective(glm::radians(45.0f),1.0f,0.1f, 100.0f);
    MVP_Block(CGMAT4 model, CGMAT4 view, CGMAT4 projection);
    MVP_Block() = default;
};

typedef UniformBuffer<MVP_Block> MVP_Block_Buffer;

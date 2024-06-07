#include "uniform_buffer.h"
#include <stdexcept>

void UBO_ShaderAttachment::shaderBind(unsigned shaderProgram) {
        GLuint uniformBlockIndex = glGetUniformBlockIndex(shaderProgram, shaderIdentifier.c_str());
        if (uniformBlockIndex == GL_INVALID_INDEX) {
            throw std::runtime_error("invalid shader uniform identifier");
        }
        glUniformBlockBinding(shaderProgram, uniformBlockIndex, 0); // Bind the block index to binding point 0
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);
    }


UBO_ShaderAttachment::UBO_ShaderAttachment(std::string shaderIdentifier) : shaderIdentifier(shaderIdentifier) {
    glGenBuffers(1, &ubo);
}

UBO_ShaderAttachment::~UBO_ShaderAttachment() {
    glDeleteBuffers(1, &ubo);
}
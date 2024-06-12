#include "shader_manager.h"
#include <memory>
#include "uniform_buffer.h"

static ShaderManager shm;

ShaderManager* const ShaderManager::instance = &shm;

Shader* ShaderManager::getModelShader() const {
    static MVP_Block_Buffer mvp_ubo("MVP_BLOCK");
    static UBO_Shader modelShader(&mvp_ubo,1,"assets/shaders/basic.vs", "assets/shaders/basic.fs", nullptr);
    return &modelShader;
}
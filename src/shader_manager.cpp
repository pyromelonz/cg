#include "shader_manager.h"
#include <memory>

static ShaderManager shm;

ShaderManager* const ShaderManager::instance = &shm;

Shader* ShaderManager::getModelShader() const {
    
    static Basic3D_Shader modelShader("assets/shaders/basic.vs", "assets/shaders/basic.fs", nullptr);
    return &modelShader;
}
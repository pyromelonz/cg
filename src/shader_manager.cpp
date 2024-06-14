#include "shader_manager.h"
#include <memory>
#include "uniform_buffer.h"

static ShaderManager shm;

ShaderManager *const ShaderManager::instance = &shm;

static MVP_Block_Buffer *mvp_ubo = nullptr;

Shader *ShaderManager::getModelShader() const
{
    if (!mvp_ubo)
        mvp_ubo = new MVP_Block_Buffer("MVP_BLOCK");

    static auto *peen = static_cast<UBO_ShaderAttachment *>(mvp_ubo);
    static UBO_Shader modelShader(&peen, 1, "assets/shaders/basic.vs", "assets/shaders/basic.fs", nullptr);
    return &modelShader;
}

ShaderManager::~ShaderManager()
{
    if (mvp_ubo)
        delete mvp_ubo;
}
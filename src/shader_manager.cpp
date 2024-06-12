#include "shader_manager.h"
#include <memory>
#include "uniform_buffer.h"

static ShaderManager shm;

ShaderManager* const ShaderManager::instance = &shm;

static MVP_Block mvp(glm::identity<CGMAT4>(),
glm::lookAt(CGXYZ(0), CGXYZ(0), CGXYZ(0.0,1.0,0.0))
,glm::perspective(1.0,1.0,0.3, 0.9));

static MVP_Block_Buffer mvp_ubo ("MVP_BLOCK", &mvp);

Shader* ShaderManager::getModelShader() const {
    auto peen = static_cast<UBO_ShaderAttachment*>(&mvp_ubo);
    static UBO_Shader modelShader(&peen,1,"assets/shaders/basic.vs", "assets/shaders/basic.fs", nullptr);
    return &modelShader;
}

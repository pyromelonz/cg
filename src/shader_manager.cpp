#include "shader_manager.h"

void ShaderManager::addShaderGlobal(std::unique_ptr<ShaderGlobal>&& global) {
    globals.push_back(std::move(global));
}

void ShaderManager::updateGlobals() const{
    for (const auto s : shaders) {
        s->Use();
        for (const auto& g : globals)
            g->shaderUpdateUniform();
    }
}

ShaderManager ShaderManager::instance;
#pragma once
#include "shader.h"

// class to handle shaders, return shaders to use
// for a given render object and so on

struct ShaderManager {
    static ShaderManager* const instance;
    ShaderManager operator=(const ShaderManager&) = delete;
    ShaderManager(const ShaderManager&) = delete;
    ShaderManager() = default;
    ~ShaderManager();

    Shader* getModelShader() const;
};
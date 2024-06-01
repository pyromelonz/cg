#pragma once
#include <vector>
#include "shader.h"
#include <memory>

struct ShaderGlobal {
    virtual void shaderUpdateUniform() = 0;
    virtual unsigned layoutLocation() const = 0;
};

template <typename uniform_t>
class TypedShaderGlobal : public ShaderGlobal {
    protected:
    uniform_t uniform;
    public:
    void setUniform(const uniform_t& uniform) {
        this->uniform = uniform;
    }
};

class ShaderManager {
    std::vector<Shader*> shaders;
    std::vector<std::unique_ptr<ShaderGlobal>> globals;
    friend Shader;
    public:
    static ShaderManager instance;
    void addShaderGlobal(std::unique_ptr<ShaderGlobal>&& global);
    ShaderManager(const ShaderManager&) = delete;
    ShaderManager operator=(const ShaderManager&) = delete;
    ShaderManager() = default;
    void updateGlobals() const;
};
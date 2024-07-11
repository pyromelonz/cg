#pragma once

#include <memory>

#include "entity.h"
#include "shader.h"

class ShaderManager {

    struct ShadowMap {
        unsigned depthmap;
        ShadowMap();
    };

    struct Pass {
        Shader* pShader;
        GLuint frameBuffer = 0;
        Pass(Shader* pShader) : pShader(pShader){};
        virtual void prepare(Shader*) = 0;
    };

    struct ShadowMapPass : public Pass {
        ShadowMapPass(Entity* lightSource);
        ShadowMap shadowMap;
        Entity* lightSource;
        void prepare(Shader* pShader) override;
    };

    struct MainShaderPass : public Pass {
        using Pass::Pass;
        void prepare(Shader* pShader) override;
    };

    private:
    std::vector<std::unique_ptr<Pass>> passes;
    Shader* currentShader;

    public:
    ~ShaderManager();
    Shader* CurrentShader() const;
    Shader* mainShader = nullptr;

    private:
    ShaderManager();
    Shader* shadowMapShader = nullptr;
    unsigned WIDTH, HEIGHT;

    static ShaderManager shaderManager;

    public:
    void Init();
    void wndResize(unsigned w, unsigned h);

    bool PreparePass();

    void* RegisterLightSource(Entity* lightSource);
    void UnregisterLightSource(void* id);

    void UploadShadowMaps();

    ShaderManager(const ShaderManager&) = delete;
    ShaderManager operator=(const ShaderManager&) = delete;
    static ShaderManager& instance();

};
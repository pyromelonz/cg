#include "shader_manager.h"
#include "components/camera.h"
#include "components/light.h"


static constexpr unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

ShaderManager ShaderManager::shaderManager;

ShaderManager& ShaderManager::instance() {
    return shaderManager;
}

ShaderManager::ShadowMapPass::ShadowMapPass(Entity* lightSource) : Pass(ShaderManager::shaderManager.shadowMapShader)
{
    this->lightSource = lightSource;
}

void ShaderManager::wndResize(unsigned w, unsigned h) {
    WIDTH = w;
    HEIGHT = h;
}

void ShaderManager::ShadowMapPass::prepare(Shader* pShader) {
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMap.depthmap);
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glClear(GL_DEPTH_BUFFER_BIT);
    pShader->Use();
    lightSource->getComponent<Camera>()->SetShaderVP(pShader);
}

void ShaderManager::MainShaderPass::prepare(Shader* pShader) {
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glViewport(0, 0, ShaderManager::instance().WIDTH, ShaderManager::instance().HEIGHT);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    pShader->Use();
    Camera::main->SetShaderVP(pShader);
}

void* ShaderManager::RegisterLightSource(Entity* lightSource) {
    auto it = passes.emplace(passes.begin(), std::make_unique<ShadowMapPass>(lightSource));
    return static_cast<void*>(it.base());
}

void ShaderManager::UnregisterLightSource(void* id) {
    auto it = passes.begin();
    while (static_cast<void*>(it.base()) != id) {
        ++it;
        if (it == passes.end()-1) {
            return;
        }
    }
    passes.erase(it);
}

ShaderManager::ShadowMap::ShadowMap() {
    glGenFramebuffers(1, &depthmap);  

    //create texture

    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //attach to framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthmap);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0); 
}

void ShaderManager::UploadShadowMaps() {
};

void ShaderManager::Init()
{
    //shadowMapShader = new Shader("assets/shaders/basic.vs","assets/shaders/basic.fs");//shadow map
    mainShader = new Shader("assets/shaders/basic.vs", "assets/shaders/basic.fs", "assets/shaders/basic.gs"); //main shader

    passes.emplace_back(std::make_unique<MainShaderPass>(
        mainShader
    ));
};

Shader* ShaderManager::CurrentShader() const {
    return currentShader;
}

bool ShaderManager::PreparePass() {
    static uint8_t pass = 0;
    if (pass<passes.size())
    {
        currentShader = passes[pass]->pShader;
        passes[pass]->prepare(currentShader);
        pass++;
        return true;
    }
    else
    {
        pass = 0;
        return false;
    }
}

ShaderManager::~ShaderManager() {
    if (mainShader) delete mainShader;
    if (shadowMapShader) delete shadowMapShader;
}

ShaderManager::ShaderManager(){}
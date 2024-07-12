#include "shader_manager.h"
#include "components/camera.h"
#include "components/light.h"


static constexpr unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

static constexpr unsigned int MAX_LIGHTS = 10;

ShaderManager ShaderManager::shaderManager;

ShaderManager& ShaderManager::instance() {
    return shaderManager;
}

void ShaderManager::wndResize(unsigned w, unsigned h) {
    WIDTH = w;
    HEIGHT = h;
}

void ShaderManager::UpdateDelta(double delta) {
    delta_t = (delta_t + delta*0.1) - (static_cast<double>(delta_t > glm::two_pi<double>() ) * glm::two_pi<double>());
}

void ShaderManager::generateShadowMapArray() {
    if (shadowMapArray) glDeleteTextures(1, &shadowMapArray);
    glGenTextures(1, &shadowMapArray);
    glBindTexture(GL_TEXTURE_2D_ARRAY, shadowMapArray);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, n_lights, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

    for (int i = 0; i < n_lights; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, shadowMaps[i]);
        glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMapArray, 0, i);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}

void ShaderManager::RegisterLightSource(Entity* lightSource) {
    if (n_lights >= MAX_LIGHTS) return;

    GLuint depthmap;
    {
        glGenFramebuffers(1, &depthmap);  

        //attach to framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, depthmap);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0); 
    }

    shadowMaps.emplace_back(depthmap);
    lightSources.push_back(lightSource);

    n_lights = lightSources.size();
    lightSpaceMatrices.resize(n_lights);
    lightPositions.resize(n_lights);
    lightColors.resize(n_lights);

    generateShadowMapArray();
}

void ShaderManager::UnregisterLightSource(Entity* lightSource) {
    if (n_lights == 0) return;

    for (int i = 0; i < lightSources.size(); i++)
    {
        if (lightSources[i] == lightSource)
        {
            glDeleteFramebuffers(1, &shadowMaps[i]);
            shadowMaps.erase(shadowMaps.begin() + i);
            lightSources.erase(lightSources.begin() + i);
            break;
        }
    }
    n_lights = lightSources.size();

    generateShadowMapArray();
}

void ShaderManager::Init()
{
    shadowMapShader = new Shader("assets/shaders/shadow.vs","assets/shaders/shadow.fs");//shadow map
    mainShader = new Shader("assets/shaders/basic.vs", "assets/shaders/basic.fs", "assets/shaders/basic.gs"); //main shader
};

Shader* ShaderManager::CurrentShader() const {
    return currentShader;
}

bool ShaderManager::PreparePass() {
    static uint8_t pass = 0;

    if (pass<shadowMaps.size())
    {
        //update lights
        lightSpaceMatrices[pass] = lightSources[pass]->getComponent<Camera>()->GetViewProjectionMatrix();
        lightPositions[pass] = lightSources[pass]->getComponent<Transform>()->Position;
        lightColors[pass] = lightSources[pass]->getComponent<Light>()->GetColor();

        //render to shadow map
        currentShader =shadowMapShader;
        glBindFramebuffer(GL_FRAMEBUFFER, shadowMaps[pass]);
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glClear(GL_DEPTH_BUFFER_BIT);
        currentShader->Use();
        currentShader->SetFloat("delta_t", delta_t);
        currentShader->SetMatrix4("lightSpaceMatrix", lightSpaceMatrices[pass]);
        pass++;
        return true;
    }
    else if (pass == shadowMaps.size())
    {
        //render to screen

        currentShader = mainShader;
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        glViewport(0, 0, ShaderManager::instance().WIDTH, ShaderManager::instance().HEIGHT);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        currentShader->Use();
        Camera::main->SetShaderVP(currentShader);
        currentShader->SetVector3f("viewPos", Camera::main->GetPos());
        currentShader->SetFloat("delta_t", delta_t);
        currentShader->SetTextureArray("shadowMaps", shadowMapArray, 1);
        currentShader->SetMatrix4Array("lightSpaceMatrices", lightSpaceMatrices.data(), lightSpaceMatrices.size());
        currentShader->SetVector3fArray("lightPositions", lightPositions.data(), lightPositions.size());
        currentShader->SetVector3fArray("lightColors", lightColors.data(), lightColors.size());
        currentShader->SetInteger("n_lights", n_lights);
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
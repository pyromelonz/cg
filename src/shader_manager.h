#pragma once

#include <memory>

#include "entity.h"
#include "shader.h"

class ShaderManager {

    double delta_t = 0.0f;
    unsigned n_lights = 0;

    std::vector<Entity*> lightSources;

    std::vector<glm::mat4> lightSpaceMatrices;
    std::vector<glm::vec3> lightPositions;
    std::vector<GLuint> shadowMaps;

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

    void RegisterLightSource(Entity* lightSource);
    void UnregisterLightSource(Entity* lightSource);

    void UpdateDelta(double delta);

    ShaderManager(const ShaderManager&) = delete;
    ShaderManager operator=(const ShaderManager&) = delete;
    static ShaderManager& instance();

};
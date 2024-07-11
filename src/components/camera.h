#pragma once

#include <glm/glm.hpp>

#include "component.h"
#include "transform.h"
#include "shader.h"

class Camera : public Component
{
    float fov;
    Camera();
public:
    static Camera *main; //FIRST INSTANCE

    void Update(double delta) override;
    void Init() override;
    Camera(int w, int h, float fov = 45.0f, float near = 0.1f, float far=100.0f);
    Camera(float worldSize, float near, float far);
    
    
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    glm::mat4 GetViewProjectionMatrix();
    void SetShaderVP(Shader* pShader, const char* v_name = "viewMatrix", const char* p_name = "projectionMatrix");

private:
    Transform *transform = nullptr;
    glm::mat4 view = {};
    glm::mat4 projection = {};
};

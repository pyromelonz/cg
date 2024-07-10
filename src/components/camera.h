#pragma once

#include <glm/glm.hpp>

#include "component.h"
#include "transform.h"

class Camera : public Component
{
public:
    static Camera *main;

public:
    void Update(double delta) override;
    void Init() override;
    Camera();
    Camera(int w, int h);
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();

private:
    Transform *transform = nullptr;
    glm::mat4 view = {};
    glm::mat4 projection = {};
};

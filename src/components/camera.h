#pragma once

#include <glm/glm.hpp>

#include "component.h"
#include "transform.h"

// todo: add uniform block MVP to shader and update model from mesh, view from camera, projection from .. window? input?

class Camera : public Component
{
public:
    void Update() override;
    void Init() override;
    Camera();
    Camera(int w, int h);

private:
    Transform *transform = nullptr;
    glm::mat4 view = {};
    glm::mat4 projection = {};
};

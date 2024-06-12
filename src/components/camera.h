#pragma once
#include "component.h"
#include "../global_defines.h"
#include <glm/glm.hpp>

//todo: add uniform block MVP to shader and update model from mesh, view from camera, projection from .. window? input?

class Camera : public Component {
    CGMAT4 v = CGMAT4();
    public:
    void Update() override;
    void Init() override;
    Camera() = default;
};

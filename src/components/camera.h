#pragma once
#include "component.h"
#include "../global_defines.h"
#include <glm/glm.hpp>

class Camera : public Component {
    CGMAT4 mvp;
    public:
    void Update() override;
    void Init() override;
};
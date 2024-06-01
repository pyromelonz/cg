#pragma once
#include "component.h"
#include "../global_defines.h"
#include <glm/glm.hpp>
#include "shader_manager.h"

class ShaderViewProjectionGlobal : public TypedShaderGlobal<CGMAT4> {
    void shaderUpdateUniform() override;
    unsigned layoutLocation() const override;
};

class Camera : public Component {
    CGMAT4 vp = CGMAT4();
    public:
    void Update() override;
    void Init() override;
    ShaderViewProjectionGlobal shaderUniform;
    Camera() = default;
};

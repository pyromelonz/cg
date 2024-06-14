#pragma once

#include <glm/ext/quaternion_double_precision.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/glm.hpp>

#include "game_object.h"
#include "global_defines.h"
#include "vertex.h"
#include "component.h"

struct Transform : public Component
{
    CGQUAT rotation;
    CGXYZ pos, scale;
    void Update() override;
    void FixedUpdate() override;
    CGXYZ getPos() const;
    void Init() override {};
    CGMAT4 getMatrix() const noexcept;
    void rotate(CGXYZ vec, double angle) noexcept;
};

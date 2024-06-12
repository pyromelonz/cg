#pragma once

#include "../game_object.h"

#include <glm/ext/quaternion_double_precision.hpp>
#include "../global_defines.h"
#include <glm/ext/quaternion_transform.hpp>
#include <glm/glm.hpp>
#include "../vertex.h"

struct Transform : public Component {
    CGQUAT rotation = glm::identity<CGQUAT>();
    CGXYZ pos = CGXYZ(), scale = CGXYZ(1.0,1.0,1.0);
    void Update() override;
    void FixedUpdate() override;
    CGXYZ getPos() const;
    void Init() override {};
    CGMAT4 getMatrix() const noexcept;
    void rotate(CGXYZ vec, double angle) noexcept;
};

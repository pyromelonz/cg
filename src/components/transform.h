#pragma once

#include "../game_object.h"

#include <glm/ext/quaternion_double_precision.hpp>
#include "../global_defines.h"
#include <glm/ext/quaternion_transform.hpp>
#include <glm/glm.hpp>
#include "../vertex.h"

class Transform : public Component {
    CGQUAT rotation;
    public:
    void Update() override;
    void FixedUpdate() override;
    void Init() override {};
    CGMAT4 getMatrix() const noexcept;
    void rotate(CGXYZ vec, double angle) noexcept;
    double scaleX, scaleY, scaleZ;
    double x,y,z;
};

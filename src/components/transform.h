#pragma once

#include <glm/ext/quaternion_double_precision.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/glm.hpp>

#include "entity_manager.h"
#include "global_defines.h"
#include "component.h"

class Transform : public Component
{
public:
    glm::vec3 Position, Scale, Rotation;
    void Update() override;
    void FixedUpdate() override;
    void Init() override {};
    glm::mat4 GetMatrix() const noexcept;
    void rotate(CGXYZ vec, double angle) noexcept;
};

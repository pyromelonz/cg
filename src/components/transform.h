#pragma once

#include <glm/ext/quaternion_double_precision.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/glm.hpp>

#include "entity_manager.h"
#include "component.h"

struct Transform : public Component
{
    Transform(glm::vec3 position = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f), glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f)) : Position(position), Scale(scale), Rotation(rotation) {}
    glm::quat Rotation;

    glm::vec3 Position, Scale;
    void Forwards(double amount);
    void Strafe(double amount);
    void Up(double amount);
    void Update(double delta) override;
    void FixedUpdate() override;
    void Init() override {};
    glm::mat4 GetMatrix() const noexcept;
};

#include "transform.h"
#include "glm/gtc/quaternion.hpp"

void Transform::Update()
{
}

void Transform::FixedUpdate()
{
}

glm::mat4 Transform::GetMatrix() const noexcept
{
    glm::mat4 mat = glm::mat4(1.0f);
    mat = glm::translate(mat, Position);
    mat = glm::scale(mat, Scale);
    mat *= glm::mat4_cast(Rotation);
    return mat;
}
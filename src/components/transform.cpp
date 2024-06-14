#include "transform.h"
#include "glm/gtc/quaternion.hpp"

void Transform::Update()
{
}

void Transform::FixedUpdate()
{
}

CGXYZ Transform::getPos() const
{
    return pos;
}

CGMAT4 Transform::getMatrix() const noexcept
{
    CGMAT4 mat(rotation);
    mat[0][0] *= scale.x;
    mat[1][1] *= scale.y;
    mat[2][2] *= scale.z;
    mat[0][3] = pos.x;
    mat[1][3] = pos.y;
    mat[2][3] = pos.z;
    mat[3][3] = 1;
    return mat;
}

void Transform::rotate(CGXYZ vec, double angle) noexcept
{
    rotation = glm::rotate(rotation, angle, vec);
}
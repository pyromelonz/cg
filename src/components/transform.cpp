#include "transform.h"

void Transform::Update() {

}

void Transform::FixedUpdate() {

}

CGMAT4 Transform::getMatrix() const noexcept {
    CGMAT4 mat(rotation);
    mat[0][0] *= scaleX;
    mat[1][1] *= scaleY;
    mat[2][2] *= scaleZ;
    mat[0][3] = x;
    mat[1][3] = y;
    mat[2][3] = z;
    mat[3][3] = 1;
    return mat;
}

void Transform::rotate(CGXYZ vec, double angle) noexcept {
    rotation = glm::rotate(rotation,angle,vec);
}
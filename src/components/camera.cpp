#include "camera.h"
#include "glm/ext/matrix_transform.hpp"
#include "transform.h"

void Camera::Update() {
    Init(); //temporary... unless o.o
}

void Camera::Init() {
    auto transform = pEntity->getComponent<Transform>();
    mvp = glm::lookAt(transform->getPos(), CGXYZ(CGXYZW(1.0,0.0,0.0,1.0f) * transform->getMatrix()), CGXYZ(0.0,1.0,0.0));
}
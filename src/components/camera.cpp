#include "camera.h"
#include "glm/ext/matrix_transform.hpp"
#include "transform.h"
#include <iostream>

void Camera::Update() {
    Init(); //temporary... unless o.o

    auto peen = pEntity->getComponent<Transform>()->getPos();
    //std::cout << "camera at " << peen.x << ' ' << peen.y << ' ' << peen.z << std::endl;
}

void Camera::Init() {
    auto transform = pEntity->getComponent<Transform>();
    v = glm::lookAt(transform->getPos(), CGXYZ(CGXYZW(1.0,0.0,0.0,1.0f) * transform->getMatrix()), CGXYZ(0.0,1.0,0.0));
}
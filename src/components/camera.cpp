#include "camera.h"
#include "glm/ext/matrix_transform.hpp"
#include "transform.h"

void Camera::Update() {
    Init(); //temporary... unless o.o
    shaderUniform.setUniform(vp);
}

void Camera::Init() {
    auto transform = pEntity->getComponent<Transform>();
    vp = glm::lookAt(transform->getPos(), CGXYZ(CGXYZW(1.0,0.0,0.0,1.0f) * transform->getMatrix()), CGXYZ(0.0,1.0,0.0));
}

void ShaderViewProjectionGlobal::shaderUpdateUniform() {
    glUniformMatrix4dv(2,1,0,&uniform[0][0]);
}

unsigned ShaderViewProjectionGlobal::layoutLocation() const {
    return 1;
}
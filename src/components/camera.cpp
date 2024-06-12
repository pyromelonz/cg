#include "camera.h"
#include "glm/ext/matrix_transform.hpp"
#include "transform.h"
#include <iostream>

#include "shader_manager.h"
#include "uniform_buffer.h"

void Camera::Update() {
    Init(); //temporary... unless o.o

    auto peen = pEntity->getComponent<Transform>()->getPos();
    //debug std::cout << "camera at " << peen.x << ' ' << peen.y << ' ' << peen.z << std::endl;
}

void Camera::Init() {
    auto transform = pEntity->getComponent<Transform>();
    v = glm::lookAt(CGXYZ(0,0,0), CGXYZ(1.0,0.0,0.0), CGXYZ(0.0,1.0,0.0));

    dynamic_cast<MVP_Block_Buffer*>(
        dynamic_cast<UBO_Shader*>(ShaderManager::instance->getModelShader())
            ->ubos[0])->data.view = v;
}
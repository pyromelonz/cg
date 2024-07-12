#include "components/light.h"
#include "shader_manager.h"
#include "components/transform.h"

void Light::Init() {
    ShaderManager::instance().RegisterLightSource(pEntity);
}

void Light::Update(double delta) {
    pEntity->getComponent<Transform>()->Forwards(delta);
}

glm::vec3 Light::GetColor() const {
    return color;
}

Light::Light(glm::vec3 color) : color(color) {
    flags = LIGHT_SOURCE;
}

void Light::Destroy() {
    ShaderManager::instance().UnregisterLightSource(pEntity);
}
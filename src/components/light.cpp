#include "components/light.h"
#include "shader_manager.h"
#include "components/transform.h"

void Light::Init() {
    ShaderManager::instance().RegisterLightSource(pEntity);
}

void Light::Update(double delta) {
    pEntity->getComponent<Transform>()->Rotation *= glm::quat(glm::vec3(0.1f * delta, 0.01f * delta, 0.0f));
}

Light::Light(glm::vec3 color) : color(color) {
    flags = LIGHT_SOURCE;
}

Light::~Light() {
    ShaderManager::instance().UnregisterLightSource(pEntity);
}
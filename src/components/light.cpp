#include "components/light.h"
#include "shader_manager.h"

void Light::Init() {
    ShaderManager::instance().RegisterLightSource(pEntity);
}

void Light::Update(double delta) {

}

Light::Light(glm::vec3 color) : color(color) {
    flags = LIGHT_SOURCE;
}

Light::~Light() {
    ShaderManager::instance().UnregisterLightSource(pEntity);
}
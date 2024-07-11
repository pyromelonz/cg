#include "components/light.h"
#include "shader_manager.h"

void Light::Init() {
    smRef = ShaderManager::instance().RegisterLightSource(pEntity);
}

void Light::Update(double delta) {

}

Light::~Light() {
    ShaderManager::instance().UnregisterLightSource(smRef);
}
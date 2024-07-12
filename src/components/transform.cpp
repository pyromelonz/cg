#include "transform.h"
#include "glm/gtc/quaternion.hpp"
#include "components/light.h"
#include "components/camera.h"
#include "components/cube.h"

void Transform::Update(double delta)
{
}

void Transform::FixedUpdate()
{
}

glm::mat4 Transform::GetMatrix() const noexcept
{
    glm::mat4 mat = glm::mat4(1.0f);
    mat = glm::translate(mat, Position);
    mat = glm::scale(mat, Scale);
    mat *= glm::mat4_cast(Rotation);
    return mat;
}

void Transform::Forwards(double amount) {
    Position += Rotation * glm::vec4(0.0f,0.0f,-amount,1.0f);
}
void Transform::Strafe(double amount) {
  Position += Rotation * glm::vec4(-amount,0.0f,0.0f,1.0f) ;
}
void Transform::Up(double amount) {
    Position += glm::vec4(0.0f,amount,0.0f,1.0f);
}
Entity* Transform::SpawnLight(double delta) {
    auto light = std::make_unique<Entity>();
    auto pLight = light.get();
    light->addComponent(new Light(glm::vec3(1.0f,1.0f,1.0f)));
    light->addComponent(new Transform(Position,glm::vec3(0.4f),Rotation));
    light->addComponent(new Camera(40.0f,0.1f,100.0f));
    light->addComponent(new Cube(nullptr));
    EntityManager::instance().AddEntity(std::move(light));
    return pLight;
}
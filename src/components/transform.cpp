#include "transform.h"
#include "glm/gtc/quaternion.hpp"

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
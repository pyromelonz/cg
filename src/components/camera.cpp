#include "camera.h"
#include "transform.h"
#include "entity.h"

Camera *Camera::main; // Static member declaration

Camera::Camera()
{
    view = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 1000.0f);
    if (Camera::main == NULL)
    {
        Camera::main = this;
    }
}

Camera::Camera(int w, int h)
{
    view = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 1000.0f);
    if (Camera::main == NULL)
    {
        Camera::main = this;
    }
}

glm::mat4 Camera::GetViewMatrix()
{
    return view;
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return projection;
}

void Camera::Init()
{
    transform = pEntity->getComponent<Transform>();
    updatePriority = 5;
}

void Camera::Update()
{
    glm::mat4 matRoll = glm::mat4(1.0f);
    glm::mat4 matPitch = glm::mat4(1.0f);
    glm::mat4 matYaw = glm::mat4(1.0f);

    matRoll = glm::rotate(matRoll, (float)transform->rotation.z, glm::vec3(0, 0, 1));
    matPitch = glm::rotate(matPitch, (float)transform->rotation.x, glm::vec3(1, 0, 0));
    matYaw = glm::rotate(matYaw, (float)transform->rotation.y, glm::vec3(0, 1, 0));

    glm::mat4 rotation = matRoll * matPitch * matYaw;

    glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(-transform->pos.x, -transform->pos.y, -transform->pos.z));

    view = rotation * translation;
}
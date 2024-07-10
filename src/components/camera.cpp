#include "camera.h"
#include "transform.h"
#include "entity.h"

Camera *Camera::main; // Static member declaration

Camera::Camera()
{
    view = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    if (Camera::main == NULL)
    {
        Camera::main = this;
    }
}

Camera::Camera(int w, int h)
{
    view = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);
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

void Camera::Update(double delta)
{
    view = glm::lookAt(transform->Position, transform->Position + transform->Rotation * glm::vec3(0.0f, 0.0f, -1.0f), transform->Rotation * glm::vec3(0.0f, 1.0f, 0.0f));
}
#include "camera.h"
#include "transform.h"
#include "entity.h"

Camera *Camera::main; // Static member declaration

Camera::Camera()
{
    view = glm::mat4(1.0f);
    if (Camera::main == NULL)
    {
        Camera::main = this;
    }
}

Camera::Camera(int w, int h, float fov, float near, float far) : Camera()
{
    projection = glm::perspective(glm::radians(fov), (float)w / (float)h, 0.1f, 100.0f);
}

glm::vec3 Camera::GetPos() const
{
    return transform->Position;
}

Camera::Camera(float worldSize, float near, float far) : Camera()
{
    projection = glm::ortho(-worldSize, worldSize, -worldSize, worldSize, near, far);
}

glm::mat4 Camera::GetViewMatrix()
{
    return view;
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return projection;
}

glm::mat4 Camera::GetViewProjectionMatrix()
{
    return projection * view;
}

void Camera::Init()
{
    transform = pEntity->getComponent<Transform>();
    updatePriority = 5;
}

void Camera::Update(double delta)
{
    view = glm::lookAt(
        transform->Position,
        transform->Position + transform->Rotation * glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));

}

void Camera::SetShaderVP(Shader* pShader,const char* v_name, const char* p_name) {
    pShader->SetMatrix4(v_name, GetViewMatrix());
    pShader->SetMatrix4(p_name, GetProjectionMatrix());
}
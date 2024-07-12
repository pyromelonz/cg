#pragma once

#include "components/component.h"
#include "shader.h"

class Light : public Component {
    glm::vec3 color;
    public:
    void Update(double delta) override;
    glm::vec3 GetColor() const;
    void Init() override;
    Light(glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
    void Destroy() override;
};
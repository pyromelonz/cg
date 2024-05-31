#pragma once

#include "component.h"
#include <vector>
#include "../shader.h"
#include "../vertex.h"

class Mesh : public Component {
    bool visible;
    protected:
    std::vector<Vertex> vertices;
    std::vector<CGINDEX> indices;
    unsigned ebo, vbo, vao;
    Shader* pShader;
    public:
    virtual void Load_Mesh() = 0;
    virtual void Load_Texture() = 0;
    Mesh(Shader* pShaderProgram);
    void Init() override;
    void Update() override;
    void FixedUpdate() override {};
};
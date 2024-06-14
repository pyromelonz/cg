#pragma once

#include <vector>

#include "component.h"
#include "shader.h"
#include "vertex.h"

class Mesh : public Component
{
    bool visible;

protected:
    std::vector<Vertex> vertices;
    std::vector<CGINDEX> indices;
    unsigned ebo, vbo, vao;
    Shader *pShader;

public:
    virtual void LoadMesh() = 0;
    virtual void LoadTexture() = 0;
    Mesh(Shader *pShaderProgram);
    void Init() override;
    void Update() override;
    void FixedUpdate() override {};
};
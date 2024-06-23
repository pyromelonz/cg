#pragma once

#include <vector>

#include "component.h"
#include "shader.h"

class Mesh : public Component
{
    bool visible;

protected:
    std::vector<GLfloat> vertices;
    unsigned ebo, vbo, vao;
    Shader *pShader;

public:
    Mesh(Shader *pShaderProgram, const char *objPath);
    Mesh(Shader *pShaderProgram, const GLfloat *vertices, size_t size);

    virtual void LoadMesh() = 0;
    virtual void LoadTexture() = 0;
    void Init() override;
    void Update() override;
    void FixedUpdate() override {};
};
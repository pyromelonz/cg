#pragma once

#include <vector>

#include "component.h"
#include "shader.h"

class Mesh : public Component
{
    bool visible;

protected:
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> uv_coords;
    std::vector<uint32_t>indices;
    unsigned ebo, vbo, vao, uvbo;
    virtual GLuint texture() {return 0;};
    //unsigned normalMap;
    Shader *pShader;

public:
    Mesh(Shader *pShaderProgram, const char *objPath);
    Mesh(Shader *pShaderProgram,
        const GLfloat *vertex_data, size_t vertex_count,
        const uint32_t*index_data, size_t index_count,
        const GLfloat *uv_data = nullptr, size_t uv_count = 0);

    void Init() override;
    void Update(double delta) override;
    void Render() override;
    void FixedUpdate() override {};
};
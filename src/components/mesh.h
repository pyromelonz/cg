#pragma once

#include "component.h"
#include <vector>

#include "../vertex.h"

class Mesh : public Component {
    bool visible;
    std::vector<Vertex> vertices;
    std::vector<CGINDEX> indices;
    unsigned ebo, vbo, vao;
    public:
    virtual void Load_Mesh() = 0;
    virtual void Load_Texture() = 0;
    void Init() override;
    void Update() override;
    void FixedUpdate() override {};
};
#pragma once

#include "mesh.h"

class Cube : public Mesh
{
    void LoadTexture() override {};
    void LoadMesh() override;

public:
    Cube(Shader *shader);
};
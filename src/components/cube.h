#pragma once

#include "mesh.h"

class Cube : public Mesh
{

public:
    Cube(Shader *shader);
    GLuint texture() override;
};
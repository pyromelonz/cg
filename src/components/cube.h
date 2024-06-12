#pragma once
#include "mesh.h"

class Cube : public Mesh {
    void Load_Texture() override{};
    void Load_Mesh() override;
    public:
    Cube(Shader* shader);
};

class Triangle : public Mesh {
    void Load_Texture() override{};
    void Load_Mesh() override;
    public:
    Triangle(Shader* shader);
};
#include "cube.h"
#include <cstring>

void Cube::Load_Mesh() {
    float s = 0.3f;
    float vertices_[] = {
        -s,-s,-s,
        -s,-s,s,
        -s,s,-s,
        -s,s,s,
        s,-s,-s,
        s,-s,s,
        s,s,-s,
        s,s,s,
    };

    unsigned int indices_[] = {
        5,1,0,
        0,4,5,
        1,3,2,
        2,0,1,
        7,3,1,
        1,5,7,
        6,2,3,
        3,7,6,
        4,0,2,
        2,6,4,
        6,7,5,
        5,4,6
    };

    vertices.resize(sizeof(vertices_));
    memcpy(vertices.data(),vertices_,sizeof(vertices_));
    indices.resize(sizeof(indices_));
    memcpy(indices.data(),indices_,sizeof(indices_));
}

Cube::Cube(Shader* shader) : Mesh(shader) {}
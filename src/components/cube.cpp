#include "cube.h"
#include <cstring>
#include "transform.h"

static constexpr
std::array<float,72> cube_vertices = {
    // Front fac
    -0.5f, -0.5f,  0.5f,  // 0
     0.5f, -0.5f,  0.5f,  // 1
     0.5f,  0.5f,  0.5f,  // 2
    -0.5f,  0.5f,  0.5f,  // 3
    // Right fac
     0.5f, -0.5f,  0.5f,  // 4
     0.5f, -0.5f, -0.5f,  // 5
     0.5f,  0.5f, -0.5f,  // 6
     0.5f,  0.5f,  0.5f,  // 7
    // Back fac
     0.5f, -0.5f, -0.5f,  // 8
    -0.5f, -0.5f, -0.5f,  // 9
    -0.5f,  0.5f, -0.5f,  // 10
     0.5f,  0.5f, -0.5f,  // 11
    // Left fac
    -0.5f, -0.5f, -0.5f,  // 12
    -0.5f, -0.5f,  0.5f,  // 13
    -0.5f,  0.5f,  0.5f,  // 14
    -0.5f,  0.5f, -0.5f,  // 15
    // Top fac
    -0.5f,  0.5f,  0.5f,  // 16
     0.5f,  0.5f,  0.5f,  // 17
     0.5f,  0.5f, -0.5f,  // 18
    -0.5f,  0.5f, -0.5f,  // 19
    // Bottom fac
    -0.5f, -0.5f, -0.5f,  // 20
     0.5f, -0.5f, -0.5f,  // 21
     0.5f, -0.5f,  0.5f,  // 22
    -0.5f, -0.5f,  0.5f   // 23
};

static constexpr
std::array<GLfloat,48> cube_uvCoords = {
    // Front face
    1.0f / 3.0f, 1.0f / 2.0f,  // Bottom-left
    2.0f / 3.0f, 1.0f / 2.0f,  // Bottom-right
    2.0f / 3.0f, 1.0f,         // Top-right
    1.0f / 3.0f, 1.0f,         // Top-left

    // Back face
    2.0f / 3.0f, 1.0f / 2.0f,  // Bottom-left
    1.0f, 1.0f / 2.0f,         // Bottom-right
    1.0f, 1.0f,                // Top-right
    2.0f / 3.0f, 1.0f,         // Top-left

    // Left face
    0.0f, 0.0f,                // Bottom-left
    1.0f / 3.0f, 0.0f,         // Bottom-right
    1.0f / 3.0f, 1.0f / 2.0f,  // Top-right
    0.0f, 1.0f / 2.0f,         // Top-left

    // Right face
    2.0f / 3.0f, 0.0f,         // Bottom-left
    1.0f, 0.0f,                // Bottom-right
    1.0f, 1.0f / 2.0f,         // Top-right
    2.0f / 3.0f, 1.0f / 2.0f,  // Top-left

    // Top face
    0.0f, 1.0f / 2.0f,         // Bottom-left
    1.0f / 3.0f, 1.0f / 2.0f,  // Bottom-right
    1.0f / 3.0f, 1.0f,         // Top-right
    0.0f, 1.0f,                // Top-left

    // Bottom face
    1.0f / 3.0f, 0.0f,         // Bottom-left
    2.0f / 3.0f, 0.0f,         // Bottom-right
    2.0f / 3.0f, 1.0f / 2.0f,  // Top-right
    1.0f / 3.0f, 1.0f / 2.0f   // Top-left
};


static constexpr
std::array<uint32_t,36> cube_indices = {
    // Front face
    0, 1, 2,
    2, 3, 0,

    // Right face
    4, 5, 6,
    6, 7, 4,

    // Back face
    8, 9, 10,
    10, 11, 8,

    // Left face
    12, 13, 14,
    14, 15, 12,

    // Top face
    16, 17, 18,
    18, 19, 16,

    // Bottom face
    20, 21, 22,
    22, 23, 20
};

Cube::Cube(Shader *shader) : Mesh(shader,
    cube_vertices.data(), cube_vertices.size(),
    cube_indices.data(), cube_indices.size(),
    cube_uvCoords.data(),cube_uvCoords.size())
{}

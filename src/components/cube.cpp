#include "cube.h"
#include <cstring>
#include "transform.h"

static constexpr
std::array<float,72> cube_vertices = {
    // Front face
    -0.5f, -0.5f,  0.5f, // bottom-left
     0.5f, -0.5f,  0.5f, // bottom-right
     0.5f,  0.5f,  0.5f, // top-right
    -0.5f,  0.5f,  0.5f, // top-left

    // Back face
    -0.5f, -0.5f, -0.5f, // bottom-left
     0.5f, -0.5f, -0.5f, // bottom-right
     0.5f,  0.5f, -0.5f, // top-right
    -0.5f,  0.5f, -0.5f, // top-left

    // Left face
    -0.5f, -0.5f, -0.5f, // bottom-back
    -0.5f, -0.5f,  0.5f, // bottom-front
    -0.5f,  0.5f,  0.5f, // top-front
    -0.5f,  0.5f, -0.5f, // top-back

    // Right face
     0.5f, -0.5f, -0.5f, // bottom-back
     0.5f, -0.5f,  0.5f, // bottom-front
     0.5f,  0.5f,  0.5f, // top-front
     0.5f,  0.5f, -0.5f, // top-back

    // Top face
    -0.5f,  0.5f,  0.5f, // front-left
     0.5f,  0.5f,  0.5f, // front-right
     0.5f,  0.5f, -0.5f, // back-right
    -0.5f,  0.5f, -0.5f, // back-left

    // Bottom face
    -0.5f, -0.5f,  0.5f, // front-left
     0.5f, -0.5f,  0.5f, // front-right
     0.5f, -0.5f, -0.5f, // back-right
    -0.5f, -0.5f, -0.5f  // back-left
};

static constexpr
std::array<GLfloat,48> cube_uvCoords = {
    // Front face
    0.0f, 0.0f, // bottom-left
    1.0f, 0.0f, // bottom-right
    1.0f, 1.0f, // top-right
    0.0f, 1.0f, // top-left

    // Back face
    1.0f, 0.0f, // bottom-left
    0.0f, 0.0f, // bottom-right
    0.0f, 1.0f, // top-right
    1.0f, 1.0f, // top-left

    // Left face
    0.0f, 0.0f, // bottom-back
    1.0f, 0.0f, // bottom-front
    1.0f, 1.0f, // top-front
    0.0f, 1.0f, // top-back

    // Right face
    1.0f, 0.0f, // bottom-back
    0.0f, 0.0f, // bottom-front
    0.0f, 1.0f, // top-front
    1.0f, 1.0f, // top-back

    // Top face
    0.0f, 1.0f, // front-left
    1.0f, 1.0f, // front-right
    1.0f, 0.0f, // back-right
    0.0f, 0.0f, // back-left

    // Bottom face
    0.0f, 1.0f, // front-left
    1.0f, 1.0f, // front-right
    1.0f, 0.0f, // back-right
    0.0f, 0.0f  // back-left
};

static constexpr
std::array<uint32_t,36> cube_indices = {
    0, 1, 2, 2, 3, 0, // Front face
    4, 5, 6, 6, 7, 4, // Back face
    8, 9, 10, 10, 11, 8, // Left face
    12, 13, 14, 14, 15, 12, // Right face
    16, 17, 18, 18, 19, 16, // Top face
    20, 21, 22, 22, 23, 20 // Bottom face
};

Cube::Cube(Shader *shader) : Mesh(shader,
    cube_vertices.data(), cube_vertices.size(),
    cube_indices.data(), cube_indices.size(),
    cube_uvCoords.data(),cube_uvCoords.size())
{}

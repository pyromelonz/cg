#include "cube.h"
#include <cstring>
#include "transform.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
std::array<GLfloat, 48> cube_uvCoords = {
    // Front face
    0.0, 1.0, // Bottom-left
    1.0, 1.0, // Bottom-right
    1.0, 0.0, // Top-right
    0.0, 0.0, // Top-left

    // Back face
    0.0, 1.0, // Bottom-left
    1.0, 1.0, // Bottom-right
    1.0, 0.0, // Top-right
    0.0, 0.0, // Top-left

    // Left face
    0.0, 1.0, // Bottom-left
    1.0, 1.0, // Bottom-right
    1.0, 0.0, // Top-right
    0.0, 0.0, // Top-left

    // Right face
    0.0, 1.0, // Bottom-left
    1.0, 1.0, // Bottom-right
    1.0, 0.0, // Top-right
    0.0, 0.0, // Top-left

    // Top face
    0.0, 1.0, // Bottom-left
    1.0, 1.0, // Bottom-right
    1.0, 0.0, // Top-right
    0.0, 0.0, // Top-left

    // Bottom face
    0.0, 1.0, // Bottom-left
    1.0, 1.0, // Bottom-right
    1.0, 0.0, // Top-right
    0.0, 0.0  // Top-left
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
{

}

GLuint Cube::texture()
{
    static GLuint texture = 0;

    if (!texture) {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
    
    
        // Set the texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
    
        unsigned char *data = stbi_load("assets/textures/image.png", &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        stbi_image_free(data);
    }
    return texture;
}
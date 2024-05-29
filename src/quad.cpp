#include "quad.h"
#include <iostream>

Quad::Quad(float x, float y, float width, float height, Shader *shader)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->shader = shader;
    float vertices[] = {
        // positions
        x, y + height, 0.0f,        // top left
        x, y, 0.0f,                 // bottom left
        x + width, y, 0.0f,         // bottom right
        x + width, y + height, 0.0f // top right
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
}

Quad::~Quad()
{
}

void Quad::Update()
{
    EntityManager &manager = EntityManager::instance();
    float mouse_x = manager.mouse.x / (800 / 2) - 1.0f;
    float mouse_y = -1 * (manager.mouse.y / (600 / 2) - 1.0f);
    if (sqrt(pow((x - mouse_x), 2) + pow((y - mouse_y), 2)) < 0.1)
    {
        velocity.x = x - mouse_x;
        velocity.y = y - mouse_y;
    }
    else
    {
        velocity.x *= 0.7;
        velocity.y *= 0.7;
    }
    velocity.truncate(0.01);
    x += velocity.x;
    y += velocity.y;

    float vertices[] = {
        // positions
        x, y + height, 0.0f,        // top left
        x, y, 0.0f,                 // bottom left
        x + width, y, 0.0f,         // bottom right
        x + width, y + height, 0.0f // top right
    };
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Quad::FixedUpdate()
{
}

void Quad::Draw()
{
    shader->Use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

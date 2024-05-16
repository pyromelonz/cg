#pragma once
#include "game_object.h"
#include "shader.h"
#include "vector2.h"

class Quad : public GameObject
{
public:
    Quad(float x, float y, float width, float height, Shader *shader);
    ~Quad();
    void Update() override;
    void FixedUpdate() override;
    void Draw() override;

private:
    Shader *shader;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    float x;
    float y;
    float width;
    float height;
    Vector2 velocity;
};
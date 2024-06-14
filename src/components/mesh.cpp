#include <iostream>

#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include "shader_manager.h"
#include "entity.h"

void Mesh::Update()
{
    pShader->Use();
    Transform *transform = pEntity->getComponent<Transform>();
    if (transform)
    {
        auto modelMatrix = transform->getMatrix();
        dynamic_cast<MVP_Block_Buffer *>(
            dynamic_cast<UBO_Shader *>(ShaderManager::instance->getModelShader())
                ->ubos[0])
            ->data.model = modelMatrix;
    }
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    auto peen = transform->getPos();
    // std::cout << "object drawn at " << peen.x << ' ' << peen.y << ' ' << peen.z << std::endl;
}

void Mesh::Init()
{
    LoadMesh();
    LoadTexture();
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);
}

Mesh::Mesh(Shader *shaderProgram) : pShader(shaderProgram)
{
}
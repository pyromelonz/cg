#include <iostream>

#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include "entity.h"
#include "camera.h"

void Mesh::Update()
{
    // Camera matrix
    glm::mat4 View = glm::lookAt(
        glm::vec3(4, 3, -3), // Camera is at (4,3,-3), in World Space
        glm::vec3(0, 0, 0),  // and looks at the origin
        glm::vec3(0, 1, 0)   // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    pShader->Use();
    pShader->SetMatrix4("viewMatrix", View);
    pShader->SetMatrix4("g_ProjectionMatrix", Camera::main->GetProjectionMatrix());
    pShader->SetMatrix4("modelMatrix", this->pEntity->getComponent<Transform>()->GetMatrix());
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

void Mesh::Init()
{
    updatePriority = UpdatePriorities::Render;
    LoadMesh();
    LoadTexture();
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::Mesh(Shader *shaderProgram, const GLfloat *vertices, size_t size) : pShader(shaderProgram), vertices(vertices, vertices + size)
{
}
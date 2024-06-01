#include "mesh.h"
#include "../shader.h"
#include "transform.h"

void Mesh::Update() {
    pShader->Use();
    Transform* transform = pEntity->getComponent<Transform>();
    if (transform) {
        auto modelMatrix = transform->getMatrix();
        glUniformMatrix4dv(2,1,0,&modelMatrix[0][0]);
        }
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT,0 );
    glBindVertexArray(0);
}

void Mesh::Init() {
    Load_Mesh();
    Load_Texture();
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, vertices.size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);
}

Mesh::Mesh(Shader* shaderProgram) : pShader(shaderProgram)
{

}
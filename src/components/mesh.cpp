#include <iostream>

#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include "entity.h"
#include "camera.h"

void Mesh::Update(double delta)
{
    pShader->Use();
    pShader->SetMatrix4("viewMatrix", Camera::main->GetViewMatrix());
    pShader->SetMatrix4("g_ProjectionMatrix", Camera::main->GetProjectionMatrix());
    pShader->SetMatrix4("modelMatrix", this->pEntity->getComponent<Transform>()->GetMatrix());
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
}

void Mesh::Init()
{
    updatePriority = UpdatePriorities::Render;
    LoadMesh();
    LoadTexture();

    for (int o = 0; o<indices.size(); o++) {
        int i = indices[o];
        std::cout << "Vertex " << o << ": x=" << vertices[i*3] << ", y="<< vertices[i*3+1]
        << ", z=" << vertices[i*3+2] << std::endl;
    }


    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(uint32_t),indices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0, (GLvoid *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::Mesh(Shader *pShaderProgram,
        const GLfloat *vertex_data, size_t vertex_count,
        const uint32_t*index_data, size_t index_count,
        const GLfloat *uv_data, size_t uv_count)
        :
        indices(index_data,index_data + index_count),
        vertices(vertex_data, vertex_data+vertex_count),
        uv_coords(uv_data,uv_data+uv_count) ,
        pShader(pShaderProgram)
{}
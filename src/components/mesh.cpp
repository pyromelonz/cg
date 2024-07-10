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
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, indices.data());
    
    glBindVertexArray(0);
}

void Mesh::Init()
{
    updatePriority = UpdatePriorities::Render;
    LoadMesh();
    LoadTexture();
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(uint16_t),indices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0, (GLvoid *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::Mesh(Shader *pShaderProgram,
        const GLfloat *vertex_data, size_t vertex_count,
        const uint16_t*index_data, size_t index_count,
        const GLfloat *uv_data, size_t uv_count)
        :
        indices(index_data,index_data + index_count),
        vertices(vertex_data, vertex_data+vertex_count),
        uv_coords(uv_data,uv_data+uv_count) ,
        pShader(pShaderProgram)
{/*
    vertices.resize(vertex_count);
    indices.resize(index_count);
    uv_coords.resize(uv_count);    
    std::memcpy( vertices.data() , vertex_data , sizeof(GLfloat) * vertex_count  );
    std::memcpy( indices.data() ,  index_data , sizeof(uint16_t) * index_count  );
    std::memcpy( uv_coords.data() , uv_data  ,  sizeof(GLfloat) * uv_count );    
*/}
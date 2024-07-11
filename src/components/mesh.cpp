#include <iostream>

#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include "entity.h"
#include "camera.h"
#include "shader_manager.h"

void Mesh::Update(double delta)
{
}

void Mesh::Render() {
    
    //pShader->Use();
    /*
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, normalMap);
    pShader->SetInteger("normalMap",0);
    */

    auto pShader = ShaderManager::instance().CurrentShader();
    pShader->SetMatrix4("modelMatrix", this->pEntity->getComponent<Transform>()->GetMatrix());
    pShader->SetVector3f("objectPosition", this->pEntity->getComponent<Transform>()->Position);
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
}

void Mesh::Init()
{
    updatePriority = UpdatePriorities::PRIORITY_RENDER;
    flags |= RENDER_OBJECT;
    LoadMesh();
    LoadTexture();

    /*
        glGenTextures(1,&normalMap);
        glBindTexture(GL_TEXTURE_2D, normalMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, smiley_dim,smiley_dim, 0, GL_RGBA, GL_UNSIGNED_BYTE, terrain);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    */

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenBuffers(1, &uvbo);

    glBindVertexArray(vao);

    //vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glEnableVertexAttribArray(0);

    //uv coordinates
    glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glBufferData(GL_ARRAY_BUFFER, uv_coords.size() * sizeof(GLfloat), uv_coords.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glEnableVertexAttribArray(1);

    //index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(uint32_t),indices.data(), GL_STATIC_DRAW);

    //unbind
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
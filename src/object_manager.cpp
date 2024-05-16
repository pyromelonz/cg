#include "object_manager.h"
#include "global_includes.h"
#include <cstring>


void ObjectManager::initialise_objects() {
    std::vector<unsigned> vaos(objs.size()), vbos(objs.size());
    glGenVertexArrays(vaos.size(), vaos.data());
    glGenBuffers(vbos.size(),vbos.data());
    for (unsigned i = 0; i<objs.size(); i++) {
        objs[i].set_vbo_vao(vbos[i],vaos[i]);
        objs[i].initialise_buffers();
    }
}

GFX_Object::GFX_Object(float* p_model_data, unsigned model_data_count) {
    model_data.resize(model_data_count);
    std::memcpy(model_data.data(),p_model_data,sizeof(float)*model_data_count);
}

void GFX_Object::set_vbo_vao(unsigned new_vbo, unsigned new_vao) {
    vbo = new_vbo;
    vao = new_vao;
}
void GFX_Object::initialise_buffers() {
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, model_data.size()*sizeof(float), model_data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);


    //unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GFX_Object::bind_vertices() {
    glBindVertexArray(vao);
}

void ObjectManager::add_object(GFX_Object&& obj) {
    objs.push_back(obj);
}

int ObjectManager::bind_current_vao() {
    if (objs.empty()) {
        return -1;
    } else {
        objs[0].bind_vertices();
    }
    return 0;
}

GFX_Object::~GFX_Object() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}
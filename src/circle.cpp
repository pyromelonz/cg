#include "circle.h"
#include "global_includes.h"
#include <cmath>
#include <iostream>

Circle::Circle(float radius, float x, float y) : pos(glm::vec2(x,y)), radius(radius), ITL_GFX_Object(std::vector<unsigned>()) {

    std::vector<float> model_data;
    unsigned current_resolution = 50; //static_cast<float>(resolution) * (radius/100.0);
    model_data.resize((1+current_resolution)*3);
    indices.resize(current_resolution*3);
    model_data[0] = pos.x;
    model_data[1] = pos.y;
    for (int i = 0; i < current_resolution;) {
        indices[3*i] = 0;
        indices[3*i+2] = (i);
        indices[3*i+1] = i+1;

        i++;

        float cur_angle = M_PI * 2.0 * static_cast<float>(i)/static_cast<float>(resolution);
        model_data[3*i] = cos(cur_angle) * radius + pos.x;
        model_data[3*i+1] = sin(cur_angle) * radius + pos.y;
    }
    std::cout << "penis";
    for (auto c : indices) std::cout << c << " ";
    std::cout << std::endl;
    for (auto c : model_data) std::cout << c << " ";
}

void ITL_GFX_Object::render() {
    glDrawElements(
     GL_TRIANGLES,      // mode
     indices.size(),    // count
     GL_UNSIGNED_INT,   // type
     (void*)0           // element array buffer offset
 );
}

void ITL_GFX_Object::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_vbo);
    GFX_Object::bind();
}

void ITL_GFX_Object::set_indices(std::vector<unsigned> indices) {
    // Generate a buffer for the indices
    glGenBuffers(1, &index_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    this->indices = indices;
}

ITL_GFX_Object::ITL_GFX_Object(std::vector<unsigned> indices) : indices(indices) {}

ITL_GFX_Object::ITL_GFX_Object(float* p_model_data, unsigned model_data_size, std::vector<unsigned> indices) : GFX_Object(p_model_data,model_data_size){
    set_indices(indices);
}

ITL_GFX_Object::~ITL_GFX_Object() {
    glDeleteBuffers(1,&index_vbo);
}
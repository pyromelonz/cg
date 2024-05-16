#pragma once

#include "objects.h"
#include <glm/vec2.hpp>

class ITL_GFX_Object : public GFX_Object {
    unsigned index_vbo;

    protected:
    std::vector<unsigned> indices;

    public:
    void render() override;
    void bind() override;

    ITL_GFX_Object(float* p_model_data, unsigned model_data_size, std::vector<unsigned> indices);
    ITL_GFX_Object(std::vector<unsigned> indices);
    ~ITL_GFX_Object();
    
    void set_indices(std::vector<unsigned> indices);
};

class Circle : public ITL_GFX_Object {
    static constexpr unsigned resolution = 20; // number of points at radius 100
    glm::vec2 pos;
    float radius;
    public:
    Circle(float radius, float x, float y);
};
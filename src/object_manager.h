#pragma once
#include <vector>

class GFX_Object {

    std::vector<float> model_data;

    unsigned vbo = 0;
    unsigned vao = 0;

    public:
    GFX_Object(float* p_model_data, unsigned model_data_size);
    void initialise_buffers();
    void bind_vertices();
    void set_vbo_vao(unsigned vbo, unsigned vao);
    ~GFX_Object();
};

class ObjectManager {    
    std::vector<GFX_Object> objs;
    public:
    void initialise_objects();
    void add_object(GFX_Object&& obj);
    int bind_current_vao();
};
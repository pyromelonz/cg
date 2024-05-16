#pragma once
#include <vector>

class GFX_Object {

    std::vector<float> model_data;

    unsigned vbo = 0;
    unsigned vao = 0;

    public:
    GFX_Object(float* p_model_data, unsigned model_data_size);
    void initialise_buffers();
    virtual void render();
    void bind_and_render();
    void bind();
    void process();
    void physics_process();
    void set_vbo_vao(unsigned vbo, unsigned vao);
    ~GFX_Object();
};

class ObjectManager {    
    std::vector<GFX_Object> objs;
    public:
    void initialise_objects();
    void add_object(GFX_Object&& obj);
    void render_all();
};
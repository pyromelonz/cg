#pragma once
#include <vector>
#include <memory>

class GFX_Object {

    unsigned vbo = 0;
    unsigned vao = 0;
    protected:
    std::vector<float> model_data;
    public:
    GFX_Object(float* p_model_data, unsigned model_data_size);
    GFX_Object() = default;
    void initialise_buffers();
    virtual void render();
    void bind_and_render();
    virtual void bind();
    virtual void process() {};
    virtual void physics_process() {};
    void set_vbo_vao(unsigned vbo, unsigned vao);
    ~GFX_Object();
};

class ObjectManager {    
    std::vector<std::unique_ptr<GFX_Object>> objs;
    public:
    void initialise_objects();
    void add_object(std::unique_ptr<GFX_Object>&& obj);
    void render_all();
};
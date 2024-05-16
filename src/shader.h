#pragma once

class Shader {
    int load_from_path(const char* path);

    public:
    Shader(const char* path);


    unsigned shader_id;
};


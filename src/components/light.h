#pragma once

#include "components/component.h"
#include "shader.h"

class Light : public Component {
    void* smRef = nullptr;

    public:
    void Update(double delta) override;
    void Init() override;
    ~Light();
};
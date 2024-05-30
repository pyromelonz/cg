#pragma once
#include "component.h"
#include "../global_defines.h"
#include "../global_includes.h"

class Camera : public Component {
    public:
    void Update() override;
    void Init() override;
};
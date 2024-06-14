#pragma once

#include "entity.h"
#include <cstdint>

class Component
{
protected:
    Entity *pEntity = nullptr;
    friend Entity;

public:
    virtual void Update() = 0;
    virtual void FixedUpdate() {};
    virtual void Init() = 0;

    // Will determine the order in which different Components are updated by the EntityManager
    const uint8_t UpdatePriority = 0;
};

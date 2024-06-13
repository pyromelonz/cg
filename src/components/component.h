#pragma once

#include "entity.h"

class Component
{
protected:
    Entity *pEntity = nullptr;
    friend Entity;

public:
    virtual void Update() = 0;
    virtual void FixedUpdate() {};
    virtual void Init() = 0;

    const uint8_t updatePriority = 0;
    // will determine order in which different Components are updated by EntityManager
};

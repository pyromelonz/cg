#pragma once

#include "entity.h"
#include <cstdint>

class Component
{
protected:
    Entity *pEntity = nullptr;
    friend Entity;

    // Will determine the order in which different Components are updated by the EntityManager
    uint8_t updatePriority = 0;
public:
    virtual void Update(double delta) = 0; //consider a delta time parameter
    virtual void FixedUpdate() {};
    virtual void Init() = 0;
    uint8_t GetUpdatePriority() const;

    enum UpdatePriorities {
        MIN, Geometry = 5, Render= 10
    };
};

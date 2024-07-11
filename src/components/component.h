#pragma once

#include "entity.h"
#include <cstdint>

enum COMPONENT_FLAGS {
    RENDER_OBJECT = 1
};

class Component
{
protected:
    uint32_t flags = 0;
    Entity *pEntity = nullptr;
    friend Entity;

    // Will determine the order in which different Components are updated by the EntityManager
    uint8_t updatePriority = 0;
public:
    virtual void Update(double delta) = 0; //consider a delta time parameter
    virtual void FixedUpdate() {};
    virtual void Init() = 0;
    virtual void Render() {};
uint8_t GetUpdatePriority() const;

    enum UpdatePriorities {
        PRIORITY_MIN, PRIORITY_GEOMETRY = 5, PRIORITY_RENDER= 10
    };
};

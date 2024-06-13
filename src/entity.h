#pragma once

#include <vector>

#include "components/component.h"

class Entity
{
    std::vector<Component *> components;

public:
    void addComponent(Component *);
    void Update();
    void Init();
    void FixedUpdate();
    template <typename ComponentType>
    ComponentType *getComponent();
    void removeComponent(unsigned index);
};
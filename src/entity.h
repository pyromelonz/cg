#pragma once

#include <vector>

class Component;

class Entity
{
    std::vector<Component *> components;

public:
    void addComponent(Component *);
    void Update(double delta);
    void Init();
    void FixedUpdate();
    template <typename ComponentType>
    ComponentType *getComponent()
    {
        for (const auto &c : components)
        {
            auto pointer = dynamic_cast<ComponentType *>(c);
            if (pointer)
                return pointer;
        }
        return nullptr;
    }
    void removeComponent(unsigned index);
};
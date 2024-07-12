#pragma once

#include <vector>
#include <cstdint>

class Component;

class Entity
{
    std::vector<Component *> components;
    uint32_t flags = 0;
public:
    uint32_t getFlags() const;
    void addComponent(Component *);
    void Update(double delta);
    void Init();
    void Render();
    void Destroy();
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
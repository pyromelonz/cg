#pragma once
#include <memory>
#include <vector>

class Entity;

class Component
{
    protected:
    Entity* pEntity = nullptr;
    friend Entity;

    public:
    virtual void Update() = 0;
    virtual void FixedUpdate() {};
    virtual void Init() = 0;

    const uint8_t updatePriority = 0;
    //will determine order in which different Components are updated by EntityManager
};

class Entity : public Component //because I'm wild like that
{
    std::vector<Component*> components;
    public:
    void addComponent(Component*);
    void Update() override;
    void FixedUpdate() override;
    void Init() override {}
    template<typename ComponentType>
    ComponentType* getComponent() {
        for (const auto& c : components) {
            auto pointer = dynamic_cast<ComponentType*>(c//.get()
            );
                if (pointer) return pointer;
            }  
        return nullptr;
    }
    void removeComponent(unsigned index);
};
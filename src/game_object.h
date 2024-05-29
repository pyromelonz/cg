#pragma once
#include <vector>
#include <memory>
#include "components/component.h"

class Entity : public Component //because I'm wild like that
{
    std::vector<std::unique_ptr<Component>> components;
    public:
    void Update() override;
    void FixedUpdate() override;
};

struct Mouse
{
    double x;
    double y;
};

class EntityManager
{
public:
    static EntityManager &instance()
    {
        static EntityManager instance;
        return instance;
    }

    Mouse mouse;

    // Add a game object to the manager
    void AddGameObject(Entity *gameObject);
    // Remove a game object from the manager
    void RemoveGameObject(Entity *gameObject);
    // Called once per frame
    void Update();
    // Called once per fixed amount of time, currently unused
    void FixedUpdate();

private:
    EntityManager(){};

    EntityManager(EntityManager const &) = delete;
    void operator=(EntityManager const &) = delete;

    std::vector<Entity*> gameObjects;
};
#pragma once
#include <vector>
#include <memory>
#include "components/component.h"

class EntityManager
{
public:
    static EntityManager &instance()
    {
        static EntityManager instance;
        return instance;
    }
    void Init();
    // Add a game object to the manager
    void AddEntity(std::unique_ptr<Entity> &&gameObject);
    // Remove a game object from the manager
    void RemoveEntity(Entity *gameObject);
    // Called once per frame
    void Update(double delta);
    // Called once per fixed amount of time, currently unused
    void FixedUpdate();

private:
    EntityManager(){};

    bool initialized = false;

    EntityManager(EntityManager const &) = delete;
    void operator=(EntityManager const &) = delete;
    std::vector<std::unique_ptr<Entity>> gameObjects;
};
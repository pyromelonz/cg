#pragma once
#include <vector>
#include <memory>
#include "components/component.h"

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
    void Init();
    // Add a game object to the manager
    void AddEntity(std::unique_ptr<Entity> &&gameObject);
    // Remove a game object from the manager
    void RemoveEntity(Entity *gameObject);
    // Called once per frame
    void Update();
    // Called once per fixed amount of time, currently unused
    void FixedUpdate();

private:
    EntityManager(){};

    EntityManager(EntityManager const &) = delete;
    void operator=(EntityManager const &) = delete;

    std::vector<std::unique_ptr<Entity>> gameObjects;
};
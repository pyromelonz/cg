#include <algorithm>

#include "entity_manager.h"
#include "shader_manager.h"

void EntityManager::AddEntity(std::unique_ptr<Entity> &&gameObject)
{
    gameObjects.push_back(std::move(gameObject));
}

void EntityManager::RemoveEntity(Entity *gameObject)
{
    for (unsigned i = 0; i < gameObjects.size(); i++)
    {
        if (gameObjects[i].get() == gameObject)
        {
            gameObjects.erase(gameObjects.begin() + i);
        }
    }
}

void EntityManager::Init()
{
    for (auto &p : gameObjects)
    {
        p->Init();
    }
}

#include <iostream>

void EntityManager::Update(double delta)
{
    for (auto &gameObject : gameObjects)
    {
        gameObject->Update(delta);
    }

    while (ShaderManager::instance().PreparePass()) {
        for (auto& gameObject : gameObjects) {
            if (gameObject->getFlags() & RENDER_OBJECT) {
                gameObject->Render();
            }
        }
    }
}

void EntityManager::FixedUpdate()
{
    for (auto &gameObject : gameObjects)
    {
        gameObject->FixedUpdate();
    }
}

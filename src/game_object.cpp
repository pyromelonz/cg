#include "game_object.h"
#include <algorithm>

void EntityManager::AddGameObject(Entity *gameObject)
{
    gameObjects.push_back(gameObject);
}

void EntityManager::RemoveGameObject(Entity *gameObject)
{
    std::remove(gameObjects.begin(), gameObjects.end(), gameObject);
}

void EntityManager::Update()
{
    for (auto gameObject : gameObjects)
    {
        gameObject->Update();
    }
}

void EntityManager::FixedUpdate()
{
    for (auto gameObject : gameObjects)
    {
        gameObject->FixedUpdate();
    }
}

void Entity::Update() {
    for (auto& c : components) c->Update();
}

void Entity::FixedUpdate() {
    for (auto& c : components) c->FixedUpdate();
}
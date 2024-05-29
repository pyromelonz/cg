#include "game_object.h"
#include <algorithm>

void GameObjectManager::AddGameObject(GameObject *gameObject)
{
    gameObjects.push_back(gameObject);
}

void GameObjectManager::RemoveGameObject(GameObject *gameObject)
{
    std::remove(gameObjects.begin(), gameObjects.end(), gameObject);
}

void GameObjectManager::Update()
{
    for (auto gameObject : gameObjects)
    {
        gameObject->Update();
    }
}

void GameObjectManager::FixedUpdate()
{
    for (auto gameObject : gameObjects)
    {
        gameObject->FixedUpdate();
    }
}

void GameObjectManager::Draw()
{
    for (auto gameObject : gameObjects)
    {
        gameObject->Draw();
    }
}

#pragma once
#include <vector>
class GameObject
{
public:
    virtual void Update() = 0;
    virtual void FixedUpdate() = 0;
    virtual void Draw() = 0;
};

struct Mouse
{
    double x;
    double y;
};

class GameObjectManager
{
public:
    static GameObjectManager &instance()
    {
        static GameObjectManager instance;
        return instance;
    }

    Mouse mouse;

    // Add a game object to the manager
    void AddGameObject(GameObject *gameObject);
    // Remove a game object from the manager
    void RemoveGameObject(GameObject *gameObject);
    // Called once per frame
    void Update();
    // Called once per fixed amount of time, currently unused
    void FixedUpdate();
    // Called once per frame after Update
    void Draw();

private:
    GameObjectManager(){};

    GameObjectManager(GameObjectManager const &);
    void operator=(GameObjectManager const &);

    std::vector<GameObject *> gameObjects;
};
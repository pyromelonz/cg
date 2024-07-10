#include <algorithm>

#include "entity.h"
#include "components/component.h"

void Entity::addComponent(Component *component)
{
    components.insert(std::lower_bound(components.begin(),components.end(),component,[](Component* c1, Component* c2){return c1->GetUpdatePriority() < c2->GetUpdatePriority();}),component);
    component->pEntity = this;
}

void Entity::Update(double delta)
{
    for (auto &c : components)
        c->Update(delta);
}

void Entity::Init()
{
    for (auto &c : components)
        c->Init();
}

void Entity::FixedUpdate()
{
    for (auto &c : components)
        c->FixedUpdate();
}

void Entity::removeComponent(unsigned index)
{
    delete components[index];
    components.erase(components.begin() + index);
}
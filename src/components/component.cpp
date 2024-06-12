#include "component.h"

void Entity::addComponent(Component* component) {
    components.push_back(std::move(component));
    component->pEntity = this;
}

void Entity::Update() {
    for (auto& c : components)
        c->Update();
}

void Entity::Init() {
    for (auto& c : components)
        c->Init();
}

void Entity::FixedUpdate() {
    for (auto& c : components)
        c->FixedUpdate();
}

void Entity::removeComponent(unsigned index) {
    delete components[index];
    components.erase(components.begin()+index);
}
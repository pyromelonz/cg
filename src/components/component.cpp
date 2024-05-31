#include "component.h"

void Entity::addComponent(std::unique_ptr<Component>&& component) {
    components.push_back(std::move(component));
    component->pEntity = this;
}

void Entity::Update() {
    for (auto& c : components)
        c->Update();
}

void Entity::FixedUpdate() {
    for (auto& c : components)
        c->FixedUpdate();
}
#include "component.h"

void Entity::addComponent(std::unique_ptr<Component>&& component) {
    components.push_back(std::move(component));
    component->pEntity = this;
}
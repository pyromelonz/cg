#include "component.h"

void Entity::addComponent(std::unique_ptr<Component>&& component) {
    components.push_back(component);
    component->pEntity = this;
}
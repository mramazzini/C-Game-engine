#include "../include/ECS/ECS.h"

void Entity::addGroup(Group mGroup)
{
    groupBitset[mGroup] = true;
    manager->addToGroup(this, mGroup);
}
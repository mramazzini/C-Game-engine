#pragma once

#include "ECS/Core/Core.h"
#include "Components.h"

extern Coordinator gCoordinator;

class ColliderSystem : public System
{
public:
    void update()
    {
        for (Entity e : mEntities)
        {
            auto &collider = gCoordinator.GetComponent<Collider>(e);
            collider.update();
        }
    }
};


#pragma once
#include "ECS/Core/Core.h"
#include "Components.h"
class PlayerSystem : public System
{
public:
    void update()
    {
        for (Entity e : mEntities)
        {
            gCoordinator.GetComponent<Gravity>(e).update();
            gCoordinator.GetComponent<Collider>(e).update();
            gCoordinator.GetComponent<Transform>(e).update();
            gCoordinator.GetComponent<Hitpoint>(e).update();
        }
    }
};
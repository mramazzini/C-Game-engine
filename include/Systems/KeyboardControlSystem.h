#pragma once

#include "../ECS/Core/Core.h"

// class TransformComponent;
// class GravityComponent;
// class ColliderComponent;

extern Coordinator gCoordinator;

class KeyboardControlSystem : public System
{
public:
    void update()
    {
        for (Entity e : mEntities)
        {
            Keyboard &keyboard = gCoordinator.GetComponent<Keyboard>(e);
            keyboard.update();
        }
    }
};
#pragma once

#include "ECS/Core/Core.h"
#include "Transform.h"
extern Coordinator gCoordinator;
class Gravity : public Component
{
public:
    Gravity(){};
    bool grounded = false;
    Gravity(Entity &mEntity)
    {
        entity = mEntity;
        transform = &gCoordinator.GetComponent<Transform>(entity);
    }

    ~Gravity(){};

    void update() override
    {

        if (transform->velocity.y < 3)
        {
            transform->acceleration.y += 0.1;
        }
    }

private:
    Transform *transform;
};
#include "Core/Core.h"
#include "Transform.h"
#include "Components/Gravity.h"
Gravity::Gravity(){};

Gravity::Gravity(Entity &mEntity)
{
    entity = mEntity;
    transform = &gCoordinator.GetComponent<Transform>(entity);
}

Gravity::~Gravity(){};

void Gravity::update()
{

    if (transform->velocity.y < 3)
    {
        transform->acceleration.y += 0.1;
    }
}
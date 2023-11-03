#include "Systems/GravitySystem.h"

#include "Components/Gravity.h"
extern Coordinator gCoordinator;

void GravitySystem::update()
{
    for (Entity e : mEntities)
    {
        gCoordinator.GetComponent<Gravity>(e).update();
    }
}
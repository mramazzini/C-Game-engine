#include "Systems/HitpointSystem.h"
#include "Components/Hitpoint.h"
void HitpointSystem::update()
{
    for (Entity e : mEntities)
    {
        Hitpoint &hitpoint = gCoordinator.GetComponent<Hitpoint>(e);
        hitpoint.update();
        // if hitpoint < 0 destroy entity
    }
}
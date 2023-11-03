#include "Systems/ColliderSystem.h"
#include "Core/Core.h"
#include "Components/Collider.h"

extern Coordinator gCoordinator;

void ColliderSystem::update()
{
    for (Entity e : mEntities)
    {
        auto &collider = gCoordinator.GetComponent<Collider>(e);
        collider.update();
    }
}
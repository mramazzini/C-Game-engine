#include "Systems/PlayerSystem.h"
#include "Core/Core.h"
#include "Components.h"

void PlayerSystem::update()
{
    for (Entity e : mEntities)
    {
        gCoordinator.GetComponent<Gravity>(e).update();
        gCoordinator.GetComponent<Collider>(e).update();
        gCoordinator.GetComponent<Transform>(e).update();
        gCoordinator.GetComponent<Hitpoint>(e).update();
    }
}
#include "Systems/PlayerSystem.h"
#include "Core/Core.h"
#include "Components.h"

void PlayerSystem::update()
{
    for (Entity e : mEntities)
    {
        gCoordinator.GetComponent<Player>(e).update();
    }
}
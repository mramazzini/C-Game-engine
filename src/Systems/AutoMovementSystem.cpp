#include "Systems/AutoMovementSystem.h"
#include "Components/AutoMovement.h"
#include "Game.h"
#include "Core/Core.h"

extern Coordinator gCoordinator;

void AutoMovementSystem::update()
{
    for (Entity e : mEntities)
    {
        auto &AutoMove = gCoordinator.GetComponent<AutoMovement>(e);
        AutoMove.update();
    }
}

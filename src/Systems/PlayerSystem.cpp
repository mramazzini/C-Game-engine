#include "Systems/PlayerSystem.h"
#include "Core/Core.h"
#include "Components.h"
#include "Game.h"

void PlayerSystem::update()
{
    for (Entity e : mEntities)
    {
        if (gCoordinator.GetComponent<Player>(e).updatePlayer())
        {
            return;
        }
    }
}

void PlayerSystem::draw()
{
    for (Entity e : mEntities)
    {

        Hitpoint &hp = gCoordinator.GetComponent<Hitpoint>(e);
        hp.draw();
        if (Game::devMode)
        {
            Collider &collider = gCoordinator.GetComponent<Collider>(e);
            collider.draw();
        }
    }
}
Entity PlayerSystem::getPlayer()
{
    for (Entity e : mEntities)
    {
        return e;
    }
    return -1;
}
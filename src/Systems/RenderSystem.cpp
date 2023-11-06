#include "Systems/RenderSystem.h"
#include "Core/Core.h"
#include "Game.h"
#include "Components.h"
extern Coordinator gCoordinator;
void RenderSystem::update()
{
    for (Entity e : mEntities)
    {
        auto &sprite = gCoordinator.GetComponent<Sprite>(e);
        sprite.update();
    }
}
void RenderSystem::draw()
{

    for (const Entity &entity : mEntities)
    {

        auto &sprite = gCoordinator.GetComponent<Sprite>(entity);
        // Store player to render on top of everything
        if (gCoordinator.HasComponent<Player>(entity))
        {
            playerEntity = entity;
            continue;
        }
        sprite.draw();
    }
}
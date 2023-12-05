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
        if (sprite.layer == "background")
        {
            sprite.draw();
        }
    }
    for (const Entity &entity : mEntities)
    {
        auto &sprite = gCoordinator.GetComponent<Sprite>(entity);
        if (sprite.layer == "preground")
        {
            sprite.draw();
        }
    }
    for (const Entity &entity : mEntities)
    {
        auto &sprite = gCoordinator.GetComponent<Sprite>(entity);
        if (sprite.layer == "playerground")
        {
            sprite.draw();
        }
    }
    for (const Entity &entity : mEntities)
    {
        auto &sprite = gCoordinator.GetComponent<Sprite>(entity);
        if (sprite.layer == "postground")
        {
            sprite.draw();
        }
    }
}
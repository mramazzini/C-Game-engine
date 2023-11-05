#include "Core/Core.h"
#include "Components/Collider.h"
#include "Managers/LevelManager.h"
#include "Components/Player.h"

Player::Player() {}
Player::~Player() {}
Player::Player(Entity ent)
{
    entity = ent;
}
bool Player::updatePlayer()
{
    // check to see if player moves to new map
    // if so, load new map
    auto &collider = gCoordinator.GetComponent<Collider>(entity).collider;
    int mapWidth = Game::levels->mapWidth;
    int mapHeight = Game::levels->mapHeight;
    if (collider.x + collider.w > mapWidth)
    {
        Game::levels->loadLevelByDirection("right");
        return true;
    }
    if (collider.y + collider.h > mapHeight)
    {
        Game::levels->loadLevelByDirection("down");
        return true;
    }
    if (collider.x < 0)
    {
        Game::levels->loadLevelByDirection("left");
        return true;
    }
    if (collider.y < 0)
    {
        Game::levels->loadLevelByDirection("up");
        return true;
    }
    return false;
}
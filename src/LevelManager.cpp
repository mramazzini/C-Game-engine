#include "../include/LevelManager.h"
#include "../include/Game.h"

#include "../include/AssetManager.h"
#include "../include/HitboxManager.h"

LevelManager::LevelManager(Manager *man)
{
    manager = man;
}

void LevelManager::loadLevel()
{
    loadLevel("level1");
}
void LevelManager::loadLevel(std::string level)
{
    Game::hitboxes->generateHitboxes();
    Game::assets->generateAssets();
    Game::assets->generateLevel(level);
}
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
    Game::assets->generateAssets();
    loadLevel("level1");
}
void LevelManager::loadLevel(std::string level)
{
    SDL_RenderClear(Game::renderer);
    Game::hitboxes->generateHitboxes();

    Game::assets->generateLevel(level);
}
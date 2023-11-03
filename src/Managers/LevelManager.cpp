#include "Managers.h"
#include "SDL2/SDL.h"
#include "Game.h"

LevelManager::LevelManager(Coordinator *coordinator)
{
    this->coordinator = coordinator;
}
LevelManager::~LevelManager(){};

void LevelManager::loadLevel(std::string level)
{
    SDL_RenderClear(Game::renderer);
    Game::hitboxes->generateHitboxes();

    Game::assets->generateLevel(level);
};
void LevelManager::loadLevel()
{
    Game::assets->generateAssets();
    loadLevel("Arena");
};
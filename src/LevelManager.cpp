#include "../include/ECS/Components.h"
#include "../include/AssetManager.h"
#include "../include/LevelManager.h"
#include "../include/Map.h"
#include "../include/Game.h"

LevelManager::LevelManager(Manager *man) : manager(man) {}

LevelManager::~LevelManager()
{
}
void LevelManager::LoadLevel()
{
    LoadLevel(1);
}
void LevelManager::LoadLevel(int level)
{
    Game::hitboxes->generateHitboxes(level);
    Game::assets->generateAssets(level);
}
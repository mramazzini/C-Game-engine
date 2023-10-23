#include "../include/ECS/Components.h"
#include "../include/AssetManager.h"
#include "../include/Map.h"
#include <fstream>

AssetManager::AssetManager(Manager *man)
    : manager(man) {}

AssetManager::~AssetManager() {}

void AssetManager::addTexture(std::string id, const char *path)
{
    textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture *AssetManager::getTexture(std::string id)
{

    return textures[id];
}

void AssetManager::createPlayer()
{
    auto &player(manager->addEntity());
    player.addComponent<TransformComponent>(4);
    player.addComponent<SpriteComponent>("player", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addComponent<HitpointComponent>(10);
    player.addGroup(Game::groupPlayers);
}
void AssetManager::createProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string texid)
{
    auto &projectile(manager->addEntity());
    projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
    projectile.addComponent<SpriteComponent>(texid, false);
    projectile.addComponent<ProjectileComponent>(range, speed, vel);
    projectile.addComponent<ColliderComponent>("projectile");
    projectile.addComponent<HitpointComponent>(10);
    projectile.addComponent<DamageComponent>(1, false);
    projectile.addGroup(Game::groupProjectiles);
}
void AssetManager::createAttack(std::string name)
{
    // auto &attack(manager->addEntity());
    // projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
    // projectile.addComponent<SpriteComponent>(texid, false);
}
void AssetManager::generateAssets()
{
    addTexture("terrain", "assets/mapdata/terrain_ss.png");

    addTexture("player", "assets/images/player.png");
    addTexture("projectile", "assets/images/fireball.png");
    addTexture("hpbar", "assets/images/hpbar.png");

    Map *map = new Map("terrain", 2, 32);
    map->LoadMap("assets/mapdata/map.map", 16, 16);

    createPlayer();

    createProjectile(Vector2D(100, 100), Vector2D(1, 1), 1000, 2, "projectile");
}

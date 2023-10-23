#include "../include/ECS/Components.h"
#include "../include/AssetManager.h"
#include "../include/Map.h"

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
    projectile.addGroup(Game::groupProjectiles);
}
void AssetManager::generateAssets()
{
    addTexture("terrain", "assets/terrain_ss.png");
    addTexture("player", "assets/player.png");
    addTexture("projectile", "assets/fireball.png");
    addTexture("hpbar", "assets/hpbar.png");

    Map *map = new Map("terrain", 2, 32);
    map->LoadMap("assets/map.map", 16, 16);

    createPlayer();

    createProjectile(Vector2D(600, 600), Vector2D(1, 1), 1000, 2, "projectile");
}
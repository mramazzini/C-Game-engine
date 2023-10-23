#include "../include/ECS/Components.h"
#include "../include/AssetManager.h"

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

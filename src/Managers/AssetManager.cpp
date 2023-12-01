#include "Utils/Map.h"
#include "Components.h"
#include "Game.h"
#include "Systems/GlobalSystem.h"
#include "Managers.h"
#include <filesystem>
#include <fstream>

AssetManager::AssetManager(Coordinator *coord)
    : coordinator(coord) {}

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
    std::cout << "Generating player" << std::endl;

    Entity player = coordinator->CreateEntity();
    coordinator->AddComponent<Transform>(player, Transform(4, player));
    coordinator->AddComponent<Sprite>(player, Sprite("playerground", "player", true, player));
    coordinator->AddComponent<Collider>(player, Collider("player", player));
    coordinator->AddComponent<Gravity>(player, Gravity(player));
    coordinator->AddComponent<Player>(player, Player(player));
    coordinator->AddComponent<Keyboard>(player, Keyboard(player));
    coordinator->AddComponent<Hitpoint>(player, Hitpoint(10, true, player));
    coordinator->AddComponent<Damage>(player, Damage(1, true, player));
    std::cout << "Player created" << std::endl;
}
void AssetManager::createProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
    Entity projectile = coordinator->CreateEntity();
    coordinator->AddComponent<Transform>(projectile, Transform(pos.x, pos.y, 32, 32, 1, projectile));

    coordinator->AddComponent<Sprite>(projectile, Sprite("postground", id, false, projectile));
    coordinator->AddComponent<Projectile>(projectile, Projectile(range, speed, vel, projectile));
    coordinator->AddComponent<Collider>(projectile, Collider(id, projectile));

    coordinator->AddComponent<Damage>(projectile, Damage(1, false, projectile));
}
void AssetManager::createAttack(std::string name)
{
    // auto &attack(manager->addEntity());
    // projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
    // projectile.addComponent<SpriteComponent>(texid, false);
}
void AssetManager::generateAssets()
{

    std::cout << "Generating assets in directory " << Game::projectDir << std::endl;
    // Use the absolute path when adding textures
    addTexture("collider", (Game::projectDir + "/images/texture_collider.png").c_str());
    addTexture("terrain", (Game::projectDir + "/tilesets/tileset_terrain.png").c_str());
    addTexture("player", (Game::projectDir + "/animations/animation_monk.png").c_str());
    addTexture("fireball", (Game::projectDir + "/images/texture_fireball.png").c_str());
    addTexture("hpbar", (Game::projectDir + "/images/texture_hpbar.png").c_str());
}
void AssetManager::createMap(std::string level)
{

    std::cout << "Generating map" << std::endl;
    Map *map = new Map(2, coordinator);
    std::string mapFilePath = level;
    map->LoadMap(mapFilePath.c_str());
}
void AssetManager::generateLevel(std::string level)
{

    clearLevel();
    createPlayer();

    createMap(level);
}

void AssetManager::clearLevel()
{
    coordinator->DestroyEntities(Game::systems->globalSystem->mEntities);
}
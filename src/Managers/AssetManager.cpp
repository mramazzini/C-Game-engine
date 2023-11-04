
#include "Map.h"
#include "Components.h"
#include "Game.h"
#include "Systems/GlobalSystem.h"
#include "Managers.h"
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
    coordinator->AddComponent<Sprite>(player, Sprite("player", true, player));
    coordinator->AddComponent<Collider>(player, Collider("player", player));
    coordinator->AddComponent<Gravity>(player, Gravity(player));
    coordinator->AddComponent<Player>(player, Player());
    coordinator->AddComponent<Keyboard>(player, Keyboard(player));
    coordinator->AddComponent<Hitpoint>(player, Hitpoint(10, true, player));
    coordinator->AddComponent<Damage>(player, Damage(1, true, player));
    std::cout << "Player created" << std::endl;
}
void AssetManager::createProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
    Entity projectile = coordinator->CreateEntity();
    coordinator->AddComponent<Transform>(projectile, Transform(pos.x, pos.y, 32, 32, 1, projectile));
    coordinator->AddComponent<Sprite>(projectile, Sprite(id, false, projectile));
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
    std::cout << "Generating assets" << std::endl;
    addTexture("collider", "assets/images/collider.png");
    addTexture("terrain", "assets/mapdata/terrain_ss.png");
    addTexture("player", "assets/images/monk.png");
    addTexture("fireball", "assets/images/fireball.png");
    addTexture("hpbar", "assets/images/hpbar.png");
}
void AssetManager::createMap(std::string level)
{
    std::cout << "Generating map" << std::endl;
    Map *map = new Map("terrain", 4, 16, coordinator);
    map->LoadMap("assets/mapdata/" + level + ".map");
}
void AssetManager::generateLevel(std::string level)
{

    clearLevel();
    createPlayer();

    createMap(level);
    createProjectile(Vector2D(100, 800), Vector2D(1, -1), 1000, 2, "fireball");
    createProjectile(Vector2D(100, 700), Vector2D(1, -1), 1000, 2, "fireball");
    createProjectile(Vector2D(100, 600), Vector2D(1, -1), 1000, 2, "fireball");
}

void AssetManager::clearLevel()
{
    coordinator->DestroyEntities(Game::systems->globalSystem->mEntities);
}
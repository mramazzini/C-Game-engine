#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"

#include "Core/Core.h"

class AssetManager
{
public:
    AssetManager(Coordinator *coord);
    ~AssetManager();

    // gameObjects
    void createProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string texid);
    void createPlayer();
    void createMap(std::string level);
    void createAttack(std::string);
    // Texture management
    void generateAssets();
    void addTexture(std::string id, const char *path);
    SDL_Texture *getTexture(std ::string id);

    // Level Initialization
    void generateLevel(std::string level);
    void clearLevel();

private:
    std::map<std::string, SDL_Texture *> textures;
    Coordinator *coordinator;
};
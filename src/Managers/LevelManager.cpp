#include "Managers.h"
#include "SDL2/SDL.h"
#include "Game.h"
#include "Utils/json.hpp"
#include <fstream>

using json = nlohmann::json;

LevelManager::LevelManager(Coordinator *coordinator)
{
    this->coordinator = coordinator;
    mapList = MapList();
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

void LevelManager::generateMapList()
{
    std::cout << "Retrieving MapList" << std::endl;
    std::ifstream i("assets/mapdata/MapList.json");
    json j;
    i >> j;
    i.close();

    for (json::iterator it = j.begin(); it != j.end(); ++it)
    {
        json item = *it;
        std::string tag = item["tag"];
        // Create MapNode
        mapList.addNode(tag);
    }
    std::ifstream i2("assets/mapdata/MapList.json");
    json j2;
    i2 >> j2;
    for (json::iterator it = j2.begin(); it != j2.end(); ++it)
    {
        json item = *it;

        // Create MapNode
        std::string tag = item["tag"];
        std::string nodeAbove = item["top"];
        std::string nodeBelow = item["bottom"];
        std::string nodeLeft = item["left"];
        std::string nodeRight = item["right"];

        // Add connections
        mapList.addConnection(tag, nodeAbove, "top");
        mapList.addConnection(tag, nodeBelow, "bottom");
        mapList.addConnection(tag, nodeLeft, "left");
        mapList.addConnection(tag, nodeRight, "right");
    }
    i2.close();
    mapList.print();
}
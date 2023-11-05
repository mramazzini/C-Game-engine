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

void LevelManager::init()
{
    generateMapList();
    loadLevelByTag("Extended");
};

void LevelManager::loadLevelByTag(std::string tag)
{
    SDL_RenderClear(Game::renderer);
    Game::hitboxes->generateHitboxes();
    currentMapTag = tag;
    Game::assets->generateLevel(tag);
};

void LevelManager::loadLevelByDirection(std::string direction)
{
    std::cout << "Going to map in direction: " << direction << " from map " << currentMapTag << std::endl;
    std::string nextMapTag = mapList.getMapByDirection(currentMapTag, direction);
    if (nextMapTag != "")
    {
        loadLevelByTag(nextMapTag);
    }
    else
    {
        std::cout << "Error: no map in that direction" << std::endl;
    }
}

void LevelManager::generateMapList()
{
    std::cout << "Generating MapList" << std::endl;
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
        std::string nodeAbove = item["up"];
        std::string nodeBelow = item["down"];
        std::string nodeLeft = item["left"];
        std::string nodeRight = item["right"];

        // Add connections
        mapList.addConnection(tag, nodeAbove, "up");
        mapList.addConnection(tag, nodeBelow, "down");
        mapList.addConnection(tag, nodeLeft, "left");
        mapList.addConnection(tag, nodeRight, "right");
    }
    i2.close();
    mapList.print();
}

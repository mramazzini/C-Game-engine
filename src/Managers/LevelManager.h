#pragma once
#include "Core/Core.h"
#include "Utils/MapList.h"
class LevelManager
{
public:
    LevelManager(Coordinator *coordinator);
    ~LevelManager();

    void init();
    void generateMapList();
    void loadLevelByTag(std::string tag);
    void loadLevelByDirection(std::string direction);

    int mapWidth;
    int mapHeight;
    std::string currentMapTag;

private:
    Coordinator *coordinator;
    MapList mapList;
};
#pragma once
#include "Core/Core.h"
#include "Utils/MapList.h"
class LevelManager
{
public:
    LevelManager(Coordinator *coordinator);
    ~LevelManager();

    void loadLevel(std::string levelName);
    void loadLevel();
    void generateMapList();
    void goToMapByTag(std::string tag);
    void goToMapByDirection(std::string direction);

private:
    Coordinator *coordinator;
    MapList mapList;
};
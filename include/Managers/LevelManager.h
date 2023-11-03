#pragma once
#include "Core/Core.h"

class LevelManager
{
public:
    LevelManager(Coordinator *coordinator);
    ~LevelManager();

    void loadLevel(std::string levelName);
    void loadLevel();

private:
    Coordinator *coordinator;
};
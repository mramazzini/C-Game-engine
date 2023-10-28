#pragma once
#include <vector>
#include "ECS/ECS.h"
class AssetManager;
class LevelManager
{
public:
    LevelManager(Manager *man);

    ~LevelManager();
    void LoadLevel(); // Defaults to Level 1
    void LoadLevel(int level);
    void Update();
    void Draw();

private:
    Manager *manager;
};
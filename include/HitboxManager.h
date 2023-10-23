#pragma once
#include <string>
#include <map>
#include "../include/ECS/Components.h"
class HitboxManager
{
public:
    HitboxManager(Manager *man);
    ~HitboxManager();

    // Hitbox Management
    void generateHitboxes();

private:
    std::map<std::string, SDL_Rect> hitboxes;
    Manager *manager;
};
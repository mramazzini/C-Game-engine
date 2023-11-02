#pragma once
#include <string>
#include <map>
#include "../include/ECS/Core/Core.h"
#include "SDL2/SDL.h"
class HitboxManager
{
public:
    HitboxManager(Coordinator *coord);
    ~HitboxManager();

    // Hitbox Management
    void generateHitboxes();
    SDL_Rect *getHitbox(std ::string id);

private:
    std::map<std::string, SDL_Rect> hitboxes;
    Coordinator *coordinator;
};
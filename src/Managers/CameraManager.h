#pragma once
#include "SDL2/SDL.h"
#include "Core/Core.h"

class CameraManager
{
public:
    CameraManager(Coordinator *coord);
    ~CameraManager();
    void update();
    SDL_Rect getCamera();

private:
    SDL_Rect camera;
    Coordinator *coordinator;
};
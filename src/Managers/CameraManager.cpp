#include "Managers/CameraManager.h"
#include "Core/Core.h"
#include "Components/Transform.h"
#include "Game.h"
#include "SystemManager.h"

CameraManager::CameraManager(Coordinator *coord)
{
    coordinator = coord;
    // This dictates how big the screen is
    // Need to change this to be dynamic
    camera = {0, 0, 1024, 768};
}

CameraManager::~CameraManager()
{
}

void CameraManager::update()
{
    int mapWidth = Game::levels->mapWidth;
    int mapHeight = Game::levels->mapHeight;
    Entity player = Game::systems->playerSystem->getPlayer();
    if (player != -1)
    {
        camera.x = gCoordinator.GetComponent<Transform>(player).pos.x - camera.w / 2 + 64;
        camera.y = gCoordinator.GetComponent<Transform>(player).pos.y - camera.h / 2 + 64;
    }
    if (camera.x + camera.w > mapWidth)
    {
        camera.x = mapWidth - camera.w;
    }
    if (camera.y + camera.h > mapHeight)
    {
        camera.y = mapHeight - camera.h;
    }
    if (camera.x < 0)
    {
        camera.x = 0;
    }
    if (camera.y < 0)
    {
        camera.y = 0;
    }
}
SDL_Rect CameraManager::getCamera()
{
    return camera;
}
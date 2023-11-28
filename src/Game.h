#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Utils/Vector2D.h"
#include <memory>
#include <vector>
#include <stdio.h>
#include <string>
#include <iostream>
class Coordinator;
class AssetManager;
class HitboxManager;
class SceneManager;
class LevelManager;
class SystemManager;
class TilesetManager;
class CameraManager;

class Game
{
public:
    Game();
    ~Game();
    void init(const char *title, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; };

    static SDL_Event event;
    static SDL_Renderer *renderer;

    static bool isRunning;

    static AssetManager *assets;
    static HitboxManager *hitboxes;
    static SceneManager *scenes;
    static LevelManager *levels;
    static SystemManager *systems;
    static CameraManager *camera;
    static TilesetManager *tilesets;

    static void initGameClass(const std::string &dir, const bool &dev);
    static std::string projectDir;
    static bool devMode;

private:
    SDL_Window *window;
};

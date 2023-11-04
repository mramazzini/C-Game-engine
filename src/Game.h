#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2D.h"
#include <memory>
#include <vector>
#include <stdio.h>
#include <iostream>
class Coordinator;
class AssetManager;
class HitboxManager;
class SceneManager;
class LevelManager;
class SystemManager;

class Game
{
public:
    Game();
    ~Game();
    void init(const char *title, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; };

    static SDL_Event event;
    static SDL_Renderer *renderer;

    static bool isRunning;

    static SDL_Rect camera;
    static AssetManager *assets;
    static HitboxManager *hitboxes;
    static SceneManager *scenes;
    static LevelManager *levels;
    static SystemManager *systems;

private:
    int cnt = 0;

    SDL_Window *window;
};

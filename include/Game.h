#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2D.h"

#include <vector>
#include <stdio.h>
#include <iostream>

class AssetManager;
class HitboxManager;

class SceneManager;
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
    enum groupLabels : std::size_t
    {
        groupMap,
        groupPlayers,
        groupProjectiles,
        groupColliders,

    };

private:
    int cnt = 0;

    SDL_Window *window;
};

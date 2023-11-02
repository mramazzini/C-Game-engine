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

class RenderSystem;
class KeyboardControlSystem;
class ColliderSystem;
class DamageSystem;
class HitpointSystem;
class GlobalSystem;

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

    // Systems
    static std::shared_ptr<RenderSystem> renderSystem;
    static std::shared_ptr<ColliderSystem> colliderSystem;
    static std::shared_ptr<KeyboardControlSystem> keyboardControlSystem;
    static std::shared_ptr<DamageSystem> damageSystem;
    static std::shared_ptr<HitpointSystem> hitpointSystem;
    static std::shared_ptr<GlobalSystem> globalSystem;

private:
    int cnt = 0;

    SDL_Window *window;
};

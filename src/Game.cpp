#include "Game.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "Components.h"
#include "Systems.h"
#include "HitboxManager.h"
#include "SceneManager.h"
#include "LevelManager.h"
#include "GroupManager.h"

#include "ECS/Core/Core.h"

Coordinator gCoordinator;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = {0, 0, 1024, 1024};

AssetManager *Game::assets = new AssetManager(&gCoordinator);
HitboxManager *Game::hitboxes = new HitboxManager(&gCoordinator);
SceneManager *Game::scenes = new SceneManager(&gCoordinator);
LevelManager *Game::levels = new LevelManager(&gCoordinator);
GroupManager *Game::systems = new GroupManager(&gCoordinator);

bool Game::isRunning = false;

Game::Game()
{
}

Game::~Game()
{
    delete assets;
    delete hitboxes;
    delete scenes;
    delete levels;
    delete systems;
}

void Game::init(const char *title, int width, int height, bool fullscreen)
{

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {

        int flags = 0;
        if (fullscreen)
        {
            flags = SDL_WINDOW_FULLSCREEN;
        }
        std::cout << "Subsystems Initialised!..." << std::endl;

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if (window)
        {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }
        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    gCoordinator.Init();

    // Register Components
    gCoordinator.RegisterComponent<Sprite>();
    gCoordinator.RegisterComponent<Transform>();
    gCoordinator.RegisterComponent<Collider>();
    gCoordinator.RegisterComponent<Player>();
    gCoordinator.RegisterComponent<Gravity>();
    gCoordinator.RegisterComponent<Keyboard>();
    gCoordinator.RegisterComponent<Hitpoint>();
    gCoordinator.RegisterComponent<Projectile>();
    gCoordinator.RegisterComponent<Damage>();
    std::cout << "Components registered" << std::endl;
    // Generate Assets and textures
    assets->generateAssets();
    hitboxes->generateHitboxes();

    // Initialize Component Systems
    systems->init();

    // Generate Map
    assets->generateLevel("Arena");
}

void Game::handleEvents()
{
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
    default:
        break;
    }
}

void Game::update()
{
    Game::systems->update();

    // camera.x = player->getComponent<TransformComponent>().pos.x - 512 + 64;
    // camera.y = player->getComponent<TransformComponent>().pos.y - 512 + 64;

    // if (camera.x > camera.w)
    // {
    //     camera.x = camera.w;
    // }
    // if (camera.y > camera.h)
    // {
    //     camera.y = camera.h;
    // }
    // if (camera.x < 0)
    // {
    //     camera.x = 0;
    // }
    // if (camera.y < 0)
    // {
    //     camera.y = 0;
    // }

    // if (camera.x + camera.w > Map::mapWidth)
    // {
    //     camera.x = Map::mapWidth - camera.w;
    // }
    // if (camera.y + camera.h > Map::mapHeight)
    // {
    //     camera.y = Map::mapHeight - camera.h;
    // }
}

void Game::render()
{
    // Clear wahts in rendering buffer
    SDL_RenderClear(renderer);
    // This is where we add stuff to render

    Game::systems->draw();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

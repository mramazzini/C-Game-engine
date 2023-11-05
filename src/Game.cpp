#include "Game.h"
#include "Utils/Vector2D.h"
#include "Utils/Collision.h"
#include "Components.h"
#include "Systems.h"
#include "Managers.h"

#include "Core/Core.h"

Coordinator gCoordinator;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

AssetManager *Game::assets = new AssetManager(&gCoordinator);
HitboxManager *Game::hitboxes = new HitboxManager(&gCoordinator);
SceneManager *Game::scenes = new SceneManager(&gCoordinator);
LevelManager *Game::levels = new LevelManager(&gCoordinator);
SystemManager *Game::systems = new SystemManager(&gCoordinator);
CameraManager *Game::camera = new CameraManager(&gCoordinator);

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

void Game::init(const char *title, bool fullscreen)
{

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {

        int flags = 0;
        if (fullscreen)
        {
            flags = SDL_WINDOW_FULLSCREEN;
        }
        std::cout << "Subsystems Initialised!..." << std::endl;

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, camera->getCamera().w, camera->getCamera().h, flags);
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

    // Generate MapList
    levels->generateMapList();

    // Generate Map
    assets->generateLevel("extended");
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
    Game::camera->update();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    // set to false to not draw colliders
    Game::systems->draw(true);
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

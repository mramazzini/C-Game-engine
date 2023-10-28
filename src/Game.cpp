#include "../include/Game.h"
#include "../include/TextureManager.h"

#include "../include/Map.h"
#include "../include/ECS/Components.h"
#include "../include/Vector2D.h"
#include "../include/Collision.h"
#include "../include/AssetManager.h"
#include "../include/HitboxManager.h"
#include "../include/SceneManager.h"

Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = {0, 0, 1024, 1024};
auto &tiles(manager.getGroup(Game::groupMap));
auto &players(manager.getGroup(Game::groupPlayers));
auto &colliders(manager.getGroup(Game::groupColliders));
auto &projectiles(manager.getGroup(Game::groupProjectiles));

AssetManager *Game::assets = new AssetManager(&manager);
HitboxManager *Game::hitboxes = new HitboxManager(&manager);
SceneManager *Game::scenes = new SceneManager(&manager);

bool Game::isRunning = false;

Game::Game()
{
}

Game::~Game()
{
    delete assets;
    delete hitboxes;
    delete scenes;
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
    hitboxes->generateHitboxes();
    assets->generateAssets();
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
    Entity *player = players.at(0);
    SDL_Rect playerCol = player->getComponent<ColliderComponent>().collider;
    TransformComponent &transform = player->getComponent<TransformComponent>();
    // After update revert the player poisition if the collide witha wall

    manager.refresh();
    manager.update();

    for (auto &p : projectiles)
    {
        if (Collision::AABB(player->getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
        {
            p->getComponent<DamageComponent>().attack(player);
            p->destroy();
            //  std::cout << "Hit player" << std::endl;
        }
    }

    camera.x = player->getComponent<TransformComponent>().pos.x - 512 + 64;
    camera.y = player->getComponent<TransformComponent>().pos.y - 512 + 64;

    if (camera.x > camera.w)
    {
        camera.x = camera.w;
    }
    if (camera.y > camera.h)
    {
        camera.y = camera.h;
    }
    if (camera.x < 0)
    {
        camera.x = 0;
    }
    if (camera.y < 0)
    {
        camera.y = 0;
    }

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
    for (auto &t : tiles)
    {
        t->draw();
    }
    for (auto &p : projectiles)
    {
        p->draw();
    }
    for (auto &c : colliders)
    {
        c->draw();
    }
    for (auto &p : players)
    {
        p->draw();
    }

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

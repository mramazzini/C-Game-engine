#include "../include/Game.h"
#include "../include/TextureManager.h"
#include "../include/GameObject.h"
#include "../include/Map.h"
#include "../include/ECS/Components.h"
#include "../include/Vector2D.h"
#include "../include/Collision.h"
#include "../include/AssetManager.h"

Map *map;
Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = {0, 0, 1024, 1024};

AssetManager *Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto &player(manager.addEntity());

Game::Game()
{
}

Game::~Game() {}

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

    assets->addTexture("terrain", "assets/terrain_ss.png");
    assets->addTexture("player", "assets/player.png");
    assets->addTexture("projectile", "assets/fireball.png");
    assets->addTexture("hpbar", "assets/hpbar.png");

    map = new Map("terrain", 2, 32);
    map->LoadMap("assets/map.map", 16, 16);

    player.addComponent<TransformComponent>(4);
    player.addComponent<SpriteComponent>("player", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addComponent<HitpointComponent>(10);
    player.addGroup(groupPlayers);

    assets->createProjectile(Vector2D(600, 600), Vector2D(1, 1), 1000, 2, "projectile");
}

auto &tiles(manager.getGroup(Game::groupMap));
auto &players(manager.getGroup(Game::groupPlayers));
auto &colliders(manager.getGroup(Game::groupColliders));
auto &projectiles(manager.getGroup(Game::groupProjectiles));

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

    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = player.getComponent<TransformComponent>().pos;

    manager.refresh();
    manager.update();

    // After update revert the player poisition if the collide witha wall
    for (auto &c : colliders)
    {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCol))
        {
            player.getComponent<TransformComponent>().pos = playerPos;
        }
    }

    for (auto &p : projectiles)
    {
        if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
        {
            p->destroy();
            //  std::cout << "Hit player" << std::endl;
        }
    }

    camera.x = player.getComponent<TransformComponent>().pos.x - 256 + 64;
    camera.y = player.getComponent<TransformComponent>().pos.y - 256 + 64;

    if (camera.x < 0)
    {
        camera.x = 0;
    }
    if (camera.y < 0)
    {
        camera.y = 0;
    }
    if (camera.x > camera.w)
    {
        camera.x = camera.w;
    }
    if (camera.y > camera.h)
    {
        camera.y = camera.h;
    }
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
    for (auto &p : players)
    {
        p->draw();
    }
    for (auto &c : colliders)
    {
        c->draw();
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

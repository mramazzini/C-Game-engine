#include "../include/Game.h"
#include "../include/TextureManager.h"

#include "../include/Vector2D.h"
#include "../include/Collision.h"
#include "../include/AssetManager.h"
#include "../include/ECS/Sprite.h"
#include "../include/ECS/Keyboard.h"
#include "../include/ECS/Transform.h"
#include "../include/ECS/Collider.h"
#include "../include/ECS/Player.h"
#include "../include/ECS/Gravity.h"
#include "../include/ECS/Hitpoint.h"
#include "../include/ECS/Projectile.h"
#include "../include/ECS/Damage.h"
#include "../include/Systems/RenderSystem.h"
#include "../include/Systems/ColliderSystem.h"
#include "../include/Systems/KeyboardControlSystem.h"
#include "../include/Systems/DamageSystem.h"
#include "../include/Systems/HitpointSystem.h"
#include "../include/HitboxManager.h"
// #include "../include/SceneManager.h"

#include "../include/ECS/Core/Core.h"

Coordinator gCoordinator;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = {0, 0, 1024, 1024};

AssetManager *Game::assets = new AssetManager(&gCoordinator);
HitboxManager *Game::hitboxes = new HitboxManager(&gCoordinator);
// SceneManager *Game::scenes = new SceneManager(&manager);
std::shared_ptr<RenderSystem> Game::renderSystem = nullptr;
std::shared_ptr<ColliderSystem> Game::colliderSystem = nullptr;
std::shared_ptr<KeyboardControlSystem> Game::keyboardControlSystem = nullptr;
std::shared_ptr<DamageSystem> Game::damageSystem = nullptr;
std::shared_ptr<HitpointSystem> Game::hitpointSystem = nullptr;

bool Game::isRunning = false;

Game::Game()
{
}

Game::~Game()
{
    delete assets;
    delete hitboxes;
    // delete scenes;
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
    // Register Systems
    //
    {
        Game::renderSystem = gCoordinator.RegisterSystem<RenderSystem>();
        Signature signature;
        signature.set(gCoordinator.GetComponentType<Sprite>());
        gCoordinator.SetSystemSignature<RenderSystem>(signature);
    }
    Game::renderSystem->init();
    //
    {
        Game::colliderSystem = gCoordinator.RegisterSystem<ColliderSystem>();
        Signature signature;
        signature.set(gCoordinator.GetComponentType<Collider>());
        gCoordinator.SetSystemSignature<ColliderSystem>(signature);
    }
    Game::colliderSystem->init();
    {
        Game::keyboardControlSystem = gCoordinator.RegisterSystem<KeyboardControlSystem>();
        Signature signature;
        signature.set(gCoordinator.GetComponentType<Keyboard>());
        gCoordinator.SetSystemSignature<KeyboardControlSystem>(signature);
    }
    Game::keyboardControlSystem->init();
    {
        Game::damageSystem = gCoordinator.RegisterSystem<DamageSystem>();
        Signature signature;
        signature.set(gCoordinator.GetComponentType<Damage>());
        gCoordinator.SetSystemSignature<DamageSystem>(signature);
    }
    Game::damageSystem->init();
    {
        Game::hitpointSystem = gCoordinator.RegisterSystem<HitpointSystem>();
        Signature signature;
        signature.set(gCoordinator.GetComponentType<Hitpoint>());
        gCoordinator.SetSystemSignature<HitpointSystem>(signature);
    }
    Game::hitpointSystem->init();

    assets->createPlayer();

    assets->createMap();
    assets->createProjectile(Vector2D(100, 800), Vector2D(1, -1), 1000, 2, "fireball");
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
    Game::keyboardControlSystem->update();
    Game::colliderSystem->update();
    Game::damageSystem->update();
    // Entity *player = players.at(0);
    // SDL_Rect playerCol = player->getComponent<ColliderComponent>().collider;
    // TransformComponent &transform = player->getComponent<TransformComponent>();
    // // After update revert the player poisition if the collide witha wall

    // manager.refresh();
    // manager.update();

    // for (auto &p : projectiles)
    // {
    //     if (Collision::AABB(player->getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
    //     {
    //         p->getComponent<DamageComponent>().attack(player);
    //         p->destroy();
    //         //  std::cout << "Hit player" << std::endl;
    //     }
    // }

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

    Game::renderSystem->draw();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

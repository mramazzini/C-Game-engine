#include <SDL2/SDL.h>
#include "Game.h"
#include <string>

// Initialize Game
Game *game = nullptr;

int main(int argc, char *argv[])
{

    // get project directory
    std::string projectDir;
    bool devMode = false;
    if (argc > 1)
    {
        // directory specified, use that
        projectDir = argv[1];
    }
    else
    {
        std::cout << "No project directory specified" << std::endl;
        SDL_Log("No project directory specified");
        std::cout << "Using default project directory: "
                  << "assets" << std::endl;

        SDL_Log("Using default project directory: assets");
        projectDir = "assets";
    }
    if (argc > 2 && std::string(argv[2]) == "-dev")
    {
        std::cout << "Running in development mode" << std::endl;
        SDL_Log("Running in development mode");
        devMode = true;
    }
    else
    {
        SDL_Log("Running in production mode");
        std::cout << "Running in production mode" << std::endl;
    }
    SDL_Log("Running Project on Project Directory: %s", projectDir.c_str());
    std::cout << "Running Project on Project Directory: " << projectDir << std::endl;

    // Set up FPS information
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;
    Game::initGameClass(projectDir, devMode);

    game = new Game();
    game->init("Engine", false);
    std::cout << "Game Succesfully initialized!" << std::endl;
    std::cout << "Starting game loop..." << std::endl;
    SDL_Log("Game Succesfully initialized!");
    SDL_Log("Starting game loop...");
    while (game->running())
    {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks64() - frameStart;

        // If the frame is not finished by the time the handleEvents and update() and render() run, we delay so that the frame runs smoothly.
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;
}
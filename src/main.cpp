#include <SDL2/SDL.h>
#include "Game.h"

// Initialize Game
Game *game = nullptr;

int main(int argc, char *argv[])
{

    // Set up FPS information
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("Engine", 1024, 1024, false);
    std::cout << "Game Succesfully initialized!" << std::endl;
    std::cout << "Starting game loop..." << std::endl;
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
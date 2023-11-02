#pragma once
#include <vector>
#include <algorithm>
#include "Game.h"
#include "Gravity.h"
#include "Transform.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "LevelManager.h"
extern Coordinator gCoordinator;
class Keyboard : public Component
{
public:
    Transform *transform;
    Sprite *sprite;
    Gravity *gravity;

    std::vector<SDL_Keycode> keys;
    Keyboard() {}
    Keyboard(Entity mentity)
    {
        entity = mentity;
        transform = &gCoordinator.GetComponent<Transform>(entity);
        sprite = &gCoordinator.GetComponent<Sprite>(entity);
        gravity = &gCoordinator.GetComponent<Gravity>(entity);
    }

    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    bool updateKeys()
    {

        if (Game::event.type == SDL_KEYDOWN)
        {
            // check for menu keys
            if (Game::event.key.keysym.sym == SDLK_ESCAPE)
            {
                Game::levels->loadLevel("Arena");
                Game::scenes->toggleSettings();
                return true;
            }

            keys.push_back(Game::event.key.keysym.sym);
        }
        if (Game::event.type == SDL_KEYUP)
        {
            // remove key from vector
            keys.erase(std::remove(keys.begin(), keys.end(), Game::event.key.keysym.sym), keys.end());
        }

        // if keys has the certain key increase the acceleration, else decrease it
        if (std::find(keys.begin(), keys.end(), SDLK_w) != keys.end())
        {

            if (gCoordinator.HasComponent<Gravity>(entity) && gravity)
            {
                if (gravity->grounded == true)
                {
                    transform->velocity.y = -2.5;

                    gravity->grounded = false;
                    // sprite->play("walk");
                }
            }
            else
            {
                if (transform->acceleration.y > -1 && transform->velocity.y > -1)
                {
                    transform->acceleration.y += -0.5;
                }
            }
        }
        if (std::find(keys.begin(), keys.end(), SDLK_a) != keys.end())
        {
            if (transform->acceleration.x > -1 && transform->velocity.x > -1)
            {
                transform->acceleration.x += -0.5;
            }

            sprite->spriteFlip = SDL_FLIP_NONE;
            // sprite->play("walk");
        }
        if (std::find(keys.begin(), keys.end(), SDLK_s) != keys.end())
        {
            if (transform->acceleration.y < 1 && transform->velocity.y < 1)
            {
                transform->acceleration.y += 0.5;
            }

            // sprite->play("walk");
        }
        if (std::find(keys.begin(), keys.end(), SDLK_d) != keys.end())
        {
            if (transform->acceleration.x < 1 && transform->velocity.x < 1)
            {
                transform->acceleration.x += 0.5;
            }
            sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
            // sprite->play("walk");
        }
        return false;
        //  std::cout << "A = " << transform->acceleration << "V = " << transform->velocity << std::endl;
    }
};
#pragma once
#include "../Game.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "GravityComponent.h"
#include <vector>

class KeyboardController : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    GravityComponent *gravity;
    std::vector<SDL_Keycode> keys;
    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
        gravity = &entity->getComponent<GravityComponent>();
    }

    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    void update() override
    {

        if (Game::event.type == SDL_KEYDOWN)
        {

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

            if (entity->hasComponent<GravityComponent>() && gravity)
            {
                if (gravity->grounded == true)
                {
                    transform->velocity.y = -2;

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
        //  std::cout << "A = " << transform->acceleration << "V = " << transform->velocity << std::endl;
    }
};
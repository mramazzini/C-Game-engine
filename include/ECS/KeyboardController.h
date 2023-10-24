#pragma once
#include "../Game.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "GravityComponent.h"

class KeyboardController : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    GravityComponent *gravity;

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
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                if (entity->hasComponent<GravityComponent>() && gravity)
                {
                    if (gravity->grounded == true)
                    {

                        transform->velocity.y = -3;
                        gravity->grounded = false;
                        // sprite->play("walk");
                    }
                }

                break;
            case SDLK_a:
                transform->velocity.x = -1;
                sprite->spriteFlip = SDL_FLIP_NONE;
                // sprite->play("walk");
                break;
            case SDLK_s:
                transform->velocity.y = 1;

                // sprite->play("walk");
                break;
            case SDLK_d:
                transform->velocity.x = 1;
                sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                // sprite->play("walk");
                break;
            case SDLK_e:
                Game::assets->createAttack("attack");
            default:
                break;
            }
        }
        if (Game::event.type == SDL_KEYUP)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = 0;
                //   sprite->play("idle");
                break;
            case SDLK_a:
                transform->velocity.x = 0;

                // sprite->play("idle");
                break;
            case SDLK_s:
                transform->velocity.y = 0;
                // sprite->play("idle");
                break;
            case SDLK_d:
                transform->velocity.x = 0;

                // sprite->play("idle");
                break;
            case SDLK_ESCAPE:
                Game::isRunning = false;
            default:
                break;
            }
        }
    }
};
#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL2/SDL.h"

class TileComponent : public Component
{
public:
    SDL_Texture *texture;
    SDL_Rect srcRect, desRect;
    Vector2D position;

    TileComponent() = default;

    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }
    TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string textureID)
    {
        texture = Game::assets->getTexture(textureID);

        position.x = xpos;
        position.y = ypos;

        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = tsize;
        desRect.x = xpos;
        desRect.y = ypos;
        desRect.w = desRect.h = tsize * tscale;
    }

    void update() override
    {
        desRect.x = position.x - Game::camera.x;
        desRect.y = position.y - Game::camera.y;
    }

    void draw() override
    {

        TextureManager::Draw(texture, srcRect, desRect, SDL_FLIP_NONE);
    }
};
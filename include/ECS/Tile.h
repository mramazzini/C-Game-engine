#pragma once
#include "SDL2/SDL.h"
#include "Core/Core.h"
#include "Transform.h"
#include "../TextureManager.h"
#include "Collider.h"
#include "../Game.h"
#include "../AssetManager.h"

class Tile : public Component
{
public:
    SDL_Texture *texture;
    std::string textureid;
    SDL_Rect srcRect, desRect;
    Vector2D position;

    Tile(){};

    ~Tile()
    {
        SDL_DestroyTexture(texture);
    }
    Tile(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string textureID)
    {
        texture = Game::assets->getTexture(textureID);
        textureid = textureID;
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
};
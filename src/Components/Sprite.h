#pragma once
#include "Core/Core.h"
#include <SDL2/SDL.h>
#include "Animation.h"
#include <map>
#include "Game.h"
#include "Managers.h"
#include "Transform.h"
#include "Managers/CameraManager.h"
#include "Managers/TilesetManager.h"
#include <map>

extern Coordinator gCoordinator;
class Sprite : public Component
{
private:
    Transform *transform;
    Tileset *tileset;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    bool animated = false;
    int frames = 0;
    int speed = 100;
    bool tile = false;

public:
    std::string layer;
    int animIndex = 0;
    std::map<const char *, Animation> animations;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    Sprite() = default;

    Sprite(std::string renderLayer, std::string id, bool isAnimated, Entity &mEntity)
    {
        // Animated constructor
        entity = mEntity;
        layer = renderLayer;
        transform = &gCoordinator.GetComponent<Transform>(entity);
        tile = false;
        animated = isAnimated;
        // find layer in enum base of renderLayer

        Animation idle = Animation(0, 3, 200);
        // Animation walk = Animation(1, 8, 100);

        animations.emplace("idle", idle);
        // animations.emplace("walk", walk);

        play("idle");
        setTex(id);
        srcRect.x = srcRect.y = 0;

        srcRect.w = 32;
        srcRect.h = 32;

        destRect.w = (int)transform->width;
        destRect.h = (int)transform->height;
    }
    Sprite(std::string renderLayer, int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string textureID, Entity entity)
    {

        // Tile constructor

        texture = Game::assets->getTexture(textureID);
        tileset = Game::tilesets->getTileset(textureID);
        tile = true;
        transform = &gCoordinator.GetComponent<Transform>(entity);
        layer = renderLayer;
        transform->pos.x = xpos;
        transform->pos.y = ypos;

        srcRect.x = srcX * tileset->tileWidth;
        srcRect.y = srcY * tileset->tileHeight;
        if (textureID == "collider")
        {

            // I hate this
            srcRect.w = srcRect.h = 32;
        }
        else
        {
            srcRect.w = srcRect.h = tileset->tileWidth;
        }
        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = destRect.h = 32 * tscale;
    }

    void update() override
    {

        if (animated)
        {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks64() / speed) % frames);
        }
        if (!tile)
        {
            srcRect.y = animIndex * transform->height;

            destRect.w = transform->width * transform->scale;
            destRect.h = transform->height * transform->scale;
        }
        else
        {
            destRect.x = transform->pos.x - Game::camera->getCamera().x;
            destRect.y = transform->pos.x - Game::camera->getCamera().y;
        }
        destRect.x = static_cast<int>(transform->pos.x) - Game::camera->getCamera().x;
        destRect.y = static_cast<int>(transform->pos.y) - Game::camera->getCamera().y;
    }
    ~Sprite()
    {
    }
    void draw()
    {

        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
    }
    void setTex(std::string id)
    {
        texture = Game::assets->getTexture(id);
    }
    void play(const char *animName)
    {
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }
};
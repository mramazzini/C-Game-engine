#pragma once
#include "ECS/Core/Core.h"
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "Animation.h"
#include <map>
#include "Game.h"
#include "AssetManager.h"
#include "Transform.h"
extern Coordinator gCoordinator;
class Sprite : public Component
{
private:
    Transform *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    bool animated = false;
    int frames = 0;
    int speed = 100;
    bool tile = false;

public:
    int animIndex = 0;
    std::map<const char *, Animation> animations;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    Sprite() = default;
    Sprite(std::string id)
    {
        setTex(id);
    }

    Sprite(std::string id, bool isAnimated, Entity &mEntity)
    {
        // Animated constructor
        entity = mEntity;
        transform = &gCoordinator.GetComponent<Transform>(entity);
        tile = false;
        animated = isAnimated;

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
    Sprite(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string textureID, Entity entity)
    {

        // Tile constructor
        texture = Game::assets->getTexture(textureID);
        tile = true;
        transform = &gCoordinator.GetComponent<Transform>(entity);

        transform->pos.x = xpos;
        transform->pos.y = ypos;

        srcRect.x = srcX;
        srcRect.y = srcY;
        if (textureID == "collider")
        {

            // I hate this
            srcRect.w = srcRect.h = 32;
        }
        else
        {
            srcRect.w = srcRect.h = tsize;
        }
        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = destRect.h = tsize * tscale;
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
            destRect.x = transform->pos.x - Game::camera.x;
            destRect.y = transform->pos.x - Game::camera.y;
        }
        destRect.x = static_cast<int>(transform->pos.x) - Game::camera.x;
        destRect.y = static_cast<int>(transform->pos.y) - Game::camera.y;
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
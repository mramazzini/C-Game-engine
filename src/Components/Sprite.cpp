#include "Sprite.h"
#include "Components/Transform.h"
#include "Managers/CameraManager.h"
#include "Managers/TilesetManager.h"
#include "Managers/AssetManager.h"

#include <string>
#include "Game.h"
Sprite::Sprite() = default;

Sprite::Sprite(std::string renderLayer, std::string id, bool isAnimated, Entity &mEntity)
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
Sprite::Sprite(std::string renderLayer, int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string textureID, Entity entity)
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

void Sprite::update()
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
Sprite::~Sprite()
{
}
void Sprite::draw()
{

    TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
}
void Sprite::setTex(std::string id)
{
    texture = Game::assets->getTexture(id);
}
void Sprite::play(const char *animName)
{
    frames = animations[animName].frames;
    animIndex = animations[animName].index;
    speed = animations[animName].speed;
}
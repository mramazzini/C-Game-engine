#pragma once
#include "Core/Core.h"

#include "Animation.h"
#include <map>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Transform.h"

#include <map>
class Tileset;
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

    Sprite();

    Sprite(std::string renderLayer, std::string id, bool isAnimated, Entity &mEntity);
    Sprite(std::string renderLayer, int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string textureID, Entity entity);

    void update() override;
    ~Sprite();
    void draw();
    void setTex(std::string id);
    void play(const char *animName);
};
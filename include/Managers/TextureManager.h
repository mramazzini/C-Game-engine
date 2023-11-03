#pragma once

#include "SDL2/SDL.h"

class TextureManager
{
public:
    constexpr static SDL_Rect asd = {0, 0, 32, 32};
    constexpr static SDL_Rect asd2 = {200, 200, 32, 32};
    static SDL_Texture *LoadTexture(const char *fileName);
    static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};

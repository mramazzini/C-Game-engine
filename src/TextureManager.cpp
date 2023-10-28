#include "../include/TextureManager.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../include/Game.h"
SDL_Texture *TextureManager::LoadTexture(const char *texture)
{
    /*returns a texture from an image*/
    SDL_Surface *tempSurface = IMG_Load(texture);
    if (!tempSurface)
    {
        std::cerr << "Failed to load image: " << SDL_GetError() << std::endl;
        return nullptr; // Return nullptr on failure
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    if (!tex)
    {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return nullptr; // Return nullptr on failure
    }

    return tex;
}
void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
    if (!Game::renderer || !tex)
    {
        std::cerr << "Renderer or texture is not valid." << std::endl;
        return;
    }
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, 0, NULL, flip);
};
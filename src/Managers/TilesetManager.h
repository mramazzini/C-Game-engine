#pragma once
#include <string>
#include <map>
#include "Core/Core.h"
#include "SDL2/SDL.h"

struct Tileset
{
    std::string tag;
    int tileWidth;
    int tileHeight;
    int tileCount;
    int columns;
    int rows;
    std::string base64;
};
class TilesetManager
{
public:
    TilesetManager(Coordinator *coord);
    ~TilesetManager();

    // Hitbox Management
    void generateTilesets();

    Tileset *getTileset(std ::string tag);

private:
    std::map<std::string, Tileset> tilesets;
    Coordinator *coordinator;
};
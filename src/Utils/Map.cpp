#include "Map.h"
#include "Game.h"
#include "Components.h"
#include "Core/Core.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

Map::Map(std::string mtexID, int mscale, Coordinator *coord)
{
    textureID = mtexID;
    mapScale = mscale;

    coordinator = coord;
}
Map::~Map()
{
}

void Map::LoadMap(std::string tag)
{
    std::string path = ((Game::projectDir + "/maps/map_" + tag + ".json").c_str());
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Failed to open map: " << path << std::endl;
    }

    json mapData;
    file >> mapData;
    file.close();

    // Access the values in the JSON object
    int sizeX = mapData["sizeX"];
    int sizeY = mapData["sizeY"];

    std::string tileset = mapData["tileset"];
    tileSize = Game::tilesets->getTileset(tileset)->tileWidth;
    scaledSize = 64;

    // Give Camera map size
    Game::levels->mapWidth = sizeX * scaledSize;
    Game::levels->mapHeight = sizeY * scaledSize;

    // Access the tiles array
    json tiles = mapData["tiles"];

    // Loop through the 2D array
    for (int i = 0; i < sizeY; ++i)
    {
        for (int j = 0; j < sizeX; ++j)
        {
            bool collider = tiles[i][j]["collider"];
            // tileset spritesheet x-y postion
            int srcX = tiles[i][j]["srcX"];
            int srcY = tiles[i][j]["srcY"];
            addTile(srcX, srcY, j * scaledSize, i * scaledSize);
            if (collider)
            {
                Entity tcol = coordinator->CreateEntity();
                coordinator->AddComponent<Transform>(tcol, Transform(j * scaledSize, i * scaledSize, scaledSize, scaledSize, 1, tcol));
                coordinator->AddComponent<Collider>(tcol, Collider("terrain", j * scaledSize, i * scaledSize, scaledSize, tcol));
            }
        }
    }
}
void Map::addTile(int srcX, int srcY, int xpos, int ypos)
{
    Entity tile = coordinator->CreateEntity();
    // srcX, srcY, xpos, ypos, tileSize, mapScale,

    coordinator->AddComponent<Transform>(tile, Transform(xpos, ypos, tileSize, tileSize, mapScale, tile));

    coordinator->AddComponent<Sprite>(tile, Sprite(srcX, srcY, xpos, ypos, tileSize, mapScale, textureID, tile));
}

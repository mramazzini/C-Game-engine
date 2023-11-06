#include "Map.h"
#include "Game.h"
#include "Components.h"
#include "Core/Core.h"

#include <fstream>

Map::Map(std::string mtexID, int mscale, int tSize, Coordinator *coord)
{
    textureID = mtexID;
    mapScale = mscale;
    tileSize = tSize;
    scaledSize = mscale * tSize;
    coordinator = coord;
}
Map::~Map()
{
}
void Map::LoadMap(std::string path)
{

    char tile;
    std::fstream mapFile;
    mapFile.open(path);

    int srcX, srcY;
    int sizeX = 0, sizeY = 0;
    // Read the first number
    std::string numberStr;
    while (mapFile.get(tile) && isdigit(tile))
    {
        numberStr += tile;
    }
    if (!numberStr.empty())
    {
        sizeX = std::stoi(numberStr);
    }

    // Read the second number
    numberStr.clear();
    while (mapFile.get(tile) && isdigit(tile))
    {
        numberStr += tile;
    }
    if (!numberStr.empty())
    {
        sizeY = std::stoi(numberStr);
    }

    mapFile.ignore();

    Game::levels->mapWidth = sizeX * scaledSize;
    Game::levels->mapHeight = sizeY * scaledSize;

    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            // Map file represents the coordinates of the terrain file in between each comma
            // We can decide which tile to use based off that.
            mapFile.get(tile);
            srcY = atoi(&tile) * tileSize;
            mapFile.get(tile);
            srcX = atoi(&tile) * tileSize;
            addTile(srcX, srcY, x * scaledSize, y * scaledSize);
            mapFile.ignore();
        }
    }

    // skips a single character
    mapFile.ignore();
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(tile);
            if (tile == '1')
            {

                Entity tcol = coordinator->CreateEntity();
                coordinator->AddComponent<Transform>(tcol, Transform(x * scaledSize, y * scaledSize, scaledSize, scaledSize, 1, tcol));
                coordinator->AddComponent<Collider>(tcol, Collider("terrain", x * scaledSize, y * scaledSize, scaledSize, tcol));
            }
            mapFile.ignore();
        }
    }

    mapFile.close();
}
void Map::addTile(int srcX, int srcY, int xpos, int ypos)
{
    Entity tile = coordinator->CreateEntity();
    // srcX, srcY, xpos, ypos, tileSize, mapScale,

    coordinator->AddComponent<Transform>(tile, Transform(xpos, ypos, tileSize, tileSize, mapScale, tile));

    coordinator->AddComponent<Sprite>(tile, Sprite(srcX, srcY, xpos, ypos, tileSize, mapScale, textureID, tile));
}

#include "../include/Map.h"
#include "../include/Game.h"
#include "../include/ECS/Sprite.h"
#include "../include/ECS/Collider.h"
#include "../include/ECS/Transform.h"
#include "../include/ECS/Core/Core.h"

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
void Map::LoadMap(std::string path, int sizeX, int sizeY)
{

    char tile;
    std::fstream mapFile;
    mapFile.open(path);

    int srcX, srcY;

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
                coordinator->AddComponent<Sprite>(tcol, Sprite(0, 0, x * scaledSize, y * scaledSize, tileSize, mapScale, "collider", tcol));
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

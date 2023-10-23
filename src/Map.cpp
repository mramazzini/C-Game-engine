#include "../include/Map.h"
#include "../include/Game.h"
#include <fstream>

#include "../include/ECS/Components.h"

extern Manager manager;

Map::Map(std::string mtexID, int mscale, int tSize)
{
    textureID = mtexID;

    mapScale = mscale;
    tileSize = tSize;
    scaledSize = mscale * tSize;
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
                auto &tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                tcol.addGroup(Game::groupColliders);
            }
            mapFile.ignore();
        }
    }

    mapFile.close();
}
void Map::addTile(int srcX, int srcY, int xpos, int ypos)
{
    auto &tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, textureID);
    tile.addGroup(Game::groupMap);
}
#include "Map.h"
#include "Game.h"
#include "Components.h"
#include "Core/Core.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

Map::Map(int mscale, Coordinator *coord)
{

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
    textureID = mapData["tileset"];

    std::string tileset = mapData["tileset"];
    tileSize = Game::tilesets->getTileset(tileset)->tileWidth;
    scaledSize = 64;

    // Give Camera map size
    Game::levels->mapWidth = sizeX * scaledSize;
    Game::levels->mapHeight = sizeY * scaledSize;

    // Access the layers array
    json layers = mapData["layers"];

    // Loop through the layers
    for (int i = 0; i < layers.size(); ++i)
    {
        // Access the tiles array
        json tiles = layers[i]["tiles"];

        // Loop through the data array
        std::string layerName = layers[i]["tag"];
        for (int i = 0; i < sizeY; ++i)
        {
            for (int j = 0; j < sizeX; ++j)
            {

                int srcX = tiles[i][j]["srcX"];
                int srcY = tiles[i][j]["srcY"];
                addTileToLayer(layerName, srcX, srcY, j * scaledSize, i * scaledSize);
            }
        }
    }

    json colliders = mapData["colliders"];
    for (int i = 0; i < sizeY; ++i)
    {
        for (int j = 0; j < sizeX; ++j)
        {
            // collider at this position
            if (colliders[i][j])
            {
                Entity tcol = coordinator->CreateEntity();
                coordinator->AddComponent<Transform>(tcol, Transform(j * scaledSize, i * scaledSize, scaledSize, scaledSize, 1, tcol));
                coordinator->AddComponent<Collider>(tcol, Collider("terrain", j * scaledSize, i * scaledSize, scaledSize, tcol));
            }
        }
    }
}
void Map::addTileToLayer(std::string layer, int srcX, int srcY, int xpos, int ypos)
{
    Entity tile = coordinator->CreateEntity();
    // srcX, srcY, xpos, ypos, tileSize, mapScale,

    coordinator->AddComponent<Transform>(tile, Transform(xpos, ypos, tileSize, tileSize, mapScale, tile));

    coordinator->AddComponent<Sprite>(tile, Sprite(layer, srcX, srcY, xpos, ypos, tileSize, mapScale, textureID, tile));
}

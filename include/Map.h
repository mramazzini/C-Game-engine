#pragma once
#include <string>
#include "ECS/Core/Core.h"
class Map
{
public:
    ~Map();
    Map(std::string texID, int mscale, int tileSize, Coordinator *coord);
    void LoadMap(std::string path, int sizeX, int sizeY);

    void addTile(int srcX, int srcY, int xpos, int ypos);

private:
    std::string textureID;
    int mapScale;
    int tileSize;
    int scaledSize;
    Coordinator *coordinator;
};
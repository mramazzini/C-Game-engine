#pragma once
#include <string>
#include "Core/Core.h"
class Map
{
public:
    ~Map();
    Map(int mscale, Coordinator *coord);
    void LoadMap(std::string path);

    void addTileToLayer(std::string layer, int srcX, int srcY, int xpos, int ypos);

private:
    std::string textureID;
    int mapScale;
    int tileSize;
    int scaledSize;
    Coordinator *coordinator;
};
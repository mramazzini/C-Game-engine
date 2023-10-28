#pragma once
#include <string>
class Map
{
public:
    ~Map();
    Map(std::string texID, int mscale, int tileSize);
    void LoadMap(std::string path, int sizeX, int sizeY);
    void unloadMap();
    void addTile(int srcX, int srcY, int xpos, int ypos);

private:
    std::string textureID;
    int mapScale;
    int tileSize;
    int scaledSize;
};
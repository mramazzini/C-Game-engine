#include "Managers/TilesetManager.h"
#include "Managers/AssetManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Utils/json.hpp"
#include <filesystem>
#include "Game.h"

namespace fs = std::filesystem;

using json = nlohmann::json;

TilesetManager::TilesetManager(Coordinator *coord) : coordinator(coord) {}
TilesetManager::~TilesetManager() {}
void TilesetManager::generateTilesets()
{
    std::cout << "Generating Tilesets" << std::endl;
    int id;
    Tileset tileset;

    std::string filepath = ((Game::projectDir + "/relationships/tilesets.json").c_str());

    std::ifstream file(filepath);

    // Check if the file is open
    if (!file.is_open())
    {
        std::cerr << "Failed to open the file: " << filepath << std::endl;
        return;
    }

    // Parse the JSON data
    json data;
    file >> data;

    // Iterate through the JSON data and print the values
    for (const auto &item : data)
    {
        std::string path = ((Game::projectDir + "/tilesets/tileset_" + item["tag"].get<std::string>() + ".png").c_str());
        // Add to Assetmanager
        std::cout << "Adding texture: " << path << std::endl;
        Game::assets->addTexture(item["tag"], path.c_str());
        tileset = {
            item["tag"],
            item["tileWidth"],
            item["tileHeight"],
            item["tileCount"],
            item["columns"],
            item["rows"],
            item["base64"],
        };
        tilesets.emplace(item["tag"], tileset);
    }

    // close file
    file.close();
}

Tileset *TilesetManager::getTileset(std::string tag)
{
    return &tilesets[tag];
}
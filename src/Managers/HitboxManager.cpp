#include "Managers/HitboxManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Utils/json.hpp"
#include <filesystem>
#include "Game.h"

namespace fs = std::filesystem;

using json = nlohmann::json;

HitboxManager::HitboxManager(Coordinator *coord) : coordinator(coord) {}
HitboxManager::~HitboxManager() {}
void HitboxManager::generateHitboxes()
{
    std::cout << "Generating Hitboxes" << std::endl;
    int id;
    SDL_Rect hitbox;

    std::string filepath = ((Game::projectDir + "/relationships/hitboxes.json").c_str());

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
        SDL_Rect hitbox = {item["x"], item["y"], item["width"], item["height"]};
        hitboxes.emplace(item["tag"], hitbox);

        std::cout << std::endl;
    }

    // close file
    file.close();
}

SDL_Rect *HitboxManager::getHitbox(std::string id)
{

    return &hitboxes[id];
}
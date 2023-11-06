#include "Managers/HitboxManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Utils/json.hpp"

using json = nlohmann::json;

HitboxManager::HitboxManager(Coordinator *coord) : coordinator(coord) {}
HitboxManager::~HitboxManager() {}
void HitboxManager::generateHitboxes()
{
    std::cout << "Generating Hitboxes" << std::endl;
    int id;
    SDL_Rect hitbox;
    std::string filepath = "assets/data/hitboxes.json";

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

    // std::ifstream inputFile("assets/data/hitboxes.txt");

    // if (!inputFile.is_open())
    // {
    //     std::cerr << "Failed to open the hitbox file." << std::endl;
    //     return;
    // }

    // std::string line;
    // while (std::getline(inputFile, line))
    // {
    //     // Split each line into key and values
    //     std::istringstream lineStream(line);
    //     std::string key;
    //     std::string values;
    //     std::getline(lineStream, key, ':');
    //     std::getline(lineStream, values);

    //     // Split values into x, y, width, and height
    //     std::istringstream valuesStream(values);
    //     int x, y, width, height;
    //     char comma;
    //     valuesStream >> x >> comma >> y >> comma >> width >> comma >> height;

    //     // Create an SDL_Rect and add it to the map
    //     SDL_Rect hitbox = {x, y, width, height};

    //     hitboxes.emplace(key, hitbox);
    // }

    // inputFile.close();
}

SDL_Rect *HitboxManager::getHitbox(std::string id)
{

    return &hitboxes[id];
}
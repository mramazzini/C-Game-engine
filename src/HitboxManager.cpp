#include "../include/HitboxManager.h"
#include "../include/ECS/Components.h"
#include <fstream>
#include <sstream>

HitboxManager::HitboxManager(Manager *man) : manager(man) {}
HitboxManager::~HitboxManager() {}
void HitboxManager::generateHitboxes()
{
    int id;
    SDL_Rect hitbox;
    std::ifstream inputFile("assets/data/hitboxes.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open the hitbox file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        // Split each line into key and values
        std::istringstream lineStream(line);
        std::string key;
        std::string values;
        std::getline(lineStream, key, ':');
        std::getline(lineStream, values);

        // Split values into x, y, width, and height
        std::istringstream valuesStream(values);
        int x, y, width, height;
        char comma;
        valuesStream >> x >> comma >> y >> comma >> width >> comma >> height;

        // Create an SDL_Rect and add it to the map
        SDL_Rect hitbox = {x, y, width, height};

        hitboxes.emplace(key, hitbox);
    }
    std::cout << "Successfully generated Hitboxes" << std::endl;
    for (const auto &entry : hitboxes)
    {
        std::cout << "Key: " << entry.first << " - Rect: x=" << entry.second.x
                  << ", y=" << entry.second.y << ", width=" << entry.second.w
                  << ", height=" << entry.second.h << std::endl;
    }
    inputFile.close();
}

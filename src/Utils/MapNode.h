#pragma once
#include <string>
class MapNode
{
public:
    MapNode()
    {
        up = nullptr;
        down = nullptr;
        left = nullptr;
        right = nullptr;
        tag = "";
    }

    MapNode(std::string tag) : tag(tag), up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}
    // Each node points to up to 4 other nodes, depending on which direction the character leave the current node.
    std::shared_ptr<MapNode> up;
    std::shared_ptr<MapNode> down;
    std::shared_ptr<MapNode> left;
    std::shared_ptr<MapNode> right;
    // Tag is a way of organizing the maps in the maplist
    // It is always set to the name of the map file
    // ex "map1.map" would have a tag of "map1"
    std::string tag;
};

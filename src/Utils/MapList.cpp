#include "MapList.h"
#include "MapNode.h"
#include <iostream>
MapList::MapList()
{
}

MapList::~MapList()
{
}

void MapList::addNode(std::string newTag)
{
    // get from node
    std::unordered_map<std::string, std::shared_ptr<MapNode>>::const_iterator got = mapList.find(newTag);
    if (got != mapList.end())
    {
        std::cerr << "Error: Tag already exists: " << newTag << std::endl;
        return;
    }

    // create new node
    std::shared_ptr<MapNode> tNode = std::make_shared<MapNode>(newTag);

    mapList[newTag] = tNode;
}

void MapList::addConnection(std::string fromTag, std::string toTag, std::string fromDir)
{
    // early return
    if (toTag == "none")
        return;

    // Creates a relationship between two tags based off of the direction
    std::unordered_map<std::string, std::shared_ptr<MapNode>>::const_iterator got = mapList.find(fromTag);
    if (got == mapList.end())
    {
        std::cout << "Error: fromTag not found: " << fromTag << std::endl;
        return;
    }
    std::shared_ptr<MapNode> fromNode = got->second;

    // get to node
    got = mapList.find(toTag);
    if (got == mapList.end())
    {
        std::cout << "Error: toTag not found: " << toTag << std::endl;
        return;
    }
    std::shared_ptr<MapNode> toNode = got->second;

    addRelationship(fromNode, toNode, fromDir);
}
void MapList::addRelationship(std::shared_ptr<MapNode> fNode, std::shared_ptr<MapNode> tNode, std::string fromDir)
{
    // Assigns the nodes to each other based off of the direction
    if (fromDir == "top" && !tNode->top)
    {
        fNode->top = tNode;
        tNode->bottom = fNode;
    }
    else if (fromDir == "bottom")
    {
        fNode->bottom = tNode;
        tNode->top = fNode;
    }
    else if (fromDir == "left")
    {
        fNode->left = tNode;
        tNode->right = fNode;
    }
    else if (fromDir == "right")
    {
        fNode->right = tNode;
        tNode->left = fNode;
    }
    else
    {
        std::cout << "Error: invalid direction" << std::endl;
    }
}

void MapList::print()
{
    // Prints the maplist
    std::cout << "Printing MapList" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::unordered_map<std::string, std::shared_ptr<MapNode>>::const_iterator got = mapList.begin();
    while (got != mapList.end())
    {
        std::cout << "Tag: " << got->first << std::endl;

        if (got->second)
        {
            std::shared_ptr<MapNode> node = got->second;
            std::cout << "--------------------------------------------" << std::endl;
            std::cout << "   Top: " << (node->top ? node->top->tag : "nullptr") << std::endl;
            std::cout << "Bottom: " << (node->bottom ? node->bottom->tag : "nullptr") << std::endl;
            std::cout << "  Left: " << (node->left ? node->left->tag : "nullptr") << std::endl;
            std::cout << " Right: " << (node->right ? node->right->tag : "nullptr") << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
        }
        else
        {
            std::cout << "Node is null" << std::endl;
        }

        got++;
    }
}
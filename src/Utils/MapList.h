#pragma once

#include <string>
#include <unordered_map>
#include <memory>
class MapNode;
class MapList
{
public:
    MapList();
    ~MapList();
    void addNode(std::string newTag);
    void addConnection(std::string fromTag, std::string toTag, std::string fromDir);
    void print();

    std::shared_ptr<MapNode> getHead();
    std::string getMapByDirection(std::string fromTag, std::string direction);

private:
    std::shared_ptr<MapNode> head;
    std::unordered_map<std::string, std::shared_ptr<MapNode>> mapList; //<tag of node, node>
    void addRelationship(std::shared_ptr<MapNode> fromNode, std::shared_ptr<MapNode> toNode, std::string fromDir);
};
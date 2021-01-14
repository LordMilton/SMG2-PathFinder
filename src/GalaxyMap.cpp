#include <string>
#include "GalaxyMap.h"

GalaxyMap::GalaxyMap():Map()
{
   moveTime = 500;
}

GalaxyMap::~GalaxyMap()
{
   
}

void* GalaxyMap::containsNode(std::string name)
{
   return (new MapNode(new Galaxy(), 0));
}

int GalaxyMap::pathTime(std::string name1, std::string name2)
{
   MapNode* startNode = (MapNode*)containsNode(name1);
   MapNode* endNode = (MapNode*)containsNode(name2);
   
   return -1;
}

void GalaxyMap::readMapFromFile(std::string filename)
{
}
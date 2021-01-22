#include <string>
#include <queue>
#include "GalaxyMap.h"

GalaxyMap::GalaxyMap():Map()
{
   moveTime = 500;
}

GalaxyMap::~GalaxyMap()
{
   std::queue<MapNode*> toDestroy;
   toDestroy.push(head);
   while(!toDestroy.empty())
   {
      MapNode* next = toDestroy.front();
      int futureNodesSize = -1;
      MapNode** futureNodes = next->getCons(futureNodesSize);
      for(int i = 0; i < futureNodesSize; i++)
      {
         toDestroy.push(futureNodes[i]);
      }
      delete(futureNodes);
      futureNodes = NULL;
      toDestroy.pop(); //This calls the popped MapNodes constructor??
      next = NULL;
   }
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
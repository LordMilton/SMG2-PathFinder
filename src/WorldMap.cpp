#include <string>
#include <cstring>
#include <queue>
#include <iostream>
#include <fstream>
#include "WorldMap.h"
#include "World.h"

#define WORLDMAP_MAX_LINE_LENGTH 200
#define AVAILABLE_MARKER "-A-"
#define GALAXIES_SEPARATOR "--- Worlds ---"
//Character placed before stars to differentiate between stars and galaxies
#define CONNECTIONS_SEPARATOR "--- Connections ---"
//Character that goes inbetween the two galaxy names
#define CONNECTION_DELIMITER "-"
#define MAX_NODES 100
#define MAX_CONNECTIONS 2

#define GALAXY_MOVE_SPEED 500

WorldMap::WorldMap(int moveTime):Map()
{
   this->moveTime = moveTime;
}

WorldMap::~WorldMap()
{
   std::queue<MapNode*> toDestroy;
   if(head != NULL)
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
      futureNodes = NULL;
      toDestroy.pop();
      World* val = (World*)(next->getVal());
      delete(val);
      delete(next);
      next = NULL;
   }
}

WorldMap::MapNode* WorldMap::containsNode(std::string name)
{
   if(head == NULL)
   {
      return NULL;
   }
   
   getNextNode(true);
   
   MapNode* cur = getNextNode();
   bool found = false;
   MapNode* toReturn = NULL;
   while(!found && cur != NULL)
   {
      if(((World*)(cur->getVal()))->getName() == name)
      {
         toReturn = cur;
         found = true;
      }
      
      cur = getNextNode();
   }
   
   getNextNode(true);
   
   return toReturn;
}

std::string WorldMap::getName()
{
   return name;
}

void** WorldMap::toArray(int* arrSize)
{
   void** toReturn = new void*[numNodes];
   *arrSize = numNodes;
 
   if(numNodes <= 0)
      return toReturn;
 
   getNextNode(true);
 
   int counter = 0;
   MapNode* cur = getNextNode();
   while(cur != NULL)
   {
      toReturn[counter++] = cur->getVal();
      cur = getNextNode();
   }
   
   getNextNode(true);
   
   return toReturn;
}

void* WorldMap::containsValue(std::string name)
{
   MapNode* node = containsNode(name);
   if(node == NULL)
      return NULL;
   
   return node->getVal();
}

int WorldMap::pathTime(std::string name1, std::string name2)
{
   MapNode* start = containsNode(name1);
   if(start == NULL)
   {
      return -1;
   }
   
   start->reached = 0;
   std::queue<MapNode*> que;
   que.push(start);
   bool found = false;
   MapNode* foundNode = NULL;
   while(!found && !que.empty())
   {
      MapNode* cur = que.front();
      if(((World*)(cur->getVal()))->getName() == name2)
      {
         foundNode = cur;
         found = true;
      }
      else
      {
         int numCons = 0;
         MapNode** cons = cur->getCons(numCons);
         for(int i = 0; i < numCons; i++)
         {
            if(cons[i]->reached < 0 || cons[i]->reached > (cur->reached + moveTime))
            {
               cons[i]->reached = cur->reached + moveTime;
               que.push(cons[i]);
            }
         }
      }
      que.pop();
   }
   int toReturn = -1;
   if(foundNode != NULL)
   {
      toReturn = foundNode->reached;
   }
   
   start->resetReached();
   
   return toReturn;
}

bool WorldMap::safeReadLine(std::ifstream* file, char line[WORLDMAP_MAX_LINE_LENGTH])
{
   if(file->is_open() && file->good())
   {
      file->getline(line,WORLDMAP_MAX_LINE_LENGTH);
   }
   return file->good();
}

WorldMap::MapNode* WorldMap::fetchNodeFromArray(MapNode* nodes[], int arrLen, std::string name)
{
   for(int i = 0; i < arrLen; i++)
   {
      MapNode* cur = nodes[i];
      if(((World*)(cur->getVal()))->getName() == name)
      {
         return cur;
      }
   }
   return NULL;
}

void WorldMap::readMapFromFile(std::string filename)
{
   std::ifstream specs;
   specs.open(filename);
   char nextLine[WORLDMAP_MAX_LINE_LENGTH];
   bool lastReadGood = true;
   if(specs.is_open())
   {
      //--- Worlds ---
      MapNode* nodes[MAX_NODES];
      int numWorlds = 0;
      lastReadGood = safeReadLine(&specs, nextLine); //Burn separator
      
      readWorldsFromFile(filename, &specs, nextLine, nodes, &numWorlds);
      this->numNodes = numWorlds;
      
      //--- Connections ---
      // Separator already got burned in the last loop
      readConsFromFile(filename, &specs, nextLine, nodes, numWorlds);
      
      specs.close();
   }
}

void WorldMap::readWorldsFromFile(std::string filename, std::ifstream* file, char nextLine[], MapNode* nodes[], int* numWorlds)
{
   bool lastReadGood = safeReadLine(file, nextLine);
   bool firstWorld = true;
   while(lastReadGood && (strcmp(nextLine, CONNECTIONS_SEPARATOR)) != 0)
   {
      bool available = false;
      int cutOff = 0; //How many characters of the nextLine to cut off (takes care of AVAILABLE_MARKER if necessary)
      if(strstr(nextLine, AVAILABLE_MARKER) != NULL)
      {
         available = true;
         cutOff = strlen(AVAILABLE_MARKER);
      }
      nextLine[strlen(nextLine) - cutOff] = '\0'; // Cuts off the AVAILABLE_MARKER
      
      GalaxyMap* map = new GalaxyMap(GALAXY_MOVE_SPEED);
      map->readMapFromFile(nextLine);
      
      World* world = new World(nextLine, map, available);
      
      MapNode* node = new MapNode(world, MAX_CONNECTIONS);
      if(firstWorld)
      {
         head = node;
         firstWorld = false;
      }
      nodes[(*numWorlds)++] = node;
      
      lastReadGood = safeReadLine(file, nextLine);
   }
}

void WorldMap::readConsFromFile(std::string filename, std::ifstream* file, char nextLine[], MapNode* nodes[], int numWorlds)
{
   bool lastReadGood = safeReadLine(file, nextLine);
   while(lastReadGood) //Either until it fails or we reach EOF
   {
      std::string firstWorldName = strtok(nextLine, CONNECTION_DELIMITER);
      std::string secondWorldName = strtok(NULL, CONNECTION_DELIMITER);
      MapNode* firstNode = fetchNodeFromArray(nodes, numWorlds, firstWorldName);
      MapNode* secondNode = fetchNodeFromArray(nodes, numWorlds, secondWorldName);
      
      bool badName = false;
      if(firstNode == NULL)
      {
         std::cout << "\"" << firstWorldName << "\" does not name a world in file \"" << filename << "\"\n";
         badName = true;
      }
      if(secondNode == NULL)
      {
         std::cout << "\"" << secondWorldName << "\" does not name a world in file \"" << filename << "\"\n";
         badName = true;
      }
      
      if(!badName)
      {
         firstNode->addCon(secondNode);
      }
      
      lastReadGood = safeReadLine(file, nextLine);
   }
}
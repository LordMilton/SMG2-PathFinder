#include <string>
#include <cstring>
#include <queue>
#include <iostream>
#include <fstream>
#include "GalaxyMap.h"

#define MAX_LINE_LENGTH 200
#define AVAILABLE_MARKER "-A-"
#define GALAXIES_SEPARATOR "--- Galaxies ---"
//Character placed before stars to differentiate between stars and galaxies
#define STAR_INDICATOR '*'
#define CONNECTIONS_SEPARATOR "--- Connections ---"
//Character that goes inbetween the two galaxy names
#define CONNECTION_DELIMITER "-"
#define MAX_NODES 100
#define MAX_CONNECTIONS 4

GalaxyMap::GalaxyMap(int moveTime):Map()
{
   name = "";
   this->moveTime = moveTime;
   head = NULL;
}

GalaxyMap::~GalaxyMap()
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
      delete(next);
      next = NULL;
   }
}

std::string GalaxyMap::getName()
{
   return name;
}

void* GalaxyMap::containsNode(std::string name)
{
   std::queue<MapNode*> que;
   que.push(head);
   bool found = false;
   Galaxy* toReturn = NULL;
   while(!found && !que.empty())
   {
      MapNode* cur = que.front();
      if(cur->reached < 0)
      {
         if(((Galaxy*)(cur->getVal()))->getName() == name)
         {
            toReturn = (Galaxy*)(cur->getVal());
            found = true;
         }
         else
         {
            int numCons = 0;
            MapNode** cons = cur->getCons(numCons);
            for(int i = 0; i < numCons; i++)
            {
               que.push(cons[i]);
            }
         }
         cur->reached = 1; //Mark node as searched
      }
      
      que.pop();
   }
   head->resetReached();
   
   return toReturn;
}

int GalaxyMap::pathTime(std::string name1, std::string name2)
{
   
   return -1;
}

//Returns true as long as file's good bit is true
bool safeReadLine(std::ifstream* file, char line[MAX_LINE_LENGTH])
{
   if(file->is_open() && file->good())
   {
      file->getline(line,MAX_LINE_LENGTH);
   }
   return file->good();
}

GalaxyMap::MapNode* GalaxyMap::fetchNodeFromArray(MapNode* nodes[], int arrLen, std::string name)
{
   for(int i = 0; i < arrLen; i++)
   {
      MapNode* cur = nodes[i];
      if(((Galaxy*)(cur->getVal()))->getName() == name)
      {
         return cur;
      }
   }
   return NULL;
}

void GalaxyMap::readMapFromFile(std::string filename)
{
   std::ifstream specs;
   specs.open(filename);
   char nextLine[MAX_LINE_LENGTH];
   bool lastReadGood = true;
   if(specs.is_open())
   {
      //Name
      lastReadGood = safeReadLine(&specs, nextLine);
      if(lastReadGood)
      {
         name = nextLine;
      }
      else
      {
         std::cout << "Failure to parse Name section of Galaxy Map file";
         return;
      }
      
      //--- Galaxies ---
      MapNode* nodes[MAX_NODES];
      int numGalaxies = 0;
      lastReadGood = safeReadLine(&specs, nextLine); //Burn separator
      lastReadGood = safeReadLine(&specs, nextLine);
      bool firstGal = true;
      while(lastReadGood && (strcmp(nextLine, CONNECTIONS_SEPARATOR)) != 0)
      {
         bool available = false;
         int cutOff = 0; //How many characters of the line to cut off (takes care of AVAILABLE_MARKER if necessary)
         if(strstr(nextLine, AVAILABLE_MARKER) != NULL)
         {
            available = true;
            cutOff = strlen(AVAILABLE_MARKER);
         }
         nextLine[strlen(nextLine) - cutOff] = '\0'; // Cuts off the AVAILABLE_MARKER
         Galaxy* gal = new Galaxy(nextLine, available);
         
         lastReadGood = safeReadLine(&specs, nextLine);
         while(lastReadGood && nextLine[0] == STAR_INDICATOR)
         {
            Star* star = new Star(strtok(nextLine, STAR_INDICATOR + ""));
            gal->addStar(star);
            
            lastReadGood = safeReadLine(&specs, nextLine);
         }
         
         MapNode* node = new MapNode(gal, MAX_CONNECTIONS);
         if(firstGal)
         {
            head = node;
            firstGal = false;
         }
         nodes[numGalaxies++] = node;
      }
      
      //--- Connections ---
      // Separator already got burned in the last loop
      lastReadGood = safeReadLine(&specs, nextLine);
      while(lastReadGood) //Either until it fails or we reach EOF
      {
         std::string firstGalName = strtok(nextLine, CONNECTION_DELIMITER);
         std::string secondGalName = strtok(NULL, CONNECTION_DELIMITER);
         MapNode* firstNode = fetchNodeFromArray(nodes, numGalaxies, firstGalName);
         MapNode* secondNode = fetchNodeFromArray(nodes, numGalaxies, secondGalName);
         
         bool badName = false;
         if(firstNode == NULL)
         {
            std::cout << "\"" << firstGalName << "\" does not name a galaxy in file \"" << filename << "\"\n";
            badName = true;
         }
         if(secondNode == NULL)
         {
            std::cout << "\"" << secondGalName << "\" does not name a galaxy in file \"" << filename << "\"\n";
            badName = true;
         }
         
         if(!badName)
         {
            firstNode->addCon(secondNode);
         }
         
         lastReadGood = safeReadLine(&specs, nextLine);
      }
      
      specs.close();
   }
}
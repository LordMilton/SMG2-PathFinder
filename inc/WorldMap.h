#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <string>
#include "World.h"
#include "Map.h"

#define MAX_WORLD_CONNECTIONS 2 //Worlds are connected to at most 2 other Worlds

class WorldMap: public Map
{	private:

   //Similar to containsValue(), but returns the MapNode rather than the MapNode's value
   WorldMap::MapNode* containsNode(std::string name);
   
   //Helper method for readMapFromFile
   // Searches a list of MapNodes for one whose value has the matching name
   WorldMap::MapNode* fetchNodeFromArray(MapNode* nodes[], int arrLen, std::string name);
   
   //Returns true as long as file's good bit is true
   bool safeReadLine(std::ifstream* file, char line[]);
   //Reads the World section of the file
   void readWorldsFromFile(std::string filename, std::ifstream* file, char line[], MapNode* nodes[], int* numWorlds);
   //Reads the Connections section of the file
   void readConsFromFile(std::string filename, std::ifstream* file, char line[], MapNode* nodes[], int numWorlds);
   
   public:
   WorldMap(int moveTime);
   
   ~WorldMap();
   
   std::string getName(); 
   void* containsValue(std::string name);
	int pathTime(std::string name1, std::string name2);
   void readMapFromFile(std::string fileName);
};


#endif
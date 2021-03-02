#ifndef GALAXYMAP_H
#define GALAXYMAP_H

#include <string>
#include "Galaxy.h"
#include "Map.h"

#define MAX_GALAXY_CONNECTIONS 5 //Galaxies are probably connected to at most 4 other
                                 //Galaxies

class GalaxyMap: public Map
{	private:
   //MapNodes from connected worlds for pathfinding
   MapNode* prevWorldCon;
   MapNode* nextWorldCon;
   //Last and first MapNodes from this world so we know
   //  when we need to jump to another world for pathfinding
   MapNode* firstNode;
   MapNode* lastNode;
   
   //Helper method for readMapFromFile
   // Searches a list of MapNodes for one whose value has the matching name
   GalaxyMap::MapNode* fetchNodeFromArray(MapNode* nodes[], int arrLen, std::string name);
   
   //Similar to containsValue(), but returns the MapNode rather than the MapNode's value
   GalaxyMap::MapNode* containsNode(std::string name);
   
   //Returns true as long as file's good bit is true
   bool safeReadLine(std::ifstream* file, char line[]);
   //Reads the Galaxies section of the file
   void readGalsFromFile(std::string filename, std::ifstream* file, char line[], MapNode* nodes[], int* numGals);
   //Reads the Connections section of the file
   void readConsFromFile(std::string filename, std::ifstream* file, char line[], MapNode* nodes[], int numGals);
   
   public:
   GalaxyMap(int moveTime);
   ~GalaxyMap();

   std::string getName();
   void* containsValue(std::string name);
	int pathTime(std::string name1, std::string name2);
   void readMapFromFile(std::string fileName);
};


#endif
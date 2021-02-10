#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <string>
#include "World.h"
#include "Map.h"

#define MAX_WORLD_CONNECTIONS 2 //Worlds are connected to at most 2 other Worlds

class WorldMap: public Map
{	private:
   
   public:
   WorldMap();
   
   virtual MapNode* containsValue(std::string name);
	virtual int pathTime(std::string name1, std::string name2);
   virtual void readMapFromFile(std::string fileName);
};


#endif
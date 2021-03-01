#ifndef WORLD_H
#define WORLD_H

#include <string>
#include "Galaxy.h"
#include "GalaxyMap.h"

class World
{  private:
   std::string name;
   bool available;
   GalaxyMap* map;
   
   public:
   World(std::string name, GalaxyMap* galaxyMap, bool available=false);
   
   ~World();
   
   std::string getName();
   
   //Used to access a galaxy in this world by name
	//Returns NULL if no galaxy in this world exists with the given name
   Galaxy* containsGalaxy(std::string name);
   
   //Returns the GalaxyMap* from this World
   GalaxyMap* getMap();
   
   //Returns whether this World is available
   bool isAvailable();
   
   //Used to indicate that at least one Galaxy in this World is available
   //    (and therefore that this World is available)
   void makeAvailable();
};

#endif
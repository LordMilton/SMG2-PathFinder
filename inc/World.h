#ifndef WORLD_H
#define WORLD_H

#include <string>
#include "Galaxy.h"
#include "GalaxyMap.h"

class World
{  private:
   std::string name;
   int numGalaxies;
   GalaxyMap* map;
   
   public:
   World(std::string name, int numGalaxies, GalaxyMap* galaxyMap);
   
   std::string getName();
   
   //Used to access a galaxy in this world by name
	//Returns NULL if no galaxy in this world exists with the given name
   Galaxy* containsGalaxy(std::string name);
   
};

#endif
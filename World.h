#ifndef WORLD_H
#define WORLD_H

#include <string>
#include "Galaxy.h"
#include "GalaxyMap.h"

class World
{  private:
   String name;
   int numGalaxies;
   GalaxyMap* map;
   
   public:
   World(String name, int numGalaxies, GalaxyMap* galaxyMap);
   
   String getName();
   
   //Used to access a galaxy in this world by name
	//Returns NULL if no galaxy in this world exists with the given name
   Galaxy* containsGalaxy(String name);
   
}

#endif
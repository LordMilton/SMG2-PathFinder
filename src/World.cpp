#include "World.h"
#include "GalaxyMap.h"
#include "Galaxy.h"

World::World(std::string name, GalaxyMap* galaxyMap)
{
   map = galaxyMap;
   this->name = name;
}

World::~World()
{
}

std::string World::getName()
{
   return name;
}

Galaxy* World::containsGalaxy(std::string name)
{
   if(map == NULL)
   {
      return NULL;
   }
   return (Galaxy*)(map->containsValue(name));
}

GalaxyMap* World::getMap()
{
   return map;
}
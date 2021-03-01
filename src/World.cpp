#include "World.h"
#include "GalaxyMap.h"
#include "Galaxy.h"

World::World(std::string name, GalaxyMap* galaxyMap, bool available)
{
   map = galaxyMap;
   this->name = name;
   this->available = available;
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

bool World::isAvailable()
{
   return available;
}

void World::makeAvailable()
{
   available = true;
}
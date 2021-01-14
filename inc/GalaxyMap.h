#ifndef GALAXYMAP_H
#define GALAXYMAP_H

#include <string>
#include "Galaxy.h"
#include "Map.h"

#define MAX_GALAXY_CONNECTIONS 5 //Galaxies are probably connected to at most 4 other
                                 //Galaxies

class GalaxyMap: public Map
{	private:
   
   public:
   GalaxyMap();
   ~GalaxyMap();

   void* containsNode(std::string name);
	int pathTime(std::string name1, std::string name2);
   void readMapFromFile(std::string fileName);
};


#endif
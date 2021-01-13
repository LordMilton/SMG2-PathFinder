#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <string>
#include "World.h"
#include "Map.h"

#define MAX_WORLD_CONNECTIONS 2 //Worlds are connected to at most 2 other Worlds

class WorldMap: public Map
{	private:
   class MapNode
   {
      World* world;
      int numCons;
      MapNode* cons[MAX_WORLD_CONNECTIONS];
      
      MapNode(World* world)
      {
         this->world = world;
         numCons = 0;
      }
      
      //Adds a connection for this MapNode pointing to the given MapNode
      //Necessary that both MapNodes exist when connections are added, so can't be done in constructor
      void addCon(MapNode* con)
      {
         if(numCons < MAX_WORLD_CONNECTIONS && !conExists(con))
         {
            cons[numCons++] = con;
         }
         con->addCon(this);
      }
      
      //Returns true if the given connection is already stored, false otherwise
      //Guard against connection duplication
      bool conExists(MapNode* con)
      {
         for(int i = 0; i < numCons; i++)
         {
            if(con == cons[i])
               return true;
         }
         return false;
      }
   };
   
   public:
   WorldMap();
   
};


#endif
#ifndef GALAXYMAP_H
#define GALAXYMAP_H

#include <string>
#include "Galaxy.h"
#include "Map.h"

#define MAX_CONNECTIONS = 5 //Galaxies are probably connected to at most 4 other
                            //Galaxies

class GalaxyMap: public Map
{	private:
   class MapNode
   {
      Galaxy* gal;
      MapNode* cons[MAX_CONNECTIONS];
      
      //Adds a connection for this MapNode pointing to the given MapNode
      //Necessary that both MapNodes exist when connections are added, so can't be done in constructor
      void addCon(MapNode* con)
      {
         if(numCons < MAX_CONNECTIONS && !conExists(con))
         {
            cons[numCons++] = con;
         }
         con.addCon(this);
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
   }   
   
   public:
   GalaxyMap();
}


#endif
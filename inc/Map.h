#ifndef MAP_H
#define MAP_H

#include <string>

class Map
{	protected:
   class MapNode
   {  private:
      void* val;
      int numCons;
      int maxCons;
      MapNode** cons;
      
      public:
      MapNode(void* val, int maxConnections)
      {
         this->val = val;
         maxCons = maxConnections;
         numCons = 0;
         cons = new MapNode*[maxCons];
      }
      
      ~MapNode()
      {
         delete cons;
      }
      
      //Adds a connection for this MapNode pointing to the given MapNode
      //Necessary that both MapNodes exist when connections are added, so can't be done in constructor
      void addCon(MapNode* con)
      {
         if(numCons < maxCons && !conExists(con))
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
   
   MapNode* head;
	int moveTime;
	
	public:
   Map(); //Placeholder for linker
   ~Map(); //Placeholder for linker
   
   //Checks if a node exists in this map with the given name
   //Returns the associated MapNode or NULL if one does not exist
   //    Return type is void* to fix an issue where MapNode class isn't being
   //    seen by child classes TODO fix that issue for real
	virtual void* containsNode(std::string name)=0;
   
   //Determines time it takes to traverse from the node with the given name name1
   //to the node with the given name name2
   //Returns -1 if either parameter does not refer to an existing node in this Map
	virtual int pathTime(std::string name1, std::string name2)=0;
   
   //Reads all the map nodes and connections from a file and builds a map out of them
   virtual void readMapFromFile(std::string fileName)=0;
};

Map::Map(){}
Map::~Map(){}

#endif
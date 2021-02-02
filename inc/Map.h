#ifndef MAP_H
#define MAP_H

#include <string>

class Map
{	protected:
   class MapNode
   {  private:
      std::string name; //Name so that even placeholder nodes (ones with no galaxies) can be located
      void* val;
      int numCons;
      int maxCons;
      //Contains pointers to all connected MapNodes
      //WARNING: when we start deleting MapNodes, this can have holes (NULL pointers)
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
         purgeFromConnectedNodes();
         delete cons;
         cons = NULL;
         val = NULL;
      }
      
      //Returns this MapNode's name
      std::string getName()
      {
         return name;
      }
      
      //Adds a connection for this MapNode pointing to the given MapNode *and*
      //    adds a symmetrical connection from the given MapNode to this MapNode
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
            if(cons[i] != NULL && con == cons[i])
               return true;
         }
         return false;
      }
      
      //Returns this MapNodes list of connections with any NULL pointers removed
      MapNode** getCons(int* size)
      {
         MapNode** arr = new MapNode*[maxCons];
         int arrSize = 0;
         for(int i = 0; i < numCons; i++)
         {
            if(cons[i] != NULL)
            {
               arr[arrSize++] = cons[i];
            }
         }
         
         *size = arrSize;
         return arr;
      }
      
      private:
      //Deletes the specified MapNode from the connection list
      //Supports cleaner deletion
      //This should only be used when the whole Map is being deleted
      //Intention is for it to only be used in our destructor
      void deleteCon(MapNode* con)
      {
         for(int i = 0; i < numCons; i++)
         {
            if(cons[i] != NULL && cons[i] == con)
            {
               cons[i] == NULL;
            }
         }
      }
      
      //Deletes this Node from the cons of all connected nodes
      //Should be used in preparation for deleting this node
      //This won't be effective if the graph this Map represents becomes directed
      void purgeFromConnectedNodes()
      {
         for(int i = 0; i < numCons; i++)
         {
            if(cons[i] != NULL)
            {
               cons[i]->deleteCon(this);
            }
         }
      }
   };
   
   MapNode* head;
   std::string name;
	int moveTime;
	
	public:
   inline Map();
   inline ~Map();
   
   //Returns this Map's name
   virtual std::string getName()=0;
   
   //Checks if a node exists in this map with the given name
   //Returns the associated MapNode's value or NULL if one (MapNode or value) does not exist
   //   This is NOT returning a MapNode
	virtual void* containsNode(std::string name)=0;
   
   //Determines time it takes to traverse from the node with the given name name1
   //to the node with the given name name2
   //Returns -1 if either parameter does not refer to an accessible node
	virtual int pathTime(std::string name1, std::string name2)=0;
   
   //Reads all the map nodes and connections from a file and builds a map out of them
   virtual void readMapFromFile(std::string fileName)=0;
};

Map::Map(){} //Placeholder for linker
Map::~Map(){} //Placeholder for linker

#endif
#ifndef MAP_H
#define MAP_H

#include <string>

class Map
{	protected:
   class MapNode
   {  private:
      //The contents of this MapNode
      //    Should have some kind of identifier for searching
      void* val;
      int numCons;
      int maxCons;
      //Contains pointers to all connected MapNodes
      //WARNING: when we start deleting MapNodes, this can have holes (NULL pointers)
      MapNode** cons;
      
      public:
      //Allows tracking shortest path when path finding
      // This is only for use by external classes, so it's being left public
      int reached;
      
      MapNode(void* val, int maxConnections)
      {
         this->val = val;
         maxCons = maxConnections;
         numCons = 0;
         cons = new MapNode*[maxCons];
         reached = -1;
      }
      
      //Deallocates connections
      //Also removes this node from its connections' connections lists
      ~MapNode()
      {
         purgeFromConnectedNodes();
         delete cons;
         cons = NULL;
         val = NULL;
      }
      
      //Resets the reached value for this MapNode and
      // recursively calls this for all connected MapNodes
      //As long as a Map contains no island nodes, this only needs to be called on one MapNode
      // to affect them all
      void resetReached()
      {
         if(reached >= 0)
         {
            reached = -1;
            for(int i = 0; i < numCons; i++)
            {
               cons[i]->resetReached();
            }
         }
         
      }
      
      //Return this MapNode's value
      void* getVal()
      {
         return val;
      }
      
      //Adds a connection for this MapNode pointing to the given MapNode *and*
      //    adds a symmetrical connection from the given MapNode to this MapNode
      //Necessary that both MapNodes exist when connections are added, so can't be done in constructor
      void addCon(MapNode* con)
      {
         if(numCons < maxCons && !conExists(con))
         {
            cons[numCons++] = con;
            con->addCon(this);
         }
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
      MapNode** getCons(int &size)
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
         size = arrSize;
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
               cons[i] = NULL;
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
   //Number of Nodes in this Map
   //Mainly for toArray()
   int numNodes;
	int moveTime;
   
   //Checks if a node exists in this map with a value with the given identifier
   //Returns the associated MapNode or NULL if one does not exist
   virtual MapNode* containsNode(std::string name)=0;
	
	public:
   inline Map();
   inline ~Map();
   
   //Returns this Map's name
   virtual std::string getName()=0;
   
   //Returns the Map's contents in an array, returns the size by way of the first parameter
   virtual void** toArray(int* arrSize)=0;
   
   //Checks if a node exists in this map with a value with the given identifier
   //Returns the associated MapNode's value or NULL if one (MapNode or value) does not exist
   //   This is NOT returning a MapNode
	virtual void* containsValue(std::string name)=0;
   
   //Determines time it takes to traverse from the node with the given name name1
   //to the node with the given name name2
   //Returns -1 if the first parameter does not refer to a node in this Map or
   //    if the second paramater does not refer to an accessible node
   //    (an "accessible" node is a node that is either in this Map, or in another Map that this
   //     map is somehow connected to)
	virtual int pathTime(std::string name1, std::string name2)=0;
   
   //Reads all the map nodes and connections from a file and builds a map out of them
   virtual void readMapFromFile(std::string fileName)=0;
};

Map::Map(){} //Placeholder for linker
Map::~Map(){} //Placeholder for linker

#endif
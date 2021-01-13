#ifndef MAP_H
#define MAP_H

#include <string>

class Map
{	protected:
	MapNode *nodes;
	int moveTime;
   class MapNode;
	
	public:
   //Checks if a node exists in this map with the given name
   //Returns the associated MapNode or NULL if one does not exist
	virtual MapNode containsNode(std::string name);
   
   //Determines time it takes to traverse from the node with the given name name1
   //to the node with the given name name2
   //Returns -1 if either parameter does not refer to an existing node in this Map
	virtual int pathTime(std::string name1, std::string name2);
   
   //Reads all the map nodes and connections from a file and builds a map out of them
   virtual void readMapFromFile(std::string fileName);
};


#endif
#ifndef MAP_H
#define MAP_H

#include <string>

class Map
{	private:
	MapNode *nodes;
	int moveTime;
	
	public:
	virtual bool containsNode(std::string name);
	
}

//TODO friend MapNode


#endif
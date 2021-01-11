#ifndef GALAXY_H
#define GALAXY_H

#include <string>
#include "Star.h"

#define MAX_STARS = 6 //Maximum number of stars in a galaxy should be 6
#define MAX_SUCCESSORS = 4 //Maximum number of successors should be 4

class Galaxy
{	private:
	int numStars;
	Star* stars[MAX_STARS];
	bool oneComplete; //At least one star completed
	bool available;
	int numSuccessors;
	Galaxy* successors[MAX_SUCCESSORS];
	
	public:
	Galaxy(bool available = false);
	
	void addStar(Star* toAdd);
	
	void addSuccessor(Galaxy* toAdd);

	//Used to access a star in this galaxy by name
	//Returns NULL if no star in this galaxy exists with the given name
	Star* getStar(std::string name);
	//Used to access a star in this galaxy by number (special stars will be last)
	//Returns NULL if given num is larger than the number of stars in this galaxy
	Star* getStar(int num);
	
	//Should be used when any star is completed
	void oneCompleted();
	
	//Should be used by predecessor to indicate this galaxy is now accessible
	void makeAvailable();
};

#endif
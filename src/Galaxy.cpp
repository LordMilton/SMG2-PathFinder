#include "Galaxy.h"

using namespace std;

Galaxy::Galaxy(bool available)
{
   numSuccessors = 0;
	numStars = 0;
	oneComplete = false;
	this->available = available;
}

bool Galaxy::addStar(Star* toAdd)
{
	stars[numStars++] = toAdd;
   return true;
}

bool Galaxy::addSuccessor(Galaxy* toAdd)
{
	successors[numSuccessors++] = toAdd;
   return true;
}

Star* Galaxy::getStar(string name)
{
	for(int i = 0; i < numStars; ++i)
	{
		if(stars[i]->getName().compare(name) == 0)
			return stars[i];
	}
	return NULL;
}

Star* Galaxy::getStar(int num)
{
	if(num > numStars || num < 1)
		return NULL;
	else
		return stars[num-1];
}

void Galaxy::oneCompleted()
{
	if(!oneComplete)
	{
		for(int i = 0; i < numSuccessors; ++i)
		{
			successors[i]->makeAvailable();
		}
		oneComplete = true;
	}
}

bool Galaxy::isAvailable()
{
   return available;
}

void Galaxy::makeAvailable()
{
	available = true;
}
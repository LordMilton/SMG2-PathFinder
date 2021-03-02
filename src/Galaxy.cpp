#include "Galaxy.h"

using namespace std;

Galaxy::Galaxy(string name, bool available)
{
   this->name = name;
   numSuccessors = 0;
	numStars = 0;
	oneComplete = false;
	this->available = available;
}

Galaxy::~Galaxy()
{
   for(int i = 0; i < numStars; i++)
   {
      delete stars[i];
   }
}

string Galaxy::getName()
{
   return name;
}

bool Galaxy::addStar(Star* toAdd)
{
   if(numStars < MAX_STARS)
   {
      for(int i = 0; i < numStars; i++)
      {
         if(toAdd->getName() == stars[i]->getName())
            return false;
      }
      stars[numStars++] = toAdd;
      return true;
   }
   else
      return false;
}

bool Galaxy::addSuccessor(Galaxy* toAdd)
{
   if(numSuccessors < MAX_SUCCESSORS)
   {
      successors[numSuccessors++] = toAdd;
      return true;
   }
   else
      return false;
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
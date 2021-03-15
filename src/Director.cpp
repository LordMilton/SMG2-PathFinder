#include <iostream>
#include <fstream>
#include "Director.h"
#include "WorldMap.h"
#include "Galaxy.h"

#define 

Director::Director(std::string stateFile)
{
   state = new WorldMap(300);
   state->readMapFromFile(stateFile);
}
   
Director::~Director()
{
   delete state;
}

int Director::onePath(std::string curGal, Galaxy* nextGal)
{
   return -1;
}

int Director::fullPath(std::string firstGal)
{
   return -1;
}

void Director::readSave(std::string fileName)
{
   
}

//TODO Use new toArray() methods
void Director::writeSave(std::string fileName)
{
   
}
#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "WorldMap.h"
#include "Galaxy.h"
#include <iostream>

class Director
{  private:
   WorldMap* state = NULL;
   std::string saveFilename;
   
   public:
   Director(std::string stateFile);
   
   ~Director();
   
   //Finds the path to the next fastest Star
   // Returns the total time to perform a full loop of the Star
   //    (Travel to the star, complete it, and be back on the bridge of the Starship Mario)
   // Replaces nextGal containing the next fastest Star
   int onePath(std::string curGal, Galaxy* nextGal);
   
   //Finds the full path (Reach 60 stars then defeat the final Bowser)
   // starting from the Galaxy with the provided name and with the current state
   //Returns the total time taken to path to and complete all necessary stars
   int fullPath(std::string firstGal);
   
   //Reads IL times from file with the given fileName
   void readSave(std::string fileName);
   
   //Writes stored IL times into file with the given fileName
   void writeSave(std::string fileName);
};

#endif
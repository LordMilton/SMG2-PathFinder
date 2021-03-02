#ifndef STAR_H
#define STAR_H

#include <string>

//Represents an individual level
class Star
{	private:
	std::string name;
	int time;
	int timeWithMedal;
	
	public:
	Star(std::string name);
   
   ~Star();
	
	void setTime(int time);
	void setTimeWithMedal(int time);
	
	std::string getName();
	int getTime();
	int getTimeWithMedal();
};

#endif
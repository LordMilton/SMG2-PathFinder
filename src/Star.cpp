#include <string>
#include "Star.h"

using namespace std;

Star::Star(string name)
{
	this->name = name;
	time = 3600000;
	timeWithMedal = 3600000;
}

void Star::setTime(int time)
{
	this->time = time;
}

void Star::setTimeWithMedal(int time)
{
	timeWithMedal = time;
}

string Star::getName()
{
	return name;
}

int Star::getTime()
{
	return time;
}

int Star::getTimeWithMedal()
{
	return timeWithMedal;
}

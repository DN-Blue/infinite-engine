#include "Time.h"

#include <time.h>




Infinite::Time::Time() {

}

Infinite::Time::~Time() {

}


void Infinite::Time::Start() {
	startTime = std::clock();
}

float Infinite::Time::Get() {
	float t = std::clock()-startTime;
	return t;
}
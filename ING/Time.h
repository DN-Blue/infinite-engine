#ifndef TIME_H
#define TIME_H

#include "INGLib.h"

namespace Infinite{

	class ING;

	class Time {
	public:
		Time();
		~Time();

	public:
		ING* pING;

	public:
		void Start();

		float Get();

		float  startTime;

	};


}

#endif
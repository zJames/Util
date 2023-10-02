//------------------------------------------------------------------------------
//  Copyright : (c) 2018
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "Test.h"

#include "../Util/Util_AllHeaders.h"
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
//	ReferenceCounterTest
//------------------------------------------------------------------------------
void testReferenceCounter()
{
	ReferenceCounter counter;

	printf("Empty Check: %s\n", (counter.current() == nothing) ? "pass" : "fail");

	counter.create();

	printf("Should be 1: %s\n", (counter.current() == 1) ? "pass" : "fail");

	{
		std::vector<ReferenceCounter> counters;

		for (int i = 0; i < 200; ++i)
		{
			counters.push_back(counter);
		}

		printf("Should be 201: %s\n", (counter.current() == 201) ? "pass" : "fail");
	}

	printf("Should be 1: %s\n", (counter.current() == 1) ? "pass" : "fail");

	{
		ReferenceCounter newCounter;

		newCounter.create();

		std::vector<ReferenceCounter> counters;

		for (int i = 0; i < 200; ++i)
		{
			counters.push_back(newCounter);
		}

		counter = newCounter;

		printf("Should be 202: %s\n", (counter.current() == 202) ? "pass" : "fail");
	}

	printf("Should be 1: %s\n", (counter.current() == 1) ? "pass" : "fail");

	Maybe<int> oldVal = counter.release();
	printf("Should be 0: %s\n", (oldVal == 0) ? "pass" : "fail");
}
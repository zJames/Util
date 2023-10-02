//------------------------------------------------------------------------------
//  Copyright : (c) 2018
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "Test.h"
#include "../Util/Util_AllHeaders.h"
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
//	Local Test Functions
//------------------------------------------------------------------------------
void testFunc1()
{
	printf("testFunc1 called.\n");
}

void testFunc2(int a, float b)
{
	printf("testFunc2 called with: %d, %f\n", a, b);
}

float testFunc3(float a)
{
	printf("testFunc3 called with: %f\n", a);

	return a;
}

void testFunc4(const Function<void()>& otherFunc)
{
	printf("testFunc4 called\n");
	otherFunc();
}


//------------------------------------------------------------------------------
//	FunctionTest
//------------------------------------------------------------------------------
void testFunction()
{
	Function<void()> test1 = func(testFunc1);

	test1();

	Function<void(int, float)> test2 = func(testFunc2);

	test2(42, float(M_PI));

	Function<void(float)> test3 = func(testFunc2, 72);

	test3(1234.56789f);

	Function<float(float)> test4 = func(testFunc3);

	{
		float testVal = 9876.54321f;
		
		const float retVal = test4(9876.54321f);

		printf(
			"Return value from test4: %f, %s\n",
			retVal,
			(retVal == testVal) ? "pass" : "fail");
	}

	{
		float testVal = float(M_PI);

		Function<float()> test5 = func(testFunc3, testVal);

		const float retVal = test5();

		printf(
			"Return value from test5: %f, %s\n",
			retVal,
			(retVal == testVal) ? "pass" : "fail");
	}

	//Function<void()> test6 = func(testFunc4, testFunc1);

	//test6();
}
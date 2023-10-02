//------------------------------------------------------------------------------
//  Copyright : (c) 2018
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "Test.h"
#include "../Util/Util_AllHeaders.h"
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
//	Local Const Data
//------------------------------------------------------------------------------
const int kTestInt = 42;


//------------------------------------------------------------------------------
//	MaybeTest
//------------------------------------------------------------------------------
void testMaybe()
{
	Maybe<bool> test1;
	Maybe<int> test2;

	printf(
		"[Maybe] test for empty: %s\n",
		(test1 == nothing)
			? "pass"
			: "fail");

	test1 = true;

	printf(
		"[Maybe] test for true: %s\n",
		(test1 == true)
			? "pass"
			: "fail");

	test1 = false;

	printf(
		"[Maybe] test for true: %s\n",
		(test1 == false)
			? "pass"
			: "fail");

	test2 = kTestInt;

	printf(
		"[Maybe] test for value: %s\n",
		(test2 == kTestInt)
			? "pass"
			: "fail");

	printf(
		"[Maybe] test for wrong value: %s\n",
		(test1 == kTestInt)
			? "fail"
			: "pass");
}
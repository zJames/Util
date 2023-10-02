//------------------------------------------------------------------------------
//  Copyright : (c) 2015
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "Test.h"

#include "../Util/Util_AllHeaders.h"
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
//	DefaultsTest
//------------------------------------------------------------------------------
void testDefaults()
{
	const Config::Default kDefaults[] =
	{
		{ "test", "42" },
		{ "testTwo", "42,72" },
	};

	Config::Chain chain(new Config::Defaults(kDefaults, ARRAY_LENGTH(kDefaults)));

	{
		Config::Option<int> testOption("test");
		int testValue = chain.get(testOption);

		if (testValue != 42)
		{
			throw "testOption: unexpected value";
		}
	}

	{
		Config::Option<std::vector<int> > testTwoOption("testTwo");
		std::vector<int> testValues = chain.get(testTwoOption);
		int checkValues[] = {42, 72};

		for (size_t i = 0; i < ARRAY_LENGTH(checkValues); ++i)
		{
			if (!contains(testValues, checkValues[i]))
			{
				throw "testTwoOption: text not found";
			}
		}
	}
}
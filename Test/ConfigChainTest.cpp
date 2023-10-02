//------------------------------------------------------------------------------
//  Copyright : (c) 2015
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "Test.h"
#include "../Util/Util_AllHeaders.h"
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
//	Local Functions
//------------------------------------------------------------------------------
Config::Chain::BaseList getChain()
{
	static const Config::Default kDefaults[] =
	{
		{"stringList", "test1,test2,test3"},
		{"intList", "0,1,2,3,4"},
		{"intArray", "5,6,7,8,9"},
		{"falseBool", "true"},
	};

	static const char* args[] =
	{
		"scope.exe",
		"/string:value",
		"/stringArray:test4,test5,test6",
		"/int:42",
		"/intList:0,1,2,3,4",
		"/intArray:5,6,7,8,9",
		"/falseBool:false",
		"/trueBool:true"
	};

	Config::Chain::BaseList chain;

	chain.push_back(new Config::CommandLine(args, ARRAY_LENGTH(args)));
	chain.push_back(new Config::Defaults(kDefaults, ARRAY_LENGTH(kDefaults)));

	return chain;
}

//------------------------------------------------------------------------------
//	testConfigChain
//------------------------------------------------------------------------------
void testConfigChain()
{
	auto chain = getChain();

	if (chain.empty())
	{
		throw "getChain: Chain generation was unsuccessful.";
	}

	Config::Chain objectUnderTest(chain);

	if (!chain.empty())
	{
		throw "Chain constructor did not take ownership of chain values.";
	}
	
	{
		Config::Option<std::string> stringOption("string");

		std::string testValue = objectUnderTest.get(stringOption);

		if (testValue != "value")
		{
			throw "stringOption: Unexpected value";
		}
	}

	{
		Config::Option<std::list<std::string> > stringListOption("stringList");
		std::list<std::string> testValues = objectUnderTest.get(stringListOption);
		const std::string checkValues[] = {"test1", "test2", "test3"};

		for (size_t i = 0; i < ARRAY_LENGTH(checkValues); ++i)
		{
			if (!contains(testValues, checkValues[i]))
			{
				throw "stringListOption: text not found";
			}
		}
	}

	{
		Config::Option<std::vector<std::string> > stringArrayOption("stringArray");
		std::vector<std::string> testValues = objectUnderTest.get(stringArrayOption);
		const std::string checkValues[] = {"test4", "test5", "test6"};

		for (size_t i = 0; i < ARRAY_LENGTH(testValues); ++i)
		{
			if (!contains(testValues, checkValues[i]))
			{
				throw "stringArrayOption: text not found";
			}
		}
	}

	{
		Config::Option<int> intOption("int");
		int testValue = objectUnderTest.get(intOption);

		if (testValue != 42)
		{
			throw "intOption: Unexpected value";
		}
	}

	{
		Config::Option<std::list<int> > intListOption("intList");
		std::list<int> testValues = objectUnderTest.get(intListOption);
		int checkValues[] = { 0, 1, 2, 3, 4 };

		for (size_t i = 0; i < ARRAY_LENGTH(checkValues); ++i)
		{
			if (!contains(testValues, checkValues[i]))
			{
				throw "intListOption: text not found";
			}
		}
	}

	{
		Config::Option<std::vector<int> > intArrayOption("intArray");
		std::vector<int> testValues = objectUnderTest.get(intArrayOption);
		int checkValues[] = { 5, 6, 7, 8, 9 };

		for (size_t i = 0; i < ARRAY_LENGTH(checkValues); ++i)
		{
			if (!contains(testValues, checkValues[i]))
			{
				throw "intArrayOption: text not found";
			}
		}
	}
	
	{
		Config::Option<bool> falseBoolOption("falseBool");
		bool testValue = objectUnderTest.get(falseBoolOption);

		if (testValue != false)
		{
			throw "falseBoolOption: Unexpected value";
		}
	}

	{
		Config::Option<bool> trueBoolOption("trueBool");
		bool testValue = objectUnderTest.get(trueBoolOption);

		if (testValue != true)
		{
			throw "trueBoolOption: Unexpected value";
		}
	}

	{
		Config::Option<const char*> notFoundOption("notFound");
		const char* testValue = objectUnderTest.get(notFoundOption);

		if (testValue != NULL)
		{
			throw "notFoundOption: Unexpected value";
		}
	}
}
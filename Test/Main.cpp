//------------------------------------------------------------------------------
//  Copyright : (c) 2015
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "Test.h"

#include "../Util/Util_AllHeaders.h"
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
//	Local Types
//------------------------------------------------------------------------------
struct TestFunc
{
	void(*function)();
	const char* name;
};


//------------------------------------------------------------------------------
//	Local Data
//------------------------------------------------------------------------------
TestFunc kTestFunctions[] =
{
	{ testBlockArray,		"testBlockArray"		},
	{ testSharedPtr,		"testSharedPtr"			},
	{ testReferenceCounter, "testReferenceCounter"	},
	{ testEnumChain,		"testEnumChain"			},
	{ testConfigChain,		"testConfigChain"		},
	{ testDefaults,			"testDefaults"			},
	{ testCommandLine,		"testCommandLine"		},
	{ testDomXml,			"testDomXml"			},
	{ testMaybe,			"testMaybe"				},
	{ testFunction,			"testFunction"			},
	{ testAdapt,			"testAdapt"				},
	{ testProcess,			"testProcess"			},
	{ testRefString,		"testRefString"			},
};


//------------------------------------------------------------------------------
//	Main
//------------------------------------------------------------------------------
int main()
{
	for (int i = 0; i < ARRAY_LENGTH(kTestFunctions); ++i)
	{
		try
		{
			printf("[Testing: %s]\n", kTestFunctions[i].name);
			kTestFunctions[i].function();
			printf("\n");
		}
		catch (const char* text)
		{
			printf("Exception in %s: %s.\n", kTestFunctions[i].name, text);
		}
		catch (...)
		{
			printf("Exception in %s.\n", kTestFunctions[i].name);
		}
	}

	return 0;
}

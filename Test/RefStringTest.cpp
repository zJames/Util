//------------------------------------------------------------------------------
//  Copyright : (c) 2015
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "Test.h"

#include "../Util/Util_AllHeaders.h"
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
//	RefStringTest
//------------------------------------------------------------------------------
void testRefString()
{
	const char* kLongerString = "This is a test string that should not display fully";

	RefString test = "test";
	RefString test2 = test;

	test2 += " more test";

	RefString test3 = test2;
	RefString test4 = test + " " + test;

	RefString test5;

	test5.resize(1024);

	test5 += test;
	test5 += " ";
	test5 += test4;

	RefString test6 = RefString::copy(kLongerString, strlen(kLongerString) / 2);
	RefString test7 = RefString("[Text] ") + test6;

	test7 += " <end>";

	printf("test: %s\n", test.const_ptr());
	printf("test2: %s\n", test2.const_ptr());
	printf("test3: %s\n", test3.const_ptr());
	printf("test4: %s\n", test4.const_ptr());
	printf("test5: %s\n", test5.const_ptr());
	printf("test6: %s\n", test6.const_ptr());
	printf("test7: %s\n", test7.const_ptr());
}
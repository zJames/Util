//------------------------------------------------------------------------------
//  Copyright : (c) 2015
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "Test.h"
#include "../Util/Util_AllHeaders.h"
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
//	Test
//------------------------------------------------------------------------------
void printBlockArray(BlockArray<int>& blocks)
{
	int idx = 0;

	printf("BlockArray Size: %zd\n", blocks.size());

	for (BlockArray<int>::Iterator i = blocks.begin(); i != blocks.end(); ++i, ++idx)
	{
		printf("BlockArray idx(%d): %d\n", idx, *i);
	}
}

void testBlockArray()
{
	BlockArray<int> objectUnderTest;

	for (int i = 0; i < 10; ++i)
	{
		objectUnderTest.construct(i);
	}

	printf("BlockArray should be 0 to 9, sequential.\n");
	printBlockArray(objectUnderTest);

	for (int i = 0; i < 3; ++i)
	{
		objectUnderTest.pop_front();
		objectUnderTest.pop_back();

		printf("\n");
		printBlockArray(objectUnderTest);
	}

	for (int i = 0; i < 3; ++i)
	{
		objectUnderTest.construct(i);
	}

	for (int i = 0; i < 3; ++i)
	{
		objectUnderTest.construct(7 + i);
	}

	printf("\n");
	printBlockArray(objectUnderTest);
}

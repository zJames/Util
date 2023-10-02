//------------------------------------------------------------------------------
//  Copyright : (c) 2018
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "Test.h"

#include "../Util/Util_AllHeaders.h"
////////////////////////////////////////////////////////////////////////////////


class TestProcess : public Process
{
public:
	TestProcess(std::function<void()> toRun)
		:
		toRun(toRun)
	{
	}

	std::function<void()> toRun;

protected:
	virtual void update()
	{
		toRun();
	}
};


Process* createTestProcess4()
{
	return new TestProcess([]() { printf("Ran Test 4\n"); });
}



//------------------------------------------------------------------------------
//	ProcessTest
//------------------------------------------------------------------------------
void testProcess()
{
	ProcessList root;

	root.add(new TestProcess([](){ printf("Ran Test 1\n"); }));

	root.exec();

	root.queueDeleteAll();
	root.add(new TestProcess([]() { printf("Ran Test 2\n"); }));

	root.exec();

	root.deleteAll();

	{
		Process* p = new TestProcess([]() { printf("Ran Test 3\n"); });
		root.add(p);

		p->queueReplace(createTestProcess4);
	}

	root.exec();
	root.exec();
}
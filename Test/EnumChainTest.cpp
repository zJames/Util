//------------------------------------------------------------------------------
//  Copyright : (c) 2015
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "Test.h"
#include "../Util/Util_AllHeaders.h"
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
//	EnumChainTest
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//	Local Enumerations
//------------------------------------------------------------------------------
enum EFirst
{
	eFirst_num = 4
};


enum ESecond
{
	eSecond_num = 5,
};


//------------------------------------------------------------------------------
//	Local Types
//------------------------------------------------------------------------------
typedef EmptyChain::Append<EFirst, eFirst_num>::Result FirstEnum;
typedef FirstEnum::Append<ESecond, eSecond_num>::Result SecondEnum;


//------------------------------------------------------------------------------
//	Local Functions
//------------------------------------------------------------------------------
template<class T>
RefString maybeToString(const Maybe<T>& maybe)
{
	if (!maybe.get())
	{
		return "nothing";
	}

	char temp[128];

	sprintf_s(temp, "%d", *maybe);

	return temp;
}

void printEnum(const char* baseText, const FirstEnum& enumVal)
{
	const Maybe<EFirst>& val = enumVal.get<EFirst>();

	printf(baseText, enumVal.val(), maybeToString(val).c_str());
}

void printEnum2(const char* baseText, const SecondEnum& enumVal)
{
	const Maybe<EFirst>& val = enumVal.get<EFirst>();
	const Maybe<ESecond>& val2 = enumVal.get<ESecond>();

	printf(baseText, enumVal.val(), maybeToString(val).c_str(), maybeToString(val2).c_str());
}


//------------------------------------------------------------------------------
//	Global Test Function
//------------------------------------------------------------------------------
void testEnumChain()
{
	FirstEnum e(EFirst(1));
	SecondEnum f(ESecond(1));
	SecondEnum g(EFirst(1));

	printEnum("e: raw(%d), EFirst(%s)\n", e);
	printEnum2("f: raw(%d), EFirst(%s), ESecond(%s)\n", f);
	printEnum2("g: raw(%d), EFirst(%s), ESecond(%s)\n", g);
}
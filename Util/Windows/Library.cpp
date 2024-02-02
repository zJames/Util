//------------------------------------------------------------------------------
//  Copyright : (c) 2022
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "Library.h"
////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// Library
//------------------------------------------------------------------------------

Library::Library()
	:
	mModule(NULL)
{
}

Library::Library(RefString file)
	:
	mModule(NULL)
{
	load(file);
}

void Library::load(RefString file)
{
	release();

	mModule = LoadLibraryA(file);
}

void Library::release()
{
	if (mModule != NULL)
	{
		FreeLibrary(mModule);
	}
}

FARPROC Library::findProc(RefString name)
{
	return (mModule == NULL) ? NULL : GetProcAddress(mModule, name);;
}

Library& Library::operator=(Library& other)
{
	release();

	mModule = other.mModule;
	other.mModule = NULL;

	return *this;
}

bool Library::isValid() const
{
	return mModule != NULL;
}

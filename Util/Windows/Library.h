//------------------------------------------------------------------------------
//  Copyright : (c) 2022
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#pragma once

#include "WindowsInc.h"

#include "..\Text\RefString.h"
////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
//	Library
//------------------------------------------------------------------------------
class Library
{
public:
	Library();
	Library(RefString file);

	void load(RefString file);
	void release();
	FARPROC findProc(RefString name);

	Library& operator =(Library& other);

	bool isValid() const;

private:
	HMODULE mModule;
};


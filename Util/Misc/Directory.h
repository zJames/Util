//------------------------------------------------------------------------------
//  Copyright : (c) 2022
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#pragma once

#include "..\Text\RefString.h"

#include <list>
////////////////////////////////////////////////////////////////////////////////

namespace Directory
{
//------------------------------------------------------------------------------
//	Directory Functions
//------------------------------------------------------------------------------
RefString fileName(); //Returns the filename of the current module
RefString current(); //Returns the current directory

std::list<RefString> enumerate(RefString path);
std::list<RefString> enumerate(RefString path, RefString extension); //Filters files by extension, requires "." in front
std::list<RefString> enumerateEx(RefString match); //Can take a file list with supported Windows' wildcards

} //end namespace Directory

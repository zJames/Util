//------------------------------------------------------------------------------
//  Copyright : (c) 2022
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#pragma once

#include "WindowsInc.h"

#include "..\Containers\Maybe.h"
////////////////////////////////////////////////////////////////////////////////


namespace Windows
{
//------------------------------------------------------------------------------
//	DesktopWorker
//------------------------------------------------------------------------------
BOOL __stdcall enumProc(HWND hWnd, LPARAM param);
Maybe<HWND> findWallpaperWindow(HWND hTopWindow);
Maybe<HWND> createWorker();
HINSTANCE moduleHandle();

} //end namespace Windows

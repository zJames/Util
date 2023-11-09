//------------------------------------------------------------------------------
//  Copyright : (c) 2008
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#pragma once

#include "Rect.h"
#include "WindowsInc.h"
#include "..\Text\RefString.h"

#include <list>
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
//	Information About Each Monitor
//------------------------------------------------------------------------------
struct MonitorInfo
{
	HMONITOR hMonitor; // handle to display monitor
	HDC hdcMonitor; // handle to monitor DC
	Rect rcMonitor; // monitor rectangle
	Rect rcWork; // "work" area of the monitor, IE no taskbar
	DWORD dwFlags;
	RefString name;
	int index;
};


//------------------------------------------------------------------------------
//	Enumerates the monitors and stores their info. If dpiAdjust is true, the
//  rcMonitor is adjusted to pixels from the dpi information
//------------------------------------------------------------------------------
void enumerateMonitors(std::list<MonitorInfo>* monitorInfo, bool dpiAdjust);

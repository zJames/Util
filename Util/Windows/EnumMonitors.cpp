//------------------------------------------------------------------------------
//  Copyright : (c) 2008
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "EnumMonitors.h"

#include "..\Math\Interp.h"

#include <shellscalingapi.h>
#include <vector>
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
//	Local Const Data
//------------------------------------------------------------------------------
const UINT kDefaultScale = 72;


//------------------------------------------------------------------------------
//	Enum Monitors Implementation
//------------------------------------------------------------------------------
BOOL CALLBACK monitorEnumProc(
	HMONITOR hMonitor,	// handle to display monitor
	HDC hdcMonitor,		// handle to monitor DC
	LPRECT lprcMonitor,	// monitor intersection rectangle
	LPARAM dwData)		// data
{
	if (dwData == NULL)
	{
		return FALSE;
	}

	MonitorInfo newInfo;

	newInfo.hMonitor = hMonitor;
	newInfo.hdcMonitor = hdcMonitor;

	MONITORINFOEX monInfo = { 0 };

	monInfo.cbSize = sizeof(monInfo);

	GetMonitorInfo(hMonitor, &monInfo);

	newInfo.dwFlags = monInfo.dwFlags;
	newInfo.rcMonitor = monInfo.rcMonitor;
	newInfo.rcWork = monInfo.rcWork;
	newInfo.name = RefString::copy(monInfo.szDevice);

	reinterpret_cast<std::list<MonitorInfo>*>(dwData)->push_back(newInfo);

	return TRUE;
}


void enumerateMonitors(std::list<MonitorInfo>* monitorInfo, bool dpiAdjust)
{
	EnumDisplayMonitors(NULL, NULL, monitorEnumProc, (LPARAM)monitorInfo);

	std::vector<int> indices;
	
	for (int i = 0; i < monitorInfo->size(); ++i)
	{
		DISPLAY_DEVICEA deviceInfo = { 0 };
		deviceInfo.cb = sizeof(deviceInfo);

		EnumDisplayDevicesA(NULL, i, &deviceInfo, EDD_GET_DEVICE_INTERFACE_NAME);

		for (auto& monitor : *monitorInfo)
		{
			if (monitor.name == deviceInfo.DeviceName)
			{
				monitor.index = i;
			}
		}
	}

	if (dpiAdjust)
	{
		for (auto& monitor : *monitorInfo)
		{
			MONITORINFOEX monInfo = { 0 };

			monInfo.cbSize = sizeof(monInfo);

			GetMonitorInfo(monitor.hMonitor, &monInfo);

			DEVMODE devmode = { 0 };

			devmode.dmSize = sizeof(DEVMODE);

			EnumDisplaySettings(monInfo.szDevice, ENUM_CURRENT_SETTINGS, &devmode);

			//Adjust work rect for real pixels
			monitor.rcWork.right = interp(monitor.rcWork.left, monitor.rcWork.right, double(devmode.dmPelsWidth) / monitor.rcMonitor.width());
			monitor.rcWork.bottom = interp(monitor.rcWork.top, monitor.rcWork.bottom, double(devmode.dmPelsHeight) / monitor.rcMonitor.height());

			//Adjust monitor rect for real pixels
			monitor.rcMonitor.right = monitor.rcMonitor.left + devmode.dmPelsWidth;
			monitor.rcMonitor.bottom = monitor.rcMonitor.top + devmode.dmPelsHeight;
		}
	}
}
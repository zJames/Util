//------------------------------------------------------------------------------
//  Copyright : (c) 2022
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "DesktopWorker.h"

#include "..\Core\Debug.h"
#include "..\Text\RefString.h"
////////////////////////////////////////////////////////////////////////////////


namespace Windows
{
//------------------------------------------------------------------------------
//	Local Const Data
//------------------------------------------------------------------------------
const RefString kHookTarget = "Progman";
const RefString kWorkerWindow = "WorkerW";
const RefString kShellWindow = "SHELLDLL_DefView";
const UINT16 kSecretMessage = 0x052C;


//------------------------------------------------------------------------------
// DesktopWorker
//------------------------------------------------------------------------------
BOOL __stdcall enumProc(HWND hWnd, LPARAM param)
{
	HWND hShell = FindWindowEx(hWnd, NULL, kShellWindow, NULL);

	if (!hShell)
	{
		//continue search
		return TRUE;
	}

	HWND hWorker = FindWindowEx(NULL, hWnd, kWorkerWindow, NULL);

	if (!hWorker)
	{
		//continue search
		return TRUE;
	}

	*(HWND*)param = hWorker;

	//stop search
	return FALSE;
}

Maybe<HWND> findWallpaperWindow(HWND hTopWindow)
{
	HWND result = 0;

	//Go through all the Windows until we find the one that matches
	EnumWindows(&enumProc, LPARAM(&result));

	if (result != 0)
	{
		return result;
	}

	//We didn't find our target
	LogDebugArgs("Unable to find wallpaper window: %08X\n", hTopWindow);
	return nothing;
}

Maybe<HWND> createWorker()
{
	//Find the Desktop handler
	HWND hProgman = FindWindow(kHookTarget, NULL);

	if (!hProgman)
	{
		LogDebug("Unable to find top level Window\n");
		return nothing;
	}

	SendMessage(hProgman, kSecretMessage, WPARAM(0x000D), LPARAM(1));

	return findWallpaperWindow(hProgman);
}

HINSTANCE moduleHandle()
{
	HMODULE hModule = NULL;

	GetModuleHandleEx(
		GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
		(LPCSTR)&createWorker,
		&hModule);

	return hModule;
}

} //end namespace Windows

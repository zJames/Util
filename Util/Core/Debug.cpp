//------------------------------------------------------------------------------
//  Copyright : (c) 2015
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "Debug.h"

#include "File.h"
#include "../Util.h"
#include "../Misc/TextManip.h"
#include "../Text/RefString.h"

#include <time.h>
#include <stdarg.h>
#include <windows.h>
#include <Psapi.h>
////////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG

static const RefString kBaseFolder = "D:\\Logs\\";

//------------------------------------------------------------------------------
//	Local Functions
//------------------------------------------------------------------------------
tm* getTime()
{
	static tm s_tm;

	time_t t = time(NULL);

	localtime_s(&s_tm, &t);

	return &s_tm;
}

const char* getTimeStr()
{
	static char kTimeBuffer[64];

	strftime(kTimeBuffer, ARRAY_LENGTH(kTimeBuffer), "%Y-%m-%d %OH:%M:%S", getTime());

	return kTimeBuffer;
}

RefString debugFileName()
{
	RefString moduleName(256);

	HMODULE hModule = NULL;

	if (!GetModuleHandleEx(
			GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
			(LPCSTR)&getTimeStr,
			&hModule))
	{
		return kBaseFolder + "Default.txt";
	}
	
	if (!GetModuleFileName(hModule, moduleName.ptr(), DWORD(moduleName.dataSize())))
	{
		return kBaseFolder + "Default.txt";
	}

	//GetModuleFileName(NULL, moduleName.ptr(), DWORD(moduleName.dataSize()));

	return kBaseFolder + plainName(moduleName) + "_Debug.txt";
}

File& getDebugText()
{
	static File sDebugText;

	if (!sDebugText.isValid())
	{
		sDebugText.open(debugFileName(), File::eOption_Append_Text);
	}

	return sDebugText;
}


//------------------------------------------------------------------------------
//	Debug
//------------------------------------------------------------------------------
void LogDebug(const char* text)
{
	OutputDebugString(text);
	fprintf(getDebugText(), "%s %s", getTimeStr(), text);
	fflush(getDebugText());
}

void LogDebugArgs(const char* text, ...)
{
	static char strBuffer[2048];

	va_list args;
	va_start(args, text);
	vsprintf_s(strBuffer, 512, text, args);
	strBuffer[511] = L'\0';
	va_end(args);

	LogDebug(strBuffer);
}

void LogDebugW(const wchar_t* text)
{
	OutputDebugStringW(text);
	fwprintf(getDebugText(), text);
	fflush(getDebugText());
}

void LogDebugArgsW(const wchar_t* text, ...)
{
	static wchar_t strBuffer[2048];

	va_list args;
	va_start(args, text);
	vswprintf_s(strBuffer, 512, text, args);
	strBuffer[511] = L'\0';
	va_end(args);

	LogDebugW(strBuffer);
}

#endif
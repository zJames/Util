//------------------------------------------------------------------------------
//  Copyright : (c) 2022
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "Directory.h"

#include "TextIterator.h"
#include "TextManip.h"
#include "..\Windows\WindowsInc.h"

#include <filesystem>
////////////////////////////////////////////////////////////////////////////////


namespace Directory
{
//------------------------------------------------------------------------------
// Directory Implementation
//------------------------------------------------------------------------------
RefString fileName()
{
	RefString file(512);

	GetModuleFileName(NULL, file.ptr(), DWORD(file.dataSize()));

	return file;
}

RefString current()
{
	return directoryPath(fileName());
}

std::list<RefString> enumerate(RefString path)
{
	std::list<RefString> files;

	std::string strPath = path.c_str();

	try
	{
		for (const auto& entry : std::filesystem::directory_iterator(strPath))
		{
			const std::string entryPath = entry.path().string();

			files.push_back(RefString::copy(entryPath.c_str()));
		}
	}
	catch (...)
	{
		//Likely the directory just didn't exist, which is okay
	}

	return files;
}

std::list<RefString> enumerate(RefString path, RefString extension)
{
	std::list<RefString> files;

	std::string strPath = path.c_str();

	try
	{
		for (const auto& entry : std::filesystem::directory_iterator(strPath))
		{
			if (entry.path().extension() != extension.const_ptr())
			{
				continue;
			}

			const std::string entryPath = entry.path().string();

			files.push_back(RefString::copy(entryPath.c_str()));
		}
	}
	catch (...)
	{
		//Likely the directory just didn't exist, which is okay
	}

	return files;
}

std::list<RefString> enumerateEx(RefString match)
{
	std::list<RefString> files;

	for (TextIterator it(match.ptr(), ','); it.get(); ++it)
	{
		WIN32_FIND_DATA find = { 0 };
		HANDLE hFind = FindFirstFile(it.get(), &find);

		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				RefString fileName(find.cFileName);

				if (!fileName.empty())
				{
					files.push_back(fileName);
				}
			} while (FindNextFile(hFind, &find));
		}
	}

	return files;
}

} //end namespace Directory

//------------------------------------------------------------------------------
//  Copyright : (c) 2023
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "LoadJPEG.h"

#include "ARGB.h"
#include "Bitmap.h"

#include "..\Pointers\ScopedPtr.h"
#include "..\Misc\Convert.h"

#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
// LoadJPEG
//------------------------------------------------------------------------------
bool loadJPEG(const char* szFileName, Bitmap& output)
{
	bool success = false;

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	const RefStringW fileNameW = convertToW(szFileName);
	ScopedPtr<Gdiplus::Bitmap> image(new Gdiplus::Bitmap(fileNameW.c_str()));

	output.setSize(
		int(image->GetWidth()),
		int(image->GetHeight()),
		Bitmap::F_A8R8G8B8);

	for (int y = 0; y < output.height(); ++y)
	{
		ARGB* line = (ARGB*)output.linePtr(y);

		for (int x = 0; x < output.width(); ++x)
		{
			Gdiplus::Color pixel(Gdiplus::Color::White);
			image->GetPixel(x, y, &pixel);

			line[x].alpha = pixel.GetAlpha();
			line[x].red = pixel.GetRed();
			line[x].green = pixel.GetGreen();
			line[x].blue = pixel.GetBlue();
		}
	}

	// delete the image when done 
	image.set(nullptr);

	// Shutdown Gdiplus 
	Gdiplus::GdiplusShutdown(gdiplusToken);

	return success;
}
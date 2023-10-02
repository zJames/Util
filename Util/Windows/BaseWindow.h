//------------------------------------------------------------------------------
//  Copyright : (c) 2015
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#pragma once

#include "Rect.h"
#include "WindowsInc.h"
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
//	BaseWindow
//------------------------------------------------------------------------------
class BaseWindow
{
public:
	BaseWindow();
	virtual ~BaseWindow();

	void setTitle(const TCHAR* szTitle);

	HWND hWnd() const;
	HWND hParent() const;
	HINSTANCE hInstance() const;
	Rect clientRect() const;
	Rect windowRect() const;

protected:
	HWND m_hWnd;
	HWND m_hParent;
	HINSTANCE m_hInstance;
};

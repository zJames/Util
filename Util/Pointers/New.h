//------------------------------------------------------------------------------
//  Copyright : (c) 2010
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#pragma once
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
//	New
//------------------------------------------------------------------------------
template<class T>
T* New() { return new T(); }

template<class T, typename... Args>
T* New(Args... args) { return new T(args...); }

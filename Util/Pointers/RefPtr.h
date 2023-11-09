//------------------------------------------------------------------------------
//  Copyright : (c) 2023
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#pragma once

#include "..\Core\ReferenceCounter.h"
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
//	Referenced Pointer
//------------------------------------------------------------------------------
template<class T>
class RefPtr
{
public:
	typedef RefPtr<T> This;

	RefPtr(): mPtr(nullptr) {}
	RefPtr(T* t): mPtr(nullptr) { set(t); }
	
	~RefPtr() { set(nullptr); }

	void set(T* ptr)
	{
		Maybe<int> check = mRefCounter.release();

		if (check != nothing && *check == 0)
		{
			delete mPtr;
		}

		mPtr = ptr;

		if (mPtr != nullptr)
		{
			mRefCounter.create();
		}
	}

	void set(This& other)
	{
		set(nullptr);
		mPtr = other.mPtr;
		mRefCounter = other.mRefCounter;
	}
	
	This& operator =(const This& rhs)	{ set(rhs); return *this; }
	
	operator T* ()						{ return mPtr;}
	operator const T* () const			{ return mPtr;}
	T& operator[] (int idx)				{ return mPtr[idx]; }
	const T& operator[] (int idx) const	{ return mPtr[idx]; }
	T* operator ->()					{ return mPtr; }
	const T* operator ->() const		{ return mPtr; }
	operator bool ()					{ return mPtr != nullptr; }

private:
	T* mPtr;
	ReferenceCounter mRefCounter;
};

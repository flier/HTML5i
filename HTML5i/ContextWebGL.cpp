// ContextWebGL.cpp : Implementation of CContextWebGL

#include "stdafx.h"
#include "ContextWebGL.h"


// CContextWebGL

STDMETHODIMP CContextWebGL::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] = 
	{
		&IID_IContextWebGL
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

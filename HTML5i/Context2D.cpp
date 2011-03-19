// Context2D.cpp : Implementation of CContext2D

#include "stdafx.h"
#include "Context2D.h"


// CContext2D

STDMETHODIMP CContext2D::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] = 
	{
		&IID_IContext2D
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

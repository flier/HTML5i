// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "HTML5i_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CHTML5iModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
#ifdef _MERGE_PROXYSTUB
	if (!PrxDllMain(hInstance, dwReason, lpReserved))
		return FALSE;
#endif
  if (dwReason == DLL_PROCESS_ATTACH)
  {
    ::DisableThreadLibraryCalls(hInstance);
  }
	return _AtlModule.DllMain(dwReason, lpReserved); 
}

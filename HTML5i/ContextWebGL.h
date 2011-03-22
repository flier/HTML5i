// ContextWebGL.h : Declaration of the CContextWebGL

#pragma once
#include "resource.h"       // main symbols

#include "DispExImpl.h"

#include "HTML5i_i.h"
#include "_IContextWebGLEvents_CP.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CContextWebGL

class ATL_NO_VTABLE CContextWebGL :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CContextWebGL, &CLSID_ContextWebGL>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CContextWebGL>,
	public CProxy_IContextWebGLEvents<CContextWebGL>,
	public IDispatchExImpl<CContextWebGL, IContextWebGL, 
                         &IID_IContextWebGL, &LIBID_HTML5iLib, 
                         /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CContextWebGL()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CONTEXTWEBGL)


BEGIN_COM_MAP(CContextWebGL)
	COM_INTERFACE_ENTRY(IContextWebGL)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CContextWebGL)
	CONNECTION_POINT_ENTRY(__uuidof(_IContextWebGLEvents))
END_CONNECTION_POINT_MAP()
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



};

OBJECT_ENTRY_AUTO(__uuidof(ContextWebGL), CContextWebGL)

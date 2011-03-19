// Context2D.h : Declaration of the CContext2D

#pragma once
#include "resource.h"       // main symbols



#include "HTML5i_i.h"
#include "_IContext2DEvents_CP.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CContext2D

class ATL_NO_VTABLE CContext2D :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CContext2D, &CLSID_Context2D>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CContext2D>,
	public CProxy_IContext2DEvents<CContext2D>,
	public IDispatchImpl<IContext2D, &IID_IContext2D, &LIBID_HTML5iLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CContext2D()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CONTEXT2D)


BEGIN_COM_MAP(CContext2D)
	COM_INTERFACE_ENTRY(IContext2D)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CContext2D)
	CONNECTION_POINT_ENTRY(__uuidof(_IContext2DEvents))
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

OBJECT_ENTRY_AUTO(__uuidof(Context2D), CContext2D)

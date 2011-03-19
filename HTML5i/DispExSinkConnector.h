// DispExSinkConnector.h : Declaration of the CDispExSinkConnector

#pragma once
#include "resource.h"       // main symbols



#include "HTML5i_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CDispExSinkConnector

class ATL_NO_VTABLE CDispExSinkConnector :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDispExSinkConnector, &CLSID_DispExSinkConnector>,
	public IDispatchImpl<IDispExSinkConnector, &IID_IDispExSinkConnector, &LIBID_HTML5iLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
  IDispatchEx *m_target;
  bool m_enabled;
public:
	CDispExSinkConnector() : m_target(NULL), m_enabled(true)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DISPEXSINKCONNECTOR)

DECLARE_NOT_AGGREGATABLE(CDispExSinkConnector)

BEGIN_COM_MAP(CDispExSinkConnector)
	COM_INTERFACE_ENTRY(IDispExSinkConnector)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

  ////
  // IDispExSinkConnector
  //
  virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_target( 
    /* [retval][out] */ IDispatchEx **target)
  {
    if (!target) return E_INVALIDARG;

    *target = m_target;

    return S_OK;
  }

  virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_target( 
    /* [in] */ IDispatchEx *target) 
  {
    m_target = target;

    return S_OK;
  }
  virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_enabled( 
    /* [retval][out] */ boolean *enabled) 
  {
    if (!enabled) return E_INVALIDARG;

    *enabled = m_enabled;

    return S_OK;
  }

  virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_enabled( 
    /* [in] */ boolean enabled) 
  {
    m_enabled = enabled;

    return S_OK;
  }

  virtual HRESULT STDMETHODCALLTYPE AddNamedObject( 
    /* [in] */ BSTR bstrName,
    /* [in] */ IDispatch *pDisp) 
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE RemoveNamedObject( 
    /* [in] */ BSTR bstrName)
  {
      return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE AddTypeLib( 
    /* [in] */ REFGUID guidTypeLib,
    /* [defaultvalue][in] */ WORD wMajorVer = 1,
    /* [defaultvalue][in] */ WORD wMinorVer = 0)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE ConnectObject( 
    /* [in] */ IUnknown *pUnk,
    /* [in] */ BSTR bstrPrefix,
    /* [in] */ REFGUID piid,
    /* [in] */ REFGUID plibid,
    /* [defaultvalue][in] */ WORD wMajorVer = 1,
    /* [defaultvalue][in] */ WORD wMinorVer = 0)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE DisconnectObject( 
    /* [in] */ IUnknown *pUnk,
    /* [in] */ REFGUID piid)
  {
    return E_NOTIMPL;
  }
};

OBJECT_ENTRY_AUTO(__uuidof(DispExSinkConnector), CDispExSinkConnector)

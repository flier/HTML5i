// DispExSinkConnector.h : Declaration of the CDispExSinkConnector

#pragma once
#include "resource.h"       // main symbols

#include <memory>

#include "HTML5i_i.h"

// Extending the Internet Explorer Scripting Engine
// http://www.codeproject.com/KB/COM/dispexsinkconnector.aspx

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

class CConnectedObject;
class CDispExSinkConnector;

class CTypeInfoHolder
{
  friend class CConnectedObject;
  friend class CDispExSinkConnector;

  REFGUID m_piid, m_plibid;
  WORD m_wMajorVer, m_wMinorVer;

  CComPtr<ITypeInfo> m_spTypeInfo;
  CSimpleMap<DISPID, CComBSTR> m_mapDispId;

  HRESULT LoadFunctionNames(void);
public:
  CTypeInfoHolder(REFGUID piid, REFGUID plibid, WORD wMajorVer, WORD wMinorVer)
    : m_piid(piid), m_plibid(plibid), m_wMajorVer(wMajorVer), m_wMinorVer(wMinorVer)
  {
    LoadFunctionNames();
  }
};

class CConnectedObject 
  : CComObjectRootEx<CComSingleThreadModel>,
  public IDispatch
{  
  friend class CDispExSinkConnector;

  CDispExSinkConnector *m_connector;
  std::auto_ptr<CTypeInfoHolder> m_holder;
  CComPtr<IUnknown> m_spUnkCP;

  DWORD m_dwCookie;
  CComBSTR m_bstrPrefix;  
public:
  CConnectedObject(CDispExSinkConnector *connector, CTypeInfoHolder *holder, 
    IUnknown *pUnkCP, BSTR bstrPrefix)
    : m_connector(connector), m_holder(holder), m_spUnkCP(pUnkCP), 
    m_bstrPrefix(bstrPrefix), m_dwCookie(0)
  {
    ::AtlAdvise(m_spUnkCP, this, m_holder->m_piid, &m_dwCookie);
  }

  ~CConnectedObject()
  {
    if (m_spUnkCP && m_dwCookie)
    {
      ::AtlUnadvise(m_spUnkCP, m_holder->m_piid, m_dwCookie);

      m_dwCookie = 0;
    }
  }

  ////
  // IUnknown
  //
  STDMETHOD_(ULONG, AddRef)() throw() 
  {
    return InternalAddRef();
  }
  STDMETHOD_(ULONG, Release)() throw()
  {
    ULONG l = InternalRelease();
    if (l == 0)
      delete this;
    return l;
  }

  STDMETHOD(QueryInterface)(
    _In_ REFIID iid, 
    _Deref_out_ void** ppvObject) throw()
  {
    *ppvObject = InlineIsEqualGUID(iid, m_holder->m_piid) ? this : NULL;

    return *ppvObject ? S_OK : E_NOINTERFACE;
  }

  ////
  // IDispatch
  // 
  STDMETHOD(GetTypeInfoCount)( 
    /* [out] */ __RPC__out UINT *pctinfo)
  { 
    return E_NOTIMPL; 
  }

  STDMETHOD(GetTypeInfo)( 
    /* [in] */ UINT iTInfo,
    /* [in] */ LCID lcid,
    /* [out] */ __RPC__deref_out_opt ITypeInfo **ppTInfo)
  { 
    return E_NOTIMPL; 
  }

  STDMETHOD(GetIDsOfNames)( 
    /* [in] */ __RPC__in REFIID riid,
    /* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames,
    /* [range][in] */ __RPC__in_range(0,16384) UINT cNames,
    /* [in] */ LCID lcid,
    /* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId)
  { 
    return E_NOTIMPL; 
  }

  STDMETHOD(Invoke)( 
    /* [in] */ DISPID dispIdMember,
    /* [in] */ REFIID riid,
    /* [in] */ LCID lcid,
    /* [in] */ WORD wFlags,
    /* [out][in] */ DISPPARAMS *pDispParams,
    /* [out] */ VARIANT *pVarResult,
    /* [out] */ EXCEPINFO *pExcepInfo,
    /* [out] */ UINT *puArgErr);
};

class ATL_NO_VTABLE CDispExSinkConnector :
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<CDispExSinkConnector, &CLSID_DispExSinkConnector>,
  public IDispatchImpl<IDispExSinkConnector, &IID_IDispExSinkConnector, &LIBID_HTML5iLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
  IDispatchEx *m_target;
  bool m_enabled;

  CSimpleArray<CConnectedObject*> m_arrObjects;
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
  bool enabled(void) const { return m_enabled; }
  IDispatchEx *target(void) const { return m_target; }

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
    /* [in] */ IDispatch *pDisp);

  virtual HRESULT STDMETHODCALLTYPE RemoveNamedObject( 
    /* [in] */ BSTR bstrName);

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
    /* [defaultvalue][in] */ WORD wMinorVer = 0);

  virtual HRESULT STDMETHODCALLTYPE DisconnectObject( 
    /* [in] */ IUnknown *pUnk,
    /* [in] */ REFGUID piid);
};

OBJECT_ENTRY_AUTO(__uuidof(DispExSinkConnector), CDispExSinkConnector)

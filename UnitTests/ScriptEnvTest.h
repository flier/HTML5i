#pragma once

#include <ActivScp.h>

#include <gtest/gtest.h>

class CScriptEnvTest;

class CScriptHost : public IActiveScriptSite
{
  friend class CScriptEnvTest;

  ULONG m_refCnt;

  SCRIPTSTATE m_state;
  size_t m_depth;
  CComVariant m_result;

  EXCEPINFO m_exc;
  CComBSTR m_excSrcLine;
  DWORD m_excCookie;
  ULONG m_excLineNum;
  LONG m_excCharPos;

  CSimpleMap<CComBSTR, IUnknown *> m_items;
public:
  CScriptHost()
    : m_refCnt(0), m_state(SCRIPTSTATE_UNINITIALIZED), m_depth(0),
      m_excCookie(0), m_excLineNum(-1), m_excCharPos(-1)
  {
    memset(&m_exc, 0, sizeof(m_exc));
  }

  // IUnknown

  virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject) 
  {
    if (InlineIsEqualGUID(riid, __uuidof(IActiveScriptSite)))
    {
      *ppvObject = static_cast<IActiveScriptSite *>(this);

      return S_OK;
    }
    else if (InlineIsEqualGUID(riid, __uuidof(IUnknown)))
    {
      *ppvObject = static_cast<IUnknown *>(this);

      return S_OK;
    }

    return E_NOINTERFACE;
  }

  virtual ULONG STDMETHODCALLTYPE AddRef( void) { return m_refCnt++; }

  virtual ULONG STDMETHODCALLTYPE Release( void) { return --m_refCnt; }

  // IActiveScriptSite

  virtual HRESULT STDMETHODCALLTYPE GetLCID( 
    /* [out] */ __RPC__out LCID *plcid) 
  {
    *plcid = LOCALE_USER_DEFAULT;

    return S_OK;
  }

  virtual HRESULT STDMETHODCALLTYPE GetItemInfo( 
    /* [in] */ __RPC__in LPCOLESTR pstrName,
    /* [in] */ DWORD dwReturnMask,
    /* [out] */ __RPC__deref_out_opt IUnknown **ppiunkItem,
    /* [out] */ __RPC__deref_out_opt ITypeInfo **ppti) 
  {
    if (SCRIPTINFO_IUNKNOWN == (dwReturnMask & SCRIPTINFO_IUNKNOWN))
    {
      if (ppiunkItem)
      {
        *ppiunkItem = m_items.Lookup(CComBSTR(pstrName));

        if (*ppiunkItem) (*ppiunkItem)->AddRef();
      }
      if (ppti) *ppti = NULL;
    }

    return S_OK;
  }

  virtual HRESULT STDMETHODCALLTYPE GetDocVersionString( 
    /* [out] */ __RPC__deref_out_opt BSTR *pbstrVersion) 
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE OnScriptTerminate( 
    /* [in] */ __RPC__in const VARIANT *pvarResult,
    /* [in] */ __RPC__in const EXCEPINFO *pexcepinfo)
  {
    if (pvarResult)
      m_result = *pvarResult;

    if (pexcepinfo)
    {
      if (pexcepinfo->pfnDeferredFillIn)
        pexcepinfo->pfnDeferredFillIn(&m_exc);

      m_exc = *pexcepinfo;
    }

    return S_OK;
  }

  virtual HRESULT STDMETHODCALLTYPE OnStateChange( 
    /* [in] */ SCRIPTSTATE ssScriptState) 
  { 
    m_state = ssScriptState; 
    
    return S_OK; 
  }

  virtual HRESULT STDMETHODCALLTYPE OnScriptError( 
    /* [in] */ __RPC__in_opt IActiveScriptError *pscripterror) 
  { 
    if (pscripterror)
    {
      pscripterror->GetExceptionInfo(&m_exc);
      pscripterror->GetSourceLineText(&m_excSrcLine);
      pscripterror->GetSourcePosition(&m_excCookie, &m_excLineNum, &m_excCharPos);
    }

    return S_OK; 
  }

  virtual HRESULT STDMETHODCALLTYPE OnEnterScript( void) 
  { 
    m_depth++;

    return S_OK; 
  }

  virtual HRESULT STDMETHODCALLTYPE OnLeaveScript( void) 
  { 
    m_depth--;

    return S_OK; 
  }
};

class CScriptEnvTest : public ::testing::Test
{  
  std::auto_ptr<CScriptHost> m_host;
  CComPtr<IActiveScript> m_spEngine;

  typedef HRESULT (STDAPICALLTYPE * DllGetClassObjectFunc)(
    REFCLSID rclsid,
    REFIID riid,
    LPVOID * ppv
    );

  void InitEngine();
  void LoadExtension();
  void LoadClass(DllGetClassObjectFunc fnDllGetClassObject, LPCTSTR name, REFCLSID clsid);
protected:
  CScriptEnvTest(void) : m_host(new CScriptHost())
  {
    EXPECT_HRESULT_SUCCEEDED(::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED));  
  }
  virtual ~CScriptEnvTest(void)
  {
    ::CoUninitialize();
  }

  virtual void SetUp();
  virtual void TearDown();

  HRESULT ExecuteScript(LPCTSTR source, EXCEPINFO *exc=NULL, CComVariant *result=NULL);
};


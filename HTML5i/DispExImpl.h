#pragma once

using namespace ATL;

template <class T, const IID* piid = &__uuidof(T), const GUID* plibid = &CAtlModule::m_libid, 
  WORD wMajor = 1, WORD wMinor = 0, class tihclass = CComTypeInfoHolder>
class ATL_NO_VTABLE IDispatchExImpl 
  : public IDispatchImpl<T, piid, plibid, wMajor, wMinor, tihclass>
{
public:
  virtual HRESULT STDMETHODCALLTYPE GetDispID( 
    /* [in] */ __RPC__in BSTR bstrName,
    /* [in] */ DWORD grfdex,
    /* [out] */ __RPC__out DISPID *pid)
  {
    return E_NOTIMPL;
  }

  virtual /* [local] */ HRESULT STDMETHODCALLTYPE InvokeEx( 
    /* [annotation][in] */ 
    __in  DISPID id,
    /* [annotation][in] */ 
    __in  LCID lcid,
    /* [annotation][in] */ 
    __in  WORD wFlags,
    /* [annotation][in] */ 
    __in  DISPPARAMS *pdp,
    /* [annotation][out] */ 
    __out_opt  VARIANT *pvarRes,
    /* [annotation][out] */ 
    __out_opt  EXCEPINFO *pei,
    /* [annotation][unique][in] */ 
    __in_opt  IServiceProvider *pspCaller)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE DeleteMemberByName( 
    /* [in] */ __RPC__in BSTR bstrName,
    /* [in] */ DWORD grfdex)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE DeleteMemberByDispID( 
    /* [in] */ DISPID id)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE GetMemberProperties( 
    /* [in] */ DISPID id,
    /* [in] */ DWORD grfdexFetch,
    /* [out] */ __RPC__out DWORD *pgrfdex)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE GetMemberName( 
    /* [in] */ DISPID id,
    /* [out] */ __RPC__deref_out_opt BSTR *pbstrName)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE GetNextDispID( 
    /* [in] */ DWORD grfdex,
    /* [in] */ DISPID id,
    /* [out] */ __RPC__out DISPID *pid)
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE GetNameSpaceParent( 
    /* [out] */ __RPC__deref_out_opt IUnknown **ppunk)
  {
    return E_NOTIMPL;
  }
};
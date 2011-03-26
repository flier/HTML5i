#pragma once

#include <vector>

#include "LogHelper.h"

using namespace ATL;

class CClassFactoryConstructor;

class IDispatchExBase
{
protected:
  struct memberdispid : public CComTypeInfoHolder::stringdispid
  {
    DWORD props;
    CComVariant value;

    memberdispid(BSTR bstrName) : props(fdexPropDynamicType)       
    {
      bstr = bstrName;
    }
  };  

  CComTypeInfoHolder& m_tih;
  std::vector<memberdispid> m_members;
public:
  IDispatchExBase(CComTypeInfoHolder& tih) : m_tih(tih)
  {

  }

  CComTypeInfoHolder::stringdispid *findItem(BSTR bstrName, bool insensitive)
  {
    for (int i=0; i<m_tih.m_nCount; i++)
    {
      if (0 == (insensitive ? _wcsicmp : wcscmp)(m_tih.m_pMap[i].bstr, bstrName))
      {
        return &m_tih.m_pMap[i];
      }
    }

    return NULL;
  }

  memberdispid *findMember(BSTR bstrName, bool insensitive)
  {
    for (size_t i=0; i<m_members.size(); i++)
    {
      if (0 == (insensitive ? _wcsicmp : wcscmp)(m_members[i].bstr, bstrName))
      {
        return &m_members[i];
      }
    }

    return NULL;
  }

  CComTypeInfoHolder::stringdispid *findItem(DISPID id)
  {
    for (int i=0; i<m_tih.m_nCount; i++)
    {
      if (id == m_tih.m_pMap[i].id)
      {
        return &m_tih.m_pMap[i];
      }
    }

    return NULL;
  }

  memberdispid *findMember(DISPID id)
  {
    for (size_t i=0; i<m_members.size(); i++)
    {
      if (id == m_members[i].id)
      {
        return &m_members[i];
      }
    }

    return NULL;
  }

  DWORD getItemProp(DISPID id)
  {
    FUNCDESC* pfd = NULL;

    DWORD prop = fdexPropCannotConstruct | fdexPropCannotSourceEvents;

    if (m_tih.m_pInfo && SUCCEEDED(m_tih.m_pInfo->GetFuncDesc(id, &pfd)))
    {
      prop |= (pfd->invkind & INVOKE_FUNC) ? fdexPropCanCall : fdexPropCannotCall;
      prop |= (pfd->invkind & INVOKE_PROPERTYGET) ? fdexPropCanGet : fdexPropCannotGet;
      prop |= (pfd->invkind & INVOKE_PROPERTYPUT) ? fdexPropCanPut : fdexPropCannotPut;
      prop |= (pfd->invkind & INVOKE_PROPERTYPUTREF) ? fdexPropCanPutRef : fdexPropCannotPutRef;

      m_tih.m_pInfo->ReleaseFuncDesc(pfd);
    }

    return prop;
  }

  DISPID getNext(DISPID id)
  {
    bool found = DISPID_STARTENUM == id;

    for (int i=0; i<m_tih.m_nCount; i++)
    {
      if (found) return m_tih.m_pMap[i].id;

      found = id == m_tih.m_pMap[i].id;
    }

    for (size_t i=0; i<m_members.size(); i++)
    {
      if (found) return m_members[i].id;

      found = id == m_members[i].id;
    }

    return DISPID_UNKNOWN;
  }

  DISPID findNextId()
  {
    DISPID id = m_members.empty() ? 0 : m_members.rbegin()->id+1;

    for (; !findItem(id) && !findMember(id); id++)
    {
    }

    return id;
  }

  DISPID createMember(BSTR bstrName)
  {
    memberdispid member(bstrName);

    member.id = findNextId();

    m_members.push_back(member);

    return member.id;
  }
};

template <class C, class T, const IID* piid = &__uuidof(T), const GUID* plibid = &CAtlModule::m_libid, 
  WORD wMajor = 1, WORD wMinor = 0, class tihclass = CComTypeInfoHolder>
class ATL_NO_VTABLE IDispatchExImpl 
  : public IDispatchImpl<T, piid, plibid, wMajor, wMinor, tihclass>,
    public IDispatchExBase
{    
public:
  IDispatchExImpl() : IDispatchExBase(_tih)
  {

  }

  static CClassFactoryConstructor *CreateConstructor(CComBSTR name)
  {
    CComPtr<IClassFactory> spFactory;

    C::_ClassFactoryCreatorClass::CreateInstance(NULL, __uuidof(IClassFactory), (LPVOID *) &spFactory);

    CComObject<CClassFactoryConstructor> *ctor = new CComObject<CClassFactoryConstructor>();

    ctor->Attach(name, spFactory.Detach());

    return ctor;
  }

  virtual HRESULT STDMETHODCALLTYPE DeleteMemberByName( 
    /* [in] */ __RPC__in BSTR bstrName,
    /* [in] */ DWORD grfdex)
  {
    bool caseSensitive = fdexNameCaseInsensitive == (grfdex & fdexNameCaseInsensitive);

    tihclass::stringdispid *item = findItem(bstrName, caseSensitive);

    if (item) return S_FALSE;

    memberdispid *member = findMember(bstrName, caseSensitive);

    if (member)
    {
      member->props = 0;
      member->value.Clear();

      return S_OK;
    }
    
    return DISP_E_UNKNOWNNAME;
  }

  virtual HRESULT STDMETHODCALLTYPE DeleteMemberByDispID( 
    /* [in] */ DISPID id)
  {    
    tihclass::stringdispid *item = findItem(id);

    if (item) return S_FALSE;

    memberdispid *member = findMember(id);

    if (member)
    {
      member->props = 0;
      member->value.Clear();

      return S_OK;
    }

    return DISP_E_UNKNOWNNAME;
  }

  virtual HRESULT STDMETHODCALLTYPE GetMemberProperties( 
    /* [in] */ DISPID id,
    /* [in] */ DWORD grfdexFetch,
    /* [out] */ __RPC__out DWORD *pgrfdex)
  {
    if (!pgrfdex) return E_INVALIDARG;

    tihclass::stringdispid *item = findItem(id);

    if (item)
    {
      *pgrfdex = grfdexFetch & getItemProp(item->id);

      return S_OK;
    }
    
    memberdispid *member = findMember(id);

    if (member && member->props)
    {
      *pgrfdex = grfdexFetch & member->props;

      return S_OK;
    }

    return DISP_E_UNKNOWNNAME;
  }

  virtual HRESULT STDMETHODCALLTYPE GetMemberName( 
    /* [in] */ DISPID id,
    /* [out] */ __RPC__deref_out_opt BSTR *pbstrName)
  {
    if (!pbstrName) return E_INVALIDARG;

    tihclass::stringdispid *item = findItem(id);

    if (!item) item = findMember(id);

    if (item)
    {
      *pbstrName = ::SysAllocStringLen(item->bstr, item->nLen);

      return S_OK;
    }

    *pbstrName = NULL;

    return DISP_E_UNKNOWNNAME;
  }

  virtual HRESULT STDMETHODCALLTYPE GetNextDispID( 
    /* [in] */ DWORD grfdex,
    /* [in] */ DISPID id,
    /* [out] */ __RPC__out DISPID *pid)
  {
    if (!pid) return E_INVALIDARG;

    *pid = getNext(id);
  
    return DISPID_UNKNOWN == *pid ? S_FALSE : S_OK;
  }

  virtual HRESULT STDMETHODCALLTYPE GetDispID( 
    /* [in] */ __RPC__in BSTR bstrName,
    /* [in] */ DWORD grfdex,
    /* [out] */ __RPC__out DISPID *pid)
  {
    if (!pid) return E_INVALIDARG;

    tihclass::stringdispid *item = findItem(bstrName, grfdex & fdexNameCaseInsensitive);

    if (!item) item = findMember(bstrName, grfdex & fdexNameCaseInsensitive);

    if (item)
    {
      *pid = item->id;

      return S_OK;
    }

    if (fdexNameEnsure == (grfdex & fdexNameEnsure))
    {     
      *pid = createMember(bstrName);

      return S_OK;
    }

    *pid = DISPID_UNKNOWN;

    return DISP_E_UNKNOWNNAME;
  }

  virtual HRESULT STDMETHODCALLTYPE GetNameSpaceParent( 
    /* [out] */ __RPC__deref_out_opt IUnknown **ppunk)
  {
    return E_NOTIMPL;
  }

  virtual /* [local] */ HRESULT STDMETHODCALLTYPE InvokeEx( 
    /* [annotation][in] */ 
    __in  DISPID dispidMember,
    /* [annotation][in] */ 
    __in  LCID lcid,
    /* [annotation][in] */ 
    __in  WORD wFlags,
    /* [annotation][in] */ 
    __in  DISPPARAMS *pdispparams,
    /* [annotation][out] */ 
    __out_opt  VARIANT *pvarResult,
    /* [annotation][out] */ 
    __out_opt  EXCEPINFO *pexcepinfo,
    /* [annotation][unique][in] */ 
    __in_opt  IServiceProvider *pspCaller)
  {
    UINT uArgErr;

    if (findItem(dispidMember))
    {
      HRESULT hRes = _tih.EnsureTI(LOCALE_USER_DEFAULT);

      if (_tih.m_pInfo)
      {
        hRes = _tih.m_pInfo->Invoke((IDispatch *) this, dispidMember, wFlags, 
          pdispparams, pvarResult, pexcepinfo, &uArgErr);
      }

      return hRes;
    }

    memberdispid *member = findMember(dispidMember);

    if (member)
    {
      bool propget = (wFlags & DISPATCH_PROPERTYGET) && (member->props & fdexPropCanGet);
      bool propput = (wFlags & DISPATCH_PROPERTYPUT) && (member->props & fdexPropCanPut);
      bool cancall = (wFlags & DISPATCH_METHOD) && (member->props & fdexPropCanCall);

      if (propget)
      {
        if (cancall && (VT_DISPATCH == member->value.vt))
        {
          return member->value.pdispVal->Invoke(dispidMember, IID_NULL, 
            lcid, wFlags, pdispparams, pvarResult, pexcepinfo, &uArgErr);
        }

        *pvarResult = member->value;

        return S_OK;
      }
      
      if (propput)
      {
        if (cancall && (VT_DISPATCH == member->value.vt))
        {
          return member->value.pdispVal->Invoke(dispidMember, IID_NULL, 
            lcid, wFlags, pdispparams, pvarResult, pexcepinfo, &uArgErr);
        }

        if (pdispparams->cArgs != 1)
          return DISP_E_BADPARAMCOUNT;
        
        member->value = pdispparams->rgvarg[0];
        
        return S_OK;
      }

      if (cancall)
      {
        HRESULT hr = DISP_E_TYPEMISMATCH;

        if (VT_UNKNOWN == member->value.vt)
        {
          CComQIPtr<IClassFactory> spFactory = *member->value.ppunkVal;

          if (spFactory)
          {
            CComPtr<IUnknown> spUnk;

            hr = spFactory->CreateInstance(NULL, __uuidof(IUnknown), (LPVOID *) &spUnk);

            if (SUCCEEDED(hr) && spUnk)
            {
              *pvarResult = CComVariant(spUnk.Detach());

              hr = S_OK;
            }
          }
        }
        else if (VT_DISPATCH == member->value.vt)
        {
          hr = member->value.pdispVal->Invoke(dispidMember, IID_NULL, 
            lcid, wFlags, pdispparams, pvarResult, pexcepinfo, &uArgErr);
        }

        return hr;
      }
    }

    return DISP_E_MEMBERNOTFOUND;
  }

};


class CScriptConstructor
  : public CComObjectRoot,
    public IDispatchEx
{  
public:

  BEGIN_COM_MAP(CScriptConstructor)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(IDispatchEx)
  END_COM_MAP()

  DECLARE_PROTECT_FINAL_CONSTRUCT()

  // IDispatch

  virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount( 
    /* [out] */ __RPC__out UINT *pctinfo)
  {
    *pctinfo = 0;
    return S_OK;
  }

  virtual HRESULT STDMETHODCALLTYPE GetTypeInfo( 
    /* [in] */ UINT iTInfo,
    /* [in] */ LCID lcid,
    /* [out] */ __RPC__deref_out_opt ITypeInfo **ppTInfo) 
  {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames( 
    /* [in] */ __RPC__in REFIID riid,
    /* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames,
    /* [range][in] */ __RPC__in_range(0,16384) UINT cNames,
    /* [in] */ LCID lcid,
    /* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId) 
  {
    return E_NOTIMPL;
  }

  virtual /* [local] */ HRESULT STDMETHODCALLTYPE Invoke( 
    /* [in] */ DISPID dispIdMember,
    /* [in] */ REFIID riid,
    /* [in] */ LCID lcid,
    /* [in] */ WORD wFlags,
    /* [out][in] */ DISPPARAMS *pDispParams,
    /* [out] */ VARIANT *pVarResult,
    /* [out] */ EXCEPINFO *pExcepInfo,
    /* [out] */ UINT *puArgErr) 
  {
    return E_NOTIMPL;
  }

  // IDispatchEx

  virtual HRESULT STDMETHODCALLTYPE GetDispID( 
    /* [in] */ __RPC__in BSTR bstrName,
    /* [in] */ DWORD grfdex,
    /* [out] */ __RPC__out DISPID *pid)
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

class CClassFactoryConstructor : public CScriptConstructor
{
  CComBSTR m_name;
  CComPtr<IClassFactory> m_spFactory;
public:
  void Attach(CComBSTR name, IClassFactory *pFactory) { m_name = name; m_spFactory = pFactory; }

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
    LOG_INFO(_T("call %s constructor"), m_name);

    if ((id != DISPID_VALUE) || !(wFlags & DISPATCH_CONSTRUCT))
      return DISP_E_MEMBERNOTFOUND;

    if (!pdp || !pvarRes) return E_INVALIDARG;

    if (pdp->cArgs) return DISP_E_BADPARAMCOUNT;
    if (pdp->cNamedArgs) return DISP_E_NONAMEDARGS;

    CComPtr<IDispatch> spDisp;

    HRESULT hr = m_spFactory->CreateInstance(NULL, __uuidof(IDispatch), (LPVOID *) &spDisp);
      
    if (SUCCEEDED(hr))
    {
      pvarRes->vt = VT_DISPATCH;
      pvarRes->pdispVal = spDisp.Detach();
    }

    return hr;
  }
};

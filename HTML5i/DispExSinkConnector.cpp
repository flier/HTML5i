// DispExSinkConnector.cpp : Implementation of CDispExSinkConnector

#include "stdafx.h"
#include "DispExSinkConnector.h"

// CTypeInfoHolder

HRESULT CTypeInfoHolder::LoadFunctionNames(void)
{
  ATLASSERT(!m_spTypeInfo);

  CComPtr<ITypeLib> spTypeLib;

  HRESULT hr = ::LoadRegTypeLib(m_plibid, m_wMajorVer, m_wMinorVer, LOCALE_USER_DEFAULT, &spTypeLib);

  if (SUCCEEDED(hr) && spTypeLib)
  {
    hr = spTypeLib->GetTypeInfoOfGuid(m_piid, &m_spTypeInfo);

    if (SUCCEEDED(hr) && m_spTypeInfo)
    {
      TYPEATTR *pta = NULL;

      hr = m_spTypeInfo->GetTypeAttr(&pta);

      if (SUCCEEDED(hr) && pta)
      {
        for (WORD i=0; i<pta->cFuncs; i++)
        {
          FUNCDESC *pfd = NULL;

          hr = m_spTypeInfo->GetFuncDesc(i, &pfd);

          if (SUCCEEDED(hr) && pfd)
          {
            CComBSTR bstrName;
            unsigned int uiNames = 0;

            hr = m_spTypeInfo->GetNames(pfd->memid, &bstrName, 1, &uiNames);

            if (SUCCEEDED(hr) && bstrName && bstrName.Length() && uiNames)
            {
              m_mapDispId.Add(pfd->memid, bstrName);
            }

            m_spTypeInfo->ReleaseFuncDesc(pfd);
          }
        }

        m_spTypeInfo->ReleaseTypeAttr(pta);
      }
    }
  }

  return hr;
}

// CConnectedObject

HRESULT CConnectedObject::Invoke( 
  /* [in] */ DISPID dispIdMember,
  /* [in] */ REFIID riid,
  /* [in] */ LCID lcid,
  /* [in] */ WORD wFlags,
  /* [out][in] */ DISPPARAMS *pDispParams,
  /* [out] */ VARIANT *pVarResult,
  /* [out] */ EXCEPINFO *pExcepInfo,
  /* [out] */ UINT *puArgErr)
{
  if (!m_connector) return E_FAIL;

  if (!m_connector->enabled()) return S_OK;
  if (!m_connector->target()) return S_OK;

  CComBSTR bstrMember = m_holder->m_mapDispId.Lookup(dispIdMember);

  if (bstrMember && bstrMember.Length())
  {
    CComBSTR bstrFunction = m_bstrPrefix;

    bstrFunction += bstrMember;

    DISPID dispIdEx;

    HRESULT hr = m_connector->target()->GetDispID(bstrFunction, fdexNameCaseSensitive, &dispIdEx);

    if (SUCCEEDED(hr))
    {
      return m_connector->target()->InvokeEx(dispIdEx, lcid, 
        DISPATCH_METHOD, pDispParams, pVarResult, pExcepInfo, NULL);
    }
  }

  return S_OK;
}

// CDispExSinkConnector

HRESULT CDispExSinkConnector::AddNamedObject( 
  /* [in] */ BSTR bstrName,
  /* [in] */ IDispatch *pDisp) 
{
  if (!m_target) return E_FAIL;

  if (!bstrName || ::SysStringLen(bstrName) == 0 || !pDisp)
    return E_INVALIDARG;

  DISPID dispIdThis = 0;

  HRESULT hr = m_target->GetDispID(bstrName, 
    fdexNameEnsure | fdexNameCaseSensitive, &dispIdThis);

  if (SUCCEEDED(hr) && dispIdThis)
  {
    DISPID dispIdPut = DISPID_PROPERTYPUT;
    DISPPARAMS params;
    CComVariant arg = pDisp;
    EXCEPINFO exc;

    memset(&params, 0, sizeof(params));
    params.cArgs = params.cNamedArgs = 1;
    params.rgvarg = &arg;
    params.rgdispidNamedArgs = &dispIdPut;

    pDisp->AddRef();

    hr = m_target->InvokeEx(dispIdThis, LOCALE_USER_DEFAULT, 
      DISPATCH_PROPERTYPUT, &params, NULL, &exc, NULL);
  }

  return hr;
}

HRESULT CDispExSinkConnector::RemoveNamedObject( 
  /* [in] */ BSTR bstrName)
{
  if (!m_target) return E_FAIL;

  if (!bstrName || ::SysStringLen(bstrName) == 0)
    return E_INVALIDARG;

  return m_target->DeleteMemberByName(bstrName, fdexNameCaseSensitive);
}

HRESULT CDispExSinkConnector::ConnectObject( 
  /* [in] */ IUnknown *pUnk,
  /* [in] */ BSTR bstrPrefix,
  /* [in] */ REFGUID piid,
  /* [in] */ REFGUID plibid,
  /* [defaultvalue][in] */ WORD wMajorVer,
  /* [defaultvalue][in] */ WORD wMinorVer)
{
  if (!m_target) return E_FAIL;

  if (!bstrPrefix || ::SysStringLen(bstrPrefix) == 0)
    return E_INVALIDARG;

  std::auto_ptr<CTypeInfoHolder> holder(new CTypeInfoHolder(piid, plibid, wMajorVer, wMinorVer));
  std::auto_ptr<CConnectedObject> obj(new CConnectedObject(this, holder.get(), pUnk, bstrPrefix));

  if (m_arrObjects.Add(obj.get()))
  {
    holder.release();
    obj.release();
  }  

  return S_OK;
}

HRESULT CDispExSinkConnector::DisconnectObject( 
  /* [in] */ IUnknown *pUnk,
  /* [in] */ REFGUID piid)
{
  if (!m_target) return E_FAIL;

  for(int i = 0; i < m_arrObjects.GetSize(); i++)
  {
    CConnectedObject *pObj = m_arrObjects[i];

    if(pUnk == pObj->m_spUnkCP &&
       pObj->m_holder.get() && 
       InlineIsEqualGUID(piid, pObj->m_holder->m_piid))
    {
      if (m_arrObjects.RemoveAt(i))     
        delete pObj;      

      return S_OK;
    }
  }

  return E_INVALIDARG;
}
// DispExSinkConnector.cpp : Implementation of CDispExSinkConnector

#include "stdafx.h"
#include "DispExSinkConnector.h"


// CDispExSinkConnector

HRESULT CDispExSinkConnector::AddNamedObject( 
  /* [in] */ BSTR bstrName,
  /* [in] */ IDispatch *pDisp) 
{
  if (!m_target)
    return E_FAIL;

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

  return E_NOTIMPL;
}

HRESULT CDispExSinkConnector::RemoveNamedObject( 
  /* [in] */ BSTR bstrName)
{
  if (!m_target)
    return E_FAIL;

  if (!bstrName || ::SysStringLen(bstrName) == 0)
    return E_INVALIDARG;

  return m_target->DeleteMemberByName(bstrName, fdexNameCaseSensitive);
}

// Html5Ext.cpp : Implementation of CHtml5Ext

#include "stdafx.h"
#include "Html5Ext.h"

#include <ActivScp.h>

#include "LogHelper.h"
#include "DispExSinkConnector.h"
#include "Context2D.h"
#include "ContextWebGL.h"

// CHtml5Ext

HRESULT CHtml5Ext::SetSite(_In_opt_ IUnknown *pUnkSite)
{
  HRESULT hr = IObjectWithSiteImpl<CHtml5Ext>::SetSite(pUnkSite);

  LOG_DEBUG(_T("SetSite(site=0x%p)"), pUnkSite);

  if (pUnkSite)
  {
    m_spWebBrowser2 = pUnkSite;

    if (m_spWebBrowser2)
    {
      LOG_INFO(_T("sinking events from IWebBrowser2 (0x%p)"), m_spWebBrowser2);

      hr = WebBrowserEvents::DispEventAdvise(m_spWebBrowser2);

      if (FAILED(hr))
        LOG_ERROR(_T("fail to sinking events from IWebBrowser2 (0x%p)"), m_spWebBrowser2);
    }
    else
    {
      LOG_ERROR(_T("fail to QI for IWebBrowser2, %s"), pUnkSite);
    }
  }
  else
  {
    hr = WebBrowserEvents::DispEventUnadvise(m_spWebBrowser2);

    if (FAILED(hr))
      LOG_ERROR(_T("fail to unsinking events from IWebBrowser2 (0x%p), err=%08x"), m_spWebBrowser2, hr);

    m_spWebBrowser2.Release();
  }

  return hr;
}

void CHtml5Ext::OnDocumentComplete(LPDISPATCH pDisp, VARIANT* URL)
{
  CComQIPtr<IWebBrowser2> spWebBrowser2 = pDisp;  

  if (spWebBrowser2 && m_spWebBrowser2 &&
      m_spWebBrowser2.IsEqualObject(spWebBrowser2))
  {
    CComPtr<IDispatch> spDisp;

    if (SUCCEEDED(m_spWebBrowser2->get_Document(&spDisp)))
    {
      CComQIPtr<IHTMLDocument> spDoc = spDisp;

      ProcessDocument(spDoc);
    }
  }
}

void CHtml5Ext::ProcessDocument(IHTMLDocument *pDoc)
{
  CComQIPtr<IHTMLDocument3> spDoc = pDoc;
  CComPtr<IHTMLElementCollection> spElements;

  if (spDoc && SUCCEEDED(spDoc->getElementsByTagName(CComBSTR(_T("canvas")), &spElements)))
  {
    long len = 0;

    if (SUCCEEDED(spElements->get_length(&len)) && len > 0)
    {
      LOG_INFO(_T("found %d canvas tags"), len);

      InstallHtml5Ext(pDoc);
    }    
  }
}

void CHtml5Ext::LoadJavascript(UINT id, std::wstring& source)
{
  HRSRC hRes = ::FindResource(_AtlBaseModule.GetResourceInstance(), MAKEINTRESOURCEW(id), _T("JAVASCRIPT"));

  if (hRes)
  {
    HGLOBAL hData = ::LoadResource(_AtlBaseModule.GetResourceInstance(), hRes);

    if (hData)
    {
      size_t len = ::SizeofResource(_AtlBaseModule.GetResourceInstance(), hRes);
      const wchar_t *str = (const wchar_t *) ::LockResource(hData);

      if (str && len)
      {
        source = std::wstring(str, len);
      }

      ::FreeResource(hData);
    }
  }  
}

HRESULT CHtml5Ext::ExecJavascript(IHTMLDocument *pDoc, const std::wstring& source)
{
  CComPtr<IDispatch> spDisp;  

  HRESULT hr = pDoc->get_Script(&spDisp);
  
  if (SUCCEEDED(hr) && spDisp)
  {
    CComPtr<IDispExSinkConnector> spConnector;

    hr = CComCoClass<CDispExSinkConnector>::CreateInstance(&spConnector);

    ATLASSERT(SUCCEEDED(hr));

    CComQIPtr<IDispatchEx> spDispEx = spDisp;

    hr = spConnector->put_target(spDispEx);

    ATLASSERT(SUCCEEDED(hr));    

    hr = spConnector->AddNamedObject(CComBSTR("Context2D"), CContext2D::CreateConstructor("Context2D"));

    ATLASSERT(SUCCEEDED(hr));

    hr = spConnector->ConnectObject(m_spWebBrowser2, 
      CComBSTR(_T("Canvas_")), __uuidof(_IContext2DEvents), LIBID_HTML5iLib);

    ATLASSERT(SUCCEEDED(hr));

    hr = spConnector->AddNamedObject(CComBSTR("ContextWebGL"), CContextWebGL::CreateConstructor("ContextWebGL"));

    ATLASSERT(SUCCEEDED(hr));

    hr = spConnector->ConnectObject(m_spWebBrowser2, 
      CComBSTR(_T("WebGL_")), __uuidof(_IContextWebGLEvents), LIBID_HTML5iLib);

    ATLASSERT(SUCCEEDED(hr));

    /*
    DISPID dispid;
    CComBSTR bstrName;

    hr = spDispEx->GetNextDispID(fdexEnumAll, DISPID_STARTENUM, &dispid);

    while (hr == S_OK)
    {
      hr = spDispEx->GetMemberName(dispid, &bstrName);
      
      ATLASSERT(SUCCEEDED(hr));

      DWORD dwProps = 0;

      hr = spDispEx->GetMemberProperties(dispid, grfdexPropAll, &dwProps);

      if (SUCCEEDED(hr))
      {
        LOG_DEBUG(_T("#%d %s=%x %s %s %s %s %s"), dispid, bstrName, dwProps,
          ((dwProps & fdexPropCanCall) ? _T("method") : _T("")),
          ((dwProps & fdexPropCanGet) ? _T("readable") : _T("")),
          ((dwProps & fdexPropCanPut) ? _T("writable") : _T("")),
          ((dwProps & fdexPropCanConstruct) ? _T("ctor") : _T("")),
          ((dwProps & fdexPropCanSourceEvents) ? _T("event") : _T("")));
      }
      else
      {
        LOG_WARN(_T("fail to get member %s, #%d, hr=%x"), bstrName, dispid, hr);
      }

      hr = spDispEx->GetNextDispID(fdexEnumAll, dispid, &dispid);
    }
    */

    CComQIPtr<IHTMLDocument2> spDoc = pDoc;
    CComPtr<IHTMLWindow2> spWin;

    if (SUCCEEDED(spDoc->get_parentWindow(&spWin)) && spWin)
    {
      CComBSTR src(source.c_str()), lang(_T("JavaScript"));
      CComVariant ret;

      hr = spWin->execScript(CComBSTR(_T("eval('alert(\"test\")');")), lang, &ret);

      LOG_INFO(_T("execute script: %x"), hr);
    }
  }

  return hr;
}

void CHtml5Ext::InstallHtml5Ext(IHTMLDocument *pDoc)
{
  std::wstring source;
  
  LoadJavascript(IDR_HTML5I_JS, source);  
  ExecJavascript(pDoc, source);
}
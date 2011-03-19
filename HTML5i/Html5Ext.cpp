// Html5Ext.cpp : Implementation of CHtml5Ext

#include "stdafx.h"
#include "Html5Ext.h"

#include <ActivScp.h>

#include "DispExSinkConnector.h"

#define TRACE_LEVEL_FATAL 0
#define TRACE_LEVEL_ERROR 1
#define TRACE_LEVEL_WARN 2
#define TRACE_LEVEL_INFO 3
#define TRACE_LEVEL_DEBUG 4

// CHtml5Ext

HRESULT CHtml5Ext::SetSite(_In_opt_ IUnknown *pUnkSite)
{
  HRESULT hr = IObjectWithSiteImpl<CHtml5Ext>::SetSite(pUnkSite);

  if (pUnkSite)
  {
    m_spWebBrowser2 = pUnkSite;

    if (m_spWebBrowser2)
    {
      ATLTRACE2(atlTraceGeneral, TRACE_LEVEL_INFO, _T("sinking events from IWebBrowser2, %x"), m_spWebBrowser2);

      hr = ConnectBrowserEvents(true);

      if (FAILED(hr))
        ATLTRACE2(atlTraceCOM, TRACE_LEVEL_FATAL, _T("fail to sinking events from IWebBrowser2, %x"), m_spWebBrowser2);
    }
    else
    {
      ATLTRACE2(atlTraceQI, TRACE_LEVEL_FATAL, _T("fail to QI for IWebBrowser2, %s"), pUnkSite);
    }
  }

  return hr;
}

HRESULT CHtml5Ext::ConnectBrowserEvents(bool advise)
{
  ATLASSERT(m_spWebBrowser2);

  if (!m_spWebBrowser2) return S_OK;

  HRESULT hr = advise ? 
    WebBrowserEvents::DispEventAdvise(m_spWebBrowser2) :
    WebBrowserEvents::DispEventUnadvise(m_spWebBrowser2);
    
  return hr;
}

void CHtml5Ext::OnDocumentComplete(LPDISPATCH pDisp, VARIANT* URL)
{
  CComQIPtr<IWebBrowser2> spWebBrowser2 = pDisp;  

  if (spWebBrowser2)
  {
    CComPtr<IDispatch> spDisp;

    if (SUCCEEDED(spWebBrowser2->get_Document(&spDisp)))
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
      ATLTRACE2(atlTraceCOM, TRACE_LEVEL_INFO, _T("found %d canvas tags"), len);

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
  
  if (SUCCEEDED(hr))
  {
    CComPtr<IDispExSinkConnector> spConnector;

    hr = CComCoClass<CDispExSinkConnector>::CreateInstance(&spConnector);

    ATLASSERT(SUCCEEDED(hr));

    CComQIPtr<IDispatchEx> spDispEx = spDisp;

    hr = spConnector->put_target(spDispEx);

    ATLASSERT(SUCCEEDED(hr));

    CComQIPtr<IHTMLWindow2> spWin = spDisp;

    CComBSTR src(source.c_str()), lang(_T("javascript"));
    CComVariant ret;

    hr = spWin->execScript(src, lang, &ret);

    if (SUCCEEDED(hr))
    {

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
// Html5Ext.cpp : Implementation of CHtml5Ext

#include "stdafx.h"
#include "Html5Ext.h"

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
      CComQIPtr<IHTMLDocument3> spDoc = spDisp;

      ProcessDocument(spDoc);
    }
  }
}

void CHtml5Ext::ProcessDocument(IHTMLDocument3 *pDoc)
{
  CComPtr<IHTMLElementCollection> spElements;

  if (SUCCEEDED(pDoc->getElementsByTagName(CComBSTR(_T("canvas")), &spElements)))
  {
    long len = 0;

    if (SUCCEEDED(spElements->get_length(&len)))
    {
      ATLTRACE2(atlTraceCOM, TRACE_LEVEL_INFO, _T("found %d canvas tags"), len);

      for (long i=0; i<len; i++)
      {
        CComVariant index = i, width, height;
        CComPtr<IDispatch> spDisp;

        if (SUCCEEDED(spElements->item(index, index, &spDisp)))
        {
          HackCanvas(spDisp);
        }
      }
    }    
  }
}

void CHtml5Ext::HackCanvas(IDispatch *pDisp)
{

}
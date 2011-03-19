// Html5Ext.h : Declaration of the CHtml5Ext

#pragma once
#include "resource.h"       // main symbols

#include <ExDisp.h>
#include <ExDispid.h>

#include "HTML5i_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

// CHtml5Ext

class ATL_NO_VTABLE CHtml5Ext :
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<CHtml5Ext, &CLSID_Html5Ext>,
  public IObjectWithSiteImpl<CHtml5Ext>,
  public IDispatchImpl<IHtml5Ext, &IID_IHtml5Ext, &LIBID_HTML5iLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
  public IDispEventImpl<1, CHtml5Ext, &DIID_DWebBrowserEvents2, &LIBID_SHDocVw, 1, 1>
{
  typedef IDispEventImpl<1, CHtml5Ext, &DIID_DWebBrowserEvents2, &LIBID_SHDocVw, 1, 1> WebBrowserEvents;

  CComQIPtr<IWebBrowser2> m_spWebBrowser2;

  HRESULT ConnectBrowserEvents(bool advise);
  void ProcessDocument(IHTMLDocument3 *pDoc);
  void HackCanvas(IDispatch *pDisp);
public:
  CHtml5Ext() 
  {
  }

  DECLARE_REGISTRY_RESOURCEID(IDR_HTML5EXT)

  DECLARE_NOT_AGGREGATABLE(CHtml5Ext)

  BEGIN_COM_MAP(CHtml5Ext)
    COM_INTERFACE_ENTRY(IHtml5Ext)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(IObjectWithSite)
  END_COM_MAP()

  BEGIN_SINK_MAP(CHtml5Ext)
    SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, OnDocumentComplete)
  END_SINK_MAP()

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
  // IObjectWithSite
  //
  STDMETHOD(SetSite)(_In_opt_ IUnknown *pUnkSite);

  ////
  // DWebBrowserEvents2
  //
  void STDMETHODCALLTYPE OnDocumentComplete(LPDISPATCH pDisp, VARIANT* URL);
};

OBJECT_ENTRY_AUTO(__uuidof(Html5Ext), CHtml5Ext)

#include "StdAfx.h"
#include "ScriptEnvTest.h"

#include "HTML5i_i.h"
#include "DispExImpl.h"

#define SCRIPT_E_REPORTED 0x80020101 // http://support.microsoft.com/kb/247784

#define DEFINE_CLSID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
  const CLSID name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

DEFINE_CLSID(CLSID_Context2D,0xA2B02C23,0x5C77,0x44B3,0xB6,0xFE,0x12,0xBC,0x43,0xAA,0x13,0xD2);
DEFINE_CLSID(CLSID_ContextWebGL,0x801ADD56,0x023A,0x41CD,0x95,0x55,0xD6,0x15,0x6A,0x23,0xD1,0xCB);

void CScriptEnvTest::SetUp()
{
  InitEngine();
  LoadExtension();
}

void CScriptEnvTest::InitEngine()
{
  CLSID clsidJavascript;

  ASSERT_HRESULT_SUCCEEDED(::CLSIDFromProgID(_T("JavaScript"), &clsidJavascript));

  ASSERT_HRESULT_SUCCEEDED(m_spEngine.CoCreateInstance(clsidJavascript));
  
  ASSERT_HRESULT_SUCCEEDED(m_spEngine->SetScriptSite(m_host.get()));  

  CComQIPtr<IActiveScriptParse> parser = m_spEngine;

  ASSERT_HRESULT_SUCCEEDED(parser->InitNew());

  ASSERT_EQ(SCRIPTSTATE_INITIALIZED, m_host->m_state);
}

void CScriptEnvTest::LoadExtension()
{
  HMODULE hDll = ::LoadLibrary(_T("HTML5i.dll"));

  ASSERT_TRUE(NULL != hDll);

  DllGetClassObjectFunc fnDllGetClassObject = (DllGetClassObjectFunc) ::GetProcAddress(hDll, "DllGetClassObject");

  CComPtr<ITypeLib> spTypeLib;

  ASSERT_HRESULT_SUCCEEDED(::LoadTypeLib(_T("HTML5i.dll"), &spTypeLib));  

  ASSERT_TRUE(NULL != fnDllGetClassObject);

  LoadClass(fnDllGetClassObject, _T("Context2D"), CLSID_Context2D);
  LoadClass(fnDllGetClassObject, _T("ContextWebGL"), CLSID_ContextWebGL);
}

void CScriptEnvTest::LoadClass(CScriptEnvTest::DllGetClassObjectFunc fnDllGetClassObject, LPCTSTR name, REFCLSID clsid)
{
  CComPtr<IClassFactory> spFactory;

  ASSERT_HRESULT_SUCCEEDED(fnDllGetClassObject(clsid, __uuidof(IClassFactory), (LPVOID *) &spFactory));

  CComObjectNoLock<CClassFactoryConstructor> *ctor = new CComObjectNoLock<CClassFactoryConstructor>();

  ctor->Attach(CComBSTR(name), spFactory.Detach());

  m_host->m_items.Add(CComBSTR(name), ctor);

  ASSERT_HRESULT_SUCCEEDED(m_spEngine->AddNamedItem(name, 
    SCRIPTITEM_GLOBALMEMBERS | SCRIPTITEM_ISVISIBLE));  
}

void CScriptEnvTest::TearDown()
{
  m_spEngine.Release();
}

HRESULT CScriptEnvTest::ExecuteScript(LPCTSTR source, EXCEPINFO *exc, CComVariant *result)
{
  CComQIPtr<IActiveScriptParse> parser = m_spEngine;
  
  DWORD dwFlags = SCRIPTTEXT_ISVISIBLE;

  if (result) dwFlags |= SCRIPTTEXT_ISEXPRESSION;
  
  HRESULT hr = parser->ParseScriptText(source, NULL, NULL, NULL, 0, 0, dwFlags, result, exc);

  if (SUCCEEDED(hr))
  {
    EXPECT_HRESULT_SUCCEEDED(m_spEngine->SetScriptState(SCRIPTSTATE_STARTED));

    EXPECT_EQ(SCRIPTSTATE_STARTED, m_host->m_state);
  }

  return hr;
}

TEST_F(CScriptEnvTest, ExecuteScript)
{
  EXCEPINFO exc;
  CComVariant result;

  ASSERT_HRESULT_SUCCEEDED(ExecuteScript(_T("1+2"), &exc, &result));

  ASSERT_EQ(VT_I4, result.vt);
  ASSERT_EQ(3, result.intVal);

  ASSERT_EQ(SCRIPT_E_REPORTED, ExecuteScript(_T("nonexist"), &exc, &result));   
}

TEST_F(CScriptEnvTest, Constructor)
{
  ASSERT_HRESULT_SUCCEEDED(ExecuteScript(_T("var canvas = new Context2D();")));

  ASSERT_HRESULT_SUCCEEDED(ExecuteScript(_T("var webgl = new ContextWebGL();")));    
}

TEST_F(CScriptEnvTest, Properties)
{
  ASSERT_HRESULT_SUCCEEDED(ExecuteScript(_T("var canvas = new Context2D();")));

  EXCEPINFO exc;
  CComVariant result;

  ASSERT_HRESULT_SUCCEEDED(ExecuteScript(_T("canvas"), &exc, &result));

  ASSERT_EQ(VT_DISPATCH, result.vt);
  ASSERT_NE((IDispatch *) NULL, result.pdispVal);

  ASSERT_HRESULT_SUCCEEDED(ExecuteScript(_T("canvas.canvas"), &exc, &result));

  ASSERT_EQ(VT_DISPATCH, result.vt);
  ASSERT_EQ((IDispatch *) NULL, result.pdispVal);
}
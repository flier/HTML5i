#include "StdAfx.h"
#include "ScriptEnvTest.h"

#define SCRIPT_E_REPORTED 0x80020101 // http://support.microsoft.com/kb/247784

void CScriptEnvTest::SetUp()
{
  CLSID clsidJavascript;

  ASSERT_HRESULT_SUCCEEDED(::CLSIDFromProgID(_T("JavaScript"), &clsidJavascript));

  ASSERT_HRESULT_SUCCEEDED(m_spEngine.CoCreateInstance(clsidJavascript));
  
  ASSERT_HRESULT_SUCCEEDED(m_spEngine->SetScriptSite(m_host.get()));  

  CComQIPtr<IActiveScriptParse> parser = m_spEngine;

  ASSERT_HRESULT_SUCCEEDED(parser->InitNew());

  ASSERT_EQ(SCRIPTSTATE_INITIALIZED, m_host->m_state);
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

TEST_F(CScriptEnvTest, Executing)
{
  EXCEPINFO exc;
  CComVariant result;

  ASSERT_HRESULT_SUCCEEDED(ExecuteScript(_T("1+2"), &exc, &result));

  ASSERT_EQ(VT_I4, result.vt);
  ASSERT_EQ(3, result.intVal);

  ASSERT_EQ(SCRIPT_E_REPORTED, ExecuteScript(_T("nonexist"), &exc, &result));   
}

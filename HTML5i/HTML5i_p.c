

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sat Mar 19 08:57:01 2011
 */
/* Compiler settings for HTML5i.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "HTML5i_i.h"

#define TYPE_FORMAT_STRING_SIZE   3                                 
#define PROC_FORMAT_STRING_SIZE   1                                 
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _HTML5i_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } HTML5i_MIDL_TYPE_FORMAT_STRING;

typedef struct _HTML5i_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } HTML5i_MIDL_PROC_FORMAT_STRING;

typedef struct _HTML5i_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } HTML5i_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const HTML5i_MIDL_TYPE_FORMAT_STRING HTML5i__MIDL_TypeFormatString;
extern const HTML5i_MIDL_PROC_FORMAT_STRING HTML5i__MIDL_ProcFormatString;
extern const HTML5i_MIDL_EXPR_FORMAT_STRING HTML5i__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IHtml5Ext_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IHtml5Ext_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO CanvasRenderingContext2D_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO CanvasRenderingContext2D_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IContext2D_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IContext2D_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO WebGLRenderingContext_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO WebGLRenderingContext_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IContextWebGL_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IContextWebGL_ProxyInfo;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const HTML5i_MIDL_PROC_FORMAT_STRING HTML5i__MIDL_ProcFormatString =
    {
        0,
        {

			0x0
        }
    };

static const HTML5i_MIDL_TYPE_FORMAT_STRING HTML5i__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IHtml5Ext, ver. 0.0,
   GUID={0x9B84976E,0x5DA4,0x466A,{0x80,0x7F,0x36,0x7A,0x60,0x26,0x75,0x7A}} */

#pragma code_seg(".orpc")
static const unsigned short IHtml5Ext_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IHtml5Ext_ProxyInfo =
    {
    &Object_StubDesc,
    HTML5i__MIDL_ProcFormatString.Format,
    &IHtml5Ext_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IHtml5Ext_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    HTML5i__MIDL_ProcFormatString.Format,
    &IHtml5Ext_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IHtml5ExtProxyVtbl = 
{
    0,
    &IID_IHtml5Ext,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION IHtml5Ext_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _IHtml5ExtStubVtbl =
{
    &IID_IHtml5Ext,
    &IHtml5Ext_ServerInfo,
    7,
    &IHtml5Ext_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: CanvasRenderingContext2D, ver. 0.0,
   GUID={0x460266e0,0xd0fe,0x421f,{0xa6,0x69,0x42,0xe6,0xdb,0xc9,0x0b,0x89}} */

#pragma code_seg(".orpc")
static const unsigned short CanvasRenderingContext2D_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO CanvasRenderingContext2D_ProxyInfo =
    {
    &Object_StubDesc,
    HTML5i__MIDL_ProcFormatString.Format,
    &CanvasRenderingContext2D_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO CanvasRenderingContext2D_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    HTML5i__MIDL_ProcFormatString.Format,
    &CanvasRenderingContext2D_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _CanvasRenderingContext2DProxyVtbl = 
{
    0,
    &IID_CanvasRenderingContext2D,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION CanvasRenderingContext2D_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _CanvasRenderingContext2DStubVtbl =
{
    &IID_CanvasRenderingContext2D,
    &CanvasRenderingContext2D_ServerInfo,
    7,
    &CanvasRenderingContext2D_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IContext2D, ver. 0.0,
   GUID={0x25EC7740,0x2D4E,0x4304,{0xA6,0x90,0x71,0x9E,0x61,0xE1,0x83,0x86}} */

#pragma code_seg(".orpc")
static const unsigned short IContext2D_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IContext2D_ProxyInfo =
    {
    &Object_StubDesc,
    HTML5i__MIDL_ProcFormatString.Format,
    &IContext2D_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IContext2D_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    HTML5i__MIDL_ProcFormatString.Format,
    &IContext2D_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IContext2DProxyVtbl = 
{
    0,
    &IID_IContext2D,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION IContext2D_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _IContext2DStubVtbl =
{
    &IID_IContext2D,
    &IContext2D_ServerInfo,
    7,
    &IContext2D_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: WebGLRenderingContext, ver. 0.0,
   GUID={0xd09f39b0,0x9ad6,0x4fdc,{0xaf,0x56,0x6c,0x8c,0x2a,0x4c,0xaa,0x5c}} */

#pragma code_seg(".orpc")
static const unsigned short WebGLRenderingContext_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO WebGLRenderingContext_ProxyInfo =
    {
    &Object_StubDesc,
    HTML5i__MIDL_ProcFormatString.Format,
    &WebGLRenderingContext_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO WebGLRenderingContext_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    HTML5i__MIDL_ProcFormatString.Format,
    &WebGLRenderingContext_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _WebGLRenderingContextProxyVtbl = 
{
    0,
    &IID_WebGLRenderingContext,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION WebGLRenderingContext_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _WebGLRenderingContextStubVtbl =
{
    &IID_WebGLRenderingContext,
    &WebGLRenderingContext_ServerInfo,
    7,
    &WebGLRenderingContext_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IContextWebGL, ver. 0.0,
   GUID={0xA63CCF94,0x3378,0x477F,{0x94,0xAF,0x71,0xA3,0x0F,0xB9,0x22,0xAE}} */

#pragma code_seg(".orpc")
static const unsigned short IContextWebGL_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IContextWebGL_ProxyInfo =
    {
    &Object_StubDesc,
    HTML5i__MIDL_ProcFormatString.Format,
    &IContextWebGL_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IContextWebGL_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    HTML5i__MIDL_ProcFormatString.Format,
    &IContextWebGL_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IContextWebGLProxyVtbl = 
{
    0,
    &IID_IContextWebGL,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION IContextWebGL_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _IContextWebGLStubVtbl =
{
    &IID_IContextWebGL,
    &IContextWebGL_ServerInfo,
    7,
    &IContextWebGL_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    HTML5i__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x700022b, /* MIDL Version 7.0.555 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _HTML5i_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IContext2DProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IHtml5ExtProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IContextWebGLProxyVtbl,
    ( CInterfaceProxyVtbl *) &_WebGLRenderingContextProxyVtbl,
    ( CInterfaceProxyVtbl *) &_CanvasRenderingContext2DProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _HTML5i_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IContext2DStubVtbl,
    ( CInterfaceStubVtbl *) &_IHtml5ExtStubVtbl,
    ( CInterfaceStubVtbl *) &_IContextWebGLStubVtbl,
    ( CInterfaceStubVtbl *) &_WebGLRenderingContextStubVtbl,
    ( CInterfaceStubVtbl *) &_CanvasRenderingContext2DStubVtbl,
    0
};

PCInterfaceName const _HTML5i_InterfaceNamesList[] = 
{
    "IContext2D",
    "IHtml5Ext",
    "IContextWebGL",
    "WebGLRenderingContext",
    "CanvasRenderingContext2D",
    0
};

const IID *  const _HTML5i_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _HTML5i_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _HTML5i, pIID, n)

int __stdcall _HTML5i_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _HTML5i, 5, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _HTML5i, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _HTML5i, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _HTML5i, 5, *pIndex )
    
}

const ExtendedProxyFileInfo HTML5i_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _HTML5i_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _HTML5i_StubVtblList,
    (const PCInterfaceName * ) & _HTML5i_InterfaceNamesList,
    (const IID ** ) & _HTML5i_BaseIIDList,
    & _HTML5i_IID_Lookup, 
    5,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/


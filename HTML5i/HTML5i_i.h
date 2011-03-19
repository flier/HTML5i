

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sat Mar 19 01:25:02 2011
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

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __HTML5i_i_h__
#define __HTML5i_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IHtml5Ext_FWD_DEFINED__
#define __IHtml5Ext_FWD_DEFINED__
typedef interface IHtml5Ext IHtml5Ext;
#endif 	/* __IHtml5Ext_FWD_DEFINED__ */


#ifndef __Html5Ext_FWD_DEFINED__
#define __Html5Ext_FWD_DEFINED__

#ifdef __cplusplus
typedef class Html5Ext Html5Ext;
#else
typedef struct Html5Ext Html5Ext;
#endif /* __cplusplus */

#endif 	/* __Html5Ext_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IHtml5Ext_INTERFACE_DEFINED__
#define __IHtml5Ext_INTERFACE_DEFINED__

/* interface IHtml5Ext */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IHtml5Ext;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9B84976E-5DA4-466A-807F-367A6026757A")
    IHtml5Ext : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IHtml5ExtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHtml5Ext * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHtml5Ext * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHtml5Ext * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IHtml5Ext * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IHtml5Ext * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IHtml5Ext * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IHtml5Ext * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IHtml5ExtVtbl;

    interface IHtml5Ext
    {
        CONST_VTBL struct IHtml5ExtVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHtml5Ext_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHtml5Ext_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHtml5Ext_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHtml5Ext_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IHtml5Ext_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IHtml5Ext_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IHtml5Ext_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHtml5Ext_INTERFACE_DEFINED__ */



#ifndef __HTML5iLib_LIBRARY_DEFINED__
#define __HTML5iLib_LIBRARY_DEFINED__

/* library HTML5iLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_HTML5iLib;

EXTERN_C const CLSID CLSID_Html5Ext;

#ifdef __cplusplus

class DECLSPEC_UUID("275DF25D-C09D-43C8-90D7-9348D6059563")
Html5Ext;
#endif
#endif /* __HTML5iLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif



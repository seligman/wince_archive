/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri May 05 09:34:09 2000
 */
/* Compiler settings for sip_i.c:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __sip_i_h__
#define __sip_i_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_sip_i_0000 */
/* [local] */ 

typedef struct  _IID
    {
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char c[ 8 ];
    }	IID;

typedef IID CLSID;

const IID LIBID_QWERTYIM;

const IID IID_IIMCallback;

const IID IID_IInputMethod;

const CLSID CLSID_CMSQwertyIm;



extern RPC_IF_HANDLE __MIDL_itf_sip_i_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_sip_i_0000_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif

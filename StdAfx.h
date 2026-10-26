// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__098A71A8_FE31_414C_8AAD_3A8BB6624F39__INCLUDED_)
#define AFX_STDAFX_H__098A71A8_FE31_414C_8AAD_3A8BB6624F39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define WINVER 0x0500

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "usbc\error.h"
#include "usbc\usbcdef.h"
#include "usbc\usbc.h"
#include "usbc\extern.h"

#pragma warning(disable : 4996)


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__098A71A8_FE31_414C_8AAD_3A8BB6624F39__INCLUDED_)

// ManualMove.h : main header file for the MANUALMOVE application
//

#if !defined(AFX_MANUALMOVE_H__3EDDBD65_B3C0_4D7D_B755_D9999B55883F__INCLUDED_)
#define AFX_MANUALMOVE_H__3EDDBD65_B3C0_4D7D_B755_D9999B55883F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CManualMoveApp:
// See ManualMove.cpp for the implementation of this class
//

class CManualMoveApp : public CWinApp
{
public:
	CManualMoveApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManualMoveApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CManualMoveApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANUALMOVE_H__3EDDBD65_B3C0_4D7D_B755_D9999B55883F__INCLUDED_)

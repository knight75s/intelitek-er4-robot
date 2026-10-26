// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "ManualMove.h"
#include "MyButton.h"
#include "ManualMoveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyButton

CMyButton::CMyButton()
{
}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	//{{AFX_MSG_MAP(CMyButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyButton message handlers

void CMyButton::OnLButtonDown(UINT nFlags, CPoint point) 
{	
	CButton::OnLButtonDown(nFlags, point);
	CManualMoveDlg* pWnd = (CManualMoveDlg*)GetParent();
	pWnd->RunManual(GetDlgCtrlID());
}

void CMyButton::OnLButtonUp(UINT nFlags, CPoint point) 
{	
	CButton::OnLButtonUp(nFlags, point);
	CManualMoveDlg* pWnd = (CManualMoveDlg*)GetParent();
	pWnd->StopManual();
}

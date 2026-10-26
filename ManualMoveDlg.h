// ManualMoveDlg.h : header file
//

#if !defined(AFX_MANUALMOVEDLG_H__83D01FFC_1537_4117_9F68_2B6544F254E3__INCLUDED_)
#define AFX_MANUALMOVEDLG_H__83D01FFC_1537_4117_9F68_2B6544F254E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_INIT_END			WM_APP + 1 
#define WM_EMER_ON			WM_APP + 2
#define WM_EMER_OFF			WM_APP + 3
#define WM_TP_TEACH			WM_APP + 4
#define WM_TP_AUTO			WM_APP + 5
#define WM_STATUS_TEXT		WM_APP + 6
const int TIMER_ID_INIT	  =	100;
const int TIMER_ID_MANUAL = 101;
const int TIMER_MANUAL_PERIOD = 300;

#include "MyButton.h"

/////////////////////////////////////////////////////////////////////////////
// CManualMoveDlg dialog

class CManualMoveDlg : public CDialog
{
// Construction
public:
	CManualMoveDlg(CWnd* pParent = NULL);	// standard constructor

	void StartInitTimer();
	void StopInitTimer(BOOL bIsDone);
	void DisableAll(BOOL bIsDisable = TRUE);
	void RunManual(int iButtonId);
	void StopManual();

	BOOL m_bIsCon;

// Dialog Data
	//{{AFX_DATA(CManualMoveDlg)
	enum { IDD = IDD_MANUALMOVE_DIALOG };
	CMyButton	m_ButtonPlus;
	CMyButton	m_ButtonMinus;
	int		m_iCurrAxis;
	int		m_iComboSpeed;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManualMoveDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CManualMoveDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpenGropper();
	afx_msg void OnButtonCloseGropper();
	afx_msg void OnInit();
	afx_msg void OnCon();
	afx_msg void OnCoff();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnInit2();
	//}}AFX_MSG
	afx_msg LRESULT OnInitEnd( WPARAM wParam, LPARAM  lParam );
	afx_msg LRESULT OnCtrlStatus( WPARAM wParam, LPARAM  lParam );
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANUALMOVEDLG_H__83D01FFC_1537_4117_9F68_2B6544F254E3__INCLUDED_)

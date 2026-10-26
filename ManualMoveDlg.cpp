// ManualMoveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ManualMove.h"
#include "ManualMoveDlg.h"
#include "CallBack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManualMoveDlg dialog

CManualMoveDlg::CManualMoveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CManualMoveDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CManualMoveDlg)
	m_iCurrAxis = -1;
	m_iComboSpeed = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CManualMoveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManualMoveDlg)
	DDX_Control(pDX, IDC_BUTTON_PLUS, m_ButtonPlus);
	DDX_Control(pDX, IDC_BUTTON_MINUS, m_ButtonMinus);
	DDX_Radio(pDX, IDC_RADIO_AXIS_1, m_iCurrAxis);
	DDX_CBIndex(pDX, IDC_COMBO_SPEED, m_iComboSpeed);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CManualMoveDlg, CDialog)
	//{{AFX_MSG_MAP(CManualMoveDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_GROPPER, OnButtonOpenGropper)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_GROPPER, OnButtonCloseGropper)
	ON_BN_CLICKED(IDM_INIT, OnInit)
	ON_BN_CLICKED(IDM_CON, OnCon)
	ON_BN_CLICKED(IDM_COFF, OnCoff)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDM_INIT2, OnInit2)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_INIT_END, OnInitEnd)
	ON_MESSAGE(WM_STATUS_TEXT, OnCtrlStatus)
	ON_COMMAND(IDM_CON, OnCon)
	ON_COMMAND(IDM_COFF, OnCoff)
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManualMoveDlg message handlers

BOOL CManualMoveDlg::OnInitDialog()
{
	m_bIsCon = FALSE;
	m_iComboSpeed = 4;
	m_iCurrAxis = 0;

	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon	
	
	GetDlgItem(IDC_EDIT_MODE)->SetWindowText("Off-Line");
	GetDlgItem(IDC_EDIT_CON_OFF)->SetWindowText("Cof");
	Invalidate();

	WatchMotion((CallBackFun)&MotionEnd);
	WatchControl((CallBackFun)&AxisControl);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}	

void CManualMoveDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CManualMoveDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CManualMoveDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//-----------------------------------------------------
void CManualMoveDlg::OnInit() 
{	
	StartInitTimer();
	BOOL b = Initialization(INIT_MODE_ONLINE, (CallBackFun)&InitEnd, (CallBackFun)&ErrorMessage);
}

//-----------------------------------------------------
LRESULT CManualMoveDlg::OnInitEnd( WPARAM wParam, LPARAM  lParam )
{
	StopInitTimer(TRUE);
	short nMode = GetMode();
	
    switch(nMode)
	{
		case INIT_MODE_ONLINE:
		{
			GetDlgItem(IDC_EDIT_MODE)->SetWindowText("On-Line");
			if(AfxMessageBox("Control  is  off. Do you want to execute Control On?", MB_OKCANCEL) == IDOK)
			{
				SendMessage(WM_COMMAND, IDM_CON);
			}		
			break;
		}
		case INIT_MODE_OFFLINE:
		{
			GetDlgItem(IDC_EDIT_MODE)->SetWindowText("Off-Line");
			break;
		}

		case INIT_MODE_SIMULAT:
		{
			GetDlgItem(IDC_EDIT_MODE)->SetWindowText("Sumulation");
			break;
		}

		default:
		{
			AfxMessageBox( "InitEnd invalid notification");
			break;		
		}
	}
	Invalidate();
	return 0;
}

//-------------------------------------------------------
void CManualMoveDlg::OnCon() 
{
	if(Control( '&', TRUE ) == FALSE)
	{
		return;
	}
}
void CManualMoveDlg::OnCoff() 
{
	if(Control('&', FALSE) == FALSE)
	{
		return;
	}
}

//-----------------------------------------------------
LRESULT CManualMoveDlg::OnCtrlStatus( WPARAM wParam, LPARAM  lParam )
{
	if(wParam == 0)
	{
		GetDlgItem(IDC_EDIT_MODE)->SetWindowText((LPCTSTR)lParam);
	}
	else if(wParam == 1)
	{
		GetDlgItem(IDC_EDIT_CON_OFF)->SetWindowText((LPCTSTR)lParam);
	}
	Invalidate();
	return 0;
}

//-----------------------------------------------------
void CManualMoveDlg::RunManual(int iButtonId)
{
	if(!UpdateData(TRUE))
		return;

	ConfigData Config;
    if(GetConfig(Config) == FALSE)
		return;	

	static DWORD dwPrevTick = 0L;
	DWORD dwCurTick = GetTickCount();

	if(dwCurTick - dwPrevTick < (DWORD)(TIMER_MANUAL_PERIOD))
	{
		dwPrevTick = dwCurTick;
		return;
	}

	m_iComboSpeed += 1;
	if(iButtonId == IDC_BUTTON_MINUS)
		m_iComboSpeed *= -1;
	
	if(m_iCurrAxis < 0 || m_iCurrAxis > 5)
		return;

	EnterManual(MANUAL_TYPE_ENC);		
	MoveManual((unsigned char)m_iCurrAxis, m_iComboSpeed * 10);

	SetTimer(TIMER_ID_MANUAL, TIMER_MANUAL_PERIOD, 0);
	dwPrevTick = dwCurTick;
}

//-----------------------------------------------------
void CManualMoveDlg::StopManual()
{
	m_iCurrAxis = -1;
	KillTimer(TIMER_ID_MANUAL);
	CloseManual();
}

//-----------------------------------------------------
void CManualMoveDlg::OnButtonOpenGropper() 
{
	OpenGripper();
}

//-----------------------------------------------------
void CManualMoveDlg::OnButtonCloseGropper() 
{
	CloseGripper();
}

//-----------------------------------------------------
void CManualMoveDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == TIMER_ID_INIT)
	{			
		StopInitTimer(FALSE);
	}	
	if(nIDEvent == TIMER_ID_MANUAL)
	{		
		MoveManual(m_iCurrAxis, m_iComboSpeed * 10);
	}     

	CDialog::OnTimer(nIDEvent);
}
//-----------------------------------------------------
void CManualMoveDlg::StartInitTimer()
{
	SetWindowText("Initialization please wait ...");
	DisableAll();	
	SetTimer(TIMER_ID_INIT, 15000, 0);	
}
//-----------------------------------------------------
void CManualMoveDlg::StopInitTimer(BOOL bIsDone)
{
	SetWindowText("Manual Movement");
	DisableAll(FALSE);
	KillTimer(TIMER_ID_INIT);
}
//-----------------------------------------------------
void CManualMoveDlg::DisableAll(BOOL bIsDisable)
{
	CWnd* pWnd = this->GetWindow(GW_CHILD);
    while( pWnd )
	{        
		pWnd->EnableWindow(!bIsDisable);		
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);		
	}
}

HBRUSH CManualMoveDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	int iCurControl = pWnd->GetDlgCtrlID();
	if(iCurControl ==	IDC_EDIT_MODE)
	{	
		if(IsOnLineOk())
		{
			pDC->SetTextColor(RGB(0, 150, 0));
		}
		else
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
	}
	if(iCurControl == IDC_EDIT_CON_OFF)
	{		
		if(m_bIsCon)
		{
			pDC->SetTextColor(RGB(0, 150, 0));
		}
		else
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
	}
	return hbr;
}

void CManualMoveDlg::OnInit2() 
{
	BOOL b = Initialization(INIT_MODE_SIMULAT, (CallBackFun)&InitEnd, (CallBackFun)&ErrorMessage);
}

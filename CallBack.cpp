// File:  CallBack.cpp               Date: 26-AUG-2009
//

#include "stdafx.h"
#include "CallBack.h"
#include "ManualMove.h"
#include "ManualMoveDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//----------------------------------------------------
void MotionEnd(UCHAR *ucEndCode)
{
	TCHAR szWork[ 256 ] = _T("");
    UCHAR ucCode = *ucEndCode;
	CManualMoveApp *pManualMoveApp = (CManualMoveApp *)AfxGetApp();
	CManualMoveDlg* pMainFrame = (CManualMoveDlg*)pManualMoveApp->m_pMainWnd;
	if(pMainFrame == NULL)
	{
		return;
	}
	switch(ucCode)
	{
		case 'A':
		   _stprintf( szWork, _T("End of Robot's motion"));
		   break;
		case 'B':
			_stprintf( szWork, _T("End of Peripheral's motion"));
			break;
		case 'G':
			_stprintf( szWork, "End of the Gripper Movement");
			break;     
		default:
			_stprintf( szWork, _T("End of axis: %d motion"), ucCode );
			break; 
	}
}
//-----------------------------------------------
void InitEnd(ConfigData *pTheConfigData)
{
	CManualMoveApp *pManualMoveApp = (CManualMoveApp *)AfxGetApp();
	CManualMoveDlg* pMainFrame = (CManualMoveDlg*)pManualMoveApp->m_pMainWnd;
	if( pMainFrame == NULL )
		return;
    pMainFrame->PostMessage( WM_INIT_END );    
}

//--------------------------------------------------------------
void AxisControl(UINT * uiBitmap)
{
	UINT con = *uiBitmap;
	CManualMoveApp *pManualMoveApp = (CManualMoveApp *)AfxGetApp();
	CManualMoveDlg* pMainFrame = (CManualMoveDlg*)pManualMoveApp->m_pMainWnd;
	if(pMainFrame != NULL)
	{
		if(con != 255)
		{
			pMainFrame->SendMessage(WM_STATUS_TEXT, (WPARAM)1, (LPARAM) "Coff");
			pMainFrame->m_bIsCon = FALSE;
		}
        else
		{
			pMainFrame->SendMessage(WM_STATUS_TEXT, (WPARAM)1, (LPARAM) "Con");
			pMainFrame->m_bIsCon = TRUE;
		}	    
	}
}

//--------------------------------------------------------------
void ErrorMessage( ErrorInfo *pTheErrorInfo )
{	
	TCHAR szWork[512], szTemp[512];
	char szTitle[32] = "";
	char szDate[32] = "";
	char szTime[32] = "";
	_strdate(szDate);
	_strtime(szTime);			

	CManualMoveApp *pManualMoveApp = (CManualMoveApp *)AfxGetApp();
	CManualMoveDlg* pMainFrame = (CManualMoveDlg*)pManualMoveApp->m_pMainWnd;
	if( pMainFrame == NULL )
	{
		_stprintf( szWork, _T("(%d)  Axis No %d   %s"),
		pTheErrorInfo->lNumber, pTheErrorInfo->cAxis, pTheErrorInfo->cOptional );
		pMainFrame->MessageBox(szWork, "CONTROLLER MESSAGE", MB_OK |  MB_ICONEXCLAMATION);		
		return;
	}

	switch(pTheErrorInfo->lNumber)
	{
		case ERR_EMERG_ON: 
			pMainFrame->SendMessage(WM_EMER_ON);
			return;

		case ERR_EMERG_OFF:  
			pMainFrame->SendMessage(WM_EMER_OFF);
			return;

		case ERR_HT:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, szTemp );
			break;

		case ERR_HOME_ABORTED:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Homing aborted by user" );			
			break;

		case ERR_INVPAR:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Invalid parameter in file" );
			break;

		case ERR_NOT_RESPOND:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Controller is not responding" );
			pMainFrame->SendMessage(WM_STATUS_TEXT, (WPARAM)0, (LPARAM) "Off-Line");
			pMainFrame->SendMessage(WM_STATUS_TEXT, (WPARAM)1, (LPARAM) "Coff");			
			pMainFrame->MessageBox(szWork, "CONTROLLER MESSAGE", MB_OK | MB_ICONEXCLAMATION);			
			pMainFrame->m_bIsCon = FALSE;
    		return;

		case ERR_TRCK:
			sprintf(szTemp, "%s  Axis %d", "Position error during the motion is too great or impact has occurred", pTheErrorInfo->cAxis);
			_stprintf(szWork, _T("(%d)  %s.\n\n%s"), pTheErrorInfo->lNumber, szTemp, "Control  is  off. Do you want to execute Control On?" );
			if(pMainFrame->MessageBox(szWork, "CONTROLLER MESSAGE", MB_OKCANCEL | MB_ICONSTOP) == IDOK)
			{
				pMainFrame->SendMessage(WM_COMMAND, IDM_CON);
			}
			return;

		case ERR_COFF:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Control disabled" );						
			break;

		case ERR_ROBOT_HM_ND:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Robot has not been homed" );
			break;

		case KIN_ALPHA:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Position is not in the Cartesian workspace.\n( Kinematics: alpha error )" );												
			break;

		case KIN_BETA:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Position is not in the Cartesian workspace.\n( Kinematics: beta error )" );												
			break;

		case ERR_XYZ_INV:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Position is not in the Cartesian workspace" );															
			break;

		case ERR_JNT_INV:			
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Position is not in the Cartesian workspace" );
			break;

		case  ERR_ENC_INV:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Position is not in the encoder workspace" );			
			break;

		case  ERR_MOVP:			
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Motion in progress" );			
			break;

		case  ERR_SPEED:			
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Excessive speed required" );			
			break;

		case  ERR_ACCL:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Excessive acceleration required" );						
			break;

		case  ERR_MDUR:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Invalid movement duration" );
			break;

		case  ERR_TIME_PAR:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Invalid time duration for motion" );
			break;

		case  ERR_VELO_PAR:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Invalid velocity" );
			break;

		case  ERR_A_PAR:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Invalid acceleration parameter" );
			break;

		case  ERR_AA_PAR:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Invalid parameter for increase of acceleration" );
			break;

		case  ERR_SKIN:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Cannot execute movement along a specified path" );
			break;

		case  ERR_GRP_INV:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Invalid group" );
			break;

		case  KIN_CFG:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Kinematics: invalid configuration parameters" );
			break;

		case  ERR_B_INV:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Position is not in the peripheral workspace" );
			break;

		case  ERR_CCHANGE:
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, "Robot cannot execute movement due to angle of robot arm at axis 3" );
			break;

		case  TP_TEACH:
			pMainFrame->SendMessage(WM_TP_TEACH);			
			return;

		case  TP_AUTO:
			pMainFrame->SendMessage(WM_TP_AUTO);
			return;

		case  ERR_AXTYPE:
			_stprintf(szTemp, "Invalid axis type. Axis No %d", pTheErrorInfo->cAxis);
			_stprintf(szWork, _T("(%d)  %s"), pTheErrorInfo->lNumber, szTemp );
			break;
		
		default:
			if(pTheErrorInfo->cAxis == 0)
			{
    			_stprintf(szWork, _T("(%d)    %s"), pTheErrorInfo->lNumber, pTheErrorInfo->cOptional);
			}
			else
			{
    			_stprintf(szWork, _T("(%d)  Axis No %d   %s"), pTheErrorInfo->lNumber, pTheErrorInfo->cAxis, pTheErrorInfo->cOptional);
			}
			break;
	};	
	
	pMainFrame->MessageBox(szWork, "CONTROLLER MESSAGE", MB_OK |  MB_ICONEXCLAMATION);	
}


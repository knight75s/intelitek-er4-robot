; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CManualMoveDlg
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ManualMove.h"

ClassCount=4
Class1=CManualMoveApp
Class2=CManualMoveDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CMyButton
Resource3=IDD_MANUALMOVE_DIALOG

[CLS:CManualMoveApp]
Type=0
HeaderFile=ManualMove.h
ImplementationFile=ManualMove.cpp
Filter=N

[CLS:CManualMoveDlg]
Type=0
HeaderFile=ManualMoveDlg.h
ImplementationFile=ManualMoveDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_COMBO_SPEED

[CLS:CAboutDlg]
Type=0
HeaderFile=ManualMoveDlg.h
ImplementationFile=ManualMoveDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MANUALMOVE_DIALOG]
Type=1
Class=CManualMoveDlg
ControlCount=21
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RADIO_AXIS_1,button,1342308361
Control3=IDC_RADIO_AXIS_2,button,1342177289
Control4=IDC_RADIO_AXIS_3,button,1342177289
Control5=IDC_RADIO_AXIS_4,button,1342177289
Control6=IDC_RADIO_AXIS_5,button,1342177289
Control7=IDC_RADIO_AXIS_6,button,1342177289
Control8=IDC_BUTTON_PLUS,button,1342242816
Control9=IDC_BUTTON_MINUS,button,1342242816
Control10=IDC_BUTTON_OPEN_GROPPER,button,1342242816
Control11=IDC_BUTTON_CLOSE_GROPPER,button,1342242816
Control12=IDM_INIT,button,1342242816
Control13=IDM_CON,button,1342242816
Control14=IDM_COFF,button,1342242816
Control15=IDC_STATIC,static,1342308352
Control16=IDC_COMBO_SPEED,combobox,1344339971
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342177296
Control19=IDC_EDIT_MODE,edit,1350633601
Control20=IDC_EDIT_CON_OFF,edit,1350633601
Control21=IDM_INIT2,button,1342242816

[CLS:CMyButton]
Type=0
HeaderFile=MyButton.h
ImplementationFile=MyButton.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC


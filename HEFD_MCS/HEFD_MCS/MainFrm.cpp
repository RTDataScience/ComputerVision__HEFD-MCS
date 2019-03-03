// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MainFrm.cpp : implementation of the CMainFrame class
//
#pragma once
#include "stdafx.h"
#include "HEFD_MCS.h"

#include "HEFD_MCSDoc.h"
#include "HEFD_MCSView.h"


#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
    ON_COMMAND(ID_checkProperties, &CMainFrame::OnCheckProperties)
    ON_UPDATE_COMMAND_UI(ID_checkProperties, &CMainFrame::OnUpdateCheckProperties)
    ON_COMMAND(ID_buttonStart, &CMainFrame::OnButtonStart)
    ON_COMMAND(ID_buttonContinue, &CMainFrame::OnButtonContinue)
    ON_COMMAND(ID_buttonPause, &CMainFrame::OnButtonPause)
    ON_COMMAND(ID_buttonStop, &CMainFrame::OnButtonStop)
    ON_UPDATE_COMMAND_UI(ID_checkRepeat, &CMainFrame::OnUpdateCheckRepeat)
    ON_COMMAND(ID_checkRepeat, &CMainFrame::OnCheckRepeat)
    ON_COMMAND(ID_buttonStep, &CMainFrame::OnButtonStep)
    ON_COMMAND(ID_comboRate, &CMainFrame::OncomboRate)
    ON_COMMAND(ID_bottonBackwards, &CMainFrame::OnBottonBackwards)
    ON_COMMAND(ID_ButtonForwards, &CMainFrame::OnButtonForwards)
    ON_COMMAND(ID_ButtonNextFrame, &CMainFrame::OnButtonNextFrame)
    ON_COMMAND(ID_ButtonPreviousFrame, &CMainFrame::OnButtonPreviousFrame)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);
    
    m_bFirstTime = TRUE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// set the visual manager and style based on persisted value
	OnApplicationLook(theApp.m_nAppLook);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // other styles available...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // set to FALSE to place close button at right of tab area
	mdiTabParams.m_bTabIcons = FALSE;    // set to TRUE to enable document icons on MDI taba
	mdiTabParams.m_bAutoColor = TRUE;    // set to FALSE to disable auto-coloring of MDI tabs
	mdiTabParams.m_bDocumentMenu = TRUE; // enable the document menu at the right edge of the tab area
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// create docking windows
	if (!CreateDockingWindows())
	{
		TRACE0("Failed to create docking windows\n");
		return -1;
	}

    
    m_wndProperties.ShowWindow(SW_SHOW);
    m_bVideoDisplayRepeat = FALSE;
    
    CMFCRibbonComboBox* pComboBoxRate = DYNAMIC_DOWNCAST ( CMFCRibbonComboBox, m_wndRibbonBar.FindByID(ID_comboRate) );
    pComboBoxRate->RemoveAllItems();
    pComboBoxRate->AddItem ( (LPCTSTR) _T("0.5") );
    pComboBoxRate->AddItem ( (LPCTSTR) _T("1.0") );
    pComboBoxRate->AddItem ( (LPCTSTR) _T("2.0") );
    pComboBoxRate->AddItem ( (LPCTSTR) _T("4.0") );
    pComboBoxRate->AddItem ( (LPCTSTR) _T("8.0") );
    pComboBoxRate->SelectItem ( 1 );
    
	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);

	// Enable enhanced windows management dialog
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// Switch the order of document name and application name on the window title bar. This
	// improves the usability of the taskbar because the document name is visible with the thumbnail.
	ModifyStyle(0, FWS_PREFIXTITLE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;
	// Create properties window
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Properties window\n");
		return FALSE; // failed to create
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

	UpdateMDITabbedBarsIcons();
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


void CMainFrame::OnCheckProperties()
{
    // TODO: Add your command handler code here
    
    Sleep(0);
    if ( m_wndProperties.IsVisible() == TRUE )
    {
        m_wndProperties.ShowWindow(SW_HIDE);
        m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
        DockPane(&m_wndProperties);
    }
    else if ( m_wndProperties.IsVisible() == FALSE )
    {
        m_wndProperties.ShowWindow(SW_SHOW);
        m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
        DockPane(&m_wndProperties);
    }

    
}


void CMainFrame::OnUpdateCheckProperties(CCmdUI *pCmdUI)
{
    
    
    Sleep(0);
    if ( m_wndProperties.IsVisible() == TRUE )
    {
        pCmdUI->SetCheck(TRUE);
    }
    else if ( m_wndProperties.IsVisible() == FALSE )
    {
        pCmdUI->SetCheck(FALSE);
    }
    
}


void CMainFrame::OnButtonStart()
{
	((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->DisableAllRadioButton();

    ((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->lFrameCount = 1;
    if (m_wndProperties.iComboBoxProperties == 0)
    {
        ((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->bStopFlag = true;
        actisdk.Pause();
    }
    else if (m_wndProperties.iComboBoxProperties == 1)
    {
        ((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->bStopFlag = true;
        isapnvrsdk.Stop_NVRChannel();
        SAFE_DELETE_ARRAY(((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->pucMonitorSaveCurrentBitmap);
        SAFE_DELETE_ARRAY(((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->pucReduceAnalysisImageCurrent1);
        SAFE_DELETE_ARRAY(((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->pucReduceAnalysisImageCurrent2);
    }
    else if (m_wndProperties.iComboBoxProperties == 2)
    {
        if (directshow.m_hVideoDisplayThread != NULL)
        {
            ((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->bStopFlag = true;
            directshow.Pause();
        }
    }
    else if (m_wndProperties.iComboBoxProperties == 3)
    {
        ((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->bStopFlag = true;
        usbcamera.PreviewPause();
    }

    SAFE_DELETE ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pHEFD_MCS );
    SAFE_DELETE ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pOtherAlgorithm0001 );
    SAFE_DELETE ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pOtherAlgorithm0002 );
    SAFE_DELETE ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pOtherAlgorithm0003 );
    ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pHEFD_MCS = new CHEFD_MCS;
    ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pOtherAlgorithm0001 = new COtherAlgorithm0001;
    ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pOtherAlgorithm0002 = new COtherAlgorithm0002;
    ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pOtherAlgorithm0003 = new COtherAlgorithm0003;
    Sleep(0);
    CString cszTemp = _T("");
    ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->m_editResize.GetWindowTextA ( cszTemp );
    ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->stCHEFD_MCSInit.dbInThreshold04 = atof ( cszTemp.GetBuffer() );
    ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->stOtherAlgorithm0001Init.dbInThreshold04 = atof ( cszTemp.GetBuffer() );
    ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->stOtherAlgorithm0002Init.dbInThreshold04 = atof ( cszTemp.GetBuffer() );
    ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->stOtherAlgorithm0003Init.dbInThreshold04 = atof ( cszTemp.GetBuffer() );
    ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->dbReduceDivisor = atof ( cszTemp.GetBuffer() );

    SAFE_DELETE_ARRAY ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pucMonitorSaveCurrentBitmap );
    SAFE_DELETE_ARRAY ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pucReduceAnalysisImageCurrent1 );
    SAFE_DELETE_ARRAY ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pucReduceAnalysisImageCurrent2 );
    
    if ( m_wndProperties.iComboBoxProperties == 0 )
    {
        bool bRet = false;
        bRet = actisdk.SetWindowHandle ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() );
        if ( bRet == false ) { ShowError(); return; }
        bRet = m_wndProperties.GetPropertiesParameter();
        if ( bRet == false ) { ShowError(); return; }
        char* cCheckACTiTypeRAWFile = strstr ( m_wndProperties.cACTi_Type, _T("RAW File") );
        char* cCheckACTiTypeIPCamera = strstr ( m_wndProperties.cACTi_Type, _T("IP Camera") );
        if ( cCheckACTiTypeRAWFile != NULL )
        {
            size_t sizetFileName = strlen ( m_wndProperties.cACTi_FileName );
            if ( sizetFileName == 0 ) { ShowError(); return; }
            bRet = actisdk.Start_RAWFile ( 
                m_wndProperties.cACTi_FileName
                );
            if ( bRet == false ) { ShowError(); return; }
            ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->lFrameCount = 0;
            ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = false;
            ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bCHEFD_MCSInit = true;
            ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0001Init = true;
            ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0002Init = true;
            ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0003Init = true;
            OncomboRate();
        }
        else if ( cCheckACTiTypeIPCamera != NULL )
        {
            size_t sizetUserID = strlen ( m_wndProperties.cACTi_UserID );
            if ( sizetUserID == 0 ) { ShowError(); return; }
            size_t sizetPassword = strlen ( m_wndProperties.cACTi_Password );
            if ( sizetPassword == 0 ) { ShowError(); return; }
            ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->lFrameCount = 0;
            ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bCHEFD_MCSInit = true;
            ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0001Init = true;
            ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0002Init = true;
            ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0003Init = true;
            bRet = actisdk.Start_IPCamera (
                m_wndProperties.iACTi_IPv41,
                m_wndProperties.iACTi_IPv42,
                m_wndProperties.iACTi_IPv43,
                m_wndProperties.iACTi_IPv44,
                m_wndProperties.cACTi_UserID,
                m_wndProperties.cACTi_Password
                );
            if ( bRet == false ) { ShowError(); return; }
            ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = false;
        }
    }
    else if ( m_wndProperties.iComboBoxProperties == 1 )
    {
        bool bRet = false;
        bRet = m_wndProperties.GetPropertiesParameter();
        if ( bRet == false ) { ShowError(); return; }
        bRet = isapnvrsdk.Start_NVRChannel (
            m_wndProperties.iiSAPNVR_IPv41,
            m_wndProperties.iiSAPNVR_IPv42,
            m_wndProperties.iiSAPNVR_IPv43,
            m_wndProperties.iiSAPNVR_IPv44,
            m_wndProperties.iiSAPNVR_IPv4Port,
            m_wndProperties.ciSAPNVR_Channel,
            5000,
            m_wndProperties.ciSAPNVR_UserID,
            m_wndProperties.ciSAPNVR_Password,
            (unsigned long) ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )
            );
        if ( bRet == false ) { ShowError(); return; }
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->lFrameCount = 0;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = false;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bCHEFD_MCSInit = true;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0001Init = true;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0002Init = true;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0003Init = true;
    }
    else if ( m_wndProperties.iComboBoxProperties == 2 )
    {
        bool bRet = false;
        bRet = directshow.SetWindowHandle ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() );
        if ( bRet == false ) { ShowError(); return; }
        bRet = m_wndProperties.GetPropertiesParameter();
        if ( bRet == false ) { ShowError(); return; }
        size_t sizetFileName = strlen ( m_wndProperties.cDirectShow_FileName );
        if ( sizetFileName == 0 ) { ShowError(); return; }
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->lFrameCount = 0;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bCHEFD_MCSInit = true;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0001Init = true;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0002Init = true;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0003Init = true;
        bRet = directshow.Start_MovieFile ( m_wndProperties.cDirectShow_FileName, (bool) m_bVideoDisplayRepeat );
        if ( bRet == false ) { ShowError(); return; }
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = false;
    }
    else if ( m_wndProperties.iComboBoxProperties == 3 )
    {
        bool bRet = false;
        bRet = m_wndProperties.GetPropertiesParameter();
        if ( bRet == false ) { return; }
        size_t sizetFileName = strlen ( m_wndProperties.cUSBCamera_DeviceName );
        if ( sizetFileName == 0 ) { return; }
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->lFrameCount = 0;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bCHEFD_MCSInit = true;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0001Init = true;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0002Init = true;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0003Init = true;
        usbcamera.MachineRelease();
        usbcamera.Preview ( 
            (void*) (CHEFD_MCSView*) GetActiveFrame()->GetActiveView(),  
            m_wndProperties.cUSBCamera_DeviceName,
            m_bFirstTime
            );
        if ( bRet == false ) { return; }
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = false;
    }

    if ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag == false )
    {
        QueryPerformanceFrequency ( &( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->litmp ) );
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->dfFreq = (double) ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->litmp.QuadPart;
        QueryPerformanceCounter ( &( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->litmp ) );
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->QPart1 = ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->litmp.QuadPart;
    }
    
    if (((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->iChoiceMode == 1)
    {
        ((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->CheckRadioButton(IDC_radioCHEFD_MCS, IDC_radioCHEFD_MCS2, IDC_radioCHEFD_MCS);
        ((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->GetDlgItem(IDC_radioCHEFD_MCS)->SetFocus();
    }
    else if (((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->iChoiceMode == 2)
    {
        ((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->CheckRadioButton(IDC_radioCHEFD_MCS, IDC_radioCHEFD_MCS2, IDC_radioOtherAlgorithm0001);
        ((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->GetDlgItem(IDC_radioOtherAlgorithm0001)->SetFocus();
    }
    else if (((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->iChoiceMode == 3)
    {
        ((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->CheckRadioButton(IDC_radioCHEFD_MCS, IDC_radioCHEFD_MCS2, IDC_radioOtherAlgorithm0002);
        ((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->GetDlgItem(IDC_radioOtherAlgorithm0002)->SetFocus();
    }
    else if (((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->iChoiceMode == 4)
    {
        ((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->CheckRadioButton(IDC_radioCHEFD_MCS, IDC_radioCHEFD_MCS2, IDC_radioOtherAlgorithm0003);
        ((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->GetDlgItem(IDC_radioOtherAlgorithm0003)->SetFocus();
    }
    else if (((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->iChoiceMode == 11)
    {
        ((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->CheckRadioButton(IDC_radioCHEFD_MCS, IDC_radioCHEFD_MCS2, IDC_radioCHEFD_MCS2);
        ((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->GetDlgItem(IDC_radioCHEFD_MCS2)->SetFocus();
    }

}


void CMainFrame::OnButtonContinue()
{
	((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->EnableAllRadioButton();

    if ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pHEFD_MCS == NULL ||
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pOtherAlgorithm0001 == NULL ||
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pOtherAlgorithm0002 == NULL ||
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pOtherAlgorithm0003 == NULL
        )
    {
        return;
    }
    Sleep(0);
    
    if ( m_wndProperties.iComboBoxProperties == 0 )
    {
        actisdk.Continue ();
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = false;
    }
    else if ( m_wndProperties.iComboBoxProperties == 1 )
    {
        bool bRet = false;
        bRet = m_wndProperties.GetPropertiesParameter();
        if ( bRet == false ) { ShowError(); return; }
        bRet = isapnvrsdk.Start_NVRChannel (
            m_wndProperties.iiSAPNVR_IPv41,
            m_wndProperties.iiSAPNVR_IPv42,
            m_wndProperties.iiSAPNVR_IPv43,
            m_wndProperties.iiSAPNVR_IPv44,
            m_wndProperties.iiSAPNVR_IPv4Port,
            m_wndProperties.ciSAPNVR_Channel,
            5000,
            m_wndProperties.ciSAPNVR_UserID,
            m_wndProperties.ciSAPNVR_Password,
            (unsigned long) ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )
            );
        if ( bRet == false ) { ShowError(); return; }
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->lFrameCount = 0;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = false;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bCHEFD_MCSInit = true;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0001Init = true;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0002Init = true;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0003Init = true;
    }
    else if ( m_wndProperties.iComboBoxProperties == 2 )
    {
        directshow.Continue ();
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = false;
    }
    else if ( m_wndProperties.iComboBoxProperties == 3 )
    {
        bool bRet = false;
        bRet = m_wndProperties.GetPropertiesParameter();
        if ( bRet == false ) { return; }
        size_t sizetFileName = strlen ( m_wndProperties.cUSBCamera_DeviceName );
        if ( sizetFileName == 0 ) { return; }
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->lFrameCount = 0;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bCHEFD_MCSInit = true;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0001Init = true;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0002Init = true;
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bOtherAlgorithm0003Init = true;
        usbcamera.MachineRelease();
        usbcamera.Preview ( 
            (void*) (CHEFD_MCSView*) GetActiveFrame()->GetActiveView(),  
            m_wndProperties.cUSBCamera_DeviceName,
            m_bFirstTime
            );
        if ( bRet == false ) { return; }
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = false;
    }
    
}



void CMainFrame::OnButtonPause()
{
	((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->EnableAllRadioButton();

    Sleep(0);
    
    if ( m_wndProperties.iComboBoxProperties == 0 )
    {
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = true;
        actisdk.Pause ();
    }
    else if ( m_wndProperties.iComboBoxProperties == 1 )
    {
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = true;
        isapnvrsdk.Stop_NVRChannel ();
        SAFE_DELETE_ARRAY ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pucMonitorSaveCurrentBitmap );
        SAFE_DELETE_ARRAY ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pucReduceAnalysisImageCurrent1 );
        SAFE_DELETE_ARRAY ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pucReduceAnalysisImageCurrent2);
    }
    else if ( m_wndProperties.iComboBoxProperties == 2 )
    {
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = true;
        directshow.Pause ();
    }
    else if ( m_wndProperties.iComboBoxProperties == 3 )
    {
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = true;
        usbcamera.PreviewPause ();
    }
    
}



void CMainFrame::OnButtonStop()
{
	((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->EnableAllRadioButton();

    Sleep(0);
    
    if ( m_wndProperties.iComboBoxProperties == 0 )
    {
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = true;
        actisdk.Stop ();
        SAFE_DELETE_ARRAY ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pucMonitorSaveCurrentBitmap );
        SAFE_DELETE_ARRAY ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pucReduceAnalysisImageCurrent1 );
        SAFE_DELETE_ARRAY ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pucReduceAnalysisImageCurrent2 );
        SAFE_DELETE(((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->pHEFD_MCS);
        SAFE_DELETE(((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->pOtherAlgorithm0001);
        SAFE_DELETE(((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->pOtherAlgorithm0002);
        SAFE_DELETE(((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->pOtherAlgorithm0003);
    }
    else if ( m_wndProperties.iComboBoxProperties == 1 )
    {
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = true;
        isapnvrsdk.Stop_NVRChannel ();
        SAFE_DELETE_ARRAY ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pucMonitorSaveCurrentBitmap );
        SAFE_DELETE_ARRAY ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pucReduceAnalysisImageCurrent1 );
        SAFE_DELETE_ARRAY ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pucReduceAnalysisImageCurrent2 );
        SAFE_DELETE(((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->pHEFD_MCS);
        SAFE_DELETE(((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->pOtherAlgorithm0001);
        SAFE_DELETE(((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->pOtherAlgorithm0002);
        SAFE_DELETE(((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->pOtherAlgorithm0003);
    }
    else if ( m_wndProperties.iComboBoxProperties == 2 )
    {
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = true;
        directshow.Pause();
    }
    else if ( m_wndProperties.iComboBoxProperties == 3 )
    {
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = true;
        usbcamera.PreviewStop();
        usbcamera.MachineRelease();
        SAFE_DELETE_ARRAY ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pucMonitorSaveCurrentBitmap );
        SAFE_DELETE_ARRAY ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pucReduceAnalysisImageCurrent1 );
        SAFE_DELETE_ARRAY ( ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->pucReduceAnalysisImageCurrent2 );
        SAFE_DELETE(((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->pHEFD_MCS);
        SAFE_DELETE(((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->pOtherAlgorithm0001);
        SAFE_DELETE(((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->pOtherAlgorithm0002);
        SAFE_DELETE(((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->pOtherAlgorithm0003);
    }
}



void CMainFrame::OnButtonStep()
{
	((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->EnableAllRadioButton();

    Sleep(0);
    
    if ( m_wndProperties.iComboBoxProperties == 0 )
    {
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = false;
        actisdk.Pause ();
    }
    else if ( m_wndProperties.iComboBoxProperties == 1 )
    {

    }
    else if ( m_wndProperties.iComboBoxProperties == 2 )
    {
        ( (CHEFD_MCSView*) GetActiveFrame()->GetActiveView() )->bStopFlag = false;
        directshow.Step ();
    }
}



void CMainFrame::OnUpdateCheckRepeat(CCmdUI *pCmdUI)
{
    Sleep(0);

    if ( m_bVideoDisplayRepeat == TRUE )
    {
        pCmdUI->SetCheck(TRUE);
    }
    else if ( m_bVideoDisplayRepeat == FALSE )
    {
        pCmdUI->SetCheck(FALSE);
    }
}



void CMainFrame::OnCheckRepeat()
{
	((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->EnableAllRadioButton();

    Sleep(0);

    if ( m_bVideoDisplayRepeat == TRUE )
    {
        m_bVideoDisplayRepeat = FALSE;
    }
    else if ( m_bVideoDisplayRepeat == FALSE )
    {
        m_bVideoDisplayRepeat = TRUE;
    }
}


void CMainFrame::OncomboRate()
{
    Sleep(0);
    
    if ( m_wndProperties.iComboBoxProperties == 0 )
    {
        CMFCRibbonComboBox* pComboBoxRate = DYNAMIC_DOWNCAST ( CMFCRibbonComboBox, m_wndRibbonBar.FindByID(ID_comboRate) );
        long lSelect = pComboBoxRate->GetCurSel();
        if ( lSelect == 0 )
        {
            actisdk.Rate ( 0.5f );
        }
        else if ( lSelect == 1 )
        {
            actisdk.Rate ( 1.0f );
        }
        else if ( lSelect == 2 )
        {
            actisdk.Rate ( 2.0f );
        }
        else if ( lSelect == 3 )
        {
            actisdk.Rate ( 4.0f );
        }
        else if ( lSelect == 4 )
        {
            actisdk.Rate ( 8.0f );
        }
    }
    else if ( m_wndProperties.iComboBoxProperties == 1 )
    {

    }
    else if ( m_wndProperties.iComboBoxProperties == 2 )
    {

    }
    
}


void CMainFrame::OnBottonBackwards()
{
	((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->EnableAllRadioButton();

    Sleep(0);
    
    if ( m_wndProperties.iComboBoxProperties == 0 )
    {
        actisdk.Direction ( false );
    }
    else if ( m_wndProperties.iComboBoxProperties == 1 )
    {

    }
    else if ( m_wndProperties.iComboBoxProperties == 2 )
    {

    }
    
}


void CMainFrame::OnButtonForwards()
{
	((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->EnableAllRadioButton();

    Sleep(0);
    
    if ( m_wndProperties.iComboBoxProperties == 0 )
    {
        actisdk.Direction ( true );
    }
    else if ( m_wndProperties.iComboBoxProperties == 1 )
    {

    }
    else if ( m_wndProperties.iComboBoxProperties == 2 )
    {

    }
    
}


void CMainFrame::OnButtonNextFrame()
{
	((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->EnableAllRadioButton();

    Sleep(0);
    
    if ( m_wndProperties.iComboBoxProperties == 0 )
    {
        actisdk.NextFrame();
    }
    else if ( m_wndProperties.iComboBoxProperties == 1 )
    {

    }
    else if ( m_wndProperties.iComboBoxProperties == 2 )
    {
        
    }
    
}


void CMainFrame::OnButtonPreviousFrame()
{
	((CHEFD_MCSView*)GetActiveFrame()->GetActiveView())->EnableAllRadioButton();

    Sleep(0);
    
    if ( m_wndProperties.iComboBoxProperties == 0 )
    {
        actisdk.PreviousFrame();
    }
    else if ( m_wndProperties.iComboBoxProperties == 1 )
    {

    }
    else if ( m_wndProperties.iComboBoxProperties == 2 )
    {
        directshow.PreviousFrame();
    }
    
}

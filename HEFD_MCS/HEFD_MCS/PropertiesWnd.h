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

#pragma once

class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPropertiesWnd : public CDockablePane
{
// Construction
public:
	CPropertiesWnd();

	void AdjustLayout();

// Attributes
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}

protected:
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CPropertiesToolBar m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;

// Implementation
public:
	virtual ~CPropertiesWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
    //////////////////////////////////////////////////////////////////////////
    afx_msg void OnComboBoxProperties();
    //////////////////////////////////////////////////////////////////////////

	DECLARE_MESSAGE_MAP()

    void InitPropList();
    //////////////////////////////////////////////////////////////////////////
    void InitPropListACTiSDK10000();
    void InitPropListMovieFileDirectShow();
    void InitPropListUSBCameraDirectShow();
    void InitPropListiSAPNVR();

    //////////////////////////////////////////////////////////////////////////
	void SetPropListFont();

public:
    //////////////////////////////////////////////////////////////////////////
    int iComboBoxProperties;
    bool GetPropertiesParameter();
    char cACTi_Type[256];
    int iACTi_IPv41;
    int iACTi_IPv42;
    int iACTi_IPv43;
    int iACTi_IPv44;
    char cACTi_UserID[64];
    char cACTi_Password[64];
    char cACTi_FileName[256];
    char cDirectShow_FileName[256];
    char cUSBCamera_DeviceName[256];
    int iiSAPNVR_IPv41;
    int iiSAPNVR_IPv42;
    int iiSAPNVR_IPv43;
    int iiSAPNVR_IPv44;
    int iiSAPNVR_IPv4Port;
    char ciSAPNVR_UserID[256];
    char ciSAPNVR_Password[256];
    char ciSAPNVR_Channel[256];
    //////////////////////////////////////////////////////////////////////////
};

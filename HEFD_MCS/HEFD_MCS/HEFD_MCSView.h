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

// HEFD_MCSView.h : interface of the CHEFD_MCSView class
//

#pragma once

#include "resource.h"
#include "afxwin.h"


#include "..\\..\\HEFD_MCSAlgorithm\\IHEFD_MCS.h"
#include "..\\..\\OtherAlgorithm0001\\IOtherAlgorithm0001.h"
#include "..\\..\\OtherAlgorithm0002\\IOtherAlgorithm0002.h"
#include "..\\..\\OtherAlgorithm0003\\IOtherAlgorithm0003.h"
#include "CommonStructure.h"


class CHEFD_MCSView : public CFormView
{
protected: // create from serialization only
	CHEFD_MCSView();
	DECLARE_DYNCREATE(CHEFD_MCSView)

public:
	enum{ IDD = IDD_HEFD_MCS_FORM };

// Attributes
public:
	CHEFD_MCSDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CHEFD_MCSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

protected:
	//afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
    
    LARGE_INTEGER litmp; 
    LONGLONG QPart1,QPart2;
    double dfMinus, dfFreq, dfTim; 
    
    CStatic m_pictureMonitor;
    CStatic m_pictureAnalysis;
    CStatic m_pictureTemp;
    CEdit m_editFileNameSaveBitmap;
    CButton m_checkAutoSavePicture;
    CEdit m_editResize;

    bool bStopFlag;
    int iChoiceMode;
    bool m_bSavePicture;
    long lFrameCount;
    long m_lMSPCount;
    HANDLE m_handleACTiSDK;

    CRect crectBox;
    CPoint cpointDrawLineStartXY;
    CPoint cpointDrawLineEndXY;

    unsigned char* pucMonitorSaveCurrentBitmap;
    unsigned char* pucReduceAnalysisImageCurrent1;
    unsigned char* pucReduceAnalysisImageCurrent2;

    CHEFD_MCS* pHEFD_MCS;
    bool bCHEFD_MCSInit;
    stInitParameter stCHEFD_MCSInit;
    stOutputData stCHEFD_MCSOutput;
    double dbReduceDivisor;
    long lCHEFD_MCSID;

    COtherAlgorithm0001* pOtherAlgorithm0001;
    bool bOtherAlgorithm0001Init;
    stInitParameter stOtherAlgorithm0001Init;
    stOutputData stOtherAlgorithm0001Output;

    COtherAlgorithm0002* pOtherAlgorithm0002;
    bool bOtherAlgorithm0002Init;
    stInitParameter stOtherAlgorithm0002Init;
    stOutputData stOtherAlgorithm0002Output;

    COtherAlgorithm0003* pOtherAlgorithm0003;
    bool bOtherAlgorithm0003Init;
    stInitParameter stOtherAlgorithm0003Init;
    stOutputData stOtherAlgorithm0003Output;

    bool SaveBitmapToFile (
        CString csFileName,
        long lCount,
        unsigned char* pInImage1,
        int iInWidth,
        int iInHeight,
        int iInBitDepth,
        int iInBMPSX,
        int iInBMPSY,
        int iInBMPEX,
        int iInBMPEY,
        int iInBMPWidth,
        int iInBMPHeight
        );
    
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnDestroy();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnBnClickedButtonSavePicture();
    afx_msg void OnBnClickedButtonCountZero();
    afx_msg void OnBnClickedradiomakefeature();
    afx_msg void OnBnClickedRadioOtherAlgorithm0001();
    afx_msg void OnBnClickedRadioOtherAlgorithm0002();
    afx_msg void OnBnClickedRadioCHEFDMCS2();
    afx_msg void OnBnClickedRadioOtherAlgorithm0003();
};

#ifndef _DEBUG  // debug version in HEFD_MCSView.cpp
inline CHEFD_MCSDoc* CHEFD_MCSView::GetDocument() const
   { return reinterpret_cast<CHEFD_MCSDoc*>(m_pDocument); }
#endif
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

// HEFD_MCSView.cpp : implementation of the CHEFD_MCSView class
//
#pragma once

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HEFD_MCS.h"
#endif

#include "HEFD_MCSDoc.h"
#include "HEFD_MCSView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include "MainFrm.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
using namespace std;


// CHEFD_MCSView

IMPLEMENT_DYNCREATE(CHEFD_MCSView, CFormView)

BEGIN_MESSAGE_MAP(CHEFD_MCSView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
    ON_WM_LBUTTONDOWN()
    ON_WM_SETFOCUS()
    ON_WM_MOUSEMOVE()
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_buttonSavePicture, &CHEFD_MCSView::OnBnClickedButtonSavePicture)
    ON_BN_CLICKED(IDC_buttonCountZero, &CHEFD_MCSView::OnBnClickedButtonCountZero)
    ON_BN_CLICKED(IDC_radioCHEFD_MCS, &CHEFD_MCSView::OnBnClickedradiomakefeature)
    ON_BN_CLICKED(IDC_radioOtherAlgorithm0001, &CHEFD_MCSView::OnBnClickedRadioOtherAlgorithm0001)
    ON_BN_CLICKED(IDC_radioOtherAlgorithm0002, &CHEFD_MCSView::OnBnClickedRadioOtherAlgorithm0002)
    ON_BN_CLICKED(IDC_radioOtherAlgorithm0003, &CHEFD_MCSView::OnBnClickedRadioOtherAlgorithm0003)
    ON_BN_CLICKED(IDC_radioCHEFD_MCS2, &CHEFD_MCSView::OnBnClickedRadioCHEFDMCS2)
END_MESSAGE_MAP()

// CHEFD_MCSView construction/destruction

CHEFD_MCSView::CHEFD_MCSView()
	: CFormView(CHEFD_MCSView::IDD)
{
	// TODO: add construction code here
    
    bStopFlag = true;
    
    iChoiceMode = 1; 

    pucMonitorSaveCurrentBitmap = NULL;
    
    dbReduceDivisor = 1;
    
    pucReduceAnalysisImageCurrent1 = NULL;

    pucReduceAnalysisImageCurrent2 = NULL;

    cpointDrawLineStartXY.SetPoint ( 0, 0 );
    
    cpointDrawLineEndXY.SetPoint ( 0, 0 );
    
    lCHEFD_MCSID = 0;

	pHEFD_MCS = new CHEFD_MCS();
	bCHEFD_MCSInit = true;
	memset(&stCHEFD_MCSInit, 0x00, sizeof(stInitParameter));
	memset(&stCHEFD_MCSOutput, 0x00, sizeof(stOutputData));

    pOtherAlgorithm0001 = new COtherAlgorithm0001();
    bOtherAlgorithm0001Init = true;
    memset ( &stOtherAlgorithm0001Init, 0x00, sizeof(stInitParameter) );
    memset ( &stOtherAlgorithm0001Output, 0x00, sizeof(stOutputData) );

    pOtherAlgorithm0002 = new COtherAlgorithm0002();
    bOtherAlgorithm0002Init = true;
    memset ( &stOtherAlgorithm0002Init, 0x00, sizeof(stInitParameter) );
    memset ( &stOtherAlgorithm0002Output, 0x00, sizeof(stOutputData) );

    pOtherAlgorithm0003 = new COtherAlgorithm0003();
    bOtherAlgorithm0003Init = true;
    memset(&stOtherAlgorithm0003Init, 0x00, sizeof(stInitParameter));
    memset(&stOtherAlgorithm0003Output, 0x00, sizeof(stOutputData));

}

CHEFD_MCSView::~CHEFD_MCSView()
{
    SAFE_DELETE_ARRAY ( pucMonitorSaveCurrentBitmap );
    SAFE_DELETE_ARRAY ( pucReduceAnalysisImageCurrent1 );
    SAFE_DELETE_ARRAY ( pucReduceAnalysisImageCurrent2 );
    SAFE_DELETE ( pHEFD_MCS );
    SAFE_DELETE ( pOtherAlgorithm0001 );
    SAFE_DELETE ( pOtherAlgorithm0002 );
    SAFE_DELETE ( pOtherAlgorithm0003 );
}

void CHEFD_MCSView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_pictureMonitor, m_pictureMonitor);
    DDX_Control(pDX, IDC_pictureAnalysis, m_pictureAnalysis);
    DDX_Control(pDX, IDC_pictureTemp, m_pictureTemp);
    DDX_Control(pDX, IDC_editFileNameSaveBitmap, m_editFileNameSaveBitmap);
    DDX_Control(pDX, IDC_checkAutoSavePicture, m_checkAutoSavePicture);
    DDX_Control(pDX, IDC_editResize, m_editResize);
}

BOOL CHEFD_MCSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CHEFD_MCSView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();
    
    if ( iChoiceMode == 1 )
    {
        CheckRadioButton ( IDC_radioCHEFD_MCS, IDC_radioCHEFD_MCS2, IDC_radioCHEFD_MCS );
        GetDlgItem ( IDC_radioCHEFD_MCS )->SetFocus();
    }
    else if ( iChoiceMode == 2 )
    {
        CheckRadioButton ( IDC_radioCHEFD_MCS, IDC_radioCHEFD_MCS2, IDC_radioOtherAlgorithm0001 );
        GetDlgItem ( IDC_radioOtherAlgorithm0001 )->SetFocus();
    }
    else if ( iChoiceMode == 3 )
    {
        CheckRadioButton ( IDC_radioCHEFD_MCS, IDC_radioCHEFD_MCS2, IDC_radioOtherAlgorithm0002 );
        GetDlgItem ( IDC_radioOtherAlgorithm0002 )->SetFocus();
    }
    else if ( iChoiceMode == 4 )
    {
        CheckRadioButton ( IDC_radioCHEFD_MCS, IDC_radioCHEFD_MCS2, IDC_radioOtherAlgorithm0003 );
        GetDlgItem(IDC_radioOtherAlgorithm0003)->SetFocus();
    }
    else if ( iChoiceMode == 11 )
    {
        CheckRadioButton ( IDC_radioCHEFD_MCS, IDC_radioCHEFD_MCS2, IDC_radioCHEFD_MCS2 );
        GetDlgItem ( IDC_radioCHEFD_MCS2 )->SetFocus();
    }
    m_editResize.SetWindowTextA ( _T("1.0") );
    cpointDrawLineStartXY.SetPoint ( 0, 0 );
    cpointDrawLineEndXY.SetPoint ( 0, 0 );
    
    lFrameCount = 0;
    
    m_bSavePicture = false;
    
    m_lMSPCount = 0;
    
    time_t now = time ( 0 );
    struct tm  tstruct;
    CString csFileName;
    tstruct = *localtime(&now);
    csFileName.Format ( 
        "%04d_%02d%02d_", 
        tstruct.tm_year + 1900, 
        tstruct.tm_mon + 1,
        tstruct.tm_mday
        );
    m_editFileNameSaveBitmap.SetWindowTextA ( csFileName.GetBuffer() );
    
}

void CHEFD_MCSView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHEFD_MCSView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHEFD_MCSView diagnostics

#ifdef _DEBUG
void CHEFD_MCSView::AssertValid() const
{
	CFormView::AssertValid();
}

void CHEFD_MCSView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CHEFD_MCSDoc* CHEFD_MCSView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHEFD_MCSDoc)));
	return (CHEFD_MCSDoc*)m_pDocument;
}
#endif //_DEBUG


// CHEFD_MCSView message handlers


void CHEFD_MCSView::OnBnClickedradiomakefeature()
{
    // TODO: Add your control notification handler code here
    iChoiceMode = 1;
    CheckRadioButton(IDC_radioCHEFD_MCS, IDC_radioCHEFD_MCS2, IDC_radioCHEFD_MCS);
    GetDlgItem ( IDC_radioCHEFD_MCS )->SetFocus();
}


void CHEFD_MCSView::OnBnClickedRadioOtherAlgorithm0001()
{
    // TODO: Add your control notification handler code here
    iChoiceMode = 2;
    CheckRadioButton(IDC_radioCHEFD_MCS, IDC_radioCHEFD_MCS2, IDC_radioOtherAlgorithm0001);
    GetDlgItem ( IDC_radioOtherAlgorithm0001 )->SetFocus();
}


void CHEFD_MCSView::OnBnClickedRadioOtherAlgorithm0002()
{
    // TODO: Add your control notification handler code here
    iChoiceMode = 3;
    CheckRadioButton(IDC_radioCHEFD_MCS, IDC_radioCHEFD_MCS2, IDC_radioOtherAlgorithm0002);
    GetDlgItem ( IDC_radioOtherAlgorithm0002 )->SetFocus();
}

void CHEFD_MCSView::OnBnClickedRadioOtherAlgorithm0003()
{
    // TODO: Add your control notification handler code here
    iChoiceMode = 4;
    CheckRadioButton(IDC_radioCHEFD_MCS, IDC_radioCHEFD_MCS2, IDC_radioOtherAlgorithm0003);
    GetDlgItem ( IDC_radioOtherAlgorithm0003 )->SetFocus();
}

void CHEFD_MCSView::OnBnClickedRadioCHEFDMCS2()
{
    // TODO: Add your control notification handler code here
    iChoiceMode = 11;
    CheckRadioButton(IDC_radioCHEFD_MCS, IDC_radioCHEFD_MCS2, IDC_radioCHEFD_MCS2);
    GetDlgItem ( IDC_radioCHEFD_MCS2 )->SetFocus();
}


void CHEFD_MCSView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    
    CFormView::OnLButtonDown(nFlags, point);
}


void CHEFD_MCSView::OnSetFocus(CWnd* pOldWnd)
{
    CFormView::OnSetFocus(pOldWnd);
}


void CHEFD_MCSView::OnMouseMove(UINT nFlags, CPoint point)
{
    CFormView::OnMouseMove(nFlags, point);
}


void CHEFD_MCSView::OnDestroy()
{
    this->bStopFlag = true;
    Sleep(500);

    CFormView::OnDestroy();
}


bool CHEFD_MCSView::
    SaveBitmapToFile (
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
    )
{
    BITMAPFILEHEADER* bmpFH = new BITMAPFILEHEADER;
    BITMAPINFOHEADER* bmpIH = new BITMAPINFOHEADER;

    bmpFH->bfType = 0x4d42;
    bmpFH->bfReserved1 = 0;
    bmpFH->bfReserved2 = 0;
    bmpFH->bfSize = (DWORD) sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + ( iInBMPWidth * iInBMPHeight * 4 );
    bmpFH->bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    bmpIH->biSize = sizeof(BITMAPINFOHEADER);
    bmpIH->biWidth = iInBMPWidth;
    bmpIH->biHeight = -(iInBMPHeight);
    bmpIH->biPlanes = 1;
    bmpIH->biBitCount = 32;
    bmpIH->biCompression = BI_RGB;
    bmpIH->biSizeImage = ABS ( iInBMPWidth * iInBMPHeight * 4 );
    bmpIH->biXPelsPerMeter = 0;
    bmpIH->biYPelsPerMeter = 0;
    bmpIH->biClrUsed = 0;
    bmpIH->biClrImportant = 0;
    
    CString strAppName;
    GetModuleFileName(NULL, strAppName.GetBuffer(_MAX_PATH), _MAX_PATH);
    strAppName.ReleaseBuffer();
    int nPos = strAppName.ReverseFind('\\');
    strAppName = strAppName.Left(nPos + 1);
    char *FPath = new char[1024];
    for ( int iI = 0; iI < nPos + 1; iI++ )
    {
        *( FPath + iI ) = (char) strAppName[iI];
    }
    *( FPath + nPos + 1 ) = '\0';

    QueryPerformanceCounter(&litmp);
    QPart2 = litmp.QuadPart;
    dfMinus = (double)(QPart2-QPart1);
    if ( dfMinus < 0 )
    {
        dfMinus = 0;
    }
    dfTim = int ( dfMinus / dfFreq );
    char cTimeClock [50];
    ZeroMemory ( cTimeClock, 50 * sizeof(char) );
    sprintf_s( cTimeClock, "%d\n", int ( dfTim ) );

    char crFName[1000];
    memset ( crFName, 0x00, 1000 );
    sprintf_s ( crFName, "%s\%s%03d-%08d.BMP", FPath, csFileName.GetBuffer(), lCount, int ( dfTim ) );
    SAFE_DELETE_ARRAY ( FPath );

    BYTE* pBMPBuffer = new BYTE [ iInBMPWidth * iInBMPHeight * 4 ];
    memset ( pBMPBuffer, 0x00, iInBMPWidth * iInBMPHeight * 4 );

    long lYY = 0;
    long lXX = 0;
    for ( long lY = iInBMPSY; lY < iInBMPEY; lY++ )
    {
        for ( long lX = iInBMPSX; lX < iInBMPEX; lX++ )
        {
            long lIndexSrc = ( lY * iInWidth * iInBitDepth ) + ( lX * iInBitDepth );
            long lIndexDst = ( lYY * iInBMPWidth * 4 ) + ( lXX * 4 );
            pBMPBuffer [ lIndexDst + 2 ] = pInImage1 [ lIndexSrc + 2 ];
            pBMPBuffer [ lIndexDst + 1 ] = pInImage1 [ lIndexSrc + 1 ];
            pBMPBuffer [ lIndexDst + 0 ] = pInImage1 [ lIndexSrc + 0 ];
            lXX++;
        }
        lXX = 0;
        lYY++;
    }

    FILE *pBMPFile = fopen( crFName, "wb" );
    if ( pBMPFile )
    {
        fwrite ( bmpFH, sizeof(BITMAPFILEHEADER), 1, pBMPFile );
        fwrite ( bmpIH, sizeof(BITMAPINFOHEADER), 1, pBMPFile );
        fwrite ( pBMPBuffer, ( iInBMPWidth * iInBMPHeight * 4 ), 1, pBMPFile );
        fflush ( pBMPFile );
        fclose ( pBMPFile );
    }

    SAFE_DELETE ( bmpIH );
    SAFE_DELETE ( bmpFH );
    SAFE_DELETE_ARRAY ( pBMPBuffer );
    return true;
}


void CHEFD_MCSView::OnBnClickedButtonSavePicture()
{
    m_bSavePicture = true;
}


void CHEFD_MCSView::OnBnClickedButtonCountZero()
{
    m_lMSPCount = 0;
}


void CHEFD_MCSView::DisableAllRadioButton()
{
	GetDlgItem(IDC_radioCHEFD_MCS)->EnableWindow(FALSE);
	GetDlgItem(IDC_radioOtherAlgorithm0001)->EnableWindow(FALSE);
	GetDlgItem(IDC_radioOtherAlgorithm0002)->EnableWindow(FALSE);
	GetDlgItem(IDC_radioOtherAlgorithm0003)->EnableWindow(FALSE);
	GetDlgItem(IDC_radioCHEFD_MCS2)->EnableWindow(FALSE);
}


void CHEFD_MCSView::EnableAllRadioButton()
{
	GetDlgItem(IDC_radioCHEFD_MCS)->EnableWindow(TRUE);
	GetDlgItem(IDC_radioOtherAlgorithm0001)->EnableWindow(TRUE);
	GetDlgItem(IDC_radioOtherAlgorithm0002)->EnableWindow(TRUE);
	GetDlgItem(IDC_radioOtherAlgorithm0003)->EnableWindow(TRUE);
	GetDlgItem(IDC_radioCHEFD_MCS2)->EnableWindow(TRUE);
}
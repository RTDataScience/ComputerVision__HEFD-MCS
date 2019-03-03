#pragma once

#include "stdafx.h"
#include "HEFD_MCSDoc.h"
#include "HEFD_MCSView.h"


void CALLBACK ACTiSDKControl_ImageCallback ( DWORD UserParam, BYTE* buf, DWORD len, DWORD dwWidth, DWORD dwHeight )
{
    if ( UserParam == NULL || buf == NULL || len <= 0 || 
        dwWidth <= 0 || dwHeight <= 0 || dwWidth >= 2560 || dwHeight >= 2048 )
    {
        return;
    }
    CHEFD_MCSView* pView = (CHEFD_MCSView*) (__int64) UserParam; 
    if ( pView->bStopFlag == true ) 
    { 
        return; 
    }
    // Time
    DWORD dwCurrentTime = NULL;
    time_t timet;
    struct tm *newtime;
    char cTime [ 1024 ];
    memset ( cTime, 0x00, 1024 * sizeof(char) );
    dwCurrentTime = KGetCurrentTime ( m_handleACTiSDK );
    timet = (time_t) dwCurrentTime;
    newtime = gmtime((time_t *)&timet);
    sprintf_s(cTime, "%04d/%02d/%02d %02d:%02d:%02d\n", newtime->tm_year + 1900, newtime->tm_mon + 1, newtime->tm_mday, newtime->tm_hour, newtime->tm_min, newtime->tm_sec);
    OutputDebugStringA(cTime);

    int iReduceDivisor = int ( pView->dbReduceDivisor );
    if (iReduceDivisor <= 1 || iReduceDivisor >= min(dwWidth, dwHeight))
    {
        iReduceDivisor = 1;
    }
    int iBitDepth = ( (LPBITMAPINFOHEADER) buf )->biBitCount / 8;
    int iOriginLength = dwWidth * dwHeight * iBitDepth;
    int iReduceWidth = dwWidth / iReduceDivisor;
    int iReduceHeight = dwHeight / iReduceDivisor;
    int iReduceLength = iReduceWidth * iReduceHeight * iBitDepth;
    double dbTimeDiff = 0.0f;

    if ( pView->bStopFlag == false )
    {
        if ( pView->pucMonitorSaveCurrentBitmap == NULL )
        {
            pView->pucMonitorSaveCurrentBitmap = new unsigned char [ len ];
            memset ( pView->pucMonitorSaveCurrentBitmap, 0x00, len );
        }

        if (
			pView->iChoiceMode == 1 ||
			pView->iChoiceMode == 2 ||
			pView->iChoiceMode == 3 ||
            pView->iChoiceMode == 4 ||
            pView->iChoiceMode == 11
			)
        {
            if ( pView->pucReduceAnalysisImageCurrent1 == NULL )
            {
                pView->pucReduceAnalysisImageCurrent1 = new unsigned char [ iReduceLength + sizeof(BITMAPINFOHEADER) ];
                memset ( pView->pucReduceAnalysisImageCurrent1, 0x00, iReduceLength + sizeof(BITMAPINFOHEADER) );
            }
            if (pView->pucReduceAnalysisImageCurrent2 == NULL)
            {
                pView->pucReduceAnalysisImageCurrent2 = new unsigned char[iReduceLength + sizeof(BITMAPINFOHEADER)];
                memset(pView->pucReduceAnalysisImageCurrent2, 0x00, iReduceLength + sizeof(BITMAPINFOHEADER));
            }
        }
    }

    // Lai Linwen, Lai Taiyu, "A High Efficiency Flame Detection Mobile Camera System (HEFD-MCS)"
    if (
        pView->iChoiceMode == 1 ||
        pView->iChoiceMode == 11
        )
    {
        pView->stCHEFD_MCSInit.stRectInROI01.lSX = 1;
        pView->stCHEFD_MCSInit.stRectInROI01.lSY = 1;
        pView->stCHEFD_MCSInit.stRectInROI01.lEX = dwWidth;
        pView->stCHEFD_MCSInit.stRectInROI01.lEY = dwHeight;
        pView->stCHEFD_MCSInit.stRectInROI01.lWidth = pView->stCHEFD_MCSInit.stRectInROI01.lEX - pView->stCHEFD_MCSInit.stRectInROI01.lSX + 1;
        pView->stCHEFD_MCSInit.stRectInROI01.lHeight = pView->stCHEFD_MCSInit.stRectInROI01.lEY - pView->stCHEFD_MCSInit.stRectInROI01.lSY + 1;

        double dbHEFD_MCSTime = 0.0f;

        bool bRet = false;

        bRet = pView->pHEFD_MCS->AlgInit ( 
            &pView->bCHEFD_MCSInit,  
            &pView->stCHEFD_MCSInit, 
            NULL
            );
        if ( bRet == false ) { return; }

        bRet = pView->pHEFD_MCS->AlgInput (
            buf + sizeof(BITMAPINFOHEADER),      
            dwWidth,                             
            dwHeight,                            
            iBitDepth,                           
            NULL,
            NULL
            );
        if ( bRet == false ) { return; }

        bRet = pView->pHEFD_MCS->AlgProcessing (
            NULL,
            NULL
            );
        if ( bRet == false ) { return; }
        
        bRet = pView->pHEFD_MCS->AlgOutput (
			pView->pucReduceAnalysisImageCurrent1 + sizeof(BITMAPINFOHEADER),
			pView->pucReduceAnalysisImageCurrent2 + sizeof(BITMAPINFOHEADER),
			&dbHEFD_MCSTime,
            &pView->stCHEFD_MCSOutput,                                      
            NULL
            );
        if ( bRet == false ) { return; }
    }
    // Other Algorithm 0001
    else if (pView->iChoiceMode == 2)
    {
        pView->stOtherAlgorithm0001Init.stRectInROI01.lSX = 1;
        pView->stOtherAlgorithm0001Init.stRectInROI01.lSY = 1;
        pView->stOtherAlgorithm0001Init.stRectInROI01.lEX = dwWidth;
        pView->stOtherAlgorithm0001Init.stRectInROI01.lEY = dwHeight;
        pView->stOtherAlgorithm0001Init.stRectInROI01.lWidth = pView->stOtherAlgorithm0001Init.stRectInROI01.lEX - pView->stOtherAlgorithm0001Init.stRectInROI01.lSX + 1;
        pView->stOtherAlgorithm0001Init.stRectInROI01.lHeight = pView->stOtherAlgorithm0001Init.stRectInROI01.lEY - pView->stOtherAlgorithm0001Init.stRectInROI01.lSY + 1;

        pView->stOtherAlgorithm0001Output.bOutTrigger01 = false;

        double dbPeopleCounting = 0.0f;

        bool bRet = false;

        bRet = pView->pOtherAlgorithm0001->AlgInit ( 
            &pView->bOtherAlgorithm0001Init, 
            &pView->stOtherAlgorithm0001Init,
            NULL
            );
        if ( bRet == false ) { return; }

        bRet = pView->pOtherAlgorithm0001->AlgInput (
            buf + sizeof(BITMAPINFOHEADER),    
            dwWidth,                           
            dwHeight,                          
            iBitDepth,                         
            NULL,
            (void*) &timet
            );
        if ( bRet == false ) { return; }

        bRet = pView->pOtherAlgorithm0001->AlgProcessing (
            NULL,
            NULL
            );
        if ( bRet == false ) { return; }

        bRet = pView->pOtherAlgorithm0001->AlgOutput (
            pView->pucReduceAnalysisImageCurrent1 + sizeof(BITMAPINFOHEADER),  
            pView->pucReduceAnalysisImageCurrent2 + sizeof(BITMAPINFOHEADER),
            &dbPeopleCounting,
            &pView->stOtherAlgorithm0001Output,                               
            NULL
            );
        if ( bRet == false ) { return; }

        if ( pView->stOtherAlgorithm0001Output.bOutTrigger01 == true )
        {
            if ( pView->m_checkAutoSavePicture.GetCheck() == BST_CHECKED )
            {
                CString csFileNameSaveBitmap = _T("");
                pView->m_editFileNameSaveBitmap.GetWindowTextA ( csFileNameSaveBitmap );
                csFileNameSaveBitmap = csFileNameSaveBitmap + _T("RealTime_");
                pView->m_lMSPCount++;
                pView->SaveBitmapToFile (
                    csFileNameSaveBitmap.GetBuffer(),
                    pView->m_lMSPCount,
                    buf + sizeof(BITMAPINFOHEADER),
                    dwWidth,
                    dwHeight,
                    ABS ( ( (LPBITMAPINFO) buf )->bmiHeader.biBitCount / 8 ),
                    0,
                    0,
                    dwWidth - 1,
                    dwHeight - 1,
                    dwWidth,
                    dwHeight
                    );
                csFileNameSaveBitmap = _T("");
                pView->m_editFileNameSaveBitmap.GetWindowTextA ( csFileNameSaveBitmap );
                csFileNameSaveBitmap = csFileNameSaveBitmap + _T("Analysis_");
                pView->SaveBitmapToFile (
                    csFileNameSaveBitmap.GetBuffer(),
                    pView->m_lMSPCount,
                    pView->pucReduceAnalysisImageCurrent1 + sizeof(BITMAPINFOHEADER),
                    iReduceWidth, 
                    iReduceHeight,
                    ABS ( ( (LPBITMAPINFO) pView->pucReduceAnalysisImageCurrent1 )->bmiHeader.biBitCount / 8 ),
                    0,
                    0,
                    iReduceWidth - 1,
                    iReduceHeight - 1,
                    iReduceWidth,
                    iReduceHeight
                    );
            }
        }
    }
	// Other Algorithm 0002
    else if (pView->iChoiceMode == 3)
    {
        pView->stOtherAlgorithm0002Init.stRectInROI01.lSX = 1;
        pView->stOtherAlgorithm0002Init.stRectInROI01.lSY = 1;
        pView->stOtherAlgorithm0002Init.stRectInROI01.lEX = dwWidth;
        pView->stOtherAlgorithm0002Init.stRectInROI01.lEY = dwHeight;
        pView->stOtherAlgorithm0002Init.stRectInROI01.lWidth = pView->stOtherAlgorithm0002Init.stRectInROI01.lEX - pView->stOtherAlgorithm0002Init.stRectInROI01.lSX + 1;
        pView->stOtherAlgorithm0002Init.stRectInROI01.lHeight = pView->stOtherAlgorithm0002Init.stRectInROI01.lEY - pView->stOtherAlgorithm0002Init.stRectInROI01.lSY + 1;

        pView->stOtherAlgorithm0002Output.bOutTrigger01 = false;

        double dbOtherAlgorithm0002 = 0.0f;

        bool bRet = false;

        bRet = pView->pOtherAlgorithm0002->AlgInit(
            &pView->bOtherAlgorithm0002Init,
            &pView->stOtherAlgorithm0002Init,
            NULL
        );
        if (bRet == false) { return; }

        bRet = pView->pOtherAlgorithm0002->AlgInput(
            buf + sizeof(BITMAPINFOHEADER),
            dwWidth,
            dwHeight,
            iBitDepth,
            NULL,
            NULL
        );
        if (bRet == false) { return; }

        bRet = pView->pOtherAlgorithm0002->AlgProcessing(
            NULL,
            NULL
        );
        if (bRet == false) { return; }

        bRet = pView->pOtherAlgorithm0002->AlgOutput(
            pView->pucReduceAnalysisImageCurrent1 + sizeof(BITMAPINFOHEADER),
            pView->pucReduceAnalysisImageCurrent2 + sizeof(BITMAPINFOHEADER),
            &dbOtherAlgorithm0002,
            &pView->stOtherAlgorithm0002Output,
            NULL
        );
        if (bRet == false) { return; }

        if (pView->stOtherAlgorithm0002Output.bOutTrigger01 == true)
        {
            if (pView->m_checkAutoSavePicture.GetCheck() == BST_CHECKED)
            {
                CString csFileNameSaveBitmap = _T("");
                pView->m_editFileNameSaveBitmap.GetWindowTextA(csFileNameSaveBitmap);
                csFileNameSaveBitmap = csFileNameSaveBitmap + _T("RealTime_");
                pView->m_lMSPCount++;
                pView->SaveBitmapToFile(
                    csFileNameSaveBitmap.GetBuffer(),
                    pView->m_lMSPCount,
                    buf + sizeof(BITMAPINFOHEADER),
                    dwWidth,
                    dwHeight,
                    ABS(((LPBITMAPINFO)buf)->bmiHeader.biBitCount / 8),
                    0,
                    0,
                    dwWidth - 1,
                    dwHeight - 1,
                    dwWidth,
                    dwHeight
                );
                csFileNameSaveBitmap = _T("");
                pView->m_editFileNameSaveBitmap.GetWindowTextA(csFileNameSaveBitmap);
                csFileNameSaveBitmap = csFileNameSaveBitmap + _T("Analysis_");
                pView->SaveBitmapToFile(
                    csFileNameSaveBitmap.GetBuffer(),
                    pView->m_lMSPCount,
                    pView->pucReduceAnalysisImageCurrent1 + sizeof(BITMAPINFOHEADER),
                    iReduceWidth,
                    iReduceHeight,
                    ABS(((LPBITMAPINFO)pView->pucReduceAnalysisImageCurrent1)->bmiHeader.biBitCount / 8),
                    0,
                    0,
                    iReduceWidth - 1,
                    iReduceHeight - 1,
                    iReduceWidth,
                    iReduceHeight
                );
            }
        }
    }
	// Other Algorithm 0003
    else if (pView->iChoiceMode == 4)
    {
        pView->stOtherAlgorithm0003Init.stRectInROI01.lSX = 1;
        pView->stOtherAlgorithm0003Init.stRectInROI01.lSY = 1;
        pView->stOtherAlgorithm0003Init.stRectInROI01.lEX = dwWidth;
        pView->stOtherAlgorithm0003Init.stRectInROI01.lEY = dwHeight;
        pView->stOtherAlgorithm0003Init.stRectInROI01.lWidth = pView->stOtherAlgorithm0003Init.stRectInROI01.lEX - pView->stOtherAlgorithm0003Init.stRectInROI01.lSX + 1;
        pView->stOtherAlgorithm0003Init.stRectInROI01.lHeight = pView->stOtherAlgorithm0003Init.stRectInROI01.lEY - pView->stOtherAlgorithm0003Init.stRectInROI01.lSY + 1;

        pView->stOtherAlgorithm0003Output.bOutTrigger01 = false;

        double dbOtherAlgorithm0003 = 0.0f;

        bool bRet = false;

        bRet = pView->pOtherAlgorithm0003->AlgInit(
            &pView->bOtherAlgorithm0003Init,
            &pView->stOtherAlgorithm0003Init,
            NULL
        );
        if (bRet == false) { return; }

        bRet = pView->pOtherAlgorithm0003->AlgInput(
            buf + sizeof(BITMAPINFOHEADER),
            dwWidth,
            dwHeight,
            iBitDepth,
            NULL,
            NULL
        );
        if (bRet == false) { return; }

        bRet = pView->pOtherAlgorithm0003->AlgProcessing(
            NULL,
            NULL
        );
        if (bRet == false) { return; }

        bRet = pView->pOtherAlgorithm0003->AlgOutput(
            pView->pucReduceAnalysisImageCurrent1 + sizeof(BITMAPINFOHEADER),
            pView->pucReduceAnalysisImageCurrent2 + sizeof(BITMAPINFOHEADER),
            &dbOtherAlgorithm0003,
            &pView->stOtherAlgorithm0003Output,
            NULL
        );
        if (bRet == false) { return; }

        if (pView->stOtherAlgorithm0003Output.bOutTrigger01 == true)
        {
            if (pView->m_checkAutoSavePicture.GetCheck() == BST_CHECKED)
            {
                CString csFileNameSaveBitmap = _T("");
                pView->m_editFileNameSaveBitmap.GetWindowTextA(csFileNameSaveBitmap);
                csFileNameSaveBitmap = csFileNameSaveBitmap + _T("RealTime_");
                pView->m_lMSPCount++;
                pView->SaveBitmapToFile(
                    csFileNameSaveBitmap.GetBuffer(),
                    pView->m_lMSPCount,
                    buf + sizeof(BITMAPINFOHEADER),
                    dwWidth,
                    dwHeight,
                    ABS(((LPBITMAPINFO)buf)->bmiHeader.biBitCount / 8),
                    0,
                    0,
                    dwWidth - 1,
                    dwHeight - 1,
                    dwWidth,
                    dwHeight
                );
                csFileNameSaveBitmap = _T("");
                pView->m_editFileNameSaveBitmap.GetWindowTextA(csFileNameSaveBitmap);
                csFileNameSaveBitmap = csFileNameSaveBitmap + _T("Analysis_");
                pView->SaveBitmapToFile(
                    csFileNameSaveBitmap.GetBuffer(),
                    pView->m_lMSPCount,
                    pView->pucReduceAnalysisImageCurrent1 + sizeof(BITMAPINFOHEADER),
                    iReduceWidth,
                    iReduceHeight,
                    ABS(((LPBITMAPINFO)pView->pucReduceAnalysisImageCurrent1)->bmiHeader.biBitCount / 8),
                    0,
                    0,
                    iReduceWidth - 1,
                    iReduceHeight - 1,
                    iReduceWidth,
                    iReduceHeight
                );
            }
        }
    }


    if ( pView->bStopFlag == false )
    {
        memcpy ( pView->pucMonitorSaveCurrentBitmap, buf, len );

        if (
            pView->iChoiceMode == 1 ||
            pView->iChoiceMode == 2 ||
            pView->iChoiceMode == 3 ||
            pView->iChoiceMode == 4 ||
            pView->iChoiceMode == 11
            )
        {
            memcpy(pView->pucReduceAnalysisImageCurrent1, buf, sizeof(BITMAPINFOHEADER) );
            ( (LPBITMAPINFO) pView->pucReduceAnalysisImageCurrent1 )->bmiHeader.biWidth = iReduceWidth;
            ( (LPBITMAPINFO) pView->pucReduceAnalysisImageCurrent1 )->bmiHeader.biHeight = -(iReduceHeight);
            ( (LPBITMAPINFO) pView->pucReduceAnalysisImageCurrent1 )->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            ( (LPBITMAPINFO) pView->pucReduceAnalysisImageCurrent1 )->bmiHeader.biSizeImage = iReduceLength;

            memcpy(pView->pucReduceAnalysisImageCurrent2, buf, sizeof(BITMAPINFOHEADER) );
            ( (LPBITMAPINFO) pView->pucReduceAnalysisImageCurrent2 )->bmiHeader.biWidth = iReduceWidth;
            ( (LPBITMAPINFO) pView->pucReduceAnalysisImageCurrent2 )->bmiHeader.biHeight = -(iReduceHeight);
            ( (LPBITMAPINFO) pView->pucReduceAnalysisImageCurrent2 )->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            ( (LPBITMAPINFO) pView->pucReduceAnalysisImageCurrent2 )->bmiHeader.biSizeImage = iReduceLength;
        }
    }

    if (true)
    {
        static LARGE_INTEGER liPreTime;
        static LARGE_INTEGER liCurTime;
        LARGE_INTEGER liFrequency;
        double dbTimeDiff = 0.0f;
        BOOL bRet = false;
        bRet = QueryPerformanceCounter ( &liCurTime );
        bRet = QueryPerformanceFrequency ( &liFrequency );
        dbTimeDiff = double ( liCurTime.QuadPart - liPreTime.QuadPart ) / double ( liFrequency.QuadPart );
        char cTimeClock [50];
        ZeroMemory ( cTimeClock, 50 * sizeof(char) );
        sprintf_s( cTimeClock, "%f\n", dbTimeDiff );
        OutputDebugStringA( cTimeClock );
        liPreTime = liCurTime;
    }

    /*******************************************************************************************/
    // Lai Linwen, Lai Taiyu, "A High Efficiency Flame Detection Mobile Camera System (HEFD-MCS)"
    // Other Algorithm 0001
    // Other Algorithm 0002
    // Other Algorithm 0003
    if (
        pView->iChoiceMode == 1 ||
        pView->iChoiceMode == 2 ||
        pView->iChoiceMode == 3 ||
        pView->iChoiceMode == 4
        )
    {
        // Current Image
        if (true)
        {
            HDC RenderDC = ::GetDC(pView->m_pictureMonitor.m_hWnd);
            CRect crect;
            int iRet = 0;
            pView->m_pictureMonitor.GetClientRect(crect);
            ::SetStretchBltMode(RenderDC, COLORONCOLOR);
            ::SetBkMode(RenderDC, TRANSPARENT);
            ::SetBkColor(RenderDC, TRANSPARENT);
            iRet = StretchDIBits(
                RenderDC,
                0,
                0,
                crect.right,
                crect.bottom,
                0,
                0,
                dwWidth,
                dwHeight,
                buf + sizeof(BITMAPINFOHEADER),
                (LPBITMAPINFO)buf,
                DIB_RGB_COLORS,
                SRCCOPY
            );
            if (iRet == GDI_ERROR) {}

            LOGFONT lf;
            HFONT font, oldFont;
            memset(&lf, 0, sizeof(LOGFONT));
            lf.lfHeight = -24;
            lf.lfCharSet = DEFAULT_CHARSET;
            lf.lfOutPrecision = OUT_TT_PRECIS;
            lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
            lf.lfQuality = PROOF_QUALITY;
            strncpy(lf.lfFaceName, _T("Arial Black\0"), sizeof(lf.lfFaceName) - 1);
            font = CreateFontIndirectA(&lf);
            oldFont = (HFONT)SelectObject(RenderDC, font);
            CString strTmp;
            strTmp.Format(_T("Processing Pre Frame Time (Second): %4.4f"), dbTimeDiff);
            SetTextColor(RenderDC, RGB(255, 0, 0));
            TextOut(RenderDC, 10, 0, strTmp, strTmp.GetLength());
            strTmp.Format(_T("Frame Count: %d"), pView->lFrameCount);
            SetTextColor(RenderDC, RGB(255, 0, 0));
            TextOut(RenderDC, 10, 28, strTmp, strTmp.GetLength());
            SelectObject(RenderDC, oldFont);

            ReleaseDC(pView->m_pictureMonitor.m_hWnd, RenderDC);
            DeleteDC(RenderDC);
        }
        // Analysis Image
        if (true)
        {
            HDC RenderDC = ::GetDC(pView->m_pictureAnalysis.m_hWnd);
            CRect crect;
            int iRet = 0;
            pView->m_pictureAnalysis.GetClientRect(crect);
            ::SetStretchBltMode(RenderDC, COLORONCOLOR);
            iRet = StretchDIBits(
                RenderDC,
                0,
                0,
                crect.right,
                crect.bottom,
                0,
                0,
                iReduceWidth,
                iReduceHeight,
                pView->pucReduceAnalysisImageCurrent1 + sizeof(BITMAPINFOHEADER),
                (LPBITMAPINFO)pView->pucReduceAnalysisImageCurrent1,
                DIB_RGB_COLORS,
                SRCCOPY
            );
            if (iRet == GDI_ERROR) {}
            ReleaseDC(pView->m_pictureAnalysis.m_hWnd, RenderDC);
            DeleteDC(RenderDC);
        }
    }
    /*******************************************************************************************/
    // Lai Linwen, Lai Taiyu, "A High Efficiency Flame Detection Mobile Camera System (HEFD-MCS)"
    else if (pView->iChoiceMode == 11)
    {
        // Current Image
        if (true)
        {
            HDC RenderDC = ::GetDC(pView->m_pictureMonitor.m_hWnd);
            CRect crect;
            int iRet = 0;
            pView->m_pictureMonitor.GetClientRect(crect);
            ::SetStretchBltMode(RenderDC, COLORONCOLOR);
            ::SetBkMode(RenderDC, TRANSPARENT);
            ::SetBkColor(RenderDC, TRANSPARENT);
            iRet = StretchDIBits(
                RenderDC,
                0,
                0,
                crect.right,
                crect.bottom,
                0,
                0,
                dwWidth,
                dwHeight,
                buf + sizeof(BITMAPINFOHEADER),
                (LPBITMAPINFO)buf,
                DIB_RGB_COLORS,
                SRCCOPY
            );
            if (iRet == GDI_ERROR) {}

            LOGFONT lf;
            HFONT font, oldFont;
            memset(&lf, 0, sizeof(LOGFONT));
            lf.lfHeight = -24; /* character height rather than cell height */
            lf.lfCharSet = DEFAULT_CHARSET;
            lf.lfOutPrecision = OUT_TT_PRECIS;
            lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
            lf.lfQuality = PROOF_QUALITY;
            strncpy(lf.lfFaceName, _T("Arial Black\0"), sizeof(lf.lfFaceName) - 1);
            font = CreateFontIndirectA(&lf);
            oldFont = (HFONT)SelectObject(RenderDC, font);
            CString strTmp;
            strTmp.Format(_T("Processing Pre Frame Time (Second): %4.4f"), dbTimeDiff);
            SetTextColor(RenderDC, RGB(255, 0, 0));
            TextOut(RenderDC, 10, 0, strTmp, strTmp.GetLength());
            strTmp.Format(_T("Frame Count: %d"), pView->lFrameCount);
            SetTextColor(RenderDC, RGB(255, 0, 0));
            TextOut(RenderDC, 10, 28, strTmp, strTmp.GetLength());
            SelectObject(RenderDC, oldFont);
            DeleteObject(font);

            ReleaseDC(pView->m_pictureMonitor.m_hWnd, RenderDC);
            DeleteDC(RenderDC);
        }
        // Analysis Image
        if (true)
        {
            HDC RenderDC = ::GetDC(pView->m_pictureAnalysis.m_hWnd);
            CRect crect;
            int iRet = 0;
            pView->m_pictureAnalysis.GetClientRect(crect);
            ::SetStretchBltMode(RenderDC, COLORONCOLOR);
            iRet = StretchDIBits(
                RenderDC,
                0,
                0,
                crect.right,
                crect.bottom,
                0,
                0,
                iReduceWidth,
                iReduceHeight,
                pView->pucReduceAnalysisImageCurrent2 + sizeof(BITMAPINFOHEADER),
                (LPBITMAPINFO)pView->pucReduceAnalysisImageCurrent1,
                DIB_RGB_COLORS,
                SRCCOPY
            );
            if (iRet == GDI_ERROR) {}
            ReleaseDC(pView->m_pictureAnalysis.m_hWnd, RenderDC);
            DeleteDC(RenderDC);
        }
    }
    /***************************************************************************/
    if ( pView->m_bSavePicture == true )
    {
        CString csFileNameSaveBitmap = _T("");
        pView->m_editFileNameSaveBitmap.GetWindowTextA ( csFileNameSaveBitmap );
        csFileNameSaveBitmap = csFileNameSaveBitmap + _T("RealTime_");
        pView->m_lMSPCount++;
        pView->SaveBitmapToFile (
            csFileNameSaveBitmap.GetBuffer(),
            pView->m_lMSPCount,
            buf + sizeof(BITMAPINFOHEADER),
            dwWidth,
            dwHeight,
            ABS ( ( (LPBITMAPINFO) buf )->bmiHeader.biBitCount / 8 ),
            0,
            0,
            dwWidth - 1,
            dwHeight - 1,
            dwWidth,
            dwHeight
            );
        csFileNameSaveBitmap = _T("");
        pView->m_editFileNameSaveBitmap.GetWindowTextA ( csFileNameSaveBitmap );
        csFileNameSaveBitmap = csFileNameSaveBitmap + _T("Analysis_");
        pView->SaveBitmapToFile (
            csFileNameSaveBitmap.GetBuffer(),
            pView->m_lMSPCount,
            pView->pucReduceAnalysisImageCurrent1 + sizeof(BITMAPINFOHEADER),
            iReduceWidth, 
            iReduceHeight,
            ABS ( ( (LPBITMAPINFO) pView->pucReduceAnalysisImageCurrent1 )->bmiHeader.biBitCount / 8 ),
            0,
            0,
            iReduceWidth - 1,
            iReduceHeight - 1,
            iReduceWidth,
            iReduceHeight
            );
        pView->m_bSavePicture = false;
    }
    /***************************************************************************/
    // Frame Count
    pView->lFrameCount++;
    if ( pView->lFrameCount > INT_MAX )
    {
        pView->lFrameCount = 1;
    }
}

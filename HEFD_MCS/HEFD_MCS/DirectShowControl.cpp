#pragma once
#include "StdAfx.h"
#include "DirectShowControl.h"
#include "DirectShowControl_ImageCallback.h"

#include "HEFD_MCSDoc.h"
#include "HEFD_MCSView.h"


DWORD WINAPI VideoDisplayThreadProcess ( LPVOID lpParameter )
{
    DirectShowControl* pWnd = (DirectShowControl*) lpParameter;
    HANDLE hEvent = NULL;
    REFERENCE_TIME pos = 0;
    HRESULT hr = S_FALSE;
    bool bDone = false;
    long code = 0;
    long p1 = 0;
    long p2 = 0;
    pWnd->pMediaEventEx->GetEventHandle ( (OAEVENT*) &hEvent );
    while ( !bDone )
    {
        if ( WaitForSingleObject ( hEvent, 80 ) == WAIT_OBJECT_0 )
        {
            while ( SUCCEEDED ( pWnd->pMediaEventEx->GetEvent ( &code, &p1, &p2, 0 ) ) )
            {
                pWnd->pMediaEventEx->FreeEventParams ( code, p1, p2 );
                if ( code == EC_COMPLETE )
                {
                    if ( pWnd->m_bRepeat == true )
                    {
                        pos = 0;
                        hr = pWnd->pMediaSeeking->SetPositions ( 
                            &pos, 
                            AM_SEEKING_AbsolutePositioning,
                            NULL, 
                            AM_SEEKING_NoPositioning
                            );
                    }
                    else if ( pWnd->m_bRepeat == false )
                    {
                        bDone = true;
                    }
                }
            }
        }
    }
    if ( bDone == true )
    {
        pWnd->pMediaControl->Stop();
        AfxMessageBox( _T("Vedio Complete.\nPress Stop Button.\nEnable All Radio Button.\n"), MB_OK );
    }
    pWnd->m_hVideoDisplayThread = NULL;
    TerminateThread ( 
        pWnd->m_hVideoDisplayThread, 
        0 
        );
    return 0 ;
}


DirectShowControl::DirectShowControl(void)
{
    m_hwnd = NULL;
    pGraphBuilder = NULL;
    pEnhancedVideoRenderer = NULL;
    pGetService = NULL;
    pVideoDisplayControl = NULL;
    pVideoWindow = NULL;
    pSampleGrabberFilter = NULL;
    pSampleGrabber = NULL;
    pMediaControl = NULL;
    pMediaSeeking = NULL;
    pMediaEventEx = NULL;
    pMediaPosition = NULL;
    m_hVideoDisplayThread = NULL;
    m_bRepeat = false;
    CoInitializeEx ( NULL, COINIT_APARTMENTTHREADED );
}


DirectShowControl::~DirectShowControl(void)
{
    m_hwnd = NULL;
    SAFE_RELEASE ( pGraphBuilder );
    SAFE_RELEASE ( pEnhancedVideoRenderer );
    SAFE_RELEASE ( pGetService );
    SAFE_RELEASE ( pVideoDisplayControl );
    SAFE_RELEASE ( pVideoWindow );
    SAFE_RELEASE ( pSampleGrabberFilter );
    SAFE_RELEASE ( pSampleGrabber );
    SAFE_RELEASE ( pMediaControl );
    SAFE_RELEASE ( pMediaSeeking );
    SAFE_RELEASE ( pMediaEventEx );
    if ( m_hVideoDisplayThread )
    {
        TerminateThread ( 
            m_hVideoDisplayThread, 
            0 
            );
        m_hVideoDisplayThread = NULL;
    }
    m_bRepeat = false;
    CoUninitialize();
}


BSTR DirectShowControl::AnsiToBstr (
    char* cSrc
    )
{
    BSTR bDst = NULL;
    int iReq = MultiByteToWideChar(CP_ACP, 0, cSrc, -1, NULL, 0);

    if(iReq == 0)
        return NULL;

    bDst = (BSTR)malloc((iReq + 1) * sizeof(wchar_t));
    if(bDst == NULL)
        return NULL;

    MultiByteToWideChar(CP_ACP, 0, cSrc, -1, bDst, iReq);
    return bDst;
}


void DirectShowControl::EmptyParameter ()
{
    SAFE_RELEASE ( pMediaPosition );
    SAFE_RELEASE ( pMediaEventEx );
    SAFE_RELEASE ( pMediaSeeking );
    SAFE_RELEASE ( pMediaControl );
    SAFE_RELEASE ( pSampleGrabber );
    SAFE_RELEASE ( pSampleGrabberFilter );
    SAFE_RELEASE ( pVideoWindow );
    SAFE_RELEASE ( pVideoDisplayControl );
    SAFE_RELEASE ( pGetService );
    SAFE_RELEASE ( pEnhancedVideoRenderer );
    SAFE_RELEASE ( pGraphBuilder );
    if ( m_hVideoDisplayThread )
    {
        TerminateThread ( 
            m_hVideoDisplayThread, 
            0 
            );
        m_hVideoDisplayThread = NULL;
    }
}


bool DirectShowControl::SetWindowHandle ( CHEFD_MCSView* hwnd )
{
    if ( hwnd == NULL )
    {
        m_hwnd = NULL;
        return false;
    }
    else if ( hwnd != NULL )
    {
        m_hwnd = hwnd;
    }
    return true;
}


bool DirectShowControl::Start_MovieFile ( 
    char* pcFileName,
    bool bRepeat
    )
{
    
    HRESULT hr = S_FALSE;
    
    EmptyParameter ();
    
    m_bRepeat = bRepeat;
    
    hr = CoCreateInstance (
        CLSID_FilterGraph,
        NULL,
        CLSCTX_INPROC_SERVER, 
        IID_IGraphBuilder,
        (LPVOID*) &pGraphBuilder
        );
    if ( FAILED ( hr ) )
    { 
        AfxMessageBox ( _T("Create Graph fail.\n") ); 
        return false;
    }
    
    hr = AddFilterByCLSID ( 
        pGraphBuilder, 
        CLSID_EnhancedVideoRenderer, 
        (LPCWSTR) _T("Enhanced Video Render"), 
        &pEnhancedVideoRenderer 
        ); 
    if ( FAILED ( hr ) )
    { 
        AfxMessageBox ( _T("Enhanced Video Render fail.\n") ); 
        return false;
    }
    
    hr = pEnhancedVideoRenderer->QueryInterface (
        __uuidof ( IMFGetService ), 
        (void**) &pGetService
        ); 
    if ( FAILED ( hr ) )
    { 
        AfxMessageBox ( _T("IMFGetService fail\n") ); 
        return false;
    } 
    
    hr = pGetService->GetService ( 
        MR_VIDEO_RENDER_SERVICE,
        __uuidof(IMFVideoDisplayControl),
        (void**) &pVideoDisplayControl
        ); 
    if ( FAILED ( hr ) )
    { 
        AfxMessageBox ( _T("GetService fail::The object does not support the service.\n") ); 
        return false; 
    } 
    
    hr = pVideoDisplayControl->SetVideoWindow ( 
        m_hwnd->m_pictureTemp.m_hWnd
        ); 
    if ( FAILED ( hr ) )
    { 
        AfxMessageBox ( _T("SetVideoWindow fail::EVR\n") ); 
        return false;  
    }
    
    hr = pVideoDisplayControl->SetAspectRatioMode ( 
        MFVideoARMode_None
        );  
    if ( FAILED ( hr ) )
    { 
        AfxMessageBox ( _T("SetAspectRatioMode fail::EVR\n") ); 
        return false; 
    }
    
    RECT recDec; 
    memset ( &recDec, 0x00, sizeof ( RECT ) );
    

    hr = pVideoDisplayControl->SetVideoPosition ( 
        NULL, 
        &recDec 
        ); 
    if ( FAILED ( hr ) )
    { 
        AfxMessageBox ( _T("SetVideoPosition fail::EVR\n") ); 
        return false; 
    }
    
    hr = AddFilterByCLSID ( 
        pGraphBuilder, 
        CLSID_SampleGrabber, 
        (LPCWSTR) _T("Sample Grabber Filter"), 
        &pSampleGrabberFilter 
        ); 
    if ( FAILED ( hr ) )
    { 
        AfxMessageBox ( _T("Sample Grabber Filter fail\n") ); 
        return false; 
    }
    
    hr = pSampleGrabberFilter->QueryInterface ( 
        IID_ISampleGrabber,
        (LPVOID*) &pSampleGrabber 
        );
    if ( FAILED ( hr ) )
    { 
        AfxMessageBox ( _T("Sample Grabber fail\n") ); 
        return false; 
    }
    
    ZeroMemory ( &set_am_media_type, sizeof(set_am_media_type) );
    set_am_media_type.majortype = MEDIATYPE_Video;
    set_am_media_type.subtype = MEDIASUBTYPE_RGB32;
    set_am_media_type.formattype = FORMAT_VideoInfo;
    pSampleGrabber->SetMediaType ( &set_am_media_type );
    
    pGraphBuilder->QueryInterface ( 
        IID_IMediaControl,
        (LPVOID*) &pMediaControl 
        );
    BSTR bstrTemp = AnsiToBstr ( pcFileName );
    pMediaControl->RenderFile ( bstrTemp );
    SAFE_DELETE ( bstrTemp );
    
    pSampleGrabber->SetOneShot ( FALSE );       
    pSampleGrabber->SetBufferSamples ( TRUE );
    SampleGrabberCallback.SetImageCallback ( 
        m_hwnd, 
        (DirectShowControl_SampleGrabberCallback::DirectShowControl_ImageCallback) fnDirectShowControl_ImageCallback 
        );
    pSampleGrabber->SetCallback ( &SampleGrabberCallback, 1 );
    pSampleGrabber->GetConnectedMediaType ( &get_am_media_type );
    SampleGrabberCallback.SetAmMediaType ( get_am_media_type );
    
    hr = pGraphBuilder->QueryInterface ( 
        IID_IMediaEventEx, 
        (void**) &pMediaEventEx 
        );
    if ( FAILED ( hr ) )
    { 
        AfxMessageBox ( _T("Media Event Interface fail\n") ); 
        return false; 
    }
    
    hr = pGraphBuilder->QueryInterface ( 
        IID_IMediaSeeking, 
        (void**) &pMediaSeeking 
        );
    if ( FAILED ( hr ) )
    { 
        AfxMessageBox ( _T("Media Event Interface fail\n") ); 
        return false; 
    }
    
    hr = pGraphBuilder->QueryInterface (
        IID_IMediaPosition,
        (void**) &pMediaPosition
        );
    if ( FAILED ( hr ) )
    { 
        AfxMessageBox ( _T("Media Position Interface fail\n") ); 
        return false; 
    }
    pMediaPosition->put_Rate ( 1.0f );
    
    DWORD dwThreadID = 0;
    if ( m_hVideoDisplayThread != NULL )
    {
        TerminateThread ( 
            m_hVideoDisplayThread, 
            0 
            );
        m_hVideoDisplayThread = NULL;
    }
    m_hVideoDisplayThread = CreateThread (
        NULL,
        0,
        VideoDisplayThreadProcess,
        (void*) this,
        0,
        &dwThreadID
        );
    
    pMediaControl->Run();

    return true;
}


bool DirectShowControl::Continue ()
{
    if ( pMediaControl == NULL ) { ShowError(); return false; }
    pMediaControl->Run();
    return true;
}


bool DirectShowControl::Pause ()
{
    if ( pMediaControl == NULL ) { ShowError(); return false; }
    pMediaControl->Pause();
    return true;
}


bool DirectShowControl::Stop ()
{
    if ( pMediaControl == NULL ) { ShowError(); return false; }
    pMediaControl->Stop();
    EmptyParameter ();
    return true;
}


bool DirectShowControl::Step ()
{
    HRESULT hr = S_OK;
    IVideoFrameStep* pFrameStep = NULL;
    
    if ( pGraphBuilder == NULL ) { ShowError(); return false; }
    
    hr = pGraphBuilder->QueryInterface ( 
        IID_IVideoFrameStep, 
        (void**) &pFrameStep 
        );
    if ( SUCCEEDED ( hr ) )
    {
        hr = pFrameStep->CanStep ( 0L, NULL );
    }
    pFrameStep->Release();
    pFrameStep = NULL;
    
    if ( SUCCEEDED ( hr ) )
    {
        hr = pGraphBuilder->QueryInterface ( 
            IID_IVideoFrameStep, 
            (void**) &pFrameStep 
            );
        pFrameStep->Step ( 1, NULL );
        pFrameStep->Release();
    }
    return true;
}



HRESULT DirectShowControl::
    AddFilterByCLSID (
    IGraphBuilder *pGraph,  
    const GUID& clsid,      
    LPCWSTR wszName,        
    IBaseFilter **ppF       
    )      
{
    if ( !pGraph || !ppF )
    { 
        return E_POINTER;
    }
    *ppF = 0;
    IBaseFilter *pF = 0;
    HRESULT hr = CoCreateInstance (
        clsid, 
        0, 
        CLSCTX_INPROC_SERVER,
        IID_IBaseFilter, 
        reinterpret_cast<void**>(&pF)
        );
    if ( SUCCEEDED(hr) )
    {
        hr = pGraph->AddFilter ( pF, wszName );
        if ( SUCCEEDED(hr) )
        {
            *ppF = pF;
        }
        else
        {
            pF->Release();
        }
    }
    return hr;
}



bool DirectShowControl::PreviousFrame ()
{
    return true;
}

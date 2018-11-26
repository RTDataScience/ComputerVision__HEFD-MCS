#pragma once

#pragma comment( lib, "Strmiids.lib" )  
#ifdef _DEBUG
#pragma comment( lib, "Strmbasd.lib" ) 
#else
#pragma comment( lib, "Strmbase.lib" ) 
#endif
#include <Dshow.h>
#include <Qedit.h>  
#include <uuids.h>
#include <mfidl.h>
#include <evr.h>
#include "DirectShowControl_SampleGrabberCallback.h"

#include "HEFD_MCSDoc.h"
#include "HEFD_MCSView.h"


class DirectShowControl
{
private:
    CHEFD_MCSView* m_hwnd;
    IGraphBuilder* pGraphBuilder;
    IBaseFilter* pEnhancedVideoRenderer;
    IMFGetService* pGetService;
    IMFVideoDisplayControl* pVideoDisplayControl;
    IBaseFilter* pSampleGrabberFilter;
    ISampleGrabber* pSampleGrabber;


    IVideoWindow* pVideoWindow;
    IBaseFilter* pNullRender;
    AM_MEDIA_TYPE set_am_media_type;
    AM_MEDIA_TYPE get_am_media_type;
    DirectShowControl_SampleGrabberCallback SampleGrabberCallback;


private:
    BSTR AnsiToBstr (
        char *cSrc
        );
    
    void EmptyParameter ();
    
    HRESULT AddFilterByCLSID (
        IGraphBuilder *pGraph,  
        const GUID& clsid,      
        LPCWSTR wszName,        
        IBaseFilter **ppF       
        );

public:
    IMediaEventEx* pMediaEventEx;
    IMediaSeeking* pMediaSeeking;
    IMediaPosition* pMediaPosition;
    IMediaControl* pMediaControl;
    
    bool m_bRepeat;
    HANDLE m_hVideoDisplayThread;

public:
    DirectShowControl(void);
    virtual ~DirectShowControl(void);
    bool SetWindowHandle ( 
        CHEFD_MCSView* hwnd 
        );
    bool Start_MovieFile (  
        char* pcFileName,
        bool bRepeat
        );
    bool Continue ();
    bool Pause ();
    bool Stop ();
    bool Step ();
    
    bool PreviousFrame ();
};



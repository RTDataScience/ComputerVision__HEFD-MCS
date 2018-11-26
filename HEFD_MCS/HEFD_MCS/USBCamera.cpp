#include "StdAfx.h"
#include "USBCamera.h"
#include "USBCamera_ImageCallback.h"


#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }
#define SAFE_DELETE(x) if( (x) != NULL ) {delete (x); (x) = NULL;}
#define SAFE_DELETE_ARRAY(x) if( (x) != NULL ) {delete[] (x); (x) = NULL;}



CUSBCamera::CUSBCamera(void)
{
    
    if ( FAILED ( CoInitializeEx ( NULL, COINIT_APARTMENTTHREADED ) ) ) 
    {
        AfxMessageBox ( _T("CoInitialize Failed!\r\n") ); 
        return;
    }
    
    pGraph = NULL;
    
    pBuild = NULL;
    
    pCapture = NULL;
    
    pControl = NULL;
    
    pNull = NULL;
    
    pGrabber.Release();
}


CUSBCamera::~CUSBCamera(void)
{
    
    MachineRelease ();
    
    CoUninitialize ();
}


BOOL CUSBCamera::MachineRelease()
{
    
    if ( pControl != NULL )
    {
        pControl->Stop();
    }
    
    
    SAFE_RELEASE ( pGraph );
    
    if ( pBuild )
    {
        SAFE_RELEASE ( pBuild );
    }
    
    SAFE_RELEASE ( pCapture );
    
    SAFE_RELEASE ( pControl );
    
    SAFE_RELEASE ( pNull );
    
    pGrabber.Release();
    return TRUE;
}


BOOL CUSBCamera::
    VideoInputDeviceList ( 
    CStringArray& caryList 
    )
{
    caryList.RemoveAll();
	ICreateDevEnum *pDevEnum = NULL;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
		                          CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, 
		                          reinterpret_cast<void**>(&pDevEnum) );
	IEnumMoniker *pEnum = NULL;
	if (SUCCEEDED(hr))
    {
		hr = pDevEnum->CreateClassEnumerator ( CLSID_VideoInputDeviceCategory, &pEnum, 0 );
        if ( pEnum == NULL )
        {
            return FALSE;
        }
        if (SUCCEEDED(hr))
        {
            IMoniker *pMoniker = NULL;
            while (pEnum->Next(1, &pMoniker, NULL) == S_OK)	
            {
                IPropertyBag *pPropBag;
                hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void**)(&pPropBag));
                if (FAILED(hr)){
                    pMoniker->Release();
                    continue;  
                } 
                VARIANT varName;
                VariantInit(&varName);
                hr = pPropBag->Read(L"FriendlyName", &varName, 0);
                if (SUCCEEDED(hr))	
                {
                    COLE2T strName(varName.bstrVal);
                    caryList.Add( strName );
                    VariantClear(&varName);
                }
                pPropBag->Release();
                pMoniker->Release();

            }
        }
	}
    return TRUE;
}



BOOL CUSBCamera::
    Preview ( 
    void* UserParam, 
    CString cszDeviceName,
    bool& bFirstTime
    )
{
    
    HRESULT hr = S_FALSE;
    long lResoultion = 0;
    long lResoultionMaximum = 0;
    long lMaxWidth = 0;
    long lMaxHeight = 0;
    long lFormat = 0;
    
    if ( pControl != NULL )
    {
        
        hr = pControl->Run();
        if ( FAILED ( hr ) )
        {
            AfxMessageBox ( _T("Couldn't run the graph!") );
            return FALSE;
        }
    }
    
    else if ( pControl == NULL )
    {
        
        AM_MEDIA_TYPE stAMT;  
        
        hr = GetVideoInputDevice ( &pCapture, cszDeviceName );
        if ( FAILED ( hr ) || cszDeviceName.GetLength() <= 0 || pCapture == NULL )
        {
            AfxMessageBox ( _T("Cannot Found Device.\n") );
            PostQuitMessage ( 0 );
            return FALSE;
        }
        
        hr = InitCaptureGraphBuilder ( &pGraph, &pBuild );
        if ( FAILED ( hr ) )
        {
            return FALSE;
        }
        
        hr = CoCreateInstance ( 
            CLSID_NullRenderer, 
            NULL, 
            CLSCTX_INPROC_SERVER, 
            IID_IBaseFilter, 
            (void**) &pNull
            );
        if ( FAILED ( hr ) )
        {
            AfxMessageBox ( _T("Cannot create Null Renderer\n") );
            return FALSE;
        }
        
        hr = pGraph->AddFilter ( 
            pNull,  
            L"NullRender"
            );
        if ( FAILED ( hr ) )
        {
            AfxMessageBox ( _T("Cannot Add Null Renderer\n") );
            return FALSE;
        }
        
        if ( bFirstTime == true )
        {
            TakeBreak ( 500 );
        }
        
        hr = pGraph->AddFilter ( pCapture, L"Capture Filter" );     
        if ( FAILED ( hr ) )
        {
            AfxMessageBox ( _T("Cannot Add Device.\n") );
            return FALSE;
        }
        
        IAMStreamConfig* pConfig = NULL;
        hr = pBuild->FindInterface (
            &PIN_CATEGORY_CAPTURE,
            &MEDIATYPE_Video,
            pCapture,
            IID_IAMStreamConfig,
            (void**)& pConfig
            );
        int iCount = 0;
        int iSize = 0;
        int iFormat = 0;
        DWORD cbSize = sizeof(int) * 2;
        
        hr = pConfig->GetNumberOfCapabilities ( &iCount, &iSize );
        if ( SUCCEEDED(hr) &&
            iSize == sizeof(VIDEO_STREAM_CONFIG_CAPS) )
        {
            for ( iFormat = 0; iFormat < iCount && iFormat * cbSize < iCount * cbSize ; iFormat++ )
            {
                VIDEO_STREAM_CONFIG_CAPS scc;
                AM_MEDIA_TYPE *pmtConfig;
                
                hr = pConfig->GetStreamCaps ( iFormat, &pmtConfig, (BYTE*)&scc );
                if (SUCCEEDED(hr))
                {
                    
                    if ( scc.MaxOutputSize.cx == 640 && scc.MaxOutputSize.cy == 480 )
                    {
                        lMaxWidth = scc.MaxOutputSize.cx;
                        lMaxHeight = scc.MaxOutputSize.cy;
                        lFormat = iFormat;
                        hr = pConfig->SetFormat ( pmtConfig );
                        if ( FAILED ( hr ) )
                        {
                            MessageBox ( NULL, TEXT("SetFormat Failed\n"), NULL, MB_OK );
                        }
                    }
                    DeleteMediaType ( pmtConfig );
                }
            }
        }
        else
        {
            hr = E_FAIL;
        }
        
        
        pGrabber.Release();
        hr = pGrabber.CoCreateInstance ( CLSID_SampleGrabber );
        if ( FAILED ( hr ) )
        {
            AfxMessageBox ( _T("Fail to create SampleGrabber, maybe qedit.dll is not registered? \
                               Install the latest version of Microsoft DirectX. Chances are, \
                               upgrading to the latest version of DirectX will fix the qedit.dll not found error.\n") );
            return FALSE;
        }
        
        CComQIPtr<IBaseFilter, &IID_IBaseFilter> pGrabBase ( pGrabber );
        
        ZeroMemory ( &stAMT, sizeof(AM_MEDIA_TYPE) );
        
        stAMT.majortype = MEDIATYPE_Video;
        
        stAMT.subtype = MEDIASUBTYPE_RGB32; 
        
        stAMT.formattype = FORMAT_VideoInfo;
        
        hr = pGrabber->SetMediaType ( &stAMT );
        if ( FAILED ( hr ) )
        {
            AfxMessageBox ( _T("Fail to set media type!\n") );
            return FALSE;
        }
        
        hr = pGraph->AddFilter ( pGrabBase, L"Grabber" );
        if ( FAILED ( hr ) )
        {
            AfxMessageBox ( _T("Fail to put sample grabber in graph\n") );
            return FALSE;
        }
        
        hr = pBuild->RenderStream ( 
            &PIN_CATEGORY_CAPTURE, 
            &MEDIATYPE_Video,
            pCapture,
            pGrabBase,
            pNull
            );
        
        if ( bFirstTime == true )
        {
            TakeBreak ( 200 );
        }
        if ( FAILED ( hr ) )
        {
            
            hr = pBuild->RenderStream ( 
                &PIN_CATEGORY_PREVIEW, 
                &MEDIATYPE_Video,
                pCapture,
                pGrabBase,
                pNull
                );
        }
        if ( FAILED ( hr ) )
        {
            AfxMessageBox ( _T("Can't build the graph\n") );
            return FALSE;
        }
        
        mCB.SetImageCallback ( (void*) UserParam, fnUSBCamera_ImageCallback );
        
        hr = pGrabber->GetConnectedMediaType ( &stAMT );
        if ( FAILED ( hr ) )
        {
            AfxMessageBox ( _T("Can't get video format\n") );
            return FALSE;
        }
        VIDEOINFOHEADER* pVIH = (VIDEOINFOHEADER*) stAMT.pbFormat;
        mCB.lWidth = pVIH->bmiHeader.biWidth;
        mCB.lHeight = pVIH->bmiHeader.biHeight;
        FreeMediaType ( stAMT );
        
        hr = pGrabber->SetBufferSamples ( FALSE );
        if ( FAILED ( hr ) )
        {
            AfxMessageBox ( _T("Can't Set Buffer Samples\n") );
            return FALSE;
        }
        
        hr = pGrabber->SetOneShot ( FALSE );
        if ( FAILED ( hr ) )
        {
            AfxMessageBox ( _T("Can't Set One Shot\n") );
            return FALSE;
        }
        
        hr = pGrabber->SetCallback ( &mCB, 1 );
        if ( FAILED ( hr ) )
        {
            AfxMessageBox ( _T("Can't Set Callback\n") );
            return FALSE;
        }
        pGrabber.Release();
        
        hr = pGraph->QueryInterface ( 
            IID_IMediaControl, 
            (void **) &pControl
            );
        if ( FAILED ( hr ) )
        {
            AfxMessageBox ( _T("Couldn't create media control!") );
            return FALSE;
        }
        
        hr = pControl->Run();
        if ( FAILED ( hr ) )
        {
            AfxMessageBox ( _T("Couldn't run the graph!") );
            return FALSE;
        }
    }
    if ( bFirstTime == true )
    {

        bFirstTime = false;
    }
    return TRUE;
}


BOOL CUSBCamera::PreviewStopWhenReady()
{
    if ( pControl != NULL )
    {
        pControl->StopWhenReady();
    }
    return TRUE;
}


BOOL CUSBCamera::PreviewStop()
{
    if ( pControl != NULL )
    {
        pControl->Stop();
    }
    return TRUE;
}


BOOL CUSBCamera::PreviewPause()
{
    if ( pControl != NULL )
    {
        pControl->Pause();
    }
    return TRUE;
}


BOOL CUSBCamera::
    VideoCaptureFilter ( 
    HWND hwnd 
    )
{
    if ( pCapture == NULL )
    {
        return FALSE;
    }
    ISpecifyPropertyPages* pSpec = NULL;
    CAUUID cauuid;
    HRESULT hr = S_FALSE;
    hr = pCapture->QueryInterface ( 
        IID_ISpecifyPropertyPages, 
        (void **) &pSpec
        );
    if ( hr == S_OK )
    {
        hr = pSpec->GetPages ( &cauuid );
        if ( hr == S_OK )
        {
            hr = OleCreatePropertyFrame ( 
                hwnd, 
                30, 
                30, 
                NULL, 
                1,
                (IUnknown**) &pCapture, 
                cauuid.cElems,
                (GUID*) cauuid.pElems, 
                0, 
                0, 
                NULL
                );
            if ( hr == S_OK )
            {
                CoTaskMemFree(cauuid.pElems);
            }
        }
    }
    SAFE_RELEASE ( pSpec );
    return TRUE;
}


BOOL CUSBCamera::VideoCapturePin ( void* UserParam, CString cszDeviceName )
{
    
    HRESULT hr = S_FALSE;
    AM_MEDIA_TYPE stAMT;  
    
    MachineRelease();
    
    hr = InitCaptureGraphBuilder ( &pGraph, &pBuild );
    if ( FAILED ( hr ) )
    {
        return FALSE;
    }
    
    hr = GetVideoInputDevice ( &pCapture, cszDeviceName );
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Cannot Found Device.\n") );
        PostQuitMessage ( 0 );
        return FALSE;
    }
    
    hr = pGraph->AddFilter ( pCapture, L"Capture Filter" );     
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Cannot Add Device.\n") );
        return FALSE;
    }

    
    if ( 1 )
    {
        IAMStreamConfig *pSC;
        ISpecifyPropertyPages* pSpec;
        hr = pBuild->FindInterface ( 
            &PIN_CATEGORY_CAPTURE,
            &MEDIATYPE_Video,
            pCapture,
            IID_IAMStreamConfig,
            (void**) &pSC
            );
        CAUUID cauuid;
        hr = pSC->QueryInterface (
            IID_ISpecifyPropertyPages,
            (void**) &pSpec
            );
        if ( hr == S_OK )
        {
            hr = pSpec->GetPages(&cauuid);
            hr = OleCreatePropertyFrame (
                ((CWnd*)UserParam)->m_hWnd,
                30,
                30,
                NULL,
                1,
                (IUnknown**) &pSC,
                cauuid.cElems,
                (GUID*) cauuid.pElems,
                0,
                0,
                NULL
                );
            CoTaskMemFree(cauuid.pElems);
            pSpec->Release();
            pSC->Release();
        }
    }
    
    pGrabber.Release();
    hr = pGrabber.CoCreateInstance ( CLSID_SampleGrabber );
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Fail to create SampleGrabber, maybe qedit.dll is not registered? \
                           Install the latest version of Microsoft DirectX. Chances are, \
                           upgrading to the latest version of DirectX will fix the qedit.dll not found error.\n") );
        return FALSE;
    }
    
    CComQIPtr<IBaseFilter, &IID_IBaseFilter> pGrabBase ( pGrabber );
    
    ZeroMemory ( &stAMT, sizeof(AM_MEDIA_TYPE) );
    
    stAMT.majortype = MEDIATYPE_Video;
    
    stAMT.subtype = MEDIASUBTYPE_RGB32; 
    
    stAMT.formattype = FORMAT_VideoInfo;
    
    hr = pGrabber->SetMediaType ( &stAMT );
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Fail to set media type!\n") );
        return FALSE;
    }
    
    hr = pGraph->AddFilter ( pGrabBase, L"Grabber" );
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Fail to put sample grabber in graph\n") );
        return FALSE;
    }
    
    hr = CoCreateInstance ( 
        CLSID_NullRenderer, 
        NULL, 
        CLSCTX_INPROC_SERVER, 
        IID_IBaseFilter, 
        (void**) &pNull
        );
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Cannot create Null Renderer\n") );
        return FALSE;
    }
    
    hr = pGraph->AddFilter ( 
        pNull,  
        L"NullRender"
        );
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Cannot Add Null Renderer\n") );
        return FALSE;
    }
    
    hr = pBuild->RenderStream ( 
        &PIN_CATEGORY_PREVIEW, 
        &MEDIATYPE_Video,
        pCapture,
        pGrabBase,
        pNull
        );
    if ( FAILED ( hr ) )
    {
        
        hr = pBuild->RenderStream ( 
            &PIN_CATEGORY_CAPTURE, 
            &MEDIATYPE_Video,
            pCapture,
            pGrabBase,
            pNull
            );
    }
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Can't build the graph\n") );
        return FALSE;
    }
    
    mCB.SetImageCallback ( (void*) UserParam, fnUSBCamera_ImageCallback );
    
    hr = pGrabber->GetConnectedMediaType ( &stAMT );
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Can't get video format\n") );
        return FALSE;
    }
    VIDEOINFOHEADER* pVIH = (VIDEOINFOHEADER*) stAMT.pbFormat;
    mCB.lWidth = pVIH->bmiHeader.biWidth;
    mCB.lHeight = pVIH->bmiHeader.biHeight;
    FreeMediaType ( stAMT );
    
    hr = pGrabber->SetBufferSamples ( FALSE );
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Can't Set Buffer Samples\n") );
        return FALSE;
    }
    
    hr = pGrabber->SetOneShot ( FALSE );
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Can't Set One Shot\n") );
        return FALSE;
    }
    
    hr = pGrabber->SetCallback ( &mCB, 1 );
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Can't Set Callback\n") );
        return FALSE;
    }
    pGrabber.Release();
    
    hr = pGraph->QueryInterface ( 
        IID_IMediaControl, 
        (void **) &pControl
        );
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Couldn't create media control!") );
        return FALSE;
    }
    
    TakeBreak ( 100 );
    
    hr = pControl->Run();
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Couldn't run the graph!") );
        return FALSE;
    }
    return TRUE;
}


HRESULT CUSBCamera::InitCaptureGraphBuilder (
    IGraphBuilder **ppGraph,                    
    ICaptureGraphBuilder2 **ppBuild             
    )
{
    if ( !ppGraph || !ppBuild )
    {
        return E_POINTER;
    }
    
    IGraphBuilder *pGraph = NULL;
    ICaptureGraphBuilder2 *pBuild = NULL;
    HRESULT hr = S_FALSE;
    
    hr = CoCreateInstance ( 
        CLSID_CaptureGraphBuilder2, 
        NULL, 
        CLSCTX_INPROC_SERVER, 
        IID_ICaptureGraphBuilder2, 
        (void**) &pBuild 
        );
    if ( SUCCEEDED ( hr ) )
    {
        
        hr = CoCreateInstance (
            CLSID_FilterGraph, 
            0, 
            CLSCTX_INPROC,
            IID_IGraphBuilder, 
            (void**) &pGraph
            );
        if ( SUCCEEDED ( hr ) )
        {
            
            pBuild->SetFiltergraph ( pGraph );
            
            *ppBuild = pBuild;
            *ppGraph = pGraph; 
            return S_OK;
        }
        else 
        {
            pBuild->Release();
            hr = S_FALSE;
        }
    }
    
    return hr; 
}


HRESULT CUSBCamera::GetVideoInputDevice ( 
    IBaseFilter **pCap, 
    CString cszDeviceName 
    )
{
    
	ICreateDevEnum* pDevEnum = NULL;
    IEnumMoniker* pEnum = NULL;
    IMoniker* pMoniker = NULL;
    HRESULT hr = S_FALSE;
	
	hr = CoCreateInstance ( 
        CLSID_SystemDeviceEnum, 
        NULL,
        CLSCTX_INPROC_SERVER, 
        IID_ICreateDevEnum, 
        reinterpret_cast<void**>(&pDevEnum)
        );
	if ( SUCCEEDED ( hr ) )
    {
        
		hr = pDevEnum->CreateClassEnumerator ( 
            CLSID_VideoInputDeviceCategory, 
            &pEnum, 
            0 
            );
	}
    if ( pEnum == NULL )
    {
        return FALSE;
    }
	
	while ( pEnum->Next ( 1, &pMoniker, NULL ) == S_OK )	
    {
		IPropertyBag* pPropBag = NULL;
        CString cszTemp = _T("");
		hr = pMoniker->BindToStorage ( 
            0, 
            0, 
            IID_IPropertyBag, 
            (void**) &pPropBag 
            );
		if ( FAILED ( hr ) )
        {
            SAFE_RELEASE ( pMoniker );
			continue;  
		} 
	    
		VARIANT varName;
		VariantInit ( &varName );
		hr = pPropBag->Read ( 
            L"FriendlyName", 
            &varName, 
            0
            );
		if ( SUCCEEDED ( hr ) )	
        {
			
			COLE2T strName ( varName.bstrVal );
            cszTemp = strName;
			VariantClear ( &varName );
			hr = pMoniker->BindToObject (
                0, 
                0, 
                IID_IBaseFilter, 
                (void**) pCap
                ); 
		}
		SAFE_RELEASE ( pPropBag );
        SAFE_RELEASE ( pMoniker );
        
        if ( cszDeviceName == cszTemp )
        {
            return S_OK;
        }
	}
    
    return S_FALSE;
}


void CUSBCamera::
    TakeBreak ( 
    int iInNumber 
    )
{
    for ( int iI = 0; iI < iInNumber; iI++ )
    {
        Sleep(1);
    }
}


HRESULT CUSBCamera::
    GetCameraResolutions ( 
    CString cszDeviceName,
    long& lOutMaxWidth, 
    long& lOutMaxHeight,
    long& lOutFormat
    )
{
    
    HRESULT hr = S_OK;
    long lResoultion = 0;
    long lResoultionMaximum = 0;
    long lMaxWidth = 0;
    long lMaxHeight = 0;
    long lFormat = 0;
    
    MachineRelease();
    
    hr = InitCaptureGraphBuilder ( &pGraph, &pBuild );
    if ( FAILED ( hr ) )
    {
        return FALSE;
    }
    
    hr = GetVideoInputDevice ( &pCapture, cszDeviceName );
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Cannot Found Device.\n") );
        PostQuitMessage ( 0 );
        return FALSE;
    }
    
    TakeBreak ( 500 );
    
    hr = pGraph->AddFilter ( pCapture, L"Capture Filter" );     
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Cannot Add Device.\n") );
        return FALSE;
    }

    IAMStreamConfig* pConfig = NULL;
    hr = pBuild->FindInterface(
        &PIN_CATEGORY_CAPTURE,
        &MEDIATYPE_Video,
        pCapture,
        IID_IAMStreamConfig,
        (void**)&pConfig);

    int iCount = 0;
    int iSize = 0;
    
    hr = pConfig->GetNumberOfCapabilities(&iCount, &iSize);


    DWORD cbSize = sizeof(int) * 2;


    if ( 1 )
    {
        if (iSize == sizeof(VIDEO_STREAM_CONFIG_CAPS))
        {
            int iFormat = 0;
            for (iFormat = 0; iFormat < iCount && iFormat * cbSize < iCount * cbSize /* *pcbResolutionsSize*/; iFormat++)
            {
                VIDEO_STREAM_CONFIG_CAPS scc;
                AM_MEDIA_TYPE *pmtConfig;
                hr = pConfig->GetStreamCaps(iFormat, &pmtConfig, (BYTE*)&scc);
                if (SUCCEEDED(hr))
                {
                    lResoultion = scc.MaxOutputSize.cx * scc.MaxOutputSize.cy;
                    if ( lResoultion >= lResoultionMaximum )
                    {
                        lResoultionMaximum = lResoultion;
                        lMaxWidth = scc.MaxOutputSize.cx;
                        lMaxHeight = scc.MaxOutputSize.cy;
                        lFormat = iFormat;
                    }
                    DeleteMediaType(pmtConfig);
                }
            }
        }
    }

    MachineRelease();
    lOutMaxWidth = lMaxWidth;
    lOutMaxHeight = lMaxHeight;
    lOutFormat = lFormat;

    return hr;
}


HRESULT CUSBCamera::
    SetCameraResolution ( 
    CString cszDeviceName,
    long lInWidth,
    long lInHeight,
    long lInFormat
    )
{

    HRESULT hr = S_OK;
    
    MachineRelease();
    
    hr = InitCaptureGraphBuilder ( &pGraph, &pBuild );
    if ( FAILED ( hr ) )
    {
        return FALSE;
    }
    
    hr = GetVideoInputDevice ( &pCapture, cszDeviceName );
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Cannot Found Device.\n") );
        PostQuitMessage ( 0 );
        return FALSE;
    }
    
    hr = pGraph->AddFilter ( pCapture, L"Capture Filter" );     
    if ( FAILED ( hr ) )
    {
        AfxMessageBox ( _T("Cannot Add Device.\n") );
        return FALSE;
    }


    IAMStreamConfig* pConfig = NULL;
    
    hr = pBuild->FindInterface (
        &PIN_CATEGORY_CAPTURE,
        &MEDIATYPE_Video,
        pCapture,
        IID_IAMStreamConfig,
        (void**)& pConfig
        );


    int iCount = 0;
    int iSize = 0;
    
    hr = pConfig->GetNumberOfCapabilities(&iCount, &iSize);

    if ( SUCCEEDED(hr) &&
        iSize == sizeof(VIDEO_STREAM_CONFIG_CAPS) )
    {
        VIDEO_STREAM_CONFIG_CAPS scc;
        AM_MEDIA_TYPE *pmtConfig;
        
        hr = pConfig->GetStreamCaps((int)lInFormat, &pmtConfig, (BYTE*)&scc);
        if (SUCCEEDED(hr))
        {
            
            pConfig->SetFormat(pmtConfig);

            DeleteMediaType(pmtConfig);
        }
    }
    else
    {
        hr = E_FAIL;
    }


    return hr;
}







































































































































































































































































































































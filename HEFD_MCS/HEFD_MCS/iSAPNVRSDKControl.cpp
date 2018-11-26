#include "StdAfx.h"
#include "iSAPNVRSDKControl.h"
#include "iSAPNVRSDKControl_ImageCallback.h"


iSAPNVRSDKControl::iSAPNVRSDKControl(void)
{
    m_hAdapter = NULL;
}


iSAPNVRSDKControl::~iSAPNVRSDKControl(void)
{
    if ( m_hAdapter )
    {
        NVRClient_Disconnect ( m_hAdapter );
        NVRClient_FreeAdaptor ( m_hAdapter );
        m_hAdapter = NULL;
        WSACleanup();
    }
}


bool iSAPNVRSDKControl::
    Start_NVRChannel (
    long liSAPNVR_IPv41,
    long liSAPNVR_IPv42,
    long liSAPNVR_IPv43,
    long liSAPNVR_IPv44,
    long liSAPNVR_IPv4Port,
    char* ciSAPNVR_Channel,
    long liSAPNVR_Timeout,
    char* ciSAPNVR_UserID,
    char* ciSAPNVR_Password,
    unsigned long ulUserParameter
    )
{
    WSADATA wsaData;
    CString csHyperlink = _T("");
    
    csHyperlink.Format ( 
        "http://%d.%d.%d.%d:%d/airvideo/media?channel=%s\0\n",
        liSAPNVR_IPv41,
        liSAPNVR_IPv42,
        liSAPNVR_IPv43,
        liSAPNVR_IPv44,
        liSAPNVR_IPv4Port,
        ciSAPNVR_Channel
        );
    WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
    Stop_NVRChannel ();
    m_hAdapter = NVRClient_AllocAdaptor ();
    if ( m_hAdapter ) 
    {
        if ( NVRClient_Connect ( 
            m_hAdapter, 
            (const char*) csHyperlink.GetBuffer(), 
            liSAPNVR_Timeout, 
            ciSAPNVR_UserID, 
            ciSAPNVR_Password, 
            &fniSAPNVRSDKControl_ImageCallback, 
            ulUserParameter
            ) == false ) 
        {
            return false;
        }
    }
    csHyperlink.ReleaseBuffer();
    return true;
}



bool iSAPNVRSDKControl::
    Stop_NVRChannel ()
{
    if ( m_hAdapter )
    {
        NVRClient_Disconnect ( m_hAdapter );
        NVRClient_FreeAdaptor ( m_hAdapter );
        m_hAdapter = NULL;
        WSACleanup();
    }
    return true;
}


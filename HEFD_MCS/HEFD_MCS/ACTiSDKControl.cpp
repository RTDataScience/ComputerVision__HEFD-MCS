#pragma once
#include "stdafx.h"
#include "ACTiSDKControl.h"
#include "ACTiSDKControl_ImageCallback.h"


ACTiSDKControl::ACTiSDKControl(void)
{
    m_handle = NULL;
    m_hwnd = NULL;
}


ACTiSDKControl::~ACTiSDKControl(void)
{
}


bool ACTiSDKControl::SetWindowHandle ( CHEFD_MCSView* hwnd )
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


void ACTiSDKControl::EmptyStructure()
{
    m_handle = NULL;
    memset ( &m_mcc, 0x00, sizeof(m_mcc) );
    memset ( &m_mri, 0x00, sizeof(m_mri) );
    memset ( &m_mvc, 0x00, sizeof(m_mvc) );
    memset ( &m_sec, 0x00, sizeof(m_sec) );
}


bool ACTiSDKControl::Start_RAWFile ( 
    char* pcFileName
    )
{
    if ( pcFileName == NULL ) { ShowError(); return false; }
    bool bRet = false;
    EmptyStructure();
    m_mcc.ContactType = 7;
    sprintf_s( m_mcc.PlayFileName, "%s\0", pcFileName );
    if( m_handle != NULL )
    {
        KSetDICallback( m_handle, 0, NULL );
        KSetMotionDetectionCallback( m_handle, 0, NULL );
        KSetResolutionChangeCallback( m_handle, 0, NULL );
        KSetImageCallback( m_handle, 0, NULL );
        KSetNetworkLossCallback( m_handle, 0, NULL );
        KSetTimeCodeCallback ( m_handle, 0, NULL );
        KSetVideoLossCallback ( m_handle, 0, NULL );
        KStop( m_handle );
        KStopStreaming( m_handle );
        KDisconnect( m_handle );
        KCloseInterface( m_handle );
        m_handle = NULL;
    }
    m_handle = KOpenInterface();
    if ( m_handle == NULL )
    {
        MessageBox ( m_hwnd->m_hWnd, _T("Open Interface was error.\n"), _T("Warning"), MB_OK );
        return false;
    }
    KSetDICallback( m_handle, 0, NULL );
    KSetMotionDetectionCallback( m_handle, 0, NULL );
    KSetResolutionChangeCallback( m_handle, 0, NULL );
    KSetImageCallback ( m_handle, (DWORD) m_hwnd, ACTiSDKControl_ImageCallback ); 
    KSetNetworkLossCallback( m_handle, 0, NULL );
    KSetTimeCodeCallback ( m_handle, 0, NULL );
    KSetVideoLossCallback ( m_handle, 0, NULL );
    m_mri.DrawerInterface = DGDI;
    KSetTCPType ( m_handle, 0 );
    KSetMediaConfig ( m_handle, &m_mcc );
    bRet = KConnect ( m_handle );
    if ( bRet == false ) { ShowError(); return false; }
    bRet = KStartStreaming ( m_handle );
    if ( bRet == false ) { ShowError(); return false; }
    KGetVideoConfig( m_handle, &m_mvc );
    KSEStartStreaming ( m_handle );
    KPlay ( m_handle );
    m_handleACTiSDK = m_handle;
    return true;
}


bool ACTiSDKControl::Start_IPCamera ( 
    int iIPv41,
    int iIPv42,
    int iIPv43,
    int iIPv44,
    char* pcUserID,
    char* pcPassword
    )
{
    if ( iIPv41 < 0 || iIPv41 > 255 ) { ShowError(); return false; }
    if ( iIPv42 < 0 || iIPv42 > 255 ) { ShowError(); return false; }
    if ( iIPv43 < 0 || iIPv43 > 255 ) { ShowError(); return false; }
    if ( iIPv44 < 0 || iIPv44 > 255 ) { ShowError(); return false; }
    if ( pcUserID == NULL ) { ShowError(); return false; }
    if ( pcPassword == NULL ) { ShowError(); return false; }
    bool bRet = false;
    EmptyStructure();
    sprintf_s ( m_mcc.UniCastIP, "%d.%d.%d.%d\0", iIPv41, iIPv42, iIPv43, iIPv44 );
    sprintf_s ( m_mcc.MultiCastIP, "%d.%d.%d.%d\0", 228, 5, 6, 1 );
    m_mcc.ContactType = 5;
    memcpy ( &m_mcc.ChannelNumber, _T("0\0"), 2 );
    m_mcc.RegisterPort = (unsigned long) 6000;
    m_mcc.ControlPort = (unsigned long) 6001;
    m_mcc.StreamingPort = (unsigned long) 6002;
    m_mcc.HTTPPort = (unsigned long) 80;
    m_mcc.MultiCastPort = (unsigned long) 5000;
    m_mcc.RTSPPort = (unsigned long) 7070;
    m_mcc.SearchPortC2S = (unsigned long) 6005;
    m_mcc.SearchPortS2C = (unsigned long) 6006;
    m_mcc.ConnectTimeOut = (unsigned short) 0;
    memcpy ( &m_mcc.TCPVideoStreamID, _T("0\0"), 2 );
    m_mcc.RTPVideoTrackNumber = (unsigned char) 0;
    m_mcc.RTPAudioTrackNumber = (unsigned char) 0;
    memset ( &m_mcc.PlayFileName, 0x00, sizeof(m_mcc.PlayFileName) );
    sprintf_s ( m_mcc.UserID, "%s\0", pcUserID );
    sprintf_s ( m_mcc.Password, "%s\0", pcPassword );
    if( m_handle != NULL )
    {
        KSetDICallback( m_handle, 0, NULL );
        KSetMotionDetectionCallback( m_handle, 0, NULL );
        KSetResolutionChangeCallback( m_handle, 0, NULL );
        KSetImageCallback( m_handle, 0, NULL );
        KSetNetworkLossCallback( m_handle, 0, NULL );
        KSetTimeCodeCallback ( m_handle, 0, NULL );
        KSetVideoLossCallback ( m_handle, 0, NULL );
        KStop( m_handle );
        KStopStreaming( m_handle );
        KDisconnect( m_handle );
        KCloseInterface( m_handle );
        m_handle = NULL;
    }
    m_handle = KOpenInterface();
    if ( m_handle == NULL )
    {
        MessageBox ( m_hwnd->m_hWnd, _T("Open Interface was error.\n"), _T("Warning"), MB_OK );
        return false;
    }
    KSetDICallback( m_handle, 0, NULL );
    KSetMotionDetectionCallback( m_handle, 0, NULL );
    KSetResolutionChangeCallback( m_handle, 0, NULL );
    KSetImageCallback ( m_handle, (DWORD) m_hwnd, ACTiSDKControl_ImageCallback ); 
    KSetNetworkLossCallback( m_handle, 0, NULL );
    KSetTimeCodeCallback ( m_handle, 0, NULL );
    KSetVideoLossCallback ( m_handle, 0, NULL );
    m_mri.DrawerInterface = DGDI;
    KSetTCPType ( m_handle, 0 );
    KSetMediaConfig ( m_handle, &m_mcc );
    bRet = KConnect ( m_handle );
    if ( bRet == false ) { ShowError(); return false; }
    bRet = KStartStreaming ( m_handle );
    if ( bRet == false ) { ShowError(); return false; }
    KGetVideoConfig( m_handle, &m_mvc );
    KSEStartStreaming ( m_handle );
    KPlay ( m_handle );
    m_handleACTiSDK = m_handle;
    return true;
}


bool ACTiSDKControl::Continue ()
{
    if ( m_handle == NULL ) { ShowError(); return false; }
    KPlay ( m_handle );
    return true;
}


bool ACTiSDKControl::Pause ()
{
    if ( m_handle == NULL ) { ShowError(); return false; }
    KPause ( m_handle );
    return true;
}


bool ACTiSDKControl::Stop ()
{
    if ( m_handle == NULL ) { ShowError(); return false; }
    KSetDICallback( m_handle, 0, NULL );
    KSetMotionDetectionCallback( m_handle, 0, NULL );
    KSetResolutionChangeCallback( m_handle, 0, NULL );
    KSetImageCallback( m_handle, 0, NULL );
    KSetNetworkLossCallback( m_handle, 0, NULL );
    KSetTimeCodeCallback ( m_handle, 0, NULL );
    KSetVideoLossCallback ( m_handle, 0, NULL );
    KStop( m_handle );
    KStopStreaming( m_handle );
    KDisconnect( m_handle );
    KCloseInterface( m_handle );
    m_handle = NULL;
    return true;
}


bool ACTiSDKControl::
    Rate ( 
    double dbInRate 
    )
{
    if ( m_handle == NULL ) { ShowError(); return false; }
    long lSelect = 0;
    if ( dbInRate == 0.5f )
    {
        lSelect = 0;
    }
    else if ( dbInRate == 1.0f )
    {
        lSelect = 1;
    }
    else if ( dbInRate == 2.0f )
    {
        lSelect = 2;
    }
    else if ( dbInRate == 4.0f )
    {
        lSelect = 3;
    }
    else if ( dbInRate == 8.0f )
    {
        lSelect = 4;
    }
    KSetPlayRate ( m_handle, lSelect );
    return true;
}


bool ACTiSDKControl::
    Direction (
    bool bInFlag
    )
{
    if ( m_handle == NULL ) { ShowError(); return false; }
    KSetPlayDirection ( m_handle, bInFlag );
    return true;
}


bool ACTiSDKControl::
    NextFrame ()
{
    if ( m_handle == NULL ) { ShowError(); return false; }
    KPause ( m_handle );
    KStepNextFrame ( m_handle );
    return true;
}


bool ACTiSDKControl::
    PreviousFrame ()
{
    if ( m_handle == NULL ) { ShowError(); return false; }
    KPause ( m_handle );
    KStepPrevFrame ( m_handle );
    return true;
}


void GetTimeToStr ( time_t time, char *buf )
{
	struct tm *newtime;
	if(0 > time)
	{
		buf[0] = '\0';
		return;
	}
	newtime = gmtime((time_t *)&time);
	sprintf( buf, "%04d/%02d/%02d %02d:%02d:%02d\0", newtime->tm_year+1900, newtime->tm_mon+1, newtime->tm_mday, newtime->tm_hour, newtime->tm_min, newtime->tm_sec );
    OutputDebugStringA( buf );

}


bool ACTiSDKControl::
    GetPreviewTime (
    )
{
    if ( m_handle == NULL ) { ShowError(); return false; }
    DWORD dwCurrentTime = NULL;
    time_t timet;
    struct tm *newtime;
    char cTime [ 1024 ];
    memset ( cTime, 0x00, 1024 * sizeof(char) );
    dwCurrentTime = KGetCurrentTime ( m_handle );
    timet = (time_t) dwCurrentTime;
    newtime = gmtime((time_t *)&timet);
    sprintf_s( cTime, "%04d/%02d/%02d %02d:%02d:%02d\0", newtime->tm_year+1900, newtime->tm_mon+1, newtime->tm_mday, newtime->tm_hour, newtime->tm_min, newtime->tm_sec );
    OutputDebugStringA( cTime );
    return true;
}
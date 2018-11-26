#pragma once

#include "HEFD_MCSDoc.h"
#include "HEFD_MCSView.h"

#include "SDK10000.h"

class ACTiSDKControl
{
private:
    MEDIA_CONNECTION_CONFIG  m_mcc;
    MEDIA_RENDER_INFO        m_mri;
    MEDIA_VIDEO_CONFIG       m_mvc;
    STREAMING_ENGINE_CONFIG  m_sec;
    HANDLE m_handle;
    CHEFD_MCSView* m_hwnd;

private:
    void EmptyStructure();

public:
    ACTiSDKControl(void);
    virtual ~ACTiSDKControl(void);
    bool SetWindowHandle ( CHEFD_MCSView* hwnd );
    bool Start_RAWFile (  
        char* pcFileName
        );
    bool Start_IPCamera ( 
        int iIPv41,
        int iIPv42,
        int iIPv43,
        int iIPv44,
        char* pcUserID,
        char* pcPassword
        );
    bool Continue ();
    bool Pause ();
    bool Stop ();
    bool Rate ( 
        double dbInRate 
        );
    bool Direction (
        bool bInFlag
        );
    bool NextFrame ();
    bool PreviousFrame ();
    bool GetPreviewTime ();
};


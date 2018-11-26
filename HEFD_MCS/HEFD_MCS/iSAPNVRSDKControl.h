#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifdef EXPORTFUNC
#define DLL_IMPORT  
#else
#define DLL_IMPORT  __declspec(dllimport)
#endif

    typedef void ( CALLBACK* DATA_CALLBACK ) ( unsigned long ulUserParam, unsigned char* pszBuf, unsigned long ulLen );

    HANDLE	DLL_IMPORT PASCAL NVRClient_AllocAdaptor ();
    void	DLL_IMPORT PASCAL NVRClient_FreeAdaptor ( HANDLE adaptor );
    bool	DLL_IMPORT PASCAL NVRClient_Connect ( 
        HANDLE adaptor, 
        const char* url_in, 
        int Connecttimeout, 
        const char* username, 
        const char* password, 
        DATA_CALLBACK cb, 
        unsigned long param
        );
    void	DLL_IMPORT PASCAL NVRClient_Disconnect ( HANDLE adaptor );

#ifdef __cplusplus
}; 
#endif

class iSAPNVRSDKControl
{
public:
    iSAPNVRSDKControl(void);
    ~iSAPNVRSDKControl(void);

    
    bool Start_NVRChannel (
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
        );
    
    bool Stop_NVRChannel ();

public:


private:

    HANDLE m_hAdapter;


};


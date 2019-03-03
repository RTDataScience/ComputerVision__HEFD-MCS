#pragma once      


#include <vector>
#include <list>
#include <deque>
using namespace std;


#define SAFE_DELETE(x) if( (x) != NULL ) {delete (x); (x) = NULL;}         
#define SAFE_DELETE_ARRAY(x) if( (x) != NULL ) {delete[] (x); (x) = NULL;} 
#define SAFE_RELEASE(x) if( (x) != NULL ) {(x)->Release(); (x) = NULL;}    


#define _IN_        
#define _OUT_       
#define _INOUT_     


#define Round(a) int ( a + 0.5f )
#define ABS(a) ( ( (a) < 0 ) ? -(a) : (a) )


#ifdef DLLEX
#define DLL  __declspec(dllexport)     // export DLL information
#else
#define DLL  __declspec(dllimport)     // import DLL information
#endif


struct stRectangleData
{
    long lID;
    long lSX;
    long lSY;
    long lEX;
    long lEY;
    long lWidth;
    long lHeight;
    long lArea;
    long lPixels;
    double dbSX;
    double dbSY;
    double dbEX;
    double dbEY;
    double dbWidth;
    double dbHeight;
    double dbArea;
    double dbPixles;
    stRectangleData()
    {
        lID = 0;
        lSX = 0;
        lSY = 0;
        lEX = 0;
        lEY = 0;
        lWidth = 0;
        lHeight = 0;
        lArea = 0;
        lPixels = 0;
        dbSX = 0.0f;
        dbSY = 0.0f;
        dbEX = 0.0f;
        dbEY = 0.0f;
        dbWidth = 0.0f;
        dbHeight = 0.0f;
        dbArea = 0.0f;
        dbPixles = 0.0f;
    }
};


struct stLineData
{
    long lSX;
    long lSY;
    long lEX;
    long lEY;
    double dbSX;
    double dbSY;
    double dbEX;
    double dbEY;
    stLineData()
    {
        lSX = 0;
        lSY = 0;
        lEX = 0;
        lEY = 0;
        dbSX = 0.0f;
        dbSY = 0.0f;
        dbEX = 0.0f;
        dbEY = 0.0f;
    }
};


struct stTrackingData
{
    long lID;
    long lSX;
    long lSY;
    long lEX;
    long lEY;
    long lWidth;
    long lHeight;
    long lMX;
    long lMY;
    unsigned char* pucFeatureImage;
    long lFeatureImageWidth;
    long lFeatureImageHeight;
    long lFeatureImageBitDepth;
    long lFeatureImageLength;
    unsigned char* pucOriginImage;
    long lOriginImageWidth;
    long lOriginImageHeight;
    long lOriginImageBitDepth;
    long lOriginImageLength;
    double dbFeatureSimilar;
    long lSearchWindowSX;
    long lSearchWindowSY;
    long lSearchWindowEX;
    long lSearchWindowEY;
    long lSearchWindowWidth;
    long lSearchWindowHeight;
    long lFrameCount;
    int* piFeatureValue;
    long lFeatureValueLength;
    long lFeatureValueWidth;
    long lFeatureValueHeight;
    long lFeatureValueHorizontalCutting;
    long lFeatureValueVerticalCutting;
    stTrackingData()
    {
        lID = 0;
        lSX = 0;
        lSY = 0;
        lEX = 0;
        lEY = 0;
        lWidth = 0;
        lHeight = 0;
        lMX = 0;
        lMY = 0;
        pucFeatureImage = NULL;
        lFeatureImageWidth = 0;
        lFeatureImageHeight = 0;
        lFeatureImageBitDepth = 0;
        lFeatureImageLength = 0;
        pucFeatureImage = NULL;
        pucOriginImage = NULL;
        lOriginImageWidth = 0;
        lOriginImageHeight = 0;
        lOriginImageBitDepth = 0;
        lOriginImageLength = 0;
        pucOriginImage = NULL;
        dbFeatureSimilar = 0.0f;
        lSearchWindowSX = 0;
        lSearchWindowSY = 0;
        lSearchWindowEX = 0;
        lSearchWindowEY = 0;
        lSearchWindowWidth = 0;
        lSearchWindowHeight = 0;
        lFrameCount = 0;
        piFeatureValue = NULL;
        lFeatureValueLength = 0;
        lFeatureValueWidth = 0;
        lFeatureValueHeight = 0;
        lFeatureValueHorizontalCutting = 0;
        lFeatureValueVerticalCutting = 0;
        piFeatureValue = NULL;
    }
};


struct stObjectData
{
    long lID;
    deque<stTrackingData>* pdequeTracking;
    long lDirect3D;



    long lStatus;
    long lSearchWindowSX;
    long lSearchWindowSY;
    long lSearchWindowEX;
    long lSearchWindowEY;
    long lSearchWindowWidth;
    long lSearchWindowHeight;
    stObjectData()
    {
        lID = 0;
        pdequeTracking = NULL;
        lDirect3D = 0;
        lStatus = 0;
        lSearchWindowSX = 0;
        lSearchWindowSY = 0;
        lSearchWindowEX = 0;
        lSearchWindowEY = 0;
        lSearchWindowWidth = 0;
        lSearchWindowHeight = 0;
    }
};


struct stInitParameter
{
    bool _IN_ bInSwitch01;
    bool _IN_ bInSwitch02;
    bool _IN_ bInSwitch03;
    bool _IN_ bInSwitch04;
    bool _IN_ bInSwitch05;
    int _IN_ iInNumber01;
    int _IN_ iInNumber02;
    int _IN_ iInNumber03;
    int _IN_ iInNumber04;
    int _IN_ iInNumber05;
    long _IN_ lInNumber01;
    long _IN_ lInNumber02;
    long _IN_ lInNumber03;
    long _IN_ lInNumber04;
    long _IN_ lInNumber05;
    stRectangleData _IN_ stRectInROI01;
    stRectangleData _IN_ stRectInROI02;
    stRectangleData _IN_ stRectInROI03;
    stRectangleData _IN_ stRectInROI04;
    stRectangleData _IN_ stRectInROI05;
    stLineData _IN_ stLineIn01;
    stLineData _IN_ stLineIn02;
    stLineData _IN_ stLineIn03;
    stLineData _IN_ stLineIn04;
    stLineData _IN_ stLineIn05;
    double _IN_ dbInSensitivity01;
    double _IN_ dbInSensitivity02;
    double _IN_ dbInSensitivity03;
    double _IN_ dbInSensitivity04;
    double _IN_ dbInSensitivity05;
    double _IN_ dbInThreshold01;
    double _IN_ dbInThreshold02;
    double _IN_ dbInThreshold03;
    double _IN_ dbInThreshold04;
    double _IN_ dbInThreshold05;
    unsigned char* _IN_ pucInData01;
    unsigned char* _IN_ pucInData02;
    unsigned char* _IN_ pucInData03;
    unsigned char* _IN_ pucInData04;
    unsigned char* _IN_ pucInData05;
    double* _IN_ pdbInData01;
    double* _IN_ pdbInData02;
    double* _IN_ pdbInData03;
    double* _IN_ pdbInData04;
    double* _IN_ pdbInData05;
    long* _IN_ plInData01;
    long* _IN_ plInData02;
    long* _IN_ plInData03;
    long* _IN_ plInData04;
    long* _IN_ plInData05;
    void* _IN_ pvInReserve;
    stInitParameter()
    {
        bInSwitch01 = false;
        bInSwitch02 = false;
        bInSwitch03 = false;
        bInSwitch04 = false;
        bInSwitch05 = false;
        iInNumber01 = 0;
        iInNumber02 = 0;
        iInNumber03 = 0;
        iInNumber04 = 0;
        iInNumber05 = 0;
        lInNumber01 = 0;
        lInNumber02 = 0;
        lInNumber03 = 0;
        lInNumber04 = 0;
        lInNumber05 = 0;
        dbInSensitivity01 = 0.0f;
        dbInSensitivity02 = 0.0f;
        dbInSensitivity03 = 0.0f;
        dbInSensitivity04 = 0.0f;
        dbInSensitivity05 = 0.0f;
        dbInThreshold01 = 0.0f;
        dbInThreshold02 = 0.0f;
        dbInThreshold03 = 0.0f;
        dbInThreshold04 = 0.0f;
        dbInThreshold05 = 0.0f;
        pucInData01 = NULL;
        pucInData02 = NULL;
        pucInData03 = NULL;
        pucInData04 = NULL;
        pucInData05 = NULL;
        pdbInData01 = NULL;
        pdbInData02 = NULL;
        pdbInData03 = NULL;
        pdbInData04 = NULL;
        pdbInData05 = NULL;
        plInData01 = NULL;
        plInData02 = NULL;
        plInData03 = NULL;
        plInData04 = NULL;
        plInData05 = NULL;
        pvInReserve = NULL;
    }
};


struct stOutputData
{
    bool _OUT_ bOutTrigger01;
    bool _OUT_ bOutTrigger02;
    bool _OUT_ bOutTrigger03;
    bool _OUT_ bOutTrigger04;
    bool _OUT_ bOutTrigger05;
    int _OUT_ iOutNumber01;
    int _OUT_ iOutNumber02;
    int _OUT_ iOutNumber03;
    int _OUT_ iOutNumber04;
    int _OUT_ iOutNumber05;
    long _OUT_ lOutNumber01;
    long _OUT_ lOutNumber02;
    long _OUT_ lOutNumber03;
    long _OUT_ lOutNumber04;
    long _OUT_ lOutNumber05;
    double _OUT_ dbOutNumber01;
    double _OUT_ dbOutNumber02;
    double _OUT_ dbOutNumber03;
    double _OUT_ dbOutNumber04;
    double _OUT_ dbOutNumber05;
    stRectangleData _OUT_ stRectOutROI01;
    stRectangleData _OUT_ stRectOutROI02;
    stRectangleData _OUT_ stRectOutROI03;
    stRectangleData _OUT_ stRectOutROI04;
    stRectangleData _OUT_ stRectOutROI05;
    stLineData _OUT_ stLineOut01;
    stLineData _OUT_ stLineOut02;
    stLineData _OUT_ stLineOut03;
    stLineData _OUT_ stLineOut04;
    stLineData _OUT_ stLineOut05;
    unsigned char* _OUT_ pucOutData01;
    unsigned char* _OUT_ pucOutData02;
    unsigned char* _OUT_ pucOutData03;
    unsigned char* _OUT_ pucOutData04;
    unsigned char* _OUT_ pucOutData05;
    double* _OUT_ pdbOutData01;
    double* _OUT_ pdbOutData02;
    double* _OUT_ pdbOutData03;
    double* _OUT_ pdbOutData04;
    double* _OUT_ pdbOutData05;
    long* _OUT_ plOutData01;
    long* _OUT_ plOutData02;
    long* _OUT_ plOutData03;
    long* _OUT_ plOutData04;
    long* _OUT_ plOutData05;
    void* _OUT_ pvOutReserve;
    stOutputData()
    {
        bOutTrigger01 = false;
        bOutTrigger02 = false;
        bOutTrigger03 = false;
        bOutTrigger04 = false;
        bOutTrigger05 = false;
        iOutNumber01 = 0;
        iOutNumber02 = 0;
        iOutNumber03 = 0;
        iOutNumber04 = 0;
        iOutNumber05 = 0;
        lOutNumber01 = 0;
        lOutNumber02 = 0;
        lOutNumber03 = 0;
        lOutNumber04 = 0;
        lOutNumber05 = 0;
        dbOutNumber01 = 0.0f;
        dbOutNumber02 = 0.0f;
        dbOutNumber03 = 0.0f;
        dbOutNumber04 = 0.0f;
        dbOutNumber05 = 0.0f;
        pucOutData01 = NULL;
        pucOutData02 = NULL;
        pucOutData03 = NULL;
        pucOutData04 = NULL;
        pucOutData05 = NULL;
        pdbOutData01 = NULL;
        pdbOutData02 = NULL;
        pdbOutData03 = NULL;
        pdbOutData04 = NULL;
        pdbOutData05 = NULL;
        plOutData01 = NULL;
        plOutData02 = NULL;
        plOutData03 = NULL;
        plOutData04 = NULL;
        plOutData05 = NULL;
        pvOutReserve = NULL;
    }
};
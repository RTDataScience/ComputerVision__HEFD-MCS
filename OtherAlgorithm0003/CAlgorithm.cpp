#pragma once

#include "StdAfx.h"
#include "CAlgorithm.h"
#include <math.h> 
#include <cstdio>

using namespace std;

#define IN
#define OUT
#define PI 3.14159
#define _Max(x,y) ((x)>(y) ? (x) : (y))
#define _Min(x,y) ((x)<(y) ? (x) : (y))

typedef struct {
    float r;       // percent
    float g;       // percent
    float b;       // percent
} rgb;

typedef struct {
    float h;       // angle in degrees
    float s;       // percent
    float v;       // percent
} hsv;

typedef struct {
    double h;       // angle in degrees
    double s;       // percent
    double v;       // percent
} hsi;

#define NAN -1

static hsv rgb2hsv(rgb in);
static rgb hsv2rgb(hsv in);
static void RGBtoHSV(float r, float g, float b, float *h, float *s, float *v);
static void HSVtoRGB(float *r, float *g, float *b, float h, float s, float v);
static void HSI(
    IN unsigned int r,
    IN unsigned int g,
    IN unsigned int b,
    OUT double &Hue,
    OUT double &Saturation,
    OUT double &Intensity
);


CAlgorithm::CAlgorithm()
{
    bLabelTruePositive = false;
    iLabelTruePositive = 0;
    bLabelFalsePositive = false;
    iLabelFalsePositive = 0;
    bLabelTrueNegative = false;
    iLabelTrueNegative = 0;
    bLabelFalseNegative = false;
    iLabelFalseNegative = 0;

    m_dbTimeDiff = 0.0f;

    m_lOriginWidth = 0;

    m_lOriginHeight = 0;

    m_lOriginBitDepth = 0;

    m_lOriginLength = 0;

    dbReduceDivisor = 8;

    memset(&m_stInit, 0x00, sizeof(stInitParameter));

    memset(&m_stOutput, 0x00, sizeof(stOutputData));

    m_lReduceWidth = 0;

    m_lReduceHeight = 0;

    m_lReduceLength = 0;

    m_lOriginROISX = 0;

    m_lOriginROISY = 0;

    m_lOriginROIEX = 0;

    m_lOriginROIEY = 0;

    m_lOriginROIWidth = 0;

    m_lOriginROIHeight = 0;

    m_lOriginROILength = 0;

    m_lReduceROISX = 0;

    m_lReduceROISY = 0;

    m_lReduceROIEX = 0;

    m_lReduceROIEY = 0;

    m_lReduceROIWidth = 0;

    m_lReduceROIHeight = 0;

    m_lReduceROILength = 0;

    m_llFrameCount = 0;

    vectorBox.clear();

    vectorBoxAdjust.clear();


    m_pucOriginImage = NULL;

    m_pucDestinationImage = NULL;

    m_pucOriginROI = NULL;

    m_pucReduceROI = NULL;

    m_pucFireExtractionOfTheColorFeatureImage = NULL;

    m_pucContrastFilter = NULL;

    m_pucCombine = NULL;

    m_pucBoxMarker2 = NULL;

    m_pucInterFrameFlame1 = NULL;

    m_pucInterFrameFlame2 = NULL;

    m_pucFrameFlame = NULL;

    m_SearchNeighbor = NULL;

    m_piRGBtoYSH = NULL;

    m_pucThinning = NULL;

    m_pucBoxMarker1 = NULL;

    m_pucRGBtoYSH = NULL;

    m_pucStableFrame1 = NULL;

    m_pucStableFrame2 = NULL;

    m_pucStableFrame = NULL;

    //     m_pucIF1 = NULL;
    // 
    //     m_pucIF2 = NULL;
    // 
    //     m_pucIF = NULL;

}


CAlgorithm::~CAlgorithm()
{


    m_dbTimeDiff = 0.0f;

    m_lOriginWidth = 0;

    m_lOriginHeight = 0;

    m_lOriginBitDepth = 0;

    m_lOriginLength = 0;

    dbReduceDivisor = 8;

    memset(&m_stInit, 0x00, sizeof(stInitParameter));

    memset(&m_stOutput, 0x00, sizeof(stOutputData));

    m_lReduceWidth = 0;

    m_lReduceHeight = 0;

    m_lReduceLength = 0;

    m_lOriginROISX = 0;

    m_lOriginROISY = 0;

    m_lOriginROIEX = 0;

    m_lOriginROIEY = 0;

    m_lOriginROIWidth = 0;

    m_lOriginROIHeight = 0;

    m_lOriginROILength = 0;

    m_lReduceROISX = 0;

    m_lReduceROISY = 0;

    m_lReduceROIEX = 0;

    m_lReduceROIEY = 0;

    m_lReduceROIWidth = 0;

    m_lReduceROIHeight = 0;

    m_lReduceROILength = 0;

    vectorBox.clear();

    vectorBoxAdjust.clear();


    SAFE_DELETE_ARRAY(m_pucOriginImage);

    SAFE_DELETE_ARRAY(m_pucDestinationImage);

    SAFE_DELETE_ARRAY(m_pucOriginROI);

    SAFE_DELETE_ARRAY(m_pucReduceROI);

    SAFE_DELETE_ARRAY(m_pucFireExtractionOfTheColorFeatureImage);

    SAFE_DELETE_ARRAY(m_pucContrastFilter);

    SAFE_DELETE_ARRAY(m_pucCombine);

    SAFE_DELETE_ARRAY(m_pucBoxMarker2);

    SAFE_DELETE_ARRAY(m_pucInterFrameFlame1);

    SAFE_DELETE_ARRAY(m_pucInterFrameFlame2);

    SAFE_DELETE_ARRAY(m_pucFrameFlame);

    SAFE_DELETE_ARRAY(m_SearchNeighbor);

    SAFE_DELETE_ARRAY(m_piRGBtoYSH);

    SAFE_DELETE_ARRAY(m_pucThinning);

    SAFE_DELETE_ARRAY(m_pucBoxMarker1);

    SAFE_DELETE_ARRAY(m_pucRGBtoYSH);

    SAFE_DELETE_ARRAY(m_pucStableFrame1);

    SAFE_DELETE_ARRAY(m_pucStableFrame2);

    SAFE_DELETE_ARRAY(m_pucStableFrame);

    //     SAFE_DELETE_ARRAY ( m_pucIF1 );
    // 
    //     SAFE_DELETE_ARRAY ( m_pucIF2 );
    // 
    //     SAFE_DELETE_ARRAY ( m_pucIF );

}


bool CAlgorithm::
AlgInit(
    void* _IN_ pstInInitParameter
)
{

    if (pstInInitParameter == NULL)
    {
        AlgRelease();
        return false;
    }

    memcpy(&m_stInit, pstInInitParameter, sizeof(stInitParameter));

    dbReduceDivisor = m_stInit.dbInThreshold04;


    m_lOriginROISX = m_stInit.stRectInROI01.lSX - 1;

    m_lOriginROISY = m_stInit.stRectInROI01.lSY - 1;

    m_lOriginROIEX = m_stInit.stRectInROI01.lEX - 1;

    m_lOriginROIEY = m_stInit.stRectInROI01.lEY - 1;

    return true;
}


bool CAlgorithm::
AlgRelease()
{

    m_dbTimeDiff = 0.0f;

    m_lOriginWidth = 0;

    m_lOriginHeight = 0;

    m_lOriginBitDepth = 0;

    m_lOriginLength = 0;

    dbReduceDivisor = 8;

    memset(&m_stInit, 0x00, sizeof(stInitParameter));

    memset(&m_stOutput, 0x00, sizeof(stOutputData));

    m_lReduceWidth = 0;

    m_lReduceHeight = 0;

    m_lReduceLength = 0;

    m_lOriginROISX = 0;

    m_lOriginROISY = 0;

    m_lOriginROIEX = 0;

    m_lOriginROIEY = 0;

    m_lOriginROIWidth = 0;

    m_lOriginROIHeight = 0;

    m_lOriginROILength = 0;

    m_lReduceROISX = 0;

    m_lReduceROISY = 0;

    m_lReduceROIEX = 0;

    m_lReduceROIEY = 0;

    m_lReduceROIWidth = 0;

    m_lReduceROIHeight = 0;

    m_lReduceROILength = 0;

    vectorBox.clear();

    vectorBoxAdjust.clear();


    SAFE_DELETE_ARRAY(m_pucOriginImage);

    SAFE_DELETE_ARRAY(m_pucDestinationImage);

    SAFE_DELETE_ARRAY(m_pucOriginROI);

    SAFE_DELETE_ARRAY(m_pucReduceROI);

    SAFE_DELETE_ARRAY(m_pucFireExtractionOfTheColorFeatureImage);

    SAFE_DELETE_ARRAY(m_pucContrastFilter);

    SAFE_DELETE_ARRAY(m_pucCombine);

    SAFE_DELETE_ARRAY(m_pucBoxMarker2);

    SAFE_DELETE_ARRAY(m_pucInterFrameFlame1);

    SAFE_DELETE_ARRAY(m_pucInterFrameFlame2);

    SAFE_DELETE_ARRAY(m_pucFrameFlame);

    SAFE_DELETE_ARRAY(m_SearchNeighbor);

    SAFE_DELETE_ARRAY(m_piRGBtoYSH);

    SAFE_DELETE_ARRAY(m_pucThinning);

    SAFE_DELETE_ARRAY(m_pucBoxMarker1);

    SAFE_DELETE_ARRAY(m_pucRGBtoYSH);

    SAFE_DELETE_ARRAY(m_pucStableFrame1);

    SAFE_DELETE_ARRAY(m_pucStableFrame2);

    SAFE_DELETE_ARRAY(m_pucStableFrame);

    //     SAFE_DELETE_ARRAY ( m_pucIF1 );
    // 
    //     SAFE_DELETE_ARRAY ( m_pucIF2 );
    // 
    //     SAFE_DELETE_ARRAY ( m_pucIF );

    return true;
}


bool CAlgorithm::
AlgInput(
    unsigned char* _IN_ pucInData,
    long _IN_ lInWidth,
    long _IN_ lInHeight,
    long _IN_ lInBitDepth,
    void* _IN_ pstInInputParameter,
    void* _IN_ pInReserve
)
{


    if (pucInData == NULL)
    {
        return false;
    }

    if (lInWidth > 0 && lInWidth <= 2560)
    {

        m_lOriginWidth = lInWidth;
    }
    else
    {
        return false;
    }

    if (lInHeight > 0 && lInHeight <= 2048)
    {

        m_lOriginHeight = lInHeight;
    }
    else
    {
        return false;
    }

    if (lInBitDepth == 4 || lInBitDepth == 3 || lInBitDepth == 1)
    {

        m_lOriginBitDepth = lInBitDepth;
    }
    else
    {
        return false;
    }

    m_lOriginLength = m_lOriginWidth * m_lOriginHeight * m_lOriginBitDepth;


    dbReduceDivisor = m_stInit.dbInThreshold04;


    m_lReduceWidth = long(m_lOriginWidth / dbReduceDivisor);

    m_lReduceHeight = long(m_lOriginHeight / dbReduceDivisor);

    m_lReduceLength = m_lReduceWidth * m_lReduceHeight * m_lOriginBitDepth;

    if (m_lOriginROISX == m_lOriginROIEX == m_lOriginROISY == m_lOriginROIEY)
    {
        m_lOriginROISX = 0;
        m_lOriginROISY = 0;
        m_lOriginROIEX = m_lOriginWidth - 1;
        m_lOriginROIEY = m_lOriginHeight - 1;
    }

    if ((m_lOriginROISX >= 0 && m_lOriginROISX <= m_lOriginWidth - 1) &&
        (m_lOriginROISX < m_lOriginROIEX))
    {

        m_lReduceROISX = long(m_lOriginROISX / dbReduceDivisor);
    }
    else
    {
        return false;
    }

    if ((m_lOriginROISY >= 0 && m_lOriginROISY <= m_lOriginHeight - 1) &&
        (m_lOriginROISY < m_lOriginROIEY))
    {

        m_lReduceROISY = long(m_lOriginROISY / dbReduceDivisor);
    }
    else
    {
        return false;
    }

    if ((m_lOriginROIEX >= 0 && m_lOriginROIEX <= m_lOriginWidth - 1) &&
        (m_lOriginROISX < m_lOriginROIEX))
    {

        m_lReduceROIEX = long(m_lOriginROIEX / dbReduceDivisor);
    }
    else
    {
        return false;
    }

    if ((m_lOriginROIEY >= 0 && m_lOriginROIEY <= m_lOriginHeight - 1) &&
        (m_lOriginROISY < m_lOriginROIEY))
    {

        m_lReduceROIEY = long(m_lOriginROIEY / dbReduceDivisor);
    }
    else
    {
        return false;
    }

    m_lOriginROIWidth = m_lOriginROIEX - m_lOriginROISX + 1;

    m_lOriginROIHeight = m_lOriginROIEY - m_lOriginROISY + 1;

    m_lOriginROILength = m_lOriginROIWidth * m_lOriginROIHeight * m_lOriginBitDepth;

    m_lReduceROIWidth = m_lReduceROIEX - m_lReduceROISX + 1;

    m_lReduceROIHeight = m_lReduceROIEY - m_lReduceROISY + 1;

    m_lReduceROILength = m_lReduceROIWidth * m_lReduceROIHeight * m_lOriginBitDepth;



    if (m_pucOriginImage == NULL)
    {
        m_pucOriginImage = new unsigned char[m_lOriginLength];
        memcpy(m_pucOriginImage, pucInData, m_lOriginLength);
    }
    else if (m_pucOriginImage != NULL)
    {
        memcpy(m_pucOriginImage, pucInData, m_lOriginLength);
    }

    if (m_pucDestinationImage == NULL)
    {
        m_pucDestinationImage = new unsigned char[m_lReduceLength];
        memset(m_pucDestinationImage, 0x00, m_lReduceLength);
    }

    if (m_pucOriginROI == NULL)
    {
        m_pucOriginROI = new unsigned char[m_lOriginROILength];
        memset(m_pucOriginROI, 0x00, m_lOriginROILength);
    }

    if (m_pucReduceROI == NULL)
    {
        m_pucReduceROI = new unsigned char[m_lReduceROILength];
        memset(m_pucReduceROI, 0x00, m_lReduceROILength);
    }

    if (m_pucFireExtractionOfTheColorFeatureImage == NULL)
    {
        m_pucFireExtractionOfTheColorFeatureImage = new unsigned char[m_lReduceROILength];
        memset(m_pucFireExtractionOfTheColorFeatureImage, 0x00, m_lReduceROILength);
    }

    if (m_pucContrastFilter == NULL)
    {
        m_pucContrastFilter = new unsigned char[m_lReduceROILength];
        memset(m_pucContrastFilter, 0x00, m_lReduceROILength);
    }

    if (m_pucCombine == NULL)
    {
        m_pucCombine = new unsigned char[m_lReduceROILength];
        memset(m_pucCombine, 0x00, m_lReduceROILength);
    }

    if (m_pucBoxMarker2 == NULL)
    {
        m_pucBoxMarker2 = new unsigned char[m_lReduceROILength];
        memset(m_pucBoxMarker2, 0x00, m_lReduceROILength);
    }

    //     if ( m_pucIF1 == NULL )
    //     {
    //         m_pucIF1 = new unsigned char [ m_lReduceROILength ];
    //         memset ( m_pucIF1, 0x00, m_lReduceROILength );
    //     }
    // 
    //     if ( m_pucIF2 == NULL )
    //     {
    //         m_pucIF2 = new unsigned char [ m_lReduceROILength ];
    //         memset ( m_pucIF2, 0x00, m_lReduceROILength );
    //     }
    // 
    //     if ( m_pucIF == NULL )
    //     {
    //         m_pucIF = new unsigned char [ m_lReduceROILength ];
    //         memset ( m_pucIF, 0x00, m_lReduceROILength );
    //     }

    if (m_pucInterFrameFlame1 == NULL)
    {
        m_pucInterFrameFlame1 = new unsigned char[m_lReduceROILength];
        memset(m_pucInterFrameFlame1, 0x00, m_lReduceROILength);
    }

    if (m_pucInterFrameFlame2 == NULL)
    {
        m_pucInterFrameFlame2 = new unsigned char[m_lReduceROILength];
        memset(m_pucInterFrameFlame2, 0x00, m_lReduceROILength);
    }

    if (m_pucFrameFlame == NULL)
    {
        m_pucFrameFlame = new unsigned char[m_lReduceROILength];
        memset(m_pucFrameFlame, 0x00, m_lReduceROILength);
    }

    if (m_SearchNeighbor == NULL)
    {
        m_SearchNeighbor = new unsigned char[m_lReduceROILength];
        memset(m_SearchNeighbor, 0x00, m_lReduceROILength);
    }

    if (m_piRGBtoYSH == NULL)
    {
        m_piRGBtoYSH = new int[m_lReduceROILength];
        memset(m_piRGBtoYSH, 0x00, m_lReduceROILength * sizeof(int));
    }

    if (m_pucThinning == NULL)
    {
        m_pucThinning = new unsigned char[m_lReduceROILength];
        memset(m_pucThinning, 0x00, m_lReduceROILength);
    }

    if (m_pucBoxMarker1 == NULL)
    {
        m_pucBoxMarker1 = new unsigned char[m_lReduceROILength];
        memset(m_pucBoxMarker1, 0x00, m_lReduceROILength);
    }

    if (m_pucRGBtoYSH == NULL)
    {
        m_pucRGBtoYSH = new unsigned char[m_lReduceROILength];
        memset(m_pucRGBtoYSH, 0x00, m_lReduceROILength);
    }

    if (m_pucStableFrame1 == NULL)
    {
        m_pucStableFrame1 = new unsigned char[m_lReduceROILength];
        memset(m_pucStableFrame1, 0x00, m_lReduceROILength);
    }

    if (m_pucStableFrame2 == NULL)
    {
        m_pucStableFrame2 = new unsigned char[m_lReduceROILength];
        memset(m_pucStableFrame2, 0x00, m_lReduceROILength);
    }

    if (m_pucStableFrame == NULL)
    {
        m_pucStableFrame = new unsigned char[m_lReduceROILength];
        memset(m_pucStableFrame, 0x00, m_lReduceROILength);
    }



    if (m_llFrameCount + 1 < 120000000)
    {
        m_llFrameCount++;
    }
    else
    {
        m_llFrameCount = 1;
    }

    return true;
}


bool CAlgorithm::
AlgProcessing(
    void* _IN_ pInReserve,
    void* _OUT_ pOutReserve
)
{
    LARGE_INTEGER litmp;
    LONGLONG QPart1, QPart2;
    double dfMinus, dfFreq, dfTim;
    QueryPerformanceFrequency(&litmp);
    dfFreq = (double)litmp.QuadPart;
    QueryPerformanceCounter(&litmp);
    QPart1 = litmp.QuadPart;
    m_dbTimeDiff = 0.0f;
    if (m_lOriginBitDepth == 4)
    {
        if (AlgProcessing_BitDepth4() == false)
        {
            return false;
        }
    }
    else if (m_lOriginBitDepth == 3)
    {
        if (AlgProcessing_BitDepth3() == false)
        {
            return false;
        }
    }
    else if (m_lOriginBitDepth == 1)
    {
        if (AlgProcessing_BitDepth1() == false)
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    QueryPerformanceCounter(&litmp);
    QPart2 = litmp.QuadPart;
    dfMinus = (double)(QPart2 - QPart1);
    dfTim = dfMinus / dfFreq;
    char cTimeClock[50];
    ZeroMemory(cTimeClock, 50 * sizeof(char));
    sprintf_s(cTimeClock, "Second: %f\n", dfTim);
    OutputDebugStringA(cTimeClock);
    m_dbTimeDiff = dfTim;
    char cFrameIndex[50];
    ZeroMemory(cFrameIndex, 50 * sizeof(char));
    sprintf_s(cFrameIndex, "Frame Index: %d\n", m_llFrameCount);
    OutputDebugStringA(cFrameIndex);
    return true;
}


bool CAlgorithm::
AlgOutput(
    unsigned char* _OUT_ pucOutData1,
    unsigned char* _OUT_ pucOutData2,
    double* _OUT_ dbOutTimeDiff,
    void* _OUT_ pstOutputParameter,
    void* _OUT_ pOutReserve
)
{
    if (pucOutData1 != NULL && m_pucDestinationImage != NULL)
    {
        memcpy(pucOutData1, m_pucDestinationImage, m_lReduceLength);
    }
    if (pucOutData2 != NULL && m_pucDestinationImage != NULL)
    {
        memcpy(pucOutData2, m_pucDestinationImage, m_lReduceLength);
    }
    if (pstOutputParameter != NULL)
    {
        memcpy(pstOutputParameter, &m_stOutput, sizeof(stOutputData));
    }
    if (dbOutTimeDiff != NULL)
    {
        (*dbOutTimeDiff) = m_dbTimeDiff;
    }
    return true;
}


/************************************************************************/
/* private - Level 1                                                    */
/************************************************************************/


bool CAlgorithm::
AlgProcessing_BitDepth4()
{

    long lOTSUThreshold = 0;

    if (GetROIRagne(
        m_pucOriginImage,
        m_lOriginWidth,
        m_lOriginHeight,
        m_lOriginBitDepth,
        m_lOriginROISX,
        m_lOriginROIEX,
        m_lOriginROISY,
        m_lOriginROIEY,
        m_lOriginROIWidth,
        m_lOriginROIHeight,
        m_lOriginBitDepth,
        m_pucOriginROI
    ) == false)
    {
        return false;
    }

    if (ReduceImage(
        m_pucOriginROI,
        m_lOriginROIWidth,
        m_lOriginROIHeight,
        m_lOriginBitDepth,
        m_pucReduceROI,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        m_lOriginBitDepth
    ) == false)
    {
        return false;
    }

    if (FireExtractionOfTheColorFeatureImage(
        m_pucReduceROI,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        m_lOriginBitDepth,
        m_pucFireExtractionOfTheColorFeatureImage
    ) == false)
    {
        return false;
    }

    //bLabelTruePositive = false;
    ////int iLabelTruePositive = 0;
    //bLabelFalsePositive = false;
    ////int iLabelFalsePositive = 0;
    //bLabelTrueNegative = false;
    ////int iLabelTrueNegative = 0;
    //bLabelFalseNegative = false;
    ////int iLabelFalseNegative = 0;
    //int iExperimentPixelTN = 0;
    //int iExperimentPixelFN = 0;

    //for (int iY = 0; iY < m_lReduceROIHeight; iY++)
    //{
    //    for (int iX = 0; iX < m_lReduceROIWidth; iX++)
    //    {
    //        int iIndex = (iY * m_lReduceROIWidth * m_lOriginBitDepth) + (iX * m_lOriginBitDepth);
    //        if (
    //            m_pucFireExtractionOfTheColorFeatureImage[iIndex + 2] > 0 ||
    //            m_pucFireExtractionOfTheColorFeatureImage[iIndex + 1] > 0 ||
    //            m_pucFireExtractionOfTheColorFeatureImage[iIndex + 0] > 0
    //            )
    //        {
                /*************************************************************
                Intelligent Media Computing Laboratory, Sun Yat-Sen University
                Positive
                ==============================================================
                */
                //if ((iX >= 275 && iX <= 343) && (iY >= 6 && iY <= 242))
                //{
                //    if (bLabelFalsePositive == false)
                //    {
                //        bLabelFalsePositive = true;
                //        iLabelFalsePositive++;
                //    }
                //}
                //if ((iX >= 3 && iX <= 352) && (iY >= 232 && iY <= 273))
                //{
                //    if (bLabelFalsePositive == false)
                //    {
                //        bLabelFalsePositive = true;
                //        iLabelFalsePositive++;
                //    }
                //}
                //if (m_llFrameCount >= 477)
                //{
                //    if ((iX >= 110 && iX <= 278) && (iY >= 179 && iY <= 263))
                //    {
                //        if (bLabelFalsePositive == false)
                //        {
                //            bLabelFalsePositive = true;
                //            iLabelFalsePositive++;
                //        }
                //    }
                //}
                if (bLabelTruePositive == false)
                {
                    bLabelTruePositive = true;
                    iLabelTruePositive++;
                }

                /*************************************************************
                Intelligent Media Computing Laboratory, Sun Yat-Sen University
                Negative
                ==============================================================
                if (bLabelFalsePositive == false)
                {
                    bLabelFalsePositive = true;
                    iLabelFalsePositive++;
                }
                */
                /*********************************************
                National Institute of Standards and Technology
                Positive
                03_NIST_Burning Christmas tree (indoor).avi
                ==============================================
                if (m_llFrameCount > 90 & m_llFrameCount < 541)
                {
                    if (bLabelTruePositive == false)
                    {
                        bLabelTruePositive = true;
                        iLabelTruePositive++;
                    }
                }

                if (m_llFrameCount <= 90)
                {
                    if (bLabelFalsePositive == false)
                    {
                        bLabelFalsePositive = true;
                        iLabelFalsePositive++;
                    }
                }
                if (m_llFrameCount <= 350)
                {
                    if ((iX >= 414 && iX <= 719) && (iY >= 14 && iY <= 479))
                    {
                        if (bLabelFalsePositive == false)
                        {
                            bLabelFalsePositive = true;
                            iLabelFalsePositive++;
                        }
                    }
                }
                if (m_llFrameCount >= 541)
                {
                    if (bLabelFalsePositive == false)
                    {
                        bLabelFalsePositive = true;
                        iLabelFalsePositive++;
                    }
                }
                */
                /*********************************************
                National Institute of Standards and Technology
                Positive
                fire_indoor_10.avi
                ==============================================
                if (m_llFrameCount >= 697 & m_llFrameCount < 1142)
                {
                    if ((iX >= 111 && iX <= 280) && (iY >= 44 && iY <= 200))
                    {
                        if (bLabelTruePositive == false)
                        {
                            bLabelTruePositive = true;
                            iLabelTruePositive++;
                        }
                    }
                }
                if (m_llFrameCount >= 1142 & m_llFrameCount <= 2613)
                {
                    if (bLabelTruePositive == false)
                    {
                        bLabelTruePositive = true;
                        iLabelTruePositive++;
                    }
                }
                if (m_llFrameCount <= 1142)
                {
                    if ((iX >= 55 && iX <= 126) && (iY >= 155 && iY <= 253))
                    {
                        if (bLabelFalsePositive == false)
                        {
                            bLabelFalsePositive = true;
                            iLabelFalsePositive++;
                        }
                    }
                    if ((iX >= 253 && iX <= 351) && (iY >= 50 && iY <= 162))
                    {
                        if (bLabelFalsePositive == false)
                        {
                            bLabelFalsePositive = true;
                            iLabelFalsePositive++;
                        }
                    }
                }
                if (m_llFrameCount >= 2613)
                {
                    if (bLabelFalsePositive == false)
                    {
                        bLabelFalsePositive = true;
                        iLabelFalsePositive++;
                    }
                }
                */
                /*********************************************
                National Institute of Standards and Technology
                Positive
                fire_indoor_18.avi
                ==============================================
                if (m_llFrameCount > 20)
                {
                    if (bLabelTruePositive == false)
                    {
                        bLabelTruePositive = true;
                        iLabelTruePositive++;
                    }
                }
                if (m_llFrameCount <= 20)
                {
                    if (bLabelFalsePositive == false)
                    {
                        bLabelFalsePositive = true;
                        iLabelFalsePositive++;
                    }
                }
                if (m_llFrameCount > 0 && m_llFrameCount <= 2884)
                {
                    if ((iX >= 174 && iX <= 202) && (iY >= 116 && iY <= 147))
                    {
                        if (bLabelFalsePositive == false)
                        {
                            bLabelFalsePositive = true;
                            iLabelFalsePositive++;
                        }
                    }
                }
                if ((iX >= 40 && iX <= 96) && (iY >= 210 && iY <= 240))
                {
                    if (bLabelFalsePositive == false)
                    {
                        bLabelFalsePositive = true;
                        iLabelFalsePositive++;
                    }
                }
                */
                /******************
                Prof. A. Enis Cetin
                Positive
                forest1.wmv
                ===================
                if ((iX >= 51 && iX <= 367) && (iY >= 138 && iY <= 210))
                {
                    if (bLabelTruePositive == false)
                    {
                        bLabelTruePositive = true;
                        iLabelTruePositive++;
                    }
                }
                if ((iX >= 48 && iX <= 400) && (iY >= 42 && iY <= 130))
                {
                    if (bLabelFalsePositive == false)
                    {
                        bLabelFalsePositive = true;
                        iLabelFalsePositive++;
                    }
                }
                */
                /******************
                Prof. A. Enis Cetin
                Positive
                forest2.wmv
                ===================
                if ((iX >= 94 && iX <= 270) && (iY >= 79 && iY <= 213))
                {
                    if (bLabelTruePositive == false)
                    {
                        bLabelTruePositive = true;
                        iLabelTruePositive++;
                    }
                }
                if ((iX >= 291 && iX <= 395) && (iY >= 31 && iY <= 165))
                {
                    if (bLabelFalsePositive == false)
                    {
                        bLabelFalsePositive = true;
                        iLabelFalsePositive++;
                    }
                }
                */



            //}
            //else if (
            //    m_pucFireExtractionOfTheColorFeatureImage[iIndex + 2] == 0 &&
            //    m_pucFireExtractionOfTheColorFeatureImage[iIndex + 1] == 0 &&
            //    m_pucFireExtractionOfTheColorFeatureImage[iIndex + 0] == 0
            //    )
            //{
                /*********************************************
                National Institute of Standards and Technology
                Positive
                03_NIST_Burning Christmas tree (indoor).avi
                ==============================================
                iExperimentPixelFN++;
                if (
                    (m_llFrameCount <= 90) &&
                    iExperimentPixelFN >= (m_lReduceROIWidth * m_lReduceROIHeight)
                    )
                {
                    if (bLabelTrueNegative == false)
                    {
                        bLabelTrueNegative = true;
                        iLabelTrueNegative++;
                    }
                }
                if (
                    (m_llFrameCount >= 541) &&
                    iExperimentPixelFN >= (m_lReduceROIWidth * m_lReduceROIHeight)
                    )
                {
                    if (bLabelTrueNegative == false)
                    {
                        bLabelTrueNegative = true;
                        iLabelTrueNegative++;
                    }
                }

                if (
                    (m_llFrameCount > 90 & m_llFrameCount <= 2637) &&
                    iExperimentPixelFN >= (m_lReduceROIWidth * m_lReduceROIHeight)
                    )
                {
                    if (bLabelFalseNegative == false)
                    {
                        bLabelFalseNegative = true;
                        iLabelFalseNegative++;
                    }
                }
                */
                /*********************************************
                National Institute of Standards and Technology
                Positive
                fire_indoor_10.avi
                ==============================================
                if (m_llFrameCount <= 1142)
                {
                    if ((iX >= 55 && iX <= 126) && (iY >= 155 && iY <= 253))
                    {
                        if (bLabelTrueNegative == false)
                        {
                            bLabelTrueNegative = true;
                            iLabelTrueNegative++;
                        }
                    }
                    if ((iX >= 253 && iX <= 351) && (iY >= 50 && iY <= 162))
                    {
                        if (bLabelTrueNegative == false)
                        {
                            bLabelTrueNegative = true;
                            iLabelTrueNegative++;
                        }
                    }
                }
                iExperimentPixelFN++;
                if (
                    (m_llFrameCount >= 1142 & m_llFrameCount <= 2613) &&
                    iExperimentPixelFN >= (m_lReduceROIWidth * m_lReduceROIHeight)
                    )
                {
                    if (bLabelFalseNegative == false)
                    {
                        bLabelFalseNegative = true;
                        iLabelFalseNegative++;
                    }
                }
                */



    //        }
    //    }
    //}
    /*************************************************************
    Intelligent Media Computing Laboratory, Sun Yat-Sen University
    Negative
    ==============================================================
    int iExperimentPixelTP = 0;
    for (int iY = 0; iY < m_lReduceROIHeight; iY++)
    {
        for (int iX = 0; iX < m_lReduceROIWidth; iX++)
        {
            int iIndex = (iY * m_lReduceROIWidth * m_lOriginBitDepth) + (iX * m_lOriginBitDepth);
            if (
                m_pucFireExtractionOfTheColorFeatureImage[iIndex + 2] == 0 &&
                m_pucFireExtractionOfTheColorFeatureImage[iIndex + 1] == 0 &&
                m_pucFireExtractionOfTheColorFeatureImage[iIndex + 0] == 0
                )
            {
                iExperimentPixelTP++;
            }
        }
    }
    if (iExperimentPixelTP == (m_lReduceROIWidth * m_lReduceROIHeight))
    {
        iLabelTruePositive++;
    }
    */
    /*********************************************
    National Institute of Standards and Technology
    Positive
    fire_indoor_18.avi
    ==============================================
    int iExperimentPixelTN = 0;
    for (int iY = 116; iY <= 147; iY++)
    {
        for (int iX = 174; iX <= 202; iX++)
        {
            int iIndex = (iY * m_lReduceROIWidth * m_lOriginBitDepth) + (iX * m_lOriginBitDepth);
            if (m_llFrameCount > 0 && m_llFrameCount <= 2884)
            {
                if (
                    m_pucFireExtractionOfTheColorFeatureImage[iIndex + 2] == 0 &&
                    m_pucFireExtractionOfTheColorFeatureImage[iIndex + 1] == 0 &&
                    m_pucFireExtractionOfTheColorFeatureImage[iIndex + 0] == 0
                    )
                {
                    iExperimentPixelTN++;
                }
            }
        }
    }
    if (iExperimentPixelTN == ((147 - 116 + 1) * (202 - 174 + 1)))
    {
        bLabelTrueNegative = true;
        iLabelTrueNegative++;
    }
    if (bLabelTrueNegative = false)
    {
        iExperimentPixelTN = 0;
        for (int iY = 210; iY <= 240; iY++)
        {
            for (int iX = 40; iX <= 96; iX++)
            {
                int iIndex = (iY * m_lReduceROIWidth * m_lOriginBitDepth) + (iX * m_lOriginBitDepth);
                if (m_llFrameCount > 0 && m_llFrameCount <= 2884)
                {
                    if (
                        m_pucFireExtractionOfTheColorFeatureImage[iIndex + 2] == 0 &&
                        m_pucFireExtractionOfTheColorFeatureImage[iIndex + 1] == 0 &&
                        m_pucFireExtractionOfTheColorFeatureImage[iIndex + 0] == 0
                        )
                    {
                        iExperimentPixelTN++;
                    }
                }
            }
        }
        if (iExperimentPixelTN == ((240 - 210 + 1) * (96 - 40 + 1)))
        {
            bLabelTrueNegative = true;
            iLabelTrueNegative++;
        }
    }
    iExperimentPixelFN = 0;
    for (int iY = 0; iY <= 200; iY++)
    {
        for (int iX = 115; iX <= 147; iX++)
        {
            int iIndex = (iY * m_lReduceROIWidth * m_lOriginBitDepth) + (iX * m_lOriginBitDepth);
            if (m_llFrameCount > 20)
            {
                if (
                    m_pucFireExtractionOfTheColorFeatureImage[iIndex + 2] == 0 &&
                    m_pucFireExtractionOfTheColorFeatureImage[iIndex + 1] == 0 &&
                    m_pucFireExtractionOfTheColorFeatureImage[iIndex + 0] == 0
                    )
                {
                    iExperimentPixelFN++;
                }
            }
        }
    }
    if (iExperimentPixelFN == ((147 - 115 + 1) * (200 - 0 + 1)))
    {
        bLabelFalseNegative = true;
        iExperimentPixelFN++;
    }
    */
    /******************
    Prof. A. Enis Cetin
    Positive
    forest1.wmv
    ===================
    iExperimentPixelTN = 0;
    for (int iY = 42; iY <= 130; iY++)
    {
        for (int iX = 48; iX <= 400; iX++)
        {
            int iIndex = (iY * m_lReduceROIWidth * m_lOriginBitDepth) + (iX * m_lOriginBitDepth);
            if (m_llFrameCount > 0 && m_llFrameCount <= 2884)
            {
                if (
                    m_pucFireExtractionOfTheColorFeatureImage[iIndex + 2] == 0 &&
                    m_pucFireExtractionOfTheColorFeatureImage[iIndex + 1] == 0 &&
                    m_pucFireExtractionOfTheColorFeatureImage[iIndex + 0] == 0
                    )
                {
                    iExperimentPixelTN++;
                }
            }
        }
    }
    if (iExperimentPixelTN == ((400 - 48 + 1) * (130 - 42 + 1)))
    {
        bLabelTrueNegative = true;
        iLabelTrueNegative++;
    }
    iExperimentPixelFN = 0;
    for (int iY = 138; iY <= 210; iY++)
    {
        for (int iX = 51; iX <= 367; iX++)
        {
            int iIndex = (iY * m_lReduceROIWidth * m_lOriginBitDepth) + (iX * m_lOriginBitDepth);
            if (
                m_pucFireExtractionOfTheColorFeatureImage[iIndex + 2] == 0 &&
                m_pucFireExtractionOfTheColorFeatureImage[iIndex + 1] == 0 &&
                m_pucFireExtractionOfTheColorFeatureImage[iIndex + 0] == 0
                )
            {
                iExperimentPixelFN++;
            }
        }
    }
    if (iExperimentPixelFN == ((367 - 51 + 1) * (210 - 138 + 1)))
    {
        bLabelFalseNegative = true;
        iLabelFalseNegative++;
    }
    */
    /******************
    Prof. A. Enis Cetin
    Positive
    forest2.wmv
    ===================
    iExperimentPixelTN = 0;
    for (int iY = 31; iY <= 165; iY++)
    {
        for (int iX = 291; iX <= 395; iX++)
        {
            int iIndex = (iY * m_lReduceROIWidth * m_lOriginBitDepth) + (iX * m_lOriginBitDepth);
            if (m_llFrameCount > 0 && m_llFrameCount <= 2884)
            {
                if (
                    m_pucFireExtractionOfTheColorFeatureImage[iIndex + 2] == 0 &&
                    m_pucFireExtractionOfTheColorFeatureImage[iIndex + 1] == 0 &&
                    m_pucFireExtractionOfTheColorFeatureImage[iIndex + 0] == 0
                    )
                {
                    iExperimentPixelTN++;
                }
            }
        }
    }
    if (iExperimentPixelTN == ((395 - 291 + 1) * (165 - 31 + 1)))
    {
        bLabelTrueNegative = true;
        iLabelTrueNegative++;
    }
    iExperimentPixelFN = 0;
    for (int iY = 79; iY <= 213; iY++)
    {
        for (int iX = 94; iX <= 270; iX++)
        {
            int iIndex = (iY * m_lReduceROIWidth * m_lOriginBitDepth) + (iX * m_lOriginBitDepth);
            if (
                m_pucFireExtractionOfTheColorFeatureImage[iIndex + 2] == 0 &&
                m_pucFireExtractionOfTheColorFeatureImage[iIndex + 1] == 0 &&
                m_pucFireExtractionOfTheColorFeatureImage[iIndex + 0] == 0
                )
            {
                iExperimentPixelFN++;
            }
        }
    }
    if (iExperimentPixelFN == ((270 - 94 + 1) * (213 - 79 + 1)))
    {
        bLabelFalseNegative = true;
        iLabelFalseNegative++;
    }
    */




    //if (true)
    //{
    //    FILE *stream;
    //    char cLog[100];
    //    int numclosed;
    //    memset(&cLog, 0x00, 100 * sizeof(char));
    //    // Open for write
    //    if ((stream = fopen("Negative.txt", "w+")) != NULL)
    //    {
    //        sprintf(
    //            cLog,
    //            "TruePositive: %d, TrueNegative: %d, FalsePositive: %d, FalseNegative: %d \n",
    //            iLabelTruePositive,
    //            iLabelTrueNegative,
    //            iLabelFalsePositive,
    //            iLabelFalseNegative
    //        );
    //        fwrite(cLog, 1, sizeof(cLog), stream);
    //    }
    //    // Close stream if it is not NULL
    //    if (stream)
    //    {
    //        if (fclose(stream))
    //        {
    //            printf("The file 'crt_fopen.c' was not closed\n");
    //        }
    //    }
    //    // All other files are closed:
    //    numclosed = _fcloseall();
    //}

    //if (SobelFilter8Direction(
    //    m_pucReduceROI,
    //    m_lReduceROIWidth,
    //    m_lReduceROIHeight,
    //    m_lOriginBitDepth,
    //    m_pucSobelFilter
    //) == false)
    //{
    //    return false;
    //}

    //if (CombineImage(
    //    m_pucFireExtractionOfTheColorFeatureImage,
    //    m_pucContrastFilter,
    //    m_lReduceROIWidth,
    //    m_lReduceROIHeight,
    //    m_lOriginBitDepth,
    //    m_pucCombine
    //) == false)
    //{
    //    return false;
    //}


    //if (FrameFlame(
    //    m_pucCombine,
    //    m_pucReduceROI,
    //    m_lReduceROIWidth,
    //    m_lReduceROIHeight,
    //    m_lOriginBitDepth,
    //    m_pucFrameFlame
    //) == false)
    //{
    //    return false;
    //}

    //if (RGBtoHSVFrame(
    //    m_pucFrameFlame,
    //    m_pucReduceROI,
    //    m_lReduceROIWidth,
    //    m_lReduceROIHeight,
    //    m_lOriginBitDepth,
    //    m_piRGBtoYSH,
    //    m_pucRGBtoYSH
    //) == false)
    //{
    //    return false;
    //}


    if (ROItoReduceImage(
        m_pucDestinationImage,
        m_lReduceWidth,
        m_lReduceHeight,
        m_lOriginBitDepth,
        m_pucFireExtractionOfTheColorFeatureImage,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        m_lReduceROISX,
        m_lReduceROISY,
        m_lReduceROIEX,
        m_lReduceROIEY
    ) == false)
    {
        return false;
    }

    //if ( DoubleFrame (
    //    m_pucPixelWeightOpenClose,
    //    m_pucDoubleFrame1,
    //    m_pucDoubleFrame2,
    //    m_lReduceROIWidth,
    //    m_lReduceROIHeight,
    //    m_lOriginBitDepth,
    //    m_llFrameCount,
    //    m_pucDoubleFrame
    //    ) == false )
    //{
    //    return false;
    //}

    return true;
}


bool CAlgorithm::
AlgProcessing_BitDepth3()
{
    return true;
}


bool CAlgorithm::
AlgProcessing_BitDepth1()
{
    return true;
}


/************************************************************************/
/* private - Level 2                                                    */
/************************************************************************/


bool CAlgorithm::
GetROIRagne(
    unsigned char* pucInImage1,
    long lInOriginWidth,
    long lInOriginHeight,
    long lInOriginBitDepth,
    long lInROISX,
    long lInROIEX,
    long lInROISY,
    long lInROIEY,
    long lInROIWidth,
    long lInROIHeight,
    long lInROIBitDepth,
    unsigned char* pucOutImage1
)
{
    long lY = 0;
    long lX = 0;
    long lSrcIndex = 0;
    long lYY = 0;
    long lXX = 0;
    long lDstIndex = 0;
    long lROILength = lInROIWidth * lInROIHeight * lInROIBitDepth * sizeof(unsigned char);
    unsigned char ucR = 0;
    unsigned char ucG = 0;
    unsigned char ucB = 0;
    unsigned char ucY = 0;
    memset(pucOutImage1, 0x00, lROILength);
    for (lY = lInROISY; lY <= lInROIEY; lY++)
    {
        for (lX = lInROISX; lX <= lInROIEX; lX++)
        {
            lSrcIndex = (lY * lInOriginWidth * lInOriginBitDepth) + (lX * lInOriginBitDepth);
            lDstIndex = (lYY * lInROIWidth * lInROIBitDepth) + (lXX * lInROIBitDepth);
            if (lInOriginBitDepth == 4)
            {
                ucR = pucInImage1[lSrcIndex + 2];
                ucG = pucInImage1[lSrcIndex + 1];
                ucB = pucInImage1[lSrcIndex + 0];
                pucOutImage1[lDstIndex + 3] = ucR;
                pucOutImage1[lDstIndex + 2] = ucR;
                pucOutImage1[lDstIndex + 1] = ucG;
                pucOutImage1[lDstIndex + 0] = ucB;
            }
            else if (lInOriginBitDepth == 3)
            {
                ucR = pucInImage1[lSrcIndex + 2];
                ucG = pucInImage1[lSrcIndex + 1];
                ucB = pucInImage1[lSrcIndex + 0];
                pucOutImage1[lDstIndex + 2] = ucR;
                pucOutImage1[lDstIndex + 1] = ucG;
                pucOutImage1[lDstIndex + 0] = ucB;
            }
            else if (lInOriginBitDepth == 1)
            {
                ucY = pucInImage1[lSrcIndex];
                pucOutImage1[lDstIndex] = ucY;
            }
            lXX++;
        }
        lYY++;
        lXX = 0;
    }
    return true;
}



bool CAlgorithm::
ReduceImage(
    unsigned char* pInImage,
    int iInWidth,
    int iInHeight,
    int iInBitDepth,
    unsigned char* pOutImage,
    int iInReduceWidth,
    int iInReduceHeight,
    int iInReduceBitDepth
)
{
    long lSourceIndex = 0;
    long lDestinationIndex = 0;
    int iY = 0;
    int iX = 0;
    int iWidth = iInWidth;
    int iHeight = iInHeight;
    int iBitDepth = iInBitDepth;
    int iReduceWidth = iInReduceWidth;
    int iReduceHeight = iInReduceHeight;
    int iReduceBitDepth = iInReduceBitDepth;
    int iYY = 0;
    int iXX = 0;
    double dbXRate = double(iReduceWidth) / double(iWidth);
    double dbYRate = double(iReduceHeight) / double(iHeight);
    for (iY = 0; iY < iHeight; iY++)
    {
        iYY = int(iY * dbYRate);
        for (iX = 0; iX < iWidth; iX++)
        {
            iXX = int(iX * dbXRate);
            lSourceIndex = long((iY * iBitDepth) * iWidth) +
                long(iX * iBitDepth);
            lDestinationIndex = long((double(iYY * iBitDepth)) * iReduceWidth) +
                long((iXX * iBitDepth));
            switch (iReduceBitDepth)
            {
            case 4:
                pOutImage[lDestinationIndex + 3] = pInImage[lSourceIndex + 3];
                pOutImage[lDestinationIndex + 2] = pInImage[lSourceIndex + 2];
                pOutImage[lDestinationIndex + 1] = pInImage[lSourceIndex + 1];
                pOutImage[lDestinationIndex + 0] = pInImage[lSourceIndex + 0];
                break;
            case 3:
                pOutImage[lDestinationIndex + 2] = pInImage[lSourceIndex + 2];
                pOutImage[lDestinationIndex + 1] = pInImage[lSourceIndex + 1];
                pOutImage[lDestinationIndex + 0] = pInImage[lSourceIndex + 0];
                break;
            case 1:
                pOutImage[lDestinationIndex + 0] = pInImage[lSourceIndex + 0];
                break;
            default:
                return false;
            }
        }
    }
    return true;
}


bool CAlgorithm::
    FireExtractionOfTheColorFeatureImage(
    unsigned char* pInImage,
    int iInWidth,
    int iInHeight,
    int iInBitDepth,
    unsigned char* pOutImage
)
{
    long lSourceIndex = 0;
    int iY = 0;
    int iX = 0;
    int iWidth = iInWidth;
    int iHeight = iInHeight;
    int iBitDepth = iInBitDepth;
    int iRGB_R = 0;
    int iRGB_G = 0;
    int iRGB_B = 0;
    memset(pOutImage, 0x00, iWidth * iHeight * iBitDepth * sizeof(unsigned char));
    for (iY = 0; iY < iHeight; iY++)
    {
        for (iX = 0; iX < iWidth; iX++)
        {
            lSourceIndex = long((iY * iBitDepth) * iWidth) +
                long(iX * iBitDepth);
            switch (iBitDepth)
            {
            case 4:
                iRGB_R = pInImage[lSourceIndex + 2];
                iRGB_G = pInImage[lSourceIndex + 1];
                iRGB_B = pInImage[lSourceIndex + 0];
                if (
                    (iRGB_R <= 255 && iRGB_R >= 117) &&
                    (iRGB_G <= 255 && iRGB_G >= 88) &&
                    (iRGB_B <= 255 && iRGB_B >= 44)
                    )
                {
                    if (
                        (iRGB_R == 255) &&
                        (iRGB_G <= 255 && iRGB_G >= 183) &&
                        (iRGB_B <= 219 && iRGB_B >= 15)
                        )
                    {
                        pOutImage[lSourceIndex + 3] = 0;
                        pOutImage[lSourceIndex + 2] = pInImage[lSourceIndex + 2];
                        pOutImage[lSourceIndex + 1] = pInImage[lSourceIndex + 1];
                        pOutImage[lSourceIndex + 0] = pInImage[lSourceIndex + 0];
                    }
                    if (
                        (iRGB_R <= 254 && iRGB_R >= 250) &&
                        (iRGB_G == 255) &&
                        (iRGB_B <= 219 && iRGB_B >= 15)
                        )
                    {
                        pOutImage[lSourceIndex + 3] = 0;
                        pOutImage[lSourceIndex + 2] = pInImage[lSourceIndex + 2];
                        pOutImage[lSourceIndex + 1] = pInImage[lSourceIndex + 1];
                        pOutImage[lSourceIndex + 0] = pInImage[lSourceIndex + 0];
                    }
                }
                break;
            case 3:
                iRGB_R = pInImage[lSourceIndex + 2];
                iRGB_G = pInImage[lSourceIndex + 1];
                iRGB_B = pInImage[lSourceIndex + 0];
                if (
                    (iRGB_R <= 255 && iRGB_R >= 117) &&
                    (iRGB_G <= 255 && iRGB_G >= 88) &&
                    (iRGB_B <= 255 && iRGB_B >= 44)
                    )
                {
                    if (
                        (iRGB_R == 255) &&
                        (iRGB_G <= 255 && iRGB_G >= 183) &&
                        (iRGB_B <= 219 && iRGB_B >= 15)
                        )
                    {
                        pOutImage[lSourceIndex + 2] = pInImage[lSourceIndex + 2];
                        pOutImage[lSourceIndex + 1] = pInImage[lSourceIndex + 1];
                        pOutImage[lSourceIndex + 0] = pInImage[lSourceIndex + 0];
                    }
                    if (
                        (iRGB_R <= 254 && iRGB_R >= 250) &&
                        (iRGB_G == 255) &&
                        (iRGB_B <= 219 && iRGB_B >= 15)
                        )
                    {
                        pOutImage[lSourceIndex + 2] = pInImage[lSourceIndex + 2];
                        pOutImage[lSourceIndex + 1] = pInImage[lSourceIndex + 1];
                        pOutImage[lSourceIndex + 0] = pInImage[lSourceIndex + 0];
                    }
                }
                break;
            case 1:
                return false;
                break;
            default:
                return false;
            }
        }
    }
    return true;
}


bool CAlgorithm::
SobelFilter8Direction(
    unsigned char* pInImage,
    int iInWidth,
    int iInHeight,
    int iInBitDepth,
    unsigned char* pOutSF
)
{
    long lIndex = 0;
    int iY = 0;
    int iX = 0;
    int iWidth = iInWidth;
    int iHeight = iInHeight;
    int iBitDepth = iInBitDepth;
    int iYY = 0;
    int iXX = 0;
    int iHMD[3][3] =
    {
        { -1, -2, -1 },
        {  0,  0,  0 },
        {  1,  2,  1 }
    };
    int iHMU[3][3] =
    {
        {  1,  2,  1 },
        {  0,  0,  0 },
        { -1, -2, -1 }
    };
    int iVMR[3][3] =
    {
        { -1,  0,  1 },
        { -2,  0,  2 },
        { -1,  0,  1 }
    };
    int iVML[3][3] =
    {
        { 1,  0, -1 },
        { 2,  0, -2 },
        { 1,  0, -1 }
    };
    int iRMT[3][3] =
    {
        { -2, -1,  0 },
        { -1,  0,  1 },
        {  0,  1,  2 }
    };
    int iRMB[3][3] =
    {
        {  0,  1,  2 },
        { -1,  0,  1 },
        { -2, -1,  0 }
    };
    int iLMT[3][3] =
    {
        { 0, -1, -2 },
        { 1,  0, -1 },
        { 2,  1,  0 }
    };
    int iLMB[3][3] =
    {
        { 2,  1,  0 },
        { 1,  0, -1 },
        { 0, -1, -2 }
    };
    int iPSHDY = 0;
    int iPSHDU = 0;
    int iPSHDV = 0;
    int iPSHUY = 0;
    int iPSHUU = 0;
    int iPSHUV = 0;
    int iPSVRY = 0;
    int iPSVRU = 0;
    int iPSVRV = 0;
    int iPSVLY = 0;
    int iPSVLU = 0;
    int iPSVLV = 0;
    int iPSRTY = 0;
    int iPSRTU = 0;
    int iPSRTV = 0;
    int iPSRBY = 0;
    int iPSRBU = 0;
    int iPSRBV = 0;
    int iPSLTY = 0;
    int iPSLTU = 0;
    int iPSLTV = 0;
    int iPSLBY = 0;
    int iPSLBU = 0;
    int iPSLBV = 0;
    long lRangeIndex = 0;
    int iRange = 1;
    int iPMV = 0;
    int iPMU = 0;
    int iPMY = 0;
    for (iY = 0 + iRange; iY < iHeight - iRange; iY++)
    {
        for (iX = 0 + iRange; iX < iWidth - iRange; iX++)
        {
            iPSHUY = 0;
            iPSHUU = 0;
            iPSHUV = 0;
            iPSHDY = 0;
            iPSHDU = 0;
            iPSHDV = 0;
            iPSVRY = 0;
            iPSVRU = 0;
            iPSVRV = 0;
            iPSVLY = 0;
            iPSVLU = 0;
            iPSVLV = 0;
            iPSRTY = 0;
            iPSRTU = 0;
            iPSRTV = 0;
            iPSRBY = 0;
            iPSRBU = 0;
            iPSRBV = 0;
            iPSLTY = 0;
            iPSLTU = 0;
            iPSLTV = 0;
            iPSLBY = 0;
            iPSLBU = 0;
            iPSLBV = 0;
            lIndex = (iY * iWidth * iBitDepth) + (iX * iBitDepth);
            for (iYY = -(iRange); iYY <= iRange; iYY++)
            {
                for (iXX = -(iRange); iXX <= iRange; iXX++)
                {
                    lRangeIndex = ((iY + iYY) * iWidth * iBitDepth) +
                        ((iX + iXX) * iBitDepth);
                    iPSHDY +=
                        pInImage[lRangeIndex + 2] *
                        (iHMD[iYY + iRange][iXX + iRange]);
                    iPSHDU +=
                        pInImage[lRangeIndex + 1] *
                        (iHMD[iYY + iRange][iXX + iRange]);
                    iPSHDV +=
                        pInImage[lRangeIndex + 0] *
                        (iHMD[iYY + iRange][iXX + iRange]);
                    iPSHUY +=
                        pInImage[lRangeIndex + 2] *
                        (iHMU[iYY + iRange][iXX + iRange]);
                    iPSHUU +=
                        pInImage[lRangeIndex + 1] *
                        (iHMU[iYY + iRange][iXX + iRange]);
                    iPSHUV +=
                        pInImage[lRangeIndex + 0] *
                        (iHMU[iYY + iRange][iXX + iRange]);
                    iPSVRY +=
                        pInImage[lRangeIndex + 2] *
                        (iVMR[iYY + iRange][iXX + iRange]);
                    iPSVRU +=
                        pInImage[lRangeIndex + 1] *
                        (iVMR[iYY + iRange][iXX + iRange]);
                    iPSVRV +=
                        pInImage[lRangeIndex + 0] *
                        (iVMR[iYY + iRange][iXX + iRange]);
                    iPSVLY +=
                        pInImage[lRangeIndex + 2] *
                        (iVML[iYY + iRange][iXX + iRange]);
                    iPSVLU +=
                        pInImage[lRangeIndex + 1] *
                        (iVML[iYY + iRange][iXX + iRange]);
                    iPSVLV +=
                        pInImage[lRangeIndex + 0] *
                        (iVML[iYY + iRange][iXX + iRange]);
                    iPSRTY +=
                        pInImage[lRangeIndex + 2] *
                        (iRMT[iYY + iRange][iXX + iRange]);
                    iPSRTU +=
                        pInImage[lRangeIndex + 1] *
                        (iRMT[iYY + iRange][iXX + iRange]);
                    iPSRTV +=
                        pInImage[lRangeIndex + 0] *
                        (iRMT[iYY + iRange][iXX + iRange]);
                    iPSRBY +=
                        pInImage[lRangeIndex + 2] *
                        (iRMB[iYY + iRange][iXX + iRange]);
                    iPSRBU +=
                        pInImage[lRangeIndex + 1] *
                        (iRMB[iYY + iRange][iXX + iRange]);
                    iPSRBV +=
                        pInImage[lRangeIndex + 0] *
                        (iRMB[iYY + iRange][iXX + iRange]);
                    iPSLTY +=
                        pInImage[lRangeIndex + 2] *
                        (iLMT[iYY + iRange][iXX + iRange]);
                    iPSLTU +=
                        pInImage[lRangeIndex + 1] *
                        (iLMT[iYY + iRange][iXX + iRange]);
                    iPSLTV +=
                        pInImage[lRangeIndex + 0] *
                        (iLMT[iYY + iRange][iXX + iRange]);
                    iPSLBY +=
                        pInImage[lRangeIndex + 2] *
                        (iLMB[iYY + iRange][iXX + iRange]);
                    iPSLBU +=
                        pInImage[lRangeIndex + 1] *
                        (iLMB[iYY + iRange][iXX + iRange]);
                    iPSLBV +=
                        pInImage[lRangeIndex + 0] *
                        (iLMB[iYY + iRange][iXX + iRange]);
                }
            }
            iPMY = max(max(max(max(max(max(max(iPSHDY, iPSVRY), iPSVLY), iPSHUY), iPSRTY), iPSRBY), iPSLTY), iPSLBY);
            if (iPMY > 255) { iPMY = 255; }
            if (iPMY < 0) { iPMY = 0; }
            iPMU = max(max(max(max(max(max(max(iPSHDU, iPSVRU), iPSVLU), iPSHUU), iPSRTU), iPSRBU), iPSLTU), iPSLBU);
            if (iPMU > 255) { iPMU = 255; }
            if (iPMU < 0) { iPMU = 0; }
            iPMV = max(max(max(max(max(max(max(iPSHDV, iPSVRV), iPSVLV), iPSHUV), iPSRTV), iPSRBV), iPSLTV), iPSLBV);
            if (iPMV > 255) { iPMV = 255; }
            if (iPMV < 0) { iPMV = 0; }
            int iPX = ((iPMY)+(iPMU)+(iPMV)) / 3;
            if (iPX >= 255) { iPX = 255; }
            if (iPX <= 0) { iPX = 0; }
            lIndex = (iY * iWidth * iBitDepth) + (iX * iBitDepth);
            pOutSF[lIndex + 2] = unsigned char(iPX);
            pOutSF[lIndex + 1] = unsigned char(iPX);
            pOutSF[lIndex + 0] = unsigned char(iPX);
        }
    }
    return true;
}


bool CAlgorithm::
CombineImage(
    BYTE* PointByte_Image1,
    BYTE* PointByte_Image2,
    INT iInWidth,
    INT iInHeight,
    INT iInBitDepth,
    BYTE* PointByte_CombineImage
)
{
    int iPixel1A = 0;
    int iPixel1B = 0;
    int iPixel1C = 0;
    int iPixel2A = 0;
    int iPixel2B = 0;
    int iPixel2C = 0;
    int iPixelA = 0;
    int iPixelB = 0;
    int iPixelC = 0;
    for (int iY = 0; iY < iInHeight; iY++)
    {
        for (int iX = 0; iX < iInWidth; iX++)
        {
            int iIndex = (iY * iInWidth * iInBitDepth) + (iX * iInBitDepth);
            if (PointByte_Image1 != NULL)
            {
                iPixel1A = PointByte_Image1[iIndex + 2];
                iPixel1B = PointByte_Image1[iIndex + 1];
                iPixel1C = PointByte_Image1[iIndex + 0];
            }
            if (PointByte_Image2 != NULL)
            {
                iPixel2A = PointByte_Image2[iIndex + 2];
                iPixel2B = PointByte_Image2[iIndex + 1];
                iPixel2C = PointByte_Image2[iIndex + 0];
            }
            iPixelA = iPixel1A + iPixel2A >= 255 ? 255 : iPixel1A + iPixel2A;
            PointByte_CombineImage[iIndex + 2] = iPixelA;
            PointByte_CombineImage[iIndex + 1] = iPixelA;
            PointByte_CombineImage[iIndex + 0] = iPixelA;
        }
    }
    return true;
}


bool CAlgorithm::
BinaryUsingThreshold(
    unsigned char* pucInImage,
    long lInWidth,
    long lInHeight,
    long lInBitDepth,
    long lInThreshold,
    unsigned char* pucOutImage
)
{
    long lIndexImage = 0;
    memset(pucOutImage, 0x00, lInWidth * lInHeight * lInBitDepth);

    for (INT iY = 0; iY < lInHeight; iY++)
    {
        for (INT iX = 0; iX < lInWidth; iX++)
        {
            lIndexImage = (iY * lInWidth * lInBitDepth) + (iX * lInBitDepth);
            if (pucInImage[lIndexImage + 0] > lInThreshold)
            {
                pucOutImage[lIndexImage + 2] = 255;
                pucOutImage[lIndexImage + 1] = 255;
                pucOutImage[lIndexImage + 0] = 255;
            }
        }
    }
    return true;
}



bool CAlgorithm::
OTSUThreshold(
    unsigned char* pucInImage1,
    long lInWidth,
    long lInHeight,
    long lInBitDepth,
    long& lOutThreshold,
    unsigned char* pucOutImage1
)
{
    int width = lInWidth;
    int height = lInHeight;
    int pixelCount[256];
    float pixelPro[256];
    int i = 0;
    int j = 0;
    int pixelSum = width * height;
    int threshold = 0;
    unsigned char* data = pucInImage1;

    for (i = 0; i < 256; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            long lIndex = (i * width * lInBitDepth) + (j * lInBitDepth);
            pixelCount[(int)data[lIndex + 0]]++;
        }
    }


    for (i = 0; i < 256; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
    }


    float w0, w1, u0tmp, u1tmp, u0, u1, u,
        deltaTmp, deltaMax = 0;
    for (i = 0; i < 256; i++)
    {
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = 0; j < 256; j++)
        {
            if (j <= i)
            {
                w0 += pixelPro[j];
                u0tmp += j * pixelPro[j];
            }
            else
            {
                w1 += pixelPro[j];
                u1tmp += j * pixelPro[j];
            }
        }
        u0 = u0tmp / w0;
        u1 = u1tmp / w1;
        u = u0tmp + u1tmp;
        deltaTmp =
            w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
        if (deltaTmp > deltaMax)
        {
            deltaMax = deltaTmp;
            threshold = i;
        }
    }
    lOutThreshold = threshold;
    for (int iY = 0; iY < height; iY++)
    {
        for (int iX = 0; iX < width; iX++)
        {
            long lIndex = (iY * width * lInBitDepth) + (iX * lInBitDepth);
            int iPixel = pucInImage1[lIndex + 0];
            if (iPixel >= threshold)
            {
                pucOutImage1[lIndex + 2] = 255;
                pucOutImage1[lIndex + 1] = 255;
                pucOutImage1[lIndex + 0] = 255;
            }
            else
            {
                pucOutImage1[lIndex + 2] = 0;
                pucOutImage1[lIndex + 1] = 0;
                pucOutImage1[lIndex + 0] = 0;
            }
        }
    }
    return true;
}



bool CAlgorithm::
ROItoReduceImage(
    unsigned char* pucInOutImage1,
    long lInReduceWidth,
    long lInReduceHeight,
    long lInBitDepth,
    unsigned char* pucInImage2,
    long lInReduceROIWidth,
    long lInReduceROIHeight,
    long lInReduceROISX,
    long lInReduceROISY,
    long lInReduceROIEX,
    long lInReduceROIEY
)
{
    memset(pucInOutImage1, 0x00, lInReduceWidth * lInReduceHeight * lInBitDepth);
    long lY = 0;
    long lX = 0;
    long lIndex = 0;
    long lYY = 0;
    long lXX = 0;
    long lIndexROI = 0;
    for (lY = lInReduceROISY; lY <= lInReduceROIEY; lY++)
    {
        for (lX = lInReduceROISX; lX <= lInReduceROIEX; lX++)
        {
            lIndex = (lY * lInReduceWidth * lInBitDepth) + (lX * lInBitDepth);
            lIndexROI = (lYY * lInReduceROIWidth * lInBitDepth) + (lXX * lInBitDepth);
            pucInOutImage1[lIndex + 2] = pucInImage2[lIndexROI + 2];
            pucInOutImage1[lIndex + 1] = pucInImage2[lIndexROI + 1];
            pucInOutImage1[lIndex + 0] = pucInImage2[lIndexROI + 0];
            lXX++;
        }
        lXX = 0;
        lYY++;
    }
    return true;
}



bool CAlgorithm::
FrameFlame(
    unsigned char* pucInImage1,
    unsigned char* pucInImage2,
    long lInReduceWidth,
    long lInReduceHeight,
    long lInBitDepth,
    unsigned char* pucOutImage1
)
{
    if ((!pucOutImage1) || (pucOutImage1 == NULL)) { return false; }
    long lFrameIndex = 0;
    long lY = 0;
    long lX = 0;
    long lIndex = 0;
    double dbYCbCr_Y = 0.0f;
    double dbYCbCr_Cb = 0.0f;
    double dbYCbCr_Cr = 0.0f;
    long lRGB_R = 0;
    long lRGB_G = 0;
    long lRGB_B = 0;
    double dbDiff1 = 0.0f;
    double dbDiff2 = 0.0f;
    for (lY = 0; lY < lInReduceHeight; lY++)
    {
        for (lX = 0; lX < lInReduceWidth; lX++)
        {
            lIndex = (lY * lInReduceWidth * lInBitDepth) + (lX * lInBitDepth);

            lRGB_R = pucInImage2[lIndex + 2];
            lRGB_G = pucInImage2[lIndex + 1];
            lRGB_B = pucInImage2[lIndex + 0];
            dbYCbCr_Y = 0.0f + (0.299f * lRGB_R) + (0.587f * lRGB_G) + (0.114f * lRGB_B);
            dbYCbCr_Cb = 128 - (0.168736f * lRGB_R) - (0.331264f * lRGB_G) + (0.5f * lRGB_B);
            dbYCbCr_Cr = 128 + (0.5f * lRGB_R) - (0.418688f * lRGB_G) - (0.081312f * lRGB_B);
            dbDiff1 = dbYCbCr_Y - dbYCbCr_Cb;
            dbDiff2 = dbYCbCr_Cr - dbYCbCr_Cb;

            if (
                ((lRGB_R > lRGB_G) || (lRGB_R > lRGB_B)) &&
                ((dbDiff1 >= 20.0f) && (dbDiff2 >= 10.0f))
                )
            {
                //                 char clog[255];
                //                 sprintf_s ( clog, "d1:%03f, d2:%03f\n", d1, d2 );
                //                 OutputDebugString(clog);
                pucOutImage1[lIndex + 2] = pucInImage2[lIndex + 2];
                pucOutImage1[lIndex + 1] = pucInImage2[lIndex + 1];
                pucOutImage1[lIndex + 0] = pucInImage2[lIndex + 0];
            }
            else
            {
                pucOutImage1[lIndex + 2] = 0;
                pucOutImage1[lIndex + 1] = 0;
                pucOutImage1[lIndex + 0] = 0;
            }
        }
    }

    return true;
}


bool CAlgorithm::
DoubleFrame(
    unsigned char* pucInImage1,
    unsigned char* pucInImage2,
    unsigned char* pucInImage3,
    long lInReduceWidth,
    long lInReduceHeight,
    long lInBitDepth,
    long long llInFrameCount,
    unsigned char* pucOutImage1
)
{
    if ((!pucOutImage1) || (pucOutImage1 == NULL)) { return false; }
    long lFrameIndex = 0;
    long lY = 0;
    long lX = 0;
    long lIndex = 0;
    lFrameIndex = ((llInFrameCount - 1) % 2) + 1;
    if (lFrameIndex == 1)
    {
        memcpy(pucInImage2, pucInImage1, lInReduceWidth * lInReduceHeight * lInBitDepth * sizeof(BYTE));
    }
    else if (lFrameIndex == 2)
    {
        memcpy(pucInImage3, pucInImage1, lInReduceWidth * lInReduceHeight * lInBitDepth * sizeof(BYTE));
    }
    if (llInFrameCount <= 2)
    {
        return false;
    }
    memset(pucOutImage1, 0x00, lInReduceWidth * lInReduceHeight * lInBitDepth * sizeof(BYTE));
    for (lY = 0; lY < lInReduceHeight; lY++)
    {
        for (lX = 0; lX < lInReduceWidth; lX++)
        {
            lIndex = (lY * lInReduceWidth * lInBitDepth) + (lX * lInBitDepth);
            if (
                pucInImage2[lIndex + 2] == 255 &&
                pucInImage2[lIndex + 1] == 255 &&
                pucInImage2[lIndex + 0] == 255 &&
                pucInImage3[lIndex + 2] == 255 &&
                pucInImage3[lIndex + 1] == 255 &&
                pucInImage3[lIndex + 0] == 255
                )
            {
                pucOutImage1[lIndex + 2] = 255;
                pucOutImage1[lIndex + 1] = 255;
                pucOutImage1[lIndex + 0] = 255;
            }
        }
    }
    return true;
}


bool CAlgorithm::
RGBtoHSVFrame(
    unsigned char* pucInImage1,
    unsigned char* pucInImage2,
    long lInReduceWidth,
    long lInReduceHeight,
    long lInBitDepth,
    int* piOutImage1,
    unsigned char* pucOutImage1
)
{
    int    lY, lX;
    double r, g, b, y, cb, cr, s, h;
    long lIndex = 0;
    rgb RGBIn;
    hsv HSVOut;
    hsi HSIOut;
    memset(piOutImage1, 0x00, lInReduceWidth * lInReduceHeight * lInBitDepth * sizeof(int));
    memset(pucOutImage1, 0x00, lInReduceWidth * lInReduceHeight * lInBitDepth);
    for (lY = 0; lY < lInReduceHeight; lY++)
    {
        for (lX = 0; lX < lInReduceWidth; lX++)
        {
            lIndex = (lY * lInReduceWidth * lInBitDepth) + (lX * lInBitDepth);
            if (pucInImage1[lIndex + 2] == 255)
            {
                RGBIn.r = pucInImage1[lIndex + 2];
                RGBIn.g = pucInImage1[lIndex + 1];
                RGBIn.b = pucInImage1[lIndex + 0];
                HSVOut = rgb2hsv(RGBIn);
                //RGBtoHSV ( RGBIn.r, RGBIn.g, RGBIn.b, &HSVOut.h, &HSVOut.s, &HSVOut.v );
                //HSI ( RGBIn.r, RGBIn.g, RGBIn.b, HSIOut.h, HSIOut.s, HSIOut.v );
                if (
                    (HSVOut.h >= 0 && HSVOut.h <= 60)
                    )
                {
                    piOutImage1[lIndex + 2] = (int)HSVOut.h;
                    piOutImage1[lIndex + 1] = (int)HSVOut.s;
                    piOutImage1[lIndex + 0] = (int)HSVOut.v;
                    pucOutImage1[lIndex + 2] = pucInImage2[lIndex + 2];
                    pucOutImage1[lIndex + 1] = pucInImage2[lIndex + 1];
                    pucOutImage1[lIndex + 0] = pucInImage2[lIndex + 0];
                }
            }
        }
    }
    return true;
}



hsv rgb2hsv(rgb in)
{
    hsv         out;
    double      min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min < in.b ? min : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max > in.b ? max : in.b;

    out.v = max;                                // v
    delta = max - min;
    if (max > 0.0) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);                  // s
    }
    else {
        // if max is 0, then r = g = b = 0              
        // s = 0, v is undefined
        out.s = 0.0;
        out.h = NAN;                            // its now undefined
        return out;
    }
    if (in.r >= max)                           // > is bogus, just keeps compilor happy
        out.h = (in.g - in.b) / delta;        // between yellow & magenta
    else
        if (in.g >= max)
            out.h = 2.0 + (in.b - in.r) / delta;  // between cyan & yellow
        else
            out.h = 4.0 + (in.r - in.g) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if (out.h < 0.0)
        out.h += 360.0;

    return out;
}

void RGBtoHSV(float r, float g, float b, float *h, float *s, float *v)
{
    float fmin, fmax, delta;
    fmin = min(min(r, g), b);
    fmax = max(max(r, g), b);
    *v = fmax;				// v
    delta = fmax - fmin;
    if (fmax != 0)
        *s = delta / fmax;		// s
    else {
        // r = g = b = 0		// s = 0, v is undefined
        *s = 0;
        *h = -1;
        return;
    }
    if (r == fmax)
        *h = (g - b) / delta;		// between yellow & magenta
    else if (g == fmax)
        *h = 2 + (b - r) / delta;	// between cyan & yellow
    else
        *h = 4 + (r - g) / delta;	// between magenta & cyan
    *h *= 60;				// degrees
    if (*h < 0)
        *h += 360;
}


void HSI(
    IN unsigned int r,
    IN unsigned int g,
    IN unsigned int b,
    OUT double &Hue,
    OUT double &Saturation,
    OUT double &Intensity
)
{
    unsigned int nImax, nImin, nSum, nDifference;
    if ((r < 0 && g < 0 && b < 0) || (r > 255 || g > 255 || b > 255))
    {
        Hue = Saturation = Intensity = 0;
        return;
    }

    if (g == b)
    {
        if (b < 255)
        {
            b = b + 1;
        }
        else
        {
            b = b - 1;
        }
    }

    nImax = _Max(r, b);
    nImax = _Max(nImax, g);
    nImin = _Min(r, b);
    nImin = _Min(nImin, g);
    nSum = nImin + nImax;
    nDifference = nImax - nImin;

    Intensity = (float)nSum / 2;

    if (Intensity < 128)
    {
        Saturation = (255 * ((float)nDifference / nSum));
    }
    else
    {
        Saturation = (float)(255 * ((float)nDifference / (510 - nSum)));
    }

    if (Saturation != 0)
    {
        if (nImax == r)
        {
            Hue = (60 * ((float)g - (float)b) / nDifference);
        }
        else if (nImax == g)
        {
            Hue = (60 * ((float)b - (float)r) / nDifference + 120);
        }
        else if (nImax == b)
        {
            Hue = (60 * ((float)r - (float)g) / nDifference + 240);
        }

        if (Hue < 0)
        {
            Hue = (60 * ((float)b - (float)r) / nDifference + 120);
        }
    }
    else
    {
        Hue = -1;
    }

    return;
}


rgb hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if (in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if (hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch (i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;
}


void HSVtoRGB(float *r, float *g, float *b, float h, float s, float v)
{
    int i;
    float f, p, q, t;
    if (s == 0) {
        // achromatic (grey)
        *r = *g = *b = v;
        return;
    }
    h /= 60;			// sector 0 to 5
    i = floor(h);
    f = h - i;			// factorial part of h
    p = v * (1 - s);
    q = v * (1 - s * f);
    t = v * (1 - s * (1 - f));
    switch (i) {
    case 0:
        *r = v;
        *g = t;
        *b = p;
        break;
    case 1:
        *r = q;
        *g = v;
        *b = p;
        break;
    case 2:
        *r = p;
        *g = v;
        *b = t;
        break;
    case 3:
        *r = p;
        *g = q;
        *b = v;
        break;
    case 4:
        *r = t;
        *g = p;
        *b = v;
        break;
    default:		// case 5:
        *r = v;
        *g = p;
        *b = q;
        break;
    }
}

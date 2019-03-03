#pragma once

#include "StdAfx.h"
#include "CommonStructure.h"
#include <vector>

using namespace std;

class CAlgorithm
{
public:
    CAlgorithm();
    ~CAlgorithm();

    bool AlgInit(
        void* _IN_ pstInInitParameter
    );
    bool AlgRelease();
    bool AlgInput(
        unsigned char* _IN_ pucInData,
        long _IN_ lInWidth,
        long _IN_ lInHeight,
        long _IN_ lInBitDepth,
        void* _IN_ pstInInputParameter,
        void* _IN_ pInReserve
    );
    bool AlgProcessing(
        void* _IN_ pInReserve,
        void* _OUT_ pOutReserve
    );
    bool AlgOutput(
        unsigned char* _OUT_ pucOutData1,
        unsigned char* _OUT_ pucOutData2,
        double* _OUT_ dbOutTimeDiff,
        void* _OUT_ pstOutputParameter,
        void* _OUT_ pOutReserve
    );

protected:
private:
    bool AlgProcessing_BitDepth4();
    bool AlgProcessing_BitDepth3();
    bool AlgProcessing_BitDepth1();

private:

    bool GetROIRagne(
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
    );

    bool ReduceImage(
        unsigned char* pInImage,
        int iInWidth,
        int iInHeight,
        int iInBitDepth,
        unsigned char* pOutImage,
        int iInReduceWidth,
        int iInReduceHeight,
        int iInReduceBitDepth
    );

    bool FireExtractionOfTheColorFeatureImage(
        unsigned char* pInImage,
        int iInWidth,
        int iInHeight,
        int iInBitDepth,
        unsigned char* pOutImage
    );

    bool SobelFilter8Direction(
        unsigned char* pInImage,
        int iInWidth,
        int iInHeight,
        int iInBitDepth,
        unsigned char* pOutSF
    );

    bool BinaryUsingThreshold(
        unsigned char* pucInImage,
        long lInWidth,
        long lInHeight,
        long lInBitDepth,
        long lInThreshold,
        unsigned char* pucOutImage
    );

    bool CombineImage(
        BYTE* PointByte_Image1,
        BYTE* PointByte_Image2,
        INT iInWidth,
        INT iInHeight,
        INT iInBitDepth,
        BYTE* PointByte_CombineImage
    );

    bool OTSUThreshold(
        unsigned char* pucInImage1,
        long lInWidth,
        long lInHeight,
        long lInBitDepth,
        long& lOutThreshold,
        unsigned char* pucOutImage1
    );

    bool ROItoReduceImage(
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
    );

    bool FrameFlame(
        unsigned char* pucInImage1,
        unsigned char* pucInImage2,
        long lInReduceWidth,
        long lInReduceHeight,
        long lInBitDepth,
        unsigned char* pucOutImage1
    );

    bool DoubleFrame(
        unsigned char* pucInImage1,
        unsigned char* pucInImage2,
        unsigned char* pucInImage3,
        long lInReduceWidth,
        long lInReduceHeight,
        long lInBitDepth,
        long long llInFrameCount,
        unsigned char* pucOutImage1
    );

    bool RGBtoHSVFrame(
        unsigned char* pucInImage1,
        unsigned char* pucInImage2,
        long lInReduceWidth,
        long lInReduceHeight,
        long lInBitDepth,
        int* piOutImage1,
        unsigned char* pucOutImage1
    );

private:

    bool bLabelTruePositive;
    int iLabelTruePositive;
    bool bLabelFalsePositive;
    int iLabelFalsePositive;
    bool bLabelTrueNegative;
    int iLabelTrueNegative;
    bool bLabelFalseNegative;
    int iLabelFalseNegative;

    vector<stRectangleData> vectorBox;

    vector<stRectangleData> vectorBoxAdjust;

    double m_dbTimeDiff;

    long m_lOriginWidth;

    long m_lOriginHeight;

    long m_lOriginBitDepth;

    long m_lOriginLength;

    double dbReduceDivisor;

    stInitParameter m_stInit;

    stOutputData m_stOutput;

    long m_lReduceWidth;

    long m_lReduceHeight;

    long m_lReduceLength;

    long m_lOriginROISX;

    long m_lOriginROISY;

    long m_lOriginROIEX;

    long m_lOriginROIEY;

    long m_lOriginROIWidth;

    long m_lOriginROIHeight;

    long m_lOriginROILength;

    long m_lReduceROISX;

    long m_lReduceROISY;

    long m_lReduceROIEX;

    long m_lReduceROIEY;

    long m_lReduceROIWidth;

    long m_lReduceROIHeight;

    long m_lReduceROILength;

    long long m_llFrameCount;

    long m_lFrameIndex;


private:

    unsigned char* m_pucOriginImage;

    unsigned char* m_pucDestinationImage;

    unsigned char* m_pucOriginROI;

    unsigned char* m_pucReduceROI;

    unsigned char* m_pucFireExtractionOfTheColorFeatureImage;

    unsigned char* m_pucContrastFilter;

    unsigned char* m_pucCombine;

    unsigned char* m_pucBoxMarker2;

    unsigned char* m_pucInterFrameFlame1;

    unsigned char* m_pucInterFrameFlame2;

    unsigned char* m_pucFrameFlame;

    unsigned char* m_pucStableFrame1;

    unsigned char* m_pucStableFrame2;

    unsigned char* m_pucStableFrame;

    unsigned char* m_pucThinning;

    unsigned char* m_pucBoxMarker1;

    unsigned char* m_SearchNeighbor;

    int* m_piRGBtoYSH;

    unsigned char* m_pucRGBtoYSH;

};
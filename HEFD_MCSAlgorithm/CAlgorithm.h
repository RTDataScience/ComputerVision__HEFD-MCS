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

    bool AlgInit (
        void* _IN_ pstInInitParameter 
        );
    bool AlgRelease();
    bool AlgInput (  
        unsigned char* _IN_ pucInData, 
        long _IN_ lInWidth,            
        long _IN_ lInHeight,           
        long _IN_ lInBitDepth,
        void* _IN_ pstInInputParameter,
        void* _IN_ pInReserve          
        );
    bool AlgProcessing (   
        void* _IN_ pInReserve, 
        void* _OUT_ pOutReserve
        );
    bool AlgOutput (                            
		unsigned char* _OUT_ pucOutData1,
		unsigned char* _OUT_ pucOutData2,
		double* _OUT_ dbOutTimeDiff,       
        void* _OUT_ pstOutputParameter,    
        void* _OUT_ pOutReserve            
        );

protected:
private:
    bool AlgProcessing_BitDepth4 ();
    bool AlgProcessing_BitDepth3 ();
    bool AlgProcessing_BitDepth1 ();

private:
    
    bool GetROIRagne (
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
    
    bool ReduceImage ( 
        unsigned char* pInImage,
        int iInWidth,
        int iInHeight,
        int iInBitDepth, 
        unsigned char* pOutImage,
        int iInReduceWidth,
        int iInReduceHeight,
        int iInReduceBitDepth
        );
    
    bool SobelFilter8Direction ( 
        unsigned char* pInImage,
        int iInWidth,
        int iInHeight,
        int iInBitDepth,
        unsigned char* pOutSF 
        );
    
    bool ContrastFilter8Direction ( 
        unsigned char* pInImage,
        int iInWidth,
        int iInHeight,
        int iInBitDepth,
        unsigned char* pOutSF 
        );
    
    bool CombineImage(
        unsigned char* pucInImage1,
        unsigned char* pucInImage2,
        int iInWidth,
        int iInHeight,
        int iInBitDepth,
        char* cInCommand,
        unsigned char* pucOutCombineImage
    );

    bool InterFrameImage(
        unsigned char* pucInImage1,
        unsigned char* pucImage1,
        unsigned char* pucImage2,
        int iInWidth,
        int iInHeight,
        int iInBitDepth,
        long lInFrameCount,
        unsigned char* pucOutImage1
    );

    bool BinaryUsingHistogram(
        unsigned char* pucInImage,
        long lInWidth,
        long lInHeight,
        long lInBitDepth,
        float fInMiddleDivision,
        unsigned char* pucOutImage
    );

    bool RedAdjustMiddle(
        unsigned char* pInImage,
        int iInWidth,
        int iInHeight,
        int iInBitDepth,
        double dbDivision,
        int* iOutRedMean
    );

    bool FireRegionIsolationImage(
        unsigned char* pInImage1,
        unsigned char* pInImage2,
        int iInWidth,
        int iInHeight,
        int iInBitDepth,
        int iInRedThreshold,
        int iInSaturationThreshold,
        unsigned char* pOutImage
    );

    bool FireExtractionOfTheColorFeatureImage(
        unsigned char* pInImage,
        int iInWidth,
        int iInHeight,
        int iInBitDepth,
        unsigned char* pOutImage
    );

    bool CombineThreeImage(
        unsigned char* pucInImage1,
        unsigned char* pucInImage2,
        unsigned char* pucInImage3,
        int iInWidth,
        int iInHeight,
        int iInBitDepth,
        int iInRange,
        unsigned char* pucOutCombineThreeImage
    );

	bool LabelingCreateMemory(
		unsigned char* pucInImage1,
		int iInWidth,
		int iInHeight,
        int iInBitDepth,
        int* piOutData1,
		int* piOutData2
	);

    bool LabelingTracer(
        int* piInData1,
        int* piInData2,
        int* iCy,
        int* iCx,
        int* iTracingDirection,
        int iInWidth,
        int iInHeight
    );

    bool LabelingContourTracing(
        int* piInData1,
        int* piInData2,
        int iCy,
        int iCx,
        int iLabelIndex,
        int iTracingDirection,
        int iInWidth,
        int iInHeight
    );

    bool ConnectedComponentLabeling(
        int* piInData1,
        int* piInData2,
        int iInWidth,
        int iInHeight,
        int* iOutLabelTotalNumber
    );

    bool LabelToBitDepth4(
        int* piInImage1,
        int iInWidth,
        int iInHeight,
        int iInBitDepth,
        int iInLabelTotalNumber,
        unsigned char* pucOutImage1
    );

    bool ConnectLabel(
        unsigned char* pucInImage1,
        int* piInOutLabelData1,
        int* piInOutLabelRecord1,
        long lInReduceWidth,
        long lInReduceHeight,
        long lInBitDepth,
        int iInLabelOld,
        int iInLabelNew,
        int iInSX,
        int iInSY,
        unsigned char* pucOutImage1
    );

    bool CandidateFlameRegions(
        unsigned char* pucInImage1,
        int* piInOutLabelData1,
        int* piInLabelRecord1,
        long lInReduceWidth,
        long lInReduceHeight,
        long lInBitDepth,
        long lInLabelTotalNumber,
        long lInFrameIndex,
        int iInRange,
        unsigned char* pucOutImage1
    );

    bool MotionVectorFlameBlockImage(
        unsigned char* pucInImage,
        unsigned char* pucInFrame1,
        unsigned char* pucInFrame2,
        int* piInOutLabelData1,
        int* piInDataLabel1,
        int* piInDataLabel2,
        unsigned char* pucInFlameImage,
        long lInWidth,
        long lInHeight,
        long lInBitDepth,
        long lInLabelTotalNumber,
        long lInBlockWidth,
        long lInBlockHeight,
        long lInSearchXRange,
        long lInSearchYRange,
        long long llInFrameCount,
        unsigned char* pucOutImage,
        long lInBitDepthOutImage
    );






    bool PixelWeight(
        unsigned char* pucInImage1,
        double* pdbInImage2,
        long lInReduceWidth,
        long lInReduceHeight,
        long lInBitDepth,
        unsigned char* pucOutImage1
    );

    bool OTSUThreshold(
        unsigned char* pucInImage1,
        long lInWidth,
        long lInHeight,
        long lInBitDepth,
        long& lOutThreshold,
        unsigned char* pucOutImage1
    );
    
    bool ROItoReduceImage (
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

    bool SearchNeighbor (
        unsigned char* pucInImage1,
        unsigned char* pucInImage2,
        unsigned char* pucInImage3,
        unsigned char* pucInImage4,
        long lInReduceWidth,
        long lInReduceHeight,
        long lInBitDepth,
        vector<stRectangleData>& vectorBox,
        unsigned char* pucOutImage1
        );


    bool BoxMaker (
        unsigned char* pInImg1Bin,
        unsigned char* pInImg2,
        long lInWidth,
        long lInHeight,
        long lInBitDepth,
        vector<stRectangleData>& vectorBox,
        long lInMode,
        unsigned char* pOutImage
        );

    bool BoxAdjust (
        unsigned char* pInImage1,
        vector<stRectangleData>& vectorBox,
        int iInWidth,
        int iInHeight,
        int iInBitDepth,
        unsigned char* pOutImage1 
        );


    bool OpenClose (
        unsigned char* pInImage,
        int iInWidth,
        int iInHeight,
        int iInBitDepth,
        int iInRangeY,
        int iInRangeX,
        int iInThreshold1,
        int iInThreshold2,
        int iInThreshold3,
        int iInThreshold4,
        int iInThreshold5,
        int iInThreshold6,
        int iInLoop,
        unsigned char* pOutImage 
        );

    bool DoubleFrame (
        unsigned char* pucInImage1,
        unsigned char* pucInImage2,
        unsigned char* pucInImage3,
        long lInReduceWidth,
        long lInReduceHeight,
        long lInBitDepth,
        long long llInFrameCount,
        unsigned char* pucOutImage1
        );

    bool StableFrame (
        unsigned char* pucInImage1,
        unsigned char* pucInImage2,
        unsigned char* pucInImage3,
        unsigned char* pucInImage4,
        long lInReduceWidth,
        long lInReduceHeight,
        long lInBitDepth,
        long long llInFrameCount,
        unsigned char* pucOutImage1
        );

    bool Thinning (
        unsigned char* pucInImage1,
        long lInReduceWidth,
        long lInReduceHeight,
        long lInBitDepth,
        unsigned char* pucOutImage1
        );

    bool RGBtoHSVFrame (
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

    int iReLoadCount;

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

    double m_dbSplitDegree;


private:
    
    unsigned char* m_pucOriginImage;
    
    unsigned char* m_pucDestinationImage;
    
    unsigned char* m_pucOriginROI;
    
    unsigned char* m_pucReduceROI;
    
    unsigned char* m_pucSobelFilter;
    
    unsigned char* m_pucContrastFilter;
    
    unsigned char* m_pucCombine;

    unsigned char* m_pucCombineBinary;

    unsigned char* m_pucInterFrame1;

    unsigned char* m_pucInterFrame2;

    unsigned char* m_pucInterFrame;

    unsigned char* m_pucInterFrameBinary;

    unsigned char* m_pucCombineFireRegionIsolationImage;

    unsigned char* m_pucInterFrameFireRegionIsolationImage;

    unsigned char* m_pucFireExtractionOfTheColorFeatureImage;

    int* m_piBinaryImage;

    int* m_piLabelImage;

    unsigned char* m_pucLabelImage;

    int* m_piInterFrameLabelImage1;
    
    int* m_piInterFrameLabelImage2;

    int* m_piInterFrameLabelImage3;

    int* m_piInterFrameLabelImage;

    int* m_piLabelRecord;

	unsigned char* m_pucPixelWeight;

	double* m_pdbPixelWeight;

	unsigned char* m_pucCandidateFlameRegions;

    unsigned char* m_pucMotionVectorImage1;

    unsigned char* m_pucMotionVectorImage2;

    unsigned char* m_pucMotionVectorImage;

    int* m_piMotionVectorImage1;

    int* m_piMotionVectorImage2;







    unsigned char* m_pucBoxMarker2;

    unsigned char* m_pucStableFrame1;

    unsigned char* m_pucStableFrame2;

    unsigned char* m_pucStableFrame;

    unsigned char* m_pucThinning;

    unsigned char* m_pucBoxMarker1;

    unsigned char* m_SearchNeighbor;

    int* m_piRGBtoYSH;

    unsigned char* m_pucRGBtoYSH;

    //     unsigned char* m_pucIF1;
    // 
    //     unsigned char* m_pucIF2;
    // 
    //     unsigned char* m_pucIF;



};
#pragma once

#include "StdAfx.h"
#include "CAlgorithm.h"
#include <math.h> 
#include <cstdio>
#include <time.h>

using namespace std;

#define IN
#define OUT
#define PI 3.14159
#define _Max(x,y) ((x)>(y) ? (x) : (y))
#define _Min(x,y) ((x)<(y) ? (x) : (y))
static int SearchDirection[8][2] = { {0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1} };

typedef struct {
    double r;       // percent
    double g;       // percent
    double b;       // percent
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // percent
    double v;       // percent
} hsv;

typedef struct {
    double h;       // angle in degrees
    double s;       // percent
    double v;       // percent
} hsi;

#define NAN -1

static hsv rgb2hsv ( rgb in );
static rgb hsv2rgb ( hsv in );
static void RGBtoHSV ( float r, float g, float b, float *h, float *s, float *v );
static void HSVtoRGB ( float *r, float *g, float *b, float h, float s, float v );
static void HSI (
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

    iReLoadCount = 0;

    m_dbTimeDiff = 0.0f;
    
    m_lOriginWidth = 0;
    
    m_lOriginHeight = 0;
    
    m_lOriginBitDepth = 0;
    
    m_lOriginLength = 0;
    
    dbReduceDivisor = 8;
    
    memset ( &m_stInit, 0x00, sizeof(stInitParameter) );
    
    memset ( &m_stOutput, 0x00, sizeof(stOutputData) );
    
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

    m_dbSplitDegree = 0.0f;

    vectorBox.clear();

    vectorBoxAdjust.clear();

    
    m_pucOriginImage = NULL;
    
    m_pucDestinationImage = NULL;
    
    m_pucOriginROI = NULL;
    
    m_pucReduceROI = NULL;
    
    m_pucSobelFilter = NULL;
    
    m_pucContrastFilter = NULL;
    
    m_pucCombine = NULL;

    m_pucCombineBinary = NULL;

    m_pucInterFrame1 = NULL;

    m_pucInterFrame2 = NULL;

    m_pucInterFrame = NULL;

    m_pucInterFrameBinary = NULL;
    
    m_pucCombineFireRegionIsolationImage = NULL;

    m_pucInterFrameFireRegionIsolationImage = NULL;

    m_pucFireExtractionOfTheColorFeatureImage = NULL;

    m_piBinaryImage = NULL;

    m_piLabelImage = NULL;

    m_pucLabelImage = NULL;

    m_piInterFrameLabelImage1 = NULL;

    m_piInterFrameLabelImage2 = NULL;

    m_piInterFrameLabelImage3 = NULL;

    m_piInterFrameLabelImage = NULL;

    m_piLabelRecord = NULL;

	m_pucCandidateFlameRegions = NULL;

    m_pucMotionVectorImage1 = NULL;

    m_pucMotionVectorImage2 = NULL;

    m_pucMotionVectorImage = NULL;

    m_piMotionVectorImage1 = NULL;

    m_piMotionVectorImage2 = NULL;





    m_pucPixelWeight = NULL;

    m_pdbPixelWeight = NULL;

    m_pucBoxMarker2 = NULL;

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
    
    memset ( &m_stInit, 0x00, sizeof(stInitParameter) );
    
    memset ( &m_stOutput, 0x00, sizeof(stOutputData) );
    
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

    m_dbSplitDegree = 0.0f;
    
    vectorBox.clear();

    vectorBoxAdjust.clear();


    SAFE_DELETE_ARRAY ( m_pucOriginImage );
    
    SAFE_DELETE_ARRAY ( m_pucDestinationImage );
    
    SAFE_DELETE_ARRAY ( m_pucOriginROI );
    
    SAFE_DELETE_ARRAY ( m_pucReduceROI );
    
    SAFE_DELETE_ARRAY ( m_pucSobelFilter );
    
    SAFE_DELETE_ARRAY ( m_pucContrastFilter );
    
    SAFE_DELETE_ARRAY ( m_pucCombine );

    SAFE_DELETE_ARRAY(m_pucCombineBinary);

    SAFE_DELETE_ARRAY(m_pucInterFrame1);

    SAFE_DELETE_ARRAY(m_pucInterFrame2);

    SAFE_DELETE_ARRAY(m_pucInterFrame);

    SAFE_DELETE_ARRAY(m_pucInterFrameBinary);

    SAFE_DELETE_ARRAY(m_pucCombineFireRegionIsolationImage);

    SAFE_DELETE_ARRAY(m_pucInterFrameFireRegionIsolationImage);

    SAFE_DELETE_ARRAY(m_pucFireExtractionOfTheColorFeatureImage);

    SAFE_DELETE_ARRAY(m_piBinaryImage);

    SAFE_DELETE_ARRAY(m_piLabelImage);

    SAFE_DELETE_ARRAY(m_pucLabelImage);

    SAFE_DELETE_ARRAY(m_piInterFrameLabelImage1);

    SAFE_DELETE_ARRAY(m_piInterFrameLabelImage2);

    SAFE_DELETE_ARRAY(m_piInterFrameLabelImage3);

    SAFE_DELETE_ARRAY(m_piInterFrameLabelImage);

    SAFE_DELETE_ARRAY(m_piLabelRecord);

    SAFE_DELETE_ARRAY(m_pucCandidateFlameRegions);

    SAFE_DELETE_ARRAY(m_pucMotionVectorImage1);

    SAFE_DELETE_ARRAY(m_pucMotionVectorImage2);

    SAFE_DELETE_ARRAY(m_pucMotionVectorImage);

    SAFE_DELETE_ARRAY(m_piMotionVectorImage1);

    SAFE_DELETE_ARRAY(m_piMotionVectorImage2);





	SAFE_DELETE_ARRAY(m_pucPixelWeight);

	SAFE_DELETE_ARRAY(m_pdbPixelWeight);

    
    SAFE_DELETE_ARRAY ( m_pucBoxMarker2 );

    SAFE_DELETE_ARRAY ( m_SearchNeighbor );

    SAFE_DELETE_ARRAY ( m_piRGBtoYSH );
    
    SAFE_DELETE_ARRAY ( m_pucThinning );

    SAFE_DELETE_ARRAY ( m_pucBoxMarker1 );

    SAFE_DELETE_ARRAY ( m_pucRGBtoYSH );

    SAFE_DELETE_ARRAY ( m_pucStableFrame1 );

    SAFE_DELETE_ARRAY ( m_pucStableFrame2 );

    SAFE_DELETE_ARRAY ( m_pucStableFrame );

//     SAFE_DELETE_ARRAY ( m_pucIF1 );
// 
//     SAFE_DELETE_ARRAY ( m_pucIF2 );
// 
//     SAFE_DELETE_ARRAY ( m_pucIF );

}


bool CAlgorithm::
    AlgInit ( 
    void* _IN_ pstInInitParameter 
    )
{

    if ( pstInInitParameter == NULL )
    {
        AlgRelease();
        return false;
    }
    
    memcpy ( &m_stInit, pstInInitParameter, sizeof(stInitParameter) );
    
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
    
    memset ( &m_stInit, 0x00, sizeof(stInitParameter) );
    
    memset ( &m_stOutput, 0x00, sizeof(stOutputData) );
    
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

    m_dbSplitDegree = 0.0f;
    
    vectorBox.clear();

    vectorBoxAdjust.clear();


    SAFE_DELETE_ARRAY ( m_pucOriginImage );
    
    SAFE_DELETE_ARRAY ( m_pucDestinationImage );
    
    SAFE_DELETE_ARRAY ( m_pucOriginROI );
    
    SAFE_DELETE_ARRAY ( m_pucReduceROI );
    
    SAFE_DELETE_ARRAY ( m_pucSobelFilter );
    
    SAFE_DELETE_ARRAY ( m_pucContrastFilter );
    
    SAFE_DELETE_ARRAY ( m_pucCombine );

    SAFE_DELETE_ARRAY(m_pucCombineBinary);

    SAFE_DELETE_ARRAY(m_pucInterFrame1);

    SAFE_DELETE_ARRAY(m_pucInterFrame2);

    SAFE_DELETE_ARRAY(m_pucInterFrame);

    SAFE_DELETE_ARRAY(m_pucInterFrameBinary);

    SAFE_DELETE_ARRAY(m_pucCombineFireRegionIsolationImage);

    SAFE_DELETE_ARRAY(m_pucInterFrameFireRegionIsolationImage);

    SAFE_DELETE_ARRAY(m_pucFireExtractionOfTheColorFeatureImage);

    SAFE_DELETE_ARRAY(m_piBinaryImage);

    SAFE_DELETE_ARRAY(m_piLabelImage);

    SAFE_DELETE_ARRAY(m_pucLabelImage);

    SAFE_DELETE_ARRAY(m_piInterFrameLabelImage1);

    SAFE_DELETE_ARRAY(m_piInterFrameLabelImage2);

    SAFE_DELETE_ARRAY(m_piInterFrameLabelImage3);

    SAFE_DELETE_ARRAY(m_piInterFrameLabelImage);

    SAFE_DELETE_ARRAY(m_piLabelRecord);

    SAFE_DELETE_ARRAY(m_pucCandidateFlameRegions);

    SAFE_DELETE_ARRAY(m_pucMotionVectorImage1);

    SAFE_DELETE_ARRAY(m_pucMotionVectorImage2);

    SAFE_DELETE_ARRAY(m_pucMotionVectorImage);

    SAFE_DELETE_ARRAY(m_piMotionVectorImage1);

    SAFE_DELETE_ARRAY(m_piMotionVectorImage2);





	SAFE_DELETE_ARRAY(m_pucPixelWeight);

	SAFE_DELETE_ARRAY(m_pdbPixelWeight);

    SAFE_DELETE_ARRAY ( m_pucBoxMarker2 );

    SAFE_DELETE_ARRAY ( m_SearchNeighbor );

    SAFE_DELETE_ARRAY ( m_piRGBtoYSH );

    SAFE_DELETE_ARRAY ( m_pucThinning );

    SAFE_DELETE_ARRAY ( m_pucBoxMarker1 );

    SAFE_DELETE_ARRAY ( m_pucRGBtoYSH );

    SAFE_DELETE_ARRAY ( m_pucStableFrame1 );

    SAFE_DELETE_ARRAY ( m_pucStableFrame2 );

    SAFE_DELETE_ARRAY ( m_pucStableFrame );

//     SAFE_DELETE_ARRAY ( m_pucIF1 );
// 
//     SAFE_DELETE_ARRAY ( m_pucIF2 );
// 
//     SAFE_DELETE_ARRAY ( m_pucIF );

    return true;
}


bool CAlgorithm::
    AlgInput (  
    unsigned char* _IN_ pucInData, 
    long _IN_ lInWidth,            
    long _IN_ lInHeight,           
    long _IN_ lInBitDepth,
    void* _IN_ pstInInputParameter,
    void* _IN_ pInReserve          
    )
{
    
    
    if ( pucInData == NULL )
    {
        return false;
    }
    
    if ( lInWidth > 0 && lInWidth <= 2560 )
    {
        
        m_lOriginWidth = lInWidth;
    }
    else
    {
        return false;
    }
    
    if ( lInHeight > 0 && lInHeight <= 2048 )
    {
        
        m_lOriginHeight = lInHeight;
    }
    else
    {
        return false;
    }
    
    if ( lInBitDepth == 4 || lInBitDepth == 3 || lInBitDepth == 1 )
    {
        
        m_lOriginBitDepth = lInBitDepth;
    }
    else
    {
        return false;
    }
    
    m_lOriginLength = m_lOriginWidth * m_lOriginHeight * m_lOriginBitDepth;
    
    
    dbReduceDivisor = m_stInit.dbInThreshold04;
    
    
    m_lReduceWidth = long ( m_lOriginWidth / dbReduceDivisor );
    
    m_lReduceHeight = long ( m_lOriginHeight / dbReduceDivisor );
    
    m_lReduceLength = m_lReduceWidth * m_lReduceHeight * m_lOriginBitDepth;
    
    if ( m_lOriginROISX == m_lOriginROIEX == m_lOriginROISY == m_lOriginROIEY )
    {
        m_lOriginROISX = 0;
        m_lOriginROISY = 0;
        m_lOriginROIEX = m_lOriginWidth - 1;
        m_lOriginROIEY = m_lOriginHeight - 1;
    }
    
    if ( ( m_lOriginROISX >= 0 && m_lOriginROISX <= m_lOriginWidth - 1 ) &&  
        ( m_lOriginROISX < m_lOriginROIEX ) )
    {
        
        m_lReduceROISX = long ( m_lOriginROISX / dbReduceDivisor );
    }
    else
    {
        return false;
    }
    
    if ( ( m_lOriginROISY >= 0 && m_lOriginROISY <= m_lOriginHeight - 1 ) &&  
        ( m_lOriginROISY < m_lOriginROIEY ) )
    {
        
        m_lReduceROISY = long ( m_lOriginROISY / dbReduceDivisor );
    }
    else
    {
        return false;
    }
    
    if ( ( m_lOriginROIEX >= 0 && m_lOriginROIEX <= m_lOriginWidth - 1 ) &&  
        ( m_lOriginROISX < m_lOriginROIEX ) )
    {
        
        m_lReduceROIEX = long ( m_lOriginROIEX / dbReduceDivisor );
    }
    else
    {
        return false;
    }
    
    if ( ( m_lOriginROIEY >= 0 && m_lOriginROIEY <= m_lOriginHeight - 1 ) &&  
        ( m_lOriginROISY < m_lOriginROIEY ) )
    {
        
        m_lReduceROIEY = long ( m_lOriginROIEY / dbReduceDivisor );
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
    
    
    
    if ( m_pucOriginImage == NULL )
    {
        m_pucOriginImage = new unsigned char [ m_lOriginLength ];
        memcpy ( m_pucOriginImage, pucInData, m_lOriginLength );
    }
    else if ( m_pucOriginImage != NULL )
    {
        memcpy ( m_pucOriginImage, pucInData, m_lOriginLength );
    }
    
    if ( m_pucDestinationImage == NULL )
    {
        m_pucDestinationImage = new unsigned char [ m_lReduceLength ];
        memset ( m_pucDestinationImage, 0x00, m_lReduceLength );
    }
    
    if ( m_pucOriginROI == NULL )
    {
        m_pucOriginROI = new unsigned char [ m_lOriginROILength ];
        memset ( m_pucOriginROI, 0x00, m_lOriginROILength );
    }
    
    if ( m_pucReduceROI == NULL )
    {
        m_pucReduceROI = new unsigned char [ m_lReduceROILength ];
        memset ( m_pucReduceROI, 0x00, m_lReduceROILength );
    }
    
    if ( m_pucSobelFilter == NULL )
    {
        m_pucSobelFilter = new unsigned char [ m_lReduceROILength ];
        memset ( m_pucSobelFilter, 0x00, m_lReduceROILength );
    }
    
    if ( m_pucContrastFilter == NULL )
    {
        m_pucContrastFilter = new unsigned char [ m_lReduceROILength ];
        memset ( m_pucContrastFilter, 0x00, m_lReduceROILength );
    }
    
    if ( m_pucCombine == NULL )
    {
        m_pucCombine = new unsigned char [ m_lReduceROILength ];
        memset ( m_pucCombine, 0x00, m_lReduceROILength );
    }

    if (m_pucCombineBinary == NULL)
    {
        m_pucCombineBinary = new unsigned char[m_lReduceROILength];
        memset(m_pucCombineBinary, 0x00, m_lReduceROILength);
    }

    if (m_pucInterFrame1 == NULL)
    {
        m_pucInterFrame1 = new unsigned char[m_lReduceROILength];
        memset(m_pucInterFrame1, 0x00, m_lReduceROILength);
    }

    if (m_pucInterFrame2 == NULL)
    {
        m_pucInterFrame2 = new unsigned char[m_lReduceROILength];
        memset(m_pucInterFrame2, 0x00, m_lReduceROILength);
    }

    if (m_pucInterFrame == NULL)
    {
        m_pucInterFrame = new unsigned char[m_lReduceROILength];
        memset(m_pucInterFrame, 0x00, m_lReduceROILength);
    }

    if (m_pucInterFrameBinary == NULL)
    {
        m_pucInterFrameBinary = new unsigned char[m_lReduceROILength];
        memset(m_pucInterFrameBinary, 0x00, m_lReduceROILength);
    }

    if (m_pucCombineFireRegionIsolationImage == NULL)
    {
        m_pucCombineFireRegionIsolationImage = new unsigned char[m_lReduceROILength];
        memset(m_pucCombineFireRegionIsolationImage, 0x00, m_lReduceROILength);
    }

    if (m_pucInterFrameFireRegionIsolationImage == NULL)
    {
        m_pucInterFrameFireRegionIsolationImage = new unsigned char[m_lReduceROILength];
        memset(m_pucInterFrameFireRegionIsolationImage, 0x00, m_lReduceROILength);
    }

    if (m_pucFireExtractionOfTheColorFeatureImage == NULL)
    {
        m_pucFireExtractionOfTheColorFeatureImage = new unsigned char[m_lReduceROILength];
        memset(m_pucFireExtractionOfTheColorFeatureImage, 0x00, m_lReduceROILength);
    }

    if (m_piBinaryImage == NULL)
    {
        m_piBinaryImage = new int[m_lReduceROIWidth * m_lReduceROIHeight];
        memset(m_piBinaryImage, 0x00, m_lReduceROIWidth * m_lReduceROIHeight * sizeof(int));
    }

    if (m_piLabelImage == NULL)
    {
        m_piLabelImage = new int[m_lReduceROIWidth * m_lReduceROIHeight];
        memset(m_piLabelImage, 0x00, m_lReduceROIWidth * m_lReduceROIHeight * sizeof(int));
    }

    if (m_pucLabelImage == NULL)
    {
        m_pucLabelImage = new unsigned char[m_lReduceROILength];
        memset(m_pucLabelImage, 0x00, m_lReduceROILength);
    }

    if (m_piInterFrameLabelImage1 == NULL)
    {
        m_piInterFrameLabelImage1 = new int[m_lReduceROIWidth * m_lReduceROIHeight];
        memset(m_piInterFrameLabelImage1, 0x00, m_lReduceROIWidth * m_lReduceROIHeight * sizeof(int));
    }

    if (m_piInterFrameLabelImage2 == NULL)
    {
        m_piInterFrameLabelImage2 = new int[m_lReduceROIWidth * m_lReduceROIHeight];
        memset(m_piInterFrameLabelImage2, 0x00, m_lReduceROIWidth * m_lReduceROIHeight * sizeof(int));
    }

    if (m_piInterFrameLabelImage3 == NULL)
    {
        m_piInterFrameLabelImage3 = new int[m_lReduceROIWidth * m_lReduceROIHeight];
        memset(m_piInterFrameLabelImage3, 0x00, m_lReduceROIWidth * m_lReduceROIHeight * sizeof(int));
    }

    if (m_piInterFrameLabelImage == NULL)
    {
        m_piInterFrameLabelImage = new int[m_lReduceROIWidth * m_lReduceROIHeight];
        memset(m_piInterFrameLabelImage, 0x00, m_lReduceROIWidth * m_lReduceROIHeight * sizeof(int));
    }

    if (m_piLabelRecord == NULL)
    {
        m_piLabelRecord = new int[m_lReduceROIWidth * m_lReduceROIHeight];
        memset(m_piLabelRecord, 0x00, m_lReduceROIWidth * m_lReduceROIHeight * sizeof(int));
    }

    if (m_pucCandidateFlameRegions == NULL)
    {
        m_pucCandidateFlameRegions = new unsigned char[m_lReduceROILength];
        memset(m_pucCandidateFlameRegions, 0x00, m_lReduceROILength);
    }

    if (m_pucMotionVectorImage1 == NULL)
    {
        m_pucMotionVectorImage1 = new unsigned char[m_lReduceROILength];
        memset(m_pucMotionVectorImage1, 0x00, m_lReduceROILength);
    }

    if (m_pucMotionVectorImage2 == NULL)
    {
        m_pucMotionVectorImage2 = new unsigned char[m_lReduceROILength];
        memset(m_pucMotionVectorImage2, 0x00, m_lReduceROILength);
    }

    if (m_pucMotionVectorImage == NULL)
    {
        m_pucMotionVectorImage = new unsigned char[m_lReduceROILength];
        memset(m_pucMotionVectorImage, 0x00, m_lReduceROILength);
    }

    if (m_piMotionVectorImage1 == NULL)
    {
        m_piMotionVectorImage1 = new int[m_lReduceROIWidth * m_lReduceROIHeight];
        memset(m_piMotionVectorImage1, 0x00, m_lReduceROIWidth * m_lReduceROIHeight * sizeof(int));
    }

    if (m_piMotionVectorImage2 == NULL)
    {
        m_piMotionVectorImage2 = new int[m_lReduceROIWidth * m_lReduceROIHeight];
        memset(m_piMotionVectorImage2, 0x00, m_lReduceROIWidth * m_lReduceROIHeight * sizeof(int));
    }








	if (m_pucPixelWeight == NULL)
	{
		m_pucPixelWeight = new unsigned char[m_lReduceROILength];
		memset(m_pucPixelWeight, 0x00, m_lReduceROILength);
	}

	if (m_pdbPixelWeight == NULL)
	{
		m_pdbPixelWeight = new double[m_lReduceROIWidth * m_lReduceROIHeight * m_lOriginBitDepth];
		memset(m_pdbPixelWeight, 0x00, m_lReduceROIWidth * m_lReduceROIHeight * m_lOriginBitDepth * sizeof(double));
	}

    if ( m_pucBoxMarker2 == NULL )
    {
        m_pucBoxMarker2 = new unsigned char [ m_lReduceROILength ];
        memset ( m_pucBoxMarker2, 0x00, m_lReduceROILength );
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
    
    if ( m_SearchNeighbor == NULL )
    {
        m_SearchNeighbor = new unsigned char [ m_lReduceROILength ];
        memset ( m_SearchNeighbor, 0x00, m_lReduceROILength );
    }

    if ( m_piRGBtoYSH == NULL )
    {
        m_piRGBtoYSH = new int [ m_lReduceROILength ];
        memset ( m_piRGBtoYSH, 0x00, m_lReduceROILength * sizeof(int) );
    }

    if ( m_pucThinning == NULL )
    {
        m_pucThinning = new unsigned char [ m_lReduceROILength ];
        memset ( m_pucThinning, 0x00, m_lReduceROILength );
    }

    if ( m_pucBoxMarker1 == NULL )
    {
        m_pucBoxMarker1 = new unsigned char [ m_lReduceROILength ];
        memset ( m_pucBoxMarker1, 0x00, m_lReduceROILength );
    }

    if ( m_pucRGBtoYSH == NULL )
    {
        m_pucRGBtoYSH = new unsigned char [ m_lReduceROILength ];
        memset ( m_pucRGBtoYSH, 0x00, m_lReduceROILength );
    }

    if ( m_pucStableFrame1 == NULL )
    {
        m_pucStableFrame1 = new unsigned char [ m_lReduceROILength ];
        memset ( m_pucStableFrame1, 0x00, m_lReduceROILength );
    }

    if ( m_pucStableFrame2 == NULL )
    {
        m_pucStableFrame2 = new unsigned char [ m_lReduceROILength ];
        memset ( m_pucStableFrame2, 0x00, m_lReduceROILength );
    }

    if ( m_pucStableFrame == NULL )
    {
        m_pucStableFrame = new unsigned char [ m_lReduceROILength ];
        memset ( m_pucStableFrame, 0x00, m_lReduceROILength );
    }



    if ( m_llFrameCount + 1 < 120000000 )
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
    AlgProcessing (   
    void* _IN_ pInReserve, 
    void* _OUT_ pOutReserve
    )
{
    LARGE_INTEGER litmp; 
    LONGLONG QPart1,QPart2;
    double dfMinus, dfFreq, dfTim; 
    QueryPerformanceFrequency ( &litmp );
    dfFreq = (double) litmp.QuadPart;
    QueryPerformanceCounter ( &litmp );
    QPart1 = litmp.QuadPart;
    m_dbTimeDiff = 0.0f;
	m_stOutput.bOutTrigger01 = false;
    if ( m_lOriginBitDepth == 4 )
    {
        if ( AlgProcessing_BitDepth4() == false )
        {
            return false;
        }
    }
    else if ( m_lOriginBitDepth == 3 )
    {
        if ( AlgProcessing_BitDepth3() == false )
        {
            return false;
        }
    }
    else if ( m_lOriginBitDepth == 1 )
    {
        if ( AlgProcessing_BitDepth1() == false )
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
    dfMinus = (double)(QPart2-QPart1);
    dfTim = dfMinus / dfFreq;
    char cTimeClock [50];
    ZeroMemory ( cTimeClock, 50 * sizeof(char) );
    sprintf_s( cTimeClock, "Second: %f\n", dfTim );
    OutputDebugStringA( cTimeClock );
    m_dbTimeDiff = dfTim;
    char cFrameIndex [50];
    ZeroMemory ( cFrameIndex, 50 * sizeof(char) );
    sprintf_s ( cFrameIndex, "Frame Index: %d\n", m_llFrameCount );
    OutputDebugStringA ( cFrameIndex );
	m_stOutput.bOutTrigger01 = true;
    return true;
}


bool CAlgorithm::
    AlgOutput (                            
	unsigned char* _OUT_ pucOutData1,
	unsigned char* _OUT_ pucOutData2,
    double* _OUT_ dbOutTimeDiff,       
    void* _OUT_ pstOutputParameter,    
    void* _OUT_ pOutReserve            
    )
{
	if (pucOutData1 != NULL && m_pucCandidateFlameRegions != NULL)
	{
		memcpy(pucOutData1, m_pucCandidateFlameRegions, m_lReduceLength);
	}
	if ( pucOutData2 != NULL && m_pucMotionVectorImage != NULL )
    {
        memcpy ( pucOutData2, m_pucMotionVectorImage, m_lReduceLength );
    }
	if ( pstOutputParameter != NULL )
    {
        memcpy ( pstOutputParameter, &m_stOutput, sizeof(stOutputData) );
    }
    if ( dbOutTimeDiff != NULL )
    {
        (*dbOutTimeDiff) = m_dbTimeDiff;
    }
    return true;
}


/************************************************************************/
/* private - Level 1                                                    */
/************************************************************************/


bool CAlgorithm::
    AlgProcessing_BitDepth4 ()
{
    
    if ( GetROIRagne (
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
        ) == false )
    {
        return false;
    }
    
    if ( ReduceImage ( 
        m_pucOriginROI,
        m_lOriginROIWidth,
        m_lOriginROIHeight,
        m_lOriginBitDepth,
        m_pucReduceROI,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        m_lOriginBitDepth
        ) == false )
    {
        return false;
    }
    
    if ( SobelFilter8Direction ( 
        m_pucReduceROI,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        m_lOriginBitDepth,
        m_pucSobelFilter 
        ) == false )
    {
        return false;
    }
    
    if ( ContrastFilter8Direction ( 
        m_pucReduceROI,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        m_lOriginBitDepth,
        m_pucContrastFilter 
        ) == false )
    {
        return false;
    }
    
    if ( CombineImage (
        m_pucSobelFilter,
        m_pucContrastFilter,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        m_lOriginBitDepth,
        "ADD",
        m_pucCombine
        ) == false )
    {
        return false;
    }

    float fInCombineMiddleDivision = 4.0f;

    if (BinaryUsingHistogram(
        m_pucCombine,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        m_lOriginBitDepth,
        fInCombineMiddleDivision,
        m_pucCombineBinary
    ) == false)
    {
        return false;
    }

    if (InterFrameImage(
        m_pucReduceROI,
        m_pucInterFrame1,
        m_pucInterFrame2,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        m_lOriginBitDepth,
        m_llFrameCount,
        m_pucInterFrame
    ) == false)
    {
        return false;
    }

    float fInInterFrameMiddleDivision = 4.0f;

    if (BinaryUsingHistogram(
        m_pucInterFrame,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        m_lOriginBitDepth,
        fInInterFrameMiddleDivision,
        m_pucInterFrameBinary
    ) == false)
    {
        return false;
    }

    int iRedAdjustMiddle = 0;
    double iRedDivision = 3.0f;

    if (RedAdjustMiddle(
        m_pucReduceROI,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        m_lOriginBitDepth,
        iRedDivision,
        &iRedAdjustMiddle
    ) == false)
    {
        return false;
    }

    // RT is the red channel threshold (range: 115 -> 135)
    int iInRedThreshold = iRedAdjustMiddle;
    // ST is the saturation channel threshold (range: 55 -> 65)
    int iInCombineSaturationThreshold = 55;

    if (FireRegionIsolationImage(
        m_pucReduceROI,
        m_pucCombineBinary,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        m_lOriginBitDepth,
        iInRedThreshold,
        iInCombineSaturationThreshold,
        m_pucCombineFireRegionIsolationImage
    ) == false)
    {
        return false;
    }

    int iInInterFrameSaturationThreshold = 44;

    if (FireRegionIsolationImage(
        m_pucReduceROI,
        m_pucInterFrameBinary,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        m_lOriginBitDepth,
        iInRedThreshold,
        iInInterFrameSaturationThreshold,
        m_pucInterFrameFireRegionIsolationImage
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

    if (CombineThreeImage(
        m_pucCombineFireRegionIsolationImage,
        m_pucInterFrameFireRegionIsolationImage,
        m_pucFireExtractionOfTheColorFeatureImage,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        m_lOriginBitDepth,
        4,
        m_pucCombine
    ) == false)
    {
        return false;
    }
 
    if (LabelingCreateMemory(
        m_pucCombine,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        m_lOriginBitDepth,
        m_piBinaryImage,
        m_piLabelImage
    ) == false)
    {
        return false;
    }

    int iLabelTotalNumber = 0;

    if (ConnectedComponentLabeling(
        m_piBinaryImage,
        m_piLabelImage,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        &iLabelTotalNumber
    ) == false)
    {
        return false;
    }

    if (false)
    {
        if (LabelToBitDepth4(
            m_piLabelImage,
            m_lReduceROIWidth,
            m_lReduceROIHeight,
            m_lOriginBitDepth,
            iLabelTotalNumber,
            m_pucLabelImage
        ) == false)
        {
            return false;
        }
    }

    if (CandidateFlameRegions(
        m_pucReduceROI,
        m_piLabelImage,
        m_piLabelRecord,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        m_lOriginBitDepth,
        iLabelTotalNumber,
        m_llFrameCount,
        8,
        m_pucCandidateFlameRegions
    ) == false)
    {
        return false;
    }

    if (false)
    {
        if (LabelToBitDepth4(
            m_piLabelImage,
            m_lReduceROIWidth,
            m_lReduceROIHeight,
            m_lOriginBitDepth,
            iLabelTotalNumber,
            m_pucLabelImage
        ) == false)
        {
            return false;
        }
    }

    if (MotionVectorFlameBlockImage(
        m_pucReduceROI,
        m_pucMotionVectorImage1,
        m_pucMotionVectorImage2,
        m_piLabelImage,
        m_piMotionVectorImage1,
        m_piMotionVectorImage2,
        m_pucFireExtractionOfTheColorFeatureImage,
        m_lReduceROIWidth,
        m_lReduceROIHeight,
        m_lOriginBitDepth,
        iLabelTotalNumber,
        4,
        4,
        4,
        4,
        m_llFrameCount,
        m_pucMotionVectorImage,
        m_lOriginBitDepth
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
    //            m_pucMotionVectorImage[iIndex + 2] > 0 ||
    //            m_pucMotionVectorImage[iIndex + 1] > 0 ||
    //            m_pucMotionVectorImage[iIndex + 0] > 0
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
                //if (bLabelTruePositive == false)
                //{
                //    bLabelTruePositive = true;
                //    iLabelTruePositive++;
                //}


                /***
                [17]
                ====
                if (bLabelTruePositive == false)
                {
                    bLabelTruePositive = true;
                    iLabelTruePositive++;
                }
                if ((iX >= 110 && iX <= 150) && (iY >= 150 && iY <= 180))
                {
                    if (bLabelFalsePositive == false)
                    {
                        bLabelFalsePositive = true;
                        iLabelFalsePositive++;
                    }
                }
                */

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
            //    m_pucLabelImage[iIndex + 2] == 0 &&
            //    m_pucLabelImage[iIndex + 1] == 0 &&
            //    m_pucLabelImage[iIndex + 0] == 0
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
                m_pucLabelImage[iIndex + 2] == 0 &&
                m_pucLabelImage[iIndex + 1] == 0 &&
                m_pucLabelImage[iIndex + 0] == 0
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
                    m_pucLabelImage[iIndex + 2] == 0 &&
                    m_pucLabelImage[iIndex + 1] == 0 &&
                    m_pucLabelImage[iIndex + 0] == 0
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
                        m_pucLabelImage[iIndex + 2] == 0 &&
                        m_pucLabelImage[iIndex + 1] == 0 &&
                        m_pucLabelImage[iIndex + 0] == 0
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
                    m_pucLabelImage[iIndex + 2] == 0 &&
                    m_pucLabelImage[iIndex + 1] == 0 &&
                    m_pucLabelImage[iIndex + 0] == 0
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
                    m_pucLabelImage[iIndex + 2] == 0 &&
                    m_pucLabelImage[iIndex + 1] == 0 &&
                    m_pucLabelImage[iIndex + 0] == 0
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
                m_pucLabelImage[iIndex + 2] == 0 &&
                m_pucLabelImage[iIndex + 1] == 0 &&
                m_pucLabelImage[iIndex + 0] == 0
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
                    m_pucLabelImage[iIndex + 2] == 0 &&
                    m_pucLabelImage[iIndex + 1] == 0 &&
                    m_pucLabelImage[iIndex + 0] == 0
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
                m_pucLabelImage[iIndex + 2] == 0 &&
                m_pucLabelImage[iIndex + 1] == 0 &&
                m_pucLabelImage[iIndex + 0] == 0
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

    
    //if (PixelWeight(
	//	m_pucCombine,
	//	m_pdbPixelWeight,
	//	m_lReduceROIWidth,
	//	m_lReduceROIHeight,
	//	m_lOriginBitDepth,
	//	m_pucPixelWeight
	//) == false)
	//{
	//	return false;
	//}

 //   int iRedMeanCandidateFlameRegions = 0;
 //   double iRedDivisionCandidateFlameRegions = 1.5f;

 //   if (RedMean(
 //       m_pucReduceROI,
 //       m_lReduceROIWidth,
 //       m_lReduceROIHeight,
 //       m_lOriginBitDepth,
 //       iRedDivisionCandidateFlameRegions,
 //       &iRedMeanCandidateFlameRegions
 //   ) == false)
 //   {
 //       return false;
 //   }

 //   int iInCandidateFlameRegionsSaturationThreshold = 65;






    //if ( OTSUThreshold(
    //    m_pucInterFrame,
    //    m_lReduceROIWidth,
    //    m_lReduceROIHeight,
    //    m_lOriginBitDepth,
    //    lOTSUThreshold,
    //    m_pucOTSU
    //) == false)
    //{
    //    return false;
    //}


    //if ( RGBtoHSVFrame (
    //    m_pucFrameFlame,
    //    m_pucReduceROI,
    //    m_lReduceROIWidth,
    //    m_lReduceROIHeight,
    //    m_lOriginBitDepth,
    //    m_piRGBtoYSH,
    //    m_pucRGBtoYSH
    //    ) == false )
    //{
    //    return false;
    //}

    //if ( Thinning (        
    //    m_pucRGBtoYSH,
    //    m_lReduceROIWidth,
    //    m_lReduceROIHeight,
    //    m_lOriginBitDepth,
    //    m_pucThinning
    //    ) == false )
    //{
    //    return false;
    //}

    //vectorBox.clear();

    //if ( BoxMaker (
    //    m_pucThinning,
    //    m_pucReduceROI,
    //    m_lReduceROIWidth,
    //    m_lReduceROIHeight,
    //    m_lOriginBitDepth,
    //    vectorBox,
    //    2,
    //    m_pucBoxMarker1
    //    ) == false )
    //{
    //    return false;
    //}

    //vectorBox.clear();

    //if ( BoxMaker (
    //    m_pucBoxMarker1,
    //    m_pucReduceROI,
    //    m_lReduceROIWidth,
    //    m_lReduceROIHeight,
    //    m_lOriginBitDepth,
    //    vectorBox,
    //    1,
    //    m_pucBoxMarker2
    //    ) == false )
    //{
    //    return false;
    //}

    //if ( SearchNeighbor (
    //    m_pucBoxMarker2,
    //    m_pucReduceROI,
    //    m_pucStableFrame,
    //    m_pucThinning,
    //    m_lReduceROIWidth,
    //    m_lReduceROIHeight,
    //    m_lOriginBitDepth,
    //    vectorBox,
    //    m_SearchNeighbor
    //    ) == false )
    //{
    //    return false;
    //}

    //if ( BoxAdjust (
    //    m_pucReduceROI,
    //    vectorBox,
    //    m_lReduceROIWidth,
    //    m_lReduceROIHeight,
    //    m_lOriginBitDepth,
    //    m_pucStableFrame
    //    ) == false )
    //{
    //    return false;
    //}
    
    //if ( ROItoReduceImage (
    //    m_pucDestinationImage,
    //    m_lReduceWidth,
    //    m_lReduceHeight,
    //    m_lOriginBitDepth,
    //    m_pucMotionVectorImage, //m_pucStableFrame,
    //    m_lReduceROIWidth,
    //    m_lReduceROIHeight,
    //    m_lReduceROISX,
    //    m_lReduceROISY,
    //    m_lReduceROIEX,
    //    m_lReduceROIEY
    //    ) == false )
    //{
    //    return false;
    //}

//     if ( StableFrame (
//         m_pucFrameFlame,
//         m_pucStableFrame1,
//         m_pucStableFrame2,
//         m_pucReduceROI,
//         m_lReduceROIWidth,
//         m_lReduceROIHeight,
//         m_lOriginBitDepth,
//         m_llFrameCount,
//         m_pucStableFrame
//         ) == false )
//     {
//         return false;
//     }


//     vectorBox.clear();
// 
//     if ( BoxMaker (
//         m_SearchNeighbor,
//         m_pucReduceROI,
//         m_lReduceROIWidth,
//         m_lReduceROIHeight,
//         m_lOriginBitDepth,
//         vectorBox,
//         2,
//         m_pucBoxMarker
//         ) == false )
//     {
//         return false;
//     }


//     if ( OpenClose (
//         m_pucInterFrame,
//         m_lReduceROIWidth,
//         m_lReduceROIHeight,
//         m_lOriginBitDepth,
//         1,
//         1,
//         3, 2, 3, 1, 1, 1, 
//         //9, 6, 4, 0, 0, 0, 
//         2,
//         m_pucPixelWeightOpenClose
//         ) == false )
//     {
//         return false;
//     }


//     if ( BoxAdjust (
//         m_pucThinning,
//         m_pucReduceROI,
//         vectorBox,
//         vectorBoxAdjust,
//         m_lReduceROIWidth,
//         m_lReduceROIHeight,
//         m_lOriginBitDepth,
//         m_pucOTSU
//         ) == false )
//     {
//         return false;
//     }



//     if ( OpenClose (
//         m_pucCombine,
//         m_lReduceROIWidth,
//         m_lReduceROIHeight,
//         m_lOriginBitDepth,
//         1,
//         1,
//         //6, 2, 3, 1, 1, 1, 
//         9, 6, 4, 0, 0, 0, 
//         2,
//         m_pucPixelWeightOpenClose
//         ) == false )
//     {
//         return false;
//     }
// 
//     if ( DoubleFrame (
//         m_pucPixelWeightOpenClose,
//         m_pucDoubleFrame1,
//         m_pucDoubleFrame2,
//         m_lReduceROIWidth,
//         m_lReduceROIHeight,
//         m_lOriginBitDepth,
//         m_llFrameCount,
//         m_pucDoubleFrame
//         ) == false )
//     {
//         return false;
//     }
// 
//     if ( PixelWeight (
//         m_pucDoubleFrame,
//         m_dbPixelWeight,
//         m_lReduceROIWidth,
//         m_lReduceROIHeight,
//         m_lOriginBitDepth,
//         m_pucPixelWeight
//         ) == false )
//     {
//         return false;
//     }
// 

    return true;
}


bool CAlgorithm::
    AlgProcessing_BitDepth3 ()
{
    return true;
}


bool CAlgorithm::
    AlgProcessing_BitDepth1 ()
{
    return true;
}


/************************************************************************/
/* private - Level 2                                                    */
/************************************************************************/



bool CAlgorithm::
    GetROIRagne (
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
    memset ( pucOutImage1, 0x00, lROILength );
    for ( lY = lInROISY; lY <= lInROIEY; lY++ )
    {
        for ( lX = lInROISX; lX <= lInROIEX; lX++ )
        {
            lSrcIndex = ( lY * lInOriginWidth * lInOriginBitDepth ) + ( lX * lInOriginBitDepth );
            lDstIndex = ( lYY * lInROIWidth * lInROIBitDepth ) + ( lXX * lInROIBitDepth );
            if ( lInOriginBitDepth == 4 )
            {
                ucR = pucInImage1 [ lSrcIndex + 2 ];
                ucG = pucInImage1 [ lSrcIndex + 1 ];
                ucB = pucInImage1 [ lSrcIndex + 0 ];
                pucOutImage1 [ lDstIndex + 3 ] = ucR;
                pucOutImage1 [ lDstIndex + 2 ] = ucR;
                pucOutImage1 [ lDstIndex + 1 ] = ucG;
                pucOutImage1 [ lDstIndex + 0 ] = ucB;
            }
            else if ( lInOriginBitDepth == 3 )
            {
                ucR = pucInImage1 [ lSrcIndex + 2 ];
                ucG = pucInImage1 [ lSrcIndex + 1 ];
                ucB = pucInImage1 [ lSrcIndex + 0 ];
                pucOutImage1 [ lDstIndex + 2 ] = ucR;
                pucOutImage1 [ lDstIndex + 1 ] = ucG;
                pucOutImage1 [ lDstIndex + 0 ] = ucB;
            }
            else if ( lInOriginBitDepth == 1 )
            {
                ucY = pucInImage1 [ lSrcIndex ];
                pucOutImage1 [ lDstIndex ] = ucY;
            }
            lXX++;
        }
        lYY++;
        lXX = 0;
    }
    return true;
}



bool CAlgorithm::
    ReduceImage ( 
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
    double dbXRate = double ( iReduceWidth ) / double ( iWidth );
    double dbYRate = double ( iReduceHeight ) / double ( iHeight );
    for ( iY = 0; iY < iHeight; iY++ )
    {
        iYY = int ( iY * dbYRate );
        for ( iX = 0; iX < iWidth; iX++ )
        {
            iXX = int ( iX * dbXRate );
            lSourceIndex = long ( ( iY * iBitDepth ) * iWidth ) + 
                long ( iX * iBitDepth );
            lDestinationIndex = long ( ( double( iYY * iBitDepth ) ) * iReduceWidth ) + 
                long ( ( iXX * iBitDepth ) );
            switch ( iReduceBitDepth )
            {
            case 4:
                pOutImage [ lDestinationIndex + 3 ] = pInImage [ lSourceIndex + 3 ];
                pOutImage [ lDestinationIndex + 2 ] = pInImage [ lSourceIndex + 2 ];
                pOutImage [ lDestinationIndex + 1 ] = pInImage [ lSourceIndex + 1 ];
                pOutImage [ lDestinationIndex + 0 ] = pInImage [ lSourceIndex + 0 ];
                break;
            case 3:
                pOutImage [ lDestinationIndex + 2 ] = pInImage [ lSourceIndex + 2 ];
                pOutImage [ lDestinationIndex + 1 ] = pInImage [ lSourceIndex + 1 ];
                pOutImage [ lDestinationIndex + 0 ] = pInImage [ lSourceIndex + 0 ];
                break;
            case 1:
                pOutImage [ lDestinationIndex + 0 ] = pInImage [ lSourceIndex + 0 ];
                break;
            default:
                return true;
            }
        }
    }
    return true;
}



bool CAlgorithm::
    SobelFilter8Direction ( 
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
        { -1, -4, -1 },
        {  0,  0,  0 },
        {  1,  4,  1 }
    };
    int iHMU[3][3] = 
    {
        {  1,  4,  1 },
        {  0,  0,  0 },
        { -1, -4, -1 }
    };
    int iVMR[3][3] = 
    {
        { -1,  0,  1 },
        { -4,  0,  4 },
        { -1,  0,  1 }
    };
    int iVML[3][3] = 
    {
        { 1,  0, -1 },
        { 4,  0, -4 },
        { 1,  0, -1 }
    };
    int iRMT[3][3] = 
    {
        { -4, -1,  0 },
        { -1,  0,  1 },
        {  0,  1,  4 }
    };
    int iRMB[3][3] = 
    {
        {  0,  1,  4 },
        { -1,  0,  1 },
        { -4, -1,  0 }
    };
    int iLMT[3][3] = 
    {
        { 0, -1, -4 },
        { 1,  0, -1 },
        { 4,  1,  0 }
    };
    int iLMB[3][3] = 
    {
        { 4,  1,  0 },
        { 1,  0, -1 },
        { 0, -1, -4 }
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
    for ( iY = 0 + iRange; iY < iHeight - iRange; iY++ )
    {
        for ( iX = 0 + iRange; iX < iWidth - iRange; iX++ )
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
            lIndex = ( iY * iWidth * iBitDepth ) + ( iX * iBitDepth );
            for ( iYY = -(iRange); iYY <= iRange; iYY++ )
            {
                for ( iXX = -(iRange); iXX <= iRange; iXX++ )
                {
                    lRangeIndex = ( ( iY + iYY ) * iWidth * iBitDepth ) + 
                        ( ( iX + iXX ) * iBitDepth );
                    iPSHDY +=  
                        pInImage [ lRangeIndex + 2 ] * 
                        ( iHMD [ iYY + iRange ][ iXX + iRange ] );
                    iPSHDU +=  
                        pInImage [ lRangeIndex + 1 ] * 
                        ( iHMD [ iYY + iRange ][ iXX + iRange ] );
                    iPSHDV +=  
                        pInImage [ lRangeIndex + 0 ] * 
                        ( iHMD [ iYY + iRange ][ iXX + iRange ] );
                    iPSHUY +=  
                        pInImage [ lRangeIndex + 2 ] * 
                        ( iHMU [ iYY + iRange ][ iXX + iRange ] );
                    iPSHUU +=  
                        pInImage [ lRangeIndex + 1 ] * 
                        ( iHMU [ iYY + iRange ][ iXX + iRange ] );
                    iPSHUV +=  
                        pInImage [ lRangeIndex + 0 ] * 
                        ( iHMU [ iYY + iRange ][ iXX + iRange ] );
                    iPSVRY += 
                        pInImage [ lRangeIndex + 2 ] * 
                        ( iVMR [ iYY + iRange ][ iXX + iRange ] );
                    iPSVRU += 
                        pInImage [ lRangeIndex + 1 ] * 
                        ( iVMR [ iYY + iRange ][ iXX + iRange ] );
                    iPSVRV += 
                        pInImage [ lRangeIndex + 0 ] * 
                        ( iVMR [ iYY + iRange ][ iXX + iRange ] );
                    iPSVLY += 
                        pInImage [ lRangeIndex + 2 ] * 
                        ( iVML [ iYY + iRange ][ iXX + iRange ] );
                    iPSVLU += 
                        pInImage [ lRangeIndex + 1 ] * 
                        ( iVML [ iYY + iRange ][ iXX + iRange ] );
                    iPSVLV += 
                        pInImage [ lRangeIndex + 0 ] * 
                        ( iVML [ iYY + iRange ][ iXX + iRange ] );
                    iPSRTY += 
                        pInImage [ lRangeIndex + 2 ] * 
                        ( iRMT [ iYY + iRange ][ iXX + iRange ] );
                    iPSRTU += 
                        pInImage [ lRangeIndex + 1 ] * 
                        ( iRMT [ iYY + iRange ][ iXX + iRange ] );
                    iPSRTV += 
                        pInImage [ lRangeIndex + 0 ] * 
                        ( iRMT [ iYY + iRange ][ iXX + iRange ] );
                    iPSRBY += 
                        pInImage [ lRangeIndex + 2 ] * 
                        ( iRMB [ iYY + iRange ][ iXX + iRange ] );
                    iPSRBU += 
                        pInImage [ lRangeIndex + 1 ] * 
                        ( iRMB [ iYY + iRange ][ iXX + iRange ] );
                    iPSRBV += 
                        pInImage [ lRangeIndex + 0 ] * 
                        ( iRMB [ iYY + iRange ][ iXX + iRange ] );
                    iPSLTY += 
                        pInImage [ lRangeIndex + 2 ] * 
                        ( iLMT [ iYY + iRange ][ iXX + iRange ] );
                    iPSLTU += 
                        pInImage [ lRangeIndex + 1 ] * 
                        ( iLMT [ iYY + iRange ][ iXX + iRange ] );
                    iPSLTV += 
                        pInImage [ lRangeIndex + 0 ] * 
                        ( iLMT [ iYY + iRange ][ iXX + iRange ] );
                    iPSLBY += 
                        pInImage [ lRangeIndex + 2 ] * 
                        ( iLMB [ iYY + iRange ][ iXX + iRange ] );
                    iPSLBU += 
                        pInImage [ lRangeIndex + 1 ] * 
                        ( iLMB [ iYY + iRange ][ iXX + iRange ] );
                    iPSLBV += 
                        pInImage [ lRangeIndex + 0 ] * 
                        ( iLMB [ iYY + iRange ][ iXX + iRange ] );
                }
            }
            iPMY = max ( max ( max ( max ( max ( max ( max ( iPSHDY, iPSVRY ), iPSVLY ), iPSHUY ), iPSRTY ), iPSRBY ), iPSLTY ), iPSLBY );
            if ( iPMY > 255 ) { iPMY = 255; }
            if ( iPMY < 0 ) { iPMY = 0; }
            iPMU = max ( max ( max ( max ( max ( max ( max ( iPSHDU, iPSVRU ), iPSVLU ), iPSHUU ), iPSRTU ), iPSRBU ), iPSLTU ), iPSLBU );
            if ( iPMU > 255 ) { iPMU = 255; }
            if ( iPMU < 0 ) { iPMU = 0; }
            iPMV = max ( max ( max ( max ( max ( max ( max ( iPSHDV, iPSVRV ), iPSVLV ), iPSHUV ), iPSRTV ), iPSRBV ), iPSLTV ), iPSLBV );
            if ( iPMV > 255 ) { iPMV = 255; }
            if ( iPMV < 0 ) { iPMV = 0; }
            int iPX = max ( max ( iPMY, iPMU ), iPMV );
            if ( iPX >= 255 ) { iPX = 255; }
            if ( iPX <= 0 ) { iPX = 0; }
            lIndex = ( iY * iWidth * iBitDepth ) + ( iX * iBitDepth );
            pOutSF [ lIndex + 2 ] = unsigned char(iPX);
            pOutSF [ lIndex + 1 ] = unsigned char(iPX);
            pOutSF [ lIndex + 0 ] = unsigned char(iPX);
        }
    }
    return true;
}



bool CAlgorithm::
    ContrastFilter8Direction ( 
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
        {  0, -4,  0 },
        {  0,  4,  0 },
        {  0,  0,  0 }
    };
    int iHMU[3][3] = 
    {
        {  0,  0,  0 },
        {  0,  4,  0 },
        {  0, -4,  0 }
    };
    int iVMR[3][3] = 
    {
        {  0,  0,  0 },
        { -4,  4,  0 },
        {  0,  0,  0 }
    };
    int iVML[3][3] = 
    {
        { 0,  0,  0 },
        { 0,  4, -4 },
        { 0,  0,  0 }
    };
    int iRMT[3][3] = 
    {
        { -4,  0,  0 },
        {  0,  4,  0 },
        {  0,  0,  0 }
    };
    int iRMB[3][3] = 
    {
        {  0,  0,  0 },
        {  0,  4,  0 },
        { -4,  0,  0 }
    };
    int iLMT[3][3] = 
    {
        { 0,  0, -4 },
        { 0,  4,  0 },
        { 0,  0,  0 }
    };
    int iLMB[3][3] = 
    {
        { 0,  0,   0 },
        { 0,  4,   0 },
        { 0,  0,  -4 }
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
    for ( iY = 0 + iRange; iY < iHeight - iRange; iY++ )
    {
        for ( iX = 0 + iRange; iX < iWidth - iRange; iX++ )
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
            lIndex = ( iY * iWidth * iBitDepth ) + ( iX * iBitDepth );
            for ( iYY = -(iRange); iYY <= iRange; iYY++ )
            {
                for ( iXX = -(iRange); iXX <= iRange; iXX++ )
                {
                    lRangeIndex = ( ( iY + iYY ) * iWidth * iBitDepth ) + 
                        ( ( iX + iXX ) * iBitDepth );
                    iPSHDY +=  
                        pInImage [ lRangeIndex + 2 ] * 
                        ( iHMD [ iYY + iRange ][ iXX + iRange ] );
                    iPSHDU +=  
                        pInImage [ lRangeIndex + 1 ] * 
                        ( iHMD [ iYY + iRange ][ iXX + iRange ] );
                    iPSHDV +=  
                        pInImage [ lRangeIndex + 0 ] * 
                        ( iHMD [ iYY + iRange ][ iXX + iRange ] );
                    iPSHUY +=  
                        pInImage [ lRangeIndex + 2 ] * 
                        ( iHMU [ iYY + iRange ][ iXX + iRange ] );
                    iPSHUU +=  
                        pInImage [ lRangeIndex + 1 ] * 
                        ( iHMU [ iYY + iRange ][ iXX + iRange ] );
                    iPSHUV +=  
                        pInImage [ lRangeIndex + 0 ] * 
                        ( iHMU [ iYY + iRange ][ iXX + iRange ] );
                    iPSVRY += 
                        pInImage [ lRangeIndex + 2 ] * 
                        ( iVMR [ iYY + iRange ][ iXX + iRange ] );
                    iPSVRU += 
                        pInImage [ lRangeIndex + 1 ] * 
                        ( iVMR [ iYY + iRange ][ iXX + iRange ] );
                    iPSVRV += 
                        pInImage [ lRangeIndex + 0 ] * 
                        ( iVMR [ iYY + iRange ][ iXX + iRange ] );
                    iPSVLY += 
                        pInImage [ lRangeIndex + 2 ] * 
                        ( iVML [ iYY + iRange ][ iXX + iRange ] );
                    iPSVLU += 
                        pInImage [ lRangeIndex + 1 ] * 
                        ( iVML [ iYY + iRange ][ iXX + iRange ] );
                    iPSVLV += 
                        pInImage [ lRangeIndex + 0 ] * 
                        ( iVML [ iYY + iRange ][ iXX + iRange ] );
                    iPSRTY += 
                        pInImage [ lRangeIndex + 2 ] * 
                        ( iRMT [ iYY + iRange ][ iXX + iRange ] );
                    iPSRTU += 
                        pInImage [ lRangeIndex + 1 ] * 
                        ( iRMT [ iYY + iRange ][ iXX + iRange ] );
                    iPSRTV += 
                        pInImage [ lRangeIndex + 0 ] * 
                        ( iRMT [ iYY + iRange ][ iXX + iRange ] );
                    iPSRBY += 
                        pInImage [ lRangeIndex + 2 ] * 
                        ( iRMB [ iYY + iRange ][ iXX + iRange ] );
                    iPSRBU += 
                        pInImage [ lRangeIndex + 1 ] * 
                        ( iRMB [ iYY + iRange ][ iXX + iRange ] );
                    iPSRBV += 
                        pInImage [ lRangeIndex + 0 ] * 
                        ( iRMB [ iYY + iRange ][ iXX + iRange ] );
                    iPSLTY += 
                        pInImage [ lRangeIndex + 2 ] * 
                        ( iLMT [ iYY + iRange ][ iXX + iRange ] );
                    iPSLTU += 
                        pInImage [ lRangeIndex + 1 ] * 
                        ( iLMT [ iYY + iRange ][ iXX + iRange ] );
                    iPSLTV += 
                        pInImage [ lRangeIndex + 0 ] * 
                        ( iLMT [ iYY + iRange ][ iXX + iRange ] );
                    iPSLBY += 
                        pInImage [ lRangeIndex + 2 ] * 
                        ( iLMB [ iYY + iRange ][ iXX + iRange ] );
                    iPSLBU += 
                        pInImage [ lRangeIndex + 1 ] * 
                        ( iLMB [ iYY + iRange ][ iXX + iRange ] );
                    iPSLBV += 
                        pInImage [ lRangeIndex + 0 ] * 
                        ( iLMB [ iYY + iRange ][ iXX + iRange ] );
                }
            }
            iPMY = max ( max ( max ( max ( max ( max ( max ( iPSHDY, iPSVRY ), iPSVLY ), iPSHUY ), iPSRTY ), iPSRBY ), iPSLTY ), iPSLBY );
            if ( iPMY > 255 ) { iPMY = 255; }
            if ( iPMY < 0 ) { iPMY = 0; }
            iPMU = max ( max ( max ( max ( max ( max ( max ( iPSHDU, iPSVRU ), iPSVLU ), iPSHUU ), iPSRTU ), iPSRBU ), iPSLTU ), iPSLBU );
            if ( iPMU > 255 ) { iPMU = 255; }
            if ( iPMU < 0 ) { iPMU = 0; }
            iPMV = max ( max ( max ( max ( max ( max ( max ( iPSHDV, iPSVRV ), iPSVLV ), iPSHUV ), iPSRTV ), iPSRBV ), iPSLTV ), iPSLBV );
            if ( iPMV > 255 ) { iPMV = 255; }
            if ( iPMV < 0 ) { iPMV = 0; }
            int iPX = max( max ( iPMY, iPMU ), iPMV );
            if ( iPX >= 255 ) { iPX = 255; }
            if ( iPX <= 0 ) { iPX = 0; }
            lIndex = ( iY * iWidth * iBitDepth ) + ( iX * iBitDepth );
            pOutSF [ lIndex + 2 ] = unsigned char(iPX);
            pOutSF [ lIndex + 1 ] = unsigned char(iPX);
            pOutSF [ lIndex + 0 ] = unsigned char(iPX);
        }
    }
    return true;
}



bool CAlgorithm::
    CombineImage (
    unsigned char* pucInImage1,
    unsigned char* pucInImage2,
    int iInWidth,
    int iInHeight,
    int iInBitDepth,
    char* cInCommand,
    unsigned char* pucOutCombineImage
    )
{
    if (
        (pucInImage1 == NULL) ||
        (pucInImage2 == NULL)
        )
    {
        return false;
    }
    int iPixel1A = 0;
    int iPixel1B = 0;
    int iPixel1C = 0;
    int iPixel2A = 0;
    int iPixel2B = 0;
    int iPixel2C = 0;
    int iPixelA = 0;
    int iPixelB = 0;
    int iPixelC = 0;
    int iIndex = 0;
    int iCommand = 0;
    memset(pucOutCombineImage, 0x00, iInWidth * iInHeight * iInBitDepth * sizeof(unsigned char));
    if (strcmp(cInCommand, "ADD") == 0)
    {
        iCommand = 1;
    }
    if (strcmp(cInCommand, "AND") == 0)
    {
        iCommand = 2;
    }
    for ( int iY = 0; iY < iInHeight; iY++ )
    {
        for ( int iX = 0; iX < iInWidth; iX++ )
        {
            iIndex = ( iY * iInWidth * iInBitDepth ) + ( iX * iInBitDepth );
            iPixel1A = pucInImage1 [ iIndex + 2 ];
            iPixel1B = pucInImage1 [ iIndex + 1 ];
            iPixel1C = pucInImage1 [ iIndex + 0 ];
            iPixel2A = pucInImage2 [ iIndex + 2 ];
            iPixel2B = pucInImage2 [ iIndex + 1 ];
            iPixel2C = pucInImage2 [ iIndex + 0 ];
            if (iCommand == 1)
            {
                iPixelA = iPixel1A + iPixel2A >= 255 ? 255 : iPixel1A + iPixel2A;
                pucOutCombineImage[iIndex + 2] = iPixelA;
                pucOutCombineImage[iIndex + 1] = iPixelA;
                pucOutCombineImage[iIndex + 0] = iPixelA;
            }
            if (iCommand == 2)
            {
                if (iPixel1A > 0 && iPixel2A > 0)
                {
                    pucOutCombineImage[iIndex + 2] = 255;
                    pucOutCombineImage[iIndex + 1] = 255;
                    pucOutCombineImage[iIndex + 0] = 255;
                }
            }
        }
    }
    return true;
}


bool CAlgorithm::
InterFrameImage(
    unsigned char* pucInImage1,
    unsigned char* pucImage1,
    unsigned char* pucImage2,
    int iInWidth,
    int iInHeight,
    int iInBitDepth,
    long lInFrameCount,
    unsigned char* pucOutImage1
)
{
    if (
        pucInImage1 == NULL ||
        pucImage1 == NULL ||
        pucImage2 == NULL ||
        pucOutImage1 == NULL
        )
    {
        return false;
    }
    int iRGB1_R = 0;
    int iRGB1_G = 0;
    int iRGB1_B = 0;
    int iRGB2_R = 0;
    int iRGB2_G = 0;
    int iRGB2_B = 0;
    int iRGB_R = 0;
    int iRGB_G = 0;
    int iRGB_B = 0;
    int iFrameIndex = 0;
    int iIndex = 0;
    int iX = 0;
    int iY = 0;
    iFrameIndex = ((lInFrameCount - 1) % 2) + 1;
    if (iFrameIndex == 1)
    {
        memcpy(pucImage1, pucInImage1, iInWidth * iInHeight * iInBitDepth * sizeof(unsigned char));
    }
    else if (iFrameIndex == 2)
    {
        memcpy(pucImage2, pucInImage1, iInWidth * iInHeight * iInBitDepth * sizeof(unsigned char));
    }
    if (lInFrameCount < 2)
    {
        return true;
    }
    for (iY = 0; iY < iInHeight; iY++)
    {
        for (iX = 0; iX < iInWidth; iX++)
        {
            iIndex = (iY * iInWidth * iInBitDepth) + (iX * iInBitDepth);
            iRGB1_R = pucImage1[iIndex + 2];
            iRGB1_G = pucImage1[iIndex + 1];
            iRGB1_B = pucImage1[iIndex + 0];
            iRGB2_R = pucImage2[iIndex + 2];
            iRGB2_G = pucImage2[iIndex + 1];
            iRGB2_B = pucImage2[iIndex + 0];
            iRGB_R = abs (iRGB1_R - iRGB2_R) >= 255 ? 255 : abs(iRGB1_R - iRGB2_R);
            pucOutImage1[iIndex + 2] = iRGB_R;
            pucOutImage1[iIndex + 1] = iRGB_R;
            pucOutImage1[iIndex + 0] = iRGB_R;
        }
    }
    return true;
}


bool CAlgorithm::
BinaryUsingHistogram(
    unsigned char* pucInImage,
    long lInWidth,
    long lInHeight,
    long lInBitDepth,
    float fInMiddleDivision,
    unsigned char* pucOutImage
)
{
    if (
        pucInImage == NULL ||
        lInWidth <= 0 ||
        lInHeight <= 0 ||
        lInBitDepth <= 0
        )
    {
        return false;
    }
    long lIndexImage = 0;
    int iHistogram[256];
    int iCount = 0;
    int iMiddleCount = 0;
    memset(pucOutImage, 0x00, lInWidth * lInHeight * lInBitDepth);
    memset(&iHistogram, 0x00, 256 * sizeof(int));

    for (int iY = 0; iY < lInHeight; iY++)
    {
        for (int iX = 0; iX < lInWidth; iX++)
        {
            lIndexImage = (iY * lInWidth * lInBitDepth) + (iX * lInBitDepth);
            iHistogram[pucInImage[lIndexImage + 2]] = 1;
        }
    }

    for (int iI = 0; iI < 256; iI++)
    {
        if (iHistogram[iI] == 1)
        {
            iCount++;
        }
    }

    iMiddleCount = iCount / fInMiddleDivision;
    for (int iI = 0; iI < 256; iI++)
    {
        if (iHistogram[iI] == 1)
        {
            iMiddleCount--;
            if (iMiddleCount == 0)
            {
                fInMiddleDivision = iI;
                break;
            }
        }
    }

    for (int iY = 0; iY < lInHeight; iY++)
    {
        for (int iX = 0; iX < lInWidth; iX++)
        {
            lIndexImage = (iY * lInWidth * lInBitDepth) + (iX * lInBitDepth);
            if (pucInImage[lIndexImage + 2] > fInMiddleDivision)
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
RedAdjustMiddle(
    unsigned char* pInImage,
    int iInWidth,
    int iInHeight,
    int iInBitDepth,
    double dbDivision,
    int* iOutRedMean
)
{
    long lSourceIndex = 0;
    int iY = 0;
    int iX = 0;
    int iWidth = iInWidth;
    int iHeight = iInHeight;
    int iBitDepth = iInBitDepth;
    double dbRedSum = 0.0f;

    int iHistogram[256];
    int iCount = 0;
    int iMiddleCount = 0;
    memset(&iHistogram, 0x00, 256 * sizeof(int));

    for (int iY = 0; iY < iHeight; iY++)
    {
        for (int iX = 0; iX < iWidth; iX++)
        {
            lSourceIndex = (iY * iWidth * iBitDepth) + (iX * iBitDepth);
            iHistogram[pInImage[lSourceIndex + 2]] = 1;
        }
    }

    for (int iI = 0; iI < 256; iI++)
    {
        if (iHistogram[iI] == 1)
        {
            iCount++;
        }
    }

    iMiddleCount = iCount / dbDivision;
    for (int iI = 0; iI < 256; iI++)
    {
        if (iHistogram[iI] == 1)
        {
            iMiddleCount--;
            if (iMiddleCount == 0)
            {
                *iOutRedMean = iI;
                break;
            }
        }
    }
	return true;
}


bool CAlgorithm::
FireRegionIsolationImage(
    unsigned char* pInImage1,
    unsigned char* pInImage2,
    int iInWidth,
    int iInHeight,
    int iInBitDepth,
    int iInRedThreshold,
    int iInSaturationThreshold,
    unsigned char* pOutImage
)
{
    long lSourceIndex = 0;
    int iY = 0;
    int iX = 0;
    int iWidth = iInWidth;
    int iHeight = iInHeight;
    int iBitDepth = iInBitDepth;
    rgb RGBIn;
    hsv HSVOut;
    hsi HSIOut;
    memset(pOutImage, 0x00, iWidth * iHeight * iBitDepth * sizeof(unsigned char));
    /****************************/
    // 1. R > RT
    // 2. R > G > B
    // 3. S > (ST(255 - R)) / RT
    /****************************/
    for (iY = 0; iY < iHeight; iY++)
    {
        for (iX = 0; iX < iWidth; iX++)
        {
            lSourceIndex = long((iY * iBitDepth) * iWidth) + long(iX * iBitDepth);
            if (pInImage2[lSourceIndex + 2] != 255)
            {
                continue;
            }
            switch (iBitDepth)
            {
            case 4:
                RGBIn.r = pInImage1[lSourceIndex + 2];
                RGBIn.g = pInImage1[lSourceIndex + 1];
                RGBIn.b = pInImage1[lSourceIndex + 0];
                if (RGBIn.r > iInRedThreshold)
                {
                    if (
                        (RGBIn.r > RGBIn.g) &&
                        (RGBIn.g > RGBIn.b)
                        )
                    {
                        HSI(
                            IN RGBIn.r,
                            IN RGBIn.g,
                            IN RGBIn.b,
                            OUT HSVOut.h,
                            OUT HSVOut.s,
                            OUT HSVOut.v
                        );
                        if (HSVOut.s > ((iInSaturationThreshold * (255 - RGBIn.r)) / iInRedThreshold))
                        {
                            pOutImage[lSourceIndex + 3] = pInImage1[lSourceIndex + 3];
                            pOutImage[lSourceIndex + 2] = pInImage1[lSourceIndex + 2];
                            pOutImage[lSourceIndex + 1] = pInImage1[lSourceIndex + 1];
                            pOutImage[lSourceIndex + 0] = pInImage1[lSourceIndex + 0];
                        }
                    }
                }
                break;
            case 3:
                RGBIn.r = pInImage1[lSourceIndex + 2];
                RGBIn.g = pInImage1[lSourceIndex + 1];
                RGBIn.b = pInImage1[lSourceIndex + 0];
                if (RGBIn.r > iInRedThreshold)
                {
                    if (
                        (RGBIn.r > RGBIn.g) &&
                        (RGBIn.g > RGBIn.b)
                        )
                    {
                        HSI(
                            IN RGBIn.r,
                            IN RGBIn.g,
                            IN RGBIn.b,
                            OUT HSVOut.h,
                            OUT HSVOut.s,
                            OUT HSVOut.v
                        );
                        if (HSVOut.s > ((iInSaturationThreshold * (255 - RGBIn.r)) / iInRedThreshold))
                        {
                            pOutImage[lSourceIndex + 2] = pInImage1[lSourceIndex + 2];
                            pOutImage[lSourceIndex + 1] = pInImage1[lSourceIndex + 1];
                            pOutImage[lSourceIndex + 0] = pInImage1[lSourceIndex + 0];
                        }
                    }
                }
                break;
            case 1:
                return true;
                break;
            default:
                return true;
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
    rgb RGBIn;
    memset(pOutImage, 0x00, iWidth * iHeight * iBitDepth * sizeof(unsigned char));
    for (iY = 0; iY < iHeight; iY++)
    {
        for (iX = 0; iX < iWidth; iX++)
        {
            lSourceIndex = long((iY * iBitDepth) * iWidth) + long(iX * iBitDepth);
            switch (iBitDepth)
            {
            case 4:
                RGBIn.r = pInImage[lSourceIndex + 2];
                RGBIn.g = pInImage[lSourceIndex + 1];
                RGBIn.b = pInImage[lSourceIndex + 0];
                if (
                    (RGBIn.r <= 255 && RGBIn.r >= 117) &&
                    (RGBIn.g <= 255 && RGBIn.g >= 88) &&
                    (RGBIn.b <= 255 && RGBIn.b >= 44)
                    )
                {
                    if (
                        (RGBIn.r == 255) &&
                        (RGBIn.g <= 255 && RGBIn.g >= 183) &&
                        (RGBIn.b <= 219 && RGBIn.b >= 15)
                        )
                    {
                        pOutImage[lSourceIndex + 3] = 0;
                        pOutImage[lSourceIndex + 2] = pInImage[lSourceIndex + 2];
                        pOutImage[lSourceIndex + 1] = pInImage[lSourceIndex + 1];
                        pOutImage[lSourceIndex + 0] = pInImage[lSourceIndex + 0];
                    }
                    if (
                        (RGBIn.r <= 254 && RGBIn.r >= 250) &&
                        (RGBIn.g == 255) &&
                        (RGBIn.b <= 219 && RGBIn.b >= 15)
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
                RGBIn.r = pInImage[lSourceIndex + 2];
                RGBIn.g = pInImage[lSourceIndex + 1];
                RGBIn.b = pInImage[lSourceIndex + 0];
                if (
                    (RGBIn.r <= 255 && RGBIn.r >= 117) &&
                    (RGBIn.g <= 255 && RGBIn.g >= 88) &&
                    (RGBIn.b <= 255 && RGBIn.b >= 44)
                    )
                {
                    if (
                        (RGBIn.r == 255) &&
                        (RGBIn.g <= 255 && RGBIn.g >= 183) &&
                        (RGBIn.b <= 219 && RGBIn.b >= 15)
                        )
                    {
                        pOutImage[lSourceIndex + 2] = pInImage[lSourceIndex + 2];
                        pOutImage[lSourceIndex + 1] = pInImage[lSourceIndex + 1];
                        pOutImage[lSourceIndex + 0] = pInImage[lSourceIndex + 0];
                    }
                    if (
                        (RGBIn.r <= 254 && RGBIn.r >= 250) &&
                        (RGBIn.g == 255) &&
                        (RGBIn.b <= 219 && RGBIn.b >= 15)
                        )
                    {
                        pOutImage[lSourceIndex + 2] = pInImage[lSourceIndex + 2];
                        pOutImage[lSourceIndex + 1] = pInImage[lSourceIndex + 1];
                        pOutImage[lSourceIndex + 0] = pInImage[lSourceIndex + 0];
                    }
                }
                break;
            case 1:
                return true;
                break;
            default:
                return true;
            }
        }
    }
    return true;
}


bool CAlgorithm::
    CombineThreeImage (
    unsigned char* pucInImage1,
    unsigned char* pucInImage2,
    unsigned char* pucInImage3,
    int iInWidth,
    int iInHeight,
    int iInBitDepth,
    int iInRange,
    unsigned char* pucOutCombineThreeImage
    )
{
    if (
        (pucInImage1 == NULL) ||
        (pucInImage2 == NULL) ||
        (pucInImage3 == NULL)
        )
    {
        return false;
    }
    int iPixel1A = 0;
    int iPixel1B = 0;
    int iPixel1C = 0;
    int iPixel2A = 0;
    int iPixel2B = 0;
    int iPixel2C = 0;
    int iPixel3A = 0;
    int iPixel3B = 0;
    int iPixel3C = 0;
    int iPixelA = 0;
    int iPixelB = 0;
    int iPixelC = 0;
    int iIndex = 0;
    int iRangeSX = 0;
    int iRangeSY = 0;
    int iRangeEX = 0;
    int iRangeEY = 0;
    int iIndexRange = 0;
    int iYY = 0;
    int iXX = 0;
    memset(pucOutCombineThreeImage, 0x00, iInWidth * iInHeight * iInBitDepth * sizeof(unsigned char));
    for ( int iY = 0; iY < iInHeight; iY++ )
    {
        for ( int iX = 0; iX < iInWidth; iX++ )
        {
            iIndex = ( iY * iInWidth * iInBitDepth ) + ( iX * iInBitDepth );
            iPixel3A = pucInImage3[iIndex + 2];
            iPixel3B = pucInImage3[iIndex + 1];
            iPixel3C = pucInImage3[iIndex + 0];
            if (iPixel3A > 0)
            {
                pucOutCombineThreeImage[iIndex + 2] = pucInImage3[iIndex + 2];
                pucOutCombineThreeImage[iIndex + 1] = pucInImage3[iIndex + 1];
                pucOutCombineThreeImage[iIndex + 0] = pucInImage3[iIndex + 0];
                iRangeSX = iX - iInRange < 0 ? 0 : iX - iInRange;
                iRangeSY = iY - iInRange < 0 ? 0 : iY - iInRange;
                iRangeEX = iX + iInRange > iInWidth - 1 ? iInWidth - 1 : iX + iInRange;
                iRangeEY = iY + iInRange > iInHeight - 1 ? iInHeight - 1 : iY + iInRange;
                for (iYY = iRangeSY; iYY < iRangeEY; iYY++)
                {
                    for (iXX = iRangeSX; iXX < iRangeEX; iXX++)
                    {
                        iIndexRange = (iYY * iInWidth * iInBitDepth) + (iXX * iInBitDepth);
                        iPixel1A = pucInImage1[iIndexRange + 2];
                        iPixel1B = pucInImage1[iIndexRange + 1];
                        iPixel1C = pucInImage1[iIndexRange + 0];
                        iPixel2A = pucInImage2[iIndexRange + 2];
                        iPixel2B = pucInImage2[iIndexRange + 1];
                        iPixel2C = pucInImage2[iIndexRange + 0];
                        if (iPixel1A > 0 && iPixel2A > 0)
                        {
                            pucOutCombineThreeImage[iIndexRange + 2] = pucInImage3[iIndexRange + 2];
                            pucOutCombineThreeImage[iIndexRange + 1] = pucInImage3[iIndexRange + 1];
                            pucOutCombineThreeImage[iIndexRange + 0] = pucInImage3[iIndexRange + 0];
                        }
                    }
                }
            }
        }
    }
    return true;
}


bool CAlgorithm::
	LabelingCreateMemory (
    unsigned char* pucInImage1,
    int iInWidth,
    int iInHeight,
    int iInBitDepth,
	int* piOutData1,
	int* piOutData2
    )
{
    int iY = 0;
    int iX = 0;
    int iIndexSource = 0;
    int iIndexDestination = 0;
    memset ( piOutData1, 0x00, iInWidth * iInHeight * sizeof(int) );
    memset ( piOutData2, 0x00, iInWidth * iInHeight * sizeof(int) );

    for ( iY = 1; iY <= iInHeight - 2; iY++ )
    {
        for ( iX = 1; iX <= iInWidth - 2; iX++ )
        {
            iIndexSource = ( iY * iInWidth * iInBitDepth ) + ( iX * iInBitDepth );
            iIndexDestination = (iY * iInWidth) + (iX);
            if ( pucInImage1 [iIndexSource] > 0 )
            {
                piOutData1 [ iIndexDestination ] = 1;
            }
            else
            {
				piOutData1 [ iIndexDestination ] = 0;
            }
        }
    }
    return true;
}


bool CAlgorithm::
	LabelingTracer(
	int* piInData1,
	int* piInData2,
	int* iCy,
	int* iCx,
	int* iTracingDirection,
	int iInWidth,
	int iInHeight
)
{
	int iI = 0;
	int iY = 0;
	int iX = 0;
	int iIndex = 0;
	for (iI = 0; iI < 7; iI++)
	{
		iY = *iCy + SearchDirection[*iTracingDirection][0];
		iX = *iCx + SearchDirection[*iTracingDirection][1];
		iIndex = (iY * iInWidth) + (iX);
		if (piInData1[iIndex] == 0)
		{
			piInData2[iIndex] = -1;
			*iTracingDirection = (*iTracingDirection + 1) % 8;
		}
		else
		{
			*iCy = iY;
			*iCx = iX;
			break;
		}
	}
    return true;
}


bool CAlgorithm::
	LabelingContourTracing(
    int* piInData1,
    int* piInData2,
	int iCy,
	int iCx,
	int iLabelIndex,
	int iTracingDirection,
	int iInWidth,
	int iInHeight
)
{
	int iTracingStopFlag = 0;
    int iSearchAgain = 1;
	int iFx = 0;
	int iFy = 0;
	int iSx = iCx;
	int iSy = iCy;
	int iIndex = 0;

    if (LabelingTracer(
        piInData1,
        piInData2,
        &iCy,
        &iCx,
        &iTracingDirection,
        iInWidth,
        iInHeight
    ) == false)
    {
        return false;
    }
    
	if (iCx != iSx || iCy != iSy)
	{
		iFx = iCx;
		iFy = iCy;

		while (iSearchAgain)
		{
			iTracingDirection = (iTracingDirection + 6) % 8;
			iIndex = (iCy * iInWidth) + (iCx);
            piInData2[iIndex] = iLabelIndex;

            if (LabelingTracer(
                piInData1,
                piInData2,
                &iCy,
                &iCx,
                &iTracingDirection,
                iInWidth,
                iInHeight
            ) == false)
            {
                return false;
            }

			if (iCx == iSx && iCy == iSy)
			{
			    iTracingStopFlag = 1;
			}
			else if (iTracingStopFlag)
			{
				if (iCx == iFx && iCy == iFy)
				{
					iSearchAgain = 0;
				}
				else
				{
					iTracingStopFlag = 0;
				}
			}
		}
	}
    return true;
}


bool CAlgorithm::
    ConnectedComponentLabeling(
    int* piInData1,
    int* piInData2,
    int iInWidth,
    int iInHeight,
    int* iOutLabelTotalNumber
)
{
    int iCx = 0;
    int iCy = 0; 
    int iTracingDirection = 0; 
    int iConnectedComponentsCount = 0;
    int iLabelIndex = 0;
    int iIndex = 0;
    for (iCy = 1; iCy < iInHeight - 1; iCy++)
    {
        for (iCx = 1, iLabelIndex = 0; iCx < iInWidth - 1; iCx++)
        {
            iIndex = (iCy * iInWidth) + (iCx);
            if (piInData1[iIndex] == 1)
            {
                // use pre-pixel label
                if (iLabelIndex != 0) 
                {
                    piInData2[iIndex] = iLabelIndex;
                }
                else
                {
                    iLabelIndex = piInData2[iIndex];
                    if (iLabelIndex == 0)
                    {
                        iLabelIndex = ++iConnectedComponentsCount;
                        iTracingDirection = 0;
                        // external contour
                        if (LabelingContourTracing(
                            piInData1,
                            piInData2,
                            iCy,
                            iCx,
                            iLabelIndex,
                            iTracingDirection,
                            iInWidth,
                            iInHeight
                        ) == false)
                        {
                            return false;
                        }
                        piInData2[iIndex] = iLabelIndex;
                    }
                }
            }
            // white pixel & pre-pixel has been labeled
            else if (iLabelIndex != 0)
            {
                if (piInData2[iIndex] == 0)
                {
                    iTracingDirection = 1;
                    // internal contour
                    if (LabelingContourTracing(
                        piInData1,
                        piInData2,
                        iCy,
                        iCx - 1,
                        iLabelIndex,
                        iTracingDirection,
                        iInWidth,
                        iInHeight
                    ) == false)
                    {
                        return false;
                    }
                }
                iLabelIndex = 0;
            }
        }
    }
    *iOutLabelTotalNumber = iConnectedComponentsCount;
    return true;
}


bool CAlgorithm::
    LabelToBitDepth4(
    int* piInImage1,
    int iInWidth,
    int iInHeight,
    int iInBitDepth,
    int iInLabelTotalNumber,
    unsigned char* pucOutImage1
)
{
    int iI = 0;
    int iY = 0;
    int iX = 0;
    int iIndexSource = 0;
    int iIndexDestination = 0;
    memset(pucOutImage1, 0x00, iInWidth * iInHeight * iInBitDepth);
    int iRGB_R = 0;
    int iRGB_G = 0;
    int iRGB_B = 0;
    srand(time(NULL));
    for (iI = 1; iI <= iInLabelTotalNumber; iI++)
    {
        iRGB_R = (rand() % 255) + 1;
        iRGB_G = (rand() % 255) + 1;
        iRGB_B = (rand() % 255) + 1;
        for (iY = 0; iY < iInHeight; iY++)
        {
            for (iX = 0; iX < iInWidth; iX++)
            {
                iIndexSource = (iY * iInWidth) + (iX);
                iIndexDestination = (iY * iInBitDepth * iInWidth) + (iX * iInBitDepth);
                if (piInImage1[iIndexSource] == iI)
                {
                    pucOutImage1[iIndexDestination + 3] = 0;
                    pucOutImage1[iIndexDestination + 2] = iRGB_R;
                    pucOutImage1[iIndexDestination + 1] = iRGB_G;
                    pucOutImage1[iIndexDestination + 0] = iRGB_B;
                }
            }
        }
    }
    return true;
}



bool CAlgorithm:: 
    PixelWeight (
    unsigned char* pucInImage1,
    double* pdbInImage2,
    long lInReduceWidth,
    long lInReduceHeight,
    long lInBitDepth,
    unsigned char* pucOutImage1
    )
{
    long lY = 0;
    long lX = 0;
    long lIndex = 0;
	long lYY = 0;
	long lXX = 0;
	long lIndexRange = 0;
	int iRange = 5;
	long lRGB1_R = 0;
	long lRGB1_G = 0;
	long lRGB1_B = 0;
	int iCount = 0;
	memset(pucOutImage1, 0x00, lInReduceWidth * lInReduceHeight * lInBitDepth * sizeof(unsigned char));
	for (lY = iRange; lY < lInReduceHeight - iRange; lY++)
	{
		for (lX = iRange; lX < lInReduceWidth - iRange; lX++)
		{
			lIndex = (lY * lInReduceWidth * lInBitDepth) + (lX * lInBitDepth);
			lRGB1_R = pucInImage1[lIndex + 2];
			lRGB1_G = pucInImage1[lIndex + 1];
			lRGB1_B = pucInImage1[lIndex + 0];
			if (lRGB1_R == 255)
			{
				iCount = 0;
				for (lYY = lY - (iRange); lYY <= lY + (iRange); lYY++)
				{
					for (lXX = lX - (iRange); lXX <= lX + (iRange); lXX++)
					{
						lIndexRange = ((lYY * lInReduceWidth * lInBitDepth) + (lXX * lInBitDepth));
						lRGB1_R = pucInImage1[lIndexRange + 2];
						if (lRGB1_R == 255)
						{
							iCount++;
						}
					}
				}
				if (iCount <= ((iRange * iRange) / 2))
				{
					for (lYY = lY - (iRange); lYY <= lY + (iRange); lYY++)
					{
						for (lXX = lX - (iRange); lXX <= lX + (iRange); lXX++)
						{
							lIndexRange = ((lYY * lInReduceWidth * lInBitDepth) + (lXX * lInBitDepth));
							lRGB1_R = pucInImage1[lIndexRange + 2];
							if (lRGB1_R == 255)
							{
								pucInImage1[lIndexRange + 2] = 0;
								pucInImage1[lIndexRange + 1] = 0;
								pucInImage1[lIndexRange + 0] = 0;
							}
						}
					}
					continue;
				}
			}
		}
	}
	memcpy(pucOutImage1, pucInImage1, lInReduceWidth * lInReduceHeight * lInBitDepth * sizeof(unsigned char));
	//for ( lY = 0; lY < lInReduceHeight; lY++ )
    //{
    //    for ( lX = 0; lX < lInReduceWidth; lX++ )
    //    {
    //        lIndex = ( lY * lInReduceWidth * lInBitDepth ) + ( lX * lInBitDepth );
    //        if ( 
    //            pucInImage1 [ lIndex + 2 ] == 255 &&
    //            pucInImage1 [ lIndex + 1 ] == 255 &&
    //            pucInImage1 [ lIndex + 0 ] == 255
    //            ) 
    //        {
    //            pdbInImage2 [ lIndex + 2 ] += 0.25f;
    //        }
    //        else
    //        {
    //            pdbInImage2 [ lIndex + 2 ] -= 0.5f;
    //        }
    //    }
    //}
    //for ( lY = 0; lY < lInReduceHeight; lY++ )
    //{
    //    for ( lX = 0; lX < lInReduceWidth; lX++ )
    //    {
    //        lIndex = ( lY * lInReduceWidth * lInBitDepth ) + ( lX * lInBitDepth );
    //        if ( pdbInImage2 [ lIndex + 2 ] >= 1.5f )
    //        {
    //            pucOutImage1 [ lIndex + 2 ] = 255;
    //            pucOutImage1 [ lIndex + 1 ] = 255;
    //            pucOutImage1 [ lIndex + 0 ] = 255;
    //        }
    //        else
    //        {
    //            pucOutImage1 [ lIndex + 2 ] = 0;
    //            pucOutImage1 [ lIndex + 1 ] = 0;
    //            pucOutImage1 [ lIndex + 0 ] = 0;
    //        }
    //    }
    //}
    return true;
}


bool CAlgorithm::
    ConnectLabel(
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
)
{
    if (
        (pucInImage1 == NULL) ||
        (piInOutLabelData1 == NULL) ||
        (piInOutLabelRecord1 == NULL) ||
        (pucOutImage1 == NULL)
        )
    {
        return false;
    }
    if (iInLabelOld == iInLabelNew)
    {
        return true;
    }
    iReLoadCount++;
    if (iReLoadCount > 1000)
    {
        return true;
    }
    int iRangeSX = 0;
    int iRangeSY = 0;
    int iRangeEX = 0;
    int iRangeEY = 0;
    int iY = 0;
    int iX = 0;
    int iIndex = 0;
    iIndex = (iInSY * lInReduceWidth) + (iInSX);
    piInOutLabelData1[iIndex] = iInLabelNew;
    piInOutLabelRecord1[iIndex] = 1;
    iRangeSX = iInSX - 1 < 0 ? 0 : iInSX - 1;
    iRangeSY = iInSY - 1 < 0 ? 0 : iInSY - 1;
    iRangeEX = iInSX + 1 > lInReduceWidth - 1 ? 0 : iInSX + 1;
    iRangeEY = iInSY + 1 > lInReduceHeight - 1 ? 0 : iInSY + 1;
    for (iY = iRangeSY; iY <= iRangeEY; iY++)
    {
        for (iX = iRangeSX; iX <= iRangeEX; iX++)
        {
            if (iY == iInSY && iX == iInSX)
            {
                continue;
            }
            iIndex = (iY * lInReduceWidth) + (iX);
            if (
                (piInOutLabelData1[iIndex] == iInLabelOld) &&
                piInOutLabelRecord1[iIndex] == 0
                )
            {
                ConnectLabel(
                    pucInImage1,
                    piInOutLabelData1,
                    piInOutLabelRecord1,
                    lInReduceWidth,
                    lInReduceHeight,
                    lInBitDepth,
                    iInLabelOld,
                    iInLabelNew,
                    iX,
                    iY,
                    pucOutImage1
                );
            }
        }
    }
    return true;
}


bool CAlgorithm::
    CandidateFlameRegions (
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
    )
{
    if ( 
        (pucInImage1 == NULL) || 
        (piInOutLabelData1 == NULL) ||
        (piInLabelRecord1 == NULL) ||
        (pucOutImage1 == NULL)
        ) 
    { 
        return false; 
    }
    long lY = 0;
    long lX = 0;
    long lIndexLabelSource = 0;
    int iRange = iInRange;
    int iFrameIndex = 0;
    int iLabelMin = 0;
    struct stSEARCHED {
        int iSearchedX;
        int iSearchedY;
        int iSearchedLabel;
        stSEARCHED()
        {
            iSearchedX = 0;
            iSearchedY = 0;
            iSearchedLabel = 0;
        }
    } stSearched;
    deque<stSEARCHED> dequeLabelSearched;
    deque<stSEARCHED>::iterator iteratorLabelSearched;
    int iSearchedX = 0;
    int iSearchedY = 0;
    bool bSearched = false;
    int iSearchedSX = 0;
    int iSearchedSY = 0;
    int iSearchedEX = 0;
    int iSearchedEY = 0;
    int iLabelCurrent = 0;
    int iYY = 0;
    int iXX = 0;
    long lIndexSearched = 0;
    long lIndexImageSource = 0;
    double dbRGB_R = 0;
    double dbRGB_G = 0;
    double dbRGB_B = 0;
    int iHistogram[100];
    memset(&iHistogram, 0x00, sizeof(iHistogram));
    memset(piInLabelRecord1, 0x00, lInReduceWidth * lInReduceHeight * sizeof(int));
    memset(pucOutImage1, 0x00, lInReduceWidth * lInReduceHeight * lInBitDepth * sizeof(unsigned char));
    for (lY = 1; lY < lInReduceHeight - 1; lY += iRange / 2)
    {
        for (lX = 1; lX < lInReduceWidth - 1; lX += iRange / 2)
        {
            lIndexLabelSource = (lY * lInReduceWidth) + (lX);
            if (piInLabelRecord1[lIndexLabelSource] == 1)
            {
                continue;
            }
            iLabelMin = INT_MAX;
            dequeLabelSearched.clear();
            iSearchedX = lX;
            iSearchedY = lY;
            iSearchedSX = iSearchedX - iRange < 0 ? 0 : iSearchedX - iRange;
            iSearchedSY = iSearchedY - iRange < 0 ? 0 : iSearchedY - iRange;
            iSearchedEX = iSearchedX + iRange > lInReduceWidth - 1 ? lInReduceWidth - 1 : iSearchedX + iRange;
            iSearchedEY = iSearchedY + iRange > lInReduceHeight - 1 ? lInReduceHeight - 1 : iSearchedY + iRange;
            for (iYY = iSearchedSY; iYY <= iSearchedEY; iYY++)
            {
                for (iXX = iSearchedSX; iXX <= iSearchedEX; iXX++)
                {
                    lIndexSearched = (iYY * lInReduceWidth) + (iXX);
                    if (
                        (piInOutLabelData1[lIndexSearched] > 0)
                        )
                    {
                        if (iLabelMin > piInOutLabelData1[lIndexSearched])
                        {
                            iLabelMin = piInOutLabelData1[lIndexSearched];
                        }
                        bSearched = false;
                        for (
                            iteratorLabelSearched = dequeLabelSearched.begin();
                            iteratorLabelSearched != dequeLabelSearched.end();
                            iteratorLabelSearched++
                            )
                        {
                            if (
                                ((*iteratorLabelSearched).iSearchedLabel == piInOutLabelData1[lIndexSearched])
                                )
                            {
                                bSearched = true;
                                break;
                            }
                        }
                        if (
                            (bSearched == false)
                            )
                        {
                            stSearched.iSearchedLabel = piInOutLabelData1[lIndexSearched];
                            stSearched.iSearchedX = iXX;
                            stSearched.iSearchedY = iYY;
                            dequeLabelSearched.push_front(stSearched);
                        }
                    }
                }
            }
            lIndexLabelSource = (lY * lInReduceWidth) + (lX);
            iLabelCurrent = piInOutLabelData1[lIndexLabelSource];
            if (
                (iLabelMin != INT_MAX) &&
                (iLabelCurrent > iLabelMin)
                )
            {
                iReLoadCount = 0;
                if (ConnectLabel(
                    pucInImage1,
                    piInOutLabelData1,
                    piInLabelRecord1,
                    lInReduceWidth,
                    lInReduceHeight,
                    lInBitDepth,
                    iLabelCurrent,
                    iLabelMin,
                    iSearchedX,
                    iSearchedY,
                    pucOutImage1
                ) == false)
                {
                    return false;
                }
            }
            if (
                (iLabelMin != INT_MAX) &&
                (dequeLabelSearched.size() > 0)
                )
            {
                for (
                    iteratorLabelSearched = dequeLabelSearched.begin();
                    iteratorLabelSearched != dequeLabelSearched.end();
                    iteratorLabelSearched++
                    )
                {
                    if (ConnectLabel(
                        pucInImage1,
                        piInOutLabelData1,
                        piInLabelRecord1,
                        lInReduceWidth,
                        lInReduceHeight,
                        lInBitDepth,
                        (*iteratorLabelSearched).iSearchedLabel,
                        iLabelMin,
                        (*iteratorLabelSearched).iSearchedX,
                        (*iteratorLabelSearched).iSearchedY,
                        pucOutImage1
                    ) == false)
                    {
                        return false;
                    }
                }
            }
        }
    }
    double dbDifference = 0.0f;
    int iDifference = 0;
    int iIndexHistogram = 0;
    int iClusters = 0;
    int iPixelCount = 0;
    int iHistogramCount = 0;
    double dbSplitDegree = 0.0f;
    deque<int> dequeLabels;
    deque<int>::iterator iteratorLabels;
    dequeLabels.clear();
    memset(&iHistogram, 0x00, sizeof(iHistogram));
    for (lY = 1; lY < lInReduceHeight - 1; lY++)
    {
        for (lX = 1; lX < lInReduceWidth - 1; lX++)
        {
            lIndexLabelSource = (lY * lInReduceWidth) + (lX);
            if (piInOutLabelData1[lIndexLabelSource] > 0)
            {
                bSearched = false;
                for (
                    iteratorLabels = dequeLabels.begin();
                    iteratorLabels != dequeLabels.end();
                    iteratorLabels++
                    )
                {
                    if ((*iteratorLabels) == piInOutLabelData1[lIndexLabelSource])
                    {
                        bSearched = true;
                        break;
                    }
                }
                if (bSearched == false)
                {
                    dequeLabels.push_front(piInOutLabelData1[lIndexLabelSource]);
                }
            }
        }
    }
    if (dequeLabels.size() > 0)
    {
        double dbHistogramDifferent1 = 0.0f;
        double dbHistogramDifferent2 = 0.0f;
        double dbHistogramDifferent = 0.0f;
        double dbHistogramMax = 0.0f;
        double dbHistogramMin = INT_MAX;
        double dbHistogramCount = 0.0f;
        double dbHistogramSum = 0.0f;
        double dbHistogramAverage = 0.0f;
        int iLabelPixelCount = 0;
        double dbResolution = 0.0f;
        double dbWeight = 0.0f;
        double dbThreshold = 0.0f;
        int iLowerThanFive = 0;
        memset(&iHistogram, 0x00, sizeof(iHistogram));
        if (m_dbSplitDegree == 0.0f)
        {
            for (
                iteratorLabels = dequeLabels.begin();
                iteratorLabels != dequeLabels.end();
                iteratorLabels++
                )
            {
                for (lY = 1; lY < lInReduceHeight - 1; lY++)
                {
                    for (lX = 1; lX < lInReduceWidth - 1; lX++)
                    {
                        lIndexLabelSource = (lY * lInReduceWidth) + (lX);
                        if (piInOutLabelData1[lIndexLabelSource] == (*iteratorLabels))
                        {
                            lIndexImageSource = (lY * lInReduceWidth * lInBitDepth) + (lX * lInBitDepth);
                            dbRGB_R = pucInImage1[lIndexImageSource + 2];
                            dbRGB_G = pucInImage1[lIndexImageSource + 1];
                            dbRGB_B = pucInImage1[lIndexImageSource + 0];
                            dbDifference = sqrtf(pow(dbRGB_R, 2) + pow(dbRGB_G, 2) + pow(dbRGB_B, 2));
                            dbDifference = (dbDifference / 500.0f) * 100.0f;
                            iDifference = (int)round(dbDifference);
                            iHistogram[iDifference]++;
                            iLabelPixelCount++;
                        }
                    }
                }
            }
            iHistogramCount = 0;
            dbHistogramSum = 0.0f;
            dbHistogramAverage = 0.0f;
            dbHistogramCount = 0.0f;
            dbHistogramMin = INT_MAX;
            for (iIndexHistogram = 0; iIndexHistogram < 100; iIndexHistogram++)
            {
                if (iHistogram[iIndexHistogram] > 0)
                {
                    dbHistogramSum += iHistogram[iIndexHistogram];
                    dbHistogramCount++;
                    iHistogramCount++;
                    if (dbHistogramMin > iHistogram[iIndexHistogram])
                    {
                        dbHistogramMin = iHistogram[iIndexHistogram];
                    }
                    if (dbHistogramMax < iHistogram[iIndexHistogram])
                    {
                        dbHistogramMax = iHistogram[iIndexHistogram];
                    }
                }
            }
            if (dbHistogramSum <= 0.0f || dbHistogramCount <= 0.0f || dbHistogramMin <= 1.0f)
            {
                m_dbSplitDegree = 0.0f;
                return true;
            }
            dbHistogramAverage = dbHistogramSum / dbHistogramCount;
            dbHistogramDifferent1 = abs(dbHistogramAverage - dbHistogramMin);
            dbHistogramDifferent2 = abs(dbHistogramMax - dbHistogramAverage);
            dbHistogramDifferent = abs(dbHistogramDifferent2 - dbHistogramDifferent1);
            if (dbHistogramDifferent < 5.0f)
            {
                memset(piInOutLabelData1, 0x00, lInReduceWidth * lInReduceHeight * sizeof(int));
                m_dbSplitDegree = 0.0f;
                return true;
            }
            if (dbHistogramDifferent > dbHistogramAverage)
            {
                dbHistogramDifferent = floor(floor(dbHistogramDifferent + dbHistogramAverage + dbHistogramDifferent1) / 3.0f);
            }
            dbResolution = (double)(lInReduceWidth * lInReduceHeight);
            dbWeight = ((double)iLabelPixelCount / dbResolution);
            if (dbWeight < 0.005f)
            {
                dbThreshold = ceil(dbHistogramDifferent);
            }
            else
            {
                dbThreshold = floor(dbHistogramDifferent);
            }
            if (dbThreshold < iHistogramCount)
            {
                iHistogramCount = 0;
                dbHistogramSum = 0.0f;
                dbHistogramCount = 0.0f;
                for (iIndexHistogram = 0; iIndexHistogram < 100; iIndexHistogram++)
                {
                    if (iHistogram[iIndexHistogram] >= dbHistogramAverage)
                    {
                        dbHistogramSum += iHistogram[iIndexHistogram];
                        dbHistogramCount++;
                        iHistogramCount++;
                    }
                }
            }
            if (iLabelPixelCount > 0)
            {
                m_dbSplitDegree = iHistogramCount;
            }
        }
        for (
            iteratorLabels = dequeLabels.begin();
            iteratorLabels != dequeLabels.end();
            iteratorLabels++
            )
        {
            iPixelCount = 0;
            memset(&iHistogram, 0x00, sizeof(iHistogram));
            for (lY = 1; lY < lInReduceHeight - 1; lY++)
            {
                for (lX = 1; lX < lInReduceWidth - 1; lX++)
                {
                    lIndexLabelSource = (lY * lInReduceWidth) + (lX);
                    if ((*iteratorLabels) == piInOutLabelData1[lIndexLabelSource])
                    {
                        lIndexImageSource = (lY * lInReduceWidth * lInBitDepth) + (lX * lInBitDepth);
                        dbRGB_R = pucInImage1[lIndexImageSource + 2];
                        dbRGB_G = pucInImage1[lIndexImageSource + 1];
                        dbRGB_B = pucInImage1[lIndexImageSource + 0];
                        dbDifference = sqrtf(pow(dbRGB_R, 2) + pow(dbRGB_G, 2) + pow(dbRGB_B, 2));
                        dbDifference = (dbDifference / 500.0f) * 100.0f;
                        iDifference = (int)round(dbDifference);
                        iHistogram[iDifference]++;
                        iPixelCount++;
                    }
                }
            }
            if (iPixelCount > 0)
            {
                iHistogramCount = 0;
                for (iIndexHistogram = 0; iIndexHistogram < 100; iIndexHistogram++)
                {
                    if (iHistogram[iIndexHistogram] > 0)
                    {
                        iHistogramCount++;
                    }
                }
                if (iHistogramCount <= m_dbSplitDegree)
                {
                    for (lY = 1; lY < lInReduceHeight - 1; lY++)
                    {
                        for (lX = 1; lX < lInReduceWidth - 1; lX++)
                        {
                            lIndexLabelSource = (lY * lInReduceWidth) + (lX);
                            if ((*iteratorLabels) == piInOutLabelData1[lIndexLabelSource])
                            {
                                piInOutLabelData1[lIndexLabelSource] = -1;
                            }
                        }
                    }
                }
            }
        }
    }
    for (lY = 0; lY < lInReduceHeight; lY++)
    {
        for (lX = 0; lX < lInReduceWidth; lX++)
        {
            lIndexLabelSource = (lY * lInReduceWidth) + (lX);
            lIndexImageSource = (lY * lInReduceWidth * lInBitDepth) + (lX * lInBitDepth);
            if (piInOutLabelData1[lIndexLabelSource] > 0)
            {
                pucOutImage1[lIndexImageSource + 3] = 0;
                pucOutImage1[lIndexImageSource + 2] = pucInImage1[lIndexImageSource + 2];
                pucOutImage1[lIndexImageSource + 1] = pucInImage1[lIndexImageSource + 1];
                pucOutImage1[lIndexImageSource + 0] = pucInImage1[lIndexImageSource + 0];
            }
        }
    }
	return true;
}


bool CAlgorithm::
    MotionVectorFlameBlockImage(
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
    )
{
    if ((!pucOutImage) || (pucOutImage == NULL)) { return false; }
    long lFrameIndex = 0;
    long lY = 0;
    long lX = 0;
    long lY1 = 0;
    long lX1 = 0;
    long lIndexBlock = 0;
    double dbDistance = 0;
    double dbMinimumDistance = INT_MAX;
    long lMaximumDistance = INT_MAX;
    long lFoundX = 0;
    long lFoundY = 0;
    double dbOriginR = 0.0f;
    double dbOriginG = 0.0f;
    double dbOriginB = 0.0f;
    double dbSearchR = 0.0f;
    double dbSearchG = 0.0f;
    double dbSearchB = 0.0f;
    double dbSumH = 0.0f;
    double dbSumS = 0.0f;
    double dbSumV = 0.0f;
    double dbDiffH = 0.0f;
    double dbDiffS = 0.0f;
    double dbDiffV = 0.0f;
    double dbSimilarH = 0.0f;
    double dbSimilarS = 0.0f;
    double dbSimilarV = 0.0f;
    float dbOriginH = 0.0f;
    float dbOriginS = 0.0f;
    float dbOriginV = 0.0f;
    float dbSearchH = 0.0f;
    float dbSearchS = 0.0f;
    float dbSearchV = 0.0f;
    long lBY = 0;
    long lBX = 0;
    bool bFound = false;
    long lPY = 0;
    long lPX = 0;
    long lOriginLabelBlockIndex = 0;
    long lSearchLabelBlockIndex = 0;
    int iOriginLabel = 0;
    int iSearchLabel = 0;
    long lOriginBlockIndex = 0;
    long lSearchBlockIndex = 0;
    bool bFlameBlock = false;

    lFrameIndex = ((llInFrameCount - 1) % 2) + 1;
    if (lFrameIndex == 1)
    {
        memcpy(pucInFrame1, pucInImage, lInWidth * lInHeight * lInBitDepth * sizeof(unsigned char));
        memcpy(piInDataLabel1, piInOutLabelData1, lInWidth * lInHeight * sizeof(int));
    }
    else if (lFrameIndex == 2)
    {
        memcpy(pucInFrame2, pucInImage, lInWidth * lInHeight * lInBitDepth * sizeof(unsigned char));
        memcpy(piInDataLabel2, piInOutLabelData1, lInWidth * lInHeight * sizeof(int));
    }
    if (llInFrameCount <= 2)
    {
        return false;
    }
    memset(pucOutImage, 0x00, lInWidth * lInHeight * lInBitDepth * sizeof(unsigned char));
    for (lY = 0; lY < lInHeight; lY += lInBlockHeight)
    {
        for (lX = 0; lX < lInWidth; lX += lInBlockWidth)
        {
            dbMinimumDistance = lMaximumDistance;
            lFoundX = 0;
            lFoundY = 0;
            for (lBY = lY - (lInSearchYRange * lInBlockHeight);
                (lBY < lY + (lInSearchYRange * lInBlockHeight));
                lBY += lInBlockHeight)
            {
                if (lBY < 0 || lBY >= lInHeight)
                {
                    continue;
                }
                for (lBX = lX - (lInSearchXRange * lInBlockWidth);
                    (lBX < lX + (lInSearchXRange * lInBlockWidth));
                    lBX += lInBlockWidth)
                {
                    if (
                        lBY < 0 ||
                        lBX < 0 ||
                        lBY >= lInHeight ||
                        lBX >= lInWidth
                        )
                    {
                        continue;
                    }
                    dbDistance = 0;
                    bFound = false;
                    for (lPY = 0; lPY < lInBlockHeight; lPY++)
                    {
                        for (lPX = 0; lPX < lInBlockWidth; lPX++)
                        {
                            if (
                                ((lY + lPY) < 0) ||
                                ((lY + lPY) >= lInHeight) ||
                                ((lX + lPX) < 0) ||
                                ((lX + lPX) >= lInWidth) ||
                                ((lBY + lPY) < 0) ||
                                ((lBY + lPY) >= lInHeight) ||
                                ((lBX + lPX) < 0) ||
                                ((lBX + lPX) >= lInWidth)
                                )
                            {
                                break;
                            }
                            lOriginLabelBlockIndex = ((lY + lPY) * lInWidth) + (lX + lPX);
                            lSearchLabelBlockIndex = ((lBY + lPY) * lInWidth) + (lBX + lPX);
                            iOriginLabel = 0;
                            iSearchLabel = 0;
                            if (lFrameIndex == 1)
                            {
                                iOriginLabel = piInDataLabel1[lOriginLabelBlockIndex];
                                iSearchLabel = piInDataLabel2[lSearchLabelBlockIndex];
                            }
                            else if (lFrameIndex == 2)
                            {
                                iSearchLabel = piInDataLabel1[lSearchLabelBlockIndex];
                                iOriginLabel = piInDataLabel2[lOriginLabelBlockIndex];
                            }
                            if (iOriginLabel > 0)
                            {
                                Sleep(0);
                            }
                            if (iSearchLabel > 0)
                            {
                                Sleep(0);
                            }
                            if (iOriginLabel > 0 && iSearchLabel > 0 )
                            {
                                bFound = true;
                                break;
                            }
                        }
                        if (bFound == true)
                        {
                            break;
                        }
                    }
                    if (bFound == false)
                    {
                        continue;
                    }
                    for (lPY = 0; lPY < lInBlockHeight; lPY++)
                    {
                        for (lPX = 0; lPX < lInBlockWidth; lPX++)
                        {
                            lOriginBlockIndex = ((lY + lPY) * lInWidth * lInBitDepth) + ((lX + lPX) * lInBitDepth);
                            lSearchBlockIndex = ((lBY + lPY) * lInWidth * lInBitDepth) + ((lBX + lPX) * lInBitDepth);

                            dbDistance += (
                                abs(pucInFrame1[lOriginBlockIndex + 2] - pucInFrame2[lSearchBlockIndex + 2]) +
                                abs(pucInFrame1[lOriginBlockIndex + 1] - pucInFrame2[lSearchBlockIndex + 1]) +
                                abs(pucInFrame1[lOriginBlockIndex + 0] - pucInFrame2[lSearchBlockIndex + 0])
                                );
                        }
                        if (
                            ((lY + lPY) < 0) ||
                            ((lY + lPY) >= lInHeight) ||
                            ((lBY + lPY) < 0) ||
                            ((lBY + lPY) >= lInHeight)
                            )
                        {
                            break;
                        }
                    }
                    if (
                        dbDistance < dbMinimumDistance &&
                        (lBX != 0 && lBY != 0)
                        )
                    {
                        dbMinimumDistance = dbDistance;
                        lFoundX = lBX;
                        lFoundY = lBY;
                    }
                }
            }
            if (
                true
                )
            {
                if (
                    (dbMinimumDistance <= ((lInBlockHeight * lInBlockWidth * 3 * 255) * 0.001))
                    )
                {
                    continue;
                }
                if (
                    ((abs(lFoundX - lX) >= 0) || (abs(lFoundY - lY) >= 0)) &&
                    (dbMinimumDistance <= ((lInBlockHeight * lInBlockWidth * 3 * 255) * 1))
                    )
                {
                    for (lY1 = 0; lY1 < lInBlockHeight; lY1++)
                    {
                        for (lX1 = 0; lX1 < lInBlockWidth; lX1++)
                        {
                            if (
                                ((lY + lY1) < 0) ||
                                ((lY + lY1) >= lInHeight) ||
                                ((lX + lX1) < 0) ||
                                ((lX + lX1) >= lInWidth)
                                )
                            {
                                break;
                            }
                            lIndexBlock = ((lY + lY1) * lInWidth * lInBitDepthOutImage) + ((lX + lX1) * lInBitDepthOutImage);
                            pucOutImage[lIndexBlock + 2] = 255;
                            pucOutImage[lIndexBlock + 1] = 255;
                            pucOutImage[lIndexBlock + 0] = 255;
                        }
                    }
                }
            }
        }
    }
    for (lY = 0; lY < lInHeight; lY += lInBlockHeight)
    {
        for (lX = 0; lX < lInWidth; lX += lInBlockWidth)
        {
            lIndexBlock = (lY * lInWidth * lInBitDepthOutImage) + (lX * lInBitDepthOutImage);
            if (
                pucOutImage[lIndexBlock + 2] == 255 &&
                pucOutImage[lIndexBlock + 1] == 255 &&
                pucOutImage[lIndexBlock + 0] == 255
                )
            {
                bFlameBlock = false;
                for (lBY = lY - (lInBlockHeight);
                    (lBY < lY + (lInBlockHeight));
                    lBY++)
                {
                    if (lBY < 0 || lBY >= lInHeight)
                    {
                        continue;
                    }
                    for (lBX = lX - (lInBlockWidth);
                        (lBX < lX + (lInBlockWidth));
                        lBX++)
                    {
                        if (
                            lBY < 0 ||
                            lBX < 0 ||
                            lBY >= lInHeight ||
                            lBX >= lInWidth
                            )
                        {
                            continue;
                        }
                        lSearchBlockIndex = (lBY * lInWidth * lInBitDepth) + (lBX * lInBitDepth);
                        if (
                            pucInFlameImage[lSearchBlockIndex + 2] > 0 ||
                            pucInFlameImage[lSearchBlockIndex + 1] > 0 ||
                            pucInFlameImage[lSearchBlockIndex + 0] > 0
                            )
                        {
                            bFlameBlock = true;
                            break;
                        }
                    }
                    if (bFlameBlock == true)
                    {
                        break;
                    }
                }
                if (bFlameBlock == true)
                {
                    for (lBY = lY - ((lInSearchYRange * lInBlockHeight)/2);
                        (lBY < lY + ((lInSearchYRange * lInBlockHeight))/2);
                        lBY++)
                    {
                        if (lBY < 0 || lBY >= lInHeight)
                        {
                            continue;
                        }
                        for (lBX = lX - ((lInSearchXRange * lInBlockWidth)/2);
                            (lBX < lX + ((lInSearchXRange * lInBlockWidth))/2);
                            lBX++)
                        {
                            if (
                                lBY < 0 ||
                                lBX < 0 ||
                                lBY >= lInHeight ||
                                lBX >= lInWidth
                                )
                            {
                                continue;
                            }
                            lSearchBlockIndex = (lBY * lInWidth * lInBitDepth) + (lBX * lInBitDepth);
                            pucOutImage[lSearchBlockIndex + 2] = 255;
                            pucOutImage[lSearchBlockIndex + 1] = 255;
                            pucOutImage[lSearchBlockIndex + 0] = 255;
                        }
                    }
                }
            }
        }
    }
    for (lY = 0; lY < lInHeight; lY++)
    {
        for (lX = 0; lX < lInWidth; lX++)
        {
            lIndexBlock = (lY * lInWidth * lInBitDepthOutImage) + (lX * lInBitDepthOutImage);
            if (
                pucOutImage[lIndexBlock + 2] == 255 &&
                pucOutImage[lIndexBlock + 1] == 255 &&
                pucOutImage[lIndexBlock + 0] == 255
                )
            {
                pucOutImage[lIndexBlock + 2] = pucInImage[lIndexBlock + 2];
                pucOutImage[lIndexBlock + 1] = pucInImage[lIndexBlock + 1];
                pucOutImage[lIndexBlock + 0] = pucInImage[lIndexBlock + 0];
            }
        }
    }
    return true;
}




bool CAlgorithm::
    OTSUThreshold ( 
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

    for ( i = 0; i < 256; i++ )
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }
    
    for ( i = 0; i < height; i++ )
    {
        for ( j = 0; j < width; j++ )
        {
            long lIndex = ( i * width * lInBitDepth ) + ( j * lInBitDepth );
            pixelCount [ (int) data [ lIndex + 2 ] ]++;
        }
    }
    
    for(i = 0; i < 256; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
    }
    
    float w0, w1, u0tmp, u1tmp, u0, u1, u, 
        deltaTmp, deltaMax = 0;
    for(i = 0; i < 256; i++)
    {
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for(j = 0; j < 256; j++)
        {
            if(j <= i)   
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
        if(deltaTmp > deltaMax)
        {
            deltaMax = deltaTmp;
            threshold = i;
        }
    }
    lOutThreshold = threshold;
    for ( int iY = 0; iY < height; iY++ )
    {
        for ( int iX = 0; iX < width; iX++ )
        {
            long lIndex = ( iY * width * lInBitDepth ) + ( iX * lInBitDepth );
            int iPixel = pucInImage1 [ lIndex + 0 ];
            if ( iPixel >= threshold )
            {
                pucOutImage1 [ lIndex + 2 ] = 255;
                pucOutImage1 [ lIndex + 1 ] = 255;
                pucOutImage1 [ lIndex + 0 ] = 255;
            }
            else
            {
                pucOutImage1 [ lIndex + 2 ] = 0;
                pucOutImage1 [ lIndex + 1 ] = 0;
                pucOutImage1 [ lIndex + 0 ] = 0;
            }
        }
    }
    return true;
}



bool CAlgorithm::
    ROItoReduceImage (
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
    memset ( pucInOutImage1, 0x00, lInReduceWidth * lInReduceHeight * lInBitDepth );
    long lY = 0;
    long lX = 0;
    long lIndex = 0;
    long lYY = 0;
    long lXX = 0;
    long lIndexROI = 0;
    for ( lY = lInReduceROISY; lY <= lInReduceROIEY; lY++ )
    {
        for ( lX = lInReduceROISX; lX <= lInReduceROIEX; lX++ )
        {
            lIndex = ( lY * lInReduceWidth * lInBitDepth ) + ( lX * lInBitDepth );
            lIndexROI = ( lYY * lInReduceROIWidth * lInBitDepth ) + ( lXX * lInBitDepth );
            pucInOutImage1 [ lIndex + 2 ] = pucInImage2 [ lIndexROI + 2 ];
            pucInOutImage1 [ lIndex + 1 ] = pucInImage2 [ lIndexROI + 1 ];
            pucInOutImage1 [ lIndex + 0 ] = pucInImage2 [ lIndexROI + 0 ];
            lXX++;
        }
        lXX = 0;
        lYY++;
    }
    return true;
}







bool CAlgorithm::
    BoxMaker (
    unsigned char* pInImg1Bin,
    unsigned char* pInImg2,
    long lInWidth,
    long lInHeight,
    long lInBitDepth,
    vector<stRectangleData>& vectorBox,
    long lInMode,
    unsigned char* pOutImage
    )
{
    long lWidth = lInWidth;
    long lHeight = lInHeight;
    unsigned char* pBinGray8 = new unsigned char [ lWidth * lHeight ];
    memset ( pBinGray8, 0x00, lWidth * lHeight * sizeof(unsigned char) );
    long lBitDepth = lInBitDepth;
    long lY = 0, lX = 0;
    long lSrcImgIndex = 0, lDstImgIndex = 0;
    long slSourceSX = 0, slSourceSY = 0;
    long slCurrentSX = 0, slCurrentSY = 0;
    long ObjectSX = 0, ObjectSY = 0, ObjectEX = 0, ObjectEY = 0;
    long slCount = 0;
    long slDirect = 0;
    unsigned char byPixel = 0;
    bool bFindPoint = false;
    bool bFindStartPoint = false;
    long slSearchZone [8][2] = { {-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0} };
    unsigned char* pTmpGray8 = new unsigned char [ lWidth * lHeight ];
    memset ( pTmpGray8, 0x00, lWidth * lHeight * sizeof(unsigned char) );
    long nImgYJump1 = lWidth;
    long nImgXJump1 = 1;
    long nImgYIndexS1 = lHeight * lWidth - 1;
    long nImgIndex1 = 0;
    long nImgIndex2 = 0;
    long nImgIndex3 = 0;
    long slMarkY = 0, slMarkX = 0;
    long nObjIndexS = 0, nObjIndex = 0;
    long nRotationCount = 0;
    bool bIsolatedPoint = false;
    long lLimit = ( lWidth * lHeight ) / 4;
    long lColor = 0;
    long lRGB_B = 0;
    long lRGB_G = 0;
    long lRGB_R = 0;
    long lI = 0;
    long lIndex = 0;
    long lPixelsCount = 0;
    memset ( pOutImage, 0x00, lWidth * lHeight * lInBitDepth );
    for ( lY = 0; lY < lHeight; ++lY )
    {
        for ( lX = 0; lX < lWidth; ++lX )
        {
            long lSrcIdx = ( lY * lWidth * lBitDepth ) + ( lX * lBitDepth );
            long lDstIdx = ( lY * lWidth ) + ( lX );
            if ( 
                pInImg1Bin [ lSrcIdx + 2 ] > 0
                )
            {
                pBinGray8 [ lDstIdx ] = 255;
            }
        }
    }
    for ( lY = lHeight - 1; lY >= 0; --lY )
    {
        nImgIndex1 = nImgYIndexS1;
        for ( lX = lWidth - 1; lX >= 0; --lX )
        {
            if ( pBinGray8 [ nImgIndex1 ] == 255 &&
                pTmpGray8 [ nImgIndex1 ] == 0 )
            {
                stRectangleData stBox;
                stBox.lPixels = 1;
                slSourceSX = lX;
                slSourceSY = lY;
                slCurrentSX = lX;
                slCurrentSY = lY;
                ObjectSX = lX;
                ObjectSY = lY;
                ObjectEX = lX;
                ObjectEY = lY;
                slCount = 0;
                slDirect = 0;
                bFindStartPoint = false;
                pTmpGray8 [ nImgIndex1 ] = 255;
                nImgIndex2 = nImgIndex1;
                while ( bFindStartPoint == false )
                {
                    if ( ObjectSX > slCurrentSX ) { ObjectSX = slCurrentSX; }
                    if ( ObjectSY > slCurrentSY ) { ObjectSY = slCurrentSY; }
                    if ( ObjectEX < slCurrentSX ) { ObjectEX = slCurrentSX; }
                    if ( ObjectEY < slCurrentSY ) { ObjectEY = slCurrentSY; }
                    bFindPoint = false;
                    nRotationCount = 0;
                    bIsolatedPoint = false;
                    while ( bFindPoint == false )
                    {
                        if (
                            ( slCurrentSY + slSearchZone[slDirect][1] < 0 ) ||
                            ( slCurrentSX + slSearchZone[slDirect][0] < 0 ) ||
                            ( slCurrentSY + slSearchZone[slDirect][1] >= lHeight ) ||
                            ( slCurrentSX + slSearchZone[slDirect][0] >= lWidth )
                            ) 
                        { 
                            ++slDirect; ++nRotationCount;
                            if ( slDirect == 8 ) { slDirect = 0; }
                            ++slCount;
                            if ( ++slCount > lLimit ) { break; }
                            continue;
                        }
                        nImgIndex3 = nImgIndex2 + slSearchZone[slDirect][1] * nImgYJump1 + slSearchZone[slDirect][0] * nImgXJump1;
                        byPixel = pBinGray8 [ nImgIndex3 ];
                        if ( byPixel == 255 )
                        {
                            stBox.lPixels++;
                            bFindPoint = true;
                            slCurrentSX = ( slCurrentSX + slSearchZone[slDirect][0] ); 
                            nImgIndex2 += slSearchZone[slDirect][0] * nImgXJump1;
                            slCurrentSY = ( slCurrentSY + slSearchZone[slDirect][1] ); 
                            nImgIndex2 += slSearchZone[slDirect][1] * nImgYJump1;
                            pTmpGray8 [ slCurrentSY * lWidth + slCurrentSX ] = 255;
                            if ( slSourceSX == slCurrentSX && 
                                slSourceSY == slCurrentSY )
                            {
                                bFindStartPoint = true;
                            }
                            slDirect--;
                            if ( slDirect == -1 ) { slDirect = 7; }
                            slDirect--;
                            if ( slDirect == -1 ) { slDirect = 7; }
                        }
                        else
                        {
                            ++slDirect; ++nRotationCount;
                            if ( slDirect == 8 ) { slDirect = 0; }
                        }
                        slCount++;
                        if ( slCount > lLimit ) { break; }
                        if ( nRotationCount >= 8 )
                        { 
                            bIsolatedPoint = true;
                            bFindStartPoint = true;
                            break;
                        }
                    } 
                    if ( slCount > lLimit ) { break; }
                } 
                if ( 
                    ( ObjectSY >= 0 && ObjectEY < lHeight ) &&
                    ( ObjectSX >= 0 && ObjectEX < lWidth ) 
                    )
                {
                    stBox.lSX = ObjectSX;
                    stBox.lEX = ObjectEX;
                    stBox.lSY = ObjectSY;
                    stBox.lEY = ObjectEY;
                    stBox.lWidth = ObjectEX - ObjectSX + 1;
                    stBox.lHeight = ObjectEY - ObjectSY + 1;
                    stBox.lArea = stBox.lWidth * stBox.lHeight;

                    lPixelsCount = 0;
                    nObjIndexS = ( ObjectSY * lWidth ) + ObjectSX;
                    for ( slMarkY = ObjectSY; slMarkY <= ObjectEY; ++slMarkY )
                    {
                        nObjIndex = nObjIndexS;
                        for ( slMarkX = ObjectSX; slMarkX <= ObjectEX; ++slMarkX )
                        {
                            long lIndexImage = ( slMarkY * lWidth * lInBitDepth ) + ( slMarkX * lInBitDepth );
                            if ( lInMode == 1 )
                            {
                                if ( 
                                    pInImg1Bin [ lIndexImage + 2 ] == 255 &&
                                    pInImg1Bin [ lIndexImage + 1 ] == 0 &&
                                    pInImg1Bin [ lIndexImage + 0 ] == 0 
                                    )
                                {
                                    lPixelsCount++;
                                }
                            }
                            else if ( lInMode == 2 )
                            {
                                if ( 
                                    pInImg1Bin [ lIndexImage + 2 ] == 255
                                    )
                                {
                                    pOutImage [ lIndexImage + 2 ] = pInImg2 [ lIndexImage + 2 ];
                                    pOutImage [ lIndexImage + 1 ] = pInImg2 [ lIndexImage + 1 ];
                                    pOutImage [ lIndexImage + 0 ] = pInImg2 [ lIndexImage + 0 ];
                                }
                            }
                            ++nObjIndex;
                        }
                        nObjIndexS += nImgYJump1;
                    }
//                     char clog[255];
//                     sprintf_s( clog, "%f\n", ( stBox.lArea / ( stBox.lPixels + 0.1f ) ) );
//                     OutputDebugString ( clog );

                    if ( lInMode == 1 )
                    {
                        if (
                            ( ( stBox.lArea / ( stBox.lPixels + 0.1f ) ) <= 1.0f )
                            )
                        {
                            nObjIndexS = ( ObjectSY * lWidth ) + ObjectSX;
                            for ( slMarkY = ObjectSY; slMarkY <= ObjectEY; ++slMarkY )
                            {
                                nObjIndex = nObjIndexS;
                                for ( slMarkX = ObjectSX; slMarkX <= ObjectEX; ++slMarkX )
                                {
                                    if ( pBinGray8 [ nObjIndexS ] != 0 )
                                    {
                                        pBinGray8 [ nObjIndexS ] == 0;
                                    }
                                    long lIndexImage = ( slMarkY * lWidth * lInBitDepth ) + ( slMarkX * lInBitDepth );
                                    if ( pInImg2 [ lIndexImage + 2 ] == 255 )
                                    {
                                        pOutImage [ lIndexImage + 2 ] = 0;
                                        pOutImage [ lIndexImage + 1 ] = 0;
                                        pOutImage [ lIndexImage + 0 ] = 0;
                                    }
                                    ++nObjIndex;
                                }
                                nObjIndexS += nImgYJump1;
                            }
                        }
                        else if ( ( stBox.lArea / ( stBox.lPixels + 0.1f ) ) >= 1.0f )
                        {
                            nObjIndexS = ( ObjectSY * lWidth ) + ObjectSX;
                            for ( slMarkY = ObjectSY; slMarkY <= ObjectEY; ++slMarkY )
                            {
                                nObjIndex = nObjIndexS;
                                for ( slMarkX = ObjectSX; slMarkX <= ObjectEX; ++slMarkX )
                                {
                                    long lIndexImage = ( slMarkY * lWidth * lInBitDepth ) + ( slMarkX * lInBitDepth );
                                    if ( pInImg2 [ lIndexImage + 2 ] == 255 )
                                    {
                                        pOutImage [ lIndexImage + 2 ] = pInImg2 [ lIndexImage + 2 ];
                                        pOutImage [ lIndexImage + 1 ] = pInImg2 [ lIndexImage + 1 ];
                                        pOutImage [ lIndexImage + 0 ] = pInImg2 [ lIndexImage + 0 ];
                                    }
                                    ++nObjIndex;
                                }
                                nObjIndexS += nImgYJump1;
                            }
                            vectorBox.push_back(stBox);
                        }
                    }
                    else if ( lInMode == 2 )
                    {
                        vectorBox.push_back(stBox);
                    }

                    lX = ObjectEX - 1;
                    nImgIndex1 = nImgYIndexS1 - ( lWidth - 1 - lX ) * nImgXJump1;
                    ObjectSX = 0;
                    ObjectSY = 0;
                    ObjectEX = 0;
                    ObjectEY = 0;
                } 
                else 
                {
                    break;
                }
            }
            nImgIndex1 -= nImgXJump1;
        }
        nImgYIndexS1 -= nImgYJump1;
    }
    SAFE_DELETE_ARRAY ( pBinGray8 );
    SAFE_DELETE_ARRAY ( pTmpGray8 );
    return true;
}


bool CAlgorithm::
    OpenClose (
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
    )
{
    long lIndex = 0;
    long lIndexCount = 0;
    int iY = 0;
    int iX = 0;
    int iWidth = iInWidth;
    int iHeight = iInHeight;
    int iBitDepth = iInBitDepth;
    int iYY = 0;
    int iXX = 0;
    int iCount = 0;
    int iThreshold = 0;
    int iResult = 0;
    int iCountZero = 0;
    unsigned char* pTemp = new unsigned char [ iWidth * iHeight * iBitDepth ];
    memcpy ( pOutImage, pInImage, iWidth * iHeight * iBitDepth );
    for ( iCount = 0; iCount < iInLoop; iCount++ )
    {
        memset ( pTemp, 0x00, iWidth * iHeight * iBitDepth );
        if ( iCount == 0 ) { iThreshold = iInThreshold1; }
        else if ( iCount == 1 ) { iThreshold = iInThreshold2; }
        else if ( iCount == 2 ) { iThreshold = iInThreshold3; }
        else if ( iCount == 3 ) { iThreshold = iInThreshold4; }
        else if ( iCount == 4 ) { iThreshold = iInThreshold5; }
        else if ( iCount == 5 ) { iThreshold = iInThreshold6; }
        for ( iY = iInRangeY; iY < iHeight - iInRangeY; iY++ )
        {
            for ( iX = iInRangeX; iX < iWidth - iInRangeX; iX++ )
            {
                iResult = 0;
                iCountZero = 0;
                for ( iYY = -(iInRangeY); iYY <= iInRangeY; iYY++ )
                {
                    for ( iXX = -(iInRangeX); iXX <= iInRangeX; iXX++ )
                    {
                        lIndexCount = ( ( ( iY + iYY ) * iBitDepth ) * iWidth ) + 
                            ( ( iX + iXX ) * iBitDepth );
                        if ( pOutImage [ lIndexCount + 2 ] == 255 )
                        {
                            iCountZero++;
                            if ( iCountZero >= iThreshold ) { break; }
                        }
                    }
                    if ( iCountZero >= iThreshold )
                    {
                        iResult = 255;
                        break;
                    }
                }
                lIndex = ( iY * iBitDepth * iWidth ) + ( iX * iBitDepth );
                pTemp [ lIndex + 2 ] = unsigned char(iResult);
                pTemp [ lIndex + 1 ] = unsigned char(iResult);
                pTemp [ lIndex + 0 ] = unsigned char(iResult);
            }
        }
        memcpy ( pOutImage, pTemp, iWidth * iHeight * iBitDepth );
    }
    SAFE_DELETE_ARRAY ( pTemp );
    return true;
}


bool CAlgorithm::
    DoubleFrame (
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
    if ( ( !pucOutImage1 ) || ( pucOutImage1 == NULL ) ) { return false; }
    long lFrameIndex = 0;
    long lY = 0;
    long lX = 0;
    long lIndex = 0;
    lFrameIndex = ( ( llInFrameCount - 1 ) % 2 ) + 1;
    if ( lFrameIndex == 1 )
    {
        memcpy ( pucInImage2, pucInImage1, lInReduceWidth * lInReduceHeight * lInBitDepth * sizeof(BYTE) );
    }
    else if ( lFrameIndex == 2 )
    {
        memcpy ( pucInImage3, pucInImage1, lInReduceWidth * lInReduceHeight * lInBitDepth * sizeof(BYTE) );
    }
    if ( llInFrameCount <= 2 ) 
    { 
        return true; 
    }
    memset ( pucOutImage1, 0x00, lInReduceWidth * lInReduceHeight * lInBitDepth * sizeof(BYTE) );
    for ( lY = 0; lY < lInReduceHeight; lY++ )
    {
        for ( lX = 0; lX < lInReduceWidth; lX++ )
        {
            lIndex = ( lY * lInReduceWidth * lInBitDepth ) + ( lX * lInBitDepth );
            if (
                pucInImage2 [ lIndex + 2 ] == 255 &&
                pucInImage2 [ lIndex + 1 ] == 255 &&
                pucInImage2 [ lIndex + 0 ] == 255 &&
                pucInImage3 [ lIndex + 2 ] == 255 &&
                pucInImage3 [ lIndex + 1 ] == 255 &&
                pucInImage3 [ lIndex + 0 ] == 255 
                ) 
            {
                pucOutImage1 [ lIndex + 2 ] = 255;
                pucOutImage1 [ lIndex + 1 ] = 255;
                pucOutImage1 [ lIndex + 0 ] = 255;
            }
        }
    }
    return true;
}


bool CAlgorithm::
    BoxAdjust (
    unsigned char* pInImage1,
    vector<stRectangleData>& vectorBox,
    int iInWidth,
    int iInHeight,
    int iInBitDepth,
    unsigned char* pOutImage1 
    )
{
    long lY = 0;
    long lX = 0;
    long lIndex = 0;
    vector<stRectangleData>::iterator iterBox;
    long lBoxMinX = iInWidth;
    long lBoxMinY = iInHeight;
    long lBoxMaxX = 0;
    long lBoxMaxY = 0;
    memset ( pOutImage1, 0x00, iInWidth * iInHeight * iInBitDepth );
    if ( vectorBox.size() <= 2 )
    {
        return true;
    }
    for ( iterBox = vectorBox.begin(); iterBox != vectorBox.end(); iterBox++ )
    {
        if ( iterBox->lSX < lBoxMinX )
        {
            lBoxMinX = iterBox->lSX;
        }
        if ( iterBox->lSY < lBoxMinY )
        {
            lBoxMinY = iterBox->lSY;
        }
        if ( iterBox->lEX > lBoxMaxX )
        {
            lBoxMaxX = iterBox->lEX;
        }
        if ( iterBox->lEY > lBoxMaxY )
        {
            lBoxMaxY = iterBox->lEY;
        }
    }
    char clog[255];
    sprintf_s( clog, "Found Fire: ( %d, %d ) - ( %d, %d ) \n",
        lBoxMinX, lBoxMinY, lBoxMaxX, lBoxMaxY );
    OutputDebugString ( clog );

    for ( lY = lBoxMinY; lY <= lBoxMaxY; lY++ )
    {
        for ( lX = lBoxMinX; lX <= lBoxMaxX; lX++ )
        {
            lIndex = ( ( lY  ) * iInWidth * iInBitDepth ) + ( ( lX ) * iInBitDepth );
            pOutImage1 [ lIndex + 2 ] = pInImage1 [ lIndex + 2 ];
            pOutImage1 [ lIndex + 1 ] = pInImage1 [ lIndex + 1 ];
            pOutImage1 [ lIndex + 0 ] = pInImage1 [ lIndex + 0 ];
        } // for ( lX = lBoxMinX; lX <= lBoxMaxX; lX++ )
    } // for ( lY = lBoxMinY; lY <= lBoxMaxY; lY++ )
      
    return true;
}


bool CAlgorithm::
    SearchNeighbor (
    unsigned char* pucInImage1,
    unsigned char* pucInImage2,
    unsigned char* pucInImage3,
    unsigned char* pucInImage4,
    long lInReduceWidth,
    long lInReduceHeight,
    long lInBitDepth,
    vector<stRectangleData>& vectorBox,
    unsigned char* pucOutImage1
    )
{
    int iY = 0;
    int iX = 0;
    long lIndex = 0;
    int iYY = 0;
    int iXX = 0;
    long lIndexA = 0;
    int iYOrigin = 0;
    int iXOrigin = 0;
    long lRGB_R = 0;
    long lRGB_G = 0;
    long lRGB_B = 0;
    double dbYCbCr_Y = 0.0f;
    double dbYCbCr_Cb = 0.0f;
    double dbYCbCr_Cr = 0.0f;
    double dbDiff1 = 0.0f;
    double dbDiff2 = 0.0f;
    long lMinimumY = 0;
    long lMinimumX = 0;
    bool bFinish = false;
    vector<stRectangleData>::iterator iterBox;

    memcpy ( pucOutImage1, pucInImage1, lInReduceWidth * lInReduceHeight * lInBitDepth );

     for ( iterBox = vectorBox.begin(); iterBox != vectorBox.end(); iterBox++ )
    {
        for ( iY = iterBox->lSY; iY < iterBox->lEY; iY++ )
        {
            for ( iX = iterBox->lSX; iX < iterBox->lEX; iX++ )
            {
//         for ( iY = 1; iY < lInReduceHeight; iY++ )
//         {
//             for ( iX = 1; iX < lInReduceWidth; iX++ )
//             {
                lIndex = ( iY * lInReduceWidth * lInBitDepth ) + ( iX * lInBitDepth );
                lRGB_R = pucInImage1 [ lIndex + 2 ];
                lRGB_G = pucInImage1 [ lIndex + 1 ];
                lRGB_B = pucInImage1 [ lIndex + 0 ];
                if ( ( lRGB_R > 0 || lRGB_G > 0 || lRGB_B > 0 ) && ( pucInImage3 [ lIndex + 2 ] == 0 ) )
                {
                    for ( iYY = -1; iYY <= 1; iYY++ )
                    {
                        for ( iXX = -1; iXX <= 1; iXX++ )
                        {
                            lIndexA = ( ( iY + iYY ) * lInReduceWidth * lInBitDepth ) + ( ( iX + iXX ) * lInBitDepth );
                            lRGB_R = pucInImage1 [ lIndexA + 2 ];
                            lRGB_G = pucInImage1 [ lIndexA + 1 ];
                            lRGB_B = pucInImage1 [ lIndexA + 0 ];
                            if ( lRGB_R == 0 && lRGB_G == 0 && lRGB_B == 0 )
                            {
                                lRGB_R = pucInImage2 [ lIndexA + 2 ];
                                lRGB_G = pucInImage2 [ lIndexA + 1 ];
                                lRGB_B = pucInImage2 [ lIndexA + 0 ];
                                dbYCbCr_Y = 0.0f + ( 0.299f * lRGB_R ) + ( 0.587f * lRGB_G ) + ( 0.114f * lRGB_B );
                                dbYCbCr_Cb = 128 - ( 0.168736f * lRGB_R ) - ( 0.331264f * lRGB_G ) + ( 0.5f * lRGB_B );
                                dbYCbCr_Cr = 128 + ( 0.5f * lRGB_R ) - ( 0.418688f * lRGB_G ) - ( 0.081312f * lRGB_B );
                                dbDiff1 = dbYCbCr_Y - dbYCbCr_Cb;
                                dbDiff2 = dbYCbCr_Cr - dbYCbCr_Cb;

                                if ( ( ( lRGB_R > lRGB_G ) && ( lRGB_G > lRGB_B ) ) && 
                                    ( ( dbDiff1 >= 20.0f ) && ( dbDiff2 >= 10.0f ) ) )
                                {

                                    pucInImage1 [ lIndexA + 2 ] = pucInImage2 [ lIndexA + 2 ];
                                    pucInImage1 [ lIndexA + 1 ] = pucInImage2 [ lIndexA + 1 ];
                                    pucInImage1 [ lIndexA + 0 ] = pucInImage2 [ lIndexA + 0 ];
                                    pucOutImage1 [ lIndexA + 2 ] = pucInImage2 [ lIndexA + 2 ];
                                    pucOutImage1 [ lIndexA + 1 ] = pucInImage2 [ lIndexA + 1 ];
                                    pucOutImage1 [ lIndexA + 0 ] = pucInImage2 [ lIndexA + 0 ];
                                }
                            }
                        } // for ( iXX = -1; iXX <= 1; iXX++ )
                    } // for ( iYY = -1; iYY <= 1; iYY++ )
                } // if ( lRGB_R > 0 || lRGB_G > 0 || lRGB_B > 0 )
            } // for ( iX = 1; iX < lInReduceWidth - 1; iX++ )
        } // for ( iY = 1; iY < lInReduceHeight - 1; iY++ )
    }

    return true;
}


bool CAlgorithm::
    StableFrame (
    unsigned char* pucInImage1,
    unsigned char* pucInImage2,
    unsigned char* pucInImage3,
    unsigned char* pucInImage4,
    long lInReduceWidth,
    long lInReduceHeight,
    long lInBitDepth,
    long long llInFrameCount,
    unsigned char* pucOutImage1
    )
{
    if ( ( !pucOutImage1 ) || ( pucOutImage1 == NULL ) ) { return false; }
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
    double dbDiff = 0.0f;

    lFrameIndex = ( ( llInFrameCount - 1 ) % 2 ) + 1;
    if ( lFrameIndex == 1 )
    {
        memcpy ( pucInImage2, pucInImage1, lInReduceWidth * lInReduceHeight * lInBitDepth * sizeof(BYTE) );
    }
    else if ( lFrameIndex == 2 )
    {
        memcpy ( pucInImage3, pucInImage1, lInReduceWidth * lInReduceHeight * lInBitDepth * sizeof(BYTE) );
    }
    if ( llInFrameCount <= 2 ) 
    { 
        return true; 
    }
    memcpy ( pucOutImage1, pucInImage1, lInReduceWidth * lInReduceHeight * lInBitDepth * sizeof(BYTE) );
    for ( lY = 0; lY < lInReduceHeight; lY ++ )
    {
        for ( lX = 0; lX < lInReduceWidth; lX ++ ) 
        {
            lIndex = ( lY * lInReduceWidth * lInBitDepth ) + ( lX * lInBitDepth );
            lRGB_R = abs ( pucInImage2 [ lIndex + 2 ] - pucInImage3 [ lIndex + 2 ] );
            lRGB_G = abs ( pucInImage2 [ lIndex + 1 ] - pucInImage3 [ lIndex + 1 ] );
            lRGB_B = abs ( pucInImage2 [ lIndex + 0 ] - pucInImage3 [ lIndex + 0 ] );
            dbDiff = sqrt ( double ( lRGB_R + lRGB_G + lRGB_B ) );

//             char clog[100];
//             sprintf_s ( clog, "%f\n", dbDiff );
//             OutputDebugString ( clog );

            if ( dbDiff <= 0.0001f )
            {
                pucOutImage1 [ lIndex + 2 ] = 0;
                pucOutImage1 [ lIndex + 1 ] = 0;
                pucOutImage1 [ lIndex + 0 ] = 0;
            }
        }
    }

    return true;
}



bool CAlgorithm:: 
    Thinning (        
    unsigned char* pucInImage1,
    long lInReduceWidth,
    long lInReduceHeight,
    long lInBitDepth,
    unsigned char* pucOutImage1
    )
{
 	int flg = 1;
	long lY, lX, k, n;
	int p[9];	/* 圖形:1背景:0，背景候補:-1 */
    long lIndex = 0;
    long lYY = 0;
    long lXX = 0;
    long lIndexA = 0;

    memset ( pucOutImage1, 0x00, lInReduceWidth * lInReduceHeight * lInBitDepth );

    for (lY = 1; lY < lInReduceHeight-1; lY++) 
    {
        for (lX = 1; lX < lInReduceWidth-1; lX++) 
        {
            lIndex = ( ( lY ) * lInReduceWidth * lInBitDepth ) + ( ( lX ) * lInBitDepth );
            if ( pucInImage1 [ lIndex + 2 ] > 0 ) 
            {
                pucOutImage1 [ lIndex + 2 ] = 255;
                pucOutImage1 [ lIndex + 1 ] = 255;
                pucOutImage1 [ lIndex + 0 ] = 255;
            }
        }
    }

	while (flg != 0) {
		flg = 0;
		for (lY = 1; lY < lInReduceHeight-1; lY++) {
			for (lX = 1; lX < lInReduceWidth-1; lX++) {
                lIndex = ( ( lY ) * lInReduceWidth * lInBitDepth ) + ( ( lX ) * lInBitDepth );
                p[0] = pucOutImage1 [ lIndex + 2 ];
                lIndex = ( ( lY ) * lInReduceWidth * lInBitDepth ) + ( ( lX + 1 ) * lInBitDepth );
				p[1] = pucOutImage1 [ lIndex + 2 ];
                lIndex = ( ( lY - 1 ) * lInReduceWidth * lInBitDepth ) + ( ( lX + 1 ) * lInBitDepth );
	  			p[2] = pucOutImage1 [ lIndex + 2 ];
                lIndex = ( ( lY - 1 ) * lInReduceWidth * lInBitDepth ) + ( ( lX ) * lInBitDepth );
				p[3] = pucOutImage1 [ lIndex + 2 ];
                lIndex = ( ( lY - 1 ) * lInReduceWidth * lInBitDepth ) + ( ( lX - 1 ) * lInBitDepth );
			  	p[4] = pucOutImage1 [ lIndex + 2 ];
                lIndex = ( ( lY ) * lInReduceWidth * lInBitDepth ) + ( ( lX - 1 ) * lInBitDepth );
			  	p[5] = pucOutImage1 [ lIndex + 2 ];
                lIndex = ( ( lY + 1 ) * lInReduceWidth * lInBitDepth ) + ( ( lX - 1 ) * lInBitDepth );
			  	p[6] = pucOutImage1 [ lIndex + 2 ];
                lIndex = ( ( lY + 1 ) * lInReduceWidth * lInBitDepth ) + ( ( lX ) * lInBitDepth );
			  	p[7] = pucOutImage1 [ lIndex + 2 ];
                lIndex = ( ( lY + 1 ) * lInReduceWidth * lInBitDepth ) + ( ( lX + 1 ) * lInBitDepth );
			  	p[8] = pucOutImage1 [ lIndex + 2 ];
				for (k = 0; k < 9; k++) {
					if      (p[k] == 255) p[k] =  1;
                    else if (p[k] ==   0) p[k] =  0;
					else                   p[k] = -1;
				}
				/* 條件1:圖形的一部分 */
				if (p[0] != 1)
                {
                    continue;
                }
				/*條件2:境界像素(4個鄰近像素有1個以上是背景)*/
				if (p[1] * p[3] * p[5] * p[7] != 0)
                {
                    continue;
                }
				/*條件3:保留端點(8個鄰近像素有2個以上是圖形)*/
				n = 0;
				for (k = 1; k < 9; k++) if (p[k] != 0) n++;
				if (n < 2) 
                {
                    continue;
                }
				/*條件4:保留獨立點(8個鄰近像素有1個以上圖形)*/
				n = 0;
				for (k = 1; k < 9; k++) if (p[k] == 1) n++;
				if (n < 1) 
                {
                    continue;
                }
				/*條件5:保留連結性(8個連結數為1)*/
                n = 0;
                if (1) 
                {
                    int	i, i1, i2;
                    int q[9];
                    

                    for (i = 0; i < 9; i++) {
                        if ((p[i] == 1) || (p[i] == -1)) q[i] = 0;
                        else q[i] = 1;
                    }
                    for (i = 1; i < 9; i+=2) {
                        i1 = i + 1;
                        i2 = i + 2;
                        if (i2 == 9) i2 = 1;
                        n = n + q[i] - q[i] * q[i1] * q[i2];
                    }
                    
                }
				if (n != 1) 
                {
                    lIndex = ( ( lY ) * lInReduceWidth * lInBitDepth ) + ( ( lX ) * lInBitDepth );
                    pucOutImage1 [ lIndex + 2 ] = 255;
                    pucOutImage1 [ lIndex + 1 ] = 0;
                    pucOutImage1 [ lIndex + 0 ] = 0;

                    continue;
                }
				/*條件6:線條寬度為2時，只去除單邊(8個鄰近像素是否並非全部是-1，如果是-1時，其值為0，8個連
                                 結數為1)*/
				n = 0;
				for (k = 1; k < 9; k++) {
					if (p[k] != -1) n++;
					else if (p[k] == -1) {
						p[k] = 0;
                        n = 0;
                        if (1) 
                        {
                            int	i, i1, i2;
                            int q[9];

                            for (i = 0; i < 9; i++) {
                                if ((p[i] == 1) || (p[i] == -1)) q[i] = 0;
                                else q[i] = 1;
                            }
                            for (i = 1; i < 9; i+=2) {
                                i1 = i + 1;
                                i2 = i + 2;
                                if (i2 == 9) i2 = 1;
                                n = n + q[i] - q[i] * q[i1] * q[i2];
                            }

                        }
						if (n == 1) n++;
						p[k] = -1;
					}
				}
				if (n < 8) continue;
				/*條件1-6全部滿足時的削除對象 */
                lIndex = ( ( lY ) * lInReduceWidth * lInBitDepth ) + ( ( lX ) * lInBitDepth );
				pucOutImage1 [ lIndex + 2 ] = 128;
                pucOutImage1 [ lIndex + 1 ] = 128;
                pucOutImage1 [ lIndex + 0 ] = 128;
				flg++;
			}
		}
        for (lY = 1; lY < lInReduceHeight-1; lY++) 
        {
            for (lX = 1; lX < lInReduceWidth-1; lX++) 
            {
                lIndex = ( ( lY ) * lInReduceWidth * lInBitDepth ) + ( ( lX ) * lInBitDepth );
				if ( pucOutImage1 [ lIndex + 2 ] == 128 ) pucOutImage1 [ lIndex + 2 ] = 0;
                if ( pucOutImage1 [ lIndex + 1 ] == 128 ) pucOutImage1 [ lIndex + 1 ] = 0;
                if ( pucOutImage1 [ lIndex + 0 ] == 128 ) pucOutImage1 [ lIndex + 0 ] = 0;
            }
        }
	}
    return true;
}



bool CAlgorithm::
    RGBtoHSVFrame (
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
    memset ( piOutImage1, 0x00, lInReduceWidth * lInReduceHeight * lInBitDepth * sizeof(int) );
    memset ( pucOutImage1, 0x00, lInReduceWidth * lInReduceHeight * lInBitDepth );
	for (lY = 0; lY < lInReduceHeight; lY++) 
    {
		for (lX = 0; lX < lInReduceWidth; lX++) 
        {
            lIndex = ( lY * lInReduceWidth * lInBitDepth ) + ( lX * lInBitDepth );
            if ( pucInImage1 [ lIndex + 2 ] == 255 )
            {
                RGBIn.r = pucInImage1 [ lIndex + 2 ];
                RGBIn.g = pucInImage1 [ lIndex + 1 ]; 
                RGBIn.b = pucInImage1 [ lIndex + 0 ];
                HSVOut = rgb2hsv ( RGBIn );
                //RGBtoHSV ( RGBIn.r, RGBIn.g, RGBIn.b, &HSVOut.h, &HSVOut.s, &HSVOut.v );
                //HSI ( RGBIn.r, RGBIn.g, RGBIn.b, HSIOut.h, HSIOut.s, HSIOut.v );
                if ( 
                    ( HSVOut.h >= 0 && HSVOut.h <= 60 )
                    )
                {
                    piOutImage1 [ lIndex + 2 ] = (int) HSVOut.h;
                    piOutImage1 [ lIndex + 1 ] = (int) HSVOut.s;
                    piOutImage1 [ lIndex + 0 ] = (int) HSVOut.v;
                    pucOutImage1 [ lIndex + 2 ] = pucInImage2 [ lIndex + 2 ];
                    pucOutImage1 [ lIndex + 1 ] = pucInImage2 [ lIndex + 1 ];
                    pucOutImage1 [ lIndex + 0 ] = pucInImage2 [ lIndex + 0 ];
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
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max;                                // v
    delta = max - min;
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0              
        // s = 0, v is undefined
        out.s = 0.0;
        out.h = NAN;                            // its now undefined
        return out;
    }
    if( in.r >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
    else
        if( in.g >= max )
            out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
        else
            out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if( out.h < 0.0 )
        out.h += 360.0;

    return out;
}

void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v )
{
    float fmin, fmax, delta;
    fmin = min ( min ( r, g), b );
    fmax = max ( max ( r, g), b );
    *v = fmax;				// v
    delta = fmax - fmin;
    if( fmax != 0 )
        *s = delta / fmax;		// s
    else {
        // r = g = b = 0		// s = 0, v is undefined
        *s = 0;
        *h = -1;
        return;
    }
    if( r == fmax )
        *h = ( g - b ) / delta;		// between yellow & magenta
    else if( g == fmax )
        *h = 2 + ( b - r ) / delta;	// between cyan & yellow
    else
        *h = 4 + ( r - g ) / delta;	// between magenta & cyan
    *h *= 60;				// degrees
    if( *h < 0 )
        *h += 360;
}


void HSI (
    IN unsigned int r,
    IN unsigned int g,
    IN unsigned int b,
    OUT double &Hue,
    OUT double &Saturation,
    OUT double &Intensity
    )
{
    unsigned int nImax,nImin,nSum,nDifference;
    if( (r<0 && g<0 && b<0) || (r>255 || g>255 || b>255) )
    {
        Hue=Saturation=Intensity=0;
        return;
    }

    if(g==b)
    {
        if(b<255)
        {
            b=b+1;
        }
        else
        {
            b=b-1;
        }
    }

    nImax = _Max(r,b);
    nImax = _Max(nImax,g);
    nImin = _Min(r,b);
    nImin = _Min(nImin,g);
    nSum = nImin+nImax;
    nDifference =nImax-nImin;

    Intensity = (float)nSum/2;

    if(Intensity<128)
    {
        Saturation=(255*((float)nDifference/nSum));
    }
    else
    {
        Saturation=(float)(255*((float)nDifference/(510-nSum)));
    }

    if(Saturation!=0)
    {
        if(nImax == r)    
        {
            Hue=(60*((float)g-(float)b)/nDifference);
        }
        else if(nImax == g)
        {
            Hue=(60*((float)b-(float)r)/nDifference+120);
        }
        else if(nImax == b)
        {
            Hue=(60*((float)r-(float)g)/nDifference+240);
        }

        if(Hue<0)
        {
            Hue=(60*((float)b-(float)r)/nDifference+120);
        }
    }
    else
    {
        Hue=-1;
    }

    return;
}


rgb hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
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


void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v )
{
    int i;
    float f, p, q, t;
    if( s == 0 ) {
        // achromatic (grey)
        *r = *g = *b = v;
        return;
    }
    h /= 60;			// sector 0 to 5
    i = floor( h );
    f = h - i;			// factorial part of h
    p = v * ( 1 - s );
    q = v * ( 1 - s * f );
    t = v * ( 1 - s * ( 1 - f ) );
    switch( i ) {
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

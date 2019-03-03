#pragma once

#include "stdafx.h"
#include "COtherAlgorithm0001.h"
#include "CAlgorithm.h"


COtherAlgorithm0001::COtherAlgorithm0001()
{
    pAlg = (void*) new CAlgorithm();
}


COtherAlgorithm0001::~COtherAlgorithm0001()
{
    if ( pAlg )
    {
        delete (CAlgorithm*) pAlg;
    }
    pAlg = NULL;
}


bool COtherAlgorithm0001::
    AlgInit (                        
    bool* _INOUT_ pbInOutInitial,    
    void* _IN_ pstInInitParameter,   
    void* _IN_ pInReserve            
    )
{
    bool bInOutInitial = (*pbInOutInitial);
    if ( bInOutInitial == false )
    {
        return true;
    }
    else if ( bInOutInitial == true )
    {
        if ( ( (CAlgorithm*) pAlg )->AlgInit (
            _IN_ pstInInitParameter ) == false )
        {
            return false;
        }
        else
        {
            (*pbInOutInitial) = false;
        }
    }
    return true;
}


bool COtherAlgorithm0001::
    AlgRelease (                  
    void* _IN_ pInReserve,        
    void* _OUT_ pOutReserve       
    )
{
    if ( ( (CAlgorithm*) pAlg )->AlgRelease() == false )
    {
        return false;
    }

    return true;
}


bool COtherAlgorithm0001::
    AlgInput (                       
    unsigned char* _IN_ pucInData,   
    long _IN_ lInWidth,              
    long _IN_ lInHeight,             
    long _IN_ lInBitDepth,           
    void* _IN_ pstInInputParameter,  
    void* _IN_ pInReserve            
    )
{
    if ( ( (CAlgorithm*) pAlg )->AlgInput (
        _IN_ pucInData,
        _IN_ lInWidth,
        _IN_ lInHeight,
        _IN_ lInBitDepth,
        _IN_ pstInInputParameter,
        _IN_ pInReserve  
        ) == false )
    {
        return false;
    }
    return true;
}


bool COtherAlgorithm0001::
    AlgProcessing (                 
    void* _IN_ pInReserve,          
    void* _OUT_ pOutReserve         
    )
{
    if ( ( (CAlgorithm*) pAlg )->AlgProcessing (
        _IN_ pInReserve,  
        _OUT_ pOutReserve 
        ) == false )
    {
        return false;
    }
    return true;
}


bool COtherAlgorithm0001::
    AlgOutput (                     
    unsigned char* _OUT_ pucOutData1, 
    unsigned char* _OUT_ pucOutData2,
    double* _OUT_ dbOutTimeDiff,
    void* _OUT_ pstOutputParameter,  
    void* _OUT_ pOutReserve          
    )
{
    if ( ( (CAlgorithm*) pAlg )->AlgOutput (
        _OUT_ pucOutData1,   
        _OUT_ pucOutData2,
        _OUT_ dbOutTimeDiff,
        _OUT_ pstOutputParameter,
        _OUT_ pOutReserve        
        ) == false )
    {
        return false;
    }
    return true;
}





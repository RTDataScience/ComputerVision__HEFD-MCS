#pragma once
#include "stdafx.h"


class DirectShowControl_SampleGrabberCallback : public ISampleGrabberCB
{
public:

    STDMETHODIMP_(ULONG) AddRef() { return 1; }
    STDMETHODIMP_(ULONG) Release() { return 2; }

    STDMETHODIMP QueryInterface(REFIID riid, void **ppvObject)
    {
        if (NULL == ppvObject) return E_POINTER;
        if (riid == __uuidof(IUnknown))
        {
            *ppvObject = static_cast<IUnknown*>(this);
             return S_OK;
        }
        if (riid == __uuidof(ISampleGrabberCB))
        {
            *ppvObject = static_cast<ISampleGrabberCB*>(this);
             return S_OK;
        }
        return E_NOTIMPL;
    }

    STDMETHODIMP SampleCB(double Time, IMediaSample *pSample)
    {
        return E_NOTIMPL;
    }

    typedef void ( CALLBACK* DirectShowControl_ImageCallback )( void* UserParam, BYTE* buf, DWORD len, DWORD dwWidth, DWORD dwHeight );
    DirectShowControl_ImageCallback m_CALLBACK_Image;
    void* m_USERPARAM_Image;
    void SetImageCallback( void* UserParam, DirectShowControl_ImageCallback fnImageCallback )
    {
        m_USERPARAM_Image = UserParam;
        m_CALLBACK_Image = fnImageCallback;
    }

    AM_MEDIA_TYPE Am_Media_Type;
    void SetAmMediaType ( AM_MEDIA_TYPE am_media_type )
    {
        Am_Media_Type = am_media_type;
    }

    STDMETHODIMP BufferCB(double Time, BYTE *pBuffer, long BufferLen)
    {
        if ((Am_Media_Type.majortype != MEDIATYPE_Video) ||
            (Am_Media_Type.formattype != FORMAT_VideoInfo) ||
            (Am_Media_Type.cbFormat < sizeof(VIDEOINFOHEADER)) ||
            (Am_Media_Type.pbFormat == NULL))
        {
            return VFW_E_INVALIDMEDIATYPE;
        }

        long cbBitmapInfoSize = Am_Media_Type.cbFormat - SIZE_PREHEADER;
        VIDEOINFOHEADER *pVideoHeader = (VIDEOINFOHEADER*)Am_Media_Type.pbFormat;
        BITMAPINFOHEADER bitmapinfoheader;
        memcpy ( &bitmapinfoheader, &pVideoHeader->bmiHeader, sizeof(BITMAPINFOHEADER) );
        long BmpWidth = pVideoHeader->bmiHeader.biWidth;
        long BmpHeight = abs ( pVideoHeader->bmiHeader.biHeight );
        long BmpBitDpeth = pVideoHeader->bmiHeader.biBitCount / 8;
        long BmpLength = ( BmpWidth * BmpHeight * BmpBitDpeth );
        if ( BmpLength != BufferLen )
        {
            return VFW_E_INVALIDMEDIATYPE;
        }
        BYTE* pBmpTemp = new BYTE [ sizeof(BITMAPINFOHEADER) + BmpLength ];
        memcpy ( pBmpTemp, &bitmapinfoheader, sizeof(BITMAPINFOHEADER) );
        if ( pVideoHeader->bmiHeader.biHeight > 0 )
        {
            ( ( LPBITMAPINFOHEADER ) pBmpTemp )->biHeight = -( ( ( LPBITMAPINFOHEADER ) pBmpTemp )->biHeight );
            ReverseImage ( pBuffer, pBmpTemp + sizeof(BITMAPINFOHEADER), BmpWidth, BmpHeight, BmpBitDpeth );
        }
        else 
        {
            memcpy ( pBmpTemp + sizeof(BITMAPINFOHEADER), pBuffer, BmpLength );
        }

        m_CALLBACK_Image ( 
            m_USERPARAM_Image, 
            pBmpTemp, 
            BmpLength, 
            BmpWidth, 
            BmpHeight
            );

        delete [] pBmpTemp;

        return S_OK;

    }

    void ReverseImage ( BYTE* pInImage, BYTE* pOutImage, long lWidth, long lHeight, long lBitDepth )
    {
        long lWidthStep = lWidth * lBitDepth;
        long lY = 0;
        long lYY = lHeight - 1;
        long lIndexSrc = 0;
        long lIndexDst = 0;
        for ( lY = 0; lY < lHeight; lY++ )
        {
            lIndexSrc = ( lY * lWidthStep );
            lIndexDst = ( lYY * lWidthStep );
            memcpy ( pOutImage + lIndexDst, pInImage + lIndexSrc, lWidthStep );
            lYY--;
        }
    }


};

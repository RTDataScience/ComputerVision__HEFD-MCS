// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#define _USING_V110_SDK71_
#define __D3DRM_H__

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars




#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

extern "C"
{
    void ShowError();
};

//======(S)
#define SAFE_DELETE(x) if( (x) != NULL ) {delete (x); (x) = NULL;}
#define SAFE_DELETE_ARRAY(x) if( (x) != NULL ) {delete[] (x); (x) = NULL;}
#define SAFE_RELEASE(x) if( (x) != NULL ) {(x)->Release(); (x) = NULL;}
//======(E)


//////////////////////////////////////////////////////////////////////////
#include "streams.h"
#include <strsafe.h>
#include "DShowUtil.h"
#include "smartptr.h"
#include "resource.h"
//////////////////////////////////////////////////////////////////////////

static HANDLE m_handleACTiSDK;

/*
Error   LNK2019 unresolved external symbol __vsnprintf referenced in function "long __stdcall StringVPrintfWorkerA(char *,unsigned int,unsigned int *,char const *,char *)" (?StringVPrintfWorkerA@@YGJPADIPAIPBD0@Z)
the same problem using DXGetErrorMessage() with Dx9 and found out that MS have provided an additional library to include in the Additional Dependencies properties page to address this problem. The library name is: legacy_stdio_definitions.lib
*/

/*
<stdio.h> 和 <conio.h>
printf 和 scanf 系列的函式現在已定義為內嵌。
所有 printf 和 scanf 函式的定義都已內嵌移動到 <stdio.h>、<conio.h> 和其他 CRT 標頭中。 對於區域宣告這些函式，但不包含適當的 CRT 標頭之任何程式而言，這是會導致連結器錯誤 (LNK2019，無法解析的外部符號) 的重大變更。 可能的話，您應該更新程式碼，包含此 CRT 標頭 (亦即，加入 #include <stdio.h>) 和此內嵌函式，但如果您不要修改程式碼以包含這些標頭檔，替代方案是將額外的程式庫加入您的連結器輸入 legacy_stdio_definitions.lib 中。
若要將您在此 IDE 中的連結器輸入加入這個程式庫，請開啟專案節點的操作功能表，選擇 [屬性]，接著在 [專案屬性] 對話方塊中選擇 [連結器]，並編輯 [連結器輸入]，將 legacy_stdio_definitions.lib 加入此分號分隔的清單。
*/


#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CApp_testDataApp
// 有关此类实现的信息，请参阅 App_testData.cpp
//

class CApp_testDataApp : public CWinApp
{
public:
	CApp_testDataApp();
// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

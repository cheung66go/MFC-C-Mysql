#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CApp_testDataApp
// �йش���ʵ�ֵ���Ϣ������� App_testData.cpp
//

class CApp_testDataApp : public CWinApp
{
public:
	CApp_testDataApp();
// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

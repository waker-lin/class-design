
// 02_TCPClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy02_TCPClientApp: 
// �йش����ʵ�֣������ 02_TCPClient.cpp
//

class CMy02_TCPClientApp : public CWinApp
{
public:
	CMy02_TCPClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy02_TCPClientApp theApp;
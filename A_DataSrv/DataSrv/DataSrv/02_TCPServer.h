
// 02_TCPServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy02_TCPServerApp: 
// �йش����ʵ�֣������ 02_TCPServer.cpp
//

class CMy02_TCPServerApp : public CWinApp
{
public:
	CMy02_TCPServerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy02_TCPServerApp theApp;
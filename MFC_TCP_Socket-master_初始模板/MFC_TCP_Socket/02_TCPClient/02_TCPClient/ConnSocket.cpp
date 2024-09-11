// ConnSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "02_TCPClient.h"
#include "ConnSocket.h"
#include "02_TCPClientDlg.h"

// CConnSocket

CConnSocket::CConnSocket(CMy02_TCPClientDlg* dlg)
{
	m_dlg = dlg;
}

CConnSocket::~CConnSocket()
{
}

BOOL CConnSocket::Connect(LPCTSTR lpszHostAddress, UINT nHostPort)
{
	m_ip = lpszHostAddress;
	m_port = nHostPort;
	return CAsyncSocket::Connect(lpszHostAddress, nHostPort);
}


// CConnSocket ��Ա����

// ���ӷ������ɹ����ú����ᱻ����
void CConnSocket::OnConnect(int nErrorCode)
{
	// �������ɿ�ܵ��ã�֪ͨ���׽������Ӳ����Ѿ���ɣ�����˵�������ǳɹ�����ʧ���ˡ�

	CSocket::OnConnect(nErrorCode);
}


void CConnSocket::OnClose(int nErrorCode)
{
	// �ɿ�ܵ���֪ͨ���׽��֣��������ϵĶ�Ӧ�׽����Ѿ�����ؽ�����ֹ��
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: already close!"), t.wHour, t.wMinute, t.wSecond, m_ip, m_port);
	m_dlg->AddMsg(msg);
	m_dlg->MyEnableBtn();

	this->Close();
	CSocket::OnClose(nErrorCode);
}


void CConnSocket::OnReceive(int nErrorCode)
{
	// �������ɿ�ܵ��ã�֪ͨ�׽��ֻ����������ݣ����Ե���Receive��Ա����ȡ��
	char recvBuf[512] = { 0 };
	int recvLen = this->Receive(recvBuf, sizeof(recvBuf));
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:Car%d %s"), t.wHour,t.wMinute, t.wSecond, m_ip, nErrorCode,CString(recvBuf));
	m_dlg->AddMsg(msg);

	CSocket::OnReceive(nErrorCode);
}

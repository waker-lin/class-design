#include "stdafx.h"
#include "ClientSocket1.h"
#include "stdafx.h"
#include "02_TCPClient.h"
#include "ConnSocket.h"
#include "02_TCPClientDlg.h"
#include "CarCommu.h"

// CConnSocket

ClientSocket1::ClientSocket1(CarCommu* dlg)
{
	c_dlg = dlg;
}

ClientSocket1::~ClientSocket1()
{
}


BOOL ClientSocket1::Connect(LPCTSTR lpszHostAddress, UINT nHostPort)
{
	m_ip = lpszHostAddress;
	m_port = nHostPort;
	return CAsyncSocket::Connect(lpszHostAddress, nHostPort);
}


// CConnSocket ��Ա����

// ���ӷ������ɹ����ú����ᱻ����
void ClientSocket1::OnConnect(int nErrorCode)
{
	// �������ɿ�ܵ��ã�֪ͨ���׽������Ӳ����Ѿ���ɣ�����˵�������ǳɹ�����ʧ���ˡ�

	CSocket::OnConnect(nErrorCode);
}

void ClientSocket1::OnClose(int nErrorCode)
{
	// �ɿ�ܵ���֪ͨ���׽��֣��������ϵĶ�Ӧ�׽����Ѿ�����ؽ�����ֹ��
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: already close!"), t.wHour, t.wMinute, t.wSecond, m_ip, m_port);

	this->Close();
	CSocket::OnClose(nErrorCode);
}
CString ClientSocket1::messager;
void ClientSocket1::OnReceive(int nErrorCode)
{
	// �������ɿ�ܵ��ã�֪ͨ�׽��ֻ����������ݣ����Ե���Receive��Ա����ȡ��
	char recvBuf[512] = { 0 };
	int recvLen = this->Receive(recvBuf, sizeof(recvBuf));
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s: %s"), t.wHour, t.wMinute, t.wSecond, m_ip, CString(recvBuf));
	//c_dlg->m_rcver.SetWindowTextW(msg);


	//AfxMessageBox(msg);
	messager = msg;
	//c_dlg->AddEdit(msg);

	CSocket::OnReceive(nErrorCode);
}
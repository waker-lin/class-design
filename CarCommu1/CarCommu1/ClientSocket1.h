#pragma once
#include <afxsock.h>
class CarCommu;

class ClientSocket1 :
    public CSocket
{
public:
	ClientSocket1(CarCommu* dlg = NULL);
	virtual ~ClientSocket1();
	BOOL Connect(LPCTSTR lpszHostAddress, UINT nHostPort);

	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//private:
	//CMy02_TCPClientDlg* m_dlg;
	CarCommu* c_dlg;
	CString m_ip;
	UINT m_port;
	static CString messager;
public:
	virtual void OnReceive(int nErrorCode);
};


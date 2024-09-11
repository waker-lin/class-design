#pragma once
#include"string"
using namespace std;
// CConnSocket 命令目标
class CMy02_TCPServerDlg;

class CConnSocket : public CSocket
{
public:
	CConnSocket(CMy02_TCPServerDlg* dlg = NULL);
	virtual ~CConnSocket();
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	// 设置连接的客户端的IP和端口
	void SetClientAddr(CString ip, USHORT port);
//private:
	CString m_ip;
	USHORT m_port;
	CMy02_TCPServerDlg* m_dlg;
	//CServerSocket* Insert;

	//CConnSocket* pClient;
	//CServerSocket* s_dlg;
	
public:
	void Sender( CString msg);
	void SendAll();
	void SelectSender(char* rcv);
	void generateRandomLanguage();
};



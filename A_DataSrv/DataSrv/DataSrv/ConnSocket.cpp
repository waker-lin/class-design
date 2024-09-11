// ConnSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "02_TCPServer.h"
#include "ConnSocket.h"
#include "ServerSocket.h"
#include "string"
#include <fstream>
#include <vector>
#include "02_TCPServerDlg.h"
using namespace std;
// CConnSocket

CConnSocket::CConnSocket(CMy02_TCPServerDlg* dlg)
{
	m_dlg = dlg;
}

CConnSocket::~CConnSocket()
{
}


// CConnSocket 成员函数

// 当服务器和客户端成功建立好连接，服务器端自动调用此函数
void CConnSocket::OnSend(int nErrorCode)
{
	// 本函数由框架调用，通知套接字现在可以调用Send成员函数发送数据了。
	char buf[] = "连接服务器成功";
	Send(buf, strlen(buf)); //给客户端发送信息
	CSocket::OnSend(nErrorCode);
}

// 当对方发送消息，自动调用此函数
// 可以在函数内容做接收处理
void CConnSocket::OnReceive(int nErrorCode)
{
	// 本函数由框架调用，通知套接字缓冲中有数据，可以调用Receive成员函数取出
	char recvBuf[512] = { 0 };
	char buff[1024] = { 0 };
	char buff1[1024] = { 0 };

	int recvLen = this->Receive(recvBuf, sizeof(recvBuf));
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	
	if (strcmp(recvBuf,"路况")==0) {
		generateRandomLanguage();
	}
	else if (40 >= atof(recvBuf) && atof(recvBuf) >=20)
	{
		msg.Format(_T("[%d:%d:%d] %s:%d:速度为 %skm/h      "), t.wHour, t.wMinute, t.wSecond, m_ip, m_port, CString(recvBuf));
		m_dlg->AddMsg(msg);
		if (40 > atof(recvBuf)&& atof(recvBuf) > 35)
		{
			sprintf(buff, "速度过快，请减速，当前速度为:%s km/h        ", recvBuf);
			Send(buff, strlen(buff));
		}
	}
	else if (10>= atof(recvBuf) >=0)
	{
		msg.Format(_T("[%d:%d:%d] %s:%d:距离为:%s米        "), t.wHour, t.wMinute, t.wSecond, m_ip, m_port, CString(recvBuf));
		m_dlg->AddMsg(msg);
		if (2 > atof(recvBuf)&& atof(recvBuf) > 0)
		{
			sprintf(buff1, "车距较近，请注意，当前车距为 %s m      ", recvBuf);
			Send(buff1, strlen(buff1));
		}
	}
	else
	{
		msg.Format(_T("[%d:%d:%d] %s:%d: %s"), t.wHour, t.wMinute, t.wSecond, m_ip, m_port, CString(recvBuf));
		m_dlg->AddMsg(msg);
	}
	
	/*for (auto it = Insert->m_clientList.begin(); it != Insert->m_clientList.end(); ++it) {
		CConnSocket* pClientSocket = *it;

		// Assuming CConnSocket has member functions GetPort() and GetIPAddress()
		USHORT clientPort = pClientSocket->m_port;

		// Convert USHORT to CString for comparison
		CString strClientPort;
		strClientPort.Format(_T("%hu"), clientPort);

		// Get the C-style string from CString
		const char* charClientPort = CT2A(strClientPort.GetString());

		if (strcmp(charClientPort, recvBuf) == 0)
		{
			pClient = pClientSocket;
			AfxMessageBox(_T("选上了"));
		}
	}
	pClient->Send(recvBuf, strlen(recvBuf));*/
	/**/
	// 回射信息
	//CharUpperA(recvBuf);
	//this->Send(recvBuf, strlen(recvBuf));
}

// 对方主动断开连接，自动调用此函数
void CConnSocket::OnClose(int nErrorCode)
{
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: 断开与服务器连接!"), t.wHour,t.wMinute,t.wSecond,m_ip, m_port);
	m_dlg->AddMsg(msg);
	//this->Send(msg, strlen(msg));

	CString porte, time;
	porte.Format(_T("%d"),m_port);
	time.Format(_T("[%d:%d:%d]"), t.wHour, t.wMinute, t.wSecond);
	// Insert the information into the list control
	int nIndex = m_dlg->m_listCtrl1.GetItemCount();
	m_dlg->m_listCtrl1.InsertItem(nIndex, _T(""));//要有这个，不然显示不了

	m_dlg->m_listCtrl1.SetItemText(nIndex, 1, m_ip); // Assuming column 0 is for IP address
	m_dlg->m_listCtrl1.SetItemText(nIndex, 2, porte); // Column 1 for port
	m_dlg->m_listCtrl1.SetItemText(nIndex, 0, time); // Column 1 for port
	m_dlg->m_listCtrl1.SetItemText(nIndex, 3, _T("离线")); // Column 1 for port

	CStringA fixedFilePath1 = "D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\excel\\端口号储存.csv";
	std::ofstream SaveFile1(fixedFilePath1, std::ios::app); // 追加模式
	if (!SaveFile1.is_open())
	{
		AfxMessageBox(_T("Failed to open file!"));
		return;
	}

	CStringA timeA(time);
	CStringA clientIPA(m_ip);
	CStringA porteA(porte);

	SaveFile1 << timeA.GetString() << "," << clientIPA.GetString() << "," << porteA.GetString() << "," << "离线" << std::endl;

	SaveFile1.close();

	CSocket::OnClose(nErrorCode);
}

void CConnSocket::SetClientAddr(CString ip, USHORT port)
{
	m_ip = ip;
	m_port = port;
}


void CConnSocket::Sender(CString msg)
{
	// TODO: 在此处添加实现代码.
	
}


void CConnSocket::SendAll()
{
	// TODO: 在此处添加实现代码.
	CServerSocket* c_dlg = new CServerSocket;

	c_dlg->Sender(_T("1"));
}


void CConnSocket::SelectSender(char* rcv)
{
	// TODO: 在此处添加实现代码.
	/*for (auto it = s_dlg->m_clientList.begin(); it != s_dlg->m_clientList.end(); ++it) {
		if (*rcv == (*it)->m_port)
		{

		}
	}*/
}


void CConnSocket::generateRandomLanguage()
{
	// TODO: 在此处添加实现代码.
	std::vector<std::string> pathRecommendations = { "沿着道路直行", "左转然后右转", "沿途风景优美", "选择高速公路", "绕过交通拥堵区" };

	std::vector<std::string> trafficConditions = { "交通畅通", "遇到了一些交通拥堵", "道路状况良好", "请注意行驶速度" };

	// 随机选择语言片段
	std::string pathRecommendation = pathRecommendations[rand() % pathRecommendations.size()];
	std::string trafficCondition = trafficConditions[rand() % trafficConditions.size()];

	// 构造最终的语言描述
	std::string language1 = "推荐路径：" + pathRecommendation + "。";
	std::string language2 = "路况信息：" + trafficCondition; + "。";

	char buff2[1024] = { 0 };
	strcpy(buff2, language1.c_str());
	Send(buff2, strlen(buff2));
	Sleep(1000);
	strcpy(buff2, language2.c_str());
	Send(buff2, strlen(buff2));

}

// ConnSocket.cpp : ʵ���ļ�
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


// CConnSocket ��Ա����

// ���������Ϳͻ��˳ɹ����������ӣ����������Զ����ô˺���
void CConnSocket::OnSend(int nErrorCode)
{
	// �������ɿ�ܵ��ã�֪ͨ�׽������ڿ��Ե���Send��Ա�������������ˡ�
	char buf[] = "���ӷ������ɹ�";
	Send(buf, strlen(buf)); //���ͻ��˷�����Ϣ
	CSocket::OnSend(nErrorCode);
}

// ���Է�������Ϣ���Զ����ô˺���
// �����ں������������մ���
void CConnSocket::OnReceive(int nErrorCode)
{
	// �������ɿ�ܵ��ã�֪ͨ�׽��ֻ����������ݣ����Ե���Receive��Ա����ȡ��
	char recvBuf[512] = { 0 };
	char buff[1024] = { 0 };
	char buff1[1024] = { 0 };

	int recvLen = this->Receive(recvBuf, sizeof(recvBuf));
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	
	if (strcmp(recvBuf,"·��")==0) {
		generateRandomLanguage();
	}
	else if (40 >= atof(recvBuf) && atof(recvBuf) >=20)
	{
		msg.Format(_T("[%d:%d:%d] %s:%d:�ٶ�Ϊ %skm/h      "), t.wHour, t.wMinute, t.wSecond, m_ip, m_port, CString(recvBuf));
		m_dlg->AddMsg(msg);
		if (40 > atof(recvBuf)&& atof(recvBuf) > 35)
		{
			sprintf(buff, "�ٶȹ��죬����٣���ǰ�ٶ�Ϊ:%s km/h        ", recvBuf);
			Send(buff, strlen(buff));
		}
	}
	else if (10>= atof(recvBuf) >=0)
	{
		msg.Format(_T("[%d:%d:%d] %s:%d:����Ϊ:%s��        "), t.wHour, t.wMinute, t.wSecond, m_ip, m_port, CString(recvBuf));
		m_dlg->AddMsg(msg);
		if (2 > atof(recvBuf)&& atof(recvBuf) > 0)
		{
			sprintf(buff1, "����Ͻ�����ע�⣬��ǰ����Ϊ %s m      ", recvBuf);
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
			AfxMessageBox(_T("ѡ����"));
		}
	}
	pClient->Send(recvBuf, strlen(recvBuf));*/
	/**/
	// ������Ϣ
	//CharUpperA(recvBuf);
	//this->Send(recvBuf, strlen(recvBuf));
}

// �Է������Ͽ����ӣ��Զ����ô˺���
void CConnSocket::OnClose(int nErrorCode)
{
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: �Ͽ������������!"), t.wHour,t.wMinute,t.wSecond,m_ip, m_port);
	m_dlg->AddMsg(msg);
	//this->Send(msg, strlen(msg));

	CString porte, time;
	porte.Format(_T("%d"),m_port);
	time.Format(_T("[%d:%d:%d]"), t.wHour, t.wMinute, t.wSecond);
	// Insert the information into the list control
	int nIndex = m_dlg->m_listCtrl1.GetItemCount();
	m_dlg->m_listCtrl1.InsertItem(nIndex, _T(""));//Ҫ���������Ȼ��ʾ����

	m_dlg->m_listCtrl1.SetItemText(nIndex, 1, m_ip); // Assuming column 0 is for IP address
	m_dlg->m_listCtrl1.SetItemText(nIndex, 2, porte); // Column 1 for port
	m_dlg->m_listCtrl1.SetItemText(nIndex, 0, time); // Column 1 for port
	m_dlg->m_listCtrl1.SetItemText(nIndex, 3, _T("����")); // Column 1 for port

	CStringA fixedFilePath1 = "D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\excel\\�˿ںŴ���.csv";
	std::ofstream SaveFile1(fixedFilePath1, std::ios::app); // ׷��ģʽ
	if (!SaveFile1.is_open())
	{
		AfxMessageBox(_T("Failed to open file!"));
		return;
	}

	CStringA timeA(time);
	CStringA clientIPA(m_ip);
	CStringA porteA(porte);

	SaveFile1 << timeA.GetString() << "," << clientIPA.GetString() << "," << porteA.GetString() << "," << "����" << std::endl;

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
	// TODO: �ڴ˴����ʵ�ִ���.
	
}


void CConnSocket::SendAll()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	CServerSocket* c_dlg = new CServerSocket;

	c_dlg->Sender(_T("1"));
}


void CConnSocket::SelectSender(char* rcv)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	/*for (auto it = s_dlg->m_clientList.begin(); it != s_dlg->m_clientList.end(); ++it) {
		if (*rcv == (*it)->m_port)
		{

		}
	}*/
}


void CConnSocket::generateRandomLanguage()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	std::vector<std::string> pathRecommendations = { "���ŵ�·ֱ��", "��תȻ����ת", "��;�羰����", "ѡ����ٹ�·", "�ƹ���ͨӵ����" };

	std::vector<std::string> trafficConditions = { "��ͨ��ͨ", "������һЩ��ͨӵ��", "��·״������", "��ע����ʻ�ٶ�" };

	// ���ѡ������Ƭ��
	std::string pathRecommendation = pathRecommendations[rand() % pathRecommendations.size()];
	std::string trafficCondition = trafficConditions[rand() % trafficConditions.size()];

	// �������յ���������
	std::string language1 = "�Ƽ�·����" + pathRecommendation + "��";
	std::string language2 = "·����Ϣ��" + trafficCondition; + "��";

	char buff2[1024] = { 0 };
	strcpy(buff2, language1.c_str());
	Send(buff2, strlen(buff2));
	Sleep(1000);
	strcpy(buff2, language2.c_str());
	Send(buff2, strlen(buff2));

}

// CarCommu.cpp: 实现文件
//

#include"stdafx.h"
#include "pch.h"
#include "CarCommu.h"
#include "afxdialogex.h"
#include "resource.h"
#include "02_TCPClientDlg.h"
#include <fstream>
#include <sstream>
#include "ConnSocket.h"
#include "ClientSocket1.h"


// CarCommu 对话框

IMPLEMENT_DYNAMIC(CarCommu, CDialogEx)

CarCommu::CarCommu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_port(_T(""))
	, m_rcv(_T(""))
	, m_send(_T(""))
	, m_r(_T(""))
{

}

CarCommu::~CarCommu()
{
}

void CarCommu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_port);
	DDX_Text(pDX, IDC_EDIT3, m_rcv);
	DDX_Text(pDX, IDC_EDIT2, m_send);
	DDX_Control(pDX, IDC_EDIT1, m_CsendBuf);
	DDX_Control(pDX, IDC_EDIT2, m_sender);
	DDX_Control(pDX, IDC_EDIT3, m_rcver);
	DDX_Control(pDX, IDC_EDIT4, m_rc);
	DDX_Text(pDX, IDC_EDIT4, m_r);
}


BEGIN_MESSAGE_MAP(CarCommu, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CarCommu::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CarCommu::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CarCommu::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &CarCommu::OnBnClickedButton5)
	ON_BN_CLICKED(IDCANCEL, &CarCommu::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CarCommu::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON6, &CarCommu::OnBnClickedButton6)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CarCommu 消息处理程序


BOOL CarCommu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	CString col[4] = { _T("时间"),_T("IP"),_T("端口号"),_T("状态") };
	RECT r;	//rect对象用来存储一个矩形框的左上角坐标、宽度和高度。
	m_listCtrl.GetClientRect(&r);	//显示矩形框调用函数要加取地址符号
	for (int i = 0; i < 4; i++)
	{
		m_listCtrl.InsertColumn(i, col[i], LVCFMT_CENTER, (r.right - r.left) / 4);
	}


	m_listCtrl.SetBkColor(RGB(199, 237, 233));	//设置列表框背景颜色
	m_listCtrl.SetTextColor(RGB(18, 53, 85));	//字体颜色
	m_listCtrl.SetTextBkColor(RGB(175, 215, 237));//文字背景色

	//m_ip.SetAddress(127, 0, 0, 1);
	//UpdateData(FALSE);

	// 创建一个套接字对象


	// 尝试连接到服务器
	if (clientSocket.Create()&& clientSocket.Connect(_T("127.0.0.1"), 8811))
	{
		// 连接成功，可以发送和接收数据了
		// 在这里编写发送和接收数据的代码
		//AfxMessageBox(_T("ok"));


			//AfxMessageBox(_T("接收"));
			ThreadStart();
		//TransferSocketToAnotherThread(clientSocket);
		//ThreadStart();
	}
	else
	{
		// 连接失败，处理错误
		MessageBox(_T("连接服务器失败"));
		clientSocket.Close();
		// 可以通过调用GetLastError()获取错误码，然后根据需要进行处理
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CarCommu::OnBnClickedButton3()
{


	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	USES_CONVERSION;
	//函数T2A和W2A均支持ATL和MFC中的字符
	char* send = T2A(m_port);
	clientSocket.Send(send,strlen(send));
	//m_CsendBuf.SetWindowTextW(_T(""));
}

void CarCommu::listInit(char* port)
{
	// TODO: 在此处添加实现代码.
	for (auto it = m_clientList.begin(); it != m_clientList.end(); ++it) {
		CConnSocket* pClientSocket = *it;

		// Assuming CConnSocket has member functions GetPort() and GetIPAddress()
		int port = pClientSocket->m_port;
		CString ipAddress = pClientSocket->m_ip; // Assuming GetIPAddress() returns a std::string
		CString porte;
		porte.Format(_T("%d"), port);
		// Insert the information into the list control
		int nIndex = m_listCtrl.GetItemCount();
		m_listCtrl.SetItemText(nIndex, 0, ipAddress); // Assuming column 0 is for IP address
		m_listCtrl.SetItemText(nIndex, 1, porte);
	}
}


void CarCommu::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	   // 打开 CSV 文件
	m_listCtrl.DeleteAllItems();
	CStringA filePath = "D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\excel\\交流端口号.csv";
	std::ifstream file(filePath); // 使用窄字符版本的文件输入流
	if (!file.is_open())
	{
		AfxMessageBox(_T("Failed to open file!"));
		return;
	}

	// 逐行读取 CSV 文件内容，并将其添加到 List Control 中
	bool isFirstLine = true; // 添加一个标志以确定当前是否是第一行
	std::string line;
	while (std::getline(file, line))
	{
		// 如果是第一行，则跳过
		if (isFirstLine)
		{
			isFirstLine = false; // Set the flag to false after processing the first line
			continue; // Skip processing the first line
		}
		// 使用std::stringstream按照逗号分割每一行的数据
		std::stringstream ss(line);
		std::string item;
		int columnIndex = 0;

		// 插入新的一行
		int rowIndex = m_listCtrl.GetItemCount();
		m_listCtrl.InsertItem(rowIndex, _T(""));

		// 逐个读取每个字段，并插入到对应的列中
		while (std::getline(ss, item, ','))
		{
			// 将std::string转换为CString
			CString str(item.c_str());

			// 插入到对应的列
			m_listCtrl.SetItemText(rowIndex, columnIndex, str);

			columnIndex++;
		}
	}
}

void CarCommu::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	USES_CONVERSION;
	//函数T2A和W2A均支持ATL和MFC中的字符
	char* send = T2A(m_send);
	int flag = clientSocket.Send(send, strlen(send));
	if (!flag)
	{
		AfxMessageBox(_T("发送失败"));
	}
	m_sender.SetWindowTextW(_T(""));
}

CConnSocket& CarCommu::quote(CConnSocket& Con)
{
	// TODO: 在此处添加实现代码.
	
	return Con;
}

void CarCommu::OnBnClickedButton5()
{
	
	
}

DWORD WINAPI process(LPVOID pParam)
{
	
	/*CString ip = _T("127.0.0.1");

	if (p_Mainprocess == NULL)
	{
		//TerminateThread(p_Mainprocess->handle_Thread, 0);
		return 0;
	}

	// Assuming m_port1 is correctly set to 8888
	UINT port = 8888;

	BOOL ret = p_Mainprocess->m_connSocket1.Create();
	if (ret)
	{
		ret = p_Mainprocess->m_connSocket1.Connect(ip, port);

		if (ret)
		{
			AfxMessageBox(_T("连接成功"));
			// Connection successful
			// m_connBtn.EnableWindow(FALSE);
			// m_disConnBtn.EnableWindow(TRUE);
			// m_sendBtn.EnableWindow(TRUE);
		}
		else
		{
			AfxMessageBox(_T("Failed to connect to the server. Please check the server availability and port."));
			p_Mainprocess->m_connSocket1.Close();
		}
	}
	else
	{
		AfxMessageBox(_T("Failed to create a socket."));
	}*/CarCommu* p_Mainprocess = (CarCommu*)pParam;
	CString msg;

	while (true)
	{
		int nLength = p_Mainprocess->m_rcver.GetWindowTextLengthW();

		// 将光标移动到文本末尾
		p_Mainprocess->m_rcver.SetSel(nLength, nLength);
		// 将新文本追加到编辑框中，并换行
		if (p_Mainprocess->message->messager != msg)
		{
			p_Mainprocess->m_rcver.ReplaceSel(p_Mainprocess->message->messager);
			p_Mainprocess->m_rcver.ReplaceSel(_T("\r\n"));
		}
		p_Mainprocess->message->messager = msg;
		/*//AfxMessageBox(_T("start"));
		
		//AfxMessageBox(p_Mainprocess->message->messager);

		p_Mainprocess->m_rcver.SetWindowTextW(p_Mainprocess->message->messager);
		p_Mainprocess->m_rcver.SetWindowTextW(_T("\r\n"));*/
	}

}
void CarCommu::ThreadStart()
{
	// TODO: 在此处添加实现代码.
	handle_Thread = CreateThread(NULL, 0, process, this, 0, 0);
	if (handle_Thread == NULL)
		MessageBox(_T("创建线程失败"));
	else
	{
		//m_ButtonStartTh.EnableWindow(0);
		//m_ButtonstopTh.EnableWindow(1);
		//MessageBox(_T("开始采集"));
	}
}

void CarCommu::AddEdit(CString msg)
{
	// TODO: 在此处添加实现代码.
	//MessageBox(msg);
	//m_rcver.SetWindowText(msg);
	m_rcv = msg;
	MessageBox(m_rcv);
	m_r = msg;
	//m_rc.SetWindowTextW(m_rcv);
}


void CarCommu::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	TerminateThread(handle_Thread, 0);
	CDialog::OnOK();
}


void CarCommu::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
		// Check if data is empty
	ThreadStart2();
}





void CarCommu::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 0:
	{
		// Check if data is empty
		if (p == NULL)
		{
			AfxMessageBox(_T("空"));
			break;
		}
		if (p->m_Data.empty())
		{
			AfxMessageBox(_T("数据为空"));
			return; // Stop further processing
		}

		// Prepare a buffer for storing the data to send
		constexpr size_t BUFFER_SIZE = 512; // Adjust buffer size as needed
		char sendBuffer[BUFFER_SIZE];

		// Iterate over the data and prepare the message to send
		for (const auto& data : p->m_Data)
		{
			// Determine the prefix based on sensor type
			const char* prefix = "";
			if (data.Sensor == "毫米波雷达")
				prefix = "速度:";
			else if (data.Sensor == "激光雷达")
				prefix = "车距:";
			else
				prefix = "行人:";

			// Build the message to send
			int written = snprintf(sendBuffer, BUFFER_SIZE, "%s%s%s", prefix, data.dData.c_str(), data.unit.c_str());
			if (written < 0 || written >= BUFFER_SIZE)
			{
				// Handle error: message truncated or some other error
				// You may log an error message or take appropriate action
				// For simplicity, we just skip sending this message
				continue;
			}

			// Send the message
			int bytesSent = clientSocket.Send(sendBuffer, written);
			if (bytesSent == SOCKET_ERROR)
			{
				// Handle error: failed to send data
				// You may log an error message or take appropriate action
				// For simplicity, we just skip sending this message
				continue;
			}
		}
		break;
	}
	}

	// Call the parent class handler
	__super::OnTimer(nIDEvent);
}



DWORD WINAPI process3(LPVOID pParam)
{
	CarCommu* p_Mainprocess = (CarCommu*)pParam;

	std::ifstream file("D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\工作簿1.csv", std::ios::in);
	if (file.is_open()) {
		std::string line;
		bool isFirstLine = true; // 添加一个标志以确定当前是否是第一行
		while (getline(file, line)) {
			// 如果是第一行，则跳过
			if (isFirstLine) {
				isFirstLine = false;
				continue;
			}

			// 使用stringstream按照逗号分割每一行的数据
			std::stringstream ss(line);
			std::string item;
			std::vector<std::string> columns;

			// 逐个读取每个字段
			int colNum = 1; // 记录当前所在列数
			std::string rowData; // 用于存储同一行的第3、5、6列数据
			while (getline(ss, item, ',')) {
				// 如果是第3、5、6列，则将数据添加到rowData中
				if (colNum == 3 || colNum == 5 || colNum == 6) {
					rowData += item;

					// 如果不是最后一列，添加冒号分隔符
					if (colNum < 6) {
						rowData += ':';
					}
				}
				colNum++;
			}

			// 发送整行数据给客户端
			send(p_Mainprocess->clientSocket, rowData.c_str(), rowData.length(), 0);
			Sleep(2000);
		}

		file.close();
	}
	return 0;
}
void CarCommu::ThreadStart2()
{
	// TODO: 在此处添加实现代码.
	handle_Thread2 = CreateThread(NULL, 0, process3, this, 0, 0);
	if (handle_Thread2 == NULL)
	{
		MessageBox(_T("创建线程2失败"));
	}
	else
	{
		MessageBox(_T("线程2已开始"));
	}
}


void CarCommu::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	TerminateThread(handle_Thread2, 0);
}
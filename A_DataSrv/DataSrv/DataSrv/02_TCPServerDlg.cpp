
// 02_TCPServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "02_TCPServer.h"
#include "02_TCPServerDlg.h"
#include "afxdialogex.h"
#include "ConnSocket.h"
#include "ServerSocket.h"
#include "MyServerSocket.h"
#include<list>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy02_TCPServerDlg �Ի���



CMy02_TCPServerDlg::CMy02_TCPServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY02_TCPSERVER_DIALOG, pParent)
	, m_port(0), m_serverSocket(this)
	, m_sendBuf(_T(""))
	, m_sendMes(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy02_TCPServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_port);
	DDX_Control(pDX, IDC_BUTTON1, m_startBtn);
	DDX_Control(pDX, IDC_BUTTON2, m_stopBtn);
	DDX_Control(pDX, IDC_BUTTON3, m_clearBtn);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
	DDX_Text(pDX, IDC_EDIT2, m_sendBuf);
	DDX_Control(pDX, IDC_BUTTON4, m_sendBtn);
	DDX_Control(pDX, IDC_EDIT2, str);
	DDX_Text(pDX, IDC_EDIT3, m_sendMes);
	DDX_Control(pDX, IDC_LIST2, m_listCtrl1);
}

BEGIN_MESSAGE_MAP(CMy02_TCPServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CMy02_TCPServerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy02_TCPServerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy02_TCPServerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy02_TCPServerDlg::OnBnClickedButton4)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMy02_TCPServerDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON5, &CMy02_TCPServerDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CMy02_TCPServerDlg ��Ϣ�������

BOOL CMy02_TCPServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_port = 8888;// �������˿�
	m_port1 = 88111;// �������˿�
	m_stopBtn.EnableWindow(FALSE);
	UpdateData(FALSE);

	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_listCtrl1.SetExtendedStyle(m_listCtrl1.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	CString col[4] = { _T("ʱ��"),_T("IP"),_T("�˿ں�"),_T("״̬")};
	RECT r;	//rect���������洢һ�����ο�����Ͻ����ꡢ��Ⱥ͸߶ȡ�
	m_listCtrl1.GetClientRect(&r);	//��ʾ���ο���ú���Ҫ��ȡ��ַ����
	for (int i = 0; i < 4; i++)
	{
		m_listCtrl1.InsertColumn(i, col[i], LVCFMT_CENTER, (r.right - r.left) / 4);
	}

	
	m_listCtrl.SetBkColor(RGB(199, 237, 233));	//�����б�򱳾���ɫ
	m_listCtrl.SetTextColor(RGB(18, 53, 85));	//������ɫ
	m_listCtrl.SetTextBkColor(RGB(175, 215, 237));//���ֱ���ɫ

	m_startBtn.EnableWindow(TRUE);
	m_stopBtn.EnableWindow(FALSE);	

	if (pServerSocket->Create(8811, SOCK_STREAM)) {
		if (pServerSocket->Listen()) {
			CString LinkMsg;
			SYSTEMTIME t;
			GetLocalTime(&t);
			LinkMsg.Format(_T("[%d:%d:%d] ����ͨ�ŷ���������"), t.wHour, t.wMinute, t.wSecond);
			AddMsg(LinkMsg);
			//AfxMessageBox(_T("Server started successfully. Listening on port 8811."));
			//m_port = pServerSocket->m_port;
		}
		else {
			//AfxMessageBox(_T("Failed to listen on port 8811."));
		}
	}
	else {
		//AfxMessageBox(_T("Failed to create server socket."));

	}
	
	//draw();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy02_TCPServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy02_TCPServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// �����Ϣ�б�
void CMy02_TCPServerDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_listCtrl.DeleteAllItems();
	//m_serverSocket.SendMsg(_T("aaaa"));
}

// ����������
void CMy02_TCPServerDlg::OnBnClickedButton1()
{
	//AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);

	// Create the server socket
	
	BOOL ret = m_serverSocket.Create(m_port, SOCK_STREAM);
	if (ret)
	{
		
		ret = m_serverSocket.Listen();
		if (ret)
		{
			//m_serverSocket.a
			m_startBtn.EnableWindow(FALSE);
			m_stopBtn.EnableWindow(TRUE);
			CString LinkMsg;
			SYSTEMTIME t;
			GetLocalTime(&t);
			LinkMsg.Format(_T("[%d:%d:%d] ������������"), t.wHour, t.wMinute, t.wSecond);
			AddMsg(LinkMsg);
			return;
		}
		else
		{
			MessageBox(_T("�����׽��ּ���ʧ��"));
		}
	}
	else 
	{
		MessageBox(_T("���������׽���ʧ��"));
	}
	
	
	ClientInsert();
}

// ֹͣ������
void CMy02_TCPServerDlg::OnBnClickedButton2()
{
	m_serverSocket.CloseAllConn();
	m_startBtn.EnableWindow(TRUE);
	m_stopBtn.EnableWindow(FALSE);
}

void CMy02_TCPServerDlg::AddMsg(CString msg)
{
	m_listCtrl.InsertItem(0, msg);
}

void CMy02_TCPServerDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString msg;
	GetDlgItemText(IDC_EDIT2, msg);
	m_serverSocket.Sender(msg);
	//AfxMessageBox(msg);
}

void CMy02_TCPServerDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void CMy02_TCPServerDlg::ClientInsert()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	for (auto it = Insert->m_clientList.begin(); it != Insert->m_clientList.end(); ++it) {
		CConnSocket* pClientSocket = *it;

		// Assuming CConnSocket has member functions GetPort() and GetIPAddress()
		int port = pClientSocket->m_port;
		CString ipAddress = pClientSocket->m_ip; // Assuming GetIPAddress() returns a std::string
		CString porte;
		porte.Format(_T("%d"), port);
		// Insert the information into the list control
		int nIndex = m_listCtrl.GetItemCount();
		m_listCtrl.SetItemText(nIndex,0, ipAddress); // Assuming column 0 is for IP address
		m_listCtrl.SetItemText(nIndex, 1, porte); // Column 1 for port
		// Assuming column 2 is for time, you might need to replace "time" with the appropriate member of CConnSocket
		//m_listCtrl.SetItemText(nIndex, 2, pClientSocket->GetTime().c_str());
	}
}

void CMy02_TCPServerDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	


}


void CMy02_TCPServerDlg::draw()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	CImage image;
	image.Load(TEXT("E:\\E-download\\fatigue_detecting-master\\fatigue_detecting-master\\images\\4eea0fb74d226.png"));  //����ͼƬ
	// �����ؼ�����Ϊ��ͼ��ͬһ�ߴ�  
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC);//��þ�������ǿؼ���id
	pStatic->SetWindowPos(NULL,
		100,
		100,
		image.GetWidth(),
		image.GetHeight(),
		SWP_NOMOVE);
	pStatic->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
	pStatic->SetBitmap((HBITMAP)image.Detach());
}

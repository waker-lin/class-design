
// 02_TCPClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <Windows.h>
#include <WinSock2.h>
#include <winerror.h>
#include "02_TCPClient.h"
#include "02_TCPClientDlg.h"
#include "afxdialogex.h"
#include "ConnSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy02_TCPClientDlg �Ի���



CMy02_TCPClientDlg::CMy02_TCPClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY02_TCPCLIENT_DIALOG, pParent)
	, m_port(0)
	, m_sendBuf(_T(""))
	, m_connSocket(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy02_TCPClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_IPADDRESS1, m_serverIp);
	DDX_Text(pDX, IDC_EDIT1, m_port);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ip);
	DDX_Control(pDX, IDC_BUTTON1, m_connBtn);
	DDX_Control(pDX, IDC_BUTTON2, m_disConnBtn);
	DDX_Text(pDX, IDC_EDIT3, m_sendBuf);
	DDX_Control(pDX, IDC_BUTTON3, m_sendBtn);
	DDX_Control(pDX, IDC_BUTTON4, m_clearBtn);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CMy02_TCPClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy02_TCPClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy02_TCPClientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy02_TCPClientDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy02_TCPClientDlg::OnBnClickedButton4)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMy02_TCPClientDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CMy02_TCPClientDlg ��Ϣ�������

BOOL CMy02_TCPClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_ip.SetAddress(127, 0, 0, 1);
	m_port = 8888;
	UpdateData(FALSE);
	m_disConnBtn.EnableWindow(FALSE);
	m_sendBtn.EnableWindow(FALSE);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy02_TCPClientDlg::OnPaint()
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
HCURSOR CMy02_TCPClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ����TCP������
void CMy02_TCPClientDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	BYTE a, b, c, d;
	m_ip.GetAddress(a, b, c, d);
	CString ip;
	ip.Format(_T("%d.%d.%d.%d"), a, b, c, d);
	BOOL ret = m_connSocket.Create();
	if (ret)
	{
		ret = m_connSocket.Connect(ip, m_port);
		if (ret)
		{
			m_connBtn.EnableWindow(FALSE);
			m_disConnBtn.EnableWindow(TRUE);
			m_sendBtn.EnableWindow(TRUE);
		}
		else
		{
			MessageBox(_T("���ӷ�����ʧ��"));
			m_connSocket.Close();
		}
	}
	else
	{
		MessageBox(_T("�����׽���ʧ��"));
	}
	
}

// �Ͽ�����
void CMy02_TCPClientDlg::OnBnClickedButton2()
{
	m_connBtn.EnableWindow(TRUE);
	m_disConnBtn.EnableWindow(FALSE);
	m_sendBtn.EnableWindow(FALSE);

	m_connSocket.Close();
}

// �������������Ϣ
void CMy02_TCPClientDlg::OnBnClickedButton3()
{
	UpdateData(TRUE);
	USES_CONVERSION;
	//����T2A��W2A��֧��ATL��MFC�е��ַ�
	char * send = T2A(m_sendBuf);
	m_connSocket.Send(send, strlen(send));
}

// �����Ϣ�б�
void CMy02_TCPClientDlg::OnBnClickedButton4()
{
	m_listCtrl.DeleteAllItems();
}

void CMy02_TCPClientDlg::AddMsg(CString msg)
{
	m_listCtrl.InsertItem(0, msg);
}

void CMy02_TCPClientDlg::MyEnableBtn()
{
	m_connBtn.EnableWindow(TRUE);
	m_disConnBtn.EnableWindow(FALSE);
}


void CMy02_TCPClientDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

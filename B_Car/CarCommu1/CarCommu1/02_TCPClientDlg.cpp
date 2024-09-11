
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
#include "locale.h"
#include "Winuser.h"
#include "string.h"
#include "DataSearch.h"
#include "CarCommu.h"
#include <mutex>
#include"plot.h"
#include<fstream>  // �ļ���


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy02_TCPClientDlg �Ի���
//enum { IDD = IDD_ * **_DIALOG }


CMy02_TCPClientDlg::CMy02_TCPClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY02_TCPCLIENT_DIALOG, pParent)
	, m_port(0)
	, m_sendBuf(_T(""))
	, m_connSocket(this)
	, SpeedShow(_T(""))
	, DistanceShow(_T(""))
	, PersonShow(_T(""))
	, m_powers(_T(""))
	, m_power(_T(""))
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
	DDX_Control(pDX, IDC_LIST2, m_listCtrl1);
	DDX_Control(pDX, IDC_COMBO2, botelv);
	DDX_Control(pDX, IDC_COMBO1, chuankouhao);
	DDX_Control(pDX, IDC_MSCOMM1, communications1);
	DDX_Control(pDX, IDC_CHECK1, xuanze);
	DDX_Text(pDX, IDC_EDIT2, SpeedShow);
	DDX_Control(pDX, IDC_COMBO3, SensorType);
	DDX_Control(pDX, IDC_EDIT2, CSpeedShow);
	DDX_Control(pDX, IDC_BUTTON5, m_ButtonStartTh);
	DDX_Control(pDX, IDC_BUTTON8, m_ButtonstopTh);
	//DDX_Control(pDX, IDC_MSCOMM3, communications2);
	DDX_Text(pDX, IDC_EDIT4, DistanceShow);
	DDX_Text(pDX, IDC_EDIT5, PersonShow);
	DDX_Control(pDX, IDC_EDIT6, CSpeedShower);
	DDX_Control(pDX, IDC_EDIT4, DistanceShower);
	DDX_Control(pDX, IDC_EDIT5, PersonShower);
	DDX_Control(pDX, IDC_EDIT7, DistanceShowers);
	DDX_Control(pDX, IDC_EDIT8, PersonShowers);
	DDX_Control(pDX, IDC_ANIMATE1, m_icon_1);
	DDX_Control(pDX, IDC_BUTTON7, m_Buttoncon);
	DDX_Control(pDX, IDC_BUTTON6, m_Buttonpause);
	DDX_Control(pDX, IDC_EDIT3, m_CsendBuf);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_STATIC1, power);
	DDX_Text(pDX, IDC_STATIC2, m_powers);
	DDX_Text(pDX, IDC_STATIC1, m_power);
	DDX_Control(pDX, IDC_BUTTON11, m_SendFile);
	DDX_Control(pDX, IDC_CHECK2, SetAll);
}

BEGIN_MESSAGE_MAP(CMy02_TCPClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy02_TCPClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy02_TCPClientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy02_TCPClientDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy02_TCPClientDlg::OnBnClickedButton4)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMy02_TCPClientDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON5, &CMy02_TCPClientDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_CHECK1, &CMy02_TCPClientDlg::OnBnClickedCheck1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CMy02_TCPClientDlg::OnLvnItemchangedList2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMy02_TCPClientDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON6, &CMy02_TCPClientDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMy02_TCPClientDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMy02_TCPClientDlg::OnBnClickedButton8)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON12, &CMy02_TCPClientDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON10, &CMy02_TCPClientDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON9, &CMy02_TCPClientDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON11, &CMy02_TCPClientDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON15, &CMy02_TCPClientDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON14, &CMy02_TCPClientDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON16, &CMy02_TCPClientDlg::OnBnClickedButton16)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT3, &CMy02_TCPClientDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON13, &CMy02_TCPClientDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_CHECK2, &CMy02_TCPClientDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()


// CMy02_TCPClientDlg ��Ϣ�������

BOOL CMy02_TCPClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	m_ip.SetAddress(127, 0, 0, 1);
	m_port = 8888;
	UpdateData(FALSE);
	m_disConnBtn.EnableWindow(FALSE);
	m_sendBtn.EnableWindow(FALSE);

	m_listCtrl1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT);
	//��չlist control�ĸ�ʽ
	//���������ߣ���ͷ������ק������ѡ�����л�������
	CString col[6] = { _T("���"),_T("�û���"),_T("ʱ��"),_T("�ٶ�"),_T("����"),_T("������") };
	RECT r;	//rect���������洢һ�����ο�����Ͻ����ꡢ��Ⱥ͸߶ȡ�
	m_listCtrl1.GetClientRect(&r);	//��ʾ���ο���ú���Ҫ��ȡ��ַ����
	for (int i = 0; i < 6; i++)
	{
		m_listCtrl1.InsertColumn(i, col[i], LVCFMT_CENTER, (r.right - r.left) / 6);
	}

	m_listCtrl1.SetBkColor(RGB(199, 237, 233));	//�����б�򱳾���ɫ
	m_listCtrl1.SetTextColor(RGB(18, 53, 85));	//������ɫ
	m_listCtrl1.SetTextBkColor(RGB(175, 215, 237));//���ֱ���ɫ
	m_listCtrl.SetBkColor(RGB(199, 237, 233));	//�����б�򱳾���ɫ
	m_listCtrl.SetTextColor(RGB(18, 53, 85));	//������ɫ
	m_listCtrl.SetTextBkColor(RGB(175, 215, 237));//���ֱ���ɫ
	//InitStatus();	//��ʼ��״̬��


	//m_icon_2.SetIcon(m_hIconRed);//��ʼ��Ϊ��ɫ
	//���ڳ�ʼ��
	/*chuankouhao.AddString(_T("COM1"));
	chuankouhao.AddString(_T("COM2"));
	chuankouhao.AddString(_T("COM3"));
	chuankouhao.AddString(_T("COM4"));
	chuankouhao.AddString(_T("COM5"));
	chuankouhao.AddString(_T("COM6"));*/

	botelv.AddString(_T("4800"));
	botelv.AddString(_T("9600"));
	botelv.AddString(_T("14400"));

	chuankouhao.AddString(_T("���ײ��״�"));
	chuankouhao.AddString(_T("�����״�"));
	chuankouhao.AddString(_T("���˼����"));
	
	if (!communications1.get_PortOpen())
	{
		xuanze.EnableWindow(0);

		m_Buttoncon.EnableWindow(0);
		m_Buttonpause.EnableWindow(0);
		m_ButtonstopTh.EnableWindow(0);
	}

	CProgressCtrl* pProg = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	pProg->SetRange(0, 100);
	pProg->SetPos(100);
	//m_power = "100%";
	SetDlgItemText(IDC_STATIC2,_T("100%"));
	SetTimer(3, 90000, NULL);

	m_SendFile.EnableWindow(false);
	SetAll.EnableWindow(false);
	//draw();
	//m_Buttoncon.EnableWindow(0);

	/**/
	

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
			m_SendFile.EnableWindow(TRUE);
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
	SYSTEMTIME t;
	GetLocalTime(&t);
	CString msg;
	msg.Format(_T("[%d:%d:%d]: �Ͽ������������!"), t.wHour, t.wMinute, t.wSecond);
	AddMsg(msg);
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
	m_CsendBuf.SetWindowTextW(_T(""));
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

void CMy02_TCPClientDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	int m_McsPortNum = 0; //���崮�ں�
	CString bote, jiaoyan, tingzhi, shuju; //�����ʡ�У��λ��ֹͣλ������λ
	CString PortStr; //�����ַ���

	
	switch (chuankouhao.GetCurSel())  //��ȡ�ⲿ�˿ں�
	{
	case 0:
		m_McsPortNum = 4;
		break;
	case 1:
		m_McsPortNum = 6;
		break;
	case 2:
		m_McsPortNum = 8;
		break;
	default:
		break;
	}

	jiaoyan = _T("e");   //��У��λ��Э��ֻ��������д

	GetDlgItemText(IDC_COMBO3, bote);  //��ȡ������
	//GetDlgItemText(IDC_COMBO5, tingzhi);   //��ȡֹͣλ
	//GetDlgItemText(IDC_COMBO6, shuju);   //��ȡ����λ

	PortStr = bote + _T(",") + jiaoyan + _T(",") + shuju + _T(",") + tingzhi;//���ַ����ϳ�


	communications1.put_InBufferSize(2048);  //���ý��ջ�����
	communications1.put_OutBufferSize(2048);  //���÷��ͻ�����
	communications1.put_Settings(PortStr); //���ó�ʼ�� ������+У��λ+����λ+ֹͣλ
	communications1.put_InputMode(1);  //�Զ����Ʒ�ʽ��д

	if (communications1.get_PortOpen())  //���ص�ǰ�Ƿ��д��ڴ򿪡�true���д��ڴ�
	{
		communications1.put_PortOpen(FALSE);   //����д��ڴ򿪣������ô��ڹر�
	}
	communications1.put_CommPort(m_McsPortNum);  //����������֤û�д��ڴ򿪺�������Ҫ�򿪵Ĵ��ںţ�Ϊ���ڴ���׼��

	if (!communications1.get_PortOpen())   //���û�д��ڴ򿪣�û�д��ڴ򿪷���FALSE���������´򿪴���
	{
		communications1.put_PortOpen(TRUE);  //�򿪴���
	}
	else
	{
		MessageBox(_T("û�д򿪴���"), _T("��Ϣ��ʾ��"), MB_ICONERROR | MB_OKCANCEL);
	}

	communications1.put_RThreshold(2);  //������ֵ�������ջ����������ﵽ��ֵʱ������onComm�¼�����������
	communications1.put_SThreshold(2);  //������ֵ�������ͻ����������ﵽ��ֵʱ�����з���
	communications1.put_InputLen(0); //����0����Ϊ���ջ������е�����ȫ����ȡ
	communications1.get_Input();//��ȡ������������
	if (communications1.get_PortOpen())
	{
		CString Connect;
		Connect.Format(_T("12"));
		m_ButtonStartTh.EnableWindow(0);
		m_ButtonstopTh.EnableWindow(1);
		xuanze.EnableWindow(1);
		communications1.put_Output(COleVariant(Connect));
		m_Buttoncon.EnableWindow(0);
		m_Buttonpause.EnableWindow(1);
		m_ButtonstopTh.EnableWindow(1);
		SetAll.EnableWindow(1);
	}
	//ThreadStart();
}

void CMy02_TCPClientDlg::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������int connect = 12;
	CString SnedBegin, SnedStop,Connect, pause, conti, discon;
	SnedBegin.Format(_T("10"));
	SnedStop.Format(_T("11"));
	
	/*switch (chuankouhao.GetCurSel())  //��ȡ�ⲿ�˿ں�
	{
	case 0:
		SnedMessage.Format(_T("10"));
		break;
	case 1:
		SnedMessage.Format(_T("11"));
		break;
	case 2:
		SnedMessage.Format(_T("12"));
		break;
	default:
		break;
	}*/
	if (xuanze.GetCheck() == TRUE)   //���������ѡ������Զ����ͱ�����ֵ
	{

		if (communications1.get_PortOpen() == TRUE)  //�˿ڴ�״̬
		{
			communications1.put_Output(COleVariant(SnedBegin));
		}
	}
	else
	{
		if (communications1.get_PortOpen() == TRUE)  //�˿ڴ�״̬
		{
			communications1.put_Output(COleVariant(SnedStop));
		}
		if (communications1.get_PortOpen() == TRUE)
		{
			//xuanze.EnableWindow(FALSE);

		}
		//else
	}
}


void CMy02_TCPClientDlg::OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

BEGIN_EVENTSINK_MAP(CMy02_TCPClientDlg, CDialogEx)
	ON_EVENT(CMy02_TCPClientDlg, IDC_MSCOMM1, 1, CMy02_TCPClientDlg::OnOncommMscomm1, VTS_NONE)
	//ON_EVENT(CMy02_TCPClientDlg, IDC_MSCOMM3, 1, CMy02_TCPClientDlg::OnOncommMscomm2, VTS_NONE)
END_EVENTSINK_MAP()

void CMy02_TCPClientDlg::OnOncommMscomm1()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	setlocale(LC_CTYPE, "chs");
	SYSTEMTIME t;
	GetLocalTime(&t);
	CString Time, msgs, unit[3],test;

	VARIANT        m_Variant_Rec; //�������Ͷ���
	COleSafeArray  m_SafeArray_Rec;  //���ڴ����������ͺ�ά���������
	LONG           m_DataLenth, nCount;  //������յĳ��Ⱥͼ�����
	const int      m_RecByteLenth = 2048;
	BYTE           m_RecDataByte[m_RecByteLenth];  //������ջ�����
	CString        m_TemDataStr;  //�����ַ���������ת������ʾ
	if (communications1.get_CommEvent() == 2)   //�����¼�ֵΪ2����ʾ���ջ������ַ�
	{
		m_Variant_Rec = communications1.get_Input();  //��ȡ����������
		m_SafeArray_Rec = m_Variant_Rec;   //�ѻ��������ݷŵ�SafeArray���ݽṹ��

		m_DataLenth = m_SafeArray_Rec.GetOneDimSize(); //��ȡһά���ݵĳ���
		for (nCount = 0; nCount < m_DataLenth; nCount++)
			m_SafeArray_Rec.GetElement(&nCount, m_RecDataByte + nCount); //����SafeArray�е����ݣ��ò�ͬncoutλ�ý���ָ���ƫ������ȡ����Ӧλ������
		CSpeedShow.SetWindowText(_T(""));
		pData = new CMy02_TCPClientDlg;
		for (nCount = 0; nCount < m_DataLenth; nCount++)
		{
			BYTE m_Buff = *(char*)(m_RecDataByte + nCount);  //�����鿪ͷ����ncountƫ��������ȡ��Ӧλ�õ�����
			m_TemDataStr.Format(_T("%C"), m_Buff); //�����BYTE����ת��Ϊchar
			//test += m_TemDataStr;
			if (chuankouhao.GetCurSel() == 0)//&&(20<=(_ttoi(test)))
			{
				SpeedShow += m_TemDataStr;  //��char���뵽����ʾ���ַ�����
				//CSpeedShow.SetWindowTextW(m_TemDataStr);
				Time.Format(_T("[%d:%d:%d] :"), t.wHour, t.wMinute, t.wSecond);
				unit[chuankouhao.GetCurSel()].Format(_T("km/h"));
				msgs = Time + SpeedShow+unit[0];
				/*pFile->Sensor = "�ٶȴ�����";
				pFile->dData = CT2A(SpeedShow.GetString());
				pFile->time = CT2A(Time.GetString());
				pData->m_Data.push_back(*pFile);
				test.Format(_T("%s"), pFile->time);*/
				if (20 <= (_ttoi(SpeedShow)))
				{
					if (35 <= _ttoi(SpeedShow))
					{
						CString msgss;
						msgss.Format(_T("[%d:%d:%d] 127.0.0.1:8888 ��ʻԱ��ע�⳵��:%s km/h"),t.wHour,t.wMinute,t.wSecond, SpeedShow);
						AddMsg(msgss);
					}
					Time.Format(_T("%d:%d:%d"), t.wHour, t.wMinute, t.wSecond);
					pFile = new FileSave;
					pFile->Sensor = "���ײ��״�";
					pFile->dData = CT2A(SpeedShow.GetString());
					pFile->time = CT2A(Time.GetString());
					pFile->unit = CT2A(unit[chuankouhao.GetCurSel()].GetString());
					m_Data.push_back(*pFile);
					SendSrv.push_back(*pFile);
				}
				//AfxMessageBox(pFile->time);

				//CSpeedShower.SetWindowText(Time);
				//CSpeedShower.SetWindowText(Time+SpeedShow);
				CSpeedShower.SetWindowText(msgs);
				CSpeedShower.LineScroll(CSpeedShower.GetLineCount() - 1, 0);
			}
			//CSpeedShower.SetSel(-1, -1); //�Զ�����������m_Edit��EDIT����������EDIT���ƶ���
			//CSpeedShower.ReplaceSel(SpeedShow + "\r\n"); //�Զ�����
			if (chuankouhao.GetCurSel() == 1)//&&(_wtof(test))
			{
				DistanceShow += m_TemDataStr;  //��char���뵽����ʾ���ַ�����
				Time.Format(_T("[%d:%d:%d] :"), t.wHour, t.wMinute, t.wSecond);
				unit[chuankouhao.GetCurSel()].Format(_T("m"));
				msgs = Time + DistanceShow + unit[chuankouhao.GetCurSel()];
				DistanceShowers.SetWindowText(msgs);
				DistanceShowers.LineScroll(DistanceShowers.GetLineCount() - 1, 0);

				if (DistanceShow.GetLength() >4)
				{
					if(_ttoi(DistanceShow)<3)
					{
						CString msgss;
						msgss.Format(_T("[%d:%d:%d] 127.0.0.1:8888 ��ʻԱ��ע�⳵��:%s m"), t.wHour, t.wMinute, t.wSecond, DistanceShow);
						AddMsg(msgss);

					}
					Time.Format(_T("%d:%d:%d"), t.wHour, t.wMinute, t.wSecond);
					pFile = new FileSave;
					pFile->Sensor = "�����״�";
					pFile->dData = CT2A(DistanceShow.GetString());
					pFile->time = CT2A(Time.GetString());
					pFile->unit = CT2A(unit[chuankouhao.GetCurSel()].GetString());
					m_Data.push_back(*pFile);
					SendSrv.push_back(*pFile);
				}
			}
			if (chuankouhao.GetCurSel() == 2)//&& ( 0<= _ttoi(test)<=8)
			{
				PersonShow += m_TemDataStr;  //��char���뵽����ʾ���ַ�����
				Time.Format(_T("[%d:%d:%d] :"), t.wHour, t.wMinute, t.wSecond);
				unit[chuankouhao.GetCurSel()].Format(_T("��"));
				msgs = Time + PersonShow + unit[chuankouhao.GetCurSel()];
				PersonShowers.SetWindowText(msgs);
				PersonShowers.LineScroll(PersonShowers.GetLineCount() - 1, 0);

				if (PersonShow!=_T(" "))
				{
					Time.Format(_T("%d:%d:%d"), t.wHour, t.wMinute, t.wSecond);
					pFile = new FileSave;
					pFile->Sensor = "���˼����";
					pFile->dData = CT2A(PersonShow.GetString());
					pFile->time = CT2A(Time.GetString());
					pFile->unit = CT2A(unit[chuankouhao.GetCurSel()].GetString());
					m_Data.push_back(*pFile);
					SendSrv.push_back(*pFile);
				}
			}
		}
		//AfxMessageBox(SpeedShow);
		//SpeedShow += _T("\r\n");
		SpeedShow = _T("");
		PersonShow = _T("");
		DistanceShow = _T("");
		if (m_Data.empty())
		{
		AfxMessageBox(_T("���ݺ�̨�洢ʧ��"));
		}

		UpdateData(FALSE);
	}

	communications1.put_InBufferCount(0);  //ȡ�����ݺ󣬽������ݵ�����
	communications1.put_OutBufferCount(0);
}





void CMy02_TCPClientDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

DWORD WINAPI process1(LPVOID pParam)
{
	/*CMy02_TCPClientDlg* p_Mainprocess = (CMy02_TCPClientDlg*)pParam;
	bool Is_Thread = false;
	setlocale(LC_CTYPE, "chs");
	SYSTEMTIME t;
	GetLocalTime(&t);
	CString Time, msgs, unit[3];

	VARIANT        m_Variant_Rec; //�������Ͷ���
	COleSafeArray  m_SafeArray_Rec;  //���ڴ����������ͺ�ά���������
	LONG           m_DataLenth, nCount;  //������յĳ��Ⱥͼ�����
	const int      m_RecByteLenth = 2048;
	BYTE           m_RecDataByte[m_RecByteLenth];  //������ջ�����
	CString        m_TemDataStr;  //�����ַ���������ת������ʾ
	while (true)
	{
		switch (p_Mainprocess->chuankouhao.GetCurSel())//���ʹ�����ִ�����
		{
		case 0:
		{
			while (!p_Mainprocess->communications1.get_CommEvent())
			{

			}
			if (p_Mainprocess->communications1.get_CommEvent())
			{
				p_Mainprocess->SpeedShow += m_TemDataStr;  //��char���뵽����ʾ���ַ�����
				//CSpeedShow.SetWindowTextW(m_TemDataStr);
				Time.Format(_T("[%d:%d:%d] :"), t.wHour, t.wMinute, t.wSecond);
				unit[p_Mainprocess->chuankouhao.GetCurSel()].Format(_T("km/h"));
				msgs = Time + p_Mainprocess->SpeedShow + unit[0];
				//CSpeedShower.SetWindowText(Time);
				//CSpeedShower.SetWindowText(Time+SpeedShow);
				p_Mainprocess->CSpeedShower.SetWindowText(msgs);
				p_Mainprocess->CSpeedShower.LineScroll(p_Mainprocess->CSpeedShower.GetLineCount() - 1, 0);
				p_Mainprocess->m_Data.push_back(_wtof(p_Mainprocess->SpeedShow));
			}
			//p_Mainprocess->communications1.put_PortOpen(FALSE);
			break;
		}
		case 1:
		{

			break;
		}
		case 2:

			break;
		}
	}*/
	return 0;
}





void CMy02_TCPClientDlg::ThreadPause()
{
	// TODO: �ڴ˴����ʵ�ִ���.
}


void CMy02_TCPClientDlg::OnBnClickedButton6()
{
	/*int ref = SuspendThread(handle_Thread);
	if (ref == -1)
		MessageBox(_T("��ͣʧ��"));
	else
	{

	}*/
	if (communications1.get_PortOpen())
	{
		CString pause;
		pause.Format(_T("13"));
		m_Buttoncon.EnableWindow(1);
		m_Buttonpause.EnableWindow(0);
		communications1.put_Output(COleVariant(pause));
	}
}


void CMy02_TCPClientDlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*int ref = ResumeThread(handle_Thread);
	if (ref == -1)
		MessageBox(_T("����ʧ��"));
	else
	{

	}*/
	if (communications1.get_PortOpen()&& m_Buttonpause)
	{
		CString conti;
		conti.Format(_T("14"));
		m_Buttoncon.EnableWindow(0);
		m_Buttonpause.EnableWindow(1);
		communications1.put_Output(COleVariant(conti));
	}
}


void CMy02_TCPClientDlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*TerminateThread(handle_Thread, 0);*/
	m_ButtonStartTh.EnableWindow(1);
	m_ButtonstopTh.EnableWindow(0);
	m_Buttoncon.EnableWindow(0);
	m_Buttonpause.EnableWindow(0);
	SetAll.EnableWindow(0);


	CString stop;
	stop.Format(_T("15"));
	communications1.put_Output(COleVariant(stop));
	communications1.put_PortOpen(FALSE);
	xuanze.EnableWindow(0);
	//MessageBox(_T("�����ѹر�"));
}

void CMy02_TCPClientDlg::OnOncommMscomm2()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	VARIANT        m_Variant_Rec; //�������Ͷ���
	COleSafeArray  m_SafeArray_Rec;  //���ڴ����������ͺ�ά���������
	LONG           m_DataLenth, nCount;  //������յĳ��Ⱥͼ�����
	const int      m_RecByteLenth = 2048;
	BYTE           m_RecDataByte[m_RecByteLenth];  //������ջ�����
	CString        m_TemDataStr;  //�����ַ���������ת������ʾ
	if (communications1.get_CommEvent() == 2)   //�����¼�ֵΪ2����ʾ���ջ������ַ�
	{
		m_Variant_Rec = communications1.get_Input();  //��ȡ����������
		m_SafeArray_Rec = m_Variant_Rec;   //�ѻ��������ݷŵ�SafeArray���ݽṹ��

		m_DataLenth = m_SafeArray_Rec.GetOneDimSize(); //��ȡһά���ݵĳ���
		for (nCount = 0; nCount < m_DataLenth; nCount++)
			m_SafeArray_Rec.GetElement(&nCount, m_RecDataByte + nCount); //����SafeArray�е����ݣ��ò�ͬncoutλ�ý���ָ���ƫ������ȡ����Ӧλ������
		CSpeedShow.SetWindowText(_T(""));

		for (nCount = 0; nCount < m_DataLenth; nCount++)
		{
			BYTE m_Buff = *(char*)(m_RecDataByte + nCount);  //�����鿪ͷ����ncountƫ��������ȡ��Ӧλ�õ�����
			m_TemDataStr.Format(_T("%C"), m_Buff); //�����BYTE����ת��Ϊchar
			SpeedShow += m_TemDataStr;  //��char���뵽����ʾ���ַ�����
		}
		//AfxMessageBox(SpeedShow);
		//SpeedShow += _T("\r\n");

		UpdateData(FALSE);
	}

	communications1.put_InBufferCount(0);  //ȡ�����ݺ󣬽������ݵ�����
	communications1.put_OutBufferCount(0);
}

void CMy02_TCPClientDlg::OnBnClickedButton12()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int rank = 1;
	CFileDialog* p_savefile = new CFileDialog(FALSE, L".csv", NULL, OFN_READONLY, L"CSV(*.csv)|*.csv");
	p_savefile->DoModal();
	string FilePath_Save = CT2A(p_savefile->GetPathName().GetString());
	delete p_savefile;
	char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));//������������
	if (FilePath_Save.empty()) { // ����ļ�·���Ƿ�Ϊ��
		// ����ļ�·��Ϊ�գ��������û�ȡ���˶Ի�����ʱ��Ӧ���˳�����
		MessageBox( L"�����ļ�ʧ�ܣ������ڱ���ʱ���ļ�", L"����", MB_OK | MB_ICONERROR);
		return ;
	}

	// ���ļ�����д��
	ofstream SaveFile(FilePath_Save, ios::out);
	if (!SaveFile) {
		MessageBox( L"�����ļ�ʧ�ܣ������ڱ���ʱ���ļ�", L"����", MB_OK | MB_ICONERROR);
		return ;
	}
	// д���ͷ
	SaveFile << "���" << "," << "�û�" << "," << "����������" << "," << "ʱ��" << "," << "����" <<"," << "��λ" << endl;

	CString msg;
	

	for (auto it = m_Data.begin(); it != m_Data.end(); it++) {
		// д��ÿ��userinfo���������
		SaveFile << rank << "," << it->user << "," << it->Sensor << "," << it->time << "," << it->dData << "," << it->unit;
		rank++;
		//for (int i = 0; i < 6; i++) {
			//SaveFile << "," << it->p_data[i];
		//}
		//a.Format(_T("%s"), );
		//AfxMessageBox(rank);vector<FileSave>::iterator
		//msg.Format(_T("%s"), (it->dData));
		//AfxMessageBox(msg);
		SaveFile << endl;
	}
	//a.Format(_T("%d"), rank);
	//MessageBox(a);
	// �ر��ļ�
	setlocale(LC_CTYPE, old_locale); //��ԭ������������� 
	free(old_locale);//��ԭ�����趨
	SaveFile.close();
	MessageBox( L"����ɹ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);

	poltData();


	return ;
}


void CMy02_TCPClientDlg::OnBnClickedButton10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//DataSearch a;
	//a.DoModal();
	CFileDialog openFileDialog(TRUE, L".csv", NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, L"CSV Files (*.csv)|*.csv||");
    if (openFileDialog.DoModal() == IDOK) {
        CString filePath = openFileDialog.GetPathName();

        // �����ļ����ݴ��ڲ���ʾ�ļ�����
		DataSearch fliecontent;
		fliecontent.fileContentWindow(filePath);
		fliecontent.DoModal();
    }
}


void CMy02_TCPClientDlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog fileDlg(TRUE, _T("csv"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("CSV Files (*.csv)|*.csv||"), NULL);
	if (fileDlg.DoModal() == IDOK) {
		{
			CString filePath = fileDlg.GetPathName();
			DataSearch a;
			a.DoModal();
		}

		// ������ʹ���ļ�·�����к��������������ȡCSV�ļ����ݵ�
	}
	else {
		// �û�ȡ�����ļ��Ի������

	}
}


void CMy02_TCPClientDlg::poltData()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	// ָ���̶����ļ�·��
	/**/
	SYSTEMTIME t;
	GetLocalTime(&t);
	CString fixedFilePath1 = L"D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\excel\\������1.csv";
	CString fixedFilePath2 = L"D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\excel\\������2.csv";
	CString fixedFilePath3 = L"D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\excel\\������3.csv";
	string FilePath_Save1 = CT2A(fixedFilePath1.GetString());
	string FilePath_Save2 = CT2A(fixedFilePath2.GetString());
	string FilePath_Save3 = CT2A(fixedFilePath3.GetString());

	//if (FilePath_Save1.empty()) { // ����ļ�·���Ƿ�Ϊ��
		// ����ļ�·��Ϊ�գ��������û�ȡ���˶Ի�����ʱ��Ӧ���˳�����
		//MessageBox(L"�����ļ�ʧ�ܣ������ڱ���ʱ���ļ�", L"����", MB_OK | MB_ICONERROR);
		//return;
	//}

	// ���ļ�����д��
	ofstream SaveFile1(FilePath_Save1, ios::out);
	ofstream SaveFile2(FilePath_Save2, ios::out);
	ofstream SaveFile3(FilePath_Save3, ios::out);
	//if (!SaveFile1) { // ����Ӧ���� SaveFile1�������� SaveFile
		//MessageBox(L"�����ļ�ʧ�ܣ������ڱ���ʱ���ļ�", L"����", MB_OK | MB_ICONERROR);
		//return;
	//}
	// ��������
	for (auto it = m_Data.begin(); it != m_Data.end(); it++) {
		// д��ʱ��
		//SaveFile1 << it->time << ",";
		
		// ���ݴ���������д������
		if (it->Sensor == "���ײ��״�") {
			SaveFile1 <<t.wMonth<<"," <<t.wDay<<"," <<t.wHour<<"," << it->dData << ",";
			SaveFile1 << endl;
		}
		else if (it->Sensor == "�����״�") {
			SaveFile2 << t.wMonth << "," << t.wDay << "," << t.wHour << "," << it->dData << ",";
			SaveFile2 << endl;

		}
		else if (it->Sensor == "���˼����") {
			SaveFile3 << t.wMonth << "," << t.wDay << "," << t.wHour << "," << it->dData << ",";
			SaveFile3 << endl;
		}
	}

	// �ر��ļ�
	SaveFile1.close();
	//MessageBox(L"����ɹ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
}


void CMy02_TCPClientDlg::OnBnClickedButton11()
{
	ThreadStart();
	//SetTimer(0, 1000, NULL);
	
	
	//m_CsendBuf.SetWindowTextW(_T(""));
}

DWORD WINAPI process2(LPVOID pParam)
{
	CMy02_TCPClientDlg* p_Mainprocess = (CMy02_TCPClientDlg*)pParam;
	int error;
	socklen_t len = sizeof(error);
	int ret = getsockopt(p_Mainprocess->m_connSocket, SOL_SOCKET, SO_ERROR, (char*)&error, &len);
	/*if (ret == 0 && error == 0) {
		// �׽������ӳɹ�
		AfxMessageBox(_T("ok"));
	}
	else {
		// �׽�������ʧ��
	}*/
	using namespace std;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int flag;
	CString msg;
	//����T2A��W2A��֧��ATL��MFC�е��ַ�
	if (p_Mainprocess==NULL)
	{
		AfxMessageBox(_T("1"));

	}
	if (p_Mainprocess->m_Data.empty())
	{
		AfxMessageBox(_T("����Ϊ��"));
		return 0;
	}

	int iWrite;

	vector<FileSave>::iterator it;
	for (it = p_Mainprocess->m_Data.begin(); it != p_Mainprocess->m_Data.end(); it++) {
		char szBuf[256] = { 0 };
		// ���������߼�...

		if (it->Sensor == "���ײ��״�")
		{
			//iWrite = p_Mainprocess->m_connSocket.Send("�ٶ�:", 5);
		}
		else if (it->Sensor == "�����״�")
		{
			//iWrite = p_Mainprocess->m_connSocket.Send("����:", 5);
		}
		else
		{
			///iWrite = p_Mainprocess->m_connSocket.Send("����:", 5);
		}
		// ���������߼�...

		int errorCode = ::WSAGetLastError(); // ��ȡ�������

		//if (SOCKET_ERROR == iWrite) {
			// ������ʧ�ܵ����
			//AfxMessageBox(_T("Failed to send message to client."));
			// AfxMessageBox(errorCode); // ����������
		//}

		strncpy_s(szBuf, sizeof(szBuf), it->dData.c_str(), sizeof(it->dData) - 1);
		iWrite = p_Mainprocess->m_connSocket.Send(szBuf, strlen(szBuf));

		//strncpy_s(szBuf, sizeof(szBuf), it->unit.c_str(), sizeof(it->unit) - 1);
		//iWrite = p_Mainprocess->m_connSocket.Send(szBuf, strlen(szBuf));
		// �ȴ�1��
		Sleep(1000);
	}
	//TerminateThread(CreateThread, 0);

	return 0;
}

void CMy02_TCPClientDlg::ThreadStart()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	handle_Thread = CreateThread(NULL, 0, process2, this, 0, 0);
	if (handle_Thread == NULL)
		MessageBox(_T("�����߳�ʧ��"));
	else
	{
		m_ButtonStartTh.EnableWindow(0);
		m_ButtonstopTh.EnableWindow(1);
		//MessageBox(_T("��ʼ����"));
	}
}

void CMy02_TCPClientDlg::OnBnClickedButton15()
{
	CarCommu Car;
	Car.DoModal();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CMy02_TCPClientDlg::OnBnClickedButton14()
{
	plot p;
	p.DoModal();
}

void CMy02_TCPClientDlg::SendPort(char* send)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	int flag=m_connSocket.Send(send, strlen(send));
	if (!flag)
	{
		AfxMessageBox(_T("�˿ںŷ���ʧ��"));
	}
	else
	{
		AfxMessageBox(_T("�˿ںŷ��ͳɹ�"));
	}
}

void CMy02_TCPClientDlg::OnBnClickedButton16()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}
void CMy02_TCPClientDlg::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString msg1;

		if (SetAll.GetCheck())
		{
			SetTimer(5, 1000, NULL);
			msg1.Format(_T("%d"), 16);

			communications1.put_Output(COleVariant(msg1));
		}
		else
		{
			KillTimer(5);
			msg1.Format(_T("%d"), 17);
			communications1.put_Output(COleVariant(msg1));

		}
}

void CMy02_TCPClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 3:
	{
		int iPos = 0;
		iPos = m_progress.GetPos();//��ȡ��ǰ������λ��
		iPos -= 1;
		m_progress.SetPos(iPos);
		CString s1, s2;
		s1 = _T("%");
		s2.Format(_T("%d"), iPos);
		SetDlgItemText(IDC_STATIC2, s2 + s1);
		m_power = s2 + s1;
		if (iPos == 45)//���ﵽ100��ʱ��͹رն�ʱ��,�����°�ť����,λ����Ϊ0
		{
			KillTimer(3);
			//m_progress.SetPos(0);
		}
	}
	case 5:
	{
		CString msg1;
		CString msg2;
		CString msg3;
		CString Time;

		SYSTEMTIME t;
		GetLocalTime(&t);

		double randomDistance = 0.2 + (rand() / (double)RAND_MAX) * (10 - 0.2);
		msg1.Format(_T("[%d:%d:%d] : %.2lfm"), t.wHour, t.wDay, t.wSecond, randomDistance);
		double randomPerson = 0 + (rand() / (double)RAND_MAX) * 8;
		msg2.Format(_T("[%d:%d:%d] : %.0lf ��"), t.wHour, t.wDay, t.wSecond, randomPerson);
		double randomSpeed = 20 + (rand() / (double)RAND_MAX) * 20;
		msg3.Format(_T("[%d:%d:%d] : %.0lf km/h"), t.wHour, t.wDay, t.wSecond, randomSpeed);

		DistanceShowers.SetWindowText(msg1);
		PersonShowers.SetWindowText(msg2);
		CSpeedShower.SetWindowText(msg3);
	}
	default:
		break;
	}
	
}

void CMy02_TCPClientDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMy02_TCPClientDlg::draw()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	CImage image;
	//image.Load(TEXT("D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\s1.png"));  //����ͼƬ
	image.Load(TEXT("E:\\E-download\\fatigue_detecting-master\\fatigue_detecting-master\\images\\4eea0fb74d226.png"));  //����ͼƬ
	// �����ؼ�����Ϊ��ͼ��ͬһ�ߴ�  
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC);//��þ�����ǿؼ���id
	pStatic->SetWindowPos(NULL,
		100,
		100,
		image.GetWidth(),
		image.GetHeight(),
		SWP_NOMOVE);
	pStatic->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
	pStatic->SetBitmap((HBITMAP)image.Detach());
}


void CMy02_TCPClientDlg::OnBnClickedButton13()
{
    // �����ļ�·��
	LPCTSTR filePath = L"D:\\python.way\\pythonProject6\\dist\\main_UI.exe";

	// ʹ��ShellExecute���ļ�
	HINSTANCE result = ShellExecute(NULL, _T("open"), filePath, NULL, NULL, SW_SHOWNORMAL);

	// ���ִ���Ƿ�ɹ�
	if ((int)result <= 32)
	{
		// ������󣬿���ʹ��GetLastError��ȡ��ϸ��Ϣ
		AfxMessageBox(_T("Failed to open file"));
	}
}




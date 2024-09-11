
// 02_TCPClientDlg.cpp : 实现文件
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
#include<fstream>  // 文件流


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy02_TCPClientDlg 对话框
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


// CMy02_TCPClientDlg 消息处理程序

BOOL CMy02_TCPClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	m_ip.SetAddress(127, 0, 0, 1);
	m_port = 8888;
	UpdateData(FALSE);
	m_disConnBtn.EnableWindow(FALSE);
	m_sendBtn.EnableWindow(FALSE);

	m_listCtrl1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT);
	//拓展list control的格式
	//绘制网格线，表头可以拖拽，可以选择整行或者整列
	CString col[6] = { _T("编号"),_T("用户名"),_T("时间"),_T("速度"),_T("车距"),_T("行人数") };
	RECT r;	//rect对象用来存储一个矩形框的左上角坐标、宽度和高度。
	m_listCtrl1.GetClientRect(&r);	//显示矩形框调用函数要加取地址符号
	for (int i = 0; i < 6; i++)
	{
		m_listCtrl1.InsertColumn(i, col[i], LVCFMT_CENTER, (r.right - r.left) / 6);
	}

	m_listCtrl1.SetBkColor(RGB(199, 237, 233));	//设置列表框背景颜色
	m_listCtrl1.SetTextColor(RGB(18, 53, 85));	//字体颜色
	m_listCtrl1.SetTextBkColor(RGB(175, 215, 237));//文字背景色
	m_listCtrl.SetBkColor(RGB(199, 237, 233));	//设置列表框背景颜色
	m_listCtrl.SetTextColor(RGB(18, 53, 85));	//字体颜色
	m_listCtrl.SetTextBkColor(RGB(175, 215, 237));//文字背景色
	//InitStatus();	//初始化状态框


	//m_icon_2.SetIcon(m_hIconRed);//初始化为红色
	//串口初始化
	/*chuankouhao.AddString(_T("COM1"));
	chuankouhao.AddString(_T("COM2"));
	chuankouhao.AddString(_T("COM3"));
	chuankouhao.AddString(_T("COM4"));
	chuankouhao.AddString(_T("COM5"));
	chuankouhao.AddString(_T("COM6"));*/

	botelv.AddString(_T("4800"));
	botelv.AddString(_T("9600"));
	botelv.AddString(_T("14400"));

	chuankouhao.AddString(_T("毫米波雷达"));
	chuankouhao.AddString(_T("激光雷达"));
	chuankouhao.AddString(_T("行人检测仪"));
	
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
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE


}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy02_TCPClientDlg::OnPaint()
{

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
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


// 连接TCP服务器
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
			MessageBox(_T("连接服务器失败"));
			m_connSocket.Close();
		}
	}
	else
	{
		MessageBox(_T("创建套接字失败"));
	}
}

// 断开连接
void CMy02_TCPClientDlg::OnBnClickedButton2()
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	CString msg;
	msg.Format(_T("[%d:%d:%d]: 断开与服务器连接!"), t.wHour, t.wMinute, t.wSecond);
	AddMsg(msg);
	m_connBtn.EnableWindow(TRUE);
	m_disConnBtn.EnableWindow(FALSE);
	m_sendBtn.EnableWindow(FALSE);

	m_connSocket.Close();
}

// 向服务器发送消息
void CMy02_TCPClientDlg::OnBnClickedButton3()
{
	UpdateData(TRUE);
	USES_CONVERSION;
	//函数T2A和W2A均支持ATL和MFC中的字符
	char * send = T2A(m_sendBuf);
	m_connSocket.Send(send, strlen(send));
	m_CsendBuf.SetWindowTextW(_T(""));
}

// 清空消息列表
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
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CMy02_TCPClientDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	
	int m_McsPortNum = 0; //定义串口号
	CString bote, jiaoyan, tingzhi, shuju; //波特率、校验位、停止位、数据位
	CString PortStr; //设置字符串

	
	switch (chuankouhao.GetCurSel())  //获取外部端口号
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

	jiaoyan = _T("e");   //无校验位，协议只允许这样写

	GetDlgItemText(IDC_COMBO3, bote);  //获取波特率
	//GetDlgItemText(IDC_COMBO5, tingzhi);   //获取停止位
	//GetDlgItemText(IDC_COMBO6, shuju);   //获取数据位

	PortStr = bote + _T(",") + jiaoyan + _T(",") + shuju + _T(",") + tingzhi;//将字符串合成


	communications1.put_InBufferSize(2048);  //设置接收缓冲区
	communications1.put_OutBufferSize(2048);  //设置发送缓冲区
	communications1.put_Settings(PortStr); //设置初始化 波特率+校验位+数据位+停止位
	communications1.put_InputMode(1);  //以二进制方式读写

	if (communications1.get_PortOpen())  //返回当前是否有串口打开。true是有串口打开
	{
		communications1.put_PortOpen(FALSE);   //如果有串口打开，则设置串口关闭
	}
	communications1.put_CommPort(m_McsPortNum);  //上述操作保证没有串口打开后，设置需要打开的串口号，为串口打开做准备

	if (!communications1.get_PortOpen())   //如果没有串口打开（没有串口打开返回FALSE），则以下打开串口
	{
		communications1.put_PortOpen(TRUE);  //打开串口
	}
	else
	{
		MessageBox(_T("没有打开串口"), _T("信息提示！"), MB_ICONERROR | MB_OKCANCEL);
	}

	communications1.put_RThreshold(2);  //设置阈值，当接收缓冲区数量达到阈值时，产生onComm事件，启动接收
	communications1.put_SThreshold(2);  //设置阈值，当发送缓冲区数量达到阈值时，进行发送
	communications1.put_InputLen(0); //设置0含义为接收缓冲区中的数据全部读取
	communications1.get_Input();//读取缓冲区的数据
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
	// TODO: 在此添加控件通知处理程序代码int connect = 12;
	CString SnedBegin, SnedStop,Connect, pause, conti, discon;
	SnedBegin.Format(_T("10"));
	SnedStop.Format(_T("11"));
	
	/*switch (chuankouhao.GetCurSel())  //获取外部端口号
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
	if (xuanze.GetCheck() == TRUE)   //如果进行了选择，则把自动发送变量赋值
	{

		if (communications1.get_PortOpen() == TRUE)  //端口打开状态
		{
			communications1.put_Output(COleVariant(SnedBegin));
		}
	}
	else
	{
		if (communications1.get_PortOpen() == TRUE)  //端口打开状态
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
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

BEGIN_EVENTSINK_MAP(CMy02_TCPClientDlg, CDialogEx)
	ON_EVENT(CMy02_TCPClientDlg, IDC_MSCOMM1, 1, CMy02_TCPClientDlg::OnOncommMscomm1, VTS_NONE)
	//ON_EVENT(CMy02_TCPClientDlg, IDC_MSCOMM3, 1, CMy02_TCPClientDlg::OnOncommMscomm2, VTS_NONE)
END_EVENTSINK_MAP()

void CMy02_TCPClientDlg::OnOncommMscomm1()
{
	// TODO: 在此处添加实现代码.
	setlocale(LC_CTYPE, "chs");
	SYSTEMTIME t;
	GetLocalTime(&t);
	CString Time, msgs, unit[3],test;

	VARIANT        m_Variant_Rec; //接收类型定义
	COleSafeArray  m_SafeArray_Rec;  //用于处理任意类型和维数数组的类
	LONG           m_DataLenth, nCount;  //定义接收的长度和计数用
	const int      m_RecByteLenth = 2048;
	BYTE           m_RecDataByte[m_RecByteLenth];  //定义接收缓冲区
	CString        m_TemDataStr;  //接收字符串，用于转换后显示
	if (communications1.get_CommEvent() == 2)   //串口事件值为2，表示接收缓冲区字符
	{
		m_Variant_Rec = communications1.get_Input();  //获取缓冲区内容
		m_SafeArray_Rec = m_Variant_Rec;   //把缓冲区内容放到SafeArray数据结构中

		m_DataLenth = m_SafeArray_Rec.GetOneDimSize(); //获取一维数据的长度
		for (nCount = 0; nCount < m_DataLenth; nCount++)
			m_SafeArray_Rec.GetElement(&nCount, m_RecDataByte + nCount); //检索SafeArray中的内容，用不同ncout位置进行指针的偏移量，取出对应位置内容
		CSpeedShow.SetWindowText(_T(""));
		pData = new CMy02_TCPClientDlg;
		for (nCount = 0; nCount < m_DataLenth; nCount++)
		{
			BYTE m_Buff = *(char*)(m_RecDataByte + nCount);  //从数组开头进行ncount偏移量，提取对应位置的内容
			m_TemDataStr.Format(_T("%C"), m_Buff); //把相关BYTE内容转化为char
			//test += m_TemDataStr;
			if (chuankouhao.GetCurSel() == 0)//&&(20<=(_ttoi(test)))
			{
				SpeedShow += m_TemDataStr;  //把char加入到所显示的字符串中
				//CSpeedShow.SetWindowTextW(m_TemDataStr);
				Time.Format(_T("[%d:%d:%d] :"), t.wHour, t.wMinute, t.wSecond);
				unit[chuankouhao.GetCurSel()].Format(_T("km/h"));
				msgs = Time + SpeedShow+unit[0];
				/*pFile->Sensor = "速度传感器";
				pFile->dData = CT2A(SpeedShow.GetString());
				pFile->time = CT2A(Time.GetString());
				pData->m_Data.push_back(*pFile);
				test.Format(_T("%s"), pFile->time);*/
				if (20 <= (_ttoi(SpeedShow)))
				{
					if (35 <= _ttoi(SpeedShow))
					{
						CString msgss;
						msgss.Format(_T("[%d:%d:%d] 127.0.0.1:8888 驾驶员请注意车速:%s km/h"),t.wHour,t.wMinute,t.wSecond, SpeedShow);
						AddMsg(msgss);
					}
					Time.Format(_T("%d:%d:%d"), t.wHour, t.wMinute, t.wSecond);
					pFile = new FileSave;
					pFile->Sensor = "毫米波雷达";
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
			//CSpeedShower.SetSel(-1, -1); //自动滚屏（其中m_Edit是EDIT筐所关联的EDIT控制对象）
			//CSpeedShower.ReplaceSel(SpeedShow + "\r\n"); //自动换行
			if (chuankouhao.GetCurSel() == 1)//&&(_wtof(test))
			{
				DistanceShow += m_TemDataStr;  //把char加入到所显示的字符串中
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
						msgss.Format(_T("[%d:%d:%d] 127.0.0.1:8888 驾驶员请注意车距:%s m"), t.wHour, t.wMinute, t.wSecond, DistanceShow);
						AddMsg(msgss);

					}
					Time.Format(_T("%d:%d:%d"), t.wHour, t.wMinute, t.wSecond);
					pFile = new FileSave;
					pFile->Sensor = "激光雷达";
					pFile->dData = CT2A(DistanceShow.GetString());
					pFile->time = CT2A(Time.GetString());
					pFile->unit = CT2A(unit[chuankouhao.GetCurSel()].GetString());
					m_Data.push_back(*pFile);
					SendSrv.push_back(*pFile);
				}
			}
			if (chuankouhao.GetCurSel() == 2)//&& ( 0<= _ttoi(test)<=8)
			{
				PersonShow += m_TemDataStr;  //把char加入到所显示的字符串中
				Time.Format(_T("[%d:%d:%d] :"), t.wHour, t.wMinute, t.wSecond);
				unit[chuankouhao.GetCurSel()].Format(_T("人"));
				msgs = Time + PersonShow + unit[chuankouhao.GetCurSel()];
				PersonShowers.SetWindowText(msgs);
				PersonShowers.LineScroll(PersonShowers.GetLineCount() - 1, 0);

				if (PersonShow!=_T(" "))
				{
					Time.Format(_T("%d:%d:%d"), t.wHour, t.wMinute, t.wSecond);
					pFile = new FileSave;
					pFile->Sensor = "行人检测仪";
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
		AfxMessageBox(_T("数据后台存储失败"));
		}

		UpdateData(FALSE);
	}

	communications1.put_InBufferCount(0);  //取出数据后，进行数据的清零
	communications1.put_OutBufferCount(0);
}





void CMy02_TCPClientDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}

DWORD WINAPI process1(LPVOID pParam)
{
	/*CMy02_TCPClientDlg* p_Mainprocess = (CMy02_TCPClientDlg*)pParam;
	bool Is_Thread = false;
	setlocale(LC_CTYPE, "chs");
	SYSTEMTIME t;
	GetLocalTime(&t);
	CString Time, msgs, unit[3];

	VARIANT        m_Variant_Rec; //接收类型定义
	COleSafeArray  m_SafeArray_Rec;  //用于处理任意类型和维数数组的类
	LONG           m_DataLenth, nCount;  //定义接收的长度和计数用
	const int      m_RecByteLenth = 2048;
	BYTE           m_RecDataByte[m_RecByteLenth];  //定义接收缓冲区
	CString        m_TemDataStr;  //接收字符串，用于转换后显示
	while (true)
	{
		switch (p_Mainprocess->chuankouhao.GetCurSel())//检测使用哪种传感器
		{
		case 0:
		{
			while (!p_Mainprocess->communications1.get_CommEvent())
			{

			}
			if (p_Mainprocess->communications1.get_CommEvent())
			{
				p_Mainprocess->SpeedShow += m_TemDataStr;  //把char加入到所显示的字符串中
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
	// TODO: 在此处添加实现代码.
}


void CMy02_TCPClientDlg::OnBnClickedButton6()
{
	/*int ref = SuspendThread(handle_Thread);
	if (ref == -1)
		MessageBox(_T("暂停失败"));
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
	// TODO: 在此添加控件通知处理程序代码
	/*int ref = ResumeThread(handle_Thread);
	if (ref == -1)
		MessageBox(_T("继续失败"));
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
	// TODO: 在此添加控件通知处理程序代码
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
	//MessageBox(_T("串口已关闭"));
}

void CMy02_TCPClientDlg::OnOncommMscomm2()
{
	// TODO: 在此处添加实现代码.
	VARIANT        m_Variant_Rec; //接收类型定义
	COleSafeArray  m_SafeArray_Rec;  //用于处理任意类型和维数数组的类
	LONG           m_DataLenth, nCount;  //定义接收的长度和计数用
	const int      m_RecByteLenth = 2048;
	BYTE           m_RecDataByte[m_RecByteLenth];  //定义接收缓冲区
	CString        m_TemDataStr;  //接收字符串，用于转换后显示
	if (communications1.get_CommEvent() == 2)   //串口事件值为2，表示接收缓冲区字符
	{
		m_Variant_Rec = communications1.get_Input();  //获取缓冲区内容
		m_SafeArray_Rec = m_Variant_Rec;   //把缓冲区内容放到SafeArray数据结构中

		m_DataLenth = m_SafeArray_Rec.GetOneDimSize(); //获取一维数据的长度
		for (nCount = 0; nCount < m_DataLenth; nCount++)
			m_SafeArray_Rec.GetElement(&nCount, m_RecDataByte + nCount); //检索SafeArray中的内容，用不同ncout位置进行指针的偏移量，取出对应位置内容
		CSpeedShow.SetWindowText(_T(""));

		for (nCount = 0; nCount < m_DataLenth; nCount++)
		{
			BYTE m_Buff = *(char*)(m_RecDataByte + nCount);  //从数组开头进行ncount偏移量，提取对应位置的内容
			m_TemDataStr.Format(_T("%C"), m_Buff); //把相关BYTE内容转化为char
			SpeedShow += m_TemDataStr;  //把char加入到所显示的字符串中
		}
		//AfxMessageBox(SpeedShow);
		//SpeedShow += _T("\r\n");

		UpdateData(FALSE);
	}

	communications1.put_InBufferCount(0);  //取出数据后，进行数据的清零
	communications1.put_OutBufferCount(0);
}

void CMy02_TCPClientDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	int rank = 1;
	CFileDialog* p_savefile = new CFileDialog(FALSE, L".csv", NULL, OFN_READONLY, L"CSV(*.csv)|*.csv");
	p_savefile->DoModal();
	string FilePath_Save = CT2A(p_savefile->GetPathName().GetString());
	delete p_savefile;
	char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));//语言区域设置
	if (FilePath_Save.empty()) { // 检查文件路径是否为空
		// 如果文件路径为空，可能是用户取消了对话框，这时候应该退出程序
		MessageBox( L"保存文件失败，请勿在保存时打开文件", L"错误", MB_OK | MB_ICONERROR);
		return ;
	}

	// 打开文件进行写入
	ofstream SaveFile(FilePath_Save, ios::out);
	if (!SaveFile) {
		MessageBox( L"保存文件失败，请勿在保存时打开文件", L"错误", MB_OK | MB_ICONERROR);
		return ;
	}
	// 写入表头
	SaveFile << "标号" << "," << "用户" << "," << "传感器类型" << "," << "时间" << "," << "数据" <<"," << "单位" << endl;

	CString msg;
	

	for (auto it = m_Data.begin(); it != m_Data.end(); it++) {
		// 写入每个userinfo对象的数据
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
	// 关闭文件
	setlocale(LC_CTYPE, old_locale); //还原语言区域的设置 
	free(old_locale);//还原区域设定
	SaveFile.close();
	MessageBox( L"保存成功", L"提示", MB_OK | MB_ICONINFORMATION);

	poltData();


	return ;
}


void CMy02_TCPClientDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	//DataSearch a;
	//a.DoModal();
	CFileDialog openFileDialog(TRUE, L".csv", NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, L"CSV Files (*.csv)|*.csv||");
    if (openFileDialog.DoModal() == IDOK) {
        CString filePath = openFileDialog.GetPathName();

        // 创建文件内容窗口并显示文件内容
		DataSearch fliecontent;
		fliecontent.fileContentWindow(filePath);
		fliecontent.DoModal();
    }
}


void CMy02_TCPClientDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fileDlg(TRUE, _T("csv"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("CSV Files (*.csv)|*.csv||"), NULL);
	if (fileDlg.DoModal() == IDOK) {
		{
			CString filePath = fileDlg.GetPathName();
			DataSearch a;
			a.DoModal();
		}

		// 在这里使用文件路径进行后续操作，例如读取CSV文件内容等
	}
	else {
		// 用户取消了文件对话框操作

	}
}


void CMy02_TCPClientDlg::poltData()
{
	// TODO: 在此处添加实现代码.
	// 指定固定的文件路径
	/**/
	SYSTEMTIME t;
	GetLocalTime(&t);
	CString fixedFilePath1 = L"D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\excel\\工作簿1.csv";
	CString fixedFilePath2 = L"D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\excel\\工作簿2.csv";
	CString fixedFilePath3 = L"D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\excel\\工作簿3.csv";
	string FilePath_Save1 = CT2A(fixedFilePath1.GetString());
	string FilePath_Save2 = CT2A(fixedFilePath2.GetString());
	string FilePath_Save3 = CT2A(fixedFilePath3.GetString());

	//if (FilePath_Save1.empty()) { // 检查文件路径是否为空
		// 如果文件路径为空，可能是用户取消了对话框，这时候应该退出程序
		//MessageBox(L"保存文件失败，请勿在保存时打开文件", L"错误", MB_OK | MB_ICONERROR);
		//return;
	//}

	// 打开文件进行写入
	ofstream SaveFile1(FilePath_Save1, ios::out);
	ofstream SaveFile2(FilePath_Save2, ios::out);
	ofstream SaveFile3(FilePath_Save3, ios::out);
	//if (!SaveFile1) { // 这里应该是 SaveFile1，而不是 SaveFile
		//MessageBox(L"保存文件失败，请勿在保存时打开文件", L"错误", MB_OK | MB_ICONERROR);
		//return;
	//}
	// 遍历数据
	for (auto it = m_Data.begin(); it != m_Data.end(); it++) {
		// 写入时间
		//SaveFile1 << it->time << ",";
		
		// 根据传感器类型写入数据
		if (it->Sensor == "毫米波雷达") {
			SaveFile1 <<t.wMonth<<"," <<t.wDay<<"," <<t.wHour<<"," << it->dData << ",";
			SaveFile1 << endl;
		}
		else if (it->Sensor == "激光雷达") {
			SaveFile2 << t.wMonth << "," << t.wDay << "," << t.wHour << "," << it->dData << ",";
			SaveFile2 << endl;

		}
		else if (it->Sensor == "行人检测仪") {
			SaveFile3 << t.wMonth << "," << t.wDay << "," << t.wHour << "," << it->dData << ",";
			SaveFile3 << endl;
		}
	}

	// 关闭文件
	SaveFile1.close();
	//MessageBox(L"保存成功", L"提示", MB_OK | MB_ICONINFORMATION);
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
		// 套接字连接成功
		AfxMessageBox(_T("ok"));
	}
	else {
		// 套接字连接失败
	}*/
	using namespace std;
	// TODO: 在此添加控件通知处理程序代码
	int flag;
	CString msg;
	//函数T2A和W2A均支持ATL和MFC中的字符
	if (p_Mainprocess==NULL)
	{
		AfxMessageBox(_T("1"));

	}
	if (p_Mainprocess->m_Data.empty())
	{
		AfxMessageBox(_T("数据为空"));
		return 0;
	}

	int iWrite;

	vector<FileSave>::iterator it;
	for (it = p_Mainprocess->m_Data.begin(); it != p_Mainprocess->m_Data.end(); it++) {
		char szBuf[256] = { 0 };
		// 其他发送逻辑...

		if (it->Sensor == "毫米波雷达")
		{
			//iWrite = p_Mainprocess->m_connSocket.Send("速度:", 5);
		}
		else if (it->Sensor == "激光雷达")
		{
			//iWrite = p_Mainprocess->m_connSocket.Send("车距:", 5);
		}
		else
		{
			///iWrite = p_Mainprocess->m_connSocket.Send("行人:", 5);
		}
		// 其他发送逻辑...

		int errorCode = ::WSAGetLastError(); // 获取错误代码

		//if (SOCKET_ERROR == iWrite) {
			// 处理发送失败的情况
			//AfxMessageBox(_T("Failed to send message to client."));
			// AfxMessageBox(errorCode); // 输出错误代码
		//}

		strncpy_s(szBuf, sizeof(szBuf), it->dData.c_str(), sizeof(it->dData) - 1);
		iWrite = p_Mainprocess->m_connSocket.Send(szBuf, strlen(szBuf));

		//strncpy_s(szBuf, sizeof(szBuf), it->unit.c_str(), sizeof(it->unit) - 1);
		//iWrite = p_Mainprocess->m_connSocket.Send(szBuf, strlen(szBuf));
		// 等待1秒
		Sleep(1000);
	}
	//TerminateThread(CreateThread, 0);

	return 0;
}

void CMy02_TCPClientDlg::ThreadStart()
{
	// TODO: 在此处添加实现代码.
	handle_Thread = CreateThread(NULL, 0, process2, this, 0, 0);
	if (handle_Thread == NULL)
		MessageBox(_T("创建线程失败"));
	else
	{
		m_ButtonStartTh.EnableWindow(0);
		m_ButtonstopTh.EnableWindow(1);
		//MessageBox(_T("开始传输"));
	}
}

void CMy02_TCPClientDlg::OnBnClickedButton15()
{
	CarCommu Car;
	Car.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}
void CMy02_TCPClientDlg::OnBnClickedButton14()
{
	plot p;
	p.DoModal();
}

void CMy02_TCPClientDlg::SendPort(char* send)
{
	// TODO: 在此处添加实现代码.
	int flag=m_connSocket.Send(send, strlen(send));
	if (!flag)
	{
		AfxMessageBox(_T("端口号发送失败"));
	}
	else
	{
		AfxMessageBox(_T("端口号发送成功"));
	}
}

void CMy02_TCPClientDlg::OnBnClickedButton16()
{
	// TODO: 在此添加控件通知处理程序代码

}
void CMy02_TCPClientDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码

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
		iPos = m_progress.GetPos();//获取当前进度条位置
		iPos -= 1;
		m_progress.SetPos(iPos);
		CString s1, s2;
		s1 = _T("%");
		s2.Format(_T("%d"), iPos);
		SetDlgItemText(IDC_STATIC2, s2 + s1);
		m_power = s2 + s1;
		if (iPos == 45)//当达到100的时候就关闭定时器,并且事按钮可用,位置设为0
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
		msg2.Format(_T("[%d:%d:%d] : %.0lf 人"), t.wHour, t.wDay, t.wSecond, randomPerson);
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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMy02_TCPClientDlg::draw()
{
	// TODO: 在此处添加实现代码.
	CImage image;
	//image.Load(TEXT("D:\\HuaweiMoveData\\Users\\HUAWEI\\Desktop\\s1.png"));  //加载图片
	image.Load(TEXT("E:\\E-download\\fatigue_detecting-master\\fatigue_detecting-master\\images\\4eea0fb74d226.png"));  //加载图片
	// 将整控件调整为与图像同一尺寸  
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC);//获得句柄就是控件的id
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
    // 定义文件路径
	LPCTSTR filePath = L"D:\\python.way\\pythonProject6\\dist\\main_UI.exe";

	// 使用ShellExecute打开文件
	HINSTANCE result = ShellExecute(NULL, _T("open"), filePath, NULL, NULL, SW_SHOWNORMAL);

	// 检查执行是否成功
	if ((int)result <= 32)
	{
		// 处理错误，可以使用GetLastError获取详细信息
		AfxMessageBox(_T("Failed to open file"));
	}
}




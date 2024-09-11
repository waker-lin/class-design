
// 02_TCPClientDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ConnSocket.h"
#include "CMSCOMM1.h"
#include <vector>
#include <string>
#include "CMSCOMM2.h"
#include "FileSave.h"
#include <gdiplus.h>
#include <mutex>

using namespace std;
using namespace Gdiplus;


// CMy02_TCPClientDlg 对话框
class CMy02_TCPClientDlg : public CDialogEx
{
// 构造
public:
	CMy02_TCPClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY02_TCPCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()
public:
//	CIPAddressCtrl m_serverIp;
//private:
public:
	UINT m_port;
	CIPAddressCtrl m_ip;
	CButton m_connBtn;
	CButton m_disConnBtn;
	CString m_sendBuf;
	CButton m_sendBtn;
	CButton m_clearBtn;
	CListCtrl m_listCtrl;
	CConnSocket m_connSocket;
	bool m_connSuc;
	FileSave* pFile;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	// 往消息列表中添加一条消息
	void AddMsg(CString msg);
	
	void MyEnableBtn();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	vector<FileSave> m_Data;
	vector<FileSave> SendSrv;
	CMy02_TCPClientDlg* pData;
	CListCtrl m_listCtrl1;
	CComboBox botelv;
	CComboBox chuankouhao;
	CMSCOMM1 communications1;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedCheck1();
	CButton xuanze;
	afx_msg void OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
	void OnOncommMscomm1();
	void OnOncommMscomm2();
	CString SpeedShow;
	HANDLE handle_Thread;

	afx_msg void OnCbnSelchangeCombo1();
	CComboBox SensorType;
	CEdit CSpeedShow;
	void ThreadStart();
	CButton m_ButtonStartTh;
	CButton m_ButtonstopTh;
	void ThreadPause();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	CMSCOMM2 communications2;
	CString DistanceShow;
	CString PersonShow;
	CEdit CSpeedShower;
	CEdit DistanceShower;
	CEdit PersonShower;
	CEdit DistanceShowers;
	CEdit PersonShowers;
	CStatic m_icon_1;
	HICON m_hIconRed;
	HICON m_hIconGreen;
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton9();
	void poltData();
	CButton m_Buttoncon;
	CButton m_Buttonpause;
	CEdit m_CsendBuf;
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton14();
	void SendPort(char* send);
	afx_msg void OnBnClickedButton16();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	std::mutex m_DataMutex;
	afx_msg void OnEnChangeEdit3();

	CStatic m_picturePng;
	void draw();
	afx_msg void OnBnClickedButton13();
	CProgressCtrl m_progress;
	CStatic power;
	CString m_powers;
	CString m_power;
	CButton m_SendFile;
	afx_msg void OnBnClickedCheck2();
	CButton SetAll;
};

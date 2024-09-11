#pragma once

#include"02_TCPClientDlg.h"
#include"ClientSocket1.h"
#include<list>
// CarCommu 对话框


class CarCommu : public CDialogEx,public CSocket
{
	DECLARE_DYNAMIC(CarCommu)

public:
	CarCommu(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CarCommu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	HANDLE handle_Thread;
	HANDLE handle_Thread2;
	CConnSocket m_connSocket1;
	UINT m_port1;
	UINT m_port0;
	CIPAddressCtrl m_ip;
	CListCtrl m_listCtrl;
	list<CConnSocket*> m_clientList;
	virtual BOOL OnInitDialog();
	CString m_port;
	CString m_rcv;
	CString m_send;
	CMy02_TCPClientDlg * c_dlg=new CMy02_TCPClientDlg;
	afx_msg void OnBnClickedButton3();
	void listInit(char* port);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	CConnSocket& quote(CConnSocket& Con);
	//CSocket clientSocket;

	afx_msg void OnBnClickedButton5();
	void ThreadStart();
	CEdit m_CsendBuf;
	CEdit m_sender;
	CEdit m_rcver;
	ClientSocket1 clientSocket;
	void AddEdit(CString msg);
	CEdit m_rc;
	CString m_r;
	ClientSocket1* message;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CMy02_TCPClientDlg* p=new CMy02_TCPClientDlg;

	void ThreadStart2();
};


// 02_TCPServerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "ServerSocket.h"
#include "MyServerSocket.h"

// CMy02_TCPServerDlg 对话框
class CMy02_TCPServerDlg : public CDialogEx
{
// 构造
public:
	CMy02_TCPServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY02_TCPSERVER_DIALOG };
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
	DECLARE_MESSAGE_MAP()
private:
	UINT m_port;
	UINT m_port1;
	CButton m_startBtn;
	CButton m_stopBtn;
	CButton m_clearBtn;
	CListCtrl m_listCtrl;
	CServerSocket m_serverSocket;
	CServerSocket m_serverSocket1;
	CServerSocket* Insert;

public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

	// 往消息列表中添加一条消息
	void AddMsg(CString msg);
	
	CString m_sendBuf;
	afx_msg void OnBnClickedButton4();
	CButton m_sendBtn;
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	CEdit str;
	CString m_sendMes;
	CListCtrl m_listCtrl1;
	void ClientInsert();
	afx_msg void OnBnClickedButton5();
	MyServerSocket* pServerSocket = new MyServerSocket();
	void draw();
};


// 02_TCPClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ConnSocket.h"

// CMy02_TCPClientDlg �Ի���
class CMy02_TCPClientDlg : public CDialogEx
{
// ����
public:
	CMy02_TCPClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY02_TCPCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CIPAddressCtrl m_serverIp;
private:
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
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	// ����Ϣ�б������һ����Ϣ
	void AddMsg(CString msg);
	
	void MyEnableBtn();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
};

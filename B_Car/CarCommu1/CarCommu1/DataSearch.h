#pragma once
#include"string"
#include<vector>

// DataSearch 对话框

class DataSearch : public CDialogEx
{
	DECLARE_DYNAMIC(DataSearch)

public:
	DataSearch(CWnd* pParent = nullptr);   // 标准构造函数
	DataSearch(const DataSearch& other);
	//DataSearch();
	//DataSearch(const std::string& u, const std::string& s, const std::string& t, double d)
		//: user(u), sensorType(s), time(t), data(d) {};
	virtual ~DataSearch();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CListCtrl m_listCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	CComboBox m_SensorType;
	CString m_FilePath;
	void fileContentWindow(CString filePath);

	std::string rankNum;
	std::string user;
	std::string sensorType;
	std::string time;
	std::string unit;
	double data=0;
	std::vector<DataSearch> searchDataList;
	DataSearch* pSearch;


	void performSearch(const std::string& userQuery, const std::string& sensorTypeQuery,
		const std::string& Stattime, const std::string& overime, double minData, double maxData);
	void DataSearch::SensorData(const std::string& r,const std::string& u, const std::string& s, const std::string& t, double d, const std::string& un);
	//std::vector<DataSearch> DataSearch::readSensorData(CString& filePath);
	CEdit userQuery;
	CString maxData;
	CString minData;
	//CString minData;
	CString ueserQuer;
	CComboBox TimeSearch;
	void SearchShow();
	CEdit maxDate;
	CEdit minDate;
	void listInit();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton3();
	CString starttime;
	CString overtime;
	CEdit starttimer;
	CEdit overtimer;
};

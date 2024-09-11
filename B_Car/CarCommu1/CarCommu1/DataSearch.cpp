// DataSearch.cpp: 实现文件
//
#include"stdafx.h"
#include "pch.h"
#include "DataSearch.h"
#include "afxdialogex.h"
#include "Resource.h"
#include <fstream>
#include "string"
#include <sstream>
#include <locale>
#include <codecvt>
#include <vector>

// DataSearch 对话框

IMPLEMENT_DYNAMIC(DataSearch, CDialogEx)

DataSearch::DataSearch(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, maxData(_T(""))
	, minData(_T(""))
	//, minData(_T(""))
	, ueserQuer(_T(""))
	, starttime(_T(""))
	, overtime(_T(""))
{

}

DataSearch::~DataSearch()
{
}

void DataSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_SensorType);
	DDX_Control(pDX, IDC_EDIT2, userQuery);
	DDX_Text(pDX, IDC_EDIT3, maxData);
	DDX_Text(pDX, IDC_EDIT4, minData);
	//DDX_Text(pDX, IDC_EDIT4, minData);
	DDX_Text(pDX, IDC_EDIT2, ueserQuer);
	DDX_Control(pDX, IDC_COMBO2, TimeSearch);
	DDX_Control(pDX, IDC_EDIT3, maxDate);
	DDX_Control(pDX, IDC_EDIT4, minDate);
	DDX_Text(pDX, IDC_EDIT5, starttime);
	DDX_Text(pDX, IDC_EDIT6, overtime);
	DDX_Control(pDX, IDC_EDIT5, starttimer);
	DDX_Control(pDX, IDC_EDIT6, overtimer);
}

BEGIN_MESSAGE_MAP(DataSearch, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &DataSearch::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &DataSearch::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DataSearch::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &DataSearch::OnBnClickedButton3)
END_MESSAGE_MAP()

// DataSearch 消息处理程序



BOOL DataSearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	DWORD  style = m_listCtrl.GetExtendedStyle();
	m_listCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT);

	//添加网格线风格以及整行选中的风格以及前面加有选择框
	CString col[6] = { _T("编号"),_T("用户名"),_T("传感器类型"),_T("时间"),_T("数据"),_T("单位") };
	RECT r;	//rect对象用来存储一个矩形框的左上角坐标、宽度和高度。
	m_listCtrl.GetClientRect(&r);	//显示矩形框调用函数要加取地址符号
	for (int i = 0; i < 6; i++)
	{
		m_listCtrl.InsertColumn(i, col[i], LVCFMT_CENTER, (r.right - r.left) / 6);
	}

	m_listCtrl.SetBkColor(RGB(199, 237, 233));	//设置列表框背景颜色
	m_listCtrl.SetTextColor(RGB(18, 53, 85));	//字体颜色
	m_listCtrl.SetTextBkColor(RGB(175, 215, 237));//文字背景色

	m_SensorType.AddString(_T("激光雷达"));
	m_SensorType.AddString(_T("毫米波雷达"));
	m_SensorType.AddString(_T("行人检测仪"));
	m_SensorType.AddString(_T("无要求"));

	//TimeSearch.AddString("");
	// 打开并读取文件内容
	/*std::ifstream file(m_FilePath);
	int rank=1;
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
			int columnIndex = 0;

			// 插入新的一行
			int rowIndex = m_listCtrl.GetItemCount();
			m_listCtrl.InsertItem(rowIndex, _T(""));

			// 逐个读取每个字段，并插入到对应的列中
			while (getline(ss, item, ',')) {
				// 将string转换为CString
				CString str(item.c_str());

				// 插入到对应的列
				m_listCtrl.SetItemText(rowIndex, columnIndex, str);
				switch (columnIndex) {
				case 0:rankNum = item; break;
				case 1: user = item; break;
				case 2: sensorType = item; break;
				case 3: time = item; break;
				case 4: data = std::stod(item); break;
				case 5: unit = item; break;
				default: break;
				}
				columnIndex++;
			}
			DataSearch Data;
			Data.SensorData(rankNum,user, sensorType, time, data,unit);
			searchDataList.push_back(Data);
		}

		file.close();
		
	}*/
	listInit();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

tm parseTime(const std::string& timeStr) {
	struct tm tm = { 0 };
	std::stringstream ss(timeStr);
	ss >> tm.tm_hour;
	ss.ignore();
	ss >> tm.tm_min;
	ss.ignore();
	ss >> tm.tm_sec;
	// 如果还有其他部分，继续解析
	// ...

	return tm;
}
void DataSearch::OnBnClickedButton1()
{
	CString Sensor,Time;
	// TODO: 在此添加控件通知处理程序代码
	switch (m_SensorType.GetCurSel()) {
	case 1: Sensor = "激光雷达"; break;
	case 0: Sensor = "毫米波雷达"; break;
	case 3: Sensor = "行人检测仪"; break;
	//case 2: Sensor = "1"; break;
	default: break;
	}
	switch (TimeSearch.GetCurSel()) {
	case 0: Time = "激光雷达"; break;
	case 1: Time = "毫米波雷达"; break;
	case 2: Time = "行人检测仪"; break;
	default: break;
	}
	userQuery.GetWindowText(ueserQuer);
	std::string user = CT2A(ueserQuer.GetString()); // 将 CString 转换为 const char*，再构造 std::string
	std::string sensor = CT2A(Sensor.GetString());
	std::string  time = CT2A(Time.GetString());
	maxDate.GetWindowText(maxData);
	minDate.GetWindowText(minData);
	starttimer.GetWindowText(starttime);
	overtimer.GetWindowText(overtime);
	std::string starttim = CStringA(starttime);
	std::string overtim=CStringA(overtime);

	//MessageBox(ueserQuer);
	if (maxData < minData)
	{
		AfxMessageBox(_T("查找条件不规范"));
	}
	else if (user.empty() && sensor.empty() && time.empty() && maxData.IsEmpty() && minData.IsEmpty()&& starttime.IsEmpty())
	{
		AfxMessageBox(_T("请输入查找条件"));
	}
	else
		performSearch(user, sensor, starttim, overtim,_tstof(minData), _tstof(maxData));
		

	if (searchDataList.empty())
	{
		AfxMessageBox(_T("error"));
	}



	/*CString Data;
	for (const auto& data : searchDataList) {
		
		// 如果所有条件都匹配，则将数据添加到 listcontrol 中
			// 将符合条件的数据添加到 listcontrol 中显示
			// 添加到 listcontrol 的代码将根据你的界面框架而不同
			int index = m_listCtrl.GetItemCount();// 获取当前列表项数量
			Data.Format(_T("%.2lf"), data.data);
			
			//MessageBox(CA2T(user.c_str()));
			MessageBox(Data);
			index++;
		}
		*/
}

DataSearch::DataSearch(const DataSearch& other) {
	// 进行适当的深拷贝或浅拷贝
	this->user = other.user;
	this->sensorType = other.sensorType;
	this->time = other.time;
	this->data = other.data;
	this->unit = other.unit;
}

void DataSearch::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}

void DataSearch::fileContentWindow(CString filePath)
{
	m_FilePath = filePath;
}
//查询

void DataSearch::performSearch(const std::string& userQuery, const std::string& sensorTypeQuery,
	const std::string& Stattime, const std::string& overime,double minData, double maxData) {
	/*// 清空上次查询结果
	// 清空 listcontrol 中的内容
	m_listCtrl.DeleteAllItems();
	bool match = true, found = false;
	CString Data,Num;
	
	// 遍历所有数据，检查每个数据条目是否符合查询条件，并将符合条件的添加到 listcontrol 中
	for (const auto& data : searchDataList) {
		
		match = true;
		

		if (!userQuery.empty() && data.user != userQuery) {
			match = false;
		}
		// 检查传感器类型
		if (!sensorTypeQuery.empty() && data.sensorType != sensorTypeQuery) {
			match = false;
			if (data.sensorType == "1")
			{
				match = true;
				AfxMessageBox(_T("1"));
			}
			//MessageBox(data.sensorType);
		}
		// 检查时间
		if (!timeQuery.empty() && data.time != timeQuery) {
			match = false;
		}
		// 检查数据范围
		if (!(this->maxData.IsEmpty()&&this->minData.IsEmpty())&& (data.data < minData || data.data > maxData)) {//std::isnan(data.data)&&
			CString a;
			a.Format(_T("%lf"), data.data);
			match = false;
			//AfxMessageBox(a);
		}



		// 如果所有条件都匹配，则将数据添加到 listcontrol 中
		if (match) {
			// 将符合条件的数据添加到 listcontrol 中显示
			// 添加到 listcontrol 的代码将根据你的界面框架而不同
			//MessageBox(CA2T(data.rankNum.c_str()));
			int index = m_listCtrl.GetItemCount();// 获取当前列表项数量
			m_listCtrl.InsertItem(index, _T(""));//要有这个，不然显示不了
			Data.Format(_T("%.2lf"), data.data);
			Num.Format(_T("%d"), index+1);
			// 插入用户、传感器类型、时间、数据和单位
			m_listCtrl.SetItemText(index, 0, Num);
			m_listCtrl.SetItemText(index, 1, CA2T(data.user.c_str()));
			m_listCtrl.SetItemText(index, 2, CA2T(data.sensorType.c_str()));
			m_listCtrl.SetItemText(index, 3, CA2T(data.time.c_str()));
			m_listCtrl.SetItemText(index, 4,Data);
			m_listCtrl.SetItemText(index, 5, CA2T(data.unit.c_str()));
			//MessageBox(CA2T(user.c_str()));
			//MessageBox(Data);
			//MessageBox(CA2T(data.rankNum.c_str()));
			found = true;
			index++;
		}
	}
	if (!found)
		{
		AfxMessageBox(_T("没有符合条件的数据"));
		//listInit();
		}
	*/
	m_listCtrl.DeleteAllItems();
	CString Data, Num;
	// 解析起始时间和结束时间
	tm startTime = parseTime(Stattime);
	tm endTime = parseTime(overime);

	//AfxMessageBox(startTime);
	// 遍历所有数据，检查每个数据条目是否符合查询条件，并将符合条件的添加到 listcontrol 中
	for (const auto& data : searchDataList) {
		bool match = true;

		// 检查用户
		if (!userQuery.empty() && data.user != userQuery) {
			match = false;
		}

		// 检查传感器类型
		if (!sensorTypeQuery.empty() && data.sensorType != sensorTypeQuery) {
			match = false;
		}

		// 检查时间范围
		tm dataTime = parseTime(data.time);
		int num = dataTime.tm_hour * 3600 + dataTime.tm_min * 60 + dataTime.tm_sec;
		int start= startTime.tm_hour * 3600 + startTime.tm_min * 60 + startTime.tm_sec;
		int over= endTime.tm_hour * 3600 + endTime.tm_min * 60 + endTime.tm_sec;
		if (!(this->starttime.IsEmpty()&& this->overtime.IsEmpty())&&(num < start || num > over)) {
			match = false;
		}

		// 检查数据范围
		if (!(this->maxData.IsEmpty() && this->minData.IsEmpty()) && (data.data < minData || data.data > maxData)) {
			CString a;
			a.Format(_T("%lf"), data.data);
			match = false;
		}

		// 如果所有条件都匹配，则将数据添加到 listcontrol 中
		if (match) {
			int index = m_listCtrl.GetItemCount(); // 获取当前列表项数量
			m_listCtrl.InsertItem(index, _T(""));  // 要有这个，不然显示不了
			Data.Format(_T("%.2lf"), data.data);
			Num.Format(_T("%d"), index + 1);
			
			// 使用 localtime_s 替代 localtime
				CString formattedTime;
				formattedTime.Format(_T("%02d:%02d:%02d"), dataTime.tm_hour, dataTime.tm_min, dataTime.tm_sec);

				// 插入用户、传感器类型、时间、数据和单位
				m_listCtrl.SetItemText(index, 0, Num);
				m_listCtrl.SetItemText(index, 1, CA2T(data.user.c_str()));
				m_listCtrl.SetItemText(index, 2, CA2T(data.sensorType.c_str()));
				m_listCtrl.SetItemText(index, 3, formattedTime);
				m_listCtrl.SetItemText(index, 4, Data);
				m_listCtrl.SetItemText(index, 5, CA2T(data.unit.c_str()));
				index++;
			
		}
		else
		{
			//AfxMessageBox(_T("没有"));
		}
	}
}

void DataSearch::SensorData(const std::string& r,const std::string& u, const std::string& s, const std::string& t, double d, const std::string& un)
{
	rankNum = r;
	user=u;
	sensorType=s;
	time=t;
	data = d;
	unit = un;
}


void DataSearch::SearchShow()
{
	// TODO: 在此处添加实现代码.
	
}


void DataSearch::listInit()
{
	// TODO: 在此处添加实现代码.

	std::ifstream file(m_FilePath);
	int rank = 1;
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
			int columnIndex = 0;

			// 插入新的一行
			int rowIndex = m_listCtrl.GetItemCount();
			m_listCtrl.InsertItem(rowIndex, _T(""));

			// 逐个读取每个字段，并插入到对应的列中
			while (getline(ss, item, ',')) {
				// 将string转换为CString
				CString str(item.c_str());

				// 插入到对应的列
				m_listCtrl.SetItemText(rowIndex, columnIndex, str);
				/**/
				switch (columnIndex) {
				case 0: {rankNum = item; break; }//MessageBox(CA2T(rankNum.c_str())); 
				case 1: user = item; break;
				case 2: sensorType = item; break;
				case 3: time = item; break;
				case 4: data = std::stod(item); break;
				case 5: unit = item; break;
				default: break;
				}
				
				columnIndex++;
			}
			DataSearch Data;
			Data.SensorData(rankNum, user, sensorType, time, data, unit);
			searchDataList.push_back(Data);

		}

		file.close();

	}/**/
}


void DataSearch::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void DataSearch::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_listCtrl.DeleteAllItems();
	std::ifstream file(m_FilePath);
	int rank = 1;
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
			int columnIndex = 0;

			// 插入新的一行
			int rowIndex = m_listCtrl.GetItemCount();
			m_listCtrl.InsertItem(rowIndex, _T(""));

			// 逐个读取每个字段，并插入到对应的列中
			while (getline(ss, item, ',')) {
				// 将string转换为CString
				CString str(item.c_str());

				// 插入到对应的列
				m_listCtrl.SetItemText(rowIndex, columnIndex, str);
				/**/
				columnIndex++;
			}
		}

		file.close();

	}/**/
}

#pragma once

// 计算机生成了通过 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 请勿修改此文件的内容。如果此类
// 通过 Microsoft Visual C++ 重新生成，则你的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////

#include "afxwin.h"

class CMSCOMM2 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CMSCOMM2)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= {0x648a5600, 0x2c6e, 0x101b, {0x82, 0xb6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14}};
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = nullptr)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID);
	}

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
				UINT nID, CFile* pPersist = nullptr, BOOL bStorage = FALSE,
				BSTR bstrLicKey = nullptr)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:
enum HandshakingConstants
{
	NoHandshaking = 0,
	XonXoff = 1,
	RtsCts = 2,
	XonXoffAndRtsCts = 3
};

enum HandshakeConstants
{
	comNone = 0,
	comXOnXoff = 1,
	comRTS = 2,
	comRTSXOnXOff = 3
};

enum ErrorConstants
{
	comInvalidPropertyValue = 380,
	comGetNotSupported = 394,
	comSetNotSupported = 383,
	comPortInvalid = 8002,
	comPortAlreadyOpen = 8005,
	comPortOpen = 8000,
	comNoOpen = 8012,
	comSetCommStateFailed = 8015,
	comPortNotOpen = 8018,
	comReadError = 8020,
	comDCBError = 8021,
	comBreak = 1001,
	comCTSTO = 1002,
	comDSRTO = 1003,
	comFrame = 1004,
	comOverrun = 1006,
	comCDTO = 1007,
	comRxOver = 1008,
	comRxParity = 1009,
	comTxFull = 1010,
	comDCB = 1011
};

enum CommEventConstants
{
	comEventBreak = 1001,
	comEventCTSTO = 1002,
	comEventDSRTO = 1003,
	comEventFrame = 1004,
	comEventOverrun = 1006,
	comEventCDTO = 1007,
	comEventRxOver = 1008,
	comEventRxParity = 1009,
	comEventTxFull = 1010,
	comEventDCB = 1011
};

enum OnCommConstants
{
	comEvSend = 1,
	comEvReceive = 2,
	comEvCTS = 3,
	comEvDSR = 4,
	comEvCD = 5,
	comEvRing = 6,
	comEvEOF = 7
};

enum InputModeConstants
{
	comInputModeText = 0,
	comInputModeBinary = 1
};



// 操作
public:
// IMSComm

// 函数
//

	void put_CDHolding(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_CDHolding()
	{
		BOOL result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_CDTimeout(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	long get_CDTimeout()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	void put_CommID(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	long get_CommID()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	void put_CommPort(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	short get_CommPort()
	{
		short result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}

	void put__CommPort(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	short get__CommPort()
	{
		short result;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}

	void put_CTSHolding(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_CTSHolding()
	{
		BOOL result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_CTSTimeout(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	long get_CTSTimeout()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	void put_DSRHolding(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_DSRHolding()
	{
		BOOL result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_DSRTimeout(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	long get_DSRTimeout()
	{
		long result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	void put_DTREnable(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_DTREnable()
	{
		BOOL result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_Handshaking(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xA, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	long get_Handshaking()
	{
		long result;
		InvokeHelper(0xA, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	void put_InBufferSize(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xB, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	short get_InBufferSize()
	{
		short result;
		InvokeHelper(0xB, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}

	void put_InBufferCount(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xC, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	short get_InBufferCount()
	{
		short result;
		InvokeHelper(0xC, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}

	void put_Break(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xD, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_Break()
	{
		BOOL result;
		InvokeHelper(0xD, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_InputLen(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xE, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	short get_InputLen()
	{
		short result;
		InvokeHelper(0xE, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}

	void put_Interval(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xF, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	long get_Interval()
	{
		long result;
		InvokeHelper(0xF, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	void put_NullDiscard(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_NullDiscard()
	{
		BOOL result;
		InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_OutBufferSize(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	short get_OutBufferSize()
	{
		short result;
		InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}

	void put_OutBufferCount(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	short get_OutBufferCount()
	{
		short result;
		InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}

	void put_ParityReplace(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	CString get_ParityReplace()
	{
		CString result;
		InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}

	void put_PortOpen(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_PortOpen()
	{
		BOOL result;
		InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_RThreshold(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	short get_RThreshold()
	{
		short result;
		InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}

	void put_RTSEnable(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_RTSEnable()
	{
		BOOL result;
		InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_Settings(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	CString get_Settings()
	{
		CString result;
		InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}

	void put_SThreshold(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	short get_SThreshold()
	{
		short result;
		InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}

	void put_Output(VARIANT newValue)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, &newValue);
	}

	VARIANT get_Output()
	{
		VARIANT result;
		InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}

	void put_Input(VARIANT newValue)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0x1A, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, &newValue);
	}

	VARIANT get_Input()
	{
		VARIANT result;
		InvokeHelper(0x1A, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}

	void put_CommEvent(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x1B, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	short get_CommEvent()
	{
		short result;
		InvokeHelper(0x1B, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}

	void put_EOFEnable(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x1C, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_EOFEnable()
	{
		BOOL result;
		InvokeHelper(0x1C, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_InputMode(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1D, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	long get_InputMode()
	{
		long result;
		InvokeHelper(0x1D, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}



};

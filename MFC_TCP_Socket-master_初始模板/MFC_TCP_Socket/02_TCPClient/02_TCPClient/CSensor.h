#pragma once
#include <afx.h>
class CSensor 
{
public:
    // 初始化传感器
    virtual BOOL Initialize() = 0;

    // 启动传感器
    virtual BOOL Start() = 0;

    // 停止传感器
    virtual BOOL Stop() = 0;

    // 获取传感器数据
    virtual double GetData() = 0;
};


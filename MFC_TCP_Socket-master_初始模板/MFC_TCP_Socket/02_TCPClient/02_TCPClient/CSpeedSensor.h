#pragma once
#include "CSensor.h"
class CSpeedSensor :
    public CSensor
{
private:
    double minSpeed=100;  // 最小速度
    double maxSpeed=10;  // 最大速度

public:
    // 构造函数，设置速度范围
    CSpeedSensor(double min, double max) : minSpeed(min), maxSpeed(max) {}
    virtual BOOL Initialize() = 0;
    virtual BOOL Start() = 0;

    // 停止传感器
    virtual BOOL Stop() = 0;

    // 获取传感器数据
    virtual double GetData() = 0;
    
};


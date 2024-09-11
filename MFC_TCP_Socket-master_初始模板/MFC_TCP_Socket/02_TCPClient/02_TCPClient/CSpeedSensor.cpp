#include "stdafx.h"
#include "CSpeedSensor.h"


// 实现初始化方法
 BOOL CSpeedSensor::Initialize()
{
    // 初始化速度传感器的代码
    return TRUE;
}

// 实现启动方法
 BOOL CSpeedSensor::Start()
{
    // 启动速度传感器的代码
    return TRUE;
}

// 实现停止方法
BOOL CSpeedSensor::Stop()
{
    // 停止速度传感器的代码
    return TRUE;
}

// 实现获取数据方法
double CSpeedSensor::GetData()
{
    // 生成合理范围内的随机速度
    double randomSpeed = minSpeed + (rand() / (double)RAND_MAX) * (maxSpeed - minSpeed);

    return randomSpeed;
}
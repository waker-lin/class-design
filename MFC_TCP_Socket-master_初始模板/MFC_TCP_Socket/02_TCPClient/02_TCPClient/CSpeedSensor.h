#pragma once
#include "CSensor.h"
class CSpeedSensor :
    public CSensor
{
private:
    double minSpeed=100;  // ��С�ٶ�
    double maxSpeed=10;  // ����ٶ�

public:
    // ���캯���������ٶȷ�Χ
    CSpeedSensor(double min, double max) : minSpeed(min), maxSpeed(max) {}
    virtual BOOL Initialize() = 0;
    virtual BOOL Start() = 0;

    // ֹͣ������
    virtual BOOL Stop() = 0;

    // ��ȡ����������
    virtual double GetData() = 0;
    
};


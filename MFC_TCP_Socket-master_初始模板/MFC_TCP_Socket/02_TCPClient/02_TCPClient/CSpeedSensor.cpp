#include "stdafx.h"
#include "CSpeedSensor.h"


// ʵ�ֳ�ʼ������
 BOOL CSpeedSensor::Initialize()
{
    // ��ʼ���ٶȴ������Ĵ���
    return TRUE;
}

// ʵ����������
 BOOL CSpeedSensor::Start()
{
    // �����ٶȴ������Ĵ���
    return TRUE;
}

// ʵ��ֹͣ����
BOOL CSpeedSensor::Stop()
{
    // ֹͣ�ٶȴ������Ĵ���
    return TRUE;
}

// ʵ�ֻ�ȡ���ݷ���
double CSpeedSensor::GetData()
{
    // ���ɺ���Χ�ڵ�����ٶ�
    double randomSpeed = minSpeed + (rand() / (double)RAND_MAX) * (maxSpeed - minSpeed);

    return randomSpeed;
}
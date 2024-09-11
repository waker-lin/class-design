#pragma once
#include <afx.h>
class CSensor 
{
public:
    // ��ʼ��������
    virtual BOOL Initialize() = 0;

    // ����������
    virtual BOOL Start() = 0;

    // ֹͣ������
    virtual BOOL Stop() = 0;

    // ��ȡ����������
    virtual double GetData() = 0;
};


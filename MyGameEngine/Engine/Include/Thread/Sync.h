#pragma once

#include "../EngineInfo.h"
//�Լ� ���� ������ ������� ���������� Ư���� �̿��Ͽ� ���� ����ȭ
class CSync
{
private:
	CRITICAL_SECTION* m_Crt;

public:
	CSync(CRITICAL_SECTION* Crt)
	{
		m_Crt = Crt;
		EnterCriticalSection(m_Crt); //��
	}

	~CSync()
	{
		LeaveCriticalSection(m_Crt); //���
	}
};


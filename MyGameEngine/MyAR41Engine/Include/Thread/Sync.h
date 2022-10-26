#pragma once

#include "../EngineInfo.h"
//함수 블럭이 끝나면 사라지는 지역변수의 특성을 이용하여 만든 동기화
class CSync
{
private:
	CRITICAL_SECTION* m_Crt;

public:
	CSync(CRITICAL_SECTION* Crt)
	{
		m_Crt = Crt;
		EnterCriticalSection(m_Crt); //락
	}

	~CSync()
	{
		LeaveCriticalSection(m_Crt); //언락
	}
};


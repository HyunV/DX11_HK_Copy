#pragma once

#include "../EngineInfo.h"

class CThread
{
	friend class CThreadManager;

protected:
	CThread();
	virtual ~CThread() = 0;

protected:
	HANDLE	m_Thread;
	HANDLE	m_StartEvent; //이벤트동기화 핸들
	bool	m_Loop;

public:
	void SetLoop(bool Loop)
	{
		m_Loop = Loop;
	}

public:
	void Suspend(); //대기, 일시정지 
	void Resume();  //재시작
	void ReStart(); //카운트에 상관없이 무조건 재시작이 필요한 경우
	void Stop();	//스레드를 멈출 때
	void Start();	

public:
	virtual bool Init();
	virtual void Run() = 0;

private:
	static unsigned int __stdcall ThreadFunction(void* Arg);
};


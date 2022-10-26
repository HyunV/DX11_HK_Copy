#pragma once

#include "Thread.h"

class CThreadManager
{
private:
	std::unordered_map<std::string, CThread*>	m_mapThread;
	std::unordered_map<std::string, CRITICAL_SECTION*>	m_mapCriticalSection;

public:
	bool Init();
	CThread* FindThread(const std::string& Name);

	bool CreateCriticalSection(const std::string& Name);
	CRITICAL_SECTION* FindCriticalSection(const std::string& Name);

public:
	template <typename T>
	T* Create(const std::string& Name)
	{
		T* Thread = (T*)FindThread(Name);

		if (Thread)
			return Thread;

		Thread = new T;

		if (!Thread->Init())
		{
			SAFE_DELETE(Thread);
			return nullptr;
		}

		m_mapThread.insert(std::make_pair(Name, Thread));

		return Thread;
	}

	DECLARE_SINGLE(CThreadManager)
};


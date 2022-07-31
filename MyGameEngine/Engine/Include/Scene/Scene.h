#pragma once

#include "SceneInfo.h"

class CScene
{
	friend class CSceneManager;

private:
	CScene();
	~CScene();

private:
	bool		m_Change;
	bool		m_Start;
	CSceneInfo* m_SceneInfo;


public:
	void Start();
	bool Init();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);

public:
	template <typename T>
	bool CreateSceneInfo()
	{
		SAFE_DELETE(m_SceneInfo);

		m_SceneInfo = new T;

		if (!m_SceneInfo->Init())
		{
			SAFE_DELETE(m_SceneInfo);
			return false;
		}

		return true;
	}
};


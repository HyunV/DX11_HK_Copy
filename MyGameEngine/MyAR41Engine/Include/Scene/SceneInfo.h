#pragma once

#include "../EngineInfo.h"

class CSceneInfo
{
	friend class CScene;

protected:
	CSceneInfo();
	virtual ~CSceneInfo();

protected:
	class CScene* m_Owner;

public:
	bool Init();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
};


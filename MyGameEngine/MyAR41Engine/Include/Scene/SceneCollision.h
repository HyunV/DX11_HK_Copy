#pragma once

#include "../EngineInfo.h"

class CSceneCollision
{
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	class CScene* m_Owner;

public:
	bool Init();
	void Update(float DeltaTime);
};


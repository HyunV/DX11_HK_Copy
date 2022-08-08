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
	CSharedPtr<class CGameObject> m_PlayerObject;
public:
	void SetPlayerObject(class CGameObject* Player);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
};


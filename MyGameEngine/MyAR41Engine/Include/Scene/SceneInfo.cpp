#include "SceneInfo.h"
#include "../GameObject/GameObject.h"

CSceneInfo::CSceneInfo()
{
}

CSceneInfo::~CSceneInfo()
{
}

void CSceneInfo::SetPlayerObject(CGameObject* Player)
{
	m_PlayerObject = Player;
}

bool CSceneInfo::Init()
{
	return true;
}

void CSceneInfo::Update(float DeltaTime)
{
}

void CSceneInfo::PostUpdate(float DeltaTime)
{
}

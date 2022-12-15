#include "MyGameManager.h"
#include "UI/UIImageBlack.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"


DEFINITION_SINGLE(CMyGameManager)

CMyGameManager::CMyGameManager()
{
}

CMyGameManager::~CMyGameManager()
{
}

bool CMyGameManager::Init()
{
    return true;
}

void CMyGameManager::SetPlayerInfo(PlayerInfo Info)
{
    m_PlayerInfo = Info;
}

void CMyGameManager::CreateFadeUI(EFade Fade)
{
}

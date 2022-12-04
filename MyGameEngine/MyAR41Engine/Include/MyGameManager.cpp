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

void CMyGameManager::SetPlayerInfo(int MaxHP, int HP, int Gio)
{
    m_PlayerInfo.MaxHP = MaxHP;
    m_PlayerInfo.HP = HP;
    m_PlayerInfo.Gio = Gio;
}

void CMyGameManager::CreateFadeUI(EFade Fade)
{
}

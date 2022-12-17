
#include "MainSceneInfo.h"
#include "Scene/Scene.h"
#include "../GameObject/Player2D.h"
//#include "../GameObject/Monster.h"
#include "../GameObject/GlobalWall.h"
//#include "../GameObject/Zombie.h"
//#include "../GameObject/Zombie2.h"
//#include "../UI/PlayerHUD.h"
//#include "../UI/StartSceneUI.h"
#include "../UI/MainTitleUI.h"
#include "../GameObject/NightMareKingGrimm.h"

CMainSceneInfo::CMainSceneInfo()
{
}

CMainSceneInfo::~CMainSceneInfo()
{
}

bool CMainSceneInfo::Init()
{
	CSceneInfo::Init();

   // m_Owner->GetViewport()->CreateUIWindow<CStartSceneUI>("StartSceneUI");
    m_Owner->GetViewport()->CreateUIWindow<CMainTitleUI>("MainTitleUI");
    //m_Owner->GetViewport()->CreateUIWindow<CPlayerHUD>("PlayerHUD");

    //CGlobalWall* GlobalWall = m_Owner->CreateObject<CGlobalWall>("GlobalWall");
    //CPlayer2D* Player = m_Owner->CreateObject<CPlayer2D>("Player2D");
    //CZombie* Zombie = m_Owner->CreateObject<CZombie>("Zombie");
    //CZombie2* Zombie2 = m_Owner->CreateObject<CZombie2>("Zombie2");
    //CNightMareKingGrimm* Grimm = m_Owner->CreateObject<CNightMareKingGrimm>("Grimm");
    //m_Owner->SetPlayer((CGameObject*)Player);
    //SetPlayerObject(Player);

	return true;
}
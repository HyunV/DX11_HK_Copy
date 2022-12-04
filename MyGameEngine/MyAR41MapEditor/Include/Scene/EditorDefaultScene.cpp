#include "EditorDefaultScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneViewport.h"
#include "../UI/StartSceneUI.h"
#include "../UI/MainTitleUI.h"
#include "../UI/PlayerHUD.h"

#include "../GameObject/Monster.h"
#include "../GameObject/Player2D.h"
#include "../GameObject/GlobalWall.h"
#include "../GameObject/Zombie.h"
#include "../GameObject/Zombie2.h"
#include "PathManager.h"

CEditorDefaultScene::CEditorDefaultScene()
{
    m_ClassTypeName = "EditorDefaultScene";
}

CEditorDefaultScene::~CEditorDefaultScene()
{
}

bool CEditorDefaultScene::Init()
{
    //m_Owner->GetViewport()->CreateUIWindow<CStartSceneUI>("StartSceneUI");
    m_Owner->GetViewport()->CreateUIWindow<CMainTitleUI>("MainTitleUI");
    //m_Owner->GetViewport()->CreateUIWindow<CPlayerHUD>("PlayerHUD");


    //�� ���Ϸε��===================================
    
    //char Name[256] = {};
    //const PathInfo* Path = CPathManager::GetInst()->FindPath(SCENE_PATH);
    //strcat_s(Name, Path->PathMultibyte);
    //strcat_s(Name, "01.TOWN");
    //strcat_s(Name, ".scn");

    //m_Owner->Load(Name);
    
    //=====================================================

    

    //CMonster* Monster = m_Owner->CreateObject<CMonster>("Monster");
    //CGlobalWall* GlobalWall = m_Owner->CreateObject<CGlobalWall>("GlobalWall");
    //CPlayer2D* Player = m_Owner->CreateObject<CPlayer2D>("Player2D");
    // 
    //Player->SetWorldPosition(0.f, 1000.f);
    //CZombie* Zombie = m_Owner->CreateObject<CZombie>("Zombie");
    //CZombie2* Zombie2 = m_Owner->CreateObject<CZombie2>("Zombie2");
    return true;
}

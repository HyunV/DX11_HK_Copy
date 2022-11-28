#include "EditorDefaultScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneViewport.h"
#include "../UI/StartSceneUI.h"
#include "../UI/MainTitleUI.h"
#include "../UI/PlayerHUD.h"

#include "../GameObject/Monster.h"
#include "../GameObject/Player2D.h"
#include "../GameObject/GlobalWall.h"

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
    //m_Owner->GetViewport()->CreateUIWindow<CMainTitleUI>("MainTitleUI");
    m_Owner->GetViewport()->CreateUIWindow<CPlayerHUD>("PlayerHUD");

    //CMonster* Monster = m_Owner->CreateObject<CMonster>("Monster");
    CGlobalWall* GlobalWall = m_Owner->CreateObject<CGlobalWall>("GlobalWall");
    CPlayer2D* Player = m_Owner->CreateObject<CPlayer2D>("Player2D");

    return true;
}

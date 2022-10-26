#include "EditorDefaultScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneViewport.h"
#include "../UI/StartSceneUI.h"

#include "../GameObject/Monster.h"

CEditorDefaultScene::CEditorDefaultScene()
{
    m_ClassTypeName = "EditorDefaultScene";
}

CEditorDefaultScene::~CEditorDefaultScene()
{
}

bool CEditorDefaultScene::Init()
{
    m_Owner->GetViewport()->CreateUIWindow<CStartSceneUI>("StartUI");

    //CMonster* Monster = m_Owner->CreateObject<CMonster>("Monster");

    return true;
}

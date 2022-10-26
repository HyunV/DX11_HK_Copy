#include "EditorTestScene.h"
#include "../GameObject/Player2D.h"
#include "../GameObject/Monster.h"
#include "Scene/Scene.h"

CEditorTestScene::CEditorTestScene()
{
	m_ClassTypeName = "EditorTestScene";
}

CEditorTestScene::~CEditorTestScene()
{
}

bool CEditorTestScene::Init()
{
	CSceneInfo::Init();

	CPlayer2D* Player = m_Owner->CreateObject<CPlayer2D>("Player2D");

	SetPlayerObject(Player);

	//CMonster* Monster = m_Owner->CreateObject<CMonster>("Monster");

	return true;
}

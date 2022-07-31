
#include "Scene.h"

CScene::CScene() :
	m_Change(false),
	m_Start(false)
{
	m_SceneInfo = new CSceneInfo;

	m_SceneInfo->Init();
}

CScene::~CScene()
{
	SAFE_DELETE(m_SceneInfo);
}

void CScene::Start()
{
	m_Start = true;
}

bool CScene::Init()
{
	return true;
}

void CScene::Update(float DeltaTime)
{
	if (m_SceneInfo)
		m_SceneInfo->Update(DeltaTime);
}

void CScene::PostUpdate(float DeltaTime)
{
	if (m_SceneInfo)
		m_SceneInfo->PostUpdate(DeltaTime);
}

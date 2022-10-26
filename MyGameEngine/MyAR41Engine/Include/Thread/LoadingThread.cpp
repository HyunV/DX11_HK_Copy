#include "LoadingThread.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "../PathManager.h"

CLoadingThread::CLoadingThread()	:
	m_LoadComplete(false)
{
	m_PathName = SCENE_PATH;
}

CLoadingThread::~CLoadingThread()
{
}

void CLoadingThread::Run()
{
	// Main Scene »ý¼º
	CSceneManager::GetInst()->CreateNextScene(false);

	const PathInfo* Info = CPathManager::GetInst()->FindPath(m_PathName);

	m_FullPath = Info->PathMultibyte + m_FileName;

	CSceneManager::GetInst()->GetNextScene()->Load(m_FullPath.c_str());

	m_LoadComplete = true;
}

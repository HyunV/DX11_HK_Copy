#pragma once

#include "SceneInfo.h"
#include "SceneResource.h"
#include "CameraManager.h"

class CScene
{
	friend class CSceneManager;

private:
	CScene();
	~CScene();

private:
	bool		m_Change;
	bool		m_Start;
	CSceneInfo* m_SceneInfo;
	CSceneResource* m_Resource;
	CCameraManager* m_CameraManager;
	std::list<CSharedPtr<class CGameObject>>	m_ObjList;

public:
	CSceneInfo* GetSceneInfo()	const
	{
		return m_SceneInfo;
	}

	CSceneResource* GetResource()	const
	{
		return m_Resource;
	}

	CCameraManager* GetCameraManager()	const
	{
		return m_CameraManager;
	}


public:
	void Start();
	bool Init();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);

public:
	class CGameObject* FindObject(const std::string& Name);

public:
	template <typename T>
	bool CreateSceneInfo()
	{
		SAFE_DELETE(m_SceneInfo);

		m_SceneInfo = new T;

		m_SceneInfo->m_Owner = this;

		if (!m_SceneInfo->Init())
		{
			SAFE_DELETE(m_SceneInfo);
			return false;
		}

		return true;
	}

	template <typename T>
	T* CreateObject(const std::string& Name)
	{
		T* Obj = new T;

		Obj->SetName(Name);
		Obj->SetScene(this);

		if (!Obj->Init())
		{
			SAFE_RELEASE(Obj);
			return nullptr;
		}

		m_ObjList.push_back(Obj);

		if (m_Start)
			Obj->Start();

		return Obj;
	}
};


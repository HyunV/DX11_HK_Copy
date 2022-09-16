
#include "Scene.h"
#include "../GameObject/GameObject.h"
#include "../Input.h"
#include "../Component/SpriteComponent.h"
#include "../Component/CameraComponent.h"
#include "../Component/TargetArm.h"
#include "../Component/SceneComponent.h"

std::unordered_map<std::string, CSceneInfo*> CScene::m_mapSceneInfoCDO;

CScene::CScene()	:
	m_Change(false),
	m_Start(false)
{
	m_Name = "Scene";

	m_SceneInfo = new CSceneInfo;

	m_SceneInfo->m_Owner = this;

	m_SceneInfo->Init();

	m_Resource = new CSceneResource;

	m_Resource->m_Owner = this;

	m_Resource->Init();

	m_CameraManager = new CCameraManager;

	m_CameraManager->m_Owner = this;

	m_CameraManager->Init();
}

CScene::~CScene()
{
	CInput::GetInst()->ClearCallback(this);

	SAFE_DELETE(m_CameraManager);
	SAFE_DELETE(m_Resource);
	SAFE_DELETE(m_SceneInfo);
}

void CScene::CreateCDO()
{
	CSceneInfo* Info = new CSceneInfo;

	Info->Init();

	CScene::AddSceneInfoCDO("SceneInfo", Info);

	CGameObject* ObjCDO = new CGameObject;

	ObjCDO->Init();

	CGameObject::AddObjectCDO("GameObject", ObjCDO);

	CComponent* ComCDO = new CSceneComponent;

	ComCDO->Init();

	CComponent::AddComponentCDO("SceneComponent", ComCDO);

	ComCDO = new CSpriteComponent;

	ComCDO->Init();

	CComponent::AddComponentCDO("SpriteComponent", ComCDO);

	ComCDO = new CCameraComponent;

	ComCDO->Init();

	CComponent::AddComponentCDO("CameraComponent", ComCDO);

	ComCDO = new CTargetArm;

	ComCDO->Init();

	CComponent::AddComponentCDO("TargetArm", ComCDO);
}

void CScene::Start()
{
	m_Start = true;

	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Start();
	}

	m_CameraManager->Start();
}

bool CScene::Init()
{
	return true;
}

void CScene::Update(float DeltaTime)
{
	if (m_SceneInfo)
		m_SceneInfo->Update(DeltaTime);

	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(DeltaTime);
		++iter;
	}

	m_CameraManager->Update(DeltaTime);
}

void CScene::PostUpdate(float DeltaTime)
{
	if (m_SceneInfo)
		m_SceneInfo->PostUpdate(DeltaTime);

	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostUpdate(DeltaTime);
		++iter;
	}

	m_CameraManager->PostUpdate(DeltaTime);
}

void CScene::Save(const char* FullPath)
{
	FILE* File = nullptr;

	fopen_s(&File, FullPath, "wb");
	// FullPath이름을 쓰기 형식으로 연다.
	 

	if (!File)
		return;

	// 이름 저장
	int	Length = (int)m_Name.length();

	fwrite(&Length, 4, 1, File);
	fwrite(m_Name.c_str(), 1, Length, File);

	// SceneInfo 저장
	m_SceneInfo->Save(File);

	int	ObjCount = (int)m_ObjList.size();

	fwrite(&ObjCount, 4, 1, File);

	//씬에 들어있는 오브젝트들 저장
	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		std::string	ClassTypeName = (*iter)->GetObjectTypeName();

		Length = (int)ClassTypeName.length();

		fwrite(&Length, 4, 1, File);
		fwrite(ClassTypeName.c_str(), 1, Length, File);

		(*iter)->Save(File);
	}

	fclose(File);
}

void CScene::Load(const char* FullPath)
{
	FILE* File = nullptr;

	fopen_s(&File, FullPath, "rb");

	if (!File)
		return;

	//이름 저장
	int	Length = 0;
	char	Name[256] = {};

	fread(&Length, 4, 1, File);
	fread(Name, 1, Length, File);

	m_Name = Name;

	//SceneInfo 저장
	Length = 0;
	char	SceneInfoName[256] = {};

	fread(&Length, 4, 1, File);
	fread(SceneInfoName, 1, Length, File);

	CSceneInfo* CDO = FindSceneInfoCDO(SceneInfoName);

	m_SceneInfo = CDO->Clone();

	m_SceneInfo->Load(File);

	int	ObjCount = 0;

	fread(&ObjCount, 4, 1, File);

	for (int i = 0; i < ObjCount; ++i)
	{
		Length = 0;

		char	ObjClassTypeName[256] = {};

		fread(&Length, 4, 1, File);
		fread(ObjClassTypeName, 1, Length, File);

		CGameObject* ObjCDO = CGameObject::FindCDO(ObjClassTypeName);
		
		CGameObject* NewObj = ObjCDO->Clone();
		
		NewObj->Load(File);
		
		m_ObjList.push_back(NewObj);
	}

	m_SceneInfo->LoadComplete();

	fclose(File);
}

CGameObject* CScene::FindObject(const std::string& Name)
{
	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == Name)
			return *iter;
	}

	return nullptr;
}
